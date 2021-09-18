/*
@file  SkeletalMeshComponent.h
@brief �X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	   �R���X�g���N�^
@param _owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
*/
SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	: MeshComponent(_owner, true)
	, MSkeleton(nullptr)
	, mColor(Vector3(0,0,0))
{
}

/*
@fn		�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mOwner->GetState() != State::eDead)
	{
		if (mMesh)
		{
			//�X�y�L�����[���x
			const float SpecPower = 100.0f;

			//���[���h�ϊ����Z�b�g
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			//�s��p���b�g���Z�b�g    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//�X�y�L�����[���x���Z�b�g
			_shader->SetFloatUniform("uSpecPower", SpecPower);

			_shader->SetVectorUniform("uColor", mColor);

			// �e�N�X�`�������V�F�[�_�[�ɓn��
			HandOverTexture(_shader);
			
			//���b�V���̒��_�z����A�N�e�B�u��
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//�`��
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

/*
@fn		�e�N�X�`�������V�F�[�_�[�ɓn��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::HandOverTexture(Shader* _shader)
{
	//  �e�N�X�`�����Z�b�g 
	Texture* t = mMesh->GetTexture(mTextureIndex);
	if (t)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
		_shader->SetIntUniform("uMeshTexture", 0);
	}
}

/*
@fn		�t���[�����̏���
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void SkeletalMeshComponent::Update(float _deltaTime)
{
	if (MAnimation && MSkeleton)
	{
		mAnimTime += _deltaTime * mAnimPlayRate;
		//  �A�j���������߂��čĐ�
		while (mAnimTime > MAnimation->GetDuration())
		{
			mAnimTime -= MAnimation->GetDuration();
		}

		// �s��p���b�g�̍Čv�Z
		ComputeMatrixPalette();
	}
}

/*
@fn		�A�j���[�V�����̍Đ�
@param	_Anim �A�j���[�V�����f�[�^�N���X
@param	_playRate �A�j���[�V�����̍Đ����x
@return	�A�j���[�V�����̎c�莞��
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
@fn �s��p���b�g�̌v�Z
*/
void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// �O���[�o���t�o�C���h�s��z��̎擾
	const std::vector<Matrix4>& GlobalInvBindPoses = MSkeleton->GetGlobalInvBindPoses();
	// ���݂̃|�[�Y�s��
	std::vector<Matrix4> currentPoses;                                        
	// �A�j���������_�̃O���[�o���|�[�Y�̎擾
	MAnimation->GetGlobalPoseAtTime(currentPoses, MSkeleton, mAnimTime);
	// ���ꂼ��̃{�[���̍s��p���b�g�̃Z�b�g                                    
	for (size_t i = 0; i < MSkeleton->GetNumBones(); i++)
	{
		//�s��p���b�g[i] = �O���[�o���t�o�C���h�s��[i]�@�~�@���݂̃|�[�Y�s��[i]  (i�̓{�[��ID)         
		mPalette.mEntry[i] = GlobalInvBindPoses[i] * currentPoses[i];
	}
}
