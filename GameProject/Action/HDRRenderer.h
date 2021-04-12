/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/
#include "Game.h"
#include "Math.h"

class HDRRenderer
{
public:


	HDRRenderer(int _fbowidth, int _fboheight, int _bloomLevel);
	~HDRRenderer();

	void HdrRecordBegin();
	void HdrRecordEnd();
	void HiBrightBlurCreate();
	void HdrTonemapAndBrightBlurCombine();
	void CopyDepthToScreen();

	unsigned int GetColorTexID()	{ return mHdrColorBuffers[0]; }
	unsigned int GetHDRTexID()		{ return mHdrColorBuffers[1]; }

private:
	void  InitHDRBuffers();
	void  InitBlurBuffers();
	void  InitScreenQuadVAO();
	float GaussianDistribution(const Vector2& _pos, float _rho);
	void  CalcGaussBlurParam(int _w, int _h, Vector2 _dir, float _deviation);

	class Shader*             mGaussianBlurShader;
	class Shader*             mDownSamplingShader;
	class Shader*             mHdrToneAndBlurBlendShader;
	unsigned int              mQuadScreenVAO;
	unsigned int              mQuadScreenVBO;

	unsigned int              mBufferWidth;
	unsigned int              mBufferHeight;
	unsigned int              mBloomBufferLevel;
	unsigned int              mBloomBufferNum;

	//浮動小数点FBO
	unsigned int              mHdrFBO;

	unsigned int              mHdrRBO;
	unsigned int              mHdrColorBuffers[2];

	//ブラー用のフレームバッファオブジェクト
	std::vector<unsigned int> mBlurFBOs;
	// ブラー結果のテクスチャID
	std::vector<unsigned int> mBlurBufferTexs;

	//ガウスぼかしのサンプリング点
	const int                 mSampleCount = 15;
	//サンプリング点の座標(u,v) & w:重み
	Vector3                   mOffset[15];
};