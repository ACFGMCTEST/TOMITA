#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include <math.h>	//数学ライブラリのインクルード

#include "Define.h"		//
#include "CCamera.h"	//カメラクラスのインクルード
#include "CModel.h"		//
#include "CModelObj.h"	//
#include "CModelX.h"	//
#include "CLight.h"		//
#include "CCollision.h"	//

//オブジェクトの種類を定義
enum EObjectType {
	ENone,
	EPlayer,	//プレイヤー
	EEnemy1,	//敵1
	EEnemy2,	//敵2
	EBeamP,		//ビーム（プレイヤー発）
	EBeamE,		//ビーム（敵発）
};

class CGame {
public:
	static CVector3D player_pos;
	static CVector3D shift_pos;
};

CVector3D CGame::player_pos(0.0f, 0.0f, 0.0f);
CVector3D CGame::shift_pos(0.0f, 0.0f, 0.0f);

class CKey {
	static bool flg[256];
public:
	static bool push(char k);
	static bool once(char k);

};
bool CKey::flg[256];

bool CKey::push(char k) {
	return (GetKeyState(k) & 0x8000)==0  ? false: true;
}

bool CKey::once(char k) {
	if (GetKeyState(k) & 0x8000) {
		if (flg[k]) {
			return false;
		}
		else {
			flg[k] = true;
			return true;
		}
	}
	else {
		flg[k] = false;
	}
	return false;
}


class CBase : public CModel {
protected:
	bool enabled;
	CVector3D forward;
	float speed;
	EObjectType type;
//	bool collisionFlg;

public:
	CBase() :
		enabled(true),speed(0.0f),type(ENone)//, collisionFlg(true)
	{}

	bool getEnabled() { return enabled; }
	EObjectType getType() { return type; }

	void setCollisionFlg(bool b) {
//		collisionFlg = b;
	}

	void setEnabled(bool b) {
		enabled = b;
	}

	void setType(EObjectType t) {
		type = t;
	}

	void setForward(CVector3D fwd) {
		forward = fwd;
	}

	void setSpeed(float s) {
		speed = s;
	}

	virtual void update() {
		m_pos = m_pos + CGame::shift_pos;
		UpdateMatrix();
	}

	void RenderM(CMatrix &m) {}

	virtual void render() {
		RenderM(m_matrix);
	}

	virtual void onCollision(CBase *p) {

	}

	bool Load(const char *f) {
		return true;
	}

	void Release() {
		return;
	}

};

class CCharactorObj : public CBase {
public:
	CModelObj *pmodel;

	CCharactorObj() :
		pmodel(0) {
//		pmodel = new CModelObj();
	}

	virtual ~CCharactorObj() {
		Release();
	}

	void Release() {
		if (!pmodel) {
			delete pmodel;
		}
		pmodel = 0;
	}

	bool Load(const char *filename) {
		if (pmodel) {
			delete pmodel;
		}
		pmodel = new CModelObj();
		return pmodel->Load(filename);
	}

	void update() {
		CBase::update();
	}

	void RenderM(CMatrix &m) {
		pmodel->RenderM(m_matrix);
	}

	void render() {
		RenderM(m_matrix);
	}


	/*
	CCharactorObj& operator=(const CCharactorObj& b) {
		if (pmodel) {
			delete pmodel;
		}
		pmodel = new CModelObj();
		*pmodel = *(b.pmodel);
		return (*this);
	}
	*/

};

class CCharactorX : public CBase {
public:
	CModelX *pmodel;

	CCharactorX() :
		pmodel(0) {}

	~CCharactorX() {
		Release();
	}

	void Release() {
		if (!pmodel) {
			delete pmodel;
		}
		pmodel = 0;
	}

	bool Load(const char *filename) {
		if (pmodel) {
			delete pmodel;
		}
		pmodel = new CModelX();
		return pmodel->Load(filename);
	}

	void update() {
		CBase::update();
	}

	void RenderM(CMatrix &m) {
		pmodel->RenderM(m);
	}

	void render() {
		RenderM(m_matrix);
	}
};

class CMap {
public:
	CCharactorObj sky;
	CCharactorObj field[9];

	void init() {
		sky.Load("sky.obj");
		sky.m_pos = CVector3D(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				field[i * 3 + j].Load("plane.obj");
				field[i * 3 + j].m_pos = CVector3D(j * 400 - 400, 0.0f, i * 400 - 400);
			}
		}
	}

	void update() {
		sky.m_pos = CGame::player_pos;
		sky.m_pos.y = 0.0f;
		sky.UpdateMatrix();
		for (int i = 0; i < 9; i++) {
			field[i].UpdateMatrix();
		}
	}

	void render() {
		sky.render();
		for (int i = 0; i < 9; i++) {
			field[i].render();
		}
	}

};

