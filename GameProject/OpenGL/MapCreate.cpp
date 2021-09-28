/*
@brief インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
MapCreate::MapCreate() :GameObject(SceneBase::Scene::eOtherScene,Tag::eOtherTag)
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
	if (!readTiledJson(mPlayerMapData, "Assets/Config/TutorialStage.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/TutorialStage.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/TutorialStage.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/TutorialStage.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	mSizeY = 1;
	AccessTutorialMapData(mPlayerMapData, mSizeY);
	AccessTutorialMapData(mLowerMapData, mSizeY);
	AccessTutorialMapData(mUpperMapData, mSizeY);
	
	mSizeY = 10;
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
	if (!readTiledJson(mPlayerMapData, "Assets/Config/FirstStage.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/FirstStage.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/FirstStage.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/FirstStage.json", "Goal"))
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
	if (!readTiledJson(mPlayerMapData, "Assets/Config/SecondStage.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// 下層のマップデータの読み込み
	if (!readTiledJson(mLowerMapData, "Assets/Config/SecondStage.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// 上層のマップデータの読み込み
	if (!readTiledJson(mUpperMapData, "Assets/Config/SecondStage.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/SecondStage.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/SecondStage.json", "VerticalBlock"))
	{
		printf("don't have Layer/VerticalBlock\n");
	}

	// ゴールのマップデータの読み込み
	if (!readTiledJson(mUpBlockMapData, "Assets/Config/SecondStage.json", "UpBlock"))
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
	    case(MapDataNum::eGroundNum):
        	new Ground(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/Ground.gpmesh", Tag::eGroundTag, SceneBase::Scene::eTutorial);
        	break;
        case(MapDataNum::eGlassNum):
        	new Glass(_ObjectPos, ObjectSize, "Assets/GpMesh/Glass.gpmesh", Tag::eGlassTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        case(MapDataNum::eBlockNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 BlockPos = _ObjectPos + AddPos;
        
        	new Block(BlockPos, ObstacleSize, "Assets/GpMesh/TutorialStage/Block.gpmesh", Tag::eBlockTag, SceneBase::Scene::eTutorial);
        	break;
        }
        case(MapDataNum::eVerticalMoveGroundNum):
        	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/VerticalMoveGround.gpmesh", Tag::eVerticalMoveGroundTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        case(MapDataNum::eJumpNum):
        	new Jump(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/Jump.gpmesh", Tag::eJumpTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        case(MapDataNum::eLateralMoveGroundNum):
        	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/Ground.gpmesh", Tag::eLateralMoveGroundTag, SceneBase::Scene::eTutorial, 1000.0f, mPlayer);
        	break;
        case(MapDataNum::ePlayerNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
        	const Vector3 PlayerPos = _ObjectPos + AddPos;
        	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
        
        	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/GpMesh/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::Scene::eTutorial);
        	break;
        }
        case(MapDataNum::eLowUpBlockNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
        	const Vector3 UpBlockPos = _ObjectPos + AddPos;
        
        	new UpBlock(UpBlockPos, ObstacleSize, "Assets/GpMesh/TutorialStage/Block.gpmesh", Tag::eLowUpBlockTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        }
        case(MapDataNum::eLeftGroundNum):
        	new LeftGround(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/LeftGround.gpmesh", Tag::eLeftGroundTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        case(MapDataNum::eRightGroundNum):
        	new RightGround(_ObjectPos, ObjectSize, "Assets/GpMesh/TutorialStage/RightGround.gpmesh", Tag::eRightGroundTag, SceneBase::Scene::eTutorial, mPlayer);
        	break;
        case(MapDataNum::eGoalBlockNum):
        {
        	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
        
        	new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/GpMesh/TutorialStage/GoalBlock.gpmesh", Tag::eGoalBlockTag, SceneBase::Scene::eTutorial);
        	break;
        }
		case(MapDataNum::eGoalWarpHoleNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 300.0f, -100.0f);
			const Vector3 GoalWarpHolePos = _ObjectPos + AddPos;
			const Vector3 GoalWarpHoleSize = Vector3(4.5f, 4.0f, 1.0f);

			new GoalWarpHole(GoalWarpHolePos, GoalWarpHoleSize, "Assets/GpMesh/Cylinder.gpmesh", Tag::eGoalWarpHoleTag, SceneBase::Scene::eTutorial, mPlayer);
			break;
		}
		case(MapDataNum::eGoalCircleFrameNum):
		{
			const Vector3 AddPos = Vector3(0.0f, -150.0f, -100.0f);
			const Vector3 GoalCircleFramePos = _ObjectPos + AddPos;
			const Vector3 GoalCircleFrameSize = Vector3(2.5f, 1.0f, 2.5f);

			new GoalCircleFrame(GoalCircleFramePos, GoalCircleFrameSize, "Assets/GpMesh/CircleFrame.gpmesh", Tag::eGoalCircleFrameTag, SceneBase::Scene::eTutorial);
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
	    case(MapDataNum::eGroundNum):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/GpMesh/FirstStage/Ground.gpmesh", Tag::eGroundTag, SceneBase::Scene::eStage01);
	    	break;
	    case(MapDataNum::eGlassNum):
			new Glass(_ObjectPos, ObjectSize, "Assets/GpMesh/Glass.gpmesh", Tag::eGlassTag,SceneBase::Scene::eStage01, mPlayer);
			break;
	    case(MapDataNum::eBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
			new Block(BlockPos, ObstacleSize, "Assets/GpMesh/FirstStage/Block.gpmesh", Tag::eBlockTag, SceneBase::Scene::eStage01);
			break;
	    }
	    case(MapDataNum::eVerticalMoveGroundNum):
		    new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/FirstStage/VerticalMoveGround.gpmesh", Tag::eVerticalMoveGroundTag, SceneBase::Scene::eStage01, mPlayer);
			break;
	    case(MapDataNum::eJumpNum):
			new Jump(_ObjectPos, ObjectSize, "Assets/GpMesh/FirstStage/Jump.gpmesh", Tag::eJumpTag, SceneBase::Scene::eStage01, mPlayer);
			break;
		case(MapDataNum::eLateralMoveGroundNum):
			new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/FirstStage/Ground.gpmesh", Tag::eLateralMoveGroundTag, SceneBase::Scene::eStage01 ,1000.0f, mPlayer);
			break;
	    case(MapDataNum::ePlayerNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
		    mPlayer = new Player(PlayerPos, PlayerSize, "Assets/GpMesh/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::Scene::eStage01);
			break;
	    }
	    case(MapDataNum::eGoalBlockNum):
		{
			const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);

			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/GpMesh/FirstStage/GoalBlock.gpmesh", Tag::eGoalBlockTag, SceneBase::Scene::eStage01);
			break;
		}
		case(MapDataNum::eGoalWarpHoleNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 300.0f, -100.0f);
			const Vector3 GoalWarpHolePos = _ObjectPos + AddPos;
			const Vector3 GoalWarpHoleSize = Vector3(4.5f, 4.0f, 1.0f);

			new GoalWarpHole(GoalWarpHolePos, GoalWarpHoleSize, "Assets/GpMesh/Cylinder.gpmesh", Tag::eGoalWarpHoleTag, SceneBase::Scene::eStage01, mPlayer);
			break;
		}
		case(MapDataNum::eGoalCircleFrameNum):
		{
			const Vector3 AddPos = Vector3(0.0f, -150.0f, -100.0f);
			const Vector3 GoalCircleFramePos = _ObjectPos + AddPos;
			const Vector3 GoalCircleFrameSize = Vector3(2.5f, 1.0f, 2.5f);

			new GoalCircleFrame(GoalCircleFramePos, GoalCircleFrameSize, "Assets/GpMesh/CircleFrame.gpmesh", Tag::eGoalCircleFrameTag, SceneBase::Scene::eStage01);
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
	    case(MapDataNum::eGroundNum):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/Ground.gpmesh", Tag::eGroundTag, SceneBase::Scene::eStage02);
	    	break;
	    case(MapDataNum::eGlassNum):
	    	new Glass(_ObjectPos, ObjectSize, "Assets/GpMesh/Glass.gpmesh", Tag::eGlassTag, SceneBase::Scene::eStage02, mPlayer);
	    	break;
	    case(MapDataNum::eBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
	    	new Block(BlockPos, ObstacleSize, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eBlockTag, SceneBase::Scene::eStage02);
	    	break;
	    }
	    case(MapDataNum::eVerticalMoveGroundNum):
	    	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/VerticalMoveGround.gpmesh", Tag::eVerticalMoveGroundTag, SceneBase::Scene::eStage02, mPlayer);
	    	break;
	    case(MapDataNum::eJumpNum):
	    	new Jump(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/Jump.gpmesh", Tag::eJumpTag, SceneBase::Scene::eStage02, mPlayer);
	    	break;
	    case(MapDataNum::eLateralMoveGroundNum):
	    	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/Ground.gpmesh", Tag::eLateralMoveGroundTag, SceneBase::Scene::eStage02, 1000.0f, mPlayer);
	    	break;
	    case(MapDataNum::ePlayerNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
	    	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/GpMesh/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::Scene::eStage02);
	    	break;
	    }
	    case(MapDataNum::eLowUpBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eLowUpBlockTag, SceneBase::Scene::eStage02, mPlayer);
	    	break;
	    }
	    case(MapDataNum::eVerticalBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 VerticalBlockPos = _ObjectPos + AddPos;
	    
	    	new VerticalBlock(VerticalBlockPos, ObstacleSize, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eVerticalBlockTag, SceneBase::Scene::eStage02);
	    	break;
	    }
	    case(MapDataNum::eAerialBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 AerialBlockPos = _ObjectPos + AddPos;
			const Vector3 AerialBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
	    	new AerialBlock(AerialBlockPos, AerialBlockSize, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eAerialBlockTag, SceneBase::Scene::eStage02);
	    	break;
	    }
		case(MapDataNum::eRightBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPosX = 600.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPosX, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eRightBlockTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		}
		case(MapDataNum::eLeftBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 600.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eLeftBlockTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		}
		case(MapDataNum::eLeftGroundNum):
			new LeftGround(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/LeftGround.gpmesh", Tag::eLeftGroundTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		case(MapDataNum::eRightGroundNum):
			new RightGround(_ObjectPos, ObjectSize, "Assets/GpMesh/SecondStage/RightGround.gpmesh", Tag::eRightGroundTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		case(MapDataNum::eDownBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 1600.0f, 0.0f);
			const Vector3 DownBlockPos = _ObjectPos + AddPos;

			new DownBlock(DownBlockPos, ObjectSize, "Assets/GpMesh/SecondStage/Ground.gpmesh", Tag::eDownBlockTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		}
	    case(MapDataNum::eHighUpBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eHighUpBlockTag, SceneBase::Scene::eStage02, mPlayer);
	    	break;
	    }
	    case(MapDataNum::eGoalBlockNum):
	    {
	    	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/GpMesh/SecondStage/GoalBlock.gpmesh", Tag::eGoalBlockTag, SceneBase::Scene::eStage02);
			break;
	    }
		case(MapDataNum::eGoalWarpHoleNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 300.0f, -100.0f);
			const Vector3 GoalWarpHolePos = _ObjectPos + AddPos;
			const Vector3 GoalWarpHoleSize = Vector3(4.5f, 4.0f, 1.0f);

			new GoalWarpHole(GoalWarpHolePos, GoalWarpHoleSize, "Assets/GpMesh/Cylinder.gpmesh", Tag::eGoalWarpHoleTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		}
		case(MapDataNum::eGoalCircleFrameNum):
		{
			const Vector3 AddPos = Vector3(0.0f, -150.0f, -100.0f);
			const Vector3 GoalCircleFramePos = _ObjectPos + AddPos;
			const Vector3 GoalCircleFrameSize = Vector3(2.5f, 1.0f, 2.5f);

			new GoalCircleFrame(GoalCircleFramePos, GoalCircleFrameSize, "Assets/GpMesh/CircleFrame.gpmesh", Tag::eGoalCircleFrameTag, SceneBase::Scene::eStage02);
			break;
		}
		case(MapDataNum::eRightOneMoveBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPos, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eRightOneMoveBlockTag, SceneBase::Scene::eStage02, mPlayer);
			break;
		}
		case(MapDataNum::eLeftOneMoveBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/GpMesh/SecondStage/Block.gpmesh", Tag::eLeftOneMoveBlockTag, SceneBase::Scene::eStage02, mPlayer);
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