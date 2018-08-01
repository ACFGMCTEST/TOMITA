#include "../CGameScene.h"
#include "CTutorial.h"
#include "../../../../Define/Define.h"
#include "../../../Key/CKey.h"
#include "../../../Camera/CCamera.h"
#include "../../../Key/CMouse.h"
#include "../../../Convenient/CConvenient.h"
#include "../../../Collision/CCollision.h"
#include "../CharaDate/Player/CPlayer.h"
#include "../CharaDate/Enemy/Slime/CSlime.h"
/*テクスチャの頂点指定,簡略化*/
#define TEX_SIZE(v) v.left,v.top,v.right,v.bottom 

CTutorial* CTutorial::mpTutorial = 0;

//GetInstance
CTutorial* CTutorial::GetInstance() {
	if (mpTutorial == 0) {
		mpTutorial = new CTutorial();
	}
	return mpTutorial;
}

/*コンストラクタ*/
CTutorial::CTutorial() : mFlagUv(false), eState(ESTATE::ALL_ENE_KILL)
, mTime(0){}
/*デストラクタ*/
CTutorial::~CTutorial(){}

/*初期化*/
void CTutorial::Init() {
	mFlagText = true;
	mFlagBG = true;
	mPos = CVector3(0.0f, 0.0f, 0.0f);
	eState = ESTATE::ALL_ENE_KILL;
	mTime = 0;
#define TEX_X 600//テクスチャの横幅
#define TEX_Y 37//テクスチャ行幅
#define TEX_BG_Y 70//BGのサイズY
#define SIZE_DOUB 0.6f
	/*サイズ*/
	mRect.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_Y));
	mRect.mPosition.y = DISP_2D_Y / 2.5f;//ポジション設定
	mBG.SetVertex(RECT_SIZE(SIZE_DOUB, TEX_X, TEX_BG_Y));
	mBG.mPosition = mRect.mPosition;
	const float ajust = 10;//ポジション調整用
	mBG.mPosition.y -= TEX_Y * SIZE_DOUB - ajust;
	/*テクスチャ*/
	/*テクスチャ*/
	mTex.Load(TGA_FILE"Tutorial\\Text.tga");
	mTexBG.Load(TGA_FILE"Tutorial\\TextBG.tga");
	/*頂点数保存種類分け*/
	for (int i = 0; i < ESTATE::ARRAY; i++) {
		mVer[i] = STexVer(0.0f, TEX_Y * (i), TEX_X, TEX_Y * (i + 1));
	}
	/*UV張替え*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
	mBG.SetUv  (&mTexBG, TEX_SIZE(STexVer(0,0, TEX_X, TEX_BG_Y)));
	/*アルファ調整*/
	mRect.SetColor(NO_A_WHITE_COLOR, 0.5f);//半透明にする
}

