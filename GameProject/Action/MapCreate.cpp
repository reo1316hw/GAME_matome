/*
@brief	インクルード
*/
#include "MapCreate.h"
#include "Ground.h"
#include "Glass.h"
#include "Block.h"
#include "VerticalMoveGround.h"
#include "Jump.h"
#include "LateralMoveGround.h"
#include "Player.h"
#include "UpBlock.h"
#include "UpBlock_02.h"
#include "VerticalBlock.h"
#include "AerialBlock.h"
#include "RightBlock.h"
#include "LeftBlock.h"
#include "RightOneBlock.h"
#include "RightOneBlock_02.h"
#include "LeftOneBlock.h"
#include "LeftOneBlock_02.h"
#include "DownBlock.h"
#include "GoalBlock.h"
#include "Respawn.h"
#include "SceneBase.h"

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
	mUpBlock02MapData.clear();
	mVerticalBlockMapData.clear();
	mAerialBlockMapData.clear();
	mRightBlockMapData.clear();
	mLeftBlockMapData.clear();
	mRightOneBlockMapData.clear();
	mRightOneBlock02MapData.clear();
	mLeftOneBlockMapData.clear();
	mLeftOneBlock02MapData.clear();
	mDownBlockMapData.clear();
	mGoalBlockMapData.clear();
	mRespawn01MapData.clear();
	mRespawn02MapData.clear();
	mRespawn03MapData.clear();
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
		if (!readTiledJson(mRightOneBlockMapData, "Assets/Config/tutorial.json", "RightOneBlock"))
		{
			printf("don't have Layer/RightOneBlock\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(mLeftOneBlockMapData, "Assets/Config/tutorial.json", "LeftOneBlock"))
		{
			printf("don't have Layer/LeftOneBlock\n");
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

		//リスポーン地点01の読み込み
		if (!readTiledJson(mRespawn01MapData, "Assets/Config/RunMap.json", "Respawn01"))
		{
			printf("don't have Layer/Respawn01\n");
			return true;
		}

		//リスポーン地点02の読み込み
		if (!readTiledJson(mRespawn02MapData, "Assets/Config/RunMap.json", "Respawn02"))
		{
			printf("don't have Layer/Respawn02\n");
			return true;
		}

		//リスポーン地点03の読み込み
		if (!readTiledJson(mRespawn03MapData, "Assets/Config/RunMap.json", "Respawn03"))
		{
			printf("don't have Layer/Respawn03\n");
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
		if (!readTiledJson(mUpBlock02MapData, "Assets/Config/RunMap02.json", "UpBlock_02"))
		{
			printf("don't have Layer/UpBlock_02\n");
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
		if (!readTiledJson(mRightOneBlockMapData, "Assets/Config/RunMap02.json", "RightOneBlock"))
		{
			printf("don't have Layer/RightOneBlock\n");
			return true;
		}
		if (!readTiledJson(mRightOneBlock02MapData, "Assets/Config/RunMap02.json", "RightOneBlock_02"))
		{
			printf("don't have Layer/RightOneBlock_02\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(mLeftOneBlockMapData, "Assets/Config/RunMap02.json", "LeftOneBlock"))
		{
			printf("don't have Layer/LeftOneBlock\n");
			return true;
		}
		if (!readTiledJson(mLeftOneBlock02MapData, "Assets/Config/RunMap02.json", "LeftOneBlock_02"))
		{
			printf("don't have Layer/LeftOneBlock_02\n");
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

		//リスポーン地点01の読み込み
		if (!readTiledJson(mRespawn01MapData, "Assets/Config/RunMap02.json", "Respawn01"))
		{
			printf("don't have Layer/Respawn01\n");
			return true;
		}

		//リスポーン地点02の読み込み
		if (!readTiledJson(mRespawn02MapData, "Assets/Config/RunMap02.json", "Respawn02"))
		{
			printf("don't have Layer/Respawn02\n");
			return true;
		}

		//リスポーン地点03の読み込み
		if (!readTiledJson(mRespawn03MapData, "Assets/Config/RunMap02.json", "Respawn03"))
		{
			printf("don't have Layer/Respawn03\n");
			return true;
		}
	}

	return false;
}

/*
@fn	床を生成する
*/
void MapCreate::CreateGround()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix , 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	ガラス床を生成する
*/
void MapCreate::CreateGlass()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGlassMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					new Glass(objectPos, objectSize, glass, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(2):
					new Glass(objectPos, objectSize, glass,SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(2):
					new Glass(objectPos, objectSize, glass, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	障害物を生成する
*/
void MapCreate::CreateBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(3):
					new Block(objectPos, objectSize, block, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(3):
					new Block(objectPos, objectSize, block, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(3):
					new Block(objectPos, objectSize, block, SceneBase::stage02);
					break;
				}
				break;
			}

		}
	}
}

/*
@fn	縦移動床を生成する
*/
void MapCreate::CreateVerticalMoveGround()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mVerticalMoveGroundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(4):
					new VerticalMoveGround(objectPos, objectSize, verticalMoveGround, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(4):
					new VerticalMoveGround(objectPos, objectSize, verticalMoveGround, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(4):
					new VerticalMoveGround(objectPos, objectSize, verticalMoveGround, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	ジャンプ中を生成する
*/
void MapCreate::CreateJump()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mJumpMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			/*Vector3 tutorialObjectSize = Vector3(100, 10, 150);*/
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(5):
					new Jump(objectPos, objectSize, jump, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(5):
					new Jump(objectPos, objectSize, jump, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(5):
					new Jump(objectPos, objectSize, jump, SceneBase::stage02);
					break;
				}
				break;
			}

		}
	}
}

/*
@fn	横移動床を生成する
*/
void MapCreate::CreateLateralMoveGround()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLateralMoveGroundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(6):
					new LateralMoveGround(objectPos, objectSize, lateralMoveGround, SceneBase::tutorial,1000.0f);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(6):
					new LateralMoveGround(objectPos, objectSize, lateralMoveGround, SceneBase::stage01 ,1000.0f);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(6):
					new LateralMoveGround(objectPos, objectSize, lateralMoveGround, SceneBase::stage02, 1000.0f);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	プレイヤーを生成する
*/
void MapCreate::CreatePlayer()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);
			Vector3 objectSize = Vector3(1.2f, 1.2f, 1.2f);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(7):
					new Player(objectPos, objectSize, player, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(7):
					new Player(objectPos, objectSize, player, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(7):
					new Player(objectPos, objectSize, player, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}

}

/*
@fn	上移動ブロックを生成する
*/
void MapCreate::CreateUpBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mUpBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, -100, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(8):
					new UpBlock(objectPos, objectSize, upBlock, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(8):
					new UpBlock(objectPos, objectSize, upBlock, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	上移動ブロックを生成する
*/
void MapCreate::CreateUpBlock_02()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mUpBlock02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(17):
					new UpBlock_02(objectPos, objectSize, upBlock_02, SceneBase::stage02);
					break;
				}
			}

		}
	}
}

/*
@fn	縦長障害物を生成する
*/
void MapCreate::CreateVerticalBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (int iy = 0; iy < 2; iy++)
		{
			for (float ix = 0; ix < mSizeX; ix++)
			{
				const unsigned int name = mVerticalBlockMapData[(int)iz][(int)ix];
				Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy + 100, -mOffset * iz);
				Vector3 objectSize = Vector3(70, 100, 100);
				if (mScene == SceneBase::stage02)
				{
					switch (name)
					{
					case(9):
						new VerticalBlock(objectPos, objectSize, verticalBlock, SceneBase::stage02);
						break;
					}
				}

			}
		}
	}
}

