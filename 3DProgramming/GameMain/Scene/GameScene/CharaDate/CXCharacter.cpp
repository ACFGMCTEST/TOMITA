#include "CXCharacter.h"
/*
 Init
 ����������
*/
void CXCharacter::Init(CModelX *model) {
	mpModel = model;
	mAnimationIndex = 0;
	mAnimationLoopFlg = true;
	mAnimationFrameSize = 60.0f;
	//24
	mAnimationTime = 0.0f;
	mpModel->mAnimationSet[0]->mWeight = 1.0f;
	//	ChangeAnimation(0, true, 30.0f);
}
/*
 ChangeAnimation
 �A�j���[�V������؂�ւ���
 index:�A�j���[�V�����̔ԍ�
 loop:true �J��Ԃ�
 framesize�F�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index) return;
	//24
	////�A�j���[�V�����̏d�݂�0.0�i100%)�ɂ���
	//�폜mpModel->mAnimationSet[mAnimationIndex]->mWeight = 0.0f;
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index;
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//24
	//�A�j���[�V�����̎��Ԃ��ŏ��ɂ���
	mAnimationTime = 0.0f;
	////�A�j���[�V�����̎��Ԃ��ŏ��ɂ���
	//�폜mpModel->mAnimationSet[mAnimationIndex]->mTime = 0.0f;
	////�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	//�폜mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}
/*
 Update
 �X�V����
 matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix44 &matrix) {
	//24
	//���݂̃A�j���[�V�����ƈقȂ�Ƃ�
	if (mpModel->mAnimationIndex != mAnimationIndex) {
		mpModel->mAnimationSet[mpModel->mAnimationIndex]->mWeight = 0.0f;
		mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
		mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
		mpModel->mAnimationIndex = mAnimationIndex;
	}
	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationTime
		<= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
		//���Ԃ�i�߂�
		mAnimationTime
			+= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime
			/ mAnimationFrameSize;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A���Ԃ�0�ɖ߂�
		if (mAnimationLoopFlg) {
			mAnimationTime = 0.0f;
		}
	}
	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->Animate(&matrix);
	//���_�ɃA�j���[�V������K�p����
	mpModel->AnimateVertex();
}
/*
 �`�悷��
*/
void CXCharacter::Render() {
	mpModel->Render();
}