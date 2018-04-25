//�����O��
#ifndef CGAMERESULT_HPP
#define CGAMERESULT_HPP
#include"../../../Base/CBase.h"
#include "../../Graphic/CRectangle2.h"
#include"../CScene.h"
#include "../ItemScene/CItem.h"

#define DIGIT 3 //����
#define TIPS  4
#define NUM_SIZE -40,40,40,-40

#define PRIZE0 10 * 2
#define PRIZE1 20 * 2
#define PRIZE2 30 * 2
#define PRIZE3 40 * 2


//Result���
//�N�G�X�g�œ��肵�����z�̌v�Z���s�����Z����
//�N�G�X�g�̋��z���_���̍���
//0-5�̏ꍇ�T�{�@�Q�|�T�̏ꍇ�R�{

class CGameResult :public CScene{


public:

	CItem mItem;

	CRectangle2 mBG;                    //�o�b�N�O���E���h�̗� �i�w�i)
	CRectangle2 mResult;	            //���U���g
	CRectangle2 mQuestName;	            //�N�G�X�g�����S
	CRectangle2 mBaseMoney    [DIGIT];  //���ƂȂ���z
	CRectangle2 mMagnification[DIGIT];  //��V�ɂ�����{��
	CRectangle2 mTotalMoney   [DIGIT];  //�����Ɣ{�����v�Z�������ʁB�ŏI�I�Ɏ�ɓ�����z��\������
	CRectangle2 mPocketMoney  [DIGIT];  //�������̕\��
	CRectangle2 mTips         [TIPS];

	CRectangle2 mCursor;//�J�[�\��


	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpNumber;

	int difit1;
	int difit2;
	int difit3;

	static int mPrize;

	float mNumCount;

	int mQuestMoney; //�N�G�X�g�ŗL�̕�V

	int mDifference; //����Ƃ̃X�R�A�̍�����ۑ����Ĕ{���Ƃ��Ĉ���
	
	int  mTotal; //�����Ɣ{�����v�Z��������

	float mPocketMoneySave;

	float mAlpha = 0.0f;

	static bool mFlagResult;//�t���O�����ƍX�V����

	enum EPrize{
		E_Quest0,
		E_Quest1,
		E_Quest2,
		E_Quest3,
	};



	/*��ԑI��*/
	enum EStatus
	{
		E_GAMESTART,
		E_GAMEEXIT
	};
	EStatus eStatus;

	~CGameResult();
	CGameResult();
	
	void Number(int score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);
	void Init();
	void Update();
	void Render();

};
#endif
