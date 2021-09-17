/*
@brief プリプロセッサ
*/
#pragma once

namespace Math
{
	const float Pi = 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float _degrees)
	{
		return _degrees * Pi / 180.0f;
	}

	inline float ToDegrees(float _radians)
	{
		return _radians * 180.0f / Pi;
	}

	inline bool NearZero(float _val, float _epsilon = 0.001f)
	{
		if (fabs(_val) <= _epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& _A, const T& _B)
	{
		return (_A < _B ? _B : _A);
	}

	template <typename T>
	T Min(const T& _A, const T& _B)
	{
		return (_A < _B ? _A : _B);
	}

	template <typename T>
	T Clamp(const T& _Value, const T& _Lower, const T& _Upper)
	{
		return Min(_Upper, Max(_Lower, _Value));
	}

	inline float Abs(float _value)
	{
		return fabs(_value);
	}

	inline float Cos(float _angle)
	{
		return cosf(_angle);
	}

	inline float Sin(float _angle)
	{
		return sinf(_angle);
	}

	inline float Tan(float _angle)
	{
		return tanf(_angle);
	}

	inline float Acos(float _value)
	{
		return acosf(_value);
	}

	inline float Atan2(float _y, float _x)
	{
		return atan2f(_y, _x);
	}

	inline float Cot(float _angle)
	{
		return 1.0f / Tan(_angle);
	}

	inline float Lerp(float _a, float _b, float _f)
	{
		return _a + _f * (_b - _a);
	}

	inline float Sqrt(float _value)
	{
		return sqrtf(_value);
	}

	inline float Fmod(float _numer, float _denom)
	{
		return fmod(_numer, _denom);
	}
}

////////////////////////////////////////////
//イージング
//参考元→ http://nakamura001.hatenablog.com/entry/20111117/1321539246

namespace Quintic
{
	//イーズイン
	float EaseIn(float _elapseTime, float _initpos, float _differencePos, float _totalTim);
	//イーズアウト
	float EaseOut(float _elapseTime, float _initpos, float _differencePos, float _totalTim);
}

namespace Quartic
{
	//イーズイン
	float EaseIn(float _elapseTime, float _initpos, float _differencePos, float _totalTim);
	//イーズアウト
	float EaseOut(float _elapseTime, float _initpos, float _differencePos, float _totalTim);
}
///////////////////////////////////////////

// 2D Vector
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}

	explicit Vector2(float _inX, float _inY)
		:x(_inX)
		, y(_inY)
	{}

	// Set both components in one line
	void Set(float _inX, float _inY)
	{
		x = _inX;
		y = _inY;
	}

	// Vector addition (a + b)
	friend Vector2 operator+(const Vector2& _A, const Vector2& _B)
	{
		return Vector2(_A.x + _B.x, _A.y + _B.y);
	}

	// Vector subtraction (a - b)
	friend Vector2 operator-(const Vector2& _A, const Vector2& _B)
	{
		return Vector2(_A.x - _B.x, _A.y - _B.y);
	}

	// Component-wise multiplication
	// (a.x * b.x, ...)
	friend Vector2 operator*(const Vector2& _A, const Vector2& _B)
	{
		return Vector2(_A.x * _B.x, _A.y * _B.y);
	}

	// Scalar multiplication
	friend Vector2 operator*(const Vector2& _Vec, float _scalar)
	{
		return Vector2(_Vec.x * _scalar, _Vec.y * _scalar);
	}

	// Scalar multiplication
	friend Vector2 operator*(float _scalar, const Vector2& _Vec)
	{
		return Vector2(_Vec.x * _scalar, _Vec.y * _scalar);
	}

	// Scalar *=
	Vector2& operator*=(float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		return *this;
	}

	// Vector +=
	Vector2& operator+=(const Vector2& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		return *this;
	}

	// Vector -=
	Vector2& operator-=(const Vector2& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// Normalize the provided vector
	static Vector2 Normalize(const Vector2& _Vec)
	{
		Vector2 temp = _Vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector2& _A, const Vector2& _B)
	{
		return (_A.x * _B.x + _A.y * _B.y);
	}

	// Lerp from A to B by f
	static Vector2 Lerp(const Vector2& _A, const Vector2& _B, float _f)
	{
		return Vector2(_A + _f * (_B - _A));
	}

	// Reflect V about (normalized) N
	static Vector2 Reflect(const Vector2& _V, const Vector2& _N)
	{
		return _V - 2.0f * Vector2::Dot(_V, _N) * _N;
	}

	// Transform vector by matrix
	static Vector2 Transform(const Vector2& _Vec, const class Matrix3& _Mat, float _w = 1.0f);

	static const Vector2 sZERO;
	static const Vector2 sUNIT_X;
	static const Vector2 sUNIT_Y;
	static const Vector2 sNEG_UNIT_X;
	static const Vector2 sNEG_UNIT_Y;
};

