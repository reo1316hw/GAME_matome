/*
@brief �v���v���Z�b�T
*/
#pragma once

/*
@brief �O���錾
*/
class Sprite;
class InputSystem;
class MapCreate;
class HeartUI;
class GoalLine;
class CheckpointBoard;
class Player;

class SceneBase
{
public:

    /*
    @fn	�R���X�g���N�^
    */
    SceneBase() {};

    /*
    @fn	�f�X�g���N�^
    */
    virtual ~SceneBase() {};

    /*
    @fn	���݂̃V�[�����ɖ��t���[���X�V����������
    */
    virtual SceneBase* UpdateScene(const InputState& _State) = 0;

    /*
    @enum �V�[���̎��
    */
    enum Scene
    {
        // ���̑�
        eOtherScene,
        // �^�C�g��
        eTitle,
        // �`���[�g���A��
        eTutorial,
        // �X�e�[�W1
        eStage01,
        // �X�e�[�W2
        eStage02,
        // �Q�[���N���A
        eGameClear,
        // �Q�[���I�[�o�[
        eGameOver,
        // �R���e�B�j���[ 
        eContinue
    };

protected:

    //�w�i
    Sprite*      mSprite;
    //���͊Ǘ��N���X
    InputSystem* mInputSystem;
    //�}�b�v����
    MapCreate*   mMapCreate;
    //�v���C���[�̃|�C���^
    Player*      mPlayer;
    //�S�[�����C��
    GoalLine*        mGoalLine;
    //�`�F�b�N�|�C���g�{�[�h
    CheckpointBoard* mCheckPointBoard;
    //�v���C���[�̗̑�UI
    HeartUI*     mHeartUI;
    //�Q�[���N���A������
    bool         mClearFlag;
    //���̃V�[���ɑJ�ڂ��鎞�̑ҋ@����
    int          mNextSceneCount;

private:

    //���݂̃V�[��
    static int   mIsScene;

public://�Q�b�^�[�Z�b�^�[

    /*
    @return ���݂̃V�[��(int�^)
    */
    static int  GetScene() { return mIsScene; };

    /*
    @param _isScene ���݂̃V�[��
    */
    virtual void SetScene(int _isScene) { mIsScene = _isScene; };
};