/*
@brief プリプロセッサ
*/
#pragma once

class GoalLineRoot
{
public:

	/*
	@fn    コンストラクタ
	@param _TopLeftOrigin 左上の原点
	@param	_SceneTag シーンのタグ
	@param _playerPtr プレイヤーのポインタ
	*/
	GoalLineRoot(const Vector3& _TopLeftOrigin, const SceneBase::Scene _SceneTag, Player* _playerPtr);

	/*
    @fn デストラクタ
    */
	~GoalLineRoot() {};

private:

	
	/*
	@fn    各ゴールラインの速度を指定
	@param _Quantity 個数
	*/
	void SpecifyVel(const int _Quantity);
	
	/*
	@fn    各ゴールラインの座標を指定
	@param _Quantity 個数
	*/
	void SpecifyPos(const int _Quantity);
	
	/*
	@fn    各ゴールラインの速度を補正
	@param _Quantity 個数
	*/
	void CorrectVel(const int _Quantity);
	
	/*
	@fn   各ゴールラインのテクスチャデータを指定
	@param _Quantity 個数
	*/
	void SpecifyTextureName(const int _Quantity);

	//左側に配置されているゴールラインの数
	const int LeftNum;

	//ゴールラインのポインタ
	GoalLine* mGoalLine;

	//テクスチャデータのパス
	std::string mTextureName;

	//座標
	Vector3 mPos;
	//速度
	Vector3 mVel;
public://ゲッターセッター

	/*
	@return 座標
	*/
	Vector3 GetPos() { return mPos; };
};