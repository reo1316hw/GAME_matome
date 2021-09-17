/*
@brief �C���N���[�h
*/
#include "pch.h"

#include "filereadstream.h"

/*
@fn		json�t�@�C���̃I�[�v�� 
@param	_inputDocument rapidJson�I�u�W�F�N�g
@param	_InFileName �I�[�v��������Json�t�@�C���p�X
return	�t�@�C�����J�����Ƃ��ł�����(bool�^)
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _InFileName)
{
	// json�t�@�C���J���邩�H
	std::ifstream file(_InFileName);
	if (!file.is_open())
	{
		return false;
	}

	// filestream�Ƀt�@�C���������荞��
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// �t�@�C���������JSon������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());
	// �t�@�C���X�g���[������
	file.close();

	// ��̓I�u�W�F�N�g�쐬
	_inputDocument.ParseStream(jsonStr);

	// JSonObject�Ƃ��ēǂ߂����H
	if (!_inputDocument.IsObject())
	{
		return false;
	}
	return true;
}

/*
@fn		Doc���ɂ��̃����o�[�͑��݂��邩�H
@param	_InDocument rapidJson�I�u�W�F�N�g
@param	_MemberName �����o��
@return	Document�Ƀ����o�����܂܂�Ă������ǂ���(bool�^)
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
@fn		���̃����o�[�����݂��A���l����v���邩�H
@param	_InDocument �h�L�������g
@param	_MemberName �����o�[��
@param	_MatchValue ���ׂ��������o�[���Ƀ}�b�`����l
@return	memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ�(bool�^)
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
@return Document���Ƀ����o�����܂܂�邩(bool�^)
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
@fn		Value�l�������I��float�l�Ƃ��Ď擾
@brief	JSON�l����e��int�ł������I��float�l�Ƃ��Ď擾
@param	_Val Value�l
@return	JSON�l(float�^)
*/
float ForceGetFloat(const rapidjson::Value& _Val)
{
	std::string tmp;
	tmp = _Val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}
