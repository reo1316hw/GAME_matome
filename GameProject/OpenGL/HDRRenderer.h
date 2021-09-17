/*
@brief プリプロセッサ
*/
#pragma once

class HDRRenderer
{
public:
	
	/*
	@fn		コンストラクタ
	@param	_fboWidth バッファーの幅
	@param	_fboHeight バッファーの高さ
	@param	_bloomLevel ダウンサンプリング時の段階
	*/
	HDRRenderer(int _fboWidth, int _fboHeight, int _bloomLevel);

	/*
	@fn	デストラクタ
	*/
	~HDRRenderer();

	/*
	@fn	HDR開始
	*/
	void HdrRecordBegin();

	/*
	@fn	HDR終了
	*/
	void HdrRecordEnd();

	/*
	@fn	ダウンサンプリング＋ガウスぼかし
	*/
	void HiBrightBlurCreate();

	/*
	@fn	トーンマッピング＋ブルーム処理
	*/
	void HdrTonemapAndBrightBlurCombine();

	/*
	@fn	ブルーム情報に深度情報を加えて光る位置を決める
	*/
	void CopyDepthToScreen();

private:

	/*
	@fn	HDRバッファーの登録
	*/
	void  InitHDRBuffers();

	/*
	@fn	ぼかすバッファーの登録
	*/
	void  InitBlurBuffers();

	/*
	@fn	画面全体を描く四角形用頂点配列の登録
	*/
	void  InitScreenQuadVAO();

	float GaussianDistribution(const Vector2& _Pos, float _rho);

	/*
	@fn	ガウスぼかし計算
	*/
	void  CalcGaussBlurParam(int _w, int _h, Vector2 _dir, float _deviation);

	//ガウスぼかしシェーダー
	class Shader*             mGaussianBlurShader;
	//ダウンサンプリングシェーダー
	class Shader*             mDownSamplingShader;
	//トーンマップ&ブルーム処理シェーダー
	class Shader*             mHdrToneAndBlurBlendShader;

	//画面全体を描く四角形用頂点配列
	unsigned int              mQuadScreenVAO;
	//画面全体を描く四角形用頂点バッファー
	unsigned int              mQuadScreenVBO;
	//バッファーの幅
	unsigned int              mBufferWidth;
	//バッファーの高さ
	unsigned int              mBufferHeight;
	//ダウンサンプリング時の段階
	unsigned int              mBloomBufferLevel;
	//浮動小数点フレームバッファオブジェクト
	unsigned int              mHdrFBO;
	//レンダーバッファ
	unsigned int              mHdrRBO;
	//2つのカラーバッファ
	unsigned int              mHdrColorBuffers[2];

	//ブラー用のフレームバッファオブジェクト
	std::vector<unsigned int> mBlurFBOs;
	// ブラー結果のテクスチャID
	std::vector<unsigned int> mBlurBufferTexs;

	//サンプリング点の座標(u,v) & w:重み
	Vector3                   mOffset[15];
};