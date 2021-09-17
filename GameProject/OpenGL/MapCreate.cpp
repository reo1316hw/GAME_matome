/*
@brief インクルード
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
	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/tutorialFix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/tutorialFix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/tutorialFix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/tutorialFix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	mSizeY = 1;
	AccessTutorialMapData(mPlayerMapData, mSizeY);
	AccessTutorialMapData(mLowerMapData, mSizeY);
	AccessTutorialMapData(mUpperMapData, mSizeY);
	
	mSizeY = 5;
	AccessTutorialMapData(mGoalBlockMapData, mSizeY);

	return mPlayer;
}

/*
@fn		ステージ1のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return プレイヤーのポインタ
*/
Player* MapCreate::OpenStage01File()
{
	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage01Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage01Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage01Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage01Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	mSizeY = 1;
	AccessStage01MapData(mPlayerMapData, mSizeY);
	AccessStage01MapData(mLowerMapData, mSizeY);
	AccessStage01MapData(mUpperMapData, mSizeY);

	mSizeY = 10;
	AccessStage01MapData(mGoalBlockMapData, mSizeY);

	return mPlayer;
}

/*
@fn	  ステージ2のjsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return プレイヤーのポインタ
*/
Player* MapCreate::OpenStage02File()
{
	// プレイヤーのマップデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage02Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage02Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage02Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage02Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/stage02Fix.json", "VerticalBlock"))
	{
		printf("don't have Layer/VerticalBlock\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mUpBlockMapData, "Assets/Config/stage02Fix.json", "UpBlock"))
	{
		printf("don't have Layer/UpBlock\n");
	}

	mSizeY = 1;
	AccessStage02MapData(mPlayerMapData, mSizeY);
	AccessStage02MapData(mLowerMapData, mSizeY);
	AccessStage02MapData(mUpperMapData, mSizeY);
	AccessStage02MapData(mUpBlockMapData, mSizeY);

	mSizeY = 2;
	AccessStage02MapData(mVerticalBlockMapData, mSizeY);

	mSizeY = 10;
	AccessStage02MapData(mGoalBlockMapData, mSizeY);

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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateTutorialObject(Name, ObjectPos);
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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage01Object(Name, ObjectPos);
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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage02Object(Name, ObjectPos);
			}
		}
	}
}

/*
@fn    チュートリアルのオブジェクトを生成する
@param _Name マップデータの要素
@param _ObjectPos オブジェクトの座標
*/
void MapCreate::CreateTutorialObject(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_Name)
	{
	    case(eGround):
        	new Ground(_ObjectPos, ObjectSize, "Assets/box.gpmesh", ground, SceneBase::tutorial);
        	break;
        case(eGlass):
        	new Glass(_ObjectPos, ObjectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial, mPlayer);
        	break;
        case(eBlock):
        {
        	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
        	const Vector3 BlockPos = _ObjectPos + AddPos;
        
        	new Block(BlockPos, ObstacleSize, "Assets/box_03.gpmesh", block, SceneBase::tutorial);
        	break;
        }
        case(eVerticalMoveGround):
        	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_04.gpmesh", verticalMoveGround, SceneBase::tutorial, mPlayer);
        	break;
        case(eJump):
        	new Jump(_ObjectPos, ObjectSize, "Assets/box_05.gpmesh", jump, SceneBase::tutorial, mPlayer);
        	break;
        case(eLateralMoveGround):
        	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box.gpmesh", lateralMoveGround, SceneBase::tutorial, 1000.0f, mPlayer);
        	break;
        case(ePlayer):
        {
        	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
        	const Vector3 PlayerPos = _ObjectPos + AddPos;
        	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
        
        	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", player, SceneBase::tutorial);
        	break;
        }
        case(eLowUpBlock):
        {
        	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
        	const Vector3 UpBlockPos = _ObjectPos + AddPos;
        
        	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_03.gpmesh", upBlock, SceneBase::tutorial, mPlayer);
        	break;
        }
        case(eLeftGround):
        	new LeftGround(_ObjectPos, ObjectSize, "Assets/box_07.gpmesh", leftGround, SceneBase::tutorial, mPlayer);
        	break;
        case(eRightGround):
        	new RightGround(_ObjectPos, ObjectSize, "Assets/box_06.gpmesh", rightGround, SceneBase::tutorial, mPlayer);
        	break;
        case(eGoalBlock):
        {
        	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
        
        	new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_03.gpmesh", goalBlock, SceneBase::tutorial);
        	break;
        }
	}
}

