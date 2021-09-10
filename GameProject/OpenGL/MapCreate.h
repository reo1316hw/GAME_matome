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
	@fn		�`���[�g���A����json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return �v���C���[�̃|�C���^
	*/
	Player* OpenTutorialFile();

	/*
	@fn		�X�e�[�W1��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return �v���C���[�̃|�C���^
	*/
	Player* OpenStage01File();

	/*
	@fn		�X�e�[�W2��json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return �v���C���[�̃|�C���^
	*/
	Player* OpenStage02File();

	/*
	@fn	   �`���[�g���A���̃}�b�v�f�[�^�ɃA�N�Z�X����
	@param _mapData �}�b�v�f�[�^
	@param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
	*/
	void AccessTutorialMapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
    @fn	   �X�e�[�W1�̃}�b�v�f�[�^�ɃA�N�Z�X����
    @param _mapData �}�b�v�f�[�^
    @param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
    */
	void AccessStage01MapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
    @fn	   �X�e�[�W2�̃}�b�v�f�[�^�ɃA�N�Z�X����
    @param _mapData �}�b�v�f�[�^
    @param _sizeY ��ɔz�u���Ă������߂̃I�u�W�F�N�g�̌�
    */
	void AccessStage02MapData(std::vector<std::vector<int>> _mapData, int _sizeY);

	/*
	@fn    �`���[�g���A���̃I�u�W�F�N�g�𐶐�����
	@param _name �}�b�v�f�[�^�̗v�f
	@param _objectPos �I�u�W�F�N�g�̍��W
	*/
	void CreateTutorialObject(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn    �X�e�[�W1�̃I�u�W�F�N�g�𐶐�����
	@param _name �}�b�v�f�[�^�̗v�f
	@param _objectPos �I�u�W�F�N�g�̍��W
	*/
	void CreateStage01Object(const unsigned int _name, const Vector3 _objectPos);

	/*
	@fn    �X�e�[�W2�̃I�u�W�F�N�g�𐶐�����
	@param _name �}�b�v�f�[�^�̗v�f
	@param _objectPos �I�u�W�F�N�g�̍��W
	*/
	void CreateStage02Object(const unsigned int _name, const Vector3 _objectPos);

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
	Player* CreatePlayer(const unsigned int _name, const Vector3 _objectPos, Player* _playerPtr);

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

	// ���w�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mLowerMapData;
	// ��w�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mUpperMapData;
	// �S�[�����̃}�b�v�f�[�^
	std::vector<std::vector<int>> mGoalBlockMapData;
	// �c����Q���̃}�b�v�f�[�^
	std::vector<std::vector<int>> mVerticalBlockMapData;
	// ��ړ��u���b�N�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mUpBlockMapData;

	// �v���C���[�̃|�C���^
	Player* mPlayer;

	//int mMapData[2] = { mLowerMapData ,mUpperMapData };
	
	// ���݂̃V�[��
	int mScene;
	// ���̃}�b�v�f�[�^
	int	mSizeX;
	// �����̃}�b�v�f�[�^
	int	mSizeY;
	// ���s�̃}�b�v�f�[�^
	int	mSizeZ;

	// �I�u�W�F�N�g���Ƃ̋���
	float mOffset;
};

