#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"
#include"../../../../Graphic/CHpBar.h"

/*エネミーのクラス*/
class CEnemyBase : public CXCharPlayer{
protected:
	CHpBar * mpHp;//HPバー
	CTexture mTexmFrame;//Hpのテクスチャ
	CTexture mTexGauge; //Hpのテクスチャ
	CVector3 mDamageRot;//ダメージを受けた回転値
	float mDamagePower;//吹っ飛ぶ値
public:
	bool mFlagDamage;//ダメージ中のフラグ
	CEnemyBase();
	
	/*初期化処理*/
	void Init(CModelX *model);
	/*更新*/
	void Update();
	/*描画*/
	void  Render();
	/*攻撃準備 当たり判定部分で呼ぶ*/
	void AttackInit();
	/*当たり判定*/
	bool Collision(CColBase* me, CColBase* you);
	/*カプセル内当たり判定*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);
	/*AIの動き関数*/
	void AIMove();
	/*ダメージを受けた時の処理*/
	void Damage(float power, CVector3 rot);
	/*吹っ飛ぶ判定:引数　飛ぶ方向指定*/
	void BlowOff();

};
#endif
