/*
@file Renderer.h
@brief �`��̐i�s���s���N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"
#include "ParticleComponent.h"
#include "Player.h"


#define RENDERER Renderer::GetInstance()

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 m_direction;
	// �g�U���ːF
	Vector3 m_diffuseColor;
	// ���ʔ��ːF
	Vector3 m_specColor;
};

/*
@enum �e�N�X�`���X�e�[�W
*/
enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class InvisibleMeshComponent;
class Shader;
class VertexArray;
class ParticleComponent;
class UIComponent;
class HeartUI;
class HDRRenderer;

class Renderer
{
public:

	/*
	@fn	�C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@fn	�C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@fn		����������
	@return true : ���� , false : ���s(bool�^)
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);

	/*
	@fn	�I������
	*/
	void Shutdown();

	/*
	@fn	���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@fn	�`�揈��
	*/
	void Draw();
	   
	/*
	@fn		�X�v���C�g�̒ǉ�
	@param	_spriteComponent�@�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
	void AddSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		�X�v���C�g�̍폜
	@param	_spriteComponent�@�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* _spriteComponent);

	/*
	@fn		UI�̒ǉ�
	@param	_ui�@�ǉ�����UI�N���X�̃|�C���^
	*/
	void AddUI(UIComponent* _ui);

	/*
	@fn		UI�̍폜
	@param	_ui�@�폜����UI�N���X�̃|�C���^
	*/
	void RemoveUI(UIComponent* _ui);

	/*
	@fn		�p�[�e�B�N���̒ǉ�
	@param	_particleComponent�@�ǉ�����ParticleObject�N���X�̃|�C���^
	*/
	void AddParticle(ParticleComponent* _particleComponent);

	/*
	@fn		�p�[�e�B�N���̍폜
	@param	_particleComponent �폜����ParticleObject�N���X�̃|�C���^
	*/
	void RemoveParticle(ParticleComponent* _particleComponent);
	
	/*
	@fn		���b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		���b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		���������b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

	/*
	@fn		���������b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveInvisibleMeshComponent(InvisibleMeshComponent* _invisibleMeshComponent);

private:

	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer();

	// �X�P���g���f�[�^
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// �A�j���[�V�����f�[�^
	std::unordered_map<std::string, class Animation*> mAnims;
	// �X�P���g�����b�V���̕`��Ɏg����
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;

	//�����̃C���X�^���X
	static Renderer* mRenderer;
	//�����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	/*
	@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	@param	_view �r���[�s��
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _view);


	/*
	@fn		�V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s(bool�^)
	*/
	bool LoadShaders();

	/*
	@fn	Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateSpriteVerts();

	/*
	@fn	Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateParticleVerts();

	/*
	@fn	Particle�̕`��
	*/
	void DrawParticle();

	/*
	@fn	Particle�̕`��
	@param	_framebuffer �t���[���o�b�t�@
	@param	_view �r���[�s��
	@param	_proj �ˉe�s��
	@param	_viewPortScale �\���̈�X�P�[��
	@param	_lit ���������V�F�[�_�[�̕ϐ��ɃZ�b�g���邩�̃t���O
	*/
	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _blendType �p�[�e�B�N���ɑ΂���u�����h�̎��
	*/
	void ChangeBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM _blendType);

	/*
	@fn		�e�N�X�`���̕ύX
	@param	_changeTextureID �ύX����e�N�X�`����id 
	*/
	void ChangeTexture(int _changeTextureID);

	/*
	@fn	���[���h��Ԃ̃J�������W���v�Z
	*/
	Vector3 CalcCameraPos();

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> mMeshes;
	//���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> mMeshComponents;
	//�C���r�W�u�����b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<InvisibleMeshComponent*> mInvisibleMeshComponents;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> mSprites;
	//UI�̃|�C���^�̉ϒ��R���e�i
	std::vector<UIComponent*> mUis;
	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> mParticles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*> mTextures;

	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* mSpriteShader;
	//�X�v���C�g�p���_
	VertexArray* mSpriteVerts;
	//UI
	Shader* mUiShader;
	//UI�p���_
	VertexArray* mUiVerts;
	//���b�V��
	Shader* mMeshShader;
	//�X�L�����b�V��
	class Shader*  mSkinnedShader;
	//�C���r�W�u�����b�V��
	Shader* mInvisibleMeshShader;
	Shader* mBasicShader;
	//�p�[�e�B�N��
	Shader* mParticleShader;
	//�p�[�e�B�N���p���_
	VertexArray* mParticleVertex; 
	//�v���C���[
	Player* mPlayer;
	//HDR�����_���[
	HDRRenderer* mHDRRenderer;

	//�r���[�s��
	Matrix4 mView;
	//�ˉe�s��
	Matrix4 mProjection;
	//�r���{�[�h�s��
	Matrix4 mBillboardMat;
	//�X�N���[���̉���
	float mScreenWidth;
	//�X�N���[���̏c��
	float mScreenHeight;
	//����
	Vector3 mAmbientLight;
	//���s����
	DirectionalLight mDirLight;
	//�E�B���h�E
	SDL_Window* mWindow;
	//�R���e�L�X�g
	SDL_GLContext mContext;
	// UI�̏������W�ɉ��Z�������W
	Vector2 mAddPosition;
	//�v���C���[�̗̑�UI
	HeartUI* mHeartUI;

	//���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int mUndefineTexID;

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		�C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X(class Renderer)
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^(class Texture)
	*/
	Texture* GetTexture(const std::string& _fileName);

	/*
	@param _fileName ���f���ւ̃A�h���X
	@return �X�P���g�����f���̎擾(class Skeleton)
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);

	/*
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����̎擾(class Animation)
	*/
	const class Animation* GetAnimation(const char* _fileName);                     // �X�P���^���A�j���[�V�����̎擾

	/*
	@param	_fileName �擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^(class Mesh)
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@return	���s�����̍\����(struct DirectionalLight�j
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	/*
	@return	�X�N���[���̉���(float�^)
	*/
	float GetScreenWidth() const { return mScreenWidth; }

	/*
	@return	�X�N���[���̏c��(float�^)
	*/
	float GetScreenHeight() const { return mScreenHeight; }

	/*
	@return	�r���[�s��(class Matrix4)
	*/
	Matrix4 GetViewMatrix() const { return mView; };

	/*
	@return	�ˉe�s��(class Matrix4)
	*/
	Matrix4 GetProjectionMatrix() { return mProjection; }

	/*
	@return	�ˉe�s��(class Matrix4)
	*/
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/*
	@return	���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��(unsigned int�^)
	*/
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/*
	@param	_view �r���[�s��
	*/
	void SetViewMatrix(const Matrix4& _view) { mView = _view; }

	/*
	@param	_ambient�i������\���j
	*/
	void SetAmbientLight(const Vector3& _ambient) { mAmbientLight = _ambient; }

	/*
	@fn	�p�[�e�B�N���p���_��ݒ�
	*/
	void SetParticleVertex();
};