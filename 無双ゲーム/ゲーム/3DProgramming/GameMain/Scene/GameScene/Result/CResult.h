#ifndef RESULT_HPP
#define RESULT_HPP

#include "../../../Graphic/CRectangle2.h"

/*リザルトのクラス*/
class CResult{
private:
	static CResult *mResult;

	CRectangle2 mLogo;	//タイトルロゴ
	CRectangle2 mBG;    //バックグラウンドの略 （背景)

	CTexture mTexBG;//背景のテクスチャ
	CTexture mTexLogo;//クリアロゴのテクスチャ

	float mCount;//時間を作る

	bool mRenderFlag;//描画するフラグ
public:

	static CResult *GetInstance();
	~CResult(); //デストラクタ
	CResult() :mRenderFlag(false), mCount(0.0f){} //コンストラクタ
	void Clear();//Clearしたとき呼ぶ
	void Over();//死亡したとき呼ぶ

	void Init();//初期化関数
	void Update();//更新関数
	void Render();//描画関数

};
#endif
