/*
@file  Collision.h
@brief 正方形や線、三角形等のオブジェクト宣言
*/

/*
@brief プリプロセッサ
*/
#pragma once

//線分
struct LineSegment
{
	/*
	@param	_Start 線分の開始地点のポジション
	@param	_End 線分の終了地点のポジション
	*/
    LineSegment(const Vector3& _Start, const Vector3& _End);
	
	/*
	@fn		線分上の点を返す
	@param	_t 入力値 t（L(t) = Start + (End - Start)t）
	@return 線分上の点のポジション(Vector3型)
	*/
	Vector3 PointOnSegment(float _t) const;

	/*
	@fn		点と線分の間の最短距離を返す
	@param	_Point 任意の点のポジション
	@return 最短距離(float型)
	*/
    float MinDistanceSquared(const Vector3& _Point)const;

	/*
	@fn		線分と線分の間の最短距離を返す
	@param	_Line1 判定する線分の構造体１
	@param	_Line2 判定する線分の構造体２
	@return 最短距離(float型)
	*/
    static float MinDistanceSquared(const LineSegment& _Line1,const LineSegment& _Line2);

	//線分の開始地点
    Vector3 m_start;
	//線分の終了地点
    Vector3 m_end;
};

//平面
struct Plane
{
	/*
	@param	_Normal 平面の法線ベクトル
	@param	_distance 平面と原点の符号つき最短距離
	*/
    Plane(const Vector3& _Normal, float _distance);

	/*
	@param	_Vec1 平面上の点1
	@param	_Vec2 平面上の点2
	@param	_Vec3 平面上の点3
	*/
    Plane(const Vector3& _Vec1, const Vector3& _Vec2, const Vector3& _Vec3);

	/*
	@fn		点と平面の最短距離を返す
	@param	_Point 任意の点のポジション
	@return 符号つき最短距離(float型)
	*/
    float SignedDistance(const Vector3& _Point);

	//平面の法線ベクトル
    Vector3 m_normal;
	//平面と原点の符号つき最短距離
    float m_distance;
};

//球
struct Sphere
{
	/*
	@param	_Center 球体の中心座標
	@param	_Radius 球体の半径
	*/
    Sphere(const Vector3& _Center, const float _Radius);
    
	/*
	@fn		球体に点が含まれているかどうか
	@param	_Point 任意の点
	@return true : 当たっている , false : 当たっていない(bool型)
	*/
	bool Contains(const Vector3& _Point)const;

	//球体の中心座標
    Vector3 m_center;
	//球体の半径
    float m_radius;
};

//軸並行バウンディングボックス(Axis-Aligned Bounding Box)
struct AABB
{
	/*
	@param	_Min 最小のx,y,zの値のポジション
	@param	_Max 最大のx,y,zの値のポジション
	*/
    AABB(const Vector3& _Min,const Vector3& _Max);

	/*
	@fn		最小値と最大値を各成分ごとに更新する
	@param	_Point 任意の点のポジション
	*/
    void UpdateMinMax(const Vector3& _Point);

	/*
	@fn		当たり判定ボックスの回転
	@param	_Quaternion 回転軸と回転表す値
	*/
    void Rotate(const Quaternion& _Quaternion);
    
	/*
	@fn	ボックスに点が含まれているかどうか
	@param	_Point 任意の点
	@return true : 当たっている , false : 当たっていない(bool型)
	*/
	bool Contains(const Vector3& _Point)const;
    
	/*
	@fn		点とボックスの最短距離を返す
	@param	_Point 任意の点
	@return 最短距離
	*/
	float MinDistanceSquared(const Vector3& _Point)const;

	/*
	@fn		最小値と最大値を初期化
	@param	_Point 任意の点
	*/
	void InitMinMax(const Vector3& _Point) { m_min = m_max = _Point; };

	//最小のx,y,zの値のポジション
    Vector3 m_min;
	//最大のx,y,zの値のポジション
    Vector3 m_max;
};

//有向バウンディングボックス（Oriented Bounding Box）
//未実装
struct OBB
{
	//中心の座標
    Vector3 m_center;
	//回転クォータニオン
    Quaternion m_rotation;
	//ボックスの広がり（幅、高さ、奥行き）
    Vector3 m_extents;
};

//カプセル
struct Capsule
{
	/*
	@param	_Start 始点となる点の座標
	@param	_End 終点となる点の座標
	@param	_radius カプセルの半径
	*/
    Capsule(const Vector3& _Start,const Vector3& _End,float _radius);

	/*
	@fn	カプセルの始点と終点の線分上の点を返す
	@param	_t 入力値 t（L(t) = Start + (End - Start)t）
	@return 線分上の点のポジション(Vector3型)
	*/
    Vector3 PointOnSegment(float _t)const;

	/*
	@fn	カプセルに点が含まれているかどうか
	@param	_Point 任意の点
	@return true : 当たっている , false : 当たっていない(bool型)
	*/
    bool Contains(const Vector3& _Point)const;

	//カプセルを構成する線分
    LineSegment m_segment;
	//カプセルの半径
    float m_radius;
};

//凸ポリゴン
struct ConvexPolygon
{
	/*
	@fn		２次元のポリゴンに点が含まれているかどうか
	@param	_Point 任意の点
	@return true : 当たっている , false : 当たっていない(bool型)
	*/
    bool Contains(const Vector2& _Point)const;

	//頂点の可変長コンテナ
    std::vector<Vector2> m_vertices;
};

/*
@fn	球と球の当たり判定
@param	_Sphere1 球の構造体１
@param	_Sphere2 球の構造体２
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const Sphere& _Sphere1,const Sphere& _Sphere2);

/*
@fn		ボックスとボックスの当たり判定
@param	_AABB1 ボックスの構造体１
@param	_AABB2 ボックスの構造体２
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const AABB& _AABB1, const AABB& _AABB2);

/*
@fn		カプセルとカプセルの当たり判定
@param	_Capsule1 カプセルの構造体１
@param	_Capsule2 カプセルの構造体２
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const Capsule& _Capsule1, const Capsule& _Capsule2);

/*
@fn	球とボックスの当たり判定
@param	_Sphere 球の構造体
@param	_AABB ボックスの構造体
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const Sphere& _Sphere, const AABB& _AABB);

/*
@fn	線分と球の当たり判定
@param	_Line 線分の構造体
@param	_Sphere 球の構造体
@param	_outT 線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const LineSegment& _Line, const Sphere& _Sphere, float& _outT);

/*
@fn	線分と平面の当たり判定
@param	_Line　線分の構造体
@param	_Plane　平面の構造体
@param	_outT　線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const LineSegment& _Line, const Plane& _Plane, float& _outT);

/*
@fn	線分とボックスの当たり判定
@param	_Line 線分の構造体
@param	_AABB ボックスの構造体
@param	_outT 線分の始点から接触している点までの値tを格納する
@param	_outNorm 線分の始点から接触した面の法線ベクトルを格納する
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool Intersect(const LineSegment& _Line, const AABB& _AABB, float& _outT,
    Vector3& _outNorm);

/*
@fn	球スイープの当たり判定
@param	_Sphere1 １フレーム前の球１の構造体
@param	_Sphere2 現在のフレームの球１の構造体
@param	_Sphere3 １フレーム前の球２の構造体
@param	_Sphere4 現在のフレームの球２の構造体
@param	_outT 線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない(bool型)
*/
bool SweptSphere(const Sphere& _Sphere1, const Sphere& _Sphere2,
    const Sphere& _Sphere3, const Sphere& _Sphere4, float& _outT);
