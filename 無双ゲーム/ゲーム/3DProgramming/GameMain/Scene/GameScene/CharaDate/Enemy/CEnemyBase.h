#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CPlayer.h"
#include"../../../../Graphic/CHpBar.h"
#include "../../Effect/CExplosion.h"

/*エネミーのクラス*/
class CEnemyBase : public CPlayer{
protected:
	CHpBar     *mpHp;//HPバー
	/*hp設定　ajust*/
	void SetHpBar(CVector3 ajust);
	/*爆発設定*/
	void SetExp();
public:
	CExplosion * mpExplosion;//爆発エフェクト(死亡時の演出)
	bool mFlagUpdate;//アップデートするかしないか
	CEnemyBase();
	~CEnemyBase();
	

	/*初期化処理*/
	void Init();
	/*更新*/
	void Update();
	/*描画*/
	void Render();
	/*攻撃準備 当たり判定部分で呼ぶ*/
	void AttackInit();
	/*当たり判定*/
	bool Collision(CColBase* me, CColBase* you);
	/*カプセル内当たり判定*/
	void CapsuleCol(CColCapsule *caps, CColBase* y);
	/*球体内当たり判定 ｍ自分*/
	void SphereCol(CColSphere *m, CColBase* y);
	/*AIの動き関数*/
	void AIMove();
	/*ダメージを受けた時の処理*/
	void Damage(float power, CVector3 rot);

	/*体力ゲージのHp取得*/
	float HP() { return mpHp->mValue; }
};
#endif
