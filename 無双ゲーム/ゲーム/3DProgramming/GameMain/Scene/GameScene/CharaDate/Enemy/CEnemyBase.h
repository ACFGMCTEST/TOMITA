#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CPlayer.h"
#include"../../../../Graphic/CHpBar.h"
#include "../../Effect/CExplosion.h"
#include "../../../../Sound/CSound.h"

#define ENE_HP_MAX(doub) 10.0f * doub  //HP_引数倍率
/*エネミーのクラス*/
class CEnemyBase : public CPlayer{
protected:
	CHpBar     *mpHp;//HPバー

	CSound *mpSeDamage;//ダメージを食らった時の音
	CSound *mpSeFall;//地面に落ちた時の音

	/*hp設定　ajust*/
	void SetHpBar(float hp,CVector3 ajust);
	/*爆発設定*/
	void SetExp();

public:
	bool mFlagBlowDamage;//吹っ飛んでいるとき連鎖してダメージを与えるか判断
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

	/*球体内当たり判定 ｍ自分*/
	void SphereCol(CColSphere *m, CColBase* y);
	/*AIの動き関数*/
	void AIMove();
	/*ダメージを受けた時の処理*/
	float Damage(float power, CVector3 rot);
	/*体力ゲージのHp取得*/
	float HP() { return mpHp->mValue; }	
};
#endif
