#include "CSlimeAttack.h"
#include "../CSlime.h"
/*スピードのフレーム数でvelocityを変更する*/
/*フレーム*/
#define FRAME_VEL_ATTACK1 0
#define FRAME_VEL_ATTACK2 30
#define FRAME_VEL_ATTACK3 40
/*スピード*/
#define BASE_SPEED 0.2f
#define VEL_ATTACK1 BASE_SPEED * 0.5f
#define VEL_ATTACK2 0
#define VEL_ATTACK3 BASE_SPEED * 0.7f
//変更する関数
void CSlimeAttack::ChangeState(){
	
}
/*初めに呼び出し*/
void CSlimeAttack::Start(){
	mAnimaSpeed = 0;//初期化
}
/*攻撃の移動速さ調整*/
void CSlimeAttack::AttackSpeed(){
	
}
/*更新処理*/
void CSlimeAttack::Update()
{
	/*攻撃*/
	AttackSpeed();//攻撃で少し前に移動させる
}
//遷移時の処理
// isNextをfalseに戻す処理はここで行うとよい
void CSlimeAttack::OnChangeEvent()
{

}

CSlimeAttack::CSlimeAttack()
{
}

CSlimeAttack::~CSlimeAttack()
{
}