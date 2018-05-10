#include "CStateBase.h"
#include "../Define/Define.h"
/*�R���X�g���N�^*/
CStateBase::CStateBase() :mFlagNext(false),mNextRegisterName(""){
};
/*�f�X�g���N�^*/
CStateBase::~CStateBase(){
	P_DELETE(mpParent);
}
// �J�ڎ��̏���
// isNext��false�ɖ߂������͂����ōs���Ƃ悢
void CStateBase::OnChangeEvent(){
	mFlagNext = false;//�����ɗ���Ɛ؂�ւ����
	printf("%s�ɐ؂�ւ��܂���\n", mNextRegisterName.c_str());
	mNextRegisterName = "";//������
};

// �J�ڂ��邩�ǂ����̎擾
bool  CStateBase::IsNext()const
{
	return mFlagNext;
}
/*�e�ݒ肷��*/
void  CStateBase::SetParent(CTask *p){
	mpParent = new CTask();//�C���X�^���X�쐬
	mpParent = p;//STATE�ݒ�.���̐e�ɃA�N�Z�X�ł���悤�ɂ���
}

// �J�ڐ�̓o�^���̎擾
std::string CStateBase::NextRegisterName() 
{
	return mNextRegisterName;
}