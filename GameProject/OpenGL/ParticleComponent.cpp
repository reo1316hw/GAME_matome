/*
@file  ParticleComponent.h
@brief 画像を管理しそれを3D空間上に描画するクラス。
*/

/*
@brief インクルード
*/
#include "pch.h"

// ビルボード行列
Matrix4 ParticleComponent::mStaticBillboardMat;
// カメラのワールド座標
Vector3 ParticleComponent::mStaticCameraWorldPos;

/*
@fn	   コンストラクタ
@param _owner アタッチするゲームオブジェクトのポインタ
@param _Offset 親オブジェクトクラスと画像を描画する位置の差
@param _scale 画像の描画サイズ
@param _updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
ParticleComponent::ParticleComponent(GameObject* _owner, const Vector3& _Offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mOffset(_Offset)
	, mScale(_scale)
	, mAlpha(1.0f)
	, mBlendType(ParticleEnum::eParticleBlendAlpha)
	, mVisible(true)
	, mDrawOrder(_updateOrder)
	, mColor(Vector3(1, 1, 1))
	, mReverce(false)
	, mTextureID(0)
{
	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

/*
@fn	デストラクタ
*/
ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/*
@fn		描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void ParticleComponent::Draw(Shader* _shader)
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() == State::eDead)
	{
		return;
	}
	Matrix4 mat, matScale;
	Vector3 reverceVec = Vector3(1, 1, 1);
	//サイズを反転させる
	if (mReverce)
	{
		reverceVec.x *= -1;
	}
	matScale = Matrix4::CreateScale(mScale*reverceVec* mOwner->GetScale());

	_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mOwner->GetWorldTransform());
	_shader->SetFloatUniform("uAlpha", mAlpha);
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// カメラ距離でのソート用
bool ParticleComponent::operator<(const ParticleComponent& _Rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _Rhs.mOffset).LengthSq();
	return lenThis < lenRhs;
}

// カメラ距離でのソート用
bool ParticleComponent::operator>(const ParticleComponent& _Rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - _Rhs.mOffset).LengthSq();
	return lenThis > lenRhs;
}