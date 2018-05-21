#include "CCollision.h"
#include "math.h"


inline float min(float a, float b) {
	return (a<b) ? a : b;
}



/*�����m�̓����蔻��*/
bool CCollision::CollisionShpere(const CColSphere &sphereA,const CColSphere &sphereB)
{
	CVector3 v = sphereB.mPos - sphereA.mPos;
	return (v.LengthSq() <(sphereA.mRadius + sphereB.mRadius)*(sphereA.mRadius + sphereB.mRadius));
}
//�J�v�Z�����m�̏Փ�
bool CCollision::CollisionCapsule(const CColCapsule *capsuleA, const CColCapsule *capsuleB){

	CVector3 topA = capsuleA->mV[0].Transeform(*capsuleA->mpCombinedMatrix);
	CVector3 topB = capsuleB->mV[0].Transeform(*capsuleB->mpCombinedMatrix);
	CVector3 BottomA = capsuleA->mV[1].Transeform(*capsuleA->mpCombinedMatrix);
	CVector3 BottomB = capsuleB->mV[1].Transeform(*capsuleB->mpCombinedMatrix);

	//printf("�G�l�~�[:top(%f,%f,%f),bottom(%f,%f,%f)\n", topB.x, topB.y, topB.z, BottomB.x, BottomB.y, BottomB.z);

	//���̒��S�ƃJ�v�Z���̐����̋������v�Z
	float distance = DistanceLine(topA, BottomA, topB, BottomB, NULL, NULL);
	//���a�̘a�̓����v�Z
	float radiusSum = capsuleA->mRadius + capsuleB->mRadius;
	float radiusSumSQ = radiusSum * radiusSum;
	//���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distance < radiusSumSQ){
		return true;
	}
	else{
		return false;
	}

	///*���̗p*/
	//CColSphere TopColA(capsuleA.mRadius, capsuleA.mV[0], capsuleA.mpCombinedMatrix);
	//CColSphere TopColB(capsuleB.mRadius, capsuleB.mV[0], capsuleB.mpCombinedMatrix);
	//CColSphere BottomColA(capsuleA.mRadius, capsuleA.mV[1], capsuleA.mpCombinedMatrix);
	//CColSphere BottomColB(capsuleB.mRadius, capsuleB.mV[1], capsuleB.mpCombinedMatrix);
	////AABB�p
	//CVector3 TopPosA = CVector3(capsuleA.mV[0].x + capsuleA.mRadius, capsuleA.mV[0].y, capsuleA.mV[0].z + capsuleA.mRadius);
	//CVector3 TopPosB = CVector3(capsuleB.mV[0].x + capsuleB.mRadius, capsuleB.mV[0].y, capsuleB.mV[0].z + capsuleB.mRadius);
	//CVector3 BottomPosB = CVector3(capsuleA.mV[1].x + capsuleA.mRadius, capsuleA.mV[1].y, capsuleA.mV[1].z + capsuleA.mRadius);
	//CVector3 BottomPosB = CVector3(capsuleB.mV[1].x + capsuleB.mRadius, capsuleB.mV[1].y, capsuleB.mV[1].z + capsuleB.mRadius);


	//return (CCollision::CollisionShpere(TopColA, TopColB) ||
	//	CCollision::CollisionShpere(TopColA, BottomColB) ||
	//	CCollision::CollisionShpere(BottomColA, TopColB) ||
	//	CCollision::CollisionShpere(BottomColA, BottomColB) ||
	//	CCollision::CollisionAABB()
	//	) ;

}

bool CCollision::TriangleIntersect(const CVector3 &c, const CVector3 &v0, const CVector3 &v1, const  CVector3 &v2, const CVector3 &n){
	if (CVector3::Dot(CVector3::Cross(v1 - v0, c - v0), n)<0) return false;
	if (CVector3::Dot(CVector3::Cross(v2 - v1, c - v1), n)<0) return false;
	if (CVector3::Dot(CVector3::Cross(v0 - v2, c - v2), n)<0) return false;
	return true;
}

