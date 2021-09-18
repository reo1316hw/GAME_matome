/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Player;

/*
@brief マップデータのオブジェクトの番号
*/
enum MapDataNum
{
	eGroundNum = 1,
	eGlassNum = 2,
	eBlockNum = 3,
	eVerticalMoveGroundNum = 4,
	eJumpNum = 5,
	eLateralMoveGroundNum = 6,
	ePlayerNum = 7,
	eLowUpBlockNum = 8,
	eVerticalBlockNum = 9,
	eAerialBlockNum = 10,
	eRightBlockNum = 11,
	eLeftBlockNum = 13,
	eLeftGroundNum = 14,
	eRightGroundNum = 15,
	eDownBlockNum = 16,
	eHighUpBlockNum = 17,
	eGoalBlockNum = 20,
	eRightOneMoveBlockNum = 418,
	eLeftOneMoveBlockNum = 419,

};

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
	@fn		チュートリアルのjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return プレイヤーのポインタ
	*/
	Player* OpenTutorialFile();

	/*
	@fn		ステージ1のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return プレイヤーのポインタ
	*/
	Player* OpenStage01File();

	/*
	@fn		ステージ2のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	@return プレイヤーのポインタ
	*/
	Player* OpenStage02File();

	/*
	@fn	   チュートリアルのマップデータにアクセスする
	@param _mapData マップデータ
	@param _sizeY 上に配置していくためのオブジェクトの個数
	*/
	void AccessTutorialMapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
    @fn	   ステージ1のマップデータにアクセスする
    @param _mapData マップデータ
    @param _sizeY 上に配置していくためのオブジェクトの個数
    */
	void AccessStage01MapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
    @fn	   ステージ2のマップデータにアクセスする
    @param _mapData マップデータ
    @param _sizeY 上に配置していくためのオブジェクトの個数
    */
	void AccessStage02MapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
	@fn    チュートリアルのオブジェクトを生成する
	@param _name マップデータの要素
	@param _objectPos オブジェクトの座標
	*/
	void CreateTutorialObject(const unsigned int _Name, const Vector3 _ObjectPos);

	/*
	@fn    ステージ1のオブジェクトを生成する
	@param _name マップデータの要素
	@param _objectPos オブジェクトの座標
	*/
	void CreateStage01Object(const unsigned int _Name, const Vector3 _ObjectPos);

	/*
	@fn    ステージ2のオブジェクトを生成する
	@param _name マップデータの要素
	@param _objectPos オブジェクトの座標
	*/
	void CreateStage02Object(const unsigned int _Name, const Vector3 _ObjectPos);

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _FileName, const char* _LayerName);

	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);

	// 下層のマップデータ
	std::vector<std::vector<int>> mLowerMapData;
	// 上層のマップデータ
	std::vector<std::vector<int>> mUpperMapData;
	// プレイヤーのマップデータ
	std::vector<std::vector<int>> mPlayerMapData;
	// ゴール柱のマップデータ
	std::vector<std::vector<int>> mGoalBlockMapData;
	// 縦長障害物のマップデータ
	std::vector<std::vector<int>> mVerticalBlockMapData;
	// 上移動ブロックのマップデータ
	std::vector<std::vector<int>> mUpBlockMapData;

	// プレイヤーのポインタ
	Player* mPlayer;
	// 幅のマップデータ
	int	mSizeX;
	// 高さのマップデータ
	int	mSizeY;
	// 奥行のマップデータ
	int	mSizeZ;
	// オブジェクトごとの距離
	float mOffset;
};

