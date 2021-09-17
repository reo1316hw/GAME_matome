/*
@brief インクルード
*/
#include "pch.h"

#include "filereadstream.h"

/*
@fn		jsonファイルのオープン 
@param	_inputDocument rapidJsonオブジェクト
@param	_InFileName オープンしたいJsonファイルパス
return	ファイルを開くことができたか(bool型)
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _InFileName)
{
	// jsonファイル開けるか？
	std::ifstream file(_InFileName);
	if (!file.is_open())
	{
		return false;
	}

	// filestreamにファイル文字列取り込む
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// ファイル文字列をJSon文字列に変換
	rapidjson::StringStream jsonStr(contents.c_str());
	// ファイルストリーム閉じる
	file.close();

	// 解析オブジェクト作成
	_inputDocument.ParseStream(jsonStr);

	// JSonObjectとして読めたか？
	if (!_inputDocument.IsObject())
	{
		return false;
	}
	return true;
}

/*
@fn		Doc内にそのメンバーは存在するか？
@param	_InDocument rapidJsonオブジェクト
@param	_MemberName メンバ名
@return	Documentにメンバ名が含まれていたかどうか(bool型)
*/
bool IsExistMember(const rapidjson::Document& _InDocument, const char* _MemberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _InDocument.FindMember(_MemberName);

	if (iter == _InDocument.MemberEnd())
	{
		return false;
	}
	return true;
}

/*
@fn		そのメンバーが存在し、かつ値が一致するか？
@param	_InDocument ドキュメント
@param	_MemberName メンバー名
@param	_MatchValue 調べたいメンバー名にマッチする値
@return	memberNameに対応する値がmatchValueだったときのみtrueを返す(bool型)
*/
bool IsExistMemberAndValue(const rapidjson::Document& _InDocument, const char* _MenberName, const char* _MatchValue)
{
	if (!IsExistMember(_InDocument, _MenberName))
	{
		return false;
	}

	std::string findValueString;
	findValueString = std::string(_MatchValue);

	if (findValueString != _InDocument[_MenberName].GetString())
	{
		return false;
	}
	return true;
}

/*
@param _InDocument
@param _MenberName 
@return Document内にメンバ名が含まれるか(bool型)
*/
bool IsExistArrayName(const rapidjson::Document& _InDocument, const char* _MenberName)
{
	rapidjson::Value::ConstMemberIterator iter;
	iter = _InDocument.FindMember(_MenberName);
	if (iter == _InDocument.MemberEnd())
	{
		return false;
	}
	return _InDocument[_MenberName].IsArray();
}

/*
@fn		Value値を強制的にfloat値として取得
@brief	JSON値を内容がintでも強制的にfloat値として取得
@param	_Val Value値
@return	JSON値(float型)
*/
float ForceGetFloat(const rapidjson::Value& _Val)
{
	std::string tmp;
	tmp = _Val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}
