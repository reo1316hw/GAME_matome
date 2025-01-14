/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Sprite;
class InputSystem;
class MapCreate;
class HeartUI;
class CheckpointBoard;
class Player;

class SceneBase
{
public:

    /*
    @fn	コンストラクタ
    */
    SceneBase() {};

    /*
    @fn	デストラクタ
    */
    virtual ~SceneBase() {};

    /*
    @fn	現在のシーン時に毎フレーム更新処理をする
    @param	_KeyState 各入力機器の入力状態
    */
    virtual SceneBase* UpdateScene(const InputState& _KeyState) = 0;

    /*
    @enum シーンの種類
    */
    enum Scene
    {
        // その他
        eOtherScene,
        // タイトル
        eTitle,
        // チュートリアル
        eTutorial,
        // ステージ1
        eStage01,
        // ステージ2
        eStage02,
        // ゲームクリア
        eGameClear,
        // ゲームオーバー
        eGameOver,
        // コンティニュー 
        eContinue
    };

protected:

    //背景
    Sprite*      mSprite;
    //マップ生成
    MapCreate*   mMapCreate;
    //プレイヤーのポインタ
    Player*      mPlayer;
    //チェックポイントボード
    CheckpointBoard* mCheckPointBoard;
    //プレイヤーの体力UI
    HeartUI*     mHeartUI;
    //ゲームクリアしたか
    bool         mClearFlag;
    //次のシーンに遷移する時の待機時間
    int          mNextSceneCount;

private:

    //現在のシーン
    static int   mIsScene;

public://ゲッターセッター

    /*
    @return 現在のシーン(int型)
    */
    static int  GetScene() { return mIsScene; };

    /*
    @param _isScene 現在のシーン
    */
    virtual void SetScene(int _isScene) { mIsScene = _isScene; };
};