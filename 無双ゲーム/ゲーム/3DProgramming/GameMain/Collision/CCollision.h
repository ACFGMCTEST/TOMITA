#ifndef COLLISION_H
#define COLLISION_H

#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector2.h"
#include "../Vector/CVector3.h"
#include "../Vector/CVector4.h"

#include "stdio.h"
#include "../Task/CTask.h"
/*�����蔻��̃^�C�v�C���N���[�h*/
#include "ColType\COBB.h"
#include "ColType\CColSphere.h"
#include "ColType\CColTriangle.h"
#include "ColType\CColCapsule.h"
#include "ColType\CColLine.h"


//
///*�����蔻��N���X�@��*/
//class CColWall :public CCollBase
//{
//public:
//	CVector3 mNormal;		//����
//};

//�Փ˔���N���X
class CCollision {
private:
	//separate����ɓ��e����OBB���m���ڐG���Ă��邩���ׂ�
	static bool CompareLength(const COBB &A, const COBB &B, const CVector3 &distVec, const CVector3 &separate);
public:
	//�����m�̏Փ˔���
	static bool CollisionShpere(const CColSphere &sphereA, const CColSphere &sphereB);
	//�J�v�Z�����m�̏Փ�
	static bool CollisionCapsule(const CColCapsule *capsuleA, const CColCapsule *capsuleB);

	//OBB���m�̏Փ˔���
	static bool CollisionOBB(const COBB &A, const COBB &B);
	//AABB���m�̏Փ˔���
	static bool CollisionAABB(const CVector3 &minA, const CVector3 &maxA, const CVector3 &minB, const CVector3 &maxB);

	//�_c���O�p�`�|���S����ɂ��邩���ׂ�
	static bool TriangleIntersect(const CVector3 &c, const CVector3 &v0, const  CVector3 &v1, const CVector3 &v2, const CVector3 &n);
	static bool TriangleIntersect(const CVector3 &c, const CVector3 &v0, const  CVector3 &v1, const CVector3 &v2);
	//�����ƎO�p�`�|���S���Ƃ̏Փ˔���
	/*
	corss = �ڒn��
	p1 = ���̏���
	p2 = ���̏I���
	v0 = �O�p�`�̓_1
	v1 = �O�p�`�̓_2
	v2 = �O�p�`�̓_3
	pt = ����
	*/
	static bool IntersectTriangleRay(CVector3 *corss, const CVector3 &p1, const  CVector3 &p2, const CVector3& v0, const  CVector3 &v1, const  CVector3 &v2, float *pt);
	//point����߂�v0��v1����̓_�𒲂ׂ�
	static CVector3 PointOnLineSegmentNearestPoint(const CVector3 &v0, const CVector3 &v1, const CVector3 &point);
	static CVector3 PointOnLineSegmentNearestPoint2(const CVector3 &v0, const CVector3 &v1, const CVector3 &point);

	static CVector2 PointOnLineSegmentNearestPoint(const CVector2 &v0, const CVector2 &v1, const CVector2 &point);
	//�O�p�|���S���Ƌ��̏Փ˔���
	static bool IntersectTriangleSphere(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross = 0, float *length = 0);
	static bool IntersectTriangleSphere2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross = 0, float *length = 0, CVector3 *adjust = 0);
	//�O�p�|���S���ƃJ�v�Z���̏Փ˔���
	static bool IntersectTriangleCapsule(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross = 0, float *length = 0);
	static bool IntersectTriangleCapsule2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross = 0, float *length = 0, CVector3 *n = 0);
	static bool IntersectTriangleCapsule3(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *adjust = 0, CVector3 *cross = 0, float *length = 0);

	//2�����Ԃ̋���
	static float DistanceLine(const CVector3 &s1, const CVector3 &e1, const CVector3 &s2, const CVector3 &e2, CVector3 *cross = NULL, CVector3 *c2 = NULL);

	//�_�Ɛ��̋���
	static float DistancePointToLine(const CVector3 &v0, const CVector3 &v1, const CVector3 &p);
	//�_�Ɛ��̋���
	static float DistancePointToLineSq(const CVector3 &v0, const CVector3 &v1, const CVector3 &p);


	/*�����蔻��̊֐�(����BOX�̔���)*/
	static bool CollSphereBox(CColSphere sphere, COBB &box);


};
#endif