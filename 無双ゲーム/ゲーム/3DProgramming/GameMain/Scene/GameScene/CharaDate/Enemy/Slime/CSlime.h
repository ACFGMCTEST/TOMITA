#ifndef SLIME_H
#define SLIME_H
#include "../CEnemyBase.h"
/*当たり判定*/
#include "../../../../../Collision/ColType/CColSphere.h"
#include "../../../../../Collision/ColType/CColCapsule.h"

/*エネミー*/
/*スライム*/
#define MODEL_FILE_SLIME		MODEL_FILE"Slime\\Slime.x"//スライム	
#define SLIME_MAX 5//スライムの数
#define SLIME_POS(i) CVector3(i * SLIME_MAX + 10,POS_Y,i * SLIME_MAX + 10)//スライムの数
/*アニメーションのファイル場所*/
#define F_SLI_IDLING			MODEL_FILE"Slime\\Anima\\Idling.x"
#define F_SLI_RUN				MODEL_FILE"Slime\\Anima\\Run.x"
#define F_SLI_DAMAGE			MODEL_FILE"Slime\\Anima\\Damage.x"
#define F_SLI_ATTACK			MODEL_FILE"Slime\\Anima\\Attack.x"


/*キングスライム*/
#define KING_MODEL_FILE_SLIME		MODEL_FILE"Slime\\King\\KingSlime.x"//スライム	
/*アニメーションのファイル場所*/
#define F_SLI_KING_IDLING			MODEL_FILE"Slime\\King\\Anima\\Idling.x"
#define F_SLI_KING_RUN				MODEL_FILE"Slime\\King\\Anima\\Run.x"
#define F_SLI_KING_DAMAGE			MODEL_FILE"Slime\\King\\Anima\\Damage.x"
#define F_SLI_KING_ATTACK			MODEL_FILE"Slime\\King\\Anima\\Attack.x"

/*エネミーのクラス*/
class CSlime : public CEnemyBase{
protected:
	/*当たり判定*/
	CColCapsule * mpCaps;//カプセル胴体
	CColSphere  *mpSphere;//球体胴体
private:
	static int mAllCount;//エネミーの数
public:

	CSlime();
	~CSlime();
	/*削除*/
	void Delete();
	/*ステータス初期化 Kingスライムも同じものしよう*/
	void StateInit();
	/*スライムの初期化*/
	void SlimeInit(CModelX *model);
	/*初期化処理*/
	void Init(CModelX *model);

	/*更新*/
	void Update();
	/*描画*/
	void Render();
	/*索敵関数*/
	bool Search();
	/*攻撃範囲*/
	bool AttackRange();
	/*球体判定*/
	void SphereCol(CColSphere *sphere, CColBase *y);
};
#endif