bool CCollision::TriangleIntersect(const CVector3 &c, const CVector3 &v0, const CVector3 &v1, const  CVector3 &v2){
	CVector3 n0 = CVector3::Cross(v1 - v0, c - v0);
	CVector3 n1 = CVector3::Cross(v2 - v1, c - v1);
	CVector3 n2 = CVector3::Cross(v0 - v2, c - v2);
	if (CVector3::Dot(n0, n1)<0) return false;
	if (CVector3::Dot(n1, n2)<0) return false;
	if (CVector3::Dot(n2, n0)<0) return false;
	return true;
}


//�����ƎO�p�`�|���S���Ƃ̏Փ˔���
bool CCollision::IntersectTriangleRay(CVector3 *corss, const CVector3 &p1, const CVector3 &p2, const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, float *pt) {
	CVector3 e1, e2, normal, pv1, pv2;

	e1 = v1 - v0;
	e2 = v2 - v0;

	//�ʂ̖@�������߂�
	normal = CVector3::Cross(e1, e2).GetNormalize();

	//�n�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	pv1 = p1 - v0;
	//�I�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	pv2 = p2 - v0;

	//�|���S���̖@���Ƃ̓��ς����߂�
	float d1 = CVector3::Dot(pv1, normal);
	float d2 = CVector3::Dot(pv2, normal);

	//�|���S�����ђʂ��Ă��Ȃ�
	if (d1*d2>0) return false;

	//�n�_����|���S���܂ł̋����Ɛ����̒����̔䗦�����߂�
	//�ڒn�n�_���o���̂Ɏg�p����
	float t = d1 / (d1 - d2);
	if (*pt < t) return false;

	//������ђʂ��Ă���ꍇ�͏Փ˂��Ă��Ȃ����Ƃɂ���
	if (t<0) return false;

	//�����ƕ��ʂ̐ڒn�n�_�����߂�
	CVector3 c = p1 + (p2 - p1)*t;

	//�ڒn�n�_���O�p�`�|���S���ォ���ׂ�
	if (!TriangleIntersect(c, v0, v1, v2, normal)) return false;

	*pt = t;
	*corss = c;

	return true;
}

CVector3 CCollision::PointOnLineSegmentNearestPoint(const CVector3 &v0, const CVector3 &v1, const CVector3 &point){
	CVector3 V = v1 - v0;
	float a = V.x*V.x + V.y*V.y + V.z*V.z;
	//�����̎n�_�ƏI�_�������ꏊ
	if (a == 0) return v0;
	CVector3 VP = point - v0;
	float b = CVector3::Dot(V, VP);
	float t = b / a;
	//v0���ɉ����ꍇ�͋߂��_��V0��
	if (t<0) return v0;
	//V1���ɉ����ꍇ�͋߂��_��V1��
	if (t>1) return v1;
	//t=<1 t>=0 �̏ꍇ�͐�����ɋ߂��_������ 
	return v0 + V*t;
}

CVector3 CCollision::PointOnLineSegmentNearestPoint2(const CVector3 &v0, const CVector3 &v1, const CVector3 &point){
	CVector3 V = v1 - v0;
	float a = V.length();
	//�����̎n�_�ƏI�_�������ꏊ
	if (a == 0) return v0;
	CVector3 VP = point - v0;
	float b = CVector3::Dot(V, VP);
	float t = b / a;
	//v0���ɉ����ꍇ�͋߂��_��V0��
	if (t<0) return v0;
	//V1���ɉ����ꍇ�͋߂��_��V1��
	if (t>1) return v1;
	//t=<1 t>=0 �̏ꍇ�͐�����ɋ߂��_������ 
	return v0 + V*t;
}

CVector2 CCollision::PointOnLineSegmentNearestPoint(const CVector2 &v0, const CVector2 &v1, const CVector2 &point){
	CVector2 V = v1 - v0;
	float a = V.x*V.x + V.y*V.y;
	//�����̎n�_�ƏI�_�������ꏊ
	if (a == 0) return v0;
	CVector2 VP = v0 - point;
	float b = CVector2::Dot(V, VP);
	float t = -(b / a);
	//v0���ɉ����ꍇ�͋߂��_��V0��
	if (t<0) return v0;
	//V1���ɉ����ꍇ�͋߂��_��V1��
	if (t>1) return v1;
	//t=<1 t>=0 �̏ꍇ�͐�����ɋ߂��_������ 
	return v0 + V*t;
}

