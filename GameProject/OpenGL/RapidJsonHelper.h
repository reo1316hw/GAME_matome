/*
@brief プリプロセッサ
*/
#pragma once

/*
@fn		jsonファイルのオープン
@param	_inputDocument rapidJsonオブジェクト
@param	_InFileName オープンしたいJsonファイルパス
return	ファイルを開くことができたか(bool型)
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _InFileName);

/*
@fn		Doc内にそのメンバーは存在するか？
@param	_InDocument rapidJsonオブジェクト
@param	_MemberName メンバ名
@return	Documentにメンバ名が含まれていたかどうか(bool型)
*/
bool IsExistMember(const rapidjson::Document& _InDocument, const char* _MemberName);

/*
@fn		そのメンバーが存在し、かつ値が一致するか？
@param	_InDocument ドキュメント
@param	_MemberName メンバー名
@param	_MatchValue 調べたいメンバー名にマッチする値
@return	memberNameに対応する値がmatchValueだったときのみtrueを返す(bool型)
*/
bool IsExistMemberAndValue(const rapidjson::Document& _InDocument, const char* _MemberName, const char* _MatchValue);

/*
@param	_InDocument ドキュメント
@param	_MemberName メンバー名
@return	Document内にメンバ名が含まれるか(bool型)
*/
bool IsExistArrayName(const rapidjson::Document& _InDocument, const char* _MemberName);


/*
@fn		Value値を強制的にfloat値として取得
@brief	JSON値を内容がintでも強制的にfloat値として取得
@param	_Val Value値
@return	JSON値(float型)
*/
float ForceGetFloat(const rapidjson::Value& _Val);