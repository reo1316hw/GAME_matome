/*
 @file  BoneTransform.h
 @brief ���f���̃{�[���ϊ�
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

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
	@param	_NowFramePone	���݂̃t���[���̃|�[�Y
	@param	_NextFramePose	���̃t���[���̃|�[�Y
	@param	_interpolation	��Ԓl
	*/
	static BoneTransform Interpolate(const BoneTransform& _NowFramePone, const BoneTransform& _NextFramePose, float _interpolation);
};