//-----------------------------------------------------------------------------
bool CCollision::IntersectTriangleSphere(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross, float *length)
{
	CVector3 V1(v1 - v0);
	CVector3 V2(v2 - v1);
	CVector3 N(CVector3::Cross(V1, V2).GetNormalize());

	CVector3 V = center - v0;
	//���ʂƓ_�̋��������߂�
	float Dist = CVector3::Dot(V, N);

	//���̔��a��藣��Ă���ꍇ�͐ڐG����
	if (abs(Dist) > radius) return false;

	//�_���畽�ʏ�ɐ����ɉ��낵���n�_�����߂�
	CVector3 Point = center - (N * Dist);


	//��L�̓_���O�p�`�|���S�����Ȃ�ڐG���Ă���
	if (TriangleIntersect(Point, v0, v1, v2, N)) {
		if (cross) *cross = Point;
		if (length) *length = Dist;
		return true;
	}

	//�e�ӂɋ����������Ă���\��������
	//�P�ӂ��Ƃɋ��ƕӂ̍ŒZ���������߂�

	//�ŒZ����
	float l;
	//�ŒZ�ڐG�n�_
	CVector3 c;

	//������r�p
	float LengthSq;

	//�ӂP(v0��v1)
	Point = PointOnLineSegmentNearestPoint(v0, v1, center);
	LengthSq = (center - Point).LengthSq();
	l = LengthSq;
	c = Point;

	//�ӂQ(v1��v2)
	Point = PointOnLineSegmentNearestPoint(v1, v2, center);
	LengthSq = (center - Point).LengthSq();
	if (l>LengthSq) {
		l = LengthSq;
		c = Point;
	}

	//�ӂR(v2��v0)
	Point = PointOnLineSegmentNearestPoint(v2, v0, center);
	LengthSq = (center - Point).LengthSq();
	if (l>LengthSq) {
		l = LengthSq;
		c = Point;
	}

	//�ŒZ�������m��
	if (length) *length = sqrt(l);
	//�ŒZ�n�_���m��
	if (cross) *cross = c;

	return (*length <= radius);
}

bool CCollision::IntersectTriangleSphere2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross, float *length, CVector3 *adjust)
{
	float len = 0.0f;
	CVector3 V1(v1 - v0);
	CVector3 V2(v2 - v1);
	CVector3 N(CVector3::Cross(V1, V2).GetNormalize());
	if (adjust) *adjust = N;

	CVector3 V = center - v0;
	//���ʂƓ_�̋��������߂�
	float Dist = CVector3::Dot(V, N);

	//���̔��a��藣��Ă���ꍇ�͐ڐG����
	if (abs(Dist) > radius) return false;

	//�_���畽�ʏ�ɐ����ɉ��낵���n�_�����߂�
	CVector3 Point = center - (N * Dist);


	//��L�̓_���O�p�`�|���S�����Ȃ�ڐG���Ă���
	if (TriangleIntersect(Point, v0, v1, v2, N)) {
		if (cross) *cross = Point;
		len = radius - Dist;
		if (length)
			//*length = Dist;
			*length = len;
		if (adjust) *adjust = *adjust * len;
		return true;
	}

	//�e�ӂɋ����������Ă���\��������
	//�P�ӂ��Ƃɋ��ƕӂ̍ŒZ���������߂�

	//�ŒZ����
	float l;
	//�ŒZ�ڐG�n�_
	CVector3 c;

	//������r�p
	float LengthSq;

	//�ӂP(v0��v1)
	Point = PointOnLineSegmentNearestPoint(v0, v1, center);
	LengthSq = (center - Point).LengthSq();
	l = LengthSq;
	c = Point;

	//�ӂQ(v1��v2)
	Point = PointOnLineSegmentNearestPoint(v1, v2, center);
	LengthSq = (center - Point).LengthSq();
	if (l > LengthSq) {
		l = LengthSq;
		c = Point;
	}

	//�ӂR(v2��v0)
	Point = PointOnLineSegmentNearestPoint(v2, v0, center);
	LengthSq = (center - Point).LengthSq();
	if (l > LengthSq) {
		l = LengthSq;
		c = Point;
	}

	//�ŒZ�������m��
	len = sqrt(l);
	if (length) *length = len;
	//�ŒZ�n�_���m��
	if (cross) *cross = c;

	if (adjust) *adjust = CVector3();
	if (len <= radius) {
		//
		if (length)
			*length = 0.0f;
		return true;
	}
	else {
		return false;
	}
}