class CCollider {
public:
	CBase *Pbase;		//親インスタンスへのポインタ
	CVector4D m_pos;	//球　中心座標
	float	radius;		//球　半径
	CCollider() :
		Pbase(0), radius(0.0f)
		, m_pos(0.0f, 0.0f, 0.0f, 1.0f)
	{}
	//p:親のインスタンス　c:球の中心座標（ローカル座標）　r:球の半径
	CCollider(CBase *p, const CVector3D &c, float r) :
		Pbase(p), radius(r)
	{
		m_pos.v[0] = c.x;
		m_pos.v[1] = c.y;
		m_pos.v[2] = c.z;
		m_pos.v[3] = 1.0f;
	}
	//衝突検出　c:相手のコライダ
	bool collision(const CCollider& c) {
		CVector4D p, e;
		p = Pbase->getMatrix() * m_pos;	//自分の中心座標をワールド座標へ
		e = c.Pbase->getMatrix() * c.m_pos;	//相手の中心座標をワールド座標へ
		//球による衝突検出
		return !CCollision::CollisionShpere(CVector3D(p.x, p.y, p.z), radius, CVector3D(e.x, e.y, e.z), c.radius);
	}
};

#include <list>		//リストを使用する
/*
タスク管理クラス
タスクシステムの管理を行う
*/
class CTaskManager {
private:	//privateは他のクラスからアクセスできない
	//唯一のタスク管理クラスのインスタンス（シングルトン）
	static CTaskManager* tm;
	//リストデータの作成
	std::list<CBase*> list;
	//コリジョンリストの作成
	std::list<CCollider*> collision;
	//デフォルトコンストラクタ
	CTaskManager() {}
public:
	//デストラクタ
	~CTaskManager() {
	}
	/*
	タスク管理クラスのインスタンスの取得
	*/
	static CTaskManager* CTaskManager::GetInstance();
	/*
	更新処理
	全インスタンスの更新、および衝突判定
	*/
	void CTaskManager::update() {
		/*衝突判定*/
		std::list<CCollider*>::iterator itrc1;	//コリジョンリストのイテレータを取得
		std::list<CCollider*>::iterator itrc2;	//コリジョンリストのイテレータを取得
		//リストの最初から最後まで繰り返し
		for (itrc1 = tm->collision.begin(); itrc1 != tm->collision.end(); itrc1++) {
			//インスタンスが有効
			if ((*itrc1)->Pbase->getEnabled()) {
				//衝突判定の相手分繰り返す
				for (itrc2 = itrc1; itrc2 != tm->collision.end(); itrc2++) {
					try {
						if ((*itrc2)->Pbase->getEnabled()) {
							//同じインスタンスは処理しない
							if ((*itrc1) != (*itrc2)) {
								//衝突している時
								if ((*itrc1)->collision(*(*itrc2))) {
									(*itrc1)->Pbase->onCollision((*itrc2)->Pbase);	//衝突処理を呼び出す
									(*itrc2)->Pbase->onCollision((*itrc1)->Pbase);	//衝突処理を呼び出す
								}
							}
						}
					}
					catch (...) {
						itrc2 = collision.erase(itrc2);	//リストから削除
						if (itrc2 == tm->collision.end())	//リストの最後の場合は繰り返し終了
							break;
					}
				}
			}
		}
		std::list<CBase*>::iterator itr;	//リストのイテレータを取得
		//リストの最初から最後まで繰り返し
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//インスタンスの有効フラグが有効の場合
			if ((*itr)->getEnabled()) {
				(*itr)->update();	//有効な場合、更新処理を呼ぶ
			}
		}
		//コリジョンリストの最初から最後まで繰り返し
		for (itrc1 = tm->collision.begin(); itrc1 != tm->collision.end(); itrc1++) {
			//インスタンスが無効
			if ((*itrc1)->Pbase->getEnabled()==false) {
				itrc1 = collision.erase(itrc1);		//リストから削除
				if (itrc1 == tm->collision.end())	//リストの最後の場合は繰り返し終了
					break;
			}
		}

		//リストの最初から最後まで繰り返し
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//インスタンスの有効フラグが無効の場合
			if ((*itr)->getEnabled() == false) {
				delete (*itr);	//インスタンスを削除
				itr = list.erase(itr);	//リストから削除
				if (itr == tm->list.end())	//リストの最後の場合は繰り返し終了
					break;
			}
		}
	}
	/*
	追加処理
	インスタンスをリストに追加する
	*/
	void CTaskManager::add(CBase* r) {
		list.push_back(r);	//リストに追加する
	}
	/*
	追加処理
	インスタンスをリストとコリジョンリストに追加する
	*/
	void CTaskManager::addCollision(CCollider* r) {
		collision.push_back(r);	//リストに追加する
	}
	/*
	描画処理
	全インスタンスの描画処理を呼び出す
	*/
	void render() {
		std::list<CBase*>::iterator itr;	//イテレータ取得
		//リストの最初から最後まで繰り返し
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//インスタンスが有効
			if ((*itr)->getEnabled()) {
				(*itr)->render();	//描画処理を呼び出す
			}
		}
	}
	/*
	廃棄処理
	全インスタンスの破棄
	*/
	void destroy() {
		std::list<CBase*>::iterator itr;
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			delete *itr;	//インスタンスの削除
		}
		list.clear();	//リストのクリア
		collision.clear();
		delete tm;	//タスクマネージャのインスタンスの削除
		tm = 0;	//ポインタの初期化
	}
};
//唯一のタスク管理クラスのインスタンス（シングルトン）
CTaskManager* CTaskManager::tm = 0;
/*
タスク管理クラスのインスタンスの取得
*/
CTaskManager* CTaskManager::GetInstance() {
	//インスタンスがなければ生成する
	if (tm == 0) {
		tm = new CTaskManager();
		tm->list.clear();	//リストのクリア
	}
	return tm;	//インスタンスのポインタ値を返す
}