/*
@fn    ステージ1のオブジェクトを生成する
@param _Name マップデータの要素
@param _ObjectPos オブジェクトの座標
*/
void MapCreate::CreateStage01Object(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_Name)
	{
	    case(eGround):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/box_08.gpmesh", ground, SceneBase::stage01);
	    	break;
	    case(eGlass):
			new Glass(_ObjectPos, ObjectSize, "Assets/box_09.gpmesh", glass,SceneBase::stage01, mPlayer);
			break;
	    case(eBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
			new Block(BlockPos, ObstacleSize, "Assets/box_10.gpmesh", block, SceneBase::stage01);
			break;
	    }
	    case(eVerticalMoveGround):
		    new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_11.gpmesh", verticalMoveGround, SceneBase::stage01, mPlayer);
			break;
	    case(eJump):
			new Jump(_ObjectPos, ObjectSize, "Assets/box_12.gpmesh", jump, SceneBase::stage01, mPlayer);
			break;
		case(eLateralMoveGround):
			new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box_08.gpmesh", lateralMoveGround, SceneBase::stage01 ,1000.0f, mPlayer);
			break;
	    case(ePlayer):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
		    mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", player, SceneBase::stage01);
			break;
	    }
	    case(eGoalBlock):
		{
			const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);

			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_10.gpmesh", goalBlock, SceneBase::stage01);
			break;
		}
	}
}

/*
@fn    ステージ2のオブジェクトを生成する
@param _Name マップデータの要素
@param _ObjectPos オブジェクトの座標
*/
void MapCreate::CreateStage02Object(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);
	const Vector3 MoveObstacleSize = Vector3(70.0f, 70.0f, 100.0f);

	switch (_Name)
	{
	    case(eGround):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/box_13.gpmesh", ground, SceneBase::stage02);
	    	break;
	    case(eGlass):
	    	new Glass(_ObjectPos, ObjectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02, mPlayer);
	    	break;
	    case(eBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
	    	new Block(BlockPos, ObstacleSize, "Assets/box_15.gpmesh", block, SceneBase::stage02);
	    	break;
	    }
	    case(eVerticalMoveGround):
	    	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_16.gpmesh", verticalMoveGround, SceneBase::stage02, mPlayer);
	    	break;
	    case(eJump):
	    	new Jump(_ObjectPos, ObjectSize, "Assets/box_17.gpmesh", jump, SceneBase::stage02, mPlayer);
	    	break;
	    case(eLateralMoveGround):
	    	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box_13.gpmesh", lateralMoveGround, SceneBase::stage02, 1000.0f, mPlayer);
	    	break;
	    case(ePlayer):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
	    	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", player, SceneBase::stage02);
	    	break;
	    }
	    case(eLowUpBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_15.gpmesh", upBlock, SceneBase::stage02, mPlayer);
	    	break;
	    }
	    case(eVerticalBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 VerticalBlockPos = _ObjectPos + AddPos;
	    
	    	new VerticalBlock(VerticalBlockPos, ObstacleSize, "Assets/box_15.gpmesh", verticalBlock, SceneBase::stage02);
	    	break;
	    }
	    case(eAerialBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 AerialBlockPos = _ObjectPos + AddPos;
			const Vector3 AerialBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
	    	new AerialBlock(AerialBlockPos, AerialBlockSize, "Assets/box_15.gpmesh", aerialBlock, SceneBase::stage02);
	    	break;
	    }
		case(eRightBlock):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPosX = 600.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPosX, "Assets/box_15.gpmesh", rightBlock, ColliderTag::eRightBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(eLeftBlock):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 600.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", leftBlock, ColliderTag::eLeftBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(eLeftGround):
			new LeftGround(_ObjectPos, ObjectSize, "Assets/box_19.gpmesh", leftGround, SceneBase::stage02, mPlayer);
			break;
		case(eRightGround):
			new RightGround(_ObjectPos, ObjectSize, "Assets/box_18.gpmesh", rightGround, SceneBase::stage02, mPlayer);
			break;
		case(eDownBlock):
		{
			const Vector3 AddPos = Vector3(0.0f, 1600.0f, 0.0f);
			const Vector3 DownBlockPos = _ObjectPos + AddPos;

			new DownBlock(DownBlockPos, ObjectSize, "Assets/box_13.gpmesh", downBlock, SceneBase::stage02, mPlayer);
			break;
		}
	    case(eHighUpBlock):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_15.gpmesh", upBlock_02, SceneBase::stage02, mPlayer);
	    	break;
	    }
	    case(eGoalBlock):
	    {
	    	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_15.gpmesh", goalBlock, SceneBase::stage02);
			break;
	    }
		case(eOneRightBlock):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", rightOneMoveBlock, ColliderTag::eRightOneMoveBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
		case(eOneLeftBlock):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", leftOneMoveBlock, ColliderTag::eLeftOneMoveBlockTag, SceneBase::stage02, mPlayer);
			break;
		}
	}
}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _FileName, const char* _LayerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc, _FileName))
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
	std::string layerNameString(_LayerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _LayerName);
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