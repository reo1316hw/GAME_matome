/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class Texture;
class SpriteComponent;

class Sprite : public GameObject
{
public:

	/*
	@fn	   コンストラクタ
	@param _FileName 画像ファイルの名前
	*/
	Sprite(const std::string _FileName);

	/*
	@fn	デストラクタ
	*/
	~Sprite() {};

private:

	//テクスチャを生成
	Texture* mSpriteTexture;
	//SpriteComponentを生成
	SpriteComponent* mSpriteComponent;

};

