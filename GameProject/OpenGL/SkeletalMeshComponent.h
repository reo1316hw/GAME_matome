/*
@file  SkeletalMeshComponent.h
@brief �X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �C���N���[�h
*/
#include "MeshComponent.h"
#include "MatrixPalette.h"

class SkeletalMeshComponent : public MeshComponent
{
public:

	/*
	@fn		�R���X�g���N�^
	@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	*/
	SkeletalMeshComponent(class GameObject* _owner);

	/*
	@fn		�t���[�����̏���
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime) override;

	/*
	@fn		�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader) override;

	/*
	@fn		�e�N�X�`�������V�F�[�_�[�ɓn��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void HandOverTexture(class Shader* _shader);

   	/*
	@fn		�A�j���[�V�����̍Đ�
	@param	_Anim �A�j���[�V�����f�[�^�N���X
	@param	_playRate �A�j���[�V�����̍Đ����x
	@return	�A�j���[�V�����̎c�莞��(float�^)
	*/
	float PlayAnimation(const class Animation* _Anim, float _playRate = 1.0f);

protected:

	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();

	// �s��p���b�g
	MatrixPalette mPalette;
	// �X�P���g���f�[�^
	const class Skeleton* MSkeleton;
	// �A�j���[�V�����f�[�^
	const class Animation* MAnimation;
	// �A�j���[�V�����̍Đ����x
	float mAnimPlayRate;
	// �A�j���[�V��������
	float mAnimTime;
	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 mColor;

public://�Q�b�^�[�Z�b�^�[

	/*
	@param _Skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _Skeleton) { MSkeleton = _Skeleton; }
	/*
	@param _Color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _Color) { mColor = _Color; }
};