/*更新*/
void CTutorial::Update(){
	/*１秒たったら && キー操作説明以外の時 ポーズ*/
	if (CConvenient::Time(&mTime, 0.5f)) {
		if (eState == ESTATE::ALL_ENE_KILL) {
			CGameScene::mPauseFlag = true;
		}
	}

	/*テキスト切り替え*/
	Change();


}
/*文字切り替え*/
void CTutorial::Change() {
	/*
	当たり判定設定
	*/
#define SERACH_SPHERE(range,mat) range,CVector3(0.0f,0.0f,0.0f),mat//球体の設定(索敵に使う)
#define SEARCH_PL_RANGE 5.0f
#define SEARCH_RANGE 5.0f
	CMatrix44 m44 = CMatrix44();
	/*索敵内に入れば動く*/
	CColSphere plCol = CColSphere(SERACH_SPHERE(SEARCH_PL_RANGE, CSceneModel::mpPlayer->mpMatrix));//プレイヤー
	CColSphere Col = CColSphere(SERACH_SPHERE(SEARCH_RANGE, &m44));
	bool ChangeFlag = false;
	/*条件が整っているなら次のテキストに*/
	switch (eState)
	{
		/*すべての敵を倒そうの状態*/
	case CTutorial::ALL_ENE_KILL:
		/*キーを押すと動く説明に*/
		if (CKey::once(VK_RETURN)) {
			eState = MOVE;
			CGameScene::mPauseFlag = false;
		}
		break;
		/*動く説明*/
	case CTutorial::MOVE:
		mFlagBG = false;
		//視界内に来ているか判断
		ChangeFlag =  !CCollision::CollisionShpere(plCol.GetUpdate(), Col.GetUpdate());
		if (ChangeFlag) {
			eState = ATTACK_AVOID;
		}
		break;
		/*攻撃とよける説明*/
	case CTutorial::ATTACK_AVOID:
		/*キーを押すと動く説明 || 下にいる敵を倒すと次のテキストに*/
		if (CSceneModel::mEnemyCount <= SLIME_MAX0-1) {
			eState = BLOW_OFF;
			CGameScene::mPauseFlag = true;
			mFlagBG = true;
		}
		break;
		/*吹き飛ばすとダメージが入る説明*/
	case CTutorial::BLOW_OFF:
		/*キーを押すと次の説明に*/
		if (CKey::once(VK_RETURN)) {
			mFlagText = false;
			mFlagBG = false;
			CGameScene::mPauseFlag = false;
		}
		//敵をすべて倒すとテキスト切り替えと高台にリスポーン
		if(CSceneModel::mEnemyCount == 0){
			//高台の敵を増やす
			for (int i = 0; i < SLIME_MAX1; i++) {
				/*位置が被らないようにする*/
				const CVector3 pos = CVector3(-5 * i, 0.0f, 5 * i);
				CSlime *sl;
				sl = CSceneModel::GetInstance()->SlimeAdd(ENEMY_RESP_1, pos);//スライム
				sl->mFlagDecoy = true;
			}
			eState = HIGH_HILL_SLI;
			CGameScene::mPauseFlag = true;
		}
		break;
		/*高台説明*/
	case CTutorial::HIGH_HILL_SLI:
		mFlagText = true;
		mFlagBG = true;
		/*エンターを押すと次のテキストに*/
		if (CKey::once(VK_RETURN)) {
			eState = JUMP;
			mFlagBG = false;
			CGameScene::mPauseFlag = false;
		}
		break;
		/*ジャンプ説明*/
	case CTutorial::JUMP:
		Col.mpCombinedMatrix = &CMap::GetInstance()->Matrix(ENEMY_RESP_1);
		/*高台のリスポーン地点に近づくと次のテキスト表示に*/
		ChangeFlag = CCollision::CollisionShpere(plCol.GetUpdate(), Col.GetUpdate());
		/*上にいるなら*/
		if (ChangeFlag) {
			eState = PUSH_OFF;
			mFlagBG = true;
			mFlagText = true;
			CGameScene::mPauseFlag = true;
		}
		/*敵をすべて倒すとボスの説明*/
		if (CSceneModel::mEnemyCount == 0) {
			CSceneModel::GetInstance()->KingSlimeAdd();//キングスライム出現
			eState = KING_KILL;
			mFlagBG = true;
			mFlagText = true;
		}
		break;
		/*高台から落とそう*/
	case CTutorial::PUSH_OFF:
		/*キーを押すといったん消す*/
		if (CKey::once(VK_RETURN)) {
			mFlagBG = false;
			mFlagText = false;
			CGameScene::mPauseFlag = false;
		}
		/*敵をすべて倒すとボスの説明*/
		if (CSceneModel::mEnemyCount == 0) {
			CSceneModel::GetInstance()->KingSlimeAdd();//キングスライム出現
			eState = KING_KILL;
			mFlagBG = true;
			mFlagText = true;
		}
		break;
		/*キングを倒そう*/
	case CTutorial::KING_KILL:
		if (CKey::once(VK_RETURN)) {
			eState = SPECIAL_ATTACK;
			CGameScene::mPauseFlag = true;
		}
		break;
		/*必殺技説明*/
	case CTutorial::SPECIAL_ATTACK:
		if (CKey::once(VK_RETURN)) {
			eState = ARRAY;
			CGameScene::mPauseFlag = false;
		}
		break;
	case CTutorial::ARRAY:
#define ENEMY_MAX 20
		/*スライムがリスポーンしてくる*/
		if (CConvenient::Time(&mTime, 6.5f) && CSceneModel::mEnemyCount <= ENEMY_MAX) {
			CVector3 pos = CVector3(rand() % 4,0.0f,rand() % 4);
			CSceneModel::GetInstance()->SlimeAdd(ENEMY_RESP_2,pos);//スライム
			
			mTime = 0.0f;
		}
		break;
	default:
		break;
	}
	/*UV張替え*/
	mRect.SetUv(&mTex, TEX_SIZE(mVer[eState]));
}

/*描画*/
void CTutorial::Render(){
	/*チュートリアル中なら*/
	if (eState < ARRAY){
		CRectangle2::Disp2D_Start();//2D処理開始
		/*描画開始*/
		if  (mFlagBG)mBG.Render();
		if(mFlagText)mRect.Render();
		/*描画終了*/
		CRectangle2::Disp2D_Exit();//2D処理終了
	}
}
