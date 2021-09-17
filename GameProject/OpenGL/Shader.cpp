/*
@file  Shader.h
@brief シェーダーデータ
*/

/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
Shader::Shader()
	: mVertexShader(0)
	, mFragShader(0)
	, mShaderProgram(0)
{
}

/*
@fn	デストラクタ
*/
Shader::~Shader()
{
}

/*
@fn		頂点シェーダーとフラグメントシェーダーのロード
@param	_VertName 頂点シェーダーのファイル名
@param	_FragName 頂点シェーダーのファイル名
@return	true : 成功 , false : 失敗(bool型)
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
@fn	ロードしたシェーダーの解放
*/
void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

/*
@fn	シェーダープログラムをアクティブにする
*/
void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

/*
@fn		行列のUniform変数を設定する
@param	_Name 設定するUniform変数名
@param	_Matrix 設定する行列
*/
void Shader::SetMatrixUniform(const char * _Name, const Matrix4 & _Matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// シェーダーに行列データを送る
	glUniformMatrix4fv(loc, 1, GL_TRUE, _Matrix.GetAsFloatPtr());
}

/*
@fn		行列のUniform変数を設定する
@param	_Name 設定するUniform変数名
@param	_Matrices 設定する行列
@param	_count 行列の数
*/
void Shader::SetMatrixUniforms(const char* _Name, Matrix4* _Matrices, unsigned _count)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// 行列配列データをシェーダー変数に送る
	glUniformMatrix4fv(loc, _count, GL_TRUE, _Matrices->GetAsFloatPtr());
}

/*
@fn		Vector3のUniform変数を設定する
@param	_Name 設定するUniform変数名
@param	_Vector 設定するVector3
*/
void Shader::SetVectorUniform(const char * _Name, const Vector3 & _Vector)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
    // シェーダーにVectorデータを送る
    glUniform3fv(loc, 1, _Vector.GetAsFloatPtr());
}

/*
@fn		floatのUniform変数を設定する
@param	_Name 設定するUniform変数名
@param	_Value 設定するfloat
*/
void Shader::SetFloatUniform(const char * _Name, const float & _Value)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
    // シェーダーにfloatデータを送る
    glUniform1f(loc, _Value);
}

/*
@fn		intのUniform変数を設定する
@param	_Name 設定するUniform変数名
@param	_Value 設定するint
*/
void Shader::SetIntUniform(const char* _Name, const int _Value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _Name);
	// シェーダーにintデータを送る
	glUniform1i(loc, _Value);
}

/*
@fn		シェーダーをコンパイルする
@param	_FileName コンパイルするシェーダーのファイル名
@param	_shaderType シェーダーの種類
@param	_outShader シェーダーのID用の参照変数
@return	true : 成功 , false : 失敗(bool型)
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
@fn		シェーダーがコンパイル出来ているか確認
@param	_shader シェーダーのID
@return	true : 成功 , false : 失敗(bool型)
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
@fn		シェーダーがリンク出来ているか確認
@return	true : 成功 , false : 失敗(bool型)
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
