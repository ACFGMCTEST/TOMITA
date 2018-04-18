//�����O��
#ifndef COption_HPP
#define COption_HPP
#include "../../Graphic/CRectangle2.h"
#define BGM_GAGE 4
#define SE_GAGE 4
class COption{
public:
	CRectangle2 mBackGround;			//�w�i

	CRectangle2 mBgmBox;				//BGM

	CRectangle2 mSeBox;					//SE

	CRectangle2 mBgmGage[BGM_GAGE];		//BGM�Q�[�W
	CRectangle2 mSeGage[SE_GAGE];		//SE�Q�[�W

	CRectangle2 mBgmMin;				//BGM�ŏ�
	CRectangle2 mBgmMax;				//BGM�ő�

	CRectangle2 mSeMin;					//SE�ŏ�
	CRectangle2 mSeMax;					//SE�ő�







	CRectangle2 mBackButton;	    //�߂�{�^��

	CRectangle2 mCursor;//�J�[�\��



	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpTexCursor;
	


	float alpha;
	float alpha2;

	int status;

	int rectnum;	//�l�p�`�̐�
	int rectx;		//�l�p�`�̂����W
	int recty;		//�l�p�`�̂����W


	~COption();
	COption();
	void Init();
	void Update();
	void Render();

};
#endif
