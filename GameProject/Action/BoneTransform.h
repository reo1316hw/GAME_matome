#pragma once
#include "Math.h"

/*
 @file BoneTransform.h
 @fn ���f���̃{�[���ϊ�
*/
class BoneTransform
{
public:
	//��]
	Quaternion mRotation;
	//�ړ�
	Vector3 mTranslation;

	/*
	@fn �s����o��
	@return ��]�ƕ��s�ړ�����A�s���Ԃ�
	*/
	Matrix4 ToMatrix() const;
	
	/*
	@fn		�{�[�����
	@param	_nowFrameBone	���݂̃t���[���̃|�[�Y
	@param	_nextFrameBone	���̃t���[���̃|�[�Y
	@param	_interpolation	��Ԓl
	*/
	static BoneTransform Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, float _interpolation);
};
