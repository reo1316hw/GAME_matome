/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Player;

/*
@brief �}�b�v�f�[�^�̃I�u�W�F�N�g�̔ԍ�
*/
enum MapDataNum
{
	eGroundNum = 1,
	eGlassNum = 2,
	eBlockNum = 3,
	eVerticalMoveGroundNum = 4,
	eJumpNum = 5,
	eLateralMoveGroundNum = 6,
	ePlayerNum = 7,
	eLowUpBlockNum = 8,
	eVerticalBlockNum = 9,
	eAerialBlockNum = 10,
	eRightBlockNum = 11,
	eLeftBlockNum = 13,
	eLeftGroundNum = 14,
	eRightGroundNum = 15,
	eDownBlockNum = 16,
	eHighUpBlockNum = 17,
	eGoalBlockNum = 20,
	eRightOneMoveBlockNum = 418,
	eLeftOneMoveBlockNum = 419,

};

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
	void CreateTutorialObject(const unsigned int _Name, const Vector3 _ObjectPos);

	/*
	@fn    �X�e�[�W1�̃I�u�W�F�N�g�𐶐�����
	@param _name �}�b�v�f�[�^�̗v�f
	@param _objectPos �I�u�W�F�N�g�̍��W
	*/
	void CreateStage01Object(const unsigned int _Name, const Vector3 _ObjectPos);

	/*
	@fn    �X�e�[�W2�̃I�u�W�F�N�g�𐶐�����
	@param _name �}�b�v�f�[�^�̗v�f
	@param _objectPos �I�u�W�F�N�g�̍��W
	*/
	void CreateStage02Object(const unsigned int _Name, const Vector3 _ObjectPos);

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _FileName, const char* _LayerName);

	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);

	// ���w�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mLowerMapData;
	// ��w�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mUpperMapData;
	// �v���C���[�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mPlayerMapData;
	// �S�[�����̃}�b�v�f�[�^
	std::vector<std::vector<int>> mGoalBlockMapData;
	// �c����Q���̃}�b�v�f�[�^
	std::vector<std::vector<int>> mVerticalBlockMapData;
	// ��ړ��u���b�N�̃}�b�v�f�[�^
	std::vector<std::vector<int>> mUpBlockMapData;

	// �v���C���[�̃|�C���^
	Player* mPlayer;
	// ���̃}�b�v�f�[�^
	int	mSizeX;
	// �����̃}�b�v�f�[�^
	int	mSizeY;
	// ���s�̃}�b�v�f�[�^
	int	mSizeZ;
	// �I�u�W�F�N�g���Ƃ̋���
	float mOffset;
};

