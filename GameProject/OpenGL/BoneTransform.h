/*
 @file  BoneTransform.h
 @brief モデルのボーン変換
*/

/*
@brief プリプロセッサ
*/
#pragma once

class BoneTransform
{
public:

	//回転
	Quaternion mRotation;
	//移動
	Vector3 mTranslation;

	/*
	@fn 行列を出力
	@return 回転と平行移動から、行列を返す
	*/
	Matrix4 ToMatrix() const;
	
	/*
	@fn		ボーン補間
	@param	_NowFramePone	現在のフレームのポーズ
	@param	_NextFramePose	次のフレームのポーズ
	@param	_interpolation	補間値
	*/
	static BoneTransform Interpolate(const BoneTransform& _NowFramePone, const BoneTransform& _NextFramePose, float _interpolation);
};
