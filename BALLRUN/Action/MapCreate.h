#pragma once
#include"GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

class MapCreate : public GameObject
{
public:
	MapCreate();
	~MapCreate();

	bool OpenFile();

	void CreateGround();
	void CreatePlayer();
	void CreateLateralMoveGround();
	void CreateVerticalMoveGround();
	void CreateJump();
	void CreateBlock();
	void CreateGlass();
	void CreateUpBlock();
	void CreateUpBlock_02();
	void CreateVerticalBlock();
	void CreateAerialBlock();
	void CreateRightBlock();
	void CreateLeftBlock();
	void CreateRightOneBlock();
	void CreateRightOneBlock_02();
	void CreateLeftOneBlock();
	void CreateLeftOneBlock_02();
	void CreateDownBlock();
	void CreateGoal();
	void CreateRespawn01();
	void CreateRespawn02();
	void CreateRespawn03();

private:
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& layer,std::string& layerName);
	//�}�b�v�f�[�^
	std::vector<std::vector<int>> groundMapData;
	//�v���C���[
	std::vector<std::vector<int>> playerMapData;
	//���ړ���
	std::vector<std::vector<int>> lateralMoveGroundMapData;
	//�c�ړ���
	std::vector<std::vector<int>> verticalMoveGroundMapData;
	//�W�����v��
	std::vector<std::vector<int>> jumpMapData;
	//��Q��
	std::vector<std::vector<int>> blockMapData;
	//�K���X��
	std::vector<std::vector<int>> glassMapData;
	//��ړ��u���b�N
	std::vector<std::vector<int>> upBlockMapData;
	std::vector<std::vector<int>> upBlock_02MapData;
	//�c����Q��
	std::vector<std::vector<int>> verticalBlockMapData;
	//�󒆃u���b�N
	std::vector<std::vector<int>> aerialBlockMapData;
	//�E�ړ��u���b�N
	std::vector<std::vector<int>> rightBlockMapData;
	//���ړ��u���b�N
	std::vector<std::vector<int>> leftBlockMapData;
	//1�}�X�E�ړ���
	std::vector<std::vector<int>> rightOneBlockMapData;
	std::vector<std::vector<int>> rightOneBlock_02MapData;
	//1�}�X���ړ���
	std::vector<std::vector<int>> leftOneBlockMapData;
	std::vector<std::vector<int>> leftOneBlock_02MapData;
	//������u���b�N
	std::vector<std::vector<int>> downBlockMapData;
	//�S�[����
	std::vector<std::vector<int>> goalBlockMapData;
	//���X�|�[���n�_
	std::vector<std::vector<int>> respawn01MapData;
	std::vector<std::vector<int>> respawn02MapData;
	std::vector<std::vector<int>> respawn03MapData;

	int scene;

	int sizeX;
	int sizeY;
	int sizeZ;
	float offset;
};

