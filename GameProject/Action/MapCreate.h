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
	//マップデータ
	std::vector<std::vector<int>> mGroundMapData;
	//プレイヤー
	std::vector<std::vector<int>> mPlayerMapData;
	//横移動床
	std::vector<std::vector<int>> mLateralMoveGroundMapData;
	//縦移動床
	std::vector<std::vector<int>> mVerticalMoveGroundMapData;
	//ジャンプ床
	std::vector<std::vector<int>> mJumpMapData;
	//障害物
	std::vector<std::vector<int>> mBlockMapData;
	//ガラス床
	std::vector<std::vector<int>> mGlassMapData;
	//上移動ブロック
	std::vector<std::vector<int>> mUpBlockMapData;
	std::vector<std::vector<int>> mUpBlock02MapData;
	//縦長障害物
	std::vector<std::vector<int>> mVerticalBlockMapData;
	//空中ブロック
	std::vector<std::vector<int>> mAerialBlockMapData;
	//右移動ブロック
	std::vector<std::vector<int>> mRightBlockMapData;
	//左移動ブロック
	std::vector<std::vector<int>> mLeftBlockMapData;
	//1マス右移動床
	std::vector<std::vector<int>> mRightOneBlockMapData;
	std::vector<std::vector<int>> mRightOneBlock02MapData;
	//1マス左移動床
	std::vector<std::vector<int>> mLeftOneBlockMapData;
	std::vector<std::vector<int>> mLeftOneBlock02MapData;
	//落下ブロック
	std::vector<std::vector<int>> mDownBlockMapData;
	//ゴール柱
	std::vector<std::vector<int>> mGoalBlockMapData;
	//リスポーン地点
	std::vector<std::vector<int>> mRespawn01MapData;
	std::vector<std::vector<int>> mRespawn02MapData;
	std::vector<std::vector<int>> mRespawn03MapData;

	int mScene;
	int	mSizeX;
	int	mSizeY;
	int	mSizeZ;

	float mOffset;
};

