/*
@file  Renderer.h
@brief 描画の進行を行うクラス
*/

/*
@brief インクルード
*/
#include "pch.h"

//自分のインスタンスの初期化
Renderer* Renderer::mRenderer = nullptr;

/*
@fn	パーティクル用頂点を設定
*/
void Renderer::SetParticleVertex()
{
	mParticleVertex->SetActive();
}

/*
@fn	コンストラクタ
*/
Renderer::Renderer()
	: mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
	, mUiShader(nullptr)
	, mUiVerts(nullptr)
	, mMeshShader(nullptr)
	, mInvisibleMeshShader(nullptr)
	, mBasicShader(nullptr)
	, mParticleVertex(nullptr)
	, mView(Matrix4::sIDENTITY)
	, mProjection(Matrix4::sIDENTITY)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mAmbientLight(Vector3::sZERO)
	, mSkinnedShader(nullptr)
	, mUndefineTexID(0)
	, mHDRRenderer(nullptr)
{
}

/*
@fn	デストラクタ
*/
Renderer::~Renderer()
{
	delete mHDRRenderer;
}

/*
@fn		インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/*
@fn		インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

/*
@fn		初期化処理
@return true : 成功 , false : 失敗(bool型)
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	mScreenWidth = _screenWidth;
	mScreenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成
	mWindow = SDL_CreateWindow("OpenGL Game", 1, 1,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);

	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
	}

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mSdlRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	// 未定義テクスチャ
	mUndefineTexID = GetTexture("Assets/noneTexture.png")->GetTextureID();

	// HDRレンダラー初期化
	mHDRRenderer = new HDRRenderer(mScreenWidth, mScreenHeight, 4);

	//// カリング
	glFrontFace(GL_CCW);
	glEnable(GL_FRONT_FACE);

	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	// UIの初期座標に加算される座標
	mAddPosition = Vector2::sZERO;

	return true;
}

/*
@fn	終了処理
*/
void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	delete mUiVerts;
	mUiShader->Unload();
	delete mUiShader;
	mMeshShader->Unload();
	delete mMeshShader;
	mInvisibleMeshShader->Unload();
	delete mInvisibleMeshShader;
	mBasicShader->Unload();
	delete mBasicShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

/*
@fn	ロードしたデータの解放
*/
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// Unload animations
	for (auto a : mAnims)
	{
		delete a.second;
	}

	mMeshes.clear();
}

/*
@fn	描画処理
*/
void Renderer::Draw()
{

	mHDRRenderer->HdrRecordBegin();
	
	//アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	//デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);

	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	// すべてのスプライトの描画
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}

	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// インビジブルメッシュコンポーネントの描画
	// 基本的なインビジブルメッシュシェーダーをアクティブにする
	mInvisibleMeshShader->SetActive();
	// ビュー射影行列を更新する
	mInvisibleMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// シェーダーに渡すライティング情報を更新する
	SetLightUniforms(mInvisibleMeshShader, mView);
	// すべてのメッシュの描画
	for (auto imc : mInvisibleMeshComponents)
	{
		if (imc->GetVisible())
		{
			imc->Draw(mInvisibleMeshShader);
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// メッシュコンポーネントの描画
	// 基本的なメッシュシェーダーをアクティブにする
	mMeshShader->SetActive();
	// ビュー射影行列を更新する
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// シェーダーに渡すライティング情報を更新する
	SetLightUniforms(mMeshShader, mView);
	// すべてのメッシュの描画
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}
	
	mHDRRenderer->HdrRecordEnd();

	//////////////////////////////////////////////////////////////////
	// HDR Bloom の作成＆合成
	/////////////////////////////////////////////////////////////////
	mHDRRenderer->HiBrightBlurCreate();
	mHDRRenderer->HdrTonemapAndBrightBlurCombine();

	// HDRBufferにレンダリングしたときのDepth情報をスクリーンにコピー
	mHDRRenderer->CopyDepthToScreen();

	DrawParticle();

	// UIの描画
	// アルファブレンディングを有効にする
	glEnable(GL_BLEND);
	// デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);
	// RGB成分とα成分のブレンディング方法を別々に設定
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// UIシェーダーをアクティブにする/スプライト頂点配列を有効にする
	mUiShader->SetActive();
	mUiVerts->SetActive();
	// すべてのUIの描画
	for (auto ui : mUis)
	{
		if (ui->GetVisible())
		{
			ui->Draw(mUiShader, ui->GetOwner()->GetPosition());
		}
	}

		// バッファを交換
	SDL_GL_SwapWindow(mWindow);
}