bool CCollision::IntersectTriangleCapsule(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross, float *length){
	CVector3 V(top - bottom);
	CVector3  VP;
	float Dist = 1e10, d;

	//�|���S���̖@�������߂�
	CVector3 N(CVector3::Cross(v1 - v0, v2 - v0).GetNormalize());

	//�n�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV1 = top - v0;
	//�I�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV2 = bottom - v0;

	//�|���S���̖@���Ƃ̓��ς����߂�
	float d1 = CVector3::Dot(PV1, N);
	float d2 = CVector3::Dot(PV2, N);

	if (d1*d2<0) {
		//�ђʂ��Ă���ꍇ�͐��ƃ|���S���̔�����s��
		if (IntersectTriangleRay(cross, top + CVector3(0, radius, 0), bottom + CVector3(0, -radius, 0), v0, v1, v2, &Dist)) {
			if (length) {
				CVector3 vt = (*cross - top);
				CVector3 vb = (*cross - bottom);
				//�ђʓ_�܂ł̋��������߂�
				float lt = (*cross - top).LengthSq();
				float lb = (*cross - bottom).LengthSq();
				if (lt < lb) {
					//					*length = sqrt(lt);
					*length = N.Dot(vt);
					*cross = N;
				}
				else {
					//					*length = sqrt(lb);
					*length = N.Dot(vb);
					*cross = N;
				}
			}
			//			*cross = N;
			return true;
		}
	}

	d1 = abs(d1);
	d2 = abs(d2);
	//���ʏ�̓_�Ƃ̍ŒZ�n�_�����߂�
	CVector3 C1(top - N*d1);
	CVector3 C2(bottom - N*d2);
	//�_�����ʏ�ɂȂ��ꍇ�͖����A��̕ӂƂ̐ڐG�Œ��ׂ�
	if (!TriangleIntersect(C1, v0, v1, v2, N)) d1 = 1e10;
	if (!TriangleIntersect(C2, v0, v1, v2, N)) d2 = 1e10;

	//�ʂƂ̋������߂��_�̋�����I��
	Dist = (d1<d2) ? d1 : d2;

	//�e�ӂƂ̋��������߂�
	d = DistanceLine(top, bottom, v0, v1, cross);
	if (Dist > d) Dist = d;

	d = DistanceLine(top, bottom, v1, v2, cross);
	if (Dist > d) Dist = d;

	d = DistanceLine(top, bottom, v2, v0, cross);
	if (Dist > d) Dist = d;

	if (length) *length = Dist;

	return (Dist <= radius);
}

bool CCollision::CompareLength(const COBB &A, const COBB &B, const CVector3 &distVec, const CVector3 &separate){
	float dist = abs(CVector3::Dot(distVec, separate));
	float distA = 0;
	for (int i = 0; i<3; i++) distA += abs(CVector3::Dot(A.mAxis[i], separate)) * A.mLength[i];
	float distB = 0;
	for (int i = 0; i<3; i++) distB += abs(CVector3::Dot(B.mAxis[i], separate)) * B.mLength[i];
	if (dist > distA + distB) return false;
	return true;
}

