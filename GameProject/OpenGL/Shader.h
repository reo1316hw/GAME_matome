/*
@file  Shader.h
@brief シェーダーデータ
*/

/*
@brief プリプロセッサ
*/
#pragma once

class Shader
{
public:

	/*
	@fn	コンストラクタ
	*/
    Shader();

	/*
	@fn	デストラクタ
	*/
    ~Shader();

	/*
	@fn		頂点シェーダーとフラグメントシェーダーのロード
	@param	_VertName 頂点シェーダーのファイル名
	@param	_FragName 頂点シェーダーのファイル名
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool Load(const std::string& _VertName,const std::string& _FragName);

	/*
	@fn	ロードしたシェーダーの解放
	*/
	void Unload();

	/*
	@fn	シェーダープログラムをアクティブにする
	*/
	void SetActive();

	/*
	@fn		行列のUniform変数を設定する
	@param	_Name 設定するUniform変数名
	@param	_Matrix 設定する行列
	*/
	void SetMatrixUniform(const char* _Name , const Matrix4& _Matrix);

	/*
	@fn		行列のUniform変数を設定する
	@param	_Name 設定するUniform変数名
	@param	_Matrices 設定する行列
	@param	_count 行列の数
	*/
	void SetMatrixUniforms(const char* _Name, Matrix4* _Matrices, unsigned _count);

    /*
    @fn		Vector3のUniform変数を設定する
    @param	_Name 設定するUniform変数名
    @param	_Vector 設定するVector3
    */
    void SetVectorUniform(const char* _Name, const Vector3& _Vector);

    /*
    @fn		floatのUniform変数を設定する
    @param	_Name 設定するUniform変数名
    @param	_Value 設定するfloat
    */
    void SetFloatUniform(const char* _Name, const float& _Value);

	/*
	@fn		intのUniform変数を設定する
	@param	_Name 設定するUniform変数名
	@param	_Value 設定するint
	*/
	void SetIntUniform(const char* _Name, const int _Value);

private:

	/*
	@fn		シェーダーをコンパイルする
	@param	_FileName コンパイルするシェーダーのファイル名
	@param	_shaderType シェーダーの種類
	@param	_outShader シェーダーのID用の参照変数
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool CompileShader(const std::string& _FileName,GLenum _shaderType,GLuint& _outShader);

	/*
	@fn		シェーダーがコンパイル出来ているか確認
	@param	_shader シェーダーのID
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool IsCompiled(GLuint _shader);

	/*
	@fn		シェーダーがリンク出来ているか確認
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool IsVaildProgram();

	//頂点シェーダー
	GLuint mVertexShader;
	//フラグメントシェーダー
	GLuint mFragShader;
	//シェーダープログラム
	//頂点シェーダーとフラグメントシェーダーを結合
	GLuint mShaderProgram;
};

