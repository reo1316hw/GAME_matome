﻿/*
@brief インクルード
*/
#include "pch.h"

/*
@fn		コンストラクタ
@param	_Verts 頂点バッファの配列のポインタ
@param	_numVerts 頂点数
@param	_Indices インデックスバッファの配列のポインタ
@param	_numIndices インデックスの数
*/
VertexArray::VertexArray(const float* _Verts, unsigned int _numVerts,
	const unsigned int* _Indices, unsigned int _numIndices)
	:mNumVerts(_numVerts)
	,mNumIndices(_numIndices)
{
	// 頂点配列の作成
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// 頂点バッファの作成
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 8 * sizeof(float), _Verts, GL_STATIC_DRAW);

	// インデクスバッファの作成
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), _Indices, GL_STATIC_DRAW);

	//最初の頂点属性を有効に（位置座標）
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//頂点属性インデックス（位置座標）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		0						//頂点データの開始位置からこの属性までのオフセット
	);
	//第2の頂点属性を有効に（法線ベクトル）
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//頂点属性インデックス（法線ベクトル）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		reinterpret_cast<void*>(sizeof(float) * 3));	//オフセットポインタ
    //第3の頂点属性を有効に（テクスチャ座標）
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,						//頂点属性インデックス（テクスチャ座標）
        2,						//要素の数（UVは2個）
        GL_FLOAT,				//要素の型
        GL_FALSE,				//（GL_FLOATには使わない）
        sizeof(float) * 8,		//各頂点のサイズ
        reinterpret_cast<void*>(sizeof(float) * 6));	//オフセットポインタ
}

/*
@fn		頂点配列コンストラクタ
@param	_Verts 頂点バッファの配列のポインタ
@param	_numVerts 頂点数
@param	_layout 頂点レイアウト
@param	_Indices インデックスバッファの配列のポインタ
@param	_numIndices インデックスの数
*/
VertexArray::VertexArray(const void * _Verts, unsigned int _numVerts, Layout _layout, const unsigned int * _Indices, unsigned int _numIndices)
	: mNumVerts(_numVerts)
	, mNumIndices(_numIndices)
{
	// 頂点配列の作成
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// 頂点レイアウトが スケルタルモデルなら　ボーンID、影響度分をサイズ増やす
	unsigned vertexSize = 8 * sizeof(float);
	if (_layout == Layout::ePosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// 頂点バッファの作成
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, mNumVerts * vertexSize, _Verts, GL_STATIC_DRAW);

	// インデックスバッファの作成
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(unsigned int), _Indices, GL_STATIC_DRAW);

	// 頂点属性
	if (_layout == Layout::ePosNormTex)
	{
		// float 3個分　→　位置 x,y,z　位置属性をセット
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// 次のfloat 3個分 → 法線 nx, ny, nz　法線属性をセット
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// 次のfloat 2個分 u, v  テクスチャ座標属性をセット
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (_layout == Layout::ePosNormSkinTex)
	{
		// float 3個分　→　位置 x,y,z　位置属性をセット
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// 次のfloat 3個分 → 法線 nx, ny, nz　法線属性をセット
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		//　影響受けるボーンインデックス番号  (int型をキープ)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// ボーンウェイト情報 (float に変換)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// 次のfloat 2個分 u, v  テクスチャ座標属性をセット
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}

/*
@fn	デストラクタ
*/
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

/*
@fn 頂点配列をアクティブにする（描画に使用できるようにする）
*/
void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
