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
	//マップデータ
	std::vector<std::vector<int>> groundMapData;
	//プレイヤー
	std::vector<std::vector<int>> playerMapData;
	//横移動床
	std::vector<std::vector<int>> lateralMoveGroundMapData;
	//縦移動床
	std::vector<std::vector<int>> verticalMoveGroundMapData;
	//ジャンプ床
	std::vector<std::vector<int>> jumpMapData;
	//障害物
	std::vector<std::vector<int>> blockMapData;
	//ガラス床
	std::vector<std::vector<int>> glassMapData;
	//上移動ブロック
	std::vector<std::vector<int>> upBlockMapData;
	std::vector<std::vector<int>> upBlock_02MapData;
	//縦長障害物
	std::vector<std::vector<int>> verticalBlockMapData;
	//空中ブロック
	std::vector<std::vector<int>> aerialBlockMapData;
	//右移動ブロック
	std::vector<std::vector<int>> rightBlockMapData;
	//左移動ブロック
	std::vector<std::vector<int>> leftBlockMapData;
	//1マス右移動床
	std::vector<std::vector<int>> rightOneBlockMapData;
	std::vector<std::vector<int>> rightOneBlock_02MapData;
	//1マス左移動床
	std::vector<std::vector<int>> leftOneBlockMapData;
	std::vector<std::vector<int>> leftOneBlock_02MapData;
	//落ちるブロック
	std::vector<std::vector<int>> downBlockMapData;
	//ゴール柱
	std::vector<std::vector<int>> goalBlockMapData;
	//リスポーン地点
	std::vector<std::vector<int>> respawn01MapData;
	std::vector<std::vector<int>> respawn02MapData;
	std::vector<std::vector<int>> respawn03MapData;

	int scene;

	int sizeX;
	int sizeY;
	int sizeZ;
	float offset;
};

