/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@fn		json�t�@�C���̃I�[�v��
@param	_inputDocument rapidJson�I�u�W�F�N�g
@param	_InFileName �I�[�v��������Json�t�@�C���p�X
return	�t�@�C�����J�����Ƃ��ł�����(bool�^)
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _InFileName);

/*
@fn		Doc���ɂ��̃����o�[�͑��݂��邩�H
@param	_InDocument rapidJson�I�u�W�F�N�g
@param	_MemberName �����o��
@return	Document�Ƀ����o�����܂܂�Ă������ǂ���(bool�^)
*/
bool IsExistMember(const rapidjson::Document& _InDocument, const char* _MemberName);

/*
@fn		���̃����o�[�����݂��A���l����v���邩�H
@param	_InDocument �h�L�������g
@param	_MemberName �����o�[��
@param	_MatchValue ���ׂ��������o�[���Ƀ}�b�`����l
@return	memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ�(bool�^)
*/
bool IsExistMemberAndValue(const rapidjson::Document& _InDocument, const char* _MemberName, const char* _MatchValue);

/*
@param	_InDocument �h�L�������g
@param	_MemberName �����o�[��
@return	Document���Ƀ����o�����܂܂�邩(bool�^)
*/
bool IsExistArrayName(const rapidjson::Document& _InDocument, const char* _MemberName);


/*
@fn		Value�l�������I��float�l�Ƃ��Ď擾
@brief	JSON�l����e��int�ł������I��float�l�Ƃ��Ď擾
@param	_Val Value�l
@return	JSON�l(float�^)
*/
float ForceGetFloat(const rapidjson::Value& _Val);