/*
@fn		スプライトの追加
@param	_spriteComponent　追加するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* _spriteComponent)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
	int myDrawOrder = _spriteComponent->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mSprites.insert(iter, _spriteComponent);
}

/*
@fn		スプライトの削除
@param	_spriteComponent　削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* _spriteComponent)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), _spriteComponent);
	mSprites.erase(iter);
}

/*
@fn		UIの追加
@param	_ui　追加するUIクラスのポインタ
*/
void Renderer::AddUI(UIComponent* _ui)
{
	// 今あるスプライトから挿入する場所の検索
	// (DrawOrderが小さい順番に描画するため)
	int myUiDrawOrder = _ui->GetDrawOrder();
	auto iterUi = mUis.begin();
	for (;
		iterUi != mUis.end();
		++iterUi)
	{
		if (myUiDrawOrder < (*iterUi)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mUis.insert(iterUi, _ui);
}

/*
@fn		UIの削除
@param	_ui　削除するUIクラスのポインタ
*/
void Renderer::RemoveUI(UIComponent* _ui)
{
	auto iterUi = std::find(mUis.begin(), mUis.end(), _ui);
	mUis.erase(iterUi);
}

/*
@fn		パーティクルの追加
@param	_particleComponent　追加するParticleObjectクラスのポインタ
*/
void Renderer::AddParticle(ParticleComponent* _particleComponent)
{
	int myDrawOrder = _particleComponent->GetDrawOrder();
	auto iter = mParticles.begin();
	for (;
		iter != mParticles.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mParticles.insert(iter, _particleComponent);
}

/*
@fn		パーティクルの削除
@param	_particleComponent 削除するParticleObjectクラスのポインタ
*/
void Renderer::RemoveParticle(ParticleComponent* _particleComponent)
{
	auto iter = std::find(mParticles.begin(), mParticles.end(), _particleComponent);
	mParticles.erase(iter);
}

/*
@fn		メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		mMeshComponents.emplace_back(_meshComponent);
	}
}

/*
@fn		メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComponents.begin(), mMeshComponents.end(), _meshComponent);
		mMeshComponents.erase(iter);
	}
}

/*
@fn		半透明メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void Renderer::AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent)
{
	mInvisibleMeshComponents.emplace_back(_invisibleMeshComponent);
}

/*
@fn		半透明メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent)
{
	auto iter = std::find(mInvisibleMeshComponents.begin(), mInvisibleMeshComponents.end(), _invisibleMeshComponent);
	mInvisibleMeshComponents.erase(iter);
}

/*
@param _FileName モデルへのアドレス
@return スケルトンモデルの取得(class Skeleton)
*/
const Skeleton * Renderer::GetSkeleton(const char* _FileName)
{
	std::string file(_FileName);
	auto iter = mSkeletons.find(file);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/*
@param _FileName アニメーションへのアドレス
@return スケルトンアニメーションの取得(class Animation)
*/
const Animation * Renderer::GetAnimation(const char* _FileName)
{
	auto iter = mAnims.find(_FileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(_FileName))
		{
			mAnims.emplace(_FileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@param	_FileName　取得したいテクスチャのファイル名
@return Textureクラスのポインタ(class Texture)
*/
Texture* Renderer::GetTexture(const std::string& _FileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = mTextures.find(_FileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_FileName))
		{
			mTextures.emplace(_FileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/*
@param	_FileName 取得したいメッシュのファイル名
@return Meshクラスのポインタ(class Mesh)
*/
Mesh* Renderer::GetMesh(const std::string& _FileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = mMeshes.find(_FileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_FileName, this))
		{
			mMeshes.emplace(_FileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@fn		シェーダーの読み込み
@return true : 成功 , false : 失敗(bool型)
*/
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	// UIシェーダーの作成
	mUiShader = new Shader();
	if (!mUiShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mUiShader->SetActive();
	// ビュー行列の設定
	Matrix4 viewUiProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mUiShader->SetMatrixUniform("uViewProj", viewUiProj);

	// 標準のメッシュシェーダーの作成
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
	{
		return false;
	}

	// インビジブルメッシュシェーダーの作成
	mInvisibleMeshShader = new Shader();
	if (!mInvisibleMeshShader->Load("Shaders/Phong.vert", "Shaders/HDRMesh.frag"))
	{
		return false;
	}

	mBasicShader = new Shader();
	if (!mBasicShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag"))
	{
		return false;
	}

	mParticleShader = new Shader();
	if (!mParticleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/Phong.frag"))
	{
		return false;
	}
	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// メッシュ
	mMeshShader->SetActive();
	// ビュー行列の設定
	mView = Matrix4::CreateLookAt(Vector3::sZERO, Vector3::sUNIT_X, Vector3::sUNIT_Y);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// インビジブルメッシュ
	mInvisibleMeshShader->SetActive();
	// ビュー行列の設定
	mView = Matrix4::CreateLookAt(Vector3::sZERO, Vector3::sUNIT_X, Vector3::sUNIT_Z);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
	mInvisibleMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);
	return true;
}

/*
@fn	Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
	mUiVerts = new VertexArray(vertices, 4, indices, 6);
}

/*
@fn	Particle用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateParticleVerts()
{
	float vertices[] = {
		-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 2, 1,
		2, 0, 3
	};
	mParticleVertex = new VertexArray(vertices, 4, VertexArray::Layout::ePosNormTex, indices, 6);
}

/*
@fn	Particleの描画
*/
void Renderer::DrawParticle()
{

	std::sort(mParticles.begin(), mParticles.end(), std::greater<ParticleComponent*>());

	if (mParticles.size() == 0)
	{
		return;
	}
	// ブレンドモード初期状態取得
	ParticleComponent::ParticleBlendType blendType, prevType;
	auto itr = mParticles.begin();
	blendType = prevType = (*itr)->GetBlendType();

	// テクスチャID初期状態取得
	int nowTexture, prevTexture;
	nowTexture = prevTexture = (*itr)->GetTextureID();

	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;
	viewProjectionMat = mView * mProjection;

	// シェーダーON
	mParticleShader->SetActive();
	mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);

	// 全てのパーティクルのビルボード行列をセット
	Matrix4 tmp;
	tmp = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	(*itr)->SetBillboardMat(tmp);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	// すべてのパーティクルを描画
	ChangeBlendMode(blendType);
	ChangeTexture(nowTexture);

	for (auto particle : mParticles)
	{
		if (particle->GetVisible())
		{
			//ブレンドモード変更が必要なら変更する
			blendType = particle->GetBlendType();
			blendType = particle->GetBlendType();
			if (blendType != prevType)
			{
				ChangeBlendMode(blendType);
			}
			// テクスチャ変更が必要なら変更する
			nowTexture = particle->GetTextureID();
			if (nowTexture != prevTexture)
			{
				ChangeTexture(nowTexture);
			}

			// パーティクル描画
			particle->Draw(mParticleShader);

			// 前回描画状態として保存
			prevType = blendType;
			prevTexture = nowTexture;
		}
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

/*
@fn	Particleの描画
@param	_framebuffer フレームバッファ
@param	_View ビュー行列
@param	_Proj プロジェクション行列
@param	_viewPortScale 表示領域スケール
@param	_lit 光源情報をシェーダーの変数にセットするかのフラグ
*/
void Renderer::Draw3DScene(unsigned int _framebuffer, const Matrix4 & _View, const Matrix4 & _Proj, float _viewPortScale, bool _lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * _viewPortScale),
		static_cast<int>(mScreenHeight * _viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// Set the mesh shader active
	mMeshShader->SetActive();
	// Update view-mProjection matrix
	mMeshShader->SetMatrixUniform("uViewProj", _View * _Proj);
	// Update lighting uniforms
	if (_lit)
	{
		SetLightUniforms(mMeshShader, _View);
	}
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

}

/*
@fn		光源情報をシェーダーの変数にセットする
@param  _shader セットするShaderクラスのポインタ
@param	_View ビュー行列
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _View)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _View;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.m_direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.m_diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.m_specColor);
}

/*
@fn		光源情報をシェーダーの変数にセットする
@param  _blendType パーティクルに対するブレンドの種類
*/
void Renderer::ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType)
{
	switch (_blendType)
	{
	case ParticleComponent::ParticleBlendType::eParticleBlendAdd:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::ParticleBlendType::eParticleBlendAlpha:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::ParticleBlendType::eParticleBlendMult:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

/*
@fn		テクスチャの変更
@param	_changeTextureID 変更するテクスチャのid
*/
void Renderer::ChangeTexture(int _changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _changeTextureID);
}

/*
@fn	ワールド空間のカメラ座標を計算
*/
Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = mView;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * mView.mat[3][0];
	v.y = -1.0f * mView.mat[3][1];
	v.z = -1.0f * mView.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}