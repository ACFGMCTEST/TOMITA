#ifndef COLLISION_H
#define COLLISION_H

#include "../Matrix/CMatrix44.h"
#include "../Vector/CVector2.h"
#include "../Vector/CVector3.h"
#include "../Vector/CVector4.h"

#include "stdio.h"
#include "../Task/CTask.h"
/*当たり判定のタイプインクルード*/
#include "ColType\COBB.h"
#include "ColType\CColSphere.h"
#include "ColType\CColTriangle.h"
#include "ColType\CColCapsule.h"
#include "ColType\CColLine.h"


//
///*当たり判定クラス　壁*/
//class CColWall :public CCollBase
//{
//public:
//	CVector3 mNormal;		//向き
//};

//衝突判定クラス
class CCollision {
private:
	//separate軸上に投影したOBB同士が接触しているか調べる
	static bool CompareLength(const COBB &A, const COBB &B, const CVector3 &distVec, const CVector3 &separate);
public:
	//球同士の衝突判定
	static bool CollisionShpere(const CColSphere &sphereA, const CColSphere &sphereB);
	//カプセル同士の衝突
	static bool CollisionCapsule(const CColCapsule *capsuleA, const CColCapsule *capsuleB);

	//OBB同士の衝突判定
	static bool CollisionOBB(const COBB &A, const COBB &B);
	//AABB同士の衝突判定
	static bool CollisionAABB(const CVector3 &minA, const CVector3 &maxA, const CVector3 &minB, const CVector3 &maxB);

	//点cが三角形ポリゴン上にあるか調べる
	static bool TriangleIntersect(const CVector3 &c, const CVector3 &v0, const  CVector3 &v1, const CVector3 &v2, const CVector3 &n);
	static bool TriangleIntersect(const CVector3 &c, const CVector3 &v0, const  CVector3 &v1, const CVector3 &v2);
	//線分と三角形ポリゴンとの衝突判定
	/*
	corss = 接地面
	p1 = 線の初め
	p2 = 線の終わり
	v0 = 三角形の点1
	v1 = 三角形の点2
	v2 = 三角形の点3
	pt = 割合
	*/
	static bool IntersectTriangleRay(CVector3 *corss, const CVector3 &p1, const  CVector3 &p2, const CVector3& v0, const  CVector3 &v1, const  CVector3 &v2, float *pt);
	//pointから近いv0→v1線上の点を調べる
	static CVector3 PointOnLineSegmentNearestPoint(const CVector3 &v0, const CVector3 &v1, const CVector3 &point);
	static CVector3 PointOnLineSegmentNearestPoint2(const CVector3 &v0, const CVector3 &v1, const CVector3 &point);

	static CVector2 PointOnLineSegmentNearestPoint(const CVector2 &v0, const CVector2 &v1, const CVector2 &point);
	//三角ポリゴンと球の衝突判定
	static bool IntersectTriangleSphere(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross = 0, float *length = 0);
	static bool IntersectTriangleSphere2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &center, float radius, CVector3 *cross = 0, float *length = 0, CVector3 *adjust = 0);
	//三角ポリゴンとカプセルの衝突判定
	static bool IntersectTriangleCapsule(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross = 0, float *length = 0);
	static bool IntersectTriangleCapsule2(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *cross = 0, float *length = 0, CVector3 *n = 0);
	static bool IntersectTriangleCapsule3(const CVector3 &v0, const CVector3 &v1, const CVector3 &v2, const CVector3 &top, const CVector3 &bottom, float radius, CVector3 *adjust = 0, CVector3 *cross = 0, float *length = 0);

	//2線分間の距離
	static float DistanceLine(const CVector3 &s1, const CVector3 &e1, const CVector3 &s2, const CVector3 &e2, CVector3 *cross = NULL, CVector3 *c2 = NULL);

	//点と線の距離
	static float DistancePointToLine(const CVector3 &v0, const CVector3 &v1, const CVector3 &p);
	//点と線の距離
	static float DistancePointToLineSq(const CVector3 &v0, const CVector3 &v1, const CVector3 &p);


	/*当たり判定の関数(球とBOXの判定)*/
	static bool CollSphereBox(CColSphere sphere, COBB &box);


};
#endif