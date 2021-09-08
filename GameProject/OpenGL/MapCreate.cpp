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
	mGroundMapData.clear();
	mGlassMapData.clear();
	mBlockMapData.clear();
	mVerticalMoveGroundMapData.clear();
	mJumpMapData.clear();
	mLateralMoveGroundMapData.clear();
	mPlayerMapData.clear();
	mUpBlockMapData.clear();
	mVerticalBlockMapData.clear();
	mAerialBlockMapData.clear();
	mRightBlockMapData.clear();
	mLeftBlockMapData.clear();
	mRightGroundMapData.clear();
	mLeftGroundMapData.clear();
	mDownBlockMapData.clear();
	mGoalBlockMapData.clear();
	mRespawnMapData.clear();
}

/*
@fn		jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
@return	ファイルを開けたか(bool型)
*/
bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------
	
	if (mScene == SceneBase::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/tutorial.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeZ = mGroundMapData.size();
		mSizeY = mGroundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(mGlassMapData, "Assets/Config/tutorial.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(mBlockMapData, "Assets/Config/tutorial.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(mVerticalMoveGroundMapData, "Assets/Config/tutorial.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(mJumpMapData, "Assets/Config/tutorial.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(mLateralMoveGroundMapData, "Assets/Config/tutorial.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/tutorial.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//上移動ブロックの読み込み
		if (!readTiledJson(mUpBlockMapData, "Assets/Config/tutorial.json", "UpBlock"))
		{
			printf("don't have Layer/UpBlock\n");
			return true;
		}

		//1マス右移動床の読み込み
		if (!readTiledJson(mRightGroundMapData, "Assets/Config/tutorial.json", "RightGround"))
		{
			printf("don't have Layer/RightGround\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(mLeftGroundMapData, "Assets/Config/tutorial.json", "LeftGround"))
		{
			printf("don't have Layer/LeftGround\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(mGoalBlockMapData, "Assets/Config/tutorial.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

	}
	

	//-----------------------------------------------
	//----------------stage01------------------------
	//-----------------------------------------------
	
	if (mScene == SceneBase::stage01)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/RunMap.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeZ = mGroundMapData.size();
		mSizeY = mGroundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(mGlassMapData, "Assets/Config/RunMap.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(mBlockMapData, "Assets/Config/RunMap.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(mVerticalMoveGroundMapData, "Assets/Config/RunMap.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(mJumpMapData, "Assets/Config/RunMap.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(mLateralMoveGroundMapData, "Assets/Config/RunMap.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/RunMap.json", "player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(mGoalBlockMapData, "Assets/Config/RunMap.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

		//リスポーン地点の読み込み
		if (!readTiledJson(mRespawnMapData, "Assets/Config/RunMap.json", "Respawn"))
		{
			printf("don't have Layer/Respawn\n");
			return true;
		}
	}

	//--------------------------------------------------------------
	//------------------------stage02-------------------------------
	//--------------------------------------------------------------
	
	if (mScene == SceneBase::stage02)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/RunMap02.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeZ = mGroundMapData.size();
		mSizeY = mGroundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(mGlassMapData, "Assets/Config/RunMap02.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(mBlockMapData, "Assets/Config/RunMap02.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(mVerticalMoveGroundMapData, "Assets/Config/RunMap02.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(mJumpMapData, "Assets/Config/RunMap02.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(mLateralMoveGroundMapData, "Assets/Config/RunMap02.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//上移動ブロックの読み込み
		if (!readTiledJson(mUpBlockMapData, "Assets/Config/RunMap02.json", "UpBlock"))
		{
			printf("don't have Layer/UpBlock\n");
			return true;
		}

		//縦長障害物の読み込み
		if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/RunMap02.json", "VerticalBlock"))
		{
			printf("don't have Layer/VerticalBlock\n");
			return true;
		}

		//空中ブロックの読み込み
		if (!readTiledJson(mAerialBlockMapData, "Assets/Config/RunMap02.json", "AerialBlock"))
		{
			printf("don't have Layer/AerialBlock\n");
			return true;
		}

		//右移動ブロックの読み込み
		if (!readTiledJson(mRightBlockMapData, "Assets/Config/RunMap02.json", "RightBlock"))
		{
			printf("don't have Layer/RightBlock\n");
			return true;
		}

		//左移動ブロックの読み込み
		if (!readTiledJson(mLeftBlockMapData, "Assets/Config/RunMap02.json", "LeftBlock"))
		{
			printf("don't have Layer/LeftBlock\n");
			return true;
		}

		//1マス右移動床の読み込み
		if (!readTiledJson(mRightGroundMapData, "Assets/Config/RunMap02.json", "RightGround"))
		{
			printf("don't have Layer/RightGround\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(mLeftGroundMapData, "Assets/Config/RunMap02.json", "LeftGround"))
		{
			printf("don't have Layer/LeftGround\n");
			return true;
		}

		//落下ブロックデータの読み込み
		if (!readTiledJson(mDownBlockMapData, "Assets/Config/RunMap02.json", "DownBlock"))
		{
			printf("don't have Layer/DownBlock\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/RunMap02.json", "Player"))
		{
			printf("don't have Layer/Player\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(mGoalBlockMapData, "Assets/Config/RunMap02.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

		//リスポーン地点の読み込み
		if (!readTiledJson(mRespawnMapData, "Assets/Config/RunMap02.json", "Respawn"))
		{
			printf("don't have Layer/Respawn\n");
			return true;
		}
	}

	return false;
}

/*
@fn	床のデータにアクセスする
*/
void MapCreate::AccessGroundData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
 			const unsigned int name = mGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateGround(name, objectPos);
		}
	}
}

//void MapCreate::AccessMapData(const Tag& _tag)
//{
//	for (int iz = 0; iz < mSizeZ; iz++)
//	{
//		for (int ix = 0; ix < mSizeX; ix++)
//		{
//			CreateObject(_tag,iz, ix);
//		}
//	}
//}

//void MapCreate::CreateObject(const Tag& _groundTag, int _iz, int _ix)
//{
//	const unsigned int name = mGroundMapData[_iz][_ix];
//	const Vector3 objectPos = Vector3(mOffset * _ix, 0, -mOffset * _iz);
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (name)
//		{
//		case(1):
//			new Ground(objectPos, objectSize, "Assets/box.gpmesh", _groundTag, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (name)
//		{
//		case(1):
//			new Ground(objectPos, objectSize, "Assets/box_08.gpmesh", _groundTag, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (name)
//		{
//		case(1):
//			new Ground(objectPos, objectSize, "Assets/box_13.gpmesh", _groundTag, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}

//void MapCreate::CreateObject(const Tag& _glassTag, int _iz, int _ix)
//{
//	const unsigned int name = mGlassMapData[_iz][_ix];
//	const Vector3 objectPos = Vector3(mOffset * _ix, 0, -mOffset * _iz);
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (name)
//		{
//		case(2):
//			new Glass(objectPos, objectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (name)
//		{
//		case(2):
//			new Glass(objectPos, objectSize, "Assets/box_09.gpmesh", glass, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (name)
//		{
//		case(2):
//			new Glass(objectPos, objectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}

/*
@fn	床を生成する
*/
void MapCreate::CreateGround(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(1):
			new Ground(_objectPos, objectSize, "Assets/box.gpmesh", ground, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(1):
			new Ground(_objectPos, objectSize, "Assets/box_08.gpmesh", ground, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(1):
			new Ground(_objectPos, objectSize, "Assets/box_13.gpmesh", ground, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	ガラス床のデータにアクセスする
*/
void MapCreate::AccessGlassData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGlassMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateGlass(name, objectPos);
		}
	}
}

/*
@fn	ガラス床を生成する
*/
void MapCreate::CreateGlass(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(2):
			new Glass(_objectPos, objectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(2):
			new Glass(_objectPos, objectSize, "Assets/box_09.gpmesh", glass,SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(2):
			new Glass(_objectPos, objectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	障害物のデータにアクセスする
*/
void MapCreate::AccessBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);

			CreateBlock(name, objectPos);
		}
	}
}

/*
@fn	障害物を生成する
*/
void MapCreate::CreateBlock(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(70, 100, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(3):
			new Block(_objectPos, objectSize, "Assets/box_03.gpmesh", block, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(3):
			new Block(_objectPos, objectSize, "Assets/box_10.gpmesh", block, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(3):
			new Block(_objectPos, objectSize, "Assets/box_15.gpmesh", block, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	縦移動床のデータにアクセスする
*/
void MapCreate::AccessVerticalMoveGroundData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mVerticalMoveGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateVerticalMoveGround(name, objectPos);
		}
	}
}

/*
@fn	縦移動床を生成する
*/
void MapCreate::CreateVerticalMoveGround(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(4):
			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_04.gpmesh", verticalMoveGround, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(4):
			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_11.gpmesh", verticalMoveGround, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(4):
			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_16.gpmesh", verticalMoveGround, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	ジャンプ中のデータにアクセスする
*/
void MapCreate::AccessJumpData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mJumpMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateJump(name, objectPos);
		}
	}
}

/*
@fn	ジャンプ中を生成する
*/
void MapCreate::CreateJump(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(5):
			new Jump(_objectPos, objectSize, "Assets/box_05.gpmesh", jump, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(5):
			new Jump(_objectPos, objectSize, "Assets/box_12.gpmesh", jump, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(5):
			new Jump(_objectPos, objectSize, "Assets/box_17.gpmesh", jump, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	横移動床のデータにアクセスする
*/
void MapCreate::AccessLateralMoveGroundData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLateralMoveGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateLateralMoveGround(name, objectPos);
		}
	}
}

/*
@fn	横移動床を生成する
*/
void MapCreate::CreateLateralMoveGround(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(6):
			new LateralMoveGround(_objectPos, objectSize, "Assets/box.gpmesh", lateralMoveGround, SceneBase::tutorial,1000.0f);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(6):
			new LateralMoveGround(_objectPos, objectSize, "Assets/box_08.gpmesh", lateralMoveGround, SceneBase::stage01 ,1000.0f);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(6):
			new LateralMoveGround(_objectPos, objectSize, "Assets/box_13.gpmesh" ,lateralMoveGround, SceneBase::stage02, 1000.0f);
			break;
		}
		break;
	}
}

/*
@fn	    プレイヤーのデータにアクセスする
@return プレイヤークラスのポインタ
*/
Player* MapCreate::AccessPlayerData()
{
	// プレイヤーのポインタ
	Player* playerPtr = nullptr;

	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);

			playerPtr = CreatePlayer(name, objectPos, playerPtr);
		}
	}

	return playerPtr;
}

/*
@fn	プレイヤーを生成する
@return プレイヤークラスのポインタ
*/
Player* MapCreate::CreatePlayer(const unsigned int _name, const Vector3 _objectPos, Player* _playerPtr)
{
	const Vector3 objectSize = Vector3(1.2f, 1.2f, 1.2f);
	
	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(7):
			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(7):
			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(7):
			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::stage02);
			break;
		}
		break;
	}

	return _playerPtr;
}

/*
@fn	上移動ブロックのデータにアクセスする
*/
void MapCreate::AccessUpBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mUpBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, -100, -mOffset * iz);
			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);

			CreateUpBlock(name, objectPos, objectPos2);
		}
	}
}

