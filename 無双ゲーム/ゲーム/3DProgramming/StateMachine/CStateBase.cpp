#include "CStateBase.h"
#include "../Define/Define.h"
/*コンストラクタ*/
CStateBase::CStateBase() :mFlagNext(false),mNextRegisterName(""){
};
/*デストラクタ*/
CStateBase::~CStateBase(){
	P_DELETE(mpParent);
}
// 遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CStateBase::OnChangeEvent(){
	mFlagNext = false;//ここに来ると切り替わった
	printf("%sに切り替わりました\n", mNextRegisterName.c_str());
	mNextRegisterName = "";//初期化
};

// 遷移するかどうかの取得
bool  CStateBase::IsNext()const
{
	return mFlagNext;
}
/*親設定する*/
void  CStateBase::SetParent(CTask *p){
	mpParent = new CTask();//インスタンス作成
	mpParent = p;//STATE設定.元の親にアクセスできるようにする
}

// 遷移先の登録名の取得
std::string CStateBase::NextRegisterName() 
{
	return mNextRegisterName;
}