class CBeam : public CCharactorObj
{
public:
	float sx;	//Xサイズ
	float sy;	//Yサイズ
	float sz;	//Zサイズ
	CVector3D target_pos; //移動場所
	float m_trail;
	float m_life;
	CCollider collider;
	int hp;
	CBeam::CBeam() : CBeam(ENone, E_BEAM_SPEED, 0, CVector4D(1.0f, 1.0f, 1.0f, 1.0f))
	{}
	// t: type sp:speed h:hp c:color
	CBeam::CBeam(EObjectType t, float sp, int h, CVector4D c) : 
		target_pos(0.0f, 0.0f, 0.0f), sx(0.05f), sy(0.05f), sz(1.0f), m_trail(0.0f), m_life(0),
		collider(this, CVector3D(0.0f, 0.0f, 1.0f), 0.05f), hp(h)
	{
		pmodel = new CModelObj();
		type = t;
		InitBoxMesh(sx, sy, sz, c.r, c.g, c.b, c.a);
		CTaskManager::GetInstance()->addCollision(&collider);
		speed = sp;
	}
	~CBeam() {
		if (pmodel) {
			delete pmodel;
			pmodel = 0;
		}
	}
	void CBeam::InitBoxMesh(float sx, float sy, float sz) {
		InitBoxMesh(sx, sy, sz, 1.0f, 1.0f, 0.0f, 1.0f);
	}
	void CBeam::InitBoxMesh(float sx, float sy, float sz, float r, float g, float b, float a)
	{
		CVector3D pos(0, 0, 0);
		CVector3D len(sx, sy, sz);
		this->sx = sx;
		this->sy = sy;
		this->sz = sz;

		int FaceNum = 12;
		pmodel->m_vertexNum = 3 * FaceNum;

		//描画用頂点配列を作成
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//描画用法線配列を作成
		pmodel->m_pNormalAry = new CVector3D[pmodel->m_vertexNum];

		pmodel->m_pVertexAry[0] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[1] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[2] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pNormalAry[0] = pmodel->m_pNormalAry[1] = pmodel->m_pNormalAry[2] = CVector3D(0.0f, 0.0f, 1.0f);

		pmodel->m_pVertexAry[3] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[4] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[5] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pNormalAry[3] = pmodel->m_pNormalAry[4] = pmodel->m_pNormalAry[5] = CVector3D(0.0f, 0.0f, 1.0f);

		pmodel->m_pVertexAry[6] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pVertexAry[7] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pVertexAry[8] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pNormalAry[6] = pmodel->m_pNormalAry[7] = pmodel->m_pNormalAry[8] = CVector3D(0.0f, 0.0f, -1.0f);

		pmodel->m_pVertexAry[9] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pVertexAry[10] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pVertexAry[11] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pNormalAry[9] = pmodel->m_pNormalAry[10] = pmodel->m_pNormalAry[11] = CVector3D(0.0f, 0.0f, -1.0f);

		pmodel->m_pVertexAry[12] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pVertexAry[13] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[14] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pNormalAry[12] = pmodel->m_pNormalAry[13] = pmodel->m_pNormalAry[14] = CVector3D(0.0f, 1.0f, 0.0f);

		pmodel->m_pVertexAry[15] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pVertexAry[16] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[17] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pNormalAry[15] = pmodel->m_pNormalAry[16] = pmodel->m_pNormalAry[17] = CVector3D(0.0f, 1.0f, 0.0f);

		pmodel->m_pVertexAry[20] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pVertexAry[19] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[18] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pNormalAry[18] = pmodel->m_pNormalAry[19] = pmodel->m_pNormalAry[20] = CVector3D(0.0f, -1.0f, 0.0f);

		pmodel->m_pVertexAry[23] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pVertexAry[22] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[21] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pNormalAry[21] = pmodel->m_pNormalAry[22] = pmodel->m_pNormalAry[23] = CVector3D(0.0f, -1.0f, 0.0f);

		pmodel->m_pVertexAry[24] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[25] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[26] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pNormalAry[24] = pmodel->m_pNormalAry[25] = pmodel->m_pNormalAry[26] = CVector3D(1.0f, 0.0f, 0.0f);

		pmodel->m_pVertexAry[27] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[28] = CVector3D(pos.x + len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pVertexAry[29] = CVector3D(pos.x + len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pNormalAry[27] = pmodel->m_pNormalAry[28] = pmodel->m_pNormalAry[29] = CVector3D(1.0f, 0.0f, 0.0f);

		pmodel->m_pVertexAry[32] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[31] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z + len.z);
		pmodel->m_pVertexAry[30] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pNormalAry[30] = pmodel->m_pNormalAry[31] = pmodel->m_pNormalAry[32] = CVector3D(-1.0f, 0.0f, 0.0f);

		pmodel->m_pVertexAry[35] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z + len.z);
		pmodel->m_pVertexAry[34] = CVector3D(pos.x - len.x, pos.y - len.y, pos.z - len.z);
		pmodel->m_pVertexAry[33] = CVector3D(pos.x - len.x, pos.y + len.y, pos.z - len.z);
		pmodel->m_pNormalAry[33] = pmodel->m_pNormalAry[34] = pmodel->m_pNormalAry[35] = CVector3D(-1.0f, 0.0f, 0.0f);

		pmodel->m_material.m_diffuse[0] = r;
		pmodel->m_material.m_diffuse[1] = g;
		pmodel->m_material.m_diffuse[2] = b;
		pmodel->m_material.m_diffuse[3] = a;

		pmodel->m_material.m_ambient[0] = 0.0f;
		pmodel->m_material.m_ambient[1] = 0.0f;
		pmodel->m_material.m_ambient[2] = 0.0f;
		pmodel->m_material.m_ambient[3] = 0.0f;

		pmodel->m_material.m_specular[0] = r;
		pmodel->m_material.m_specular[1] = g;
		pmodel->m_material.m_specular[2] = b;
		pmodel->m_material.m_specular[3] = a;

		pmodel->m_material.m_shininess = 0.0f;
	}

