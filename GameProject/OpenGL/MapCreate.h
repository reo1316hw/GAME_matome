/*
@brief	�v���v���Z�b�T
*/
#pragma once

/*
@brief	�C���N���[�h
*/
class Player;

class MapCreate : public GameObject
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	MapCreate();

	/*
	@fn	�f�X�g���N�^
	*/
	~MapCreate();

	/*
	@fn		json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return	�t�@�C�����J������(bool�^)
	*/
	bool OpenFile();

	/*
	@fn	���̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessGroundData();

	/*
	@fn	���𐶐�����
	*/
	void CreateGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�K���X���̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessGlassData();

	/*
	@fn	�K���X���𐶐�����
	*/
	void CreateGlass(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	��Q���̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessBlockData();

	/*
	@fn	��Q���𐶐�����
	*/
	void CreateBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�c�ړ����̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessVerticalMoveGroundData();

	/*
	@fn	�c�ړ����𐶐�����
	*/
	void CreateVerticalMoveGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�W�����v���̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessJumpData();

	/*
	@fn	�W�����v���𐶐�����
	*/
	void CreateJump(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	���ړ����̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessLateralMoveGroundData();

	/*
	@fn	���ړ����𐶐�����
	*/
	void CreateLateralMoveGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	    �v���C���[�̃f�[�^�ɃA�N�Z�X����
	@return �v���C���[�N���X�̃|�C���^
	*/
	Player* AccessPlayerData();

	/*
	@fn	    �v���C���[�𐶐�����
	@return �v���C���[�N���X�̃|�C���^
	*/
	Player* CreatePlayer(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	��ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessUpBlockData();

	/*
	@fn	��ړ��u���b�N�𐶐�����
	*/
	void CreateUpBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	�c����Q���̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessVerticalBlockData();

	/*
	@fn	�c����Q���𐶐�����
	*/
	void CreateVerticalBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�󒆃u���b�N�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessAerialBlockData();

	/*
	@fn	�󒆃u���b�N�𐶐�����
	*/
	void CreateAerialBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�E�ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessRightBlockData();

	/*
	@fn	�E�ړ��u���b�N�𐶐�����
	*/
	void CreateRightBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	���ړ��u���b�N�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessLeftBlockData();

	/*
	@fn	���ړ��u���b�N�𐶐�����
	*/
	void CreateLeftBlock(const unsigned int _name, const Vector3 _objectPos, const Vector3 _objectPos2);

	/*
	@fn	1�}�X�E�ړ����̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessRightGroundData();

	/*
	@fn	1�}�X�E�ړ����𐶐�����
	*/
	void CreateRightGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	1�}�X���ړ����̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessLeftGroundData();

	/*
	@fn	1�}�X���ړ����𐶐�����
	*/
	void CreateLeftGround(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�����u���b�N�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessDownBlockData();

	/*
	@fn	�����u���b�N�𐶐�����
	*/
	void CreateDownBlock(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	�S�[�����̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessGoalData();

	/*
	@fn	�S�[�����𐶐�����
	*/
	void CreateGoal(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn	���X�|�[���n�_�̃f�[�^�ɃA�N�Z�X����
	*/
	void AccessRespawnData();

	/*
	@fn	���X�|�[���n�_�𐶐�����
	*/
	void CreateRespawn(const unsigned int _name, const Vector3 _objectPos);

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);

	//���}�b�v�f�[�^
	std::vector<std::vector<int>> mGroundMapData;
	//�v���C���[�}�b�v�f�[�^
	std::vector<std::vector<int>> mPlayerMapData;
	//���ړ����}�b�v�f�[�^
	std::vector<std::vector<int>> mLateralMoveGroundMapData;
	//�c�ړ����}�b�v�f�[�^
	std::vector<std::vector<int>> mVerticalMoveGroundMapData;
	//�W�����v���}�b�v�f�[�^
	std::vector<std::vector<int>> mJumpMapData;
	//��Q���}�b�v�f�[�^
	std::vector<std::vector<int>> mBlockMapData;
	//�K���X���}�b�v�f�[�^
	std::vector<std::vector<int>> mGlassMapData;
	//��ړ��u���b�N�}�b�v�f�[�^
	std::vector<std::vector<int>> mUpBlockMapData;
	//�c����Q���}�b�v�f�[�^
	std::vector<std::vector<int>> mVerticalBlockMapData;
	//�󒆃u���b�N�}�b�v�f�[�^
	std::vector<std::vector<int>> mAerialBlockMapData;
	//�E�ړ��u���b�N�}�b�v�f�[�^
	std::vector<std::vector<int>> mRightBlockMapData;
	//���ړ��u���b�N�}�b�v�f�[�^
	std::vector<std::vector<int>> mLeftBlockMapData;
	//1�}�X�E�ړ����}�b�v�f�[�^
	std::vector<std::vector<int>> mRightGroundMapData;
	//1�}�X���ړ����}�b�v�f�[�^
	std::vector<std::vector<int>> mLeftGroundMapData;
	//�����u���b�N�}�b�v�f�[�^
	std::vector<std::vector<int>> mDownBlockMapData;
	//�S�[�����}�b�v�f�[�^
	std::vector<std::vector<int>> mGoalBlockMapData;
	//���X�|�[���n�_�}�b�v�f�[�^
	std::vector<std::vector<int>> mRespawnMapData;

	//���݂̃V�[��
	int mScene;
	//���̃}�b�v�f�[�^
	int	mSizeX;
	//�����̃}�b�v�f�[�^
	int	mSizeY;
	//���s�̃}�b�v�f�[�^
	int	mSizeZ;

	//�I�u�W�F�N�g���Ƃ̋���
	float mOffset;
};

