#include "CCollider.h"
#include "glut.h"

/*初期サイズ*/
#define INIT_SIZE 1.0f
/*球体の分割数*/
#define DIVISION_NUM 20,20

/*Obbを大きくさせる*/
void CCollider::SetObbSize(CVector3 size){
	/*ボックスであるか判定*/
	if (eColTag == CTask::E_COL_BOX){
		/*サイズ変更*/
		mObb.mLength[0] = size.x;
		mObb.mLength[1] = size.y;
		mObb.mLength[2] = size.z;
		
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("当たり判定の形を設定してください\n");
		assert(false);
	}
	else
	{
		printf("設定している形が違います\n");
		assert(false);
	}
}
/*
OBBのパラメータ設定
center:中心の座標
lenght:xyzの長さ
matrix:フレームの合成行列
*/
void CCollider::SetBoxOBB(CVector3 &center, CVector3 size, CMatrix44 *matrix){
	

	/*ボックスであるか判定*/
	if (eColTag == CTask::E_COL_BOX){
		mParentNextPos = center;
		mObb.mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
		mObb.mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
		mObb.mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
		/*サイズ変更*/
		mObb.mLength[0] = size.x;
		mObb.mLength[1] = size.y;
		mObb.mLength[2] = size.z;
		/*マトリックス設定*/
		mpCombinedMatrix = matrix;
		mObb.mMatrixRotation = *matrix;
	}
	else if(eColTag == CTask::E_COL_NO){
		printf("当たり判定の形を設定してください\n");
		assert(false);
	}
	else
	{
		printf("設定している形が違います\n");
		assert(false);
	}
}

/*Obbを回転させる*/
void CCollider::SetObbRot(const CVector3 rot){
	mObb.mRotation = rot;//回転値を代入
	/*ボックスであるか判定*/
	if (eColTag == CTask::E_COL_BOX){


		CMatrix44 mx,my, mz;
		//回転させる

		mx.rotationX(mObb.mRotation.x);
		my.rotationY(mObb.mRotation.y);
		mz.rotationZ(mObb.mRotation.z);
		
		*mpCombinedMatrix = *mpCombinedMatrix *my * mx * mz;
		mObb.mMatrixRotation = *mpCombinedMatrix;
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("当たり判定の形を設定してください\n");
		assert(false);
	}
	else
	{
		printf("設定している形が違います\n");
		assert(false);
	}
}

/*球の当たり判定*/
void CCollider::SetShere(float radius,CVector3 pos,CMatrix44 *matrix){
	/*球体であるか設定*/
	if (eColTag == CTask::E_COL_SPHEPE){
		mParentNextPos = pos;
		mColSphere.mRadius = radius;
		//mpPos = pos;
		mpCombinedMatrix = matrix;
		mColSphere.mMatrixRotation = *matrix;
	}
	else if (eColTag == CTask::E_COL_NO){
		printf("当たり判定の形を設定してください\n");
		assert(false);
	}
	else
	{
		printf("設定している形が違います\n");
		assert(false);
	}
}

/*
Update
mOBBを変換行列で移動回転させる
*/
void CCollider::Update(){
	
	switch (eColTag)
	{
	case CTask::E_COL_NO:
		break;
	case CTask::E_COL_BOX:
		mObb.mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
		mObb.mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
		mObb.mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);


		//回転行列の設定
		mObb.mPos = mParentNextPos;

		
		//移動回転させる
		mObb.Transform(*mpCombinedMatrix);
		break;
	case CTask::E_COL_SPHEPE:
		mColSphere.mPos = mParentNextPos;
		//移動回転させる
		mColSphere.Transform(*mpCombinedMatrix);
		break;
	default:
		break;
	}

}

