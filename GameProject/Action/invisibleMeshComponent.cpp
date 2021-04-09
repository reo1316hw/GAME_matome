#include "InvisibleMeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

/*
@fn		コンストラクタ
@param	_owner アタッチするゲームオブジェクトのポインタ
@param	_skelton スケルトンデータを用いるか。
@sa	SkeletalMeshComponent.h
*/
InvisibleMeshComponent::InvisibleMeshComponent(GameObject* _owner, bool _skelton)
	: Component(_owner)
	, mMesh(nullptr)
	, mTextureIndex(0)
	, mVisible(true)
	, mSkeltonFlag(_skelton)
{
	//レンダラーにポインターを送る
	RENDERER->AddInvisibleMeshComponent(this);
}

/*
@fn	デストラクタ
*/
InvisibleMeshComponent::~InvisibleMeshComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveInvisibleMeshComponent(this);
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void InvisibleMeshComponent::Draw(Shader* _shader)
{
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			// Set the world transform
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// Set specular power
			_shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

			_shader->SetFloatUniform("uLuminance", mMesh->GetLuminace());

			_shader->SetFloatUniform("uAlpha", mMesh->GetAlpha());
			// Set the active texture

			// メッシュに定義されているテクスチャをセット
			SetTextureToShader(_shader);

			// Set the argMesh's vertex array as active
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			// Draw
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@fn		テクスチャをステージごとにセット
@brief	ディフューズマップ	stage00
		法線マップ			stage01
		スペキュラーマップ	stage02
		自己放射マップ		stage03
@param	_shader 使用するシェーダークラスのポインタ
*/
void InvisibleMeshComponent::SetTextureToShader(Shader* _shader)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mMesh->GetTextureID(TextureStage::DiffuseMap); // ディフューズマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::NormalMap); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::SpecularMap); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mMesh->GetTextureID(TextureStage::EmissiveMap); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}
