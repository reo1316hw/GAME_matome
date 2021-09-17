/*
 @file  BoneTransform.h
 @brief モデルのボーン変換
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn 行列を出力
@return 回転と平行移動から、行列を返す
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// 回転と平行移動から、行列を返す
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

/*
@fn		ボーン補間
@param	_NowFramePone	現在のフレームのポーズ
@param	_NextFramePose	次のフレームのポーズ
@param	_interpolation	補間値
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& _NowFramePone, const BoneTransform& _NextFramePose, float _interpolation)
{
	BoneTransform retVal;
	retVal.mRotation = Quaternion::Slerp(_NowFramePone.mRotation, _NextFramePose.mRotation, _interpolation);        // aからb に数値fで球面線形補間(slerp)する
	retVal.mTranslation = Vector3::Lerp(_NowFramePone.mTranslation, _NextFramePose.mTranslation, _interpolation);   // 平行移動成分はf で線形補間(lerp)する
	return retVal;
}
