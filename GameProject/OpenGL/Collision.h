/*
@file  Collision.h
@brief �����`����A�O�p�`���̃I�u�W�F�N�g�錾
*/

/*
@brief �v���v���Z�b�T
*/
#pragma once

//����
struct LineSegment
{
	/*
	@param	_Start �����̊J�n�n�_�̃|�W�V����
	@param	_End �����̏I���n�_�̃|�W�V����
	*/
    LineSegment(const Vector3& _Start, const Vector3& _End);
	
	/*
	@fn		������̓_��Ԃ�
	@param	_t ���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����(Vector3�^)
	*/
	Vector3 PointOnSegment(float _t) const;

	/*
	@fn		�_�Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	_Point �C�ӂ̓_�̃|�W�V����
	@return �ŒZ����(float�^)
	*/
    float MinDistanceSquared(const Vector3& _Point)const;

	/*
	@fn		�����Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	_Line1 ���肷������̍\���̂P
	@param	_Line2 ���肷������̍\���̂Q
	@return �ŒZ����(float�^)
	*/
    static float MinDistanceSquared(const LineSegment& _Line1,const LineSegment& _Line2);

	//�����̊J�n�n�_
    Vector3 m_start;
	//�����̏I���n�_
    Vector3 m_end;
};

//����
struct Plane
{
	/*
	@param	_Normal ���ʂ̖@���x�N�g��
	@param	_distance ���ʂƌ��_�̕������ŒZ����
	*/
    Plane(const Vector3& _Normal, float _distance);

	/*
	@param	_Vec1 ���ʏ�̓_1
	@param	_Vec2 ���ʏ�̓_2
	@param	_Vec3 ���ʏ�̓_3
	*/
    Plane(const Vector3& _Vec1, const Vector3& _Vec2, const Vector3& _Vec3);

	/*
	@fn		�_�ƕ��ʂ̍ŒZ������Ԃ�
	@param	_Point �C�ӂ̓_�̃|�W�V����
	@return �������ŒZ����(float�^)
	*/
    float SignedDistance(const Vector3& _Point);

	//���ʂ̖@���x�N�g��
    Vector3 m_normal;
	//���ʂƌ��_�̕������ŒZ����
    float m_distance;
};

//��
struct Sphere
{
	/*
	@param	_Center ���̂̒��S���W
	@param	_Radius ���̂̔��a
	*/
    Sphere(const Vector3& _Center, const float _Radius);
    
	/*
	@fn		���̂ɓ_���܂܂�Ă��邩�ǂ���
	@param	_Point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector3& _Point)const;

	//���̂̒��S���W
    Vector3 m_center;
	//���̂̔��a
    float m_radius;
};

//�����s�o�E���f�B���O�{�b�N�X(Axis-Aligned Bounding Box)
struct AABB
{
	/*
	@param	_Min �ŏ���x,y,z�̒l�̃|�W�V����
	@param	_Max �ő��x,y,z�̒l�̃|�W�V����
	*/
    AABB(const Vector3& _Min,const Vector3& _Max);

	/*
	@fn		�ŏ��l�ƍő�l���e�������ƂɍX�V����
	@param	_Point �C�ӂ̓_�̃|�W�V����
	*/
    void UpdateMinMax(const Vector3& _Point);

	/*
	@fn		�����蔻��{�b�N�X�̉�]
	@param	_Quaternion ��]���Ɖ�]�\���l
	*/
    void Rotate(const Quaternion& _Quaternion);
    
	/*
	@fn	�{�b�N�X�ɓ_���܂܂�Ă��邩�ǂ���
	@param	_Point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector3& _Point)const;
    
	/*
	@fn		�_�ƃ{�b�N�X�̍ŒZ������Ԃ�
	@param	_Point �C�ӂ̓_
	@return �ŒZ����
	*/
	float MinDistanceSquared(const Vector3& _Point)const;

	/*
	@fn		�ŏ��l�ƍő�l��������
	@param	_Point �C�ӂ̓_
	*/
	void InitMinMax(const Vector3& _Point) { m_min = m_max = _Point; };