	void CBeam::update()
	{
		if (!enabled)
			return;

		if (m_trail <= 0.0f) {

/*			CBeam *b = new CBeam();
			*b = *this;
			b->setArray(*this);
			b->m_trail = BEAM_LIFE_TIME;
			CTaskManager::GetInstance()->add(b);
*/
/*			switch (b->sbt) {
			case CBeam::SBT::PLAYER:
			CBeamManager::GetInstance()->Add(b);
			break;
			case CBeam::SBT::ENEMY:
			CEBeamManager::GetInstance()->Add(b);
			break;
			}
*/
			CVector3D diff = target_pos - m_pos;
			diff.Normalize();
			m_pos += diff * speed;
			m_life -= 1.0f * speed;
			if (m_life <= 0.0f) {
				enabled = false;
				return;
			}
		}
		else
		{
			pmodel->m_material.m_diffuse[3] -= m_trail;
			if (pmodel->m_material.m_diffuse[3] <= 0.0f) {
				enabled = false;
			}
		}
		CBase::update();
	}

	void CBeam::UpdateMatrix()
	{
		CMatrix translate;
		translate.SetIndentity();
		translate.m03 = m_pos.x;
		translate.m13 = m_pos.y;
		translate.m23 = m_pos.z;

		m_matrix = translate * m_rotMtx;
	}
	void CBeam::setDiffuse(float r, float g, float b, float a) {
		pmodel->m_material.m_diffuse[0] = r;
		pmodel->m_material.m_diffuse[1] = g;
		pmodel->m_material.m_diffuse[2] = b;
		pmodel->m_material.m_diffuse[3] = a;
	}	//線分との衝突判定
	float* getDiffuse();

	void CBeam::Start(const CVector3D& pos, const CVector3D& target) {
		CVector3D fwd(0.0f, 0.0f, 1.0f);
		m_pos = pos;
		target_pos = target;
		enabled = true;

		m_rotMtx.RotationAxis(fwd, m_pos, target_pos);

		m_life = (pos - target).Length();
	}
	//	void Render();

	//コピーコンストラクタ
	CBeam(const CBeam& b) {
		//描画用頂点配列を作成
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//描画用法線配列を作成
		pmodel->m_pNormalAry = new CVector3D[pmodel->m_vertexNum];

		memcpy(pmodel->m_pVertexAry, b.pmodel->m_pVertexAry, sizeof(CVector3D) * pmodel->m_vertexNum);
		memcpy(pmodel->m_pNormalAry, b.pmodel->m_pNormalAry, sizeof(CVector3D) * pmodel->m_vertexNum);
	}
	//代入演算子
	CBeam& CBeam::setArray(const CBeam& b) {
		//	m_vertexNum = b.m_vertexNum;
		//描画用頂点配列を作成
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//描画用法線配列を作成
		pmodel->m_pNormalAry = new CVector3D[pmodel->m_vertexNum];

		memcpy(pmodel->m_pVertexAry, b.pmodel->m_pVertexAry, sizeof(CVector3D) * pmodel->m_vertexNum);
		memcpy(pmodel->m_pNormalAry, b.pmodel->m_pNormalAry, sizeof(CVector3D) * pmodel->m_vertexNum);

		//	m_material = b.m_material;
		//	m_alive = b.m_alive;

		return(*this);
	}

	void onCollision(CBase *p) {
		switch (type) {
		case EBeamP:
			switch (p->getType()) {
			case EEnemy1:
			case EEnemy2:
//				m_life = 0.0f;
				enabled = false;
				break;
			default:
				break;
			}
			break;
		case EBeamE:
			switch (p->getType()) {
			case EPlayer:
				enabled = false;
				break;
			default:
				break;
			}
			break;
		}
	}
};

class CParticle : public CCharactorObj {
public:
	float scale;
	int timer;
	CParticle() : scale(0.5f), timer(10)
	{
		m_scale.x = scale;
		m_scale.y = scale;
		m_scale.z = 1.0f;
	}

