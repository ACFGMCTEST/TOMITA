#include "COBB.h"
#include "../CCollisionManager.h"
#include "glut.h"

/*コンストラクタ　引数:当たり判定を追加するかしないか判断*/
COBB::COBB(bool addCol){
	mType = COL_BOX;//球体にする
	/*引数で判断*/
	if (addCol)CCollisionManager::GetInstance()->Add(this);//あたり判定追加
};
/*パラメータ設定*/
COBB::COBB(CVector3 &center, CVector3 &v, CMatrix44 *matrix){
	/*ボックスであるか判定*/
	mPos = center;
	/*ベクトルを決める*/
	mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
	mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
	mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
	/*長さを決める*/
	mLength[0] = v.x;
	mLength[1] = v.y;
	mLength[2] = v.z;

	mpCombinedMatrix = matrix;
	mMatrixRotation = *matrix;
}
/*更新処理*/
void COBB::Update(){
	/*ベクトルの初期化*/
	mAxis[0] = CVector3(1.0f, 0.0f, 0.0f);
	mAxis[1] = CVector3(0.0f, 1.0f, 0.0f);
	mAxis[2] = CVector3(0.0f, 0.0f, 1.0f);
	//移動回転させる
	Transform(*mpCombinedMatrix);
}

/*更新処理呼び出し*/
COBB COBB::GetUpdate(){
	COBB c = *this;
	c.Update();
	return c;
}
//OBBに行列を反映
void COBB::Transform(CMatrix44 &mat){
	for (int i = 0; i < COBB::E_ARRAY; i++) mAxis[i] = mat * mAxis[i] - mat * CVector3();
	CVector4 c = CVector4(mPos.x, mPos.y, mPos.z, 1);
	c = c*mat;
	mPos = CVector3(c.x, c.y, c.z);
}
/*描画*/
void COBB::Render(){
	CVector3 pos[8];
	for (int i = 0; i < 8; i++)
	{
		pos[i] = mPos;

	}

	pos[0] += mAxis[0] * mLength[0];
	pos[0] += mAxis[1] * mLength[1];
	pos[0] += mAxis[2] * mLength[2];

	pos[1] -= mAxis[0] * mLength[0];
	pos[1] += mAxis[1] * mLength[1];
	pos[1] += mAxis[2] * mLength[2];

	pos[2] -= mAxis[0] * mLength[0];
	pos[2] -= mAxis[1] * mLength[1];
	pos[2] += mAxis[2] * mLength[2];

	pos[3] += mAxis[0] * mLength[0];
	pos[3] -= mAxis[1] * mLength[1];
	pos[3] += mAxis[2] * mLength[2];

	pos[4] += mAxis[0] * mLength[0];
	pos[4] += mAxis[1] * mLength[1];
	pos[4] -= mAxis[2] * mLength[2];

	pos[5] -= mAxis[0] * mLength[0];
	pos[5] += mAxis[1] * mLength[1];
	pos[5] -= mAxis[2] * mLength[2];

	pos[6] -= mAxis[0] * mLength[0];
	pos[6] -= mAxis[1] * mLength[1];
	pos[6] -= mAxis[2] * mLength[2];


	pos[7] += mAxis[0] * mLength[0];
	pos[7] -= mAxis[1] * mLength[1];
	pos[7] -= mAxis[2] * mLength[2];

	//色の設定設定
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, CVector3(r, g, b, a});
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