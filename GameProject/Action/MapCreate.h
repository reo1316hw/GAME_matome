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
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);
	//�}�b�v�f�[�^
	std::vector<std::vector<int>> mGroundMapData;
	//�v���C���[
	std::vector<std::vector<int>> mPlayerMapData;
	//���ړ���
	std::vector<std::vector<int>> mLateralMoveGroundMapData;
	//�c�ړ���
	std::vector<std::vector<int>> mVerticalMoveGroundMapData;
	//�W�����v��
	std::vector<std::vector<int>> mJumpMapData;
	//��Q��
	std::vector<std::vector<int>> mBlockMapData;
	//�K���X��
	std::vector<std::vector<int>> mGlassMapData;
	//��ړ��u���b�N
	std::vector<std::vector<int>> mUpBlockMapData;
	std::vector<std::vector<int>> mUpBlock02MapData;
	//�c����Q��
	std::vector<std::vector<int>> mVerticalBlockMapData;
	//�󒆃u���b�N
	std::vector<std::vector<int>> mAerialBlockMapData;
	//�E�ړ��u���b�N
	std::vector<std::vector<int>> mRightBlockMapData;
	//���ړ��u���b�N
	std::vector<std::vector<int>> mLeftBlockMapData;
	//1�}�X�E�ړ���
	std::vector<std::vector<int>> mRightOneBlockMapData;
	std::vector<std::vector<int>> mRightOneBlock02MapData;
	//1�}�X���ړ���
	std::vector<std::vector<int>> mLeftOneBlockMapData;
	std::vector<std::vector<int>> mLeftOneBlock02MapData;
	//�����u���b�N
	std::vector<std::vector<int>> mDownBlockMapData;
	//�S�[����
	std::vector<std::vector<int>> mGoalBlockMapData;
	//���X�|�[���n�_
	std::vector<std::vector<int>> mRespawn01MapData;
	std::vector<std::vector<int>> mRespawn02MapData;
	std::vector<std::vector<int>> mRespawn03MapData;

	int mScene;
	int	mSizeX;
	int	mSizeY;
	int	mSizeZ;

	float mOffset;
};

