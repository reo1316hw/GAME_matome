/*
@file  Shader.h
@brief �V�F�[�_�[�f�[�^
*/

/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
Shader::Shader()
	: mVertexShader(0)
	, mFragShader(0)
	, mShaderProgram(0)
{
}

/*
@fn	�f�X�g���N�^
*/
Shader::~Shader()
{
}

/*
@fn		���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
@param	_VertName ���_�V�F�[�_�[�̃t�@�C����
@param	_FragName ���_�V�F�[�_�[�̃t�@�C����
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::Load(const std::string & _VertName, const std::string & _FragName)
{
	if (!CompileShader(_VertName,GL_VERTEX_SHADER, mVertexShader) ||
		!CompileShader(_FragName,GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	if (!IsVaildProgram())
	{
		return false;
	}

	return true;
}

/*
@fn	���[�h�����V�F�[�_�[�̉��
*/
void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

/*
@fn	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
*/
void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

/*
@fn		�s���Uniform�ϐ���ݒ肷��
@param	_Name �ݒ肷��Uniform�ϐ���
@param	_Matrix �ݒ肷��s��
*/
void Shader::SetMatrixUniform(const char * _Name, const Matrix4 & _Matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// �V�F�[�_�[�ɍs��f�[�^�𑗂�
	glUniformMatrix4fv(loc, 1, GL_TRUE, _Matrix.GetAsFloatPtr());
}

/*
@fn		�s���Uniform�ϐ���ݒ肷��
@param	_Name �ݒ肷��Uniform�ϐ���
@param	_Matrices �ݒ肷��s��
@param	_count �s��̐�
*/
void Shader::SetMatrixUniforms(const char* _Name, Matrix4* _Matrices, unsigned _count)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// �s��z��f�[�^���V�F�[�_�[�ϐ��ɑ���
	glUniformMatrix4fv(loc, _count, GL_TRUE, _Matrices->GetAsFloatPtr());
}

/*
@fn		Vector3��Uniform�ϐ���ݒ肷��
@param	_Name �ݒ肷��Uniform�ϐ���
@param	_Vector �ݒ肷��Vector3
*/
void Shader::SetVectorUniform(const char * _Name, const Vector3 & _Vector)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
    // �V�F�[�_�[��Vector�f�[�^�𑗂�
    glUniform3fv(loc, 1, _Vector.GetAsFloatPtr());
}

/*
@fn		float��Uniform�ϐ���ݒ肷��
@param	_Name �ݒ肷��Uniform�ϐ���
@param	_Value �ݒ肷��float
*/
void Shader::SetFloatUniform(const char * _Name, const float & _Value)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
    // �V�F�[�_�[��float�f�[�^�𑗂�
    glUniform1f(loc, _Value);
}

/*
@fn		int��Uniform�ϐ���ݒ肷��
@param	_Name �ݒ肷��Uniform�ϐ���
@param	_Value �ݒ肷��int
*/
void Shader::SetIntUniform(const char* _Name, const int _Value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// �V�F�[�_�[��int�f�[�^�𑗂�
	glUniform1i(loc, _Value);
}

/*
@fn		�V�F�[�_�[���R���p�C������
@param	_FileName �R���p�C������V�F�[�_�[�̃t�@�C����
@param	_shaderType �V�F�[�_�[�̎��
@param	_outShader �V�F�[�_�[��ID�p�̎Q�ƕϐ�
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::CompileShader(const std::string & _FileName, GLenum _shaderType, GLuint & _outShader)
{
	std::ifstream shaderFile(_FileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::ifstream().swap(shaderFile);
		std::string contents = sstream.str();
		const char* ContentsChar = contents.c_str();

		_outShader = glCreateShader(_shaderType);

		glShaderSource(_outShader, 1, &(ContentsChar), nullptr);
		glCompileShader(_outShader);

		if (!IsCompiled(_outShader))
		{
			SDL_Log("Failed to compile shader %s", _FileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", _FileName.c_str());
		return false;
	}

	return true;
}

/*
@fn		�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
@param	_shader �V�F�[�_�[��ID
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	glGetShaderiv(_shader,GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetShaderInfoLog(_shader,411,nullptr,buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/*
@fn		�V�F�[�_�[�������N�o���Ă��邩�m�F
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::IsVaildProgram()
{
	GLint status;

	glGetProgramiv(mShaderProgram,GL_LINK_STATUS,&status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer,0,512);
		glGetProgramInfoLog(mShaderProgram,511,nullptr,buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
