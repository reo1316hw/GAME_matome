/*
@file  Mesh.h
@brief メッシュデータ
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		テクスチャステージを読み込み
@param	_Doc rapidJsonオブジェクト
@param	_texStage テクスチャステージ
@param	_stgString メンバ名
@return	テクスチャのID(int型)
*/
int LoadStageTextures(const rapidjson::Document& _Doc, TextureStage _texStage, const char* _StgString);

namespace
{
	union Vertex
	{
		float f;
		uint8_t b[4];
	};
}

/*
@fn	コンストラクタ
*/
Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	, mLuminance(1.0f)
	, mAlpha(1.0f)
	, mBox(Vector3::sINFINITY, Vector3::sNEG_INFINITY)
{
	mStageDefTexture.emplace(TextureStage::eDiffuseMap, 0);
	mStageDefTexture.emplace(TextureStage::eNormalMap, 0);
	mStageDefTexture.emplace(TextureStage::eSpecularMap, 0);
	mStageDefTexture.emplace(TextureStage::eEmissiveMap, 0);
}

/*
@fn		メッシュデータの読み込み
@param	_FileName ロードしたいメッシュのファイル名
@param	_renderer Rendererクラスのポインタ
@return true : 成功 , false : 失敗(bool型)
*/
bool Mesh::Load(const std::string & _FileName, Renderer* _renderer)
{
	std::ifstream file(_FileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s", _FileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s is not valid json", _FileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// バージョンのチェック
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", _FileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// Skip the vertex format/shader for now
	// (This is changed in a later chapter's code)
	// 頂点レイアウトとサイズをファイルからセット
	VertexArray::Layout layout = VertexArray::Layout::ePosNormTex;
	size_t vertSize = 8;

	std::string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::Layout::ePosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s　1個の頂点の集合の数　８　＋　２（スキニング分）
		// 3 (位置xyz) + 3(法線xyz) + 2(Boneと重み）＋　2(UV)  の計　10個分（40byte) 　
		vertSize = 10;
	}

	// テクスチャのロード
	const rapidjson::Value& ReadTextures = doc["textures"];
	if (!ReadTextures.IsArray() || ReadTextures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", _FileName.c_str());
		return false;
	}
	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	// エミッシブ強度値（定義されていれば)
	if (IsExistMember(doc, "luminance"))
	{
		mLuminance = ForceGetFloat(doc["luminance"]);
	}

	// 透明度
	if (IsExistMember(doc, "alpha"))
	{
		mAlpha = ForceGetFloat(doc["alpha"]);
	}

	for (rapidjson::SizeType i = 0; i < ReadTextures.Size(); i++)
	{
		// すでにロードされたテクスチャじゃないか調べる
		std::string texName = ReadTextures[i].GetString();
		Texture* t = _renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// テクスチャを取得する
			t = _renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// テクスチャが取得できなかった場合、デフォルトのテクスチャを使用
				t = _renderer->GetTexture("Assets/Default.png");
			}
		}
		mTextures.emplace_back(t);

		if (ReadTextures.Size() == 1)
		{
			mStageDefTexture[TextureStage::eDiffuseMap] = t->GetTextureID();
		}
	}

	// テクスチャ読み込み(新ファイル形式)
	if (IsExistMember(doc, "diffusemap"))
	{
		mStageDefTexture[TextureStage::eDiffuseMap] = LoadStageTextures(doc, TextureStage::eDiffuseMap, "diffusemap");
	}
	mStageDefTexture[TextureStage::eNormalMap] = LoadStageTextures(doc, TextureStage::eNormalMap, "normalmap");
	mStageDefTexture[TextureStage::eSpecularMap] = LoadStageTextures(doc, TextureStage::eSpecularMap, "specularmap");
	mStageDefTexture[TextureStage::eEmissiveMap] = LoadStageTextures(doc, TextureStage::eEmissiveMap, "emissivemap");

	// 頂点配列データをロード
	const rapidjson::Value& VertsJson = doc["vertices"];
	if (!VertsJson.IsArray() || VertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", _FileName.c_str());
		return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(VertsJson.Size() * vertSize);
	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < VertsJson.Size(); i++)
	{
		// 今のところは８つの要素とする
		const rapidjson::Value& Vert = VertsJson[i];
		if (!Vert.IsArray())
		{
			SDL_Log("Unexpected vertex format for %s", _FileName.c_str());
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////
		Vector3 pos(static_cast<float>(Vert[0].GetDouble()),
			static_cast<float>(Vert[1].GetDouble()),
			static_cast<float>(Vert[2].GetDouble()));
		//verts.push_back(pos);
		mRadius = Math::Max(mRadius, pos.LengthSq());

		if (i == 0)
		{
			mBox.InitMinMax(pos);
		}
		mBox.UpdateMinMax(pos);

		// 頂点レイアウトが PosNormTexなら（ボーンが無い）
		if (layout == VertexArray::Layout::ePosNormTex)
		{
			Vertex v;
			// Add the floats　float値を追加
			for (rapidjson::SizeType j = 0; j < Vert.Size(); j++)
			{
				v.f = static_cast<float>(Vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal　頂点と法線を追加　6個分
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(Vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information　スキン情報追加（ボーン番号:unsigned charの1バイト分）
			for (rapidjson::SizeType j = 6; j < 14; j += 4)  //ループとしては2回転する　1回転目はボーン番号、2回転目はボーンウェイトをintとして取ってくる（使用時に浮動小数化するっぽい）
			{
				v.b[0] = Vert[j].GetUint();
				v.b[1] = Vert[j + 1].GetUint();
				v.b[2] = Vert[j + 2].GetUint();
				v.b[3] = Vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords　テクスチャ座標
			for (rapidjson::SizeType j = 14; j < Vert.Size(); j++)
			{
				v.f = static_cast<float>(Vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
	}

	// 半径を2乗する
	mRadius = Math::Sqrt(mRadius);

	// 要素配列データのロード
	const rapidjson::Value& IndJson = doc["indices"];
	if (!IndJson.IsArray() || IndJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", _FileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(IndJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < IndJson.Size(); i++)
	{
		const rapidjson::Value& Ind = IndJson[i];
		if (!Ind.IsArray() || Ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", _FileName.c_str());
			return false;
		}

		indices.emplace_back(Ind[0].GetUint());
		indices.emplace_back(Ind[1].GetUint());
		indices.emplace_back(Ind[2].GetUint());
	}

	// ここでVertexArrayクラスの作成
	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		layout,indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

/*
@fn	ロードしたメッシュデータの解放
*/
void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

/*
@param	_index テクスチャサイズ
@return Textureクラスのポインタ(class Texture)
*/
Texture* Mesh::GetTexture(size_t _index)
{
	if (_index < mTextures.size())
	{
		return mTextures[_index];
	}
	else
	{
		return nullptr;
	}
}

/*
@param	_stage テクスチャステージ
@return テクスチャのID(int型)
*/
int Mesh::GetTextureID(TextureStage _stage)
{
	return mStageDefTexture[_stage];
}

/*
@fn		テクスチャステージを読み込み
@param	_Doc rapidJsonオブジェクト
@param	_texStage テクスチャステージ
@param	_StgString メンバ名
@return	テクスチャのID(int型)
*/
int LoadStageTextures(const rapidjson::Document& _Doc, TextureStage _texStage, const char* _StgString)
{
	std::string noneTexture("none");
	std::string texName;
	Texture* t;
	if (IsExistMember(_Doc, _StgString))
	{
		texName = _Doc[_StgString].GetString();
		if (texName != noneTexture)
		{
			t = RENDERER->GetTexture(texName);
			if (t == nullptr)
			{
				t = RENDERER->GetTexture("Assets/Texture/Object/NoneTexture.png");
			}
			return t->GetTextureID();
		}
	}
	return 0;
}