bool CCollision::CollisionOBB(const COBB &A, const COBB &B){
	CVector3 distVec = B.mPos - A.mPos;

	for (int i = 0; i<3; i++)
	if (!CompareLength(A, B, distVec, A.mAxis[i])) return false;

	for (int i = 0; i<3; i++)
	if (!CompareLength(A, B, distVec, B.mAxis[i])) return false;

	CVector3 separate;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			separate = CVector3::Cross(A.mAxis[i], B.mAxis[j]);
			if (!CompareLength(A, B, distVec, separate)) return false;
		}
	}

	return true;
}

//AABB���m�̏Փ˔���
bool CCollision::CollisionAABB(const CVector3 &minA, const CVector3 &maxA, const CVector3 &minB, const CVector3 &maxB){
	if (minA.x  < maxB.x && maxA.x > minB.x &&
		minA.y  < maxB.y && maxA.y > minB.y &&
		minA.z  < maxB.z && maxA.z > minB.z) return true;
	return false;
}

//2�����Ԃ̋���
float CCollision::DistanceLine(const CVector3 &s1, const CVector3 &e1, const CVector3 &s2, const CVector3 &e2, CVector3 *c, CVector3 *c2){
	//���̃x�N�g�������߂�
	CVector3 V1(e1 - s1);
	CVector3 V2(e2 - s2);
	//2�̐����̊O�ς����߂�
	CVector3 N(CVector3::Cross(V1, V2));
	//2�̐��������s�łȂ��ꍇ
	if (N.LengthSq()) {
		//�������Ă��邩���ׂ�	
		if (CVector3::Dot(CVector3::Cross(V1, s1 - s2), CVector3::Cross(V1, s1 - e2)) < 0 &&
			CVector3::Dot(CVector3::Cross(V2, s2 - s1), CVector3::Cross(V2, s2 - e1)) < 0) {
			return abs(CVector3::Dot(N.GetNormalize(), s1 - s2));
		}
	}
	//�n�_�ƏI�_��������Ƃ̋��������߁A�����Ƃ��Z��������Ԃ�
	return sqrt(min(
		min(DistancePointToLineSq(s2, e2, s1),
		DistancePointToLineSq(s2, e2, e1)),
		min(DistancePointToLineSq(s1, e1, s2),
		DistancePointToLineSq(s1, e1, e2))
		));
}
//�_�Ɛ��̋���
float CCollision::DistancePointToLine(const CVector3 &v0, const CVector3 &v1, const CVector3 &point)
{
	CVector3 p = PointOnLineSegmentNearestPoint(v0, v1, point);
	return (point - p).Length();
}
//�_�Ɛ��̋���
float CCollision::DistancePointToLineSq(const CVector3 &v0, const CVector3 &v1, const CVector3 &point)
{
	CVector3 p = PointOnLineSegmentNearestPoint(v0, v1, point);
	return (point - p).LengthSq();
}


/*�����蔻��̊֐�(�ۂ�BOX�̔���)*/
bool CCollision::CollSphereBox(CColSphere sphere, COBB &box){

	/*COBB�� x y z ���� ���a�����ׂČ���*/
	//Box��X�����������߂�
	CVector3 vx = box.mMatrixRotation * VEC_RIGHT;
	//Box��Y�����������߂�
	CVector3 vy = box.mMatrixRotation * VEC_TOP;
	//Box��Z�����������߂�
	CVector3 vz = box.mMatrixRotation * VEC_FRONT;



	//�l�p�`���狅�ւ̃x�N�g�������߂�
	CVector3 vectorBS = sphere.mPos - box.mPos;
	//�l�p�`���狅�ցA�l�p�`��X���ɑ΂��钷���Ƃ̍������߂�
	float dx = sphere.mRadius + box.mLength[COBB::E_X] - fabs(vx.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = sphere.mRadius + box.mLength[COBB::E_Y] - fabs(vy.Dot(vectorBS));
	//�l�p�`���狅�ցA�l�p�`��Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = sphere.mRadius + box.mLength[COBB::E_Z] - fabs(vz.Dot(vectorBS));

	//�Փ˂��Ă��邩���肷��
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		//if (dx > dy) {
		//	if (dy > dz) {
		//		//Z���Ŗ߂�
		//		if (vz.Dot(vectorBS) > 0.0f) {
		//			*pos = *pos + vz * dz;
		//		}
		//		else {
		//			*pos = *pos - vz * dz;
		//		}
		//	}
		//	else {
		//		//Y���Ŗ߂�
		//		if (vy.Dot(vectorBS) > 0.0f) {
		//			*pos = *pos + vy * dy;
		//		}
		//		else {
		//			*pos = *pos - vy * dy;
		//		}
		//	}
		//}
		//else {
		//	if (dx > dz) {
		//		//Z���Ŗ߂�
		//		if (vz.Dot(vectorBS) > 0.0f) {
		//			*pos = *pos + vz * dz;
		//		}
		//		else {
		//			*pos = *pos - vz * dz;
		//		}
		//	}
		//	else {
		//		//X���Ŗ߂�
		//		if (vx.Dot(vectorBS) > 0.0f) {
		//			*pos = *pos + vx * dx;
		//		}
		//		else {
		//			*pos = *pos - vx * dx;
		//		}
		//	}
		//}
		return true;
	}
	return false;

}

