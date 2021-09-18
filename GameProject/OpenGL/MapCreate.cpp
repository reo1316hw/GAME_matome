/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MapCreate::MapCreate() :GameObject(SceneBase::eOtherScene,Tag::eOtherTag)
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
	// �v���C���[�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mPlayerMapData, "Assets/Config/tutorialFix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/tutorialFix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/tutorialFix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
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
@fn		�X�e�[�W1��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return �v���C���[�̃|�C���^
*/
Player* MapCreate::OpenStage01File()
{
	// �v���C���[�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage01Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage01Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage01Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
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
@fn	  �X�e�[�W2��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return �v���C���[�̃|�C���^
*/
Player* MapCreate::OpenStage02File()
{
	// �v���C���[�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mPlayerMapData, "Assets/Config/stage02Fix.json", "Player"))
	{
		printf("don't have Layer/Player\n");
	}

	mSizeX = mPlayerMapData[0].size();
	mSizeZ = mPlayerMapData.size();

	// ���w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mLowerMapData, "Assets/Config/stage02Fix.json", "Lower"))
	{
		printf("don't have Layer/Lower\n");
	}

	// ��w�̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperMapData, "Assets/Config/stage02Fix.json", "Upper"))
	{
		printf("don't have Layer/Upper\n");
	}

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mGoalBlockMapData, "Assets/Config/stage02Fix.json", "Goal"))
	{
		printf("don't have Layer/Goal\n");
	}

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mVerticalBlockMapData, "Assets/Config/stage02Fix.json", "VerticalBlock"))
	{
		printf("don't have Layer/VerticalBlock\n");
	}

	// �S�[���̃}�b�v�f�[�^�̓ǂݍ���
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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateTutorialObject(Name, ObjectPos);
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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage01Object(Name, ObjectPos);
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
				const unsigned int Name = _mapData[iz][ix];
				const Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, -mOffset * iz);

				CreateStage02Object(Name, ObjectPos);
			}
		}
	}
}

/*
@fn    �`���[�g���A���̃I�u�W�F�N�g�𐶐�����
@param _Name �}�b�v�f�[�^�̗v�f
@param _ObjectPos �I�u�W�F�N�g�̍��W
*/
void MapCreate::CreateTutorialObject(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_Name)
	{
	    case(eGroundNum):
        	new Ground(_ObjectPos, ObjectSize, "Assets/box.gpmesh", eGroundTag, SceneBase::eTutorial);
        	break;
        case(eGlassNum):
        	new Glass(_ObjectPos, ObjectSize, "Assets/box_02.gpmesh", eGlassTag, SceneBase::eTutorial, mPlayer);
        	break;
        case(eBlockNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
        	const Vector3 BlockPos = _ObjectPos + AddPos;
        
        	new Block(BlockPos, ObstacleSize, "Assets/box_03.gpmesh", eBlockTag, SceneBase::eTutorial);
        	break;
        }
        case(eVerticalMoveGroundNum):
        	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_04.gpmesh", eVerticalMoveGroundTag, SceneBase::eTutorial, mPlayer);
        	break;
        case(eJumpNum):
        	new Jump(_ObjectPos, ObjectSize, "Assets/box_05.gpmesh", eJumpTag, SceneBase::eTutorial, mPlayer);
        	break;
        case(eLateralMoveGroundNum):
        	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box.gpmesh", eLateralMoveGroundTag, SceneBase::eTutorial, 1000.0f, mPlayer);
        	break;
        case(ePlayerNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
        	const Vector3 PlayerPos = _ObjectPos + AddPos;
        	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
        
        	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::eTutorial);
        	break;
        }
        case(eLowUpBlockNum):
        {
        	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
        	const Vector3 UpBlockPos = _ObjectPos + AddPos;
        
        	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_03.gpmesh", eLowUpBlockTag, SceneBase::eTutorial, mPlayer);
        	break;
        }
        case(eLeftGroundNum):
        	new LeftGround(_ObjectPos, ObjectSize, "Assets/box_07.gpmesh", eLeftGroundTag, SceneBase::eTutorial, mPlayer);
        	break;
        case(eRightGroundNum):
        	new RightGround(_ObjectPos, ObjectSize, "Assets/box_06.gpmesh", eRightGroundTag, SceneBase::eTutorial, mPlayer);
        	break;
        case(eGoalBlockNum):
        {
        	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
        
        	new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_03.gpmesh", eGoalBlockTag, SceneBase::eTutorial);
        	break;
        }
	}
}

