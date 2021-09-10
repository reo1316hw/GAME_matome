/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate() :GameObject(SceneBase::other,Tag::Other)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
	mOffset = 200;
}

/*
@fn	デストラクタ
*/
MapCreate::~MapCreate()
{
	mLowerMapData.clear();
	mUpperMapData.clear();
}

/*
@fn	    チュートリアルのjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return プレイヤーのポインタ
*/
Player* MapCreate::OpenTutorialFile()
{
	//int readCount = 0;

	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/tutorialFix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/tutorialFix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/tutorialFix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/tutorialFix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	AccessTutorialMapData(mPlayerMapData, 1);
	AccessTutorialMapData(mLowerMapData, 1);
	AccessTutorialMapData(mUpperMapData, 1);
	AccessTutorialMapData(mGoalBlockMapData, 10);

	/*readCount++;

	for (int i = 0; i < readCount; i++)
	{
		AccessMapData();
	}*/

	return mPlayer;
}

/*
@fn		ステージ1のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return プレイヤーのポインタ
*/
Player* MapCreate::OpenStage01File()
{
	//int readCount = 0;

	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage01Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage01Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage01Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage01Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	AccessStage01MapData(mPlayerMapData, 1);
	AccessStage01MapData(mLowerMapData, 1);
	AccessStage01MapData(mUpperMapData, 1);
	AccessStage01MapData(mGoalBlockMapData, 10);

	/*readCount++;

	for (int i = 0; i < readCount; i++)
	{
		AccessMapData();
	}*/

	return mPlayer;
}

/*
@fn	  ステージ2のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return プレイヤーのポインタ
*/
Player* MapCreate::OpenStage02File()
{
	//int readCount = 0;

	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage02Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage02Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage02Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage02Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	//readCount++;

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/stage02Fix.json", "VerticalBlock"))
	{
		printf("don't have Layer/VerticalBlock\n");
	}

	//readCount++;

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mUpBlockMapData, "Assets/Config/stage02Fix.json", "UpBlock"))
	{
		printf("don't have Layer/UpBlock\n");
	}

	AccessStage02MapData(mPlayerMapData, 1);
	AccessStage02MapData(mLowerMapData, 1);
	AccessStage02MapData(mUpperMapData, 1);
	AccessStage02MapData(mUpBlockMapData, 1);
	AccessStage02MapData(mVerticalBlockMapData, 2);
	AccessStage02MapData(mGoalBlockMapData, 10);

	/*readCount++;

	for (int i = 0; i < readCount; i++)
	{
		AccessMapData();
	}*/

	return mPlayer;
}

/*
@fn	   チュートリアルのマップデータにアクセスする
@param _mapData マップデータ
@param _sizeY 上に配置していくためのオブジェクトの個数
*/
void MapCreate::AccessTutorialMapData(std::vector<std::vector<int>> _mapData, int _sizeY)
{
	for (int iz = 0; iz < mSizeZ; iz++)
	{
		for (int ix = 0; ix < mSizeX; ix++)
		{
			for (int iy = 0; iy < _sizeY; iy++)
			{
				const unsigned int name = _mapData[iz][ix];
				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateTutorialObject(name, objectPos);
			}
		}
	}
}

/*
@fn	   ステージ1のマップデータにアクセスする
@param _mapData マップデータ
@param _sizeY 上に配置していくためのオブジェクトの個数
*/
void MapCreate::AccessStage01MapData(std::vector<std::vector<int>> _mapData, int _sizeY)
{
	for (int iz = 0; iz < mSizeZ; iz++)
	{
		for (int ix = 0; ix < mSizeX; ix++)
		{
			for (int iy = 0; iy < _sizeY; iy++)
			{
				const unsigned int name = _mapData[iz][ix];
				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage01Object(name, objectPos);
			}
		}
	}
}

/*
@fn	   ステージ2のマップデータにアクセスする
@param _mapData マップデータ
@param _sizeY 上に配置していくためのオブジェクトの個数
*/
void MapCreate::AccessStage02MapData(std::vector<std::vector<int>> _mapData, int _sizeY)
{
	for (int iz = 0; iz < mSizeZ; iz++)
	{
		for (int ix = 0; ix < mSizeX; ix++)
		{
			for (int iy = 0; iy < _sizeY; iy++)
			{
				const unsigned int name = _mapData[iz][ix];
				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage02Object(name, objectPos);
			}
		}
	}
}