void CCollider::Render(){

	switch (eColTag)
	{
	case CTask::E_COL_NO:
		printf("当たり判定の形を設定しましょう");
		assert(false);
		break;
	case CTask::E_COL_BOX:
		Render(&mObb);
		break;
	case CTask::E_COL_SPHEPE:
		glPushMatrix();
		glColor3d(mColSphere.r, mColSphere.g, mColSphere.b); //色の設定
		glTranslated(mColSphere.mPos.x, mColSphere.mPos.y, mColSphere.mPos.z);//平行移動値の設定
		glutSolidSphere(mColSphere.mRadius, DIVISION_NUM);//引数：(半径, Z軸まわりの分割数, Z軸に沿った分割数)
		glPopMatrix();
		break;
	default:
		break;
	}



}

//OBB描画

void CCollider::Render(COBB *obb){
	CVector3 pos[8];
	for (int i = 0; i < 8; i++)
	{
		pos[i] = obb->mPos;

	}

	pos[0] += obb->mAxis[0] * obb->mLength[0];
	pos[0] += obb->mAxis[1] * obb->mLength[1];
	pos[0] += obb->mAxis[2] * obb->mLength[2];

	pos[1] -= obb->mAxis[0] * obb->mLength[0];
	pos[1] += obb->mAxis[1] * obb->mLength[1];
	pos[1] += obb->mAxis[2] * obb->mLength[2];

	pos[2] -= obb->mAxis[0] * obb->mLength[0];
	pos[2] -= obb->mAxis[1] * obb->mLength[1];
	pos[2] += obb->mAxis[2] * obb->mLength[2];

	pos[3] += obb->mAxis[0] * obb->mLength[0];
	pos[3] -= obb->mAxis[1] * obb->mLength[1];
	pos[3] += obb->mAxis[2] * obb->mLength[2];

	pos[4] += obb->mAxis[0] * obb->mLength[0];
	pos[4] += obb->mAxis[1] * obb->mLength[1];
	pos[4] -= obb->mAxis[2] * obb->mLength[2];

	pos[5] -= obb->mAxis[0] * obb->mLength[0];
	pos[5] += obb->mAxis[1] * obb->mLength[1];
	pos[5] -= obb->mAxis[2] * obb->mLength[2];

	pos[6] -= obb->mAxis[0] * obb->mLength[0];
	pos[6] -= obb->mAxis[1] * obb->mLength[1];
	pos[6] -= obb->mAxis[2] * obb->mLength[2];


	pos[7] += obb->mAxis[0] * obb->mLength[0];
	pos[7] -= obb->mAxis[1] * obb->mLength[1];
	pos[7] -= obb->mAxis[2] * obb->mLength[2];

	//色の設定設定
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, new float[]{r, g, b, a});
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
#define GLVERPOS(i)  glVertex3f(pos[i].x, pos[i].y, pos[i].z)
	GLVERPOS(0);
	GLVERPOS(1);
	GLVERPOS(2);
	GLVERPOS(3);

	GLVERPOS(0);
	GLVERPOS(3);
	GLVERPOS(7);
	GLVERPOS(4);

	GLVERPOS(4);
	GLVERPOS(7);
	GLVERPOS(6);
	GLVERPOS(5);

	GLVERPOS(5);
	GLVERPOS(6);
	GLVERPOS(2);
	GLVERPOS(1);

	GLVERPOS(1);
	GLVERPOS(0);
	GLVERPOS(4);
	GLVERPOS(5);

	GLVERPOS(6);
	GLVERPOS(7);
	GLVERPOS(3);
	GLVERPOS(2);
	glEnd();

	//αブレンド無効
	glDisable(GL_BLEND);

}
/*色設定*/
void CCollider::SetColor(float cr, float cg, float cb, float ca){
	switch (eColTag)
	{
	case CTask::E_COL_NO:
		break;
	case CTask::E_COL_BOX:
		mObb.SetColor(cr, cg, cb, ca);

		break;
	case CTask::E_COL_SPHEPE:
		mColSphere.SetColor(cr, cg, cb, ca);

		break;
	default:
		break;
	}
}

/*サイズアップ*/
void CCollider::SizeUP(float f){
	for (int i = 0; i < 3; i++){
		mObb.mLength[i] += f;
	}
}