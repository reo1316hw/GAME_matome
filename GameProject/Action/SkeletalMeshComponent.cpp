#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "GameObject.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* owner)
	: MeshComponent(owner, true)
	, mSkeleton(nullptr)
	, mColor(Vector3(0,0,0))
{
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			//ワールド変換をセット
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// 行列パレットをセット    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//スペキュラー強度をセット
			_shader->SetFloatUniform("uSpecPower", 100);

			_shader->SetVectorUniform("uColor", mColor);
			//  テクスチャをセット 
			Texture* t = mMesh->GetTexture(mTextureIndex);
			if (t)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
				_shader->SetIntUniform("uMeshTexture", 0);
			}
			//メッシュの頂点配列をアクティブに
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//描画
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void SkeletalMeshComponent::Update(float deltaTime)
{
		if (mAnimation && mSkeleton)
		{
			mAnimTime += deltaTime * mAnimPlayRate;
			//  アニメを巻き戻して再生
			while (mAnimTime > mAnimation->GetDuration())
			{
				mAnimTime -= mAnimation->GetDuration();
			}

			// 行列パレットの再計算
			ComputeMatrixPalette();
		}
	
}

float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	mAnimation = _anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = _playRate;

	if (!mAnimation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;                                        
	// アニメ時刻時点のグローバルポーズの取得
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
