/*
 @file  BoneTransform.h
 @brief ���f���̃{�[���ϊ�
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn �s����o��
@return ��]�ƕ��s�ړ�����A�s���Ԃ�
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// ��]�ƕ��s�ړ�����A�s���Ԃ�
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

/*
@fn		�{�[�����
@param	_NowFramePone	���݂̃t���[���̃|�[�Y
@param	_NextFramePose	���̃t���[���̃|�[�Y
@param	_interpolation	��Ԓl
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& _NowFramePone, const BoneTransform& _NextFramePose, float _interpolation)
{
	BoneTransform retVal;
	retVal.mRotation = Quaternion::Slerp(_NowFramePone.mRotation, _NextFramePose.mRotation, _interpolation);        // a����b �ɐ��lf�ŋ��ʐ��`���(slerp)����
	retVal.mTranslation = Vector3::Lerp(_NowFramePone.mTranslation, _NextFramePose.mTranslation, _interpolation);   // ���s�ړ�������f �Ő��`���(lerp)����
	return retVal;
}