/*
@fn	上移動ブロックを生成する
*/
void MapCreate::CreateUpBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
{
	const Vector3 objectSize = Vector3(70, 100, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(8):
			new UpBlock(_objectPos, objectSize, "Assets/box_03.gpmesh" ,upBlock, SceneBase::tutorial);
			break;
		}

		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(8):
			new UpBlock(_objectPos, objectSize, "Assets/box_15.gpmesh" ,upBlock, SceneBase::stage02);
			break;

		case(17):
			new UpBlock(_objectPos2, objectSize, "Assets/box_15.gpmesh", upBlock_02, SceneBase::stage02);
			break;
		}

		break;
	}
}

/*
@fn	縦長障害物のデータにアクセスする
*/
void MapCreate::AccessVerticalBlockData()
{
	const int verticalBlockNumY = 2;

	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (int iy = 0; iy < verticalBlockNumY; iy++)
		{
			for (float ix = 0; ix < mSizeX; ix++)
			{
				const unsigned int name = mVerticalBlockMapData[(int)iz][(int)ix];
				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy + 100, -mOffset * iz);

				CreateVerticalBlock(name, objectPos);
			}
		}
	}
}

/*
@fn	縦長障害物を生成する
*/
void MapCreate::CreateVerticalBlock(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(70, 100, 100);

	if (mScene == SceneBase::stage02)
	{
		switch (_name)
		{
		case(9):
			new VerticalBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", verticalBlock, SceneBase::stage02);
			break;
		}
	}
}

