#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"

class CXCharacter {
public:
	CModelX *mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�J��Ԃ�
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
	//24
	float mAnimationTime;	//���݂̃A�j���[�V��������

	//����������
	void Init(CModelX *model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix44 &m);
	//�`�揈��
	void Render();
};

#endif