/*
v0, v1, v2 : Triangle
Capsule Height = radius + top - bottom - radius
*/
bool CCollision::IntersectTriangleCapsule2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross, float *length, CVector3 *n){
	//�|���S���̖@�������߂�
	CVector3 N(CVector3::Cross(v1 - v0, v2 - v0).GetNormalize());
	if (n) *n = N;
	float f;
	CVector3 v;
	if (IntersectTriangleSphere2(v0, v1, v2, top, radius, cross, length)) {
		if (IntersectTriangleSphere2(v0, v1, v2, bottom, radius, &v, &f)) {
			if (*length > f) {
				*cross = v;
				*length = f;
			}
		}
		return  true;
	}
	else if (IntersectTriangleSphere2(v0, v1, v2, bottom, radius, cross, length)) {
		return true;
	}

	CVector3 V(top - bottom);
	CVector3  VP;
	float Dist = 1e10, d;

	//�n�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV1 = top - v0;
	//�I�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV2 = bottom - v0;

	//�|���S���̖@���Ƃ̓��ς����߂�
	float dt = CVector3::Dot(PV1, N);
	float db = CVector3::Dot(PV2, N);

	if (dt*db<0) {
		//�ђʂ��Ă���ꍇ�͐��ƃ|���S���̔�����s��
		if (IntersectTriangleRay(cross, top, bottom, v0, v1, v2, &Dist)) {
			if (length) {
				CVector3 vt = (*cross - top);
				CVector3 vb = (*cross - bottom);
				//�ђʓ_�܂ł̋��������߂�
				float lt = (*cross - top).LengthSq();
				float lb = (*cross - bottom).LengthSq();
				if (dt < db) {
					*length = sqrt(lt) + radius;
					//*length = N.Dot(vt);
					//*cross = N;
				}
				else {
					*length = sqrt(lb) + radius;
					//*length = N.Dot(vb);
					//*cross = N;
				}
			}
			//			*cross = N;
			return true;
		}
	}

	dt = abs(dt);
	db = abs(db);
	//���ʏ�̓_�Ƃ̍ŒZ�n�_�����߂�
	CVector3 C1(top - N*dt);
	CVector3 C2(bottom - N*db);
	//�_�����ʏ�ɂȂ��ꍇ�͖����A��̕ӂƂ̐ڐG�Œ��ׂ�
	if (!TriangleIntersect(C1, v0, v1, v2, N)) dt = 1e10;
	if (!TriangleIntersect(C2, v0, v1, v2, N)) db = 1e10;

	//�ʂƂ̋������߂��_�̋�����I��
	Dist = (dt<db) ? dt : db;

	//�e�ӂƂ̋��������߂�
	d = DistanceLine(top, bottom, v0, v1, cross);
	if (Dist > d) Dist = d;

	d = DistanceLine(top, bottom, v1, v2, cross);
	if (Dist > d) Dist = d;

	d = DistanceLine(top, bottom, v2, v0, cross);
	if (Dist > d) Dist = d;

	if (length) *length = radius - Dist;

	return (Dist <= radius);
}
/*
v0, v1, v2 : Triangle
Capsule Height = top - bottom
*/
bool CCollision::IntersectTriangleCapsule3(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *adjust, CVector3 *cross, float *length){
	float len = 0.0f;
	CVector3 cro;
	//�|���S���̖@�������߂�
	CVector3 N(CVector3::Cross(v1 - v0, v2 - v0).GetNormalize());
	if (adjust) *adjust = N;

	CVector3 V(top - bottom);
	CVector3  VP;
	float Dist = 1e10, d;

	//if (adjust) {
	//	*adjust = V.GetNormalize();
	//}

	//�n�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV1 = top - v0;
	//�I�_����|���S����̂���n�_�i�ǂ��ł������j�ւ̃x�N�g��
	CVector3 PV2 = bottom - v0;

	//�|���S���̖@���Ƃ̓��ς����߂�
	float dt = CVector3::Dot(PV1, N);
	float db = CVector3::Dot(PV2, N);

	if (dt*db<0) {
		//�ђʂ��Ă���ꍇ�͐��ƃ|���S���̔�����s��
		if (IntersectTriangleRay(&cro, top, bottom, v0, v1, v2, &Dist)) {
			CVector3 vt = (cro - top);
			CVector3 vb = (cro - bottom);
			//�ђʓ_�܂ł̋��������߂�
			float lt = (cro - top).LengthSq();
			float lb = (cro - bottom).LengthSq();
			if (dt < db) {
				len = sqrt(lt);
				if (adjust) *adjust = *adjust * len;
			}
			else {
				len = sqrt(lb);
				if (adjust) *adjust = *adjust * len;
			}
			if (length) {
				*length = len;
			}
			if (cross)
				*cross = cro;
			return true;
		}
	}

	//	return false;

	float f = 0.0f;
	CVector3 v = (top - bottom).normalize();
	CVector3 wtop = top + v * radius * -1;
	CVector3 wbottom = bottom + v * radius;
	if (IntersectTriangleSphere2(v0, v1, v2, wtop, radius, &cro, &len)) {
		if (IntersectTriangleSphere2(v0, v1, v2, wbottom, radius, &v, &f)) {
			if (cross)
				*cross = cro;
			if (length)
				*length = len;
			if (len > f) {
				if (cross)
					*cross = v;
				if (length)
					*length = f;
			}
		}
		if (adjust) *adjust = *adjust * len;
		return  true;
	}
	else if (IntersectTriangleSphere2(v0, v1, v2, wbottom, radius, &cro, &len)) {
		if (cross)
			*cross = cro;
		if (length)
			*length = len;
		if (adjust) *adjust = *adjust * len;
		return true;
	}

	dt = abs(dt);
	db = abs(db);
	//���ʏ�̓_�Ƃ̍ŒZ�n�_�����߂�
	CVector3 C1(wtop - N*dt);
	CVector3 C2(wbottom - N*db);
	//�_�����ʏ�ɂȂ��ꍇ�͖����A��̕ӂƂ̐ڐG�Œ��ׂ�
	if (!TriangleIntersect(C1, v0, v1, v2, N)) dt = 1e10;
	if (!TriangleIntersect(C2, v0, v1, v2, N)) db = 1e10;

	//�ʂƂ̋������߂��_�̋�����I��
	Dist = (dt<db) ? dt : db;

	//�e�ӂƂ̋��������߂�
	d = DistanceLine(wtop, wbottom, v0, v1, &cro);
	if (Dist > d) Dist = d;

	d = DistanceLine(wtop, wbottom, v1, v2, &cro);
	if (Dist > d) Dist = d;

	d = DistanceLine(wtop, wbottom, v2, v0, &cro);
	if (Dist > d) Dist = d;

	if (length) *length = radius - Dist;
	if (adjust) *adjust = CVector3();
	if (cross) *cross = cro;
	return (Dist <= radius);
}
