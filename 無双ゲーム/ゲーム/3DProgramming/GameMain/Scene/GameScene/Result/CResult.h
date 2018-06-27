#ifndef RESULT_HPP
#define RESULT_HPP

#include "../../../Graphic/CRectangle2.h"

/*���U���g�̃N���X*/
class CResult{
private:
	static CResult *mResult;

	CRectangle2 mLogo;	//�^�C�g�����S
	CRectangle2 mBG;    //�o�b�N�O���E���h�̗� �i�w�i)

	CTexture mTexBG;//�w�i�̃e�N�X�`��
	CTexture mTexLogo;//�N���A���S�̃e�N�X�`��

	float mCount;//���Ԃ����

	bool mRenderFlag;//�`�悷��t���O
public:

	static CResult *GetInstance();
	~CResult(); //�f�X�g���N�^
	CResult() :mRenderFlag(false), mCount(0.0f){} //�R���X�g���N�^
	void Clear();//Clear�����Ƃ��Ă�
	void Over();//���S�����Ƃ��Ă�

	void Init();//�������֐�
	void Update();//�X�V�֐�
	void Render();//�`��֐�

};
#endif