/*
@fn    チュートリアルのオブジェクトを生成する
@param _name マップデータの要素
@param _objectPos オブジェクトの座標
*/
void MapCreate::CreateTutorialObject(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 obstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_name)
	{
        case(1):
        	new Ground(_objectPos, objectSize, "Assets/box.gpmesh", ground, SceneBase::tutorial);
        	break;
        case(2):
        	new Glass(_objectPos, objectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial, mPlayer);
        	break;
        case(3):
        {
        	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
        	const Vector3 blockPos = _objectPos + addPos;
        
        	new Block(blockPos, obstacleSize, "Assets/box_03.gpmesh", block, SceneBase::tutorial);
        	break;
        }
        case(4):
        	new VerticalMoveGround(_objectPos, objectSize, "Assets/box_04.gpmesh", verticalMoveGround, SceneBase::tutorial, mPlayer);
        	break;
        case(5):
        	new Jump(_objectPos, objectSize, "Assets/box_05.gpmesh", jump, SceneBase::tutorial);
        	break;
        case(6):
        	new LateralMoveGround(_objectPos, objectSize, "Assets/box.gpmesh", lateralMoveGround, SceneBase::tutorial, 1000.0f, mPlayer);
        	break;
        case(7):
        {
        	const Vector3 addPos = Vector3(0.0f, 500.0f, 0.0f);
        	const Vector3 playerPos = _objectPos + addPos;
        	const Vector3 playerSize = Vector3(1.2f, 1.2f, 1.2f);
        
        	mPlayer = new Player(playerPos, playerSize, "Assets/Sphere.gpmesh", player, SceneBase::tutorial);
        	break;
        }
        case(8):
        {
        	const Vector3 addPos = Vector3(0.0f, -100.0f, 0.0f);
        	const Vector3 upBlockPos = _objectPos + addPos;
        
        	new UpBlock(upBlockPos, obstacleSize, "Assets/box_03.gpmesh", upBlock, SceneBase::tutorial, mPlayer);
        	break;
        }
        case(14):
        	new LeftGround(_objectPos, objectSize, "Assets/box_07.gpmesh", leftGround, SceneBase::tutorial, mPlayer);
        	break;
        case(15):
        	new RightGround(_objectPos, objectSize, "Assets/box_06.gpmesh", rightGround, SceneBase::tutorial, mPlayer);
        	break;
        case(20):
        {
        	const Vector3 goalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
        
        	new GoalBlock(_objectPos, goalBlockSize, "Assets/box_03.gpmesh", goalBlock, SceneBase::tutorial);
        	break;
        }
	}
}

/*
@fn    ステージ1のオブジェクトを生成する
@param _name マップデータの要素
@param _objectPos オブジェクトの座標
*/
void MapCreate::CreateStage01Object(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 obstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_name)
	{
	    case(1):
	    	new Ground(_objectPos, objectSize, "Assets/box_08.gpmesh", ground, SceneBase::stage01);
	    	break;
	    case(2):
			new Glass(_objectPos, objectSize, "Assets/box_09.gpmesh", glass,SceneBase::stage01, mPlayer);
			break;
	    case(3):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 blockPos = _objectPos + addPos;
	    
			new Block(blockPos, obstacleSize, "Assets/box_10.gpmesh", block, SceneBase::stage01);
			break;
	    }
	    case(4):
		    new VerticalMoveGround(_objectPos, objectSize, "Assets/box_11.gpmesh", verticalMoveGround, SceneBase::stage01, mPlayer);
			break;
	    case(5):
			new Jump(_objectPos, objectSize, "Assets/box_12.gpmesh", jump, SceneBase::stage01);
			break;
		case(6):
			new LateralMoveGround(_objectPos, objectSize, "Assets/box_08.gpmesh", lateralMoveGround, SceneBase::stage01 ,1000.0f, mPlayer);
			break;
	    case(7):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 playerPos = _objectPos + addPos;
	    	const Vector3 playerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
		    mPlayer = new Player(playerPos, playerSize, "Assets/Sphere.gpmesh", player, SceneBase::stage01);
			break;
	    }
	    case(20):
		{
			const Vector3 goalBlockSize = Vector3(100.0f, 100.0f, 100.0f);

			new GoalBlock(_objectPos, goalBlockSize, "Assets/box_10.gpmesh", goalBlock, SceneBase::stage01);
			break;
		}
		case(21):
			new Respawn(_objectPos, objectSize, respawn01, SceneBase::stage01);
			break;
		case(22):
			new Respawn(_objectPos, objectSize, respawn02, SceneBase::stage01);
			break;
		case(23):
			new Respawn(_objectPos, objectSize, respawn03, SceneBase::stage01);
			break;
	}
}

