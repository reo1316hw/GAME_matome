/*
@file  Shader.h
@brief �V�F�[�_�[�f�[�^
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

class Shader
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
    Shader();

	/*
	@fn	�f�X�g���N�^
	*/
    ~Shader();

	/*
	@fn		���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
	@param	_VertName ���_�V�F�[�_�[�̃t�@�C����
	@param	_FragName ���_�V�F�[�_�[�̃t�@�C����
	@return	true : ���� , false : ���s(bool�^)
	*/
	bool Load(const std::string& _VertName,const std::string& _FragName);

	/*
	@fn	���[�h�����V�F�[�_�[�̉��
	*/
	void Unload();

	/*
	@fn	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
	*/
	void SetActive();

	/*
	@fn		�s���Uniform�ϐ���ݒ肷��
	@param	_Name �ݒ肷��Uniform�ϐ���
	@param	_Matrix �ݒ肷��s��
	*/
	void SetMatrixUniform(const char* _Name , const Matrix4& _Matrix);

	/*
	@fn		�s���Uniform�ϐ���ݒ肷��
	@param	_Name �ݒ肷��Uniform�ϐ���
	@param	_Matrices �ݒ肷��s��
	@param	_count �s��̐�
	*/
	void SetMatrixUniforms(const char* _Name, Matrix4* _Matrices, unsigned _count);

    /*
    @fn		Vector3��Uniform�ϐ���ݒ肷��
    @param	_Name �ݒ肷��Uniform�ϐ���
    @param	_Vector �ݒ肷��Vector3
    */
    void SetVectorUniform(const char* _Name, const Vector3& _Vector);

    /*
    @fn		float��Uniform�ϐ���ݒ肷��
    @param	_Name �ݒ肷��Uniform�ϐ���
    @param	_Value �ݒ肷��float
    */
    void SetFloatUniform(const char* _Name, const float& _Value);

	/*
	@fn		int��Uniform�ϐ���ݒ肷��
	@param	_Name �ݒ肷��Uniform�ϐ���
	@param	_Value �ݒ肷��int
	*/
	void SetIntUniform(const char* _Name, const int _Value);

private:

	/*
	@fn		�V�F�[�_�[���R���p�C������
	@param	_FileName �R���p�C������V�F�[�_�[�̃t�@�C����
	@param	_shaderType �V�F�[�_�[�̎��
	@param	_outShader �V�F�[�_�[��ID�p�̎Q�ƕϐ�
	@return	true : ���� , false : ���s(bool�^)
	*/
	bool CompileShader(const std::string& _FileName,GLenum _shaderType,GLuint& _outShader);

	/*
	@fn		�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
	@param	_shader �V�F�[�_�[��ID
	@return	true : ���� , false : ���s(bool�^)
	*/
	bool IsCompiled(GLuint _shader);

	/*
	@fn		�V�F�[�_�[�������N�o���Ă��邩�m�F
	@return	true : ���� , false : ���s(bool�^)
	*/
	bool IsVaildProgram();

	//���_�V�F�[�_�[
	GLuint mVertexShader;
	//�t���O�����g�V�F�[�_�[
	GLuint mFragShader;
	//�V�F�[�_�[�v���O����
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[������
	GLuint mShaderProgram;
};

