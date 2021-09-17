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
	eGround = 1,
	eGlass = 2,
	eBlock = 3,
	eVerticalMoveGround = 4,
	eJump = 5,
	eLateralMoveGround = 6,
	ePlayer = 7,
	eLowUpBlock = 8,
	eVerticalBlock = 9,
	eAerialBlock = 10,
	eRightBlock = 11,
	eLeftBlock = 13,
	eLeftGround = 14,
	eRightGround = 15,
	eDownBlock = 16,
	eHighUpBlock = 17,
	eGoalBlock = 20,
	eOneRightBlock = 418,
	eOneLeftBlock = 419,

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

