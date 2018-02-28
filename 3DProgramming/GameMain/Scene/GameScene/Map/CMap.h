
#ifndef MAP_HPP
#define MAP_HPP

#include "../../../Graphic/CShader.h"
#include "../../../../Base/CBase.h"
#include "../../../Graphic/CBox.h"
#include "../../../../Define/Define.h"
#include <iostream>
#include <vector>
#include "../../../Task/CTaskManager.h"
#include "../../../Collision/CCollider.h"
#include "../../../Csv/CCsv.h"

/*テクスチャサイズ*/
#define GROUND_CG -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y

/*配列からポジション*/
#define POS_Z(z) z * (MAPCHIP_SIZE*2) - CMap::mMapZ/2 * (MAPCHIP_SIZE*2)
#define POS_X(x) x * (MAPCHIP_SIZE*2) - CMap::mMapX/2 * (MAPCHIP_SIZE*2)
#define ARRAY_POS(x,y,z) CVector4(POS_X(x),y,POS_Z(z)) //配列内に書くもの

class CMap{
public:
	/*マップデータ格納用*/
	static CCsv mCsvMapData;			//マップデータ
	/*マップの座標値*/
	static int mMapX;
	static int mMapZ;

	/*VboId現在使っていない 小規模のものなので*/
	//GLuint VboId[3];

	static CCollider *mpGoalPlayer;//アクセス用
	static CCollider *mpGoalEnemy; //アクセス用
	static int mGoalCount;//ゴールのカウント

	CTaskManager mMapTaskManager;//マップのタスクマネージャー
	CBox mWallBox; //かべ
	/*タイルのテクスチャ*/
	CTexture mTexTile;

	/*ボックスの点情報*/
	std::vector<CVector3> mVer;
	std::vector<CVector3> mNormal;
	/*ボックス色情報*/
	float mDiffuse[4];
	float *mColorRGBA[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];

	GLuint mTextureId;			//テクスチャID
	CShader mShader;			//シェーダ
	GLuint	mMyVertexBuffer;	//Add Shader


	class MyColor4
	{
	public:
		float r, g, b, a;
		MyColor4(){}
		MyColor4(float cr, float cg, float cb, float ca) : r(cr), g(cg), b(cb), a(ca){}
	};
	std::vector<MyColor4> mColor;
	int mArrayCount;

	enum  E_PLANE
	{
		E_GROUND,
		E_WALL_LEFT,
		E_WALL_RIGHT,
		E_WALL_UP,
		E_WALL_DOWN,
		E_WALL_ARRAY
	};
	CCollider *mpColPlane[E_WALL_ARRAY];



	class CTile : public CTask{
	public:

		//CRectangle mRect[4];
		CRectangle mRect;
		float pos[3];
		CVector3 mPos;
		CMatrix44 matrix;



		CTile(CVector3 pos,CTexture &t){

			//テクスチャ読み込み
			/*初期化*/
			mPos = CVector3(0.0f, 0.0f, 0.0f);

			CVector3 v0(-MAPCHIP_SIZE, 0.0f, -MAPCHIP_SIZE);
			CVector3 v1(-MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE);
			CVector3 v2(MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE);
			CVector3 v3(MAPCHIP_SIZE, 0.0f, -MAPCHIP_SIZE);

			mRect.SetVertex(v0, v1, v2, v3);
			mRect.SetNormal(0.0f, 1.0f, 0.0f);

			mRect.SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			/*順番を決める*/
			ePriority = CTask::E_GROUND;
				 

			/*位置決定*/
			mPos = pos;
			/*色設定*/
			mRect.SetDiffuse(WHITE_COLOR);
			/*テクスチャ設定*/
			mRect.SetUv(&t, GROUND_CG);
			mRect.SetUvRot();//テクスチャを回転
		}

		//デストラクタ
		~CTile(){
		}
		
		void Render(){
			glPushMatrix();
			matrix.translate(mPos);
			glMultMatrixf(matrix.f);

			mRect.Render();

			glPopMatrix();
		}
	};


	/*マップデータ属性管理
	配列番号の機能一覧
	0	平地
	1	ジャンプ台
	2	加速床
	3	減速床
	4	プレイヤー
	5	相手
	6	ゴール自分
	7	ゴール相手
	8	坂
	9	高台
	A	たかい高台
	*/
	enum E_MAP
	{
		E_FLOOR_0 = '0',	//平らな場所
		E_Trampoline_1,		//ジャンプ台
		E_FAST_FLOOR_2,		//加速床　
		E_SLOW_FLOOR_3,		//減速床
		E_PLAYER_4,			//プレイヤー
		E_AI_5,				//相手
		E_GOAL_PLAYER_6,	//ゴール自分
		E_GOAL_ENEMY_7,		//ゴール相手
		E_SLOP_8,			//坂
		E_SLOP_END_9,			//坂端
		E_HIGH_BOX_A = 'A',		//高い高台

	};
	E_MAP eState = E_FLOOR_0;

	/*座標に指定された属性を返す*/
	static E_MAP MapState(int x, int z);
	/*座標値が現在のマップからはみ出してないあ判断*/
 	static bool FlagMapLimit(int x, int z);
	/*座標に指定したものがあった場合 trueを返す*/
	static bool FlagMapMacth(int x, int z, E_MAP state);
	//static char mNowMapDate[MAP_ARRAY_Z][MAP_ARRAY_X]; //今のマップデータ

	void Init();
	/*MAP要素数取得関数*/
	int MapArray(CCsv &csv, int Nonber);
	/*マップ初期配置関数*/
	void MapInit(CCsv &csv);
	/*あたり判定の初期化*/
	void ColInit();

	/*プレイヤーの初期リスポーンポジション*/
	static CVector3 PlayerFirstPos();
	/*エネミーの初期リスポーンポジション*/
	static CVector3 EnemyFirstPos();
	/*ゴールのポジション(エネミー)*/
	static CVector3 GoalEnemyFirstPos();
	/*ゴールのポジション(プレイヤー)*/
	static CVector3 GoalPlayerFirstPos();


	/*ポジションから配列会得*/
	static int ArrayX(float x);
	/*ポジションから配列会得*/
	static int ArrayZ(float z);



	CMap();
	~CMap();
	void Update();
	void Render();


};

#endif