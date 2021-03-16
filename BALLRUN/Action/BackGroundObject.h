#pragma once
#include "GameObject.h"
#include <string>

/*
@file BackGroundObject.h
@brief ��ɔw�i�ƂȂ�I�u�W�F�N�g��\������
*/
class BackGroundObject :
	public GameObject
{
public:
	/*
	@param _pos ���W
	@param _size �T�C�Y
	@param _fileName ���b�V���f�[�^�̃A�h���X
	*/
	BackGroundObject(const Vector3& _pos, const Vector3& _size, const std::string& _fileName);
	~BackGroundObject();

	void UpdateGameObject(float deltaTime)override;
private:
};

