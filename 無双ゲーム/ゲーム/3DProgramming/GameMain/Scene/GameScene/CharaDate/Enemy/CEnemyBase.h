#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "../Player/CXCharPlayer.h"
#include"../../../../Graphic/CHpBar.h"

/*エネミーのクラス*/
class CEnemyBase : public CXCharPlayer{
public:
	CTexture mTexmFrame; //Hpのテクスチャ
	CTexture mTexGauge; //Hpのテクスチャ
	CHpBar mHp;//HPバー


	CEnemyBase();
	/*初期化処理*/
	void Init(CModelX *model);
	/*AIの動き関数*/
	void AIMove();
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
	/*ダメージを受けた時の処理*/
	void Damage(float power);

};
#endif
