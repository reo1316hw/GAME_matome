/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MapCreate::MapCreate() :GameObject(SceneBase::other,Tag::Other)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
	mOffset = 200;
}

/*
@fn	�f�X�g���N�^
*/
MapCreate::~MapCreate()
{
	mLowerMapData.clear();
	mUpperMapData.clear();
}

/*
@fn	    �`���[�g���A����json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return �v���C���[�̃|�C���^
*/
Player* MapCreate::OpenTutorialFile()
{
	mScene = SceneBase::GetScene();

	//int readCount = 0;

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/tutorialFix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/tutorialFix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/tutorialFix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

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
@fn		�X�e�[�W1��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return �v���C���[�̃|�C���^
*/
Player* MapCreate::OpenStage01File()
{
	mScene = SceneBase::GetScene();

	//int readCount = 0;

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage01Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage01Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage01Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

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
@fn	  �X�e�[�W2��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return �v���C���[�̃|�C���^
*/
Player* MapCreate::OpenStage02File()
{
	mScene = SceneBase::GetScene();

	//int readCount = 0;

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage02Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	mSizeX = mLowerMapData[0].size();
	mSizeZ = mLowerMapData.size();
	mSizeY = mLowerMapData[0].size();

	//readCount++;

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage02Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	//readCount++;

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage02Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	//readCount++;

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/stage02Fix.json", "VerticalBlock"))
	{
		printf("don't have Layer/VerticalBlock\n");
	}

	//readCount++;

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpBlockMapData, "Assets/Config/stage02Fix.json", "UpBlock"))
	{
		printf("don't have Layer/UpBlock\n");
	}

	AccessStage01MapData(mLowerMapData, 1);
	AccessStage01MapData(mUpperMapData, 1);
	AccessStage01MapData(mUpBlockMapData, 1);
	AccessStage01MapData(mVerticalBlockMapData, 2);
	AccessStage01MapData(mGoalBlockMapData, 10);

	/*readCount++;

	for (int i = 0; i < readCount; i++)
	{
		AccessMapData();
	}*/

	return mPlayer;
}

/*
@fn	   �`���[�g���A���̃}�b�v�f�[�^�ɃA�N�Z�X����
@param _mapData �}�b�v�f�[�^
@param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
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
@fn	   �X�e�[�W1�̃}�b�v�f�[�^�ɃA�N�Z�X����
@param _mapData �}�b�v�f�[�^
@param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
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
@fn	   �X�e�[�W2�̃}�b�v�f�[�^�ɃA�N�Z�X����
@param _mapData �}�b�v�f�[�^
@param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
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
@fn    �`���[�g���A���̃I�u�W�F�N�g�𐶐�����
@param _name �}�b�v�f�[�^�̗v�f
@param _objectPos �I�u�W�F�N�g�̍��W
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
        	new Glass(_objectPos, objectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial);
        	break;
        case(3):
        {
        	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
        	const Vector3 blockPos = _objectPos + addPos;
        
        	new Block(blockPos, obstacleSize, "Assets/box_03.gpmesh", block, SceneBase::tutorial);
        	break;
        }
        case(4):
        	new VerticalMoveGround(_objectPos, objectSize, "Assets/box_04.gpmesh", verticalMoveGround, SceneBase::tutorial);
        	break;
        case(5):
        	new Jump(_objectPos, objectSize, "Assets/box_05.gpmesh", jump, SceneBase::tutorial);
        	break;
        case(6):
        	new LateralMoveGround(_objectPos, objectSize, "Assets/box.gpmesh", lateralMoveGround, SceneBase::tutorial, 1000.0f);
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
        
        	new UpBlock(upBlockPos, obstacleSize, "Assets/box_03.gpmesh", upBlock, SceneBase::tutorial);
        	break;
        }
        case(14):
        	new LeftGround(_objectPos, objectSize, "Assets/box_07.gpmesh", leftGround, SceneBase::tutorial);
        	break;
        case(15):
        	new RightGround(_objectPos, objectSize, "Assets/box_06.gpmesh", rightGround, SceneBase::tutorial);
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
@fn    �X�e�[�W1�̃I�u�W�F�N�g�𐶐�����
@param _name �}�b�v�f�[�^�̗v�f
@param _objectPos �I�u�W�F�N�g�̍��W
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
			new Glass(_objectPos, objectSize, "Assets/box_09.gpmesh", glass,SceneBase::stage01);
			break;
	    case(3):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 blockPos = _objectPos + addPos;
	    
			new Block(blockPos, obstacleSize, "Assets/box_10.gpmesh", block, SceneBase::stage01);
			break;
	    }
	    case(4):
		    new VerticalMoveGround(_objectPos, objectSize, "Assets/box_11.gpmesh", verticalMoveGround, SceneBase::stage01);
			break;
	    case(5):
			new Jump(_objectPos, objectSize, "Assets/box_12.gpmesh", jump, SceneBase::stage01);
			break;
		case(6):
			new LateralMoveGround(_objectPos, objectSize, "Assets/box_08.gpmesh", lateralMoveGround, SceneBase::stage01 ,1000.0f);
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
	}
}

/*
@fn    �X�e�[�W2�̃I�u�W�F�N�g�𐶐�����
@param _name �}�b�v�f�[�^�̗v�f
@param _objectPos �I�u�W�F�N�g�̍��W
*/
void MapCreate::CreateStage02Object(const unsigned int _name, const Vector3 _objectPos)
{
	const Vector3 objectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 obstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_name)
	{
	    case(1):
	    	new Ground(_objectPos, objectSize, "Assets/box_13.gpmesh", ground, SceneBase::stage02);
	    	break;
	    case(2):
	    	new Glass(_objectPos, objectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02);
	    	break;
	    case(3):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 blockPos = _objectPos + addPos;
	    
	    	new Block(blockPos, obstacleSize, "Assets/box_15.gpmesh", block, SceneBase::stage02);
	    	break;
	    }
	    case(4):
	    	new VerticalMoveGround(_objectPos, objectSize, "Assets/box_16.gpmesh", verticalMoveGround, SceneBase::stage02);
	    	break;
	    case(5):
	    	new Jump(_objectPos, objectSize, "Assets/box_17.gpmesh", jump, SceneBase::stage02);
	    	break;
	    case(6):
	    	new LateralMoveGround(_objectPos, objectSize, "Assets/box_13.gpmesh", lateralMoveGround, SceneBase::stage02, 1000.0f);
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
	    
	    	new UpBlock(upBlockPos, obstacleSize, "Assets/box_15.gpmesh", upBlock, SceneBase::stage02);
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
	    
	    	new AerialBlock(aerialBlockPos, obstacleSize, "Assets/box_15.gpmesh", aerialBlock, SceneBase::stage02);
	    	break;
	    }
		case(11):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 rightBlockPos = _objectPos + addPos;
			const float addEndPosX = 600.0f;

			new RightBlock(rightBlockPos, obstacleSize, addEndPosX, "Assets/box_15.gpmesh", rightBlock, ColliderTag::rightBlockTag, SceneBase::stage02);
			break;
		}
		case(13):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 leftBlockPos = _objectPos + addPos;
			const float addEndPos = 600.0f;

			new LeftBlock(leftBlockPos, obstacleSize, addEndPos, "Assets/box_15.gpmesh", leftBlock, ColliderTag::leftBlockTag, SceneBase::stage02);
			break;
		}
		case(14):
			new LeftGround(_objectPos, objectSize, "Assets/box_19.gpmesh", leftGround, SceneBase::stage02);
			break;
		case(15):
			new RightGround(_objectPos, objectSize, "Assets/box_18.gpmesh", rightGround, SceneBase::stage02);
			break;
		case(16):
		{
			const Vector3 addPos = Vector3(0.0f, 1600.0f, 0.0f);
			const Vector3 downBlockPos = _objectPos + addPos;

			new DownBlock(downBlockPos, obstacleSize, "Assets/box_13.gpmesh", downBlock, SceneBase::stage02);
			break;
		}
	    case(17):
	    {
	    	const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 upBlockPos = _objectPos + addPos;
	    
	    	new UpBlock(upBlockPos, obstacleSize, "Assets/box_15.gpmesh", upBlock_02, SceneBase::stage02);
	    	break;
	    }
	    case(20):
	    {
	    	const Vector3 goalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
			new GoalBlock(_objectPos, goalBlockSize, "Assets/box_15.gpmesh", goalBlock, SceneBase::stage02);
			break;
	    }
		case(418):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 rightBlockPos = _objectPos + addPos;
			const float addEndPos = 200.0f;

			new RightBlock(rightBlockPos, obstacleSize, addEndPos, "Assets/box_15.gpmesh", rightOneMoveBlock, ColliderTag::rightOneMoveBlockTag, SceneBase::stage02);
			break;
		}
		case(419):
		{
			const Vector3 addPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 leftBlockPos = _objectPos + addPos;
			const float addEndPos = 200.0f;

			new LeftBlock(leftBlockPos, obstacleSize, addEndPos, "Assets/box_15.gpmesh", leftOneMoveBlock, ColliderTag::leftOneMoveBlockTag, SceneBase::stage02);
			break;
		}
	}
}

