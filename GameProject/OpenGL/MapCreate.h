/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
class Player;

class MapCreate : public GameObject
{
public:

	/*
	@fn	コンストラクタ
	*/
	MapCreate();

	/*
	@fn	デストラクタ
	*/
	~MapCreate();

	/*
	@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return	ファイルを開けたか(bool型)
	*/
	bool OpenFile();

	/*
	@fn	床のデータにアクセスする
	*/
	void AccessGroundData();

	/*
	@fn	床を生成する
	*/
	void CreateGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	ガラス床のデータにアクセスする
	*/
	void AccessGlassData();

	/*
	@fn	ガラス床を生成する
	*/
	void CreateGlass(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	障害物のデータにアクセスする
	*/
	void AccessBlockData();

	/*
	@fn	障害物を生成する
	*/
	void CreateBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	縦移動床のデータにアクセスする
	*/
	void AccessVerticalMoveGroundData();

	/*
	@fn	縦移動床を生成する
	*/
	void CreateVerticalMoveGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	ジャンプ中のデータにアクセスする
	*/
	void AccessJumpData();

	/*
	@fn	ジャンプ中を生成する
	*/
	void CreateJump(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	横移動床のデータにアクセスする
	*/
	void AccessLateralMoveGroundData();

	/*
	@fn	横移動床を生成する
	*/
	void CreateLateralMoveGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	    プレイヤーのデータにアクセスする
	@return プレイヤークラスのポインタ
	*/
	Player* AccessPlayerData();

	/*
	@fn	    プレイヤーを生成する
	@return プレイヤークラスのポインタ
	*/
	Player* CreatePlayer(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	上移動ブロックのデータにアクセスする
	*/
	void AccessUpBlockData();

	/*
	@fn	上移動ブロックを生成する
	*/
	void CreateUpBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	縦長障害物のデータにアクセスする
	*/
	void AccessVerticalBlockData();

	/*
	@fn	縦長障害物を生成する
	*/
	void CreateVerticalBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	空中ブロックのデータにアクセスする
	*/
	void AccessAerialBlockData();

	/*
	@fn	空中ブロックを生成する
	*/
	void CreateAerialBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	右移動ブロックのデータにアクセスする
	*/
	void AccessRightBlockData();

	/*
	@fn	右移動ブロックを生成する
	*/
	void CreateRightBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	左移動ブロックのデータにアクセスする
	*/
	void AccessLeftBlockData();

	/*
	@fn	左移動ブロックを生成する
	*/
	void CreateLeftBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	1マス右移動床のデータにアクセスする
	*/
	void AccessRightGroundData();

	/*
	@fn	1マス右移動床を生成する
	*/
	void CreateRightGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	1マス左移動床のデータにアクセスする
	*/
	void AccessLeftGroundData();

	/*
	@fn	1マス左移動床を生成する
	*/
	void CreateLeftGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	落下ブロックのデータにアクセスする
	*/
	void AccessDownBlockData();

	/*
	@fn	落下ブロックを生成する
	*/
	void CreateDownBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	ゴール柱のデータにアクセスする
	*/
	void AccessGoalData();

	/*
	@fn	ゴール柱を生成する
	*/
	void CreateGoal(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	リスポーン地点のデータにアクセスする
	*/
	void AccessRespawnData();

	/*
	@fn	リスポーン地点を生成する
	*/
	void CreateRespawn(const unsigned int _name, const Vector3 _objectPos);

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);

	//床マップデータ
	std::vector<std::vector<int>> mGroundMapData;
	//プレイヤーマップデータ
	std::vector<std::vector<int>> mPlayerMapData;
	//横移動床マップデータ
	std::vector<std::vector<int>> mLateralMoveGroundMapData;
	//縦移動床マップデータ
	std::vector<std::vector<int>> mVerticalMoveGroundMapData;
	//ジャンプ床マップデータ
	std::vector<std::vector<int>> mJumpMapData;
	//障害物マップデータ
	std::vector<std::vector<int>> mBlockMapData;
	//ガラス床マップデータ
	std::vector<std::vector<int>> mGlassMapData;
	//上移動ブロックマップデータ
	std::vector<std::vector<int>> mUpBlockMapData;
	//縦長障害物マップデータ
	std::vector<std::vector<int>> mVerticalBlockMapData;
	//空中ブロックマップデータ
	std::vector<std::vector<int>> mAerialBlockMapData;
	//右移動ブロックマップデータ
	std::vector<std::vector<int>> mRightBlockMapData;
	//左移動ブロックマップデータ
	std::vector<std::vector<int>> mLeftBlockMapData;
	//1マス右移動床マップデータ
	std::vector<std::vector<int>> mRightGroundMapData;
	//1マス左移動床マップデータ
	std::vector<std::vector<int>> mLeftGroundMapData;
	//落下ブロックマップデータ
	std::vector<std::vector<int>> mDownBlockMapData;
	//ゴール柱マップデータ
	std::vector<std::vector<int>> mGoalBlockMapData;
	//リスポーン地点マップデータ
	std::vector<std::vector<int>> mRespawnMapData;

	//現在のシーン
	int mScene;
	//幅のマップデータ
	int	mSizeX;
	//高さのマップデータ
	int	mSizeY;
	//奥行のマップデータ
	int	mSizeZ;

	//オブジェクトごとの距離
	float mOffset;
};

