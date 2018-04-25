//�����O��
#ifndef CQuest_HPP
#define CQuest_HPP
#include "../../../Base/CBase.h"
#include"../../Graphic/CRectangle2.h"
#include"../CScene.h"

#define BOARD 3

class CQuest :public CScene{
public:
	CRectangle2 mBG;		//�i�w�i�j

	CRectangle2 mQuestName00;	    //�N�G�X�g��
	CRectangle2 mQuestName01;
	CRectangle2 mQuestName02;
	CRectangle2 mShadow[BOARD];


	CRectangle2 mCursor;//�J�[�\��

	CRectangle2 mBackButton;	    //�߂�{�^��

	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpTexCursor;

	/*�N�G�X�g�̏��*/
	enum E_CHOICE{
		E_QUEST00,
		E_QUEST01,
		E_QUEST02,
		E_QUEST03
	};
	static E_CHOICE eChoice;

	float alpha;
	float alpha2;

	int status;

	~CQuest();
	CQuest(){};
	void Init();
	void Update();
	void Render();

};
#endif