/*
@fn	空中ブロックのデータにアクセスする
*/
void MapCreate::AccessAerialBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mAerialBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);

			CreateAerialBlock(name, objectPos);
		}
	}
}

/*
@fn	空中ブロックを生成する
*/
void MapCreate::CreateAerialBlock(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 100, 100);

	if (mScene == SceneBase::stage02)
	{
		switch (_name)
		{
		case(10):
			new AerialBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", aerialBlock, SceneBase::stage02);
			break;
		}
	}
}

/*
@fn	右移動ブロックのデータにアクセスする
*/
void MapCreate::AccessRightBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRightBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 70, -mOffset * iz);
			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);

			CreateRightBlock(name, objectPos, objectPos2);
		}
	}
}

/*
@fn	右移動ブロックを生成する
*/
void MapCreate::CreateRightBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
{
	const Vector3 objectSize = Vector3(70, 70, 100);
	const float addPosX = 600.0f;
	const float addPosX2 = 200.0f;

	if (mScene == SceneBase::stage02)
	{
		switch (_name)
		{
		case(11):
			new RightBlock(_objectPos, objectSize, addPosX, "Assets/box_15.gpmesh", rightBlock, ColliderTag::rightBlockTag, SceneBase::stage02);
			break;

		case(418):
			new RightBlock(_objectPos2, objectSize, addPosX2, "Assets/box_15.gpmesh", rightOneMoveBlock, ColliderTag::rightOneMoveBlockTag, SceneBase::stage02);
			break;
		}
	}
}

