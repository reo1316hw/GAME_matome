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

MapCreate::MapCreate() :GameObject(SceneBase::other,Tag::Other)
{
	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
	offset = 200;
}

MapCreate::~MapCreate()
{
	groundMapData.clear();
	glassMapData.clear();
	blockMapData.clear();
	verticalMoveGroundMapData.clear();
	jumpMapData.clear();
	lateralMoveGroundMapData.clear();
	playerMapData.clear();
	upBlockMapData.clear();
	upBlock_02MapData.clear();
	verticalBlockMapData.clear();
	aerialBlockMapData.clear();
	rightBlockMapData.clear();
	leftBlockMapData.clear();
	rightOneBlockMapData.clear();
	rightOneBlock_02MapData.clear();
	leftOneBlockMapData.clear();
	leftOneBlock_02MapData.clear();
	downBlockMapData.clear();
	goalBlockMapData.clear();
	respawn01MapData.clear();
	respawn02MapData.clear();
	respawn03MapData.clear();
}

bool MapCreate::OpenFile()
{
	scene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------
	
	if (scene == SceneBase::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(groundMapData, "Assets/Config/tutorial.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		sizeX = groundMapData[0].size();
		sizeZ = groundMapData.size();
		sizeY = groundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(glassMapData, "Assets/Config/tutorial.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(blockMapData, "Assets/Config/tutorial.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(verticalMoveGroundMapData, "Assets/Config/tutorial.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(jumpMapData, "Assets/Config/tutorial.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(lateralMoveGroundMapData, "Assets/Config/tutorial.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(playerMapData, "Assets/Config/tutorial.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//上移動ブロックの読み込み
		if (!readTiledJson(upBlockMapData, "Assets/Config/tutorial.json", "UpBlock"))
		{
			printf("don't have Layer/UpBlock\n");
			return true;
		}

		//1マス右移動床の読み込み
		if (!readTiledJson(rightOneBlockMapData, "Assets/Config/tutorial.json", "RightOneBlock"))
		{
			printf("don't have Layer/RightOneBlock\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(leftOneBlockMapData, "Assets/Config/tutorial.json", "LeftOneBlock"))
		{
			printf("don't have Layer/LeftOneBlock\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(goalBlockMapData, "Assets/Config/tutorial.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

	}
	

	//-----------------------------------------------
	//----------------stage01------------------------
	//-----------------------------------------------
	
	if (scene == SceneBase::stage01)
	{
		//床データの読み込み
		if (!readTiledJson(groundMapData, "Assets/Config/RunMap.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		sizeX = groundMapData[0].size();
		sizeZ = groundMapData.size();
		sizeY = groundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(glassMapData, "Assets/Config/RunMap.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(blockMapData, "Assets/Config/RunMap.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(verticalMoveGroundMapData, "Assets/Config/RunMap.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(jumpMapData, "Assets/Config/RunMap.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(lateralMoveGroundMapData, "Assets/Config/RunMap.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(playerMapData, "Assets/Config/RunMap.json", "player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(goalBlockMapData, "Assets/Config/RunMap.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

		//リスポーン地点01の読み込み
		if (!readTiledJson(respawn01MapData, "Assets/Config/RunMap.json", "Respawn01"))
		{
			printf("don't have Layer/Respawn01\n");
			return true;
		}

		//リスポーン地点02の読み込み
		if (!readTiledJson(respawn02MapData, "Assets/Config/RunMap.json", "Respawn02"))
		{
			printf("don't have Layer/Respawn02\n");
			return true;
		}

		//リスポーン地点03の読み込み
		if (!readTiledJson(respawn03MapData, "Assets/Config/RunMap.json", "Respawn03"))
		{
			printf("don't have Layer/Respawn03\n");
			return true;
		}
	}

	//--------------------------------------------------------------
	//------------------------stage02-------------------------------
	//--------------------------------------------------------------
	
	if (scene == SceneBase::stage02)
	{
		//床データの読み込み
		if (!readTiledJson(groundMapData, "Assets/Config/RunMap02.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		sizeX = groundMapData[0].size();
		sizeZ = groundMapData.size();
		sizeY = groundMapData[0].size();

		//ガラス床データの読み込み
		if (!readTiledJson(glassMapData, "Assets/Config/RunMap02.json", "Glass"))
		{
			printf("don't have Layer/Glass\n");
			return true;
		}

		//障害物データの読み込み
		if (!readTiledJson(blockMapData, "Assets/Config/RunMap02.json", "Block"))
		{
			printf("don't have Layer/Block\n");
			return true;
		}

		//縦移動床データの読み込み
		if (!readTiledJson(verticalMoveGroundMapData, "Assets/Config/RunMap02.json", "VerticalMoveGround"))
		{
			printf("don't have Layer/VerticalMoveGround\n");
			return true;
		}

		//ジャンプ床データの読み込み
		if (!readTiledJson(jumpMapData, "Assets/Config/RunMap02.json", "Jump"))
		{
			printf("don't have Layer/Jump\n");
			return true;
		}

		//横移動床データの読み込み
		if (!readTiledJson(lateralMoveGroundMapData, "Assets/Config/RunMap02.json", "LateralMoveGround"))
		{
			printf("don't have Layer/LateralMoveGround\n");
			return true;
		}

		//上移動ブロックの読み込み
		if (!readTiledJson(upBlockMapData, "Assets/Config/RunMap02.json", "UpBlock"))
		{
			printf("don't have Layer/UpBlock\n");
			return true;
		}
		if (!readTiledJson(upBlock_02MapData, "Assets/Config/RunMap02.json", "UpBlock_02"))
		{
			printf("don't have Layer/UpBlock_02\n");
			return true;
		}

		//縦長障害物の読み込み
		if (!readTiledJson(verticalBlockMapData, "Assets/Config/RunMap02.json", "VerticalBlock"))
		{
			printf("don't have Layer/VerticalBlock\n");
			return true;
		}

		//空中ブロックの読み込み
		if (!readTiledJson(aerialBlockMapData, "Assets/Config/RunMap02.json", "AerialBlock"))
		{
			printf("don't have Layer/AerialBlock\n");
			return true;
		}

		//右移動ブロックの読み込み
		if (!readTiledJson(rightBlockMapData, "Assets/Config/RunMap02.json", "RightBlock"))
		{
			printf("don't have Layer/RightBlock\n");
			return true;
		}

		//左移動ブロックの読み込み
		if (!readTiledJson(leftBlockMapData, "Assets/Config/RunMap02.json", "LeftBlock"))
		{
			printf("don't have Layer/LeftBlock\n");
			return true;
		}

		//1マス右移動床の読み込み
		if (!readTiledJson(rightOneBlockMapData, "Assets/Config/RunMap02.json", "RightOneBlock"))
		{
			printf("don't have Layer/RightOneBlock\n");
			return true;
		}
		if (!readTiledJson(rightOneBlock_02MapData, "Assets/Config/RunMap02.json", "RightOneBlock_02"))
		{
			printf("don't have Layer/RightOneBlock_02\n");
			return true;
		}

		//1マス左移動床の読み込み
		if (!readTiledJson(leftOneBlockMapData, "Assets/Config/RunMap02.json", "LeftOneBlock"))
		{
			printf("don't have Layer/LeftOneBlock\n");
			return true;
		}
		if (!readTiledJson(leftOneBlock_02MapData, "Assets/Config/RunMap02.json", "LeftOneBlock_02"))
		{
			printf("don't have Layer/LeftOneBlock_02\n");
			return true;
		}

		//落ちるブロックデータの読み込み
		if (!readTiledJson(downBlockMapData, "Assets/Config/RunMap02.json", "DownBlock"))
		{
			printf("don't have Layer/DownBlock\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(playerMapData, "Assets/Config/RunMap02.json", "Player"))
		{
			printf("don't have Layer/Player\n");
			return true;
		}

		//ゴール柱の読み込み
		if (!readTiledJson(goalBlockMapData, "Assets/Config/RunMap02.json", "Goal"))
		{
			printf("don't have Layer/Goal\n");
			return true;
		}

		//リスポーン地点01の読み込み
		if (!readTiledJson(respawn01MapData, "Assets/Config/RunMap02.json", "Respawn01"))
		{
			printf("don't have Layer/Respawn01\n");
			return true;
		}

		//リスポーン地点02の読み込み
		if (!readTiledJson(respawn02MapData, "Assets/Config/RunMap02.json", "Respawn02"))
		{
			printf("don't have Layer/Respawn02\n");
			return true;
		}

		//リスポーン地点03の読み込み
		if (!readTiledJson(respawn03MapData, "Assets/Config/RunMap02.json", "Respawn03"))
		{
			printf("don't have Layer/Respawn03\n");
			return true;
		}
	}

	return false;
}

void MapCreate::CreateGround()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = groundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix , 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateGlass()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = glassMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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


void MapCreate::CreateBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = blockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 100, -offset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			switch (scene)
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

void MapCreate::CreateVerticalMoveGround()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = verticalMoveGroundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateJump()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = jumpMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			/*Vector3 tutorialObjectSize = Vector3(100, 10, 150);*/
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateLateralMoveGround()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = lateralMoveGroundMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreatePlayer()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = playerMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 500, -offset * iz);
			Vector3 objectSize = Vector3(1.2f, 1.2f, 1.2f);

			switch (scene)
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

void MapCreate::CreateUpBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = upBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, -100, -offset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			switch (scene)
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

void MapCreate::CreateUpBlock_02()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = upBlock_02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 100, -offset * iz);
			Vector3 objectSize = Vector3(70, 100, 100);

			if (scene == SceneBase::stage02)
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

void MapCreate::CreateVerticalBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (int iy = 0; iy < 2; iy++)
		{
			for (float ix = 0; ix < sizeX; ix++)
			{
				const unsigned int name = verticalBlockMapData[(int)iz][(int)ix];
				Vector3 objectPos = Vector3(offset * ix, offset * iy + 100, -offset * iz);
				Vector3 objectSize = Vector3(70, 100, 100);
				if (scene == SceneBase::stage02)
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

void MapCreate::CreateAerialBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = aerialBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 500, -offset * iz);
			Vector3 objectSize = Vector3(100, 100, 100);
			if (scene == SceneBase::stage02)
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

void MapCreate::CreateRightBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = rightBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix , 70, -offset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (scene == SceneBase::stage02)
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

void MapCreate::CreateLeftBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = leftBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 70 , -offset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (scene == SceneBase::stage02)
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

void MapCreate::CreateRightOneBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = rightOneBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateRightOneBlock_02()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = rightOneBlock_02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 100, -offset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);

			if (scene == SceneBase::stage02)
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

void MapCreate::CreateLeftOneBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = leftOneBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateLeftOneBlock_02()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = leftOneBlock_02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 100, -offset * iz);
			Vector3 objectSize = Vector3(70, 70, 100);
			if (scene == SceneBase::stage02)
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

void MapCreate::CreateDownBlock()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = downBlockMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 1600, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);
			if (scene == SceneBase::stage02)
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

void MapCreate::CreateGoal()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			for (float ix = 0; ix < sizeX; ix++)
			{
				const unsigned int name = goalBlockMapData[(int)iz][(int)ix];
				Vector3 objectPos = Vector3(offset * ix, offset * iy, -offset * iz);
				Vector3 objectSize = Vector3(100, 100, 100);

				switch (scene)
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

void MapCreate::CreateRespawn01()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = respawn01MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0.0f, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateRespawn02()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = respawn02MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0.0f, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

void MapCreate::CreateRespawn03()
{
	for (float iz = 0; iz < sizeZ; iz++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = respawn03MapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, 0.0f, -offset * iz);
			Vector3 objectSize = Vector3(100, 10, 100);

			switch (scene)
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

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc,fileName))
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
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	mapData.resize(height);
	for (auto&mapIter:mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

int MapCreate::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName)
{
	int layerSize = layer.Size();
	int i;
	std::string layerNameString(layerName);
	for ( i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = layer[i]["name"].GetString();
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
