//高橋弘樹
#ifndef COption_HPP
#define COption_HPP
#include "../../Graphic/CRectangle2.h"
#define BGM_GAGE 4
#define SE_GAGE 4
class COption{
public:
	CRectangle2 mBackGround;			//背景

	CRectangle2 mBgmBox;				//BGM

	CRectangle2 mSeBox;					//SE

	CRectangle2 mBgmGage[BGM_GAGE];		//BGMゲージ
	CRectangle2 mSeGage[SE_GAGE];		//SEゲージ

	CRectangle2 mBgmMin;				//BGM最少
	CRectangle2 mBgmMax;				//BGM最大

	CRectangle2 mSeMin;					//SE最少
	CRectangle2 mSeMax;					//SE最大







	CRectangle2 mBackButton;	    //戻るボタン

	CRectangle2 mCursor;//カーソル



	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpTexCursor;
	


	float alpha;
	float alpha2;

	int status;

	int rectnum;	//四角形の数
	int rectx;		//四角形のｘ座標
	int recty;		//四角形のｙ座標


	~COption();
	COption();
	void Init();
	void Update();
	void Render();

};
#endif