///*
//@fn	�K���X���̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessGlassData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mGlassMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateGlass(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	�K���X���𐶐�����
//*/
//void MapCreate::CreateGlass(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(2):
//			new Glass(_objectPos, objectSize, "Assets/box_02.gpmesh", glass, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(2):
//			new Glass(_objectPos, objectSize, "Assets/box_09.gpmesh", glass,SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(2):
//			new Glass(_objectPos, objectSize, "Assets/box_14.gpmesh", glass, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	��Q���̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 100, -mOffset * iz);
//
//			CreateBlock(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	��Q���𐶐�����
//*/
//void MapCreate::CreateBlock(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(70, 100, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(3):
//			new Block(_objectPos, objectSize, "Assets/box_03.gpmesh", block, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(3):
//			new Block(_objectPos, objectSize, "Assets/box_10.gpmesh", block, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(3):
//			new Block(_objectPos, objectSize, "Assets/box_15.gpmesh", block, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	�c�ړ����̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessVerticalMoveGroundData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mVerticalMoveGroundMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateVerticalMoveGround(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	�c�ړ����𐶐�����
//*/
//void MapCreate::CreateVerticalMoveGround(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(4):
//			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_04.gpmesh", verticalMoveGround, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(4):
//			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_11.gpmesh", verticalMoveGround, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(4):
//			new VerticalMoveGround(_objectPos, objectSize, "Assets/box_16.gpmesh", verticalMoveGround, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	�W�����v���̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessJumpData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mJumpMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateJump(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	�W�����v���𐶐�����
//*/
//void MapCreate::CreateJump(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(5):
//			new Jump(_objectPos, objectSize, "Assets/box_05.gpmesh", jump, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(5):
//			new Jump(_objectPos, objectSize, "Assets/box_12.gpmesh", jump, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(5):
//			new Jump(_objectPos, objectSize, "Assets/box_17.gpmesh", jump, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	���ړ����̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessLateralMoveGroundData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mLateralMoveGroundMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateLateralMoveGround(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	���ړ����𐶐�����
//*/
//void MapCreate::CreateLateralMoveGround(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(6):
//			new LateralMoveGround(_objectPos, objectSize, "Assets/box.gpmesh", lateralMoveGround, SceneBase::tutorial,1000.0f);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(6):
//			new LateralMoveGround(_objectPos, objectSize, "Assets/box_08.gpmesh", lateralMoveGround, SceneBase::stage01 ,1000.0f);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(6):
//			new LateralMoveGround(_objectPos, objectSize, "Assets/box_13.gpmesh" ,lateralMoveGround, SceneBase::stage02, 1000.0f);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	    �v���C���[�̃f�[�^�ɃA�N�Z�X����
//@return �v���C���[�N���X�̃|�C���^
//*/
//Player* MapCreate::AccessPlayerData()
//{
//	// �v���C���[�̃|�C���^
//	Player* playerPtr = nullptr;
//
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);
//
//			playerPtr = CreatePlayer(name, objectPos, playerPtr);
//		}
//	}
//
//	return playerPtr;
//}
//
///*
//@fn	�v���C���[�𐶐�����
//@return �v���C���[�N���X�̃|�C���^
//*/
//Player* MapCreate::CreatePlayer(const unsigned int _name, const Vector3 _objectPos, Player* _playerPtr)
//{
//	const Vector3 objectSize = Vector3(1.2f, 1.2f, 1.2f);
//	
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(7):
//			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(7):
//			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(7):
//			_playerPtr = new Player(_objectPos, objectSize, "Assets/Sphere.gpmesh", player, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//
//	return _playerPtr;
//}
//
///*
//@fn	��ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessUpBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mUpBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, -100, -mOffset * iz);
//			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);
//
//			CreateUpBlock(name, objectPos, objectPos2);
//		}
//	}
//}
//
///*
//@fn	��ړ��u���b�N�𐶐�����
//*/
//void MapCreate::CreateUpBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
//{
//	const Vector3 objectSize = Vector3(70, 100, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(8):
//			new UpBlock(_objectPos, objectSize, "Assets/box_03.gpmesh" ,upBlock, SceneBase::tutorial);
//			break;
//		}
//
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(8):
//			new UpBlock(_objectPos, objectSize, "Assets/box_15.gpmesh" ,upBlock, SceneBase::stage02);
//			break;
//
//		case(17):
//			new UpBlock(_objectPos2, objectSize, "Assets/box_15.gpmesh", upBlock_02, SceneBase::stage02);
//			break;
//		}
//
//		break;
//	}
//}
//
///*
//@fn	�c����Q���̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessVerticalBlockData()
//{
//	const int verticalBlockNumY = 2;
//
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (int iy = 0; iy < verticalBlockNumY; iy++)
//		{
//			for (float ix = 0; ix < mSizeX; ix++)
//			{
//				const unsigned int name = mVerticalBlockMapData[(int)iz][(int)ix];
//				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy + 100, -mOffset * iz);
//
//				CreateVerticalBlock(name, objectPos);
//			}
//		}
//	}
//}
//
///*
//@fn	�c����Q���𐶐�����
//*/
//void MapCreate::CreateVerticalBlock(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(70, 100, 100);
//
//	if (mScene == SceneBase::stage02)
//	{
//		switch (_name)
//		{
//		case(9):
//			new VerticalBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", verticalBlock, SceneBase::stage02);
//			break;
//		}
//	}
//}
//
///*
//@fn	�󒆃u���b�N�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessAerialBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mAerialBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 500, -mOffset * iz);
//
//			CreateAerialBlock(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	�󒆃u���b�N�𐶐�����
//*/
//void MapCreate::CreateAerialBlock(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 100, 100);
//
//	if (mScene == SceneBase::stage02)
//	{
//		switch (_name)
//		{
//		case(10):
//			new AerialBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", aerialBlock, SceneBase::stage02);
//			break;
//		}
//	}
//}
//
///*
//@fn	�E�ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessRightBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mRightBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 70, -mOffset * iz);
//			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);
//
//			CreateRightBlock(name, objectPos, objectPos2);
//		}
//	}
//}
//
///*
//@fn	�E�ړ��u���b�N�𐶐�����
//*/
//void MapCreate::CreateRightBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
//{
//	const Vector3 objectSize = Vector3(70, 70, 100);
//	const float addPosX = 600.0f;
//	const float addPosX2 = 200.0f;
//
//	if (mScene == SceneBase::stage02)
//	{
//		switch (_name)
//		{
//		case(11):
//			new RightBlock(_objectPos, objectSize, addPosX, "Assets/box_15.gpmesh", rightBlock, ColliderTag::rightBlockTag, SceneBase::stage02);
//			break;
//
//		case(418):
//			new RightBlock(_objectPos2, objectSize, addPosX2, "Assets/box_15.gpmesh", rightOneMoveBlock, ColliderTag::rightOneMoveBlockTag, SceneBase::stage02);
//			break;
//		}
//	}
//}
//
///*
//@fn	���ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessLeftBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mLeftBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 70, -mOffset * iz);
//			const Vector3 objectPos2 = Vector3(mOffset * ix, 100, -mOffset * iz);
//
//			CreateLeftBlock(name, objectPos, objectPos2);
//		}
//	}
//}
//
///*
//@fn	���ړ��u���b�N�𐶐�����
//*/
//void MapCreate::CreateLeftBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2)
//{
//	const Vector3 objectSize = Vector3(70, 70, 100);
//	const float addPosX = 600.0f;
//	const float addPosX2 = 200.0f;
//
//	if (mScene == SceneBase::stage02)
//	{
//		switch (_name)
//		{
//		case(13):
//			new LeftBlock(_objectPos, objectSize, addPosX, "Assets/box_15.gpmesh", leftBlock, ColliderTag::leftBlockTag, SceneBase::stage02);
//			break;
//
//		case(419):
//			new LeftBlock(_objectPos2, objectSize, addPosX2, "Assets/box_15.gpmesh", leftOneMoveBlock, ColliderTag::leftOneMoveBlockTag, SceneBase::stage02);
//			break;
//		}
//	}
//}
//
///*
//@fn	1�}�X�E�ړ����̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessRightGroundData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mRightGroundMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateRightGround(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	1�}�X�E�ړ����𐶐�����
//*/
//void MapCreate::CreateRightGround(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(15):
//			new RightGround(_objectPos, objectSize, "Assets/box_06.gpmesh", rightGround, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(15):
//			new RightGround(_objectPos, objectSize, "Assets/box_18.gpmesh", rightGround, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	1�}�X���ړ����̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessLeftGroundData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mLeftGroundMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0, -mOffset * iz);
//
//			CreateLeftGround(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	1�}�X���ړ����𐶐�����
//*/
//void MapCreate::CreateLeftGround(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(14):
//			new LeftGround(_objectPos, objectSize, "Assets/box_07.gpmesh", leftGround, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(14):
//			new LeftGround(_objectPos, objectSize, "Assets/box_19.gpmesh", leftGround, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	�����u���b�N�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessDownBlockData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mDownBlockMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 1600, -mOffset * iz);
//
//			CreateDownBlock(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	�����u���b�N�𐶐�����
//*/
//void MapCreate::CreateDownBlock(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	if (mScene == SceneBase::stage02)
//	{
//		switch (_name)
//		{
//		case(16):
//			new DownBlock(_objectPos, objectSize, "Assets/box_13.gpmesh", downBlock, SceneBase::stage02);
//			break;
//		default:
//			break;
//		}
//	}
//}
//
///*
//@fn	�S�[�����̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessGoalData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float iy = 0; iy < mSizeY; iy++)
//		{
//			for (float ix = 0; ix < mSizeX; ix++)
//			{
//				const unsigned int name = mGoalBlockMapData[(int)iz][(int)ix];
//				const Vector3 objectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);
//
//				CreateGoal(name, objectPos);
//			}
//		}
//	}
//}
//
///*
//@fn	�S�[�����𐶐�����
//*/
//void MapCreate::CreateGoal(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 100, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::tutorial:
//
//		switch (_name)
//		{
//		case(20):
//			new GoalBlock(_objectPos, objectSize, "Assets/box_03.gpmesh", goalBlock, SceneBase::tutorial);
//			break;
//		}
//		break;
//
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(20):
//			new GoalBlock(_objectPos, objectSize, "Assets/box_10.gpmesh", goalBlock, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(20):
//			new GoalBlock(_objectPos, objectSize, "Assets/box_15.gpmesh", goalBlock, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}
//
///*
//@fn	���X�|�[���n�_�̃f�[�^�ɃA�N�Z�X����
//*/
//void MapCreate::AccessRespawnData()
//{
//	for (float iz = 0; iz < mSizeZ; iz++)
//	{
//		for (float ix = 0; ix < mSizeX; ix++)
//		{
//			const unsigned int name = mRespawnMapData[(int)iz][(int)ix];
//			const Vector3 objectPos = Vector3(mOffset * ix, 0.0f, -mOffset * iz);
//
//			CreateRespawn(name, objectPos);
//		}
//	}
//}
//
///*
//@fn	���X�|�[���n�_�𐶐�����
//*/
//void MapCreate::CreateRespawn(const unsigned int _name, const Vector3 _objectPos)
//{
//	const Vector3 objectSize = Vector3(100, 10, 100);
//
//	switch (mScene)
//	{
//	case SceneBase::stage01:
//
//		switch (_name)
//		{
//		case(21):
//			new Respawn(_objectPos, objectSize, respawn01, SceneBase::stage01);
//			break;
//
//		case(22):
//			new Respawn(_objectPos, objectSize, respawn02, SceneBase::stage01);
//			break;
//
//		case(23):
//			new Respawn(_objectPos, objectSize, respawn03, SceneBase::stage01);
//			break;
//		}
//		break;
//
//	case SceneBase::stage02:
//
//		switch (_name)
//		{
//		case(21):
//			new Respawn(_objectPos, objectSize, respawn01, SceneBase::stage02);
//			break;
//
//		case(22):
//			new Respawn(_objectPos, objectSize, respawn02, SceneBase::stage02);
//			break;
//
//		case(23):
//			new Respawn(_objectPos, objectSize, respawn03, SceneBase::stage02);
//			break;
//		}
//		break;
//	}
//}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, _fileName))
	{
		return false;
	}

	//�J����document��type��map���H
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}
	//�J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	//���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto&mapIter: _mapData)
	{
		mapIter.resize(width);
	}

	//���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
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