// 3D Vector
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	explicit Vector3(float _inX, float _inY, float _inZ)
		:x(_inX)
		, y(_inY)
		, z(_inZ)
	{}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all three components in one line
	void Set(float _inX, float _inY, float _inZ)
	{
		x = _inX;
		y = _inY;
		z = _inZ;
	}

	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& _A, const Vector3& _B)
	{
		return Vector3(_A.x + _B.x, _A.y + _B.y, _A.z + _B.z);
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& _A, const Vector3& _B)
	{
		return Vector3(_A.x - _B.x, _A.y - _B.y, _A.z - _B.z);
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& _Left, const Vector3& _Right)
	{
		return Vector3(_Left.x * _Right.x, _Left.y * _Right.y, _Left.z * _Right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& _Vec, float _scalar)
	{
		return Vector3(_Vec.x * _scalar, _Vec.y * _scalar, _Vec.z * _scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float _scalar, const Vector3& _Vec)
	{
		return Vector3(_Vec.x * _scalar, _Vec.y * _scalar, _Vec.z * _scalar);
	}

	friend Vector3 operator/(const Vector3& _Vec, float _scalar)
	{
		return Vector3(_Vec.x / _scalar, _Vec.y / _scalar, _Vec.z / _scalar);
	}

	friend bool operator!=(const Vector3& _Vec1, const Vector3& _Vec2)
	{
		bool clear = false;
		if (_Vec1.x != _Vec2.x)
		{
			clear = true;
		}
		if (_Vec1.y != _Vec2.y)
		{
			clear = true;

		}
		if (_Vec1.z != _Vec2.z)
		{
			clear = true;
		}
		return clear;
	}

	friend bool operator==(const Vector3& _Vec1, const Vector3& _Vec2)
	{
		bool clear = true;
		if (_Vec1.x != _Vec2.x)
		{
			clear = false;
		}
		if (_Vec1.y != _Vec2.y)
		{
			clear = false;

		}
		if (_Vec1.z != _Vec2.z)
		{
			clear = false;
		}
		return clear;
	}

	// Scalar *=
	Vector3& operator*=(float _scalar)
	{
		x *= _scalar;
		y *= _scalar;
		z *= _scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		z += _Right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		z -= _Right.z;
		return *this;
	}

	// Length squared of vector
	float LengthSq() const
	{
		return (x * x + y * y + z * z);
	}

	// Length of vector
	float Length() const
	{
		return (Math::Sqrt(LengthSq()));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
	}

	// Normalize the provided vector
	static Vector3 Normalize(const Vector3& _Vec)
	{
		Vector3 temp = _Vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vector3& _A, const Vector3& _B)
	{
		return (_A.x * _B.x + _A.y * _B.y + _A.z * _B.z);
	}

	// Cross product between two vectors (a cross b)
	static Vector3 Cross(const Vector3& _A, const Vector3& _B)
	{
		Vector3 temp;
		temp.x = _A.y * _B.z - _A.z * _B.y;
		temp.y = _A.z * _B.x - _A.x * _B.z;
		temp.z = _A.x * _B.y - _A.y * _B.x;
		return temp;
	}

	// Lerp from A to B by f
	static Vector3 Lerp(const Vector3& _A, const Vector3& _B, float _f)
	{
		return Vector3(_A + _f * (_B - _A));
	}

	// Reflect V about (normalized) N
	static Vector3 Reflect(const Vector3& _V, const Vector3& _N)
	{
		return _V - 2.0f * Vector3::Dot(_V, _N) * _N;
	}

	static Vector3 Transform(const Vector3& _Vec, const class Matrix4& _Mat, float _w = 1.0f);
	// This will transform the vector and renormalize the w component
	static Vector3 TransformWithPerspDiv(const Vector3& _Vec, const class Matrix4& _Mat, float _w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 Transform(const Vector3& _V, const class Quaternion& _Q);

	static const Vector3 sZERO;
	static const Vector3 sUNIT_X;
	static const Vector3 sUNIT_Y;
	static const Vector3 sUNIT_Z;
	static const Vector3 sNEG_UNIT_X;
	static const Vector3 sNEG_UNIT_Y;
	static const Vector3 sNEG_UNIT_Z;
	static const Vector3 sINFINITY;
	static const Vector3 sNEG_INFINITY;
};

// 3x3 Matrix
class Matrix3
{
public:
	float mat[3][3];

	Matrix3()
	{
		*this = Matrix3::sIDENTITY;
	}

	explicit Matrix3(float _inMat[3][3])
	{
		memcpy(mat, _inMat, 9 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication
	friend Matrix3 operator*(const Matrix3& _Left, const Matrix3& _Right)
	{
		Matrix3 retVal;
		// row 0
		retVal.mat[0][0] =
			_Left.mat[0][0] * _Right.mat[0][0] +
			_Left.mat[0][1] * _Right.mat[1][0] +
			_Left.mat[0][2] * _Right.mat[2][0];

		retVal.mat[0][1] =
			_Left.mat[0][0] * _Right.mat[0][1] +
			_Left.mat[0][1] * _Right.mat[1][1] +
			_Left.mat[0][2] * _Right.mat[2][1];

		retVal.mat[0][2] =
			_Left.mat[0][0] * _Right.mat[0][2] +
			_Left.mat[0][1] * _Right.mat[1][2] +
			_Left.mat[0][2] * _Right.mat[2][2];

		// row 1
		retVal.mat[1][0] =
			_Left.mat[1][0] * _Right.mat[0][0] +
			_Left.mat[1][1] * _Right.mat[1][0] +
			_Left.mat[1][2] * _Right.mat[2][0];

		retVal.mat[1][1] =
			_Left.mat[1][0] * _Right.mat[0][1] +
			_Left.mat[1][1] * _Right.mat[1][1] +
			_Left.mat[1][2] * _Right.mat[2][1];

		retVal.mat[1][2] =
			_Left.mat[1][0] * _Right.mat[0][2] +
			_Left.mat[1][1] * _Right.mat[1][2] +
			_Left.mat[1][2] * _Right.mat[2][2];

		// row 2
		retVal.mat[2][0] =
			_Left.mat[2][0] * _Right.mat[0][0] +
			_Left.mat[2][1] * _Right.mat[1][0] +
			_Left.mat[2][2] * _Right.mat[2][0];

		retVal.mat[2][1] =
			_Left.mat[2][0] * _Right.mat[0][1] +
			_Left.mat[2][1] * _Right.mat[1][1] +
			_Left.mat[2][2] * _Right.mat[2][1];

		retVal.mat[2][2] =
			_Left.mat[2][0] * _Right.mat[0][2] +
			_Left.mat[2][1] * _Right.mat[1][2] +
			_Left.mat[2][2] * _Right.mat[2][2];

		return retVal;
	}

	Matrix3& operator*=(const Matrix3& _Right)
	{
		*this = *this * _Right;
		return *this;
	}

	// Create a scale matrix with x and y scales
	static Matrix3 CreateScale(float _xScale, float _yScale)
	{
		float temp[3][3] =
		{
			{ _xScale, 0.0f, 0.0f },
		{ 0.0f, _yScale, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	static Matrix3 CreateScale(const Vector2& _ScaleVector)
	{
		return CreateScale(_ScaleVector.x, _ScaleVector.y);
	}

	// Create a scale matrix with a uniform factor
	static Matrix3 CreateScale(float _scale)
	{
		return CreateScale(_scale, _scale);
	}

	// Create a rotation matrix about the Z axis
	// theta is in radians
	static Matrix3 CreateRotation(float _theta)
	{
		float temp[3][3] =
		{
			{ Math::Cos(_theta), Math::Sin(_theta), 0.0f },
		{ -Math::Sin(_theta), Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(temp);
	}

	// Create a translation matrix (on the xy-plane)
	static Matrix3 CreateTranslation(const Vector2& _Trans)
	{
		float temp[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ _Trans.x, _Trans.y, 1.0f },
		};
		return Matrix3(temp);
	}

	static const Matrix3 sIDENTITY;
};

// 4x4 Matrix
class Matrix4
{
public:
	float mat[4][4];

	Matrix4()
	{
		*this = Matrix4::sIDENTITY;
	}

	explicit Matrix4(float _inMat[4][4])
	{
		memcpy(mat, _inMat, 16 * sizeof(float));
	}

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0][0]);
	}

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(const Matrix4& _A, const Matrix4& _B)
	{
		Matrix4 retVal;
		// row 0
		retVal.mat[0][0] =
			_A.mat[0][0] * _B.mat[0][0] +
			_A.mat[0][1] * _B.mat[1][0] +
			_A.mat[0][2] * _B.mat[2][0] +
			_A.mat[0][3] * _B.mat[3][0];

		retVal.mat[0][1] =
			_A.mat[0][0] * _B.mat[0][1] +
			_A.mat[0][1] * _B.mat[1][1] +
			_A.mat[0][2] * _B.mat[2][1] +
			_A.mat[0][3] * _B.mat[3][1];

		retVal.mat[0][2] =
			_A.mat[0][0] * _B.mat[0][2] +
			_A.mat[0][1] * _B.mat[1][2] +
			_A.mat[0][2] * _B.mat[2][2] +
			_A.mat[0][3] * _B.mat[3][2];

		retVal.mat[0][3] =
			_A.mat[0][0] * _B.mat[0][3] +
			_A.mat[0][1] * _B.mat[1][3] +
			_A.mat[0][2] * _B.mat[2][3] +
			_A.mat[0][3] * _B.mat[3][3];

		// row 1
		retVal.mat[1][0] =
			_A.mat[1][0] * _B.mat[0][0] +
			_A.mat[1][1] * _B.mat[1][0] +
			_A.mat[1][2] * _B.mat[2][0] +
			_A.mat[1][3] * _B.mat[3][0];

		retVal.mat[1][1] =
			_A.mat[1][0] * _B.mat[0][1] +
			_A.mat[1][1] * _B.mat[1][1] +
			_A.mat[1][2] * _B.mat[2][1] +
			_A.mat[1][3] * _B.mat[3][1];

		retVal.mat[1][2] =
			_A.mat[1][0] * _B.mat[0][2] +
			_A.mat[1][1] * _B.mat[1][2] +
			_A.mat[1][2] * _B.mat[2][2] +
			_A.mat[1][3] * _B.mat[3][2];

		retVal.mat[1][3] =
			_A.mat[1][0] * _B.mat[0][3] +
			_A.mat[1][1] * _B.mat[1][3] +
			_A.mat[1][2] * _B.mat[2][3] +
			_A.mat[1][3] * _B.mat[3][3];

		// row 2
		retVal.mat[2][0] =
			_A.mat[2][0] * _B.mat[0][0] +
			_A.mat[2][1] * _B.mat[1][0] +
			_A.mat[2][2] * _B.mat[2][0] +
			_A.mat[2][3] * _B.mat[3][0];

		retVal.mat[2][1] =
			_A.mat[2][0] * _B.mat[0][1] +
			_A.mat[2][1] * _B.mat[1][1] +
			_A.mat[2][2] * _B.mat[2][1] +
			_A.mat[2][3] * _B.mat[3][1];

		retVal.mat[2][2] =
			_A.mat[2][0] * _B.mat[0][2] +
			_A.mat[2][1] * _B.mat[1][2] +
			_A.mat[2][2] * _B.mat[2][2] +
			_A.mat[2][3] * _B.mat[3][2];

		retVal.mat[2][3] =
			_A.mat[2][0] * _B.mat[0][3] +
			_A.mat[2][1] * _B.mat[1][3] +
			_A.mat[2][2] * _B.mat[2][3] +
			_A.mat[2][3] * _B.mat[3][3];

		// row 3
		retVal.mat[3][0] =
			_A.mat[3][0] * _B.mat[0][0] +
			_A.mat[3][1] * _B.mat[1][0] +
			_A.mat[3][2] * _B.mat[2][0] +
			_A.mat[3][3] * _B.mat[3][0];

		retVal.mat[3][1] =
			_A.mat[3][0] * _B.mat[0][1] +
			_A.mat[3][1] * _B.mat[1][1] +
			_A.mat[3][2] * _B.mat[2][1] +
			_A.mat[3][3] * _B.mat[3][1];

		retVal.mat[3][2] =
			_A.mat[3][0] * _B.mat[0][2] +
			_A.mat[3][1] * _B.mat[1][2] +
			_A.mat[3][2] * _B.mat[2][2] +
			_A.mat[3][3] * _B.mat[3][2];

		retVal.mat[3][3] =
			_A.mat[3][0] * _B.mat[0][3] +
			_A.mat[3][1] * _B.mat[1][3] +
			_A.mat[3][2] * _B.mat[2][3] +
			_A.mat[3][3] * _B.mat[3][3];

		return retVal;
	}

	Matrix4& operator*=(const Matrix4& _Right)
	{
		*this = *this * _Right;
		return *this;
	}

	// Invert the matrix - super slow
	void Invert();

	// Get the translation component of the matrix
	Vector3 GetTranslation() const
	{
		return Vector3(mat[3][0], mat[3][1], mat[3][2]);
	}

	// Get the X axis of the matrix (forward)
	Vector3 GetXAxis() const
	{
		return Vector3::Normalize(Vector3(mat[0][0], mat[0][1], mat[0][2]));
	}

	// Get the Y axis of the matrix (left)
	Vector3 GetYAxis() const
	{
		return Vector3::Normalize(Vector3(mat[1][0], mat[1][1], mat[1][2]));
	}

	// Get the Z axis of the matrix (up)
	Vector3 GetZAxis() const
	{
		return Vector3::Normalize(Vector3(mat[2][0], mat[2][1], mat[2][2]));
	}

	// Extract the scale component from the matrix
	Vector3 GetScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0][0], mat[0][1], mat[0][2]).Length();
		retVal.y = Vector3(mat[1][0], mat[1][1], mat[1][2]).Length();
		retVal.z = Vector3(mat[2][0], mat[2][1], mat[2][2]).Length();
		return retVal;
	}

	// Create a scale matrix with x, y, and z scales
	static Matrix4 CreateScale(float _xScale, float _yScale, float _zScale)
	{
		float temp[4][4] =
		{
			{ _xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, _yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _zScale, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateScale(const Vector3& _ScaleVector)
	{
		return CreateScale(_ScaleVector.x, _ScaleVector.y, _ScaleVector.z);
	}

	// Create a scale matrix with a uniform factor
	static Matrix4 CreateScale(float _scale)
	{
		return CreateScale(_scale, _scale, _scale);
	}

	// Rotation about x-axis
	static Matrix4 CreateRotationX(float _theta)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f , 0.0f },
		{ 0.0f, Math::Cos(_theta), Math::Sin(_theta), 0.0f },
		{ 0.0f, -Math::Sin(_theta), Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about y-axis
	static Matrix4 CreateRotationY(float _theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(_theta), 0.0f, -Math::Sin(_theta), 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ Math::Sin(_theta), 0.0f, Math::Cos(_theta), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Rotation about z-axis
	static Matrix4 CreateRotationZ(float _theta)
	{
		float temp[4][4] =
		{
			{ Math::Cos(_theta), Math::Sin(_theta), 0.0f, 0.0f },
		{ -Math::Sin(_theta), Math::Cos(_theta), 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(temp);
	}

	// Create a rotation matrix from a quaternion
	static Matrix4 CreateFromQuaternion(const class Quaternion& _Q);

	static Matrix4 CreateTranslation(const Vector3& _Trans)
	{
		float temp[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ _Trans.x, _Trans.y, _Trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateLookAt(const Vector3& _Eye, const Vector3& _Target, const Vector3& _Up)
	{
		Vector3 zaxis = Vector3::Normalize(_Target - _Eye);
		Vector3 xaxis = Vector3::Normalize(Vector3::Cross(_Up, zaxis));
		Vector3 yaxis = Vector3::Normalize(Vector3::Cross(zaxis, xaxis));
		Vector3 trans;
		trans.x = -Vector3::Dot(xaxis, _Eye);
		trans.y = -Vector3::Dot(yaxis, _Eye);
		trans.z = -Vector3::Dot(zaxis, _Eye);

		float temp[4][4] =
		{
			{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
		{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
		{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
		{ trans.x, trans.y, trans.z, 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreateOrtho(float _width, float _height, float _near, float _far)
	{
		float temp[4][4] =
		{
			{ 2.0f / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f / (_far - _near), 0.0f },
		{ 0.0f, 0.0f, _near / (_near - _far), 1.0f }
		};
		return Matrix4(temp);
	}

	static Matrix4 CreatePerspectiveFOV(float _fovY, float _width, float _height, float _near, float _far)
	{
		float yScale = Math::Cot(_fovY / 2.0f);
		float xScale = yScale * _height / _width;
		float temp[4][4] =
		{
			{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, _far / (_far - _near), 1.0f },
		{ 0.0f, 0.0f, -_near * _far / (_far - _near), 0.0f }
		};
		return Matrix4(temp);
	}

	// Create "Simple" View-Projection Matrix from Chapter 6
	static Matrix4 CreateSimpleViewProj(float _width, float _height)
	{
		float temp[4][4] =
		{
			{ 2.0f / _width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / _height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f }
		};
		return Matrix4(temp);
	}
	// 転置行列
	void Transpose();

	static const Matrix4 sIDENTITY;
};

// (Unit) Quaternion
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::sIDENTITY;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float _inX, float _inY, float _inZ, float _inW)
	{
		Set(_inX, _inY, _inZ, _inW);
	}

	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& _Axis, float _angle)
	{
		float scalar = Math::Sin(_angle / 2.0f);
		x = _Axis.x * scalar;
		y = _Axis.y * scalar;
		z = _Axis.z * scalar;
		w = Math::Cos(_angle / 2.0f);
	}

	// Directly set the internal components
	void Set(float _inX, float _inY, float _inZ, float _inW)
	{
		x = _inX;
		y = _inY;
		z = _inZ;
		w = _inW;
	}

	void Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float LengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	// Normalize the provided quaternion
	static Quaternion Normalize(const Quaternion& _Q)
	{
		Quaternion retVal = _Q;
		retVal.Normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion Lerp(const Quaternion& _A, const Quaternion& _B, float _f)
	{
		Quaternion retVal;
		retVal.x = Math::Lerp(_A.x, _B.x, _f);
		retVal.y = Math::Lerp(_A.y, _B.y, _f);
		retVal.z = Math::Lerp(_A.z, _B.z, _f);
		retVal.w = Math::Lerp(_A.w, _B.w, _f);
		retVal.Normalize();
		return retVal;
	}

	static float Dot(const Quaternion& _A, const Quaternion& _B)
	{
		return _A.x * _B.x + _A.y * _B.y + _A.z * _B.z + _A.w * _B.w;
	}

	// Spherical Linear Interpolation
	static Quaternion Slerp(const Quaternion& _A, const Quaternion& _B, float _f)
	{
		float rawCosm = Quaternion::Dot(_A, _B);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float Omega = Math::Acos(cosom);
			const float InvSin = 1.f / Math::Sin(Omega);
			scale0 = Math::Sin((1.f - _f) * Omega) * InvSin;
			scale1 = Math::Sin(_f * Omega) * InvSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - _f;
			scale1 = _f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * _A.x + scale1 * _B.x;
		retVal.y = scale0 * _A.y + scale1 * _B.y;
		retVal.z = scale0 * _A.z + scale1 * _B.z;
		retVal.w = scale0 * _A.w + scale1 * _B.w;
		retVal.Normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion Concatenate(const Quaternion& _Q, const Quaternion& _P)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(_Q.x, _Q.y, _Q.z);
		Vector3 pv(_P.x, _P.y, _P.z);
		Vector3 newVec = _P.w * qv + _Q.w * pv + Vector3::Cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = _P.w * _Q.w - Vector3::Dot(pv, qv);

		return retVal;
	}

	//回転行列をクォータニオンにする
	static Quaternion MatrixToQuaternion(Matrix4 mat) {
		Quaternion q;

		float s;
		float tr = mat.mat[0][0] + mat.mat[1][1] + mat.mat[2][2] + 1.0f;
		if (tr >= 1.0f) {
			s = 0.5f / sqrt(tr);
			q.w = 0.25f / s;
			q.x = (mat.mat[1][2] - mat.mat[2][1]) * s;
			q.y = (mat.mat[2][0] - mat.mat[0][2]) * s;
			q.z = (mat.mat[0][1] - mat.mat[1][0]) * s;
			return q;
		}
		else {
			float max;
			if (mat.mat[1][1] > mat.mat[2][2]) {
				max = mat.mat[1][1];
			}
			else {
				max = mat.mat[2][2];
			}

			if (max < mat.mat[0][0]) {
				s = sqrt(mat.mat[0][0] - (mat.mat[1][1] + mat.mat[2][2]) + 1.0f);
				float x = s * 0.5f;
				s = 0.5f / s;
				q.x = x;
				q.y = (mat.mat[0][1] + mat.mat[1][0]) * s;
				q.z = (mat.mat[2][0] + mat.mat[0][2]) * s;
				q.w = (mat.mat[1][2] - mat.mat[2][1]) * s;
				return q;
			}
			else if (max == mat.mat[1][1]) {
				s = sqrt(mat.mat[1][1] - (mat.mat[2][2] + mat.mat[0][0]) + 1.0f);
				float y = s * 0.5f;
				s = 0.5f / s;
				q.x = (mat.mat[0][1] + mat.mat[1][0]) * s;
				q.y = y;
				q.z = (mat.mat[1][2] + mat.mat[2][1]) * s;
				q.w = (mat.mat[2][0] - mat.mat[0][2]) * s;
				return q;
			}
			else {
				s = sqrt(mat.mat[2][2] - (mat.mat[0][0] + mat.mat[1][1]) + 1.0f);
				float z = s * 0.5f;
				s = 0.5f / s;
				q.x = (mat.mat[2][0] + mat.mat[0][2]) * s;
				q.y = (mat.mat[1][2] + mat.mat[2][1]) * s;
				q.z = z;
				q.w = (mat.mat[0][1] - mat.mat[1][0]) * s;
				return q;
			}
		}
	}

	static const Quaternion sIDENTITY;
};

namespace Color
{
	static const Vector3 sBLACK(0.0f, 0.0f, 0.0f);
	static const Vector3 sWHITE(1.0f, 1.0f, 1.0f);
	static const Vector3 sRED(1.0f, 0.0f, 0.0f);
	static const Vector3 sGREEN(0.0f, 1.0f, 0.0f);
	static const Vector3 sBLUE(0.0f, 0.0f, 1.0f);
	static const Vector3 sYELLOW(1.0f, 1.0f, 0.0f);
	static const Vector3 sLIGHT_YELLOW(1.0f, 1.0f, 0.88f);
	static const Vector3 sLIGHT_BLUE(0.68f, 0.85f, 0.9f);
	static const Vector3 sLIGHT_PINK(1.0f, 0.71f, 0.76f);
	static const Vector3 sLIGHT_GREEN(0.56f, 0.93f, 0.56f);
}