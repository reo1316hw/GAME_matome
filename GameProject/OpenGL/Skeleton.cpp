/*
@file  Skeleton.h
@brief 骨格
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn スケルトンのファイルからのロード
@param _FileName
@return 成功、失敗
*/
bool Skeleton::Load(const std::string& _FileName)
{
	// ファイル名からテキストファイルをオープンして、RapidJSONに解析させる
	std::ifstream file(_FileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Skeleton %s", _FileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSONオブジェクトか
	if (!doc.IsObject())
	{
		SDL_Log("Skeleton %s is not valid json", _FileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata　メタデータのチェック（バージョンチェック）
	if (ver != 1)
	{
		SDL_Log("Skeleton %s unknown format", _FileName.c_str());
		return false;
	}

	// bonecount ボーン数の取得
	const rapidjson::Value& Bonecount = doc["bonecount"];
	if (!Bonecount.IsUint())
	{
		SDL_Log("Skeleton %s doesn't have a bone count.", _FileName.c_str());
		return false;
	}

	size_t count = Bonecount.GetUint();

	// ボーン数がMAX_SKELETON_BONESを超えていた場合 (196本が最大)
	if (count > MAX_SKELETON_BONES)
	{
		SDL_Log("Skeleton %s exceeds maximum bone count.", _FileName.c_str());
		return false;
	}

	mBones.reserve(count);

	// ボーン配列の取得
	const rapidjson::Value& Bones = doc["bones"];
	if (!Bones.IsArray())
	{
		SDL_Log("Skeleton %s doesn't have a bone array?", _FileName.c_str());
		return false;
	}

	// ボーン配列のサイズとボーン数が異なる場合はエラーを返す
	if (Bones.Size() != count)
	{
		SDL_Log("Skeleton %s has a mismatch between the bone count and number of bones", _FileName.c_str());
		return false;
	}

	Bone temp;

	// ボーン配列数分ループ
	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		// ボーンが読めるか？
		if (!Bones[i].IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// "name" ボーン名
		const rapidjson::Value& Name = Bones[i]["name"];
		temp.mName = Name.GetString();

		// "parent" 親ボーンID
		const rapidjson::Value& Parent = Bones[i]["parent"];
		temp.mParent = Parent.GetInt();

		// "bindpose" バインドポーズ
		const rapidjson::Value& Bindpose = Bones[i]["bindpose"];
		if (!Bindpose.IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// バインドポーズの回転、位置
		const rapidjson::Value& Rot = Bindpose["rot"];
		const rapidjson::Value& Trans = Bindpose["trans"];

		// 回転と位置が配列じゃなかったらエラー返す
		if (!Rot.IsArray() || !Trans.IsArray())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", _FileName.c_str(), i);
			return false;
		}

		// バインドポーズの回転成分
		temp.mLocalBindPose.mRotation.x = static_cast<float>(Rot[0].GetDouble());
		temp.mLocalBindPose.mRotation.y = static_cast<float>(Rot[1].GetDouble());
		temp.mLocalBindPose.mRotation.z = static_cast<float>(Rot[2].GetDouble());
		temp.mLocalBindPose.mRotation.w = static_cast<float>(Rot[3].GetDouble());

		// バインドポーズの移動成分
		temp.mLocalBindPose.mTranslation.x = static_cast<float>(Trans[0].GetDouble());
		temp.mLocalBindPose.mTranslation.y = static_cast<float>(Trans[1].GetDouble());
		temp.mLocalBindPose.mTranslation.z = static_cast<float>(Trans[2].GetDouble());

		// ボーン配列に格納する
		mBones.emplace_back(temp);
	}

	// Now that we have the bones　ここでボーン配列は読みこまれているので、逆バインドポーズ行列を計算する
	ComputeGlobalInvBindPose();

	return true;
}

/*
@fn スケルトンがロードされたときに自動的に呼び出され各ボーンのグローバル逆バインドポーズを計算
*/
void Skeleton::ComputeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity    mGlobalInvIndPoses配列を、ボーン数分確保＆自動的に単位行列で初期化
	mGlobalInvBindPoses.resize(GetNumBones());

	// Step 1: Compute global bind pose for each bone　　　　　　　　　　　ステップ１：それぞれのボーンのグローバルバインドポーズを計算

	// The global bind pose for root is just the local bind pose         root ([0]のこと) のグローバルバインドポーズは、ローカルバインドポーズのことです。
	mGlobalInvBindPoses[0] = mBones[0].mLocalBindPose.ToMatrix();

	// Each remaining bone's global bind pose is its local pose          残りの各ボーンのグローバルバインドポーズは、
	// multiplied by the parent's global bind pose                       そのローカルポーズに親のグローバルバインドポーズを掛けたものです。
	for (size_t i = 1; i < mGlobalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = mBones[i].mLocalBindPose.ToMatrix();                     // そのボーンのローカルバインドポーズを行列に変換して locakMatに代入
		mGlobalInvBindPoses[i] = localMat * mGlobalInvBindPoses[mBones[i].mParent]; // localMat * 自分の親のグローバルバインドポーズ行列
	}

	// Step 2: Invert                                                   ステップ２：逆行列にする
	for (size_t i = 0; i < mGlobalInvBindPoses.size(); i++)
	{
		mGlobalInvBindPoses[i].Invert();
	}
}