/*
@fn	左移動ブロックのデータにアクセスする
*/
void MapCreate::AccessLeftBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLeftBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 70, -mOffset * iz);
			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);

			CreateLeftBlock(name, objectPos, objectPos2);
		}
	}
}

/*
@fn	左移動ブロックを生成する
*/
void MapCreate::CreateLeftBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
{
	const Vector3 objectSize = Vector3(70, 70, 100);
	const float addPosX = 600.0f;
	const float addPosX2 = 200.0f;

	if (mScene == SceneBase::stage02)
	{
		switch (_name)
		{
		case(13):
			new LeftBlock(_objectPos, objectSize, addPosX, "Assets/box_15.gpmesh", leftBlock, ColliderTag::leftBlockTag, SceneBase::stage02);
			break;

		case(419):
			new LeftBlock(_objectPos2, objectSize, addPosX2, "Assets/box_15.gpmesh", leftOneMoveBlock, ColliderTag::leftOneMoveBlockTag, SceneBase::stage02);
			break;
		}
	}
}

/*
@fn	1マス右移動床のデータにアクセスする
*/
void MapCreate::AccessRightGroundData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRightGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateRightGround(name, objectPos);
		}
	}
}

/*
@fn	1マス右移動床を生成する
*/
void MapCreate::CreateRightGround(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(15):
			new RightGround(_objectPos, objectSize, "Assets/box_06.gpmesh", rightGround, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(15):
			new RightGround(_objectPos, objectSize, "Assets/box_18.gpmesh", rightGround, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	1マス左移動床のデータにアクセスする
*/
void MapCreate::AccessLeftGroundData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLeftGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);

			CreateLeftGround(name, objectPos);
		}
	}
}

/*
@fn	1マス左移動床を生成する
*/
void MapCreate::CreateLeftGround(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(14):
			new LeftGround(_objectPos, objectSize, "Assets/box_07.gpmesh", leftGround, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(14):
			new LeftGround(_objectPos, objectSize, "Assets/box_19.gpmesh", leftGround, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	落下ブロックのデータにアクセスする
*/
void MapCreate::AccessDownBlockData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mDownBlockMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 1600, -mOffset * iz);

			CreateDownBlock(name, objectPos);
		}
	}
}

/*
@fn	落下ブロックを生成する
*/
void MapCreate::CreateDownBlock(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	if (mScene == SceneBase::stage02)
	{
		switch (_name)
		{
		case(16):
			new DownBlock(_objectPos, objectSize, "Assets/box_13.gpmesh", downBlock, SceneBase::stage02);
			break;
		default:
			break;
		}
	}
}

/*
@fn	ゴール柱のデータにアクセスする
*/
void MapCreate::AccessGoalData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			for (float ix = 0; ix < mSizeX; ix++)
			{
				const unsigned int name = mGoalBlockMapData[(int)iz][(int)ix];
				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateGoal(name, objectPos);
			}
		}
	}
}

/*
@fn	ゴール柱を生成する
*/
void MapCreate::CreateGoal(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 100, 100);

	switch (mScene)
	{
	case SceneBase::tutorial:

		switch (_name)
		{
		case(20):
			new GoalBlock(_objectPos, objectSize, "Assets/box_03.gpmesh", goalBlock, SceneBase::tutorial);
			break;
		}
		break;

	case SceneBase::stage01:

		switch (_name)
		{
		case(20):
			new GoalBlock(_objectPos, objectSize, "Assets/box_10.gpmesh", goalBlock, SceneBase::stage01);
			break;
		}
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(20):
			new GoalBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", goalBlock, SceneBase::stage02);
			break;
		}
		break;
	}
}

/*
@fn	リスポーン地点のデータにアクセスする
*/
void MapCreate::AccessRespawnData()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRespawnMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(mOffset * ix, 0.0f, -mOffset * iz);

			CreateRespawn(name, objectPos);
		}
	}
}

/*
@fn	リスポーン地点を生成する
*/
void MapCreate::CreateRespawn(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100, 10, 100);

	switch (mScene)
	{
	case SceneBase::stage01:

		switch (_name)
		{
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
		break;

	case SceneBase::stage02:

		switch (_name)
		{
		case(21):
			new Respawn(_objectPos, objectSize, respawn01, SceneBase::stage02);
			break;

		case(22):
			new Respawn(_objectPos, objectSize, respawn02, SceneBase::stage02);
			break;

		case(23):
			new Respawn(_objectPos, objectSize, respawn03, SceneBase::stage02);
			break;
		}
		break;
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