/*
@fn    �X�e�[�W1�̃I�u�W�F�N�g�𐶐�����
@param _Name �}�b�v�f�[�^�̗v�f
@param _ObjectPos �I�u�W�F�N�g�̍��W
*/
void MapCreate::CreateStage01Object(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);

	switch (_Name)
	{
	    case(eGroundNum):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/box_08.gpmesh", eGroundTag, SceneBase::eStage01);
	    	break;
	    case(eGlassNum):
			new Glass(_ObjectPos, ObjectSize, "Assets/box_09.gpmesh", eGlassTag,SceneBase::eStage01, mPlayer);
			break;
	    case(eBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
			new Block(BlockPos, ObstacleSize, "Assets/box_10.gpmesh", eBlockTag, SceneBase::eStage01);
			break;
	    }
	    case(eVerticalMoveGroundNum):
		    new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_11.gpmesh", eVerticalMoveGroundTag, SceneBase::eStage01, mPlayer);
			break;
	    case(eJumpNum):
			new Jump(_ObjectPos, ObjectSize, "Assets/box_12.gpmesh", eJumpTag, SceneBase::eStage01, mPlayer);
			break;
		case(eLateralMoveGroundNum):
			new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box_08.gpmesh", eLateralMoveGroundTag, SceneBase::eStage01 ,1000.0f, mPlayer);
			break;
	    case(ePlayerNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
		    mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::eStage01);
			break;
	    }
	    case(eGoalBlockNum):
		{
			const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);

			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_10.gpmesh", eGoalBlockTag, SceneBase::eStage01);
			break;
		}
	}
}