/*
@fn    ステージ2のオブジェクトを生成する
@param _name マップデータの要素
@param _objectPos オブジェクトの座標
*/
void MapCreate::CreateStage02Object(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 obstacleSize = Vector3(70.0f, 100.0f, 100.0f);
	const Vector3 moveObstacleSize = Vector3(70.0f, 70.0f, 100.0f);

	switch (_name)
	{
	    case(1):
	    	new Ground(_objectPos, objectSize, "Assets/box_13.gpmesh", ground, SceneBase::stage02);
	    	break;
	    case(2):
	    	new Glass(_objectPos, objectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02, mPlayer);
	    	break;
	    case(3):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 blockPos = _objectPos + addPos;
	    
	    	new Block(blockPos, obstacleSize, "Assets/box_15.gpmesh", block, SceneBase::stage02);
	    	break;
	    }
	    case(4):
	    	new VerticalMoveGround(_objectPos, objectSize, "Assets/box_16.gpmesh", verticalMoveGround, SceneBase::stage02, mPlayer);
	    	break;
	    case(5):
	    	new Jump(_objectPos, objectSize, "Assets/box_17.gpmesh", jump, SceneBase::stage02);
	    	break;
	    case(6):
	    	new LateralMoveGround(_objectPos, objectSize, "Assets/box_13.gpmesh", lateralMoveGround, SceneBase::stage02, 1000.0f, mPlayer);
	    	break;
	    case(7):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 playerPos = _objectPos + addPos;
	    	const Vector3 playerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
	    	mPlayer = new Player(playerPos, playerSize, "Assets/Sphere.gpmesh", player, SceneBase::stage02);
	    	break;
	    }
	    case(8):
	    {
	    	const Vector3 addPos = Vector3(0.0f, -100.0f, 0.0f);
	    	const Vector3 upBlockPos = _objectPos + addPos;
	    
	    	new UpBlock(upBlockPos, obstacleSize, "Assets/box_15.gpmesh", upBlock, SceneBase::stage02, mPlayer);
	    	break;
	    }
	    case(9):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 verticalBlockPos = _objectPos + addPos;
	    
	    	new VerticalBlock(verticalBlockPos, obstacleSize, "Assets/box_15.gpmesh", verticalBlock, SceneBase::stage02);
	    	break;
	    }
	    case(10):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 aerialBlockPos = _objectPos + addPos;
			const Vector3 aerialBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
	    	new AerialBlock(aerialBlockPos, aerialBlockSize, "Assets/box_15.gpmesh", aerialBlock, SceneBase::stage02);
	    	break;
	    }
		case(11):
		{
			const Vector3 addPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 rightBlockPos = _objectPos + addPos;
			const float addEndPosX = 600.0f;

			new RightBlock(rightBlockPos, moveObstacleSize, addEndPosX, "Assets/box_15.gpmesh", rightBlock, ColliderTag::rightBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(13):
		{
			const Vector3 addPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 leftBlockPos = _objectPos + addPos;
			const float addEndPos = 600.0f;

			new LeftBlock(leftBlockPos, moveObstacleSize, addEndPos, "Assets/box_15.gpmesh", leftBlock, ColliderTag::leftBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(14):
			new LeftGround(_objectPos, objectSize, "Assets/box_19.gpmesh", leftGround, SceneBase::stage02, mPlayer);
			break;
		case(15):
			new RightGround(_objectPos, objectSize, "Assets/box_18.gpmesh", rightGround, SceneBase::stage02, mPlayer);
			break;
		case(16):
		{
			const Vector3 addPos = Vector3(0.0f, 1600.0f, 0.0f);
			const Vector3 downBlockPos = _objectPos + addPos;

			new DownBlock(downBlockPos, objectSize, "Assets/box_13.gpmesh", downBlock, SceneBase::stage02, mPlayer);
			break;
		}
	    case(17):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 upBlockPos = _objectPos + addPos;
	    
	    	new UpBlock(upBlockPos, obstacleSize, "Assets/box_15.gpmesh", upBlock_02, SceneBase::stage02, mPlayer);
	    	break;
	    }
	    case(20):
	    {
	    	const Vector3 goalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
			new GoalBlock(_objectPos, goalBlockSize, "Assets/box_15.gpmesh", goalBlock, SceneBase::stage02);
			break;
	    }
		case(21):
			new Respawn(_objectPos, objectSize, respawn01, SceneBase::stage02);
			break;
		case(22):
			new Respawn(_objectPos, objectSize, respawn02, SceneBase::stage02);
			break;
		case(23):
			new Respawn(_objectPos, objectSize, respawn03, SceneBase::stage02);
			break;
		case(418):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 rightBlockPos = _objectPos + addPos;
			const float addEndPos = 200.0f;

			new RightBlock(rightBlockPos, moveObstacleSize, addEndPos, "Assets/box_15.gpmesh", rightOneMoveBlock, ColliderTag::rightOneMoveBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(419):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 leftBlockPos = _objectPos + addPos;
			const float addEndPos = 200.0f;

			new LeftBlock(leftBlockPos, moveObstacleSize, addEndPos, "Assets/box_15.gpmesh", leftOneMoveBlock, ColliderTag::leftOneMoveBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
	}
}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc, _fileName))
	{
		return false;
	}

	//開いたdocumentのtypeはmapか？
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}
	//開いたdocumentにlayerはあるか？
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer数を取得
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer名から該当layerの添え字を調べる
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	_mapData.resize(height);
	for (auto&mapIter: _mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}

	return true;
}

int MapCreate::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName)
{
	int layerSize = _layer.Size();
	int i;
	std::string layerNameString(_layerName);
	for ( i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = _layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}