/*
@fn	空中ブロックを生成する
*/
void MapCreate::CreateAerialBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mAerialBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 100, 100);
			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(10):
					new AerialBlock(objectPos, objectSize, aerialBlock, SceneBase::stage02);
					break;
				}
			}

		}
	}
}

/*
@fn	右移動ブロックを生成する
*/
void MapCreate::CreateRightBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRightBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix , 70, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(11):
					new RightBlock(objectPos, objectSize, rightBlock, SceneBase::stage02);
					break;
				}
			}

		}
	}
}

/*
@fn	左移動ブロックを生成する
*/
void MapCreate::CreateLeftBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLeftBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 70 , -mOffset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(13):
					new LeftBlock(objectPos, objectSize, leftBlock, SceneBase::stage02);
					break;
				}
			}
		}
	}
}

/*
@fn	1マス右移動床を生成する
*/
void MapCreate::CreateRightOneBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRightOneBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(15):
					new RightOneBlock(objectPos, objectSize, rightOneBlock, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(15):
					new RightOneBlock(objectPos, objectSize, rightOneBlock, SceneBase::stage02);
					break;
				}
				break;
			}

		}
	}
}

/*
@fn	1マス右移動床を生成する
*/
void MapCreate::CreateRightOneBlock_02()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRightOneBlock02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);

			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(18):
					new RightOneBlock_02(objectPos, objectSize, rightOneBlock_02, SceneBase::stage02);
					break;
				}
			}

		}
	}
}