	//�ŏ���x,y,z�̒l�̃|�W�V����
    Vector3 m_min;
	//�ő��x,y,z�̒l�̃|�W�V����
    Vector3 m_max;
};

//�L���o�E���f�B���O�{�b�N�X�iOriented Bounding Box�j
//������
struct OBB
{
	//���S�̍��W
    Vector3 m_center;
	//��]�N�H�[�^�j�I��
    Quaternion m_rotation;
	//�{�b�N�X�̍L����i���A�����A���s���j
    Vector3 m_extents;
};

//�J�v�Z��
struct Capsule
{
	/*
	@param	_Start �n�_�ƂȂ�_�̍��W
	@param	_End �I�_�ƂȂ�_�̍��W
	@param	_radius �J�v�Z���̔��a
	*/
    Capsule(const Vector3& _Start,const Vector3& _End,float _radius);

	/*
	@fn	�J�v�Z���̎n�_�ƏI�_�̐�����̓_��Ԃ�
	@param	_t ���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����(Vector3�^)
	*/
    Vector3 PointOnSegment(float _t)const;

	/*
	@fn	�J�v�Z���ɓ_���܂܂�Ă��邩�ǂ���
	@param	_Point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
    bool Contains(const Vector3& _Point)const;

	//�J�v�Z�����\���������
    LineSegment m_segment;
	//�J�v�Z���̔��a
    float m_radius;
};

//�ʃ|���S��
struct ConvexPolygon
{
	/*
	@fn		�Q�����̃|���S���ɓ_���܂܂�Ă��邩�ǂ���
	@param	_Point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
    bool Contains(const Vector2& _Point)const;

	//���_�̉ϒ��R���e�i
    std::vector<Vector2> m_vertices;
};

/*
@fn	���Ƌ��̓����蔻��
@param	_Sphere1 ���̍\���̂P
@param	_Sphere2 ���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Sphere& _Sphere1,const Sphere& _Sphere2);

/*
@fn		�{�b�N�X�ƃ{�b�N�X�̓����蔻��
@param	_AABB1 �{�b�N�X�̍\���̂P
@param	_AABB2 �{�b�N�X�̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const AABB& _AABB1, const AABB& _AABB2);

/*
@fn		�J�v�Z���ƃJ�v�Z���̓����蔻��
@param	_Capsule1 �J�v�Z���̍\���̂P
@param	_Capsule2 �J�v�Z���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Capsule& _Capsule1, const Capsule& _Capsule2);

/*
@fn	���ƃ{�b�N�X�̓����蔻��
@param	_Sphere ���̍\����
@param	_AABB �{�b�N�X�̍\����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Sphere& _Sphere, const AABB& _AABB);

/*
@fn	�����Ƌ��̓����蔻��
@param	_Line �����̍\����
@param	_Sphere ���̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _Line, const Sphere& _Sphere, float& _outT);

/*
@fn	�����ƕ��ʂ̓����蔻��
@param	_Line�@�����̍\����
@param	_Plane�@���ʂ̍\����
@param	_outT�@�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _Line, const Plane& _Plane, float& _outT);

/*
@fn	�����ƃ{�b�N�X�̓����蔻��
@param	_Line �����̍\����
@param	_AABB �{�b�N�X�̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@param	_outNorm �����̎n�_����ڐG�����ʂ̖@���x�N�g�����i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _Line, const AABB& _AABB, float& _outT,
    Vector3& _outNorm);

/*
@fn	���X�C�[�v�̓����蔻��
@param	_Sphere1 �P�t���[���O�̋��P�̍\����
@param	_Sphere2 ���݂̃t���[���̋��P�̍\����
@param	_Sphere3 �P�t���[���O�̋��Q�̍\����
@param	_Sphere4 ���݂̃t���[���̋��Q�̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool SweptSphere(const Sphere& _Sphere1, const Sphere& _Sphere2,
    const Sphere& _Sphere3, const Sphere& _Sphere4, float& _outT);
