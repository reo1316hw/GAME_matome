/*
@brief	プリプロセッサ
*/
#pragma once

class Sprite;
class InputSystem;
class MapCreate;
class HeartUI;
class GoalLine;
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
    */
    virtual SceneBase* update() = 0;

    /*
    @enum シーンの種類
    */
    enum Scene
    {
        // その他
        other,
        // タイトル
        title,
        // チュートリアル
        tutorial,
        // ステージセレクト画面
        stageSelect,
        // ステージ1
        stage01,
        // ステージ2
        stage02,
        // ゲームクリア
        gameClear,
        // ゲームオーバー
        gameOver,
        // コンティニュー 
        Continue
    };

protected:

    //背景
    Sprite*      mSprite;
    //入力管理クラス
    InputSystem* mInputSystem;
    //マップ生成
    MapCreate*   mMapCreate;
    //プレイヤーのポインタ
    Player*      mPlayer;
    //ゴールライン
    GoalLine*        mGoalLine;
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