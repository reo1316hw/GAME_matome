/*
@file  SkeletalMeshComponent.h
@brief スケルトンデータの描画とアニメーション
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	   コンストラクタ
@param _owner アタッチするゲームオブジェクトのポインタ
*/
SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	: MeshComponent(_owner, true)
	, MSkeleton(nullptr)
	, mColor(Vector3(0,0,0))
{
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() != State::eDead)
	{
		if (mMesh)
		{
			//スペキュラー強度
			const float SpecPower = 100.0f;

			//ワールド変換をセット
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			//行列パレットをセット    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//スペキュラー強度をセット
			_shader->SetFloatUniform("uSpecPower", SpecPower);

			_shader->SetVectorUniform("uColor", mColor);

			// テクスチャ情報をシェーダーに渡す
			HandOverTexture(_shader);
			
			//メッシュの頂点配列をアクティブに
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//描画
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@fn		テクスチャ情報をシェーダーに渡す
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::HandOverTexture(Shader* _shader)
{
	//  テクスチャをセット 
	Texture* t = mMesh->GetTexture(mTextureIndex);
	if (t)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
		_shader->SetIntUniform("uMeshTexture", 0);
	}
}

/*
@fn		フレーム毎の処理
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void SkeletalMeshComponent::Update(float _deltaTime)
{
	if (MAnimation && MSkeleton)
	{
		mAnimTime += _deltaTime * mAnimPlayRate;
		//  アニメを巻き戻して再生
		while (mAnimTime > MAnimation->GetDuration())
		{
			mAnimTime -= MAnimation->GetDuration();
		}

		// 行列パレットの再計算
		ComputeMatrixPalette();
	}
}

/*
@fn		アニメーションの再生
@param	_Anim アニメーションデータクラス
@param	_playRate アニメーションの再生速度
@return	アニメーションの残り時間
*/
float SkeletalMeshComponent::PlayAnimation(const Animation* _Anim, float _playRate) 
{
	MAnimation = _Anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = _playRate;

	if (!MAnimation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return MAnimation->GetDuration();
}

/*
@fn 行列パレットの計算
*/
void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& GlobalInvBindPoses = MSkeleton->GetGlobalInvBindPoses();
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;                                        
	// アニメ時刻時点のグローバルポーズの取得
	MAnimation->GetGlobalPoseAtTime(currentPoses, MSkeleton, mAnimTime);
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < MSkeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		mPalette.mEntry[i] = GlobalInvBindPoses[i] * currentPoses[i];
	}
}
