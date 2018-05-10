#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"

class CXCharacter {
public:
	CModelX *mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:繰り返す
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	//24
	float mAnimationTime;	//現在のアニメーション時間

	//初期化処理
	void Init(CModelX *model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix44 &m);
	//描画処理
	void Render();
};

#endif