/*
@fn	1マス左移動床を生成する
*/
void MapCreate::CreateLeftOneBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLeftOneBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(14):
					new LeftOneBlock(objectPos, objectSize, leftOneBlock, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(14):
					new LeftOneBlock(objectPos, objectSize, leftOneBlock, SceneBase::stage02);
					break;
				}
				break;
			}

		}
	}
}

/*
@fn	1マス左移動床を生成する
*/
void MapCreate::CreateLeftOneBlock_02()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mLeftOneBlock02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(19):
					new LeftOneBlock_02(objectPos, objectSize, leftOneBlock_02, SceneBase::stage02);
					break;
				default:
					break;
				}
			}

		}
	}
}

/*
@fn	落下ブロックを生成する
*/
void MapCreate::CreateDownBlock()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mDownBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 1600, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);
			if (mScene == SceneBase::stage02)
			{
				switch (name)
				{
				case(16):
					new DownBlock(objectPos, objectSize, downBlock, SceneBase::stage02);
					break;
				default:
					break;
				}
			}

		}
	}
}

/*
@fn	ゴール柱を生成する
*/
void MapCreate::CreateGoal()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			for (float ix = 0; ix < mSizeX; ix++)
			{
				const unsigned int name = mGoalBlockMapData[(int)iz][(int)ix];
				Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);
				Vector3 objectSize = Vector3(100, 100, 100);

				switch (mScene)
				{
				case SceneBase::tutorial:

					switch (name)
					{
					case(20):
						new GoalBlock(objectPos, objectSize, goalBlock, SceneBase::tutorial);
						break;
					}
					break;

				case SceneBase::stage01:

					switch (name)
					{
					case(20):
						new GoalBlock(objectPos, objectSize, goalBlock, SceneBase::stage01);
						break;
					}
					break;

				case SceneBase::stage02:

					switch (name)
					{
					case(20):
						new GoalBlock(objectPos, objectSize, goalBlock, SceneBase::stage02);
						break;
					}
					break;
				}
			}

		}
	}
}

/*
@fn	リスポーン地点を生成する
*/
void MapCreate::CreateRespawn01()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRespawn01MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0.0f, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::stage01:

				switch (name)
				{
				case(21):
					new Respawn(objectPos, objectSize, respawn01, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(21):
					new Respawn(objectPos, objectSize, respawn01, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	リスポーン地点を生成する
*/
void MapCreate::CreateRespawn02()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRespawn02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0.0f, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::stage01:

				switch (name)
				{
				case(22):
					new Respawn(objectPos, objectSize, respawn02, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(22):
					new Respawn(objectPos, objectSize, respawn02, SceneBase::stage02);
					break;
				}
				break;
			}
		}
	}
}

/*
@fn	リスポーン地点を生成する
*/
void MapCreate::CreateRespawn03()
{
	for (float iz = 0; iz < mSizeZ; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mRespawn03MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(mOffset * ix, 0.0f, -mOffset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (mScene)
			{
			case SceneBase::stage01:

				switch (name)
				{
				case(23):
					new Respawn(objectPos, objectSize, respawn03, SceneBase::stage01);
					break;
				}
				break;

			case SceneBase::stage02:

				switch (name)
				{
				case(23):
					new Respawn(objectPos, objectSize, respawn03, SceneBase::stage02);
					break;
				}
				break;
			}
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