	void update() {
		if (timer < 0) {
			enabled = false;
		}
		else {
			pmodel->m_material.m_diffuse[3] = 0.5f;
			m_pos = m_pos + forward * speed;
			CBase::update();
			timer--;
		}
	}

	void UpdateMatrix()
	{
		m_transMtx.Transelate(m_pos.x, m_pos.y, m_pos.z);
		m_scaleMtx.Scale(scale, scale, 1.0f);
		m_rotMtx = CCamera::getCamera()->getMatrix();
		m_rotMtx.f[12] = m_rotMtx.f[13] = m_rotMtx.f[14] = 0.0f;
		m_rotMtx = m_rotMtx.getInverse();
		m_matrix = m_transMtx * m_rotMtx * m_scaleMtx;
	}

	void render() {
		CCharactorObj::render();
	}

};

CParticle Particle;

class CEffect {
public:
	int imax;
	CEffect() : imax(100) {}
	void Start(const CParticle& r, CVector3D pos) {
		CParticle *p;
		for (int i = 0; i < imax; i++) {
			p = new CParticle();
			*p = r;
			p->m_pos = pos;
			CMatrix mtx, mty, mtz;
			mtx.RotationX(getRadian());
			mty.RotationY(getRadian());
			mtz.RotationZ(getRadian());
			mtx = mtx * mty * mtz;
			CVector4D v4(0.0f, 0.0f, 1.0f, 1.0f);
			v4 = mtx * v4;
			p->setForward(CVector3D(v4.x, v4.y, v4.z));
			p->setSpeed( rand() % 4 / 10.0f);
			CTaskManager::GetInstance()->add(p);
		}
	}

	float getRadian() {
		return rand() % 360 * M_PI / 180.0f;
	}
};

class CBar : public CBase {
public:
	CBase *parent;
	CVector3D vertex[4];
	CVector3D normal[4];
	CVector4D color;
	float maxf;
	float value;
	float size;

	CBar() : CBar(0)
	{}

	CBar(CBase *p) : color(0.0f, 0.0f, 0.0f, 1.0f),
		maxf(0.0f), value(0.0f), size(0.0f), parent(p)
	{
		vertex[0] = CVector3D(-1.0f, 0.5f, 0.0f);
		vertex[1] = CVector3D(-1.0f, 0.0f, 0.0f);
		vertex[2] = CVector3D(1.0f, 0.0f, 0.0f);
		vertex[3] = CVector3D(1.0f, 0.5f, 0.0f);
		normal[0] = normal[1] = normal[2] = normal[3] = CVector3D(0.0f, 0.0f, 1.0f);
		m_scale.y = 0.2;

	}

	void setMVSC(float m, float v, float s, CVector4D c) {
		maxf = m;
		value = v;
		size = s;
		color = c;
		vertex[0].x = vertex[1].x = -size / 2.0f;
		vertex[2].x = vertex[3].x = size / 2.0f;
	}

	void update() {
		vertex[2].x = size * value / maxf - size / 2.0f;
		vertex[3].x = size * value / maxf - size / 2.0f;
		m_transMtx.Transelate(m_pos.x, m_pos.y, m_pos.z);
		m_matrix = m_transMtx;
	}

	void render() {
		GLfloat diffuse[] = { color.r, color.g, color.b, color.a };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

		glPushMatrix();

		glMultMatrixf(m_matrix.f);
		
		glBegin(GL_TRIANGLES);
		glNormal3f(normal[0].x, normal[0].y, normal[0].z);
		glVertex3f(vertex[0].x, vertex[0].y, vertex[0].z);
		glNormal3f(normal[1].x, normal[1].y, normal[1].z);
		glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
		glNormal3f(normal[3].x, normal[3].y, normal[3].z);
		glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);

		glNormal3f(normal[1].x, normal[1].y, normal[1].z);
		glVertex3f(vertex[1].x, vertex[1].y, vertex[1].z);
		glNormal3f(normal[2].x, normal[2].y, normal[2].z);
		glVertex3f(vertex[2].x, vertex[2].y, vertex[2].z);
		glNormal3f(normal[3].x, normal[3].y, normal[3].z);
		glVertex3f(vertex[3].x, vertex[3].y, vertex[3].z);
		glEnd();
		
		/*
//		glMultMatrixf(m.f);

//		m_material.Map();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertex);
		glNormalPointer(GL_FLOAT, 0, normal);

		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
//		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		*/

		glPopMatrix();

	}
};

class CHpbar : CBase {
public:
	CBase *parent;
	CBar bg;
	CBar fg;
	CVector3D local_pos;

	CHpbar() {}
	CHpbar(CBase *p) : parent(p), bg(p), fg(p) {}

	void setMVSCP(float m, float s, CVector4D c, CVector3D pos) {
		bg.setMVSC(m, m, s, CVector4D(0.0f, 0.0f, 0.0f, 1.0f));
		bg.m_pos.z = -0.01f;
		fg.setMVSC(m, m, s, c);
		local_pos = pos;
	}

	void update() {
		m_pos = parent->getPos() + local_pos;
		UpdateMatrix();
		bg.update();
		fg.update();
	}

