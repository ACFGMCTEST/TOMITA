#include "CXCharacter.h"
/*
 Init
 初期化処理
*/
void CXCharacter::Init(CModelX *model) {
	mpModel = model;
	mAnimationIndex = 0;
	mAnimationLoopFlg = true;
	mAnimationFrameSize = 60.0f;
	mAnimationTime = 0.0f;
	mpModel->mAnimationSet[0]->mWeight = 1.0f;
}
/*
 ChangeAnimation
 アニメーションを切り替える
 index:アニメーションの番号
 loop:true 繰り返す
 framesize：最後まで再生するのに使用されるフレーム数
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//同じ場合は切り替えない
	if (mAnimationIndex == index) return;
	

	//番号、繰り返し、フレーム数を設定
	mAnimationIndex = index;
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//24
	//アニメーションの時間を最初にする
	mAnimationTime = 0.0f;
}
/*
 Update
 更新する
 matrix：移動、回転、拡大縮小の行列
*/
void CXCharacter::Update(CMatrix44 &matrix) {
	//24
	//現在のアニメーションと異なるとき
	if (mpModel->mAnimationIndex != mAnimationIndex) {
		mpModel->mAnimationSet[mpModel->mAnimationIndex]->mWeight = 0.0f;
		mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
		mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
		mpModel->mAnimationIndex = mAnimationIndex;
	}
	//最後まで再生していない
	if (mAnimationTime
		<= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
		//時間を進める
		mAnimationTime
			+= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime
			/ mAnimationFrameSize;
	}
	else {
		//繰り返しの場合は、時間を0に戻す
		if (mAnimationLoopFlg) {
			mAnimationTime = 0.0f;
		}
	}
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
	//フレームの変換行列をアニメーションで更新する
	mpModel->AnimateFrame();
	//フレームの合成行列を計算する
	mpModel->mFrame[0]->Animate(&matrix);
	//頂点にアニメーションを適用する
	mpModel->AnimateVertex();
}
/*
 描画する
*/
void CXCharacter::Render() {
	mpModel->Render();
}