/*
@fn    �X�e�[�W2�̃I�u�W�F�N�g�𐶐�����
@param _Name �}�b�v�f�[�^�̗v�f
@param _ObjectPos �I�u�W�F�N�g�̍��W
*/
void MapCreate::CreateStage02Object(const unsigned int _Name, const Vector3 _ObjectPos)
{
	const Vector3 ObjectSize = Vector3(100.0f, 10.0f, 100.0f);
	const Vector3 ObstacleSize = Vector3(70.0f, 100.0f, 100.0f);
	const Vector3 MoveObstacleSize = Vector3(70.0f, 70.0f, 100.0f);

	switch (_Name)
	{
	    case(eGroundNum):
	    	new Ground(_ObjectPos, ObjectSize, "Assets/box_13.gpmesh", eGroundTag, SceneBase::eStage02);
	    	break;
	    case(eGlassNum):
	    	new Glass(_ObjectPos, ObjectSize, "Assets/box_14.gpmesh", eGlassTag, SceneBase::eStage02, mPlayer);
	    	break;
	    case(eBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 BlockPos = _ObjectPos + AddPos;
	    
	    	new Block(BlockPos, ObstacleSize, "Assets/box_15.gpmesh", eBlockTag, SceneBase::eStage02);
	    	break;
	    }
	    case(eVerticalMoveGroundNum):
	    	new VerticalMoveGround(_ObjectPos, ObjectSize, "Assets/box_16.gpmesh", eVerticalMoveGroundTag, SceneBase::eStage02, mPlayer);
	    	break;
	    case(eJumpNum):
	    	new Jump(_ObjectPos, ObjectSize, "Assets/box_17.gpmesh", eJumpTag, SceneBase::eStage02, mPlayer);
	    	break;
	    case(eLateralMoveGroundNum):
	    	new LateralMoveGround(_ObjectPos, ObjectSize, "Assets/box_13.gpmesh", eLateralMoveGroundTag, SceneBase::eStage02, 1000.0f, mPlayer);
	    	break;
	    case(ePlayerNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 PlayerPos = _ObjectPos + AddPos;
	    	const Vector3 PlayerSize = Vector3(1.2f, 1.2f, 1.2f);
	    
	    	mPlayer = new Player(PlayerPos, PlayerSize, "Assets/Sphere.gpmesh", Tag::ePlayerTag, SceneBase::eStage02);
	    	break;
	    }
	    case(eLowUpBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, -100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_15.gpmesh", eLowUpBlockTag, SceneBase::eStage02, mPlayer);
	    	break;
	    }
	    case(eVerticalBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 VerticalBlockPos = _ObjectPos + AddPos;
	    
	    	new VerticalBlock(VerticalBlockPos, ObstacleSize, "Assets/box_15.gpmesh", eVerticalBlockTag, SceneBase::eStage02);
	    	break;
	    }
	    case(eAerialBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 500.0f, 0.0f);
	    	const Vector3 AerialBlockPos = _ObjectPos + AddPos;
			const Vector3 AerialBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
	    	new AerialBlock(AerialBlockPos, AerialBlockSize, "Assets/box_15.gpmesh", eAerialBlockTag, SceneBase::eStage02);
	    	break;
	    }
		case(eRightBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPosX = 600.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPosX, "Assets/box_15.gpmesh", eRightBlockTag, ColliderTag::eRightBlockTag, SceneBase::eStage02, mPlayer);
			break;
		}
		case(eLeftBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 70.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 600.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", eLeftBlockTag, ColliderTag::eLeftBlockTag, SceneBase::eStage02, mPlayer);
			break;
		}
		case(eLeftGroundNum):
			new LeftGround(_ObjectPos, ObjectSize, "Assets/box_19.gpmesh", eLeftGroundTag, SceneBase::eStage02, mPlayer);
			break;
		case(eRightGroundNum):
			new RightGround(_ObjectPos, ObjectSize, "Assets/box_18.gpmesh", eRightGroundTag, SceneBase::eStage02, mPlayer);
			break;
		case(eDownBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 1600.0f, 0.0f);
			const Vector3 DownBlockPos = _ObjectPos + AddPos;

			new DownBlock(DownBlockPos, ObjectSize, "Assets/box_13.gpmesh", eDownBlockTag, SceneBase::eStage02, mPlayer);
			break;
		}
	    case(eHighUpBlockNum):
	    {
	    	const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
	    	const Vector3 UpBlockPos = _ObjectPos + AddPos;
	    
	    	new UpBlock(UpBlockPos, ObstacleSize, "Assets/box_15.gpmesh", eHighUpBlockTag, SceneBase::eStage02, mPlayer);
	    	break;
	    }
	    case(eGoalBlockNum):
	    {
	    	const Vector3 GoalBlockSize = Vector3(100.0f, 100.0f, 100.0f);
	    
			new GoalBlock(_ObjectPos, GoalBlockSize, "Assets/box_15.gpmesh", eGoalBlockTag, SceneBase::eStage02);
			break;
	    }
		case(eRightOneMoveBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 RightBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new RightBlock(RightBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", eRightOneMoveBlockTag, ColliderTag::eRightOneMoveBlockTag, SceneBase::eStage02, mPlayer);
			break;
		}
		case(eLeftOneMoveBlockNum):
		{
			const Vector3 AddPos = Vector3(0.0f, 100.0f, 0.0f);
			const Vector3 LeftBlockPos = _ObjectPos + AddPos;
			const float AddEndPos = 200.0f;

			new LeftBlock(LeftBlockPos, MoveObstacleSize, AddEndPos, "Assets/box_15.gpmesh", eLeftOneMoveBlockTag, ColliderTag::eLeftOneMoveBlockTag, SceneBase::eStage02, mPlayer);
			break;
		}
	}
}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _FileName, const char* _LayerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, _FileName))
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
	std::string layerNameString(_LayerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _LayerName);
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