	void UpdateMatrix()
	{
		m_transMtx.Transelate(m_pos.x, m_pos.y, m_pos.z);
		m_rotMtx = CCamera::getCamera()->getMatrix();
		m_rotMtx.f[12] = m_rotMtx.f[13] = m_rotMtx.f[14] = 0.0f;
		m_rotMtx = m_rotMtx.getInverse();
		m_matrix = m_transMtx * m_rotMtx  * m_scaleMtx;
	}

	void render() {
		glPushMatrix();
		glMultMatrixf(m_matrix.f);

		bg.render();
		fg.render();

		glPopMatrix();
	}

	void setValue(float v) {
		fg.value = v;
	}

	float getValue() {
		return fg.value;
	}

};


class CPlayer : public CCharactorX {
public:
	CVector3D baseRadian;	//現在の回転値
	CCollider collider;		//コライダ
	int fb;					//発射タイマー
	CHpbar hpbar;			//HPバー
	CVector3D t_pos, t_rot, t_scale;	//再出撃用退避データ

	CPlayer() :
		collider(this,CVector3D(0.0f, 0.0f, 0.0f),1.5f),
		fb(P_FB), hpbar(this)
	{
		speed = P_SPEED;	//移動速度設定
		type = EPlayer;		//タイプ設定
		CTaskManager::GetInstance()->addCollision(&collider);	//コライダを衝突リストへ追加
		//HPバーを設定
		hpbar.setMVSCP(P_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 2.5f, 0.0f));
	}
	//初期化処理
	void init(CVector3D pos, CVector3D rot, CVector3D scale) {
		m_pos = t_pos = pos;	//位置座標を設定
		m_rot = t_rot = rot;	//回転値（ラジアン）を設定
		m_scale = t_scale = scale;	//拡縮値を設定
		//HPバーを設定
		hpbar.setMVSCP(P_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 2.5f, 0.0f));
	}
	//再初期化
	void reset() {
		init(t_pos, m_rot, m_scale);
	}
	//更新処理
	void update() {
		//JキーとLキーで回転
		if (CKey::push('J') || CKey::push('L')){
			baseRadian = CCamera::getCamera()->m_rot;
			m_rot.y = baseRadian.y;
		}
		//Wキーで前方
		if (CKey::push('W')){
			baseRadian = CCamera::getCamera()->m_rot;
			m_rot.y = baseRadian.y;
			m_pos = m_pos + forward;
		}
		//SDAが押されていればfalseにする
		bool flg = true;
		//Sキー：後ろ向き（180度回転）
		if (CKey::push('S')) {
			m_rot.y = baseRadian.y + 180.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
		
//4		//Dキー：右向き（-90度回転）
		if (CKey::push('D')) {
			m_rot.y = baseRadian.y + -90.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
//5		//Aキー：左向き（90度回転）
		if (CKey::push('A')) {
			m_rot.y = baseRadian.y + 90.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
		//ASDキーが押されてない場合は前向き
		if (flg) {
			m_rot.y = baseRadian.y;
		}
		//前方のベクトル設定
		forward = m_rotMtx * CVector3D(0.0f, 0.0f, 1.0f) * speed;

		//座標補正の計算
		CGame::shift_pos = CVector3D(0.0f, 0.0f, 0.0f);
		if (m_pos.x < -200.0f) {
			CGame::shift_pos.x = 400.0f;
		}
		if (m_pos.x > 200.0f) {
			CGame::shift_pos.x = -400.0f;
		}
		if (m_pos.z < -200.0f) {
			CGame::shift_pos.z = 400.0f;
		}
		if (m_pos.z > 200.0f) {
			CGame::shift_pos.z = -400.0f;
		}
		//ビーム発射間隔減算
		if (fb-- < 0) {
			fb = 0;
		}
		//スペースキー：ビーム発射
		if (CKey::push(' ') && fb == 0) {
			//ビームの作成
			CBeam *b = new CBeam(EBeamP, P_BEAM_SPEED, P_BEAM_HP, CVector4D(1.0f, 1.0f, 0.0f, 1.0f));
//7			//ビームの発射
			b->Start(m_pos, m_pos + m_rotMtx * CVector3D(0.0f, 0.0f, 1.0f)*P_BEAM_RANGE);

//7			//ビームを追加
			CTaskManager::GetInstance()->add(b);
		
			//発射間隔を設定
			fb = P_FB;
		}
		//更新処理
		CBase::update();
		//プレイヤーの座標を退避
		CGame::player_pos = m_pos;
		//HPバーの更新
		hpbar.update();
	}

	void RenderM(CMatrix &m) {
		pmodel->RenderM(m_matrix);
	}
	//描画処理
	void render() {
		//機体の描画
		RenderM(m_matrix);
		//HPバーの描画
		hpbar.render();
	}
	//衝突処理
	void onCollision(CBase *p) {
		CEffect effect;
		switch (p->getType()) {
		case EBeamE:	//相手が敵ビームの時
			//ダメージ減算
			hpbar.setValue(hpbar.getValue() - ((CBeam*)(p))->hp);
			//エフェクト発生
			effect.Start(Particle, p->getPos());
			break;
		}
	}
};

class CEnemyBase : public CCharactorX {
protected:
	CCollider collider;	//コライダ
	CHpbar hpbar;		//HPバー
public:
	CVector3D target;	//移動先
	int targettime;		//移動先更新時間
	int fbtime;			//ビーム発射時間
	//移動先設定
	void setTarget() {
		//処理タイマーが0以下
		if (targettime <= 0) {
			//プレイヤーへのベクトルを計算
			target = CGame::player_pos;
			forward = target - m_pos;
			forward.Normalize();
			//プレイヤーへ向ける
			m_rot.y = atan2f(forward.x, forward.z);
			//処理タイマーの設定
			targettime = 60;
		}
		else {
			targettime--;	//処理タイマー減算
		}
	}
	//弾を発射
	void shot() {
		//発射タイマーが0以下の時
		if (fbtime <= 0) {
			//ターゲットへのベクトルを計算
			target = CGame::player_pos;
			forward = target - m_pos;
			forward.Normalize();
			//ターゲットへ向かせる
			m_rot.y = atan2f(forward.x, forward.z);
			//ビーム作成
			CBeam *b = new CBeam(EBeamE, E_BEAM_SPEED, E_BEAM_HP, CVector4D(1.0f, 0.5f, 0.5f, 1.0f));
			//ビーム発射
			b->Start(m_pos, m_pos + forward * E_BEAM_RANGE);
			//ビームを追加
			CTaskManager::GetInstance()->add(b);
			//発射タイマーを設定
			fbtime = E_FB;
		}
		else {
			fbtime--;	//発射タイマーを減算
		}
	}

	CEnemyBase() :
		collider(this, CVector3D(0.0f, 0.0f, 0.0f), 1.5f), hpbar(this), fbtime(E_FB) {
		speed = E_SPEED;	//移動速度設定
		type = ENone;
		CTaskManager::GetInstance()->addCollision(&collider);	//コライダを衝突リストへ追加
		//HPバーを設定
		hpbar.setMVSCP(E_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.5f, 0.0f));
	}
	//更新
	void update() {
		if (enabled) {
			CCharactorX::update();
			hpbar.update();	//HPバーを更新
			//HPが0以下の時、無効にする
			if (hpbar.getValue() <= 0) {
				enabled = false;
			}
		}
	}
	//描画
	void render() {
		if (enabled) {
			CCharactorX::render();
			hpbar.render();
		}
	}
	//衝突処理
	void onCollision(CBase *p) {
		CEffect effect;	//エフェクトの作成
		switch (p->getType()) {
		case EBeamP:	//衝突がプレイヤーのビームの時
			//ビームのダメージを減算
			hpbar.setValue(hpbar.getValue() - ((CBeam*)(p))->hp);
			//エフェクトスタート
			effect.Start(Particle, p->getPos());
			break;
		}
	}
	//再初期設定（リスポン用）
	void reset() {
		//HPバーの初期化
		hpbar.setMVSCP(E_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.5f, 0.0f));
		//コライダを再度衝突リストへ追加
		CTaskManager::GetInstance()->addCollision(&collider);
		//有効にする
		enabled = true;
		m_rot = CVector3D(0.0f, 0.0f, 0.0f);
		targettime = 0;
		fbtime = E_FB;
	}

};

