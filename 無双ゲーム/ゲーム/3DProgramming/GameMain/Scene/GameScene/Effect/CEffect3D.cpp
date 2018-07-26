#include "CEffect3D.h"
#include "../../../Collision/ColType/CColSphere.h"
#include "../../../Collision/CCollisionManager.h"

/*コンストラクタ*/
CEffect3D::CEffect3D(){
	CTask::eName = CTask::E_3D_EFFECT;
}
/*デストラクタ*/
CEffect3D::~CEffect3D() {}
/*初期化*/
void CEffect3D::Init(CTask *parent,CModelX *mod,CVector3 *ppos,CVector3 *pRot) {
	mpPos = ppos;
	mpRot = pRot;

	PosInit();

	CModelXS::Init(mod);
	/*当たり判定設定*/
#define COL_RADIUS 2.5f//半径
#define COL_POS CVector3(0.0f,0.0f,0.0f)
#define COL_MATRIX(string) &mpCombinedMatrix[mpModel->FindFrame(string)->mIndex]//マトリックス
	new CColSphere(parent, COL_POS, COL_RADIUS, COL_MATRIX("Armature"), CColBase::PL_ATTACK_EFFECT3D);
}

/*描画*/
void CEffect3D::Render() {
	CModelXS::Render();
}

//ポジションを元に戻す
void CEffect3D::PosInit() {
	mPos = *mpPos;
	mRot = *mpRot;
}

/*移動関数*/
void CEffect3D::Move() {

	CMatrix44 rot_y, pos, matrix;
	//前方向指定
	CVector3 Forward = CVector3(0.0f,0.0f,1.0f);
	//回転行列の作成
	rot_y.rotationY(mRot.y);
	//進行方向を計算
	Forward = Forward * rot_y;
#define SPEED 0.5f
	//移動させる
	mPos += Forward * SPEED;
}

//ポジション更新
void CEffect3D::PosUpdate() {
	CMatrix44 pos, rot, matrix;
	//移動行列を計算する
	pos.translate(mPos);
	//回転行列の作成
	rot.rotationY(mRot.y);
	//回転移動行列を求める
	matrix = pos * rot;
	CModelXS::Update(matrix);
}

/*更新*/
void CEffect3D::Update() {
#define SPEED 40
	CModelXS::ChangeAnimation(MODEL_FILE"Effect\\EffectAnima.x", true, SPEED);
	//移動させる
	Move();
	//ポジションを更新
	PosUpdate();
	//アニメーションが終了したらエフェクトを消す
	if (mAnimationTime >
		mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
		CTask::mKillFlag = true;;
	}
}