class CEnemy1 : public CEnemyBase {
public:

	void update() {
//8		//移動先の設定
		setTarget();
//8		//弾を発射
		shot();
//8		//移動
		m_pos += forward * speed;
		//更新処理
		CEnemyBase::update();
	}

};

class CEnemy2 : public CEnemyBase {
public:

	void update() {
		//移動先の設定
		setTarget();
		//弾を発射
		shot();
		//移動
		m_pos += forward * speed;
		//更新処理
		CEnemyBase::update();
	}

};

class CRespawn : public CBase {
public:
	int time;	//リスポンするまでの時間
	EObjectType type;	//敵のタイプ
	CEnemyBase *penemy;	//敵のインスタンス
	CRespawn() : time(0), type(ENone), penemy(0) {}
	~CRespawn() {
		release();
	}
	//作成した敵の削除
	void release() {
		if (penemy) {
			delete penemy;
			penemy = 0;
		}
	}
	//	リスポン場所の初期設定
	//	type：敵のタイプ	pos:座標の値
	void init(EObjectType type, CVector3D pos) {
		//場所の座標設定
		m_pos = pos;
		switch (type) {
		case EEnemy1:	//敵１の時
			//敵作成
			penemy = new CEnemy1();
			penemy->Load("gundam3.s.x");
			penemy->m_pos = m_pos;
			penemy->setType(EEnemy1);
			break;
		case EEnemy2:	//敵２の時
			//敵作成
			penemy = new CEnemy2();
			penemy->Load("gund3.x");
			penemy->m_pos = m_pos;
			penemy->setType(EEnemy2);
			break;
		}
		//リスポン時間設定
		time = RESPAWN_TIME;
	}

	void update() {
		//敵は有効？
		if (penemy->getEnabled()) {
			penemy->update();
		}
		else {
			//リスポン時間が0以下
			if (time <= 0) {
				penemy->reset();
				penemy->m_pos = m_pos;
				penemy->setEnabled(true);
				time = RESPAWN_TIME;
			}
			else {
				time--;
			}
		}
	}

	void render() {
		penemy->render();
	}
};
//ゲームシーン
class CScenegame {
public:
	//状態遷移
	enum EStatus {
		Init,	//初期処理
		Game,	//ゲーム中
		Down,	//ダウン中
		Respawn	//リスポン
	};
	//マップ
	CMap map;
	//プレイヤー
	CPlayer	Player;
	//敵リスポン地点
	CRespawn *prespawn;
	//ゲームの状態
	EStatus status;

	CScenegame() : status(Init) {}

	~CScenegame() {
		gettm()->destroy();
	}

	CTaskManager* gettm() {
		return CTaskManager::GetInstance();
	}

	void update() {
		switch (status) {
		case Init:	//初期化
//1			//マップ初期化
			map.init();
//3			//プレイヤーモデルデータ読み込みと初期化
			Player.Load("sazabi.x");
			Player.init(
				CVector3D(0.0f, 2.0f, 0.0f),
				CVector3D(0.0f, 0.0f, 0.0f),
				CVector3D(0.8f, 0.8f, 0.8f));
			
//6			//敵を配置
			prespawn = new CRespawn();
			prespawn->init(EEnemy1, CVector3D(-10.0f, 2.0f, 45.0f));
			gettm()->GetInstance()->add(prespawn);
			prespawn = new CRespawn();
			prespawn->init(EEnemy2, CVector3D(20.0f, 2.0f, 30.0f));
			gettm()->GetInstance()->add(prespawn);

			//エフェクト素材読み込み
			Particle.Load("particle.obj");
			//ステータスをゲームへ
			status = Game;
			break;
		case Game:	//ゲーム中
//2			//カメラの設定
			setcamera();

//3			//プレイヤーの更新（最初）
			Player.update();
			
			//ビームや衝突の更新
			gettm()->update();
//1			//マップの更新（最後）
			map.update();

			//カメラ行列を反映
			glLoadMatrixf(CCamera::getCamera()->getMatrix().f);
//1			//マップの描画
			map.render();
//3			//プレイヤーの描画
			Player.render();
			
			//ビームなどの描画
			gettm()->render();
			//プレイヤーのHPが0以下
			if (Player.hpbar.getValue() <= 0) {
				status = Down;	//リスポン待ち
			}
			break;
		case Down:	//リスポン待ち
			setcamera();
			gettm()->update();
			//カメラ行列を反映
			glLoadMatrixf(CCamera::getCamera()->getMatrix().f);
			map.render();
			gettm()->render();
			if (CKey::once('Z')) {
				status = Respawn;
			}

			break;
		case Respawn:	//リスポン
			Player.reset();
			status = Game;
			break;
		}
	}
	//	カメラを回す
	//	Jキー：左を向く	Lキー：右を向く
	void setcamera() {
		CVector3D cam_pos(0.0f, 0.5f, -1.0f);	//カメラポジションの方向を決定
		CMatrix cam_matrix, rotx;
		if (CKey::push('J')) {
			CCamera::getCamera()->m_rot.y += 2.0f * M_PI / 180.0f;
		}
		if (CKey::push('L')) {
			CCamera::getCamera()->m_rot.y -= 2.0f * M_PI / 180.0f;
		}
		if (CKey::push('I')) {
			CCamera::getCamera()->m_rot.x += 2.0f * M_PI / 180.0f;
		}
		if (CKey::push('K')) {
			CCamera::getCamera()->m_rot.x -= 2.0f * M_PI / 180.0f;
		}
		rotx.RotationX(CCamera::getCamera()->m_rot.x);
		cam_matrix.RotationY(CCamera::getCamera()->m_rot.y);
		cam_pos = Player.m_pos + cam_matrix * rotx * cam_pos * 4.0f;	//カメラポジションの座標を決定
		//カメラの行列計算（ビュー行列）
		CCamera::getCamera()->LookAt(cam_pos, Player.getPos(), CVector3D(0.0f, 1.0f, 0.0f));
	}

};

//ゲームシーンを作成
CScenegame scenegame;

/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//行列の初期化
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//ゲームシーンの更新
	scenegame.update();

	//画面に表示
	glutSwapBuffers();
}

//関数のプロトタイプ宣言
void reshape(int, int);
void idle();

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);	//ディスプレイモード設定
	//ウィンドウの設定
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hello 3DProgramming");	//ウィンドウ作成
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);	//クリア色を白に設定

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

//ライトの設定
	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//メッシュシェーダー用
	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化

	//各種関数設定
	glutDisplayFunc(display);	//描画時の関数を指定
	glutReshapeFunc(reshape);	//ウィンドウ変形時の関数を指定
	glutIdleFunc(idle);			//待機時の関数を指定

	//メインループ
	glutMainLoop();

	return;
}

/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
	CCamera::getCamera()->SetSize(width, height);
	glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
}

LARGE_INTEGER last_time;	//前回のカウンタ値
//１秒間に６０回描画するように調節する
void idle() {
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値

	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//描画する関数を呼ぶ
	display();
}
