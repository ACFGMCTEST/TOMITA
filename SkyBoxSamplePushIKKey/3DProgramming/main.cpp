#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include <math.h>	//���w���C�u�����̃C���N���[�h

#include "Define.h"		//
#include "CCamera.h"	//�J�����N���X�̃C���N���[�h
#include "CModel.h"		//
#include "CModelObj.h"	//
#include "CModelX.h"	//
#include "CLight.h"		//
#include "CCollision.h"	//

//�I�u�W�F�N�g�̎�ނ��`
enum EObjectType {
	ENone,
	EPlayer,	//�v���C���[
	EEnemy1,	//�G1
	EEnemy2,	//�G2
	EBeamP,		//�r�[���i�v���C���[���j
	EBeamE,		//�r�[���i�G���j
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
	CBase *Pbase;		//�e�C���X�^���X�ւ̃|�C���^
	CVector4D m_pos;	//���@���S���W
	float	radius;		//���@���a
	CCollider() :
		Pbase(0), radius(0.0f)
		, m_pos(0.0f, 0.0f, 0.0f, 1.0f)
	{}
	//p:�e�̃C���X�^���X�@c:���̒��S���W�i���[�J�����W�j�@r:���̔��a
	CCollider(CBase *p, const CVector3D &c, float r) :
		Pbase(p), radius(r)
	{
		m_pos.v[0] = c.x;
		m_pos.v[1] = c.y;
		m_pos.v[2] = c.z;
		m_pos.v[3] = 1.0f;
	}
	//�Փˌ��o�@c:����̃R���C�_
	bool collision(const CCollider& c) {
		CVector4D p, e;
		p = Pbase->getMatrix() * m_pos;	//�����̒��S���W�����[���h���W��
		e = c.Pbase->getMatrix() * c.m_pos;	//����̒��S���W�����[���h���W��
		//���ɂ��Փˌ��o
		return !CCollision::CollisionShpere(CVector3D(p.x, p.y, p.z), radius, CVector3D(e.x, e.y, e.z), c.radius);
	}
};

#include <list>		//���X�g���g�p����
/*
�^�X�N�Ǘ��N���X
�^�X�N�V�X�e���̊Ǘ����s��
*/
class CTaskManager {
private:	//private�͑��̃N���X����A�N�Z�X�ł��Ȃ�
	//�B��̃^�X�N�Ǘ��N���X�̃C���X�^���X�i�V���O���g���j
	static CTaskManager* tm;
	//���X�g�f�[�^�̍쐬
	std::list<CBase*> list;
	//�R���W�������X�g�̍쐬
	std::list<CCollider*> collision;
	//�f�t�H���g�R���X�g���N�^
	CTaskManager() {}
public:
	//�f�X�g���N�^
	~CTaskManager() {
	}
	/*
	�^�X�N�Ǘ��N���X�̃C���X�^���X�̎擾
	*/
	static CTaskManager* CTaskManager::GetInstance();
	/*
	�X�V����
	�S�C���X�^���X�̍X�V�A����яՓ˔���
	*/
	void CTaskManager::update() {
		/*�Փ˔���*/
		std::list<CCollider*>::iterator itrc1;	//�R���W�������X�g�̃C�e���[�^���擾
		std::list<CCollider*>::iterator itrc2;	//�R���W�������X�g�̃C�e���[�^���擾
		//���X�g�̍ŏ�����Ō�܂ŌJ��Ԃ�
		for (itrc1 = tm->collision.begin(); itrc1 != tm->collision.end(); itrc1++) {
			//�C���X�^���X���L��
			if ((*itrc1)->Pbase->getEnabled()) {
				//�Փ˔���̑��蕪�J��Ԃ�
				for (itrc2 = itrc1; itrc2 != tm->collision.end(); itrc2++) {
					try {
						if ((*itrc2)->Pbase->getEnabled()) {
							//�����C���X�^���X�͏������Ȃ�
							if ((*itrc1) != (*itrc2)) {
								//�Փ˂��Ă��鎞
								if ((*itrc1)->collision(*(*itrc2))) {
									(*itrc1)->Pbase->onCollision((*itrc2)->Pbase);	//�Փˏ������Ăяo��
									(*itrc2)->Pbase->onCollision((*itrc1)->Pbase);	//�Փˏ������Ăяo��
								}
							}
						}
					}
					catch (...) {
						itrc2 = collision.erase(itrc2);	//���X�g����폜
						if (itrc2 == tm->collision.end())	//���X�g�̍Ō�̏ꍇ�͌J��Ԃ��I��
							break;
					}
				}
			}
		}
		std::list<CBase*>::iterator itr;	//���X�g�̃C�e���[�^���擾
		//���X�g�̍ŏ�����Ō�܂ŌJ��Ԃ�
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//�C���X�^���X�̗L���t���O���L���̏ꍇ
			if ((*itr)->getEnabled()) {
				(*itr)->update();	//�L���ȏꍇ�A�X�V�������Ă�
			}
		}
		//�R���W�������X�g�̍ŏ�����Ō�܂ŌJ��Ԃ�
		for (itrc1 = tm->collision.begin(); itrc1 != tm->collision.end(); itrc1++) {
			//�C���X�^���X������
			if ((*itrc1)->Pbase->getEnabled()==false) {
				itrc1 = collision.erase(itrc1);		//���X�g����폜
				if (itrc1 == tm->collision.end())	//���X�g�̍Ō�̏ꍇ�͌J��Ԃ��I��
					break;
			}
		}

		//���X�g�̍ŏ�����Ō�܂ŌJ��Ԃ�
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//�C���X�^���X�̗L���t���O�������̏ꍇ
			if ((*itr)->getEnabled() == false) {
				delete (*itr);	//�C���X�^���X���폜
				itr = list.erase(itr);	//���X�g����폜
				if (itr == tm->list.end())	//���X�g�̍Ō�̏ꍇ�͌J��Ԃ��I��
					break;
			}
		}
	}
	/*
	�ǉ�����
	�C���X�^���X�����X�g�ɒǉ�����
	*/
	void CTaskManager::add(CBase* r) {
		list.push_back(r);	//���X�g�ɒǉ�����
	}
	/*
	�ǉ�����
	�C���X�^���X�����X�g�ƃR���W�������X�g�ɒǉ�����
	*/
	void CTaskManager::addCollision(CCollider* r) {
		collision.push_back(r);	//���X�g�ɒǉ�����
	}
	/*
	�`�揈��
	�S�C���X�^���X�̕`�揈�����Ăяo��
	*/
	void render() {
		std::list<CBase*>::iterator itr;	//�C�e���[�^�擾
		//���X�g�̍ŏ�����Ō�܂ŌJ��Ԃ�
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			//�C���X�^���X���L��
			if ((*itr)->getEnabled()) {
				(*itr)->render();	//�`�揈�����Ăяo��
			}
		}
	}
	/*
	�p������
	�S�C���X�^���X�̔j��
	*/
	void destroy() {
		std::list<CBase*>::iterator itr;
		for (itr = tm->list.begin(); itr != tm->list.end(); itr++) {
			delete *itr;	//�C���X�^���X�̍폜
		}
		list.clear();	//���X�g�̃N���A
		collision.clear();
		delete tm;	//�^�X�N�}�l�[�W���̃C���X�^���X�̍폜
		tm = 0;	//�|�C���^�̏�����
	}
};
//�B��̃^�X�N�Ǘ��N���X�̃C���X�^���X�i�V���O���g���j
CTaskManager* CTaskManager::tm = 0;
/*
�^�X�N�Ǘ��N���X�̃C���X�^���X�̎擾
*/
CTaskManager* CTaskManager::GetInstance() {
	//�C���X�^���X���Ȃ���ΐ�������
	if (tm == 0) {
		tm = new CTaskManager();
		tm->list.clear();	//���X�g�̃N���A
	}
	return tm;	//�C���X�^���X�̃|�C���^�l��Ԃ�
}

class CBeam : public CCharactorObj
{
public:
	float sx;	//X�T�C�Y
	float sy;	//Y�T�C�Y
	float sz;	//Z�T�C�Y
	CVector3D target_pos; //�ړ��ꏊ
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

		//�`��p���_�z����쐬
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//�`��p�@���z����쐬
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
	}	//�����Ƃ̏Փ˔���
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

	//�R�s�[�R���X�g���N�^
	CBeam(const CBeam& b) {
		//�`��p���_�z����쐬
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//�`��p�@���z����쐬
		pmodel->m_pNormalAry = new CVector3D[pmodel->m_vertexNum];

		memcpy(pmodel->m_pVertexAry, b.pmodel->m_pVertexAry, sizeof(CVector3D) * pmodel->m_vertexNum);
		memcpy(pmodel->m_pNormalAry, b.pmodel->m_pNormalAry, sizeof(CVector3D) * pmodel->m_vertexNum);
	}
	//������Z�q
	CBeam& CBeam::setArray(const CBeam& b) {
		//	m_vertexNum = b.m_vertexNum;
		//�`��p���_�z����쐬
		pmodel->m_pVertexAry = new CVector3D[pmodel->m_vertexNum];
		//�`��p�@���z����쐬
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
	CVector3D baseRadian;	//���݂̉�]�l
	CCollider collider;		//�R���C�_
	int fb;					//���˃^�C�}�[
	CHpbar hpbar;			//HP�o�[
	CVector3D t_pos, t_rot, t_scale;	//�ďo���p�ޔ��f�[�^

	CPlayer() :
		collider(this,CVector3D(0.0f, 0.0f, 0.0f),1.5f),
		fb(P_FB), hpbar(this)
	{
		speed = P_SPEED;	//�ړ����x�ݒ�
		type = EPlayer;		//�^�C�v�ݒ�
		CTaskManager::GetInstance()->addCollision(&collider);	//�R���C�_���Փ˃��X�g�֒ǉ�
		//HP�o�[��ݒ�
		hpbar.setMVSCP(P_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 2.5f, 0.0f));
	}
	//����������
	void init(CVector3D pos, CVector3D rot, CVector3D scale) {
		m_pos = t_pos = pos;	//�ʒu���W��ݒ�
		m_rot = t_rot = rot;	//��]�l�i���W�A���j��ݒ�
		m_scale = t_scale = scale;	//�g�k�l��ݒ�
		//HP�o�[��ݒ�
		hpbar.setMVSCP(P_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 2.5f, 0.0f));
	}
	//�ď�����
	void reset() {
		init(t_pos, m_rot, m_scale);
	}
	//�X�V����
	void update() {
		//J�L�[��L�L�[�ŉ�]
		if (CKey::push('J') || CKey::push('L')){
			baseRadian = CCamera::getCamera()->m_rot;
			m_rot.y = baseRadian.y;
		}
		//W�L�[�őO��
		if (CKey::push('W')){
			baseRadian = CCamera::getCamera()->m_rot;
			m_rot.y = baseRadian.y;
			m_pos = m_pos + forward;
		}
		//SDA��������Ă����false�ɂ���
		bool flg = true;
		//S�L�[�F�������i180�x��]�j
		if (CKey::push('S')) {
			m_rot.y = baseRadian.y + 180.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
		
//4		//D�L�[�F�E�����i-90�x��]�j
		if (CKey::push('D')) {
			m_rot.y = baseRadian.y + -90.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
//5		//A�L�[�F�������i90�x��]�j
		if (CKey::push('A')) {
			m_rot.y = baseRadian.y + 90.0f * M_PI / 180.0f;
			m_pos = m_pos + forward;
			flg = false;
		}
		//ASD�L�[��������ĂȂ��ꍇ�͑O����
		if (flg) {
			m_rot.y = baseRadian.y;
		}
		//�O���̃x�N�g���ݒ�
		forward = m_rotMtx * CVector3D(0.0f, 0.0f, 1.0f) * speed;

		//���W�␳�̌v�Z
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
		//�r�[�����ˊԊu���Z
		if (fb-- < 0) {
			fb = 0;
		}
		//�X�y�[�X�L�[�F�r�[������
		if (CKey::push(' ') && fb == 0) {
			//�r�[���̍쐬
			CBeam *b = new CBeam(EBeamP, P_BEAM_SPEED, P_BEAM_HP, CVector4D(1.0f, 1.0f, 0.0f, 1.0f));
//7			//�r�[���̔���
			b->Start(m_pos, m_pos + m_rotMtx * CVector3D(0.0f, 0.0f, 1.0f)*P_BEAM_RANGE);

//7			//�r�[����ǉ�
			CTaskManager::GetInstance()->add(b);
		
			//���ˊԊu��ݒ�
			fb = P_FB;
		}
		//�X�V����
		CBase::update();
		//�v���C���[�̍��W��ޔ�
		CGame::player_pos = m_pos;
		//HP�o�[�̍X�V
		hpbar.update();
	}

	void RenderM(CMatrix &m) {
		pmodel->RenderM(m_matrix);
	}
	//�`�揈��
	void render() {
		//�@�̂̕`��
		RenderM(m_matrix);
		//HP�o�[�̕`��
		hpbar.render();
	}
	//�Փˏ���
	void onCollision(CBase *p) {
		CEffect effect;
		switch (p->getType()) {
		case EBeamE:	//���肪�G�r�[���̎�
			//�_���[�W���Z
			hpbar.setValue(hpbar.getValue() - ((CBeam*)(p))->hp);
			//�G�t�F�N�g����
			effect.Start(Particle, p->getPos());
			break;
		}
	}
};

class CEnemyBase : public CCharactorX {
protected:
	CCollider collider;	//�R���C�_
	CHpbar hpbar;		//HP�o�[
public:
	CVector3D target;	//�ړ���
	int targettime;		//�ړ���X�V����
	int fbtime;			//�r�[�����ˎ���
	//�ړ���ݒ�
	void setTarget() {
		//�����^�C�}�[��0�ȉ�
		if (targettime <= 0) {
			//�v���C���[�ւ̃x�N�g�����v�Z
			target = CGame::player_pos;
			forward = target - m_pos;
			forward.Normalize();
			//�v���C���[�֌�����
			m_rot.y = atan2f(forward.x, forward.z);
			//�����^�C�}�[�̐ݒ�
			targettime = 60;
		}
		else {
			targettime--;	//�����^�C�}�[���Z
		}
	}
	//�e�𔭎�
	void shot() {
		//���˃^�C�}�[��0�ȉ��̎�
		if (fbtime <= 0) {
			//�^�[�Q�b�g�ւ̃x�N�g�����v�Z
			target = CGame::player_pos;
			forward = target - m_pos;
			forward.Normalize();
			//�^�[�Q�b�g�֌�������
			m_rot.y = atan2f(forward.x, forward.z);
			//�r�[���쐬
			CBeam *b = new CBeam(EBeamE, E_BEAM_SPEED, E_BEAM_HP, CVector4D(1.0f, 0.5f, 0.5f, 1.0f));
			//�r�[������
			b->Start(m_pos, m_pos + forward * E_BEAM_RANGE);
			//�r�[����ǉ�
			CTaskManager::GetInstance()->add(b);
			//���˃^�C�}�[��ݒ�
			fbtime = E_FB;
		}
		else {
			fbtime--;	//���˃^�C�}�[�����Z
		}
	}

	CEnemyBase() :
		collider(this, CVector3D(0.0f, 0.0f, 0.0f), 1.5f), hpbar(this), fbtime(E_FB) {
		speed = E_SPEED;	//�ړ����x�ݒ�
		type = ENone;
		CTaskManager::GetInstance()->addCollision(&collider);	//�R���C�_���Փ˃��X�g�֒ǉ�
		//HP�o�[��ݒ�
		hpbar.setMVSCP(E_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.5f, 0.0f));
	}
	//�X�V
	void update() {
		if (enabled) {
			CCharactorX::update();
			hpbar.update();	//HP�o�[���X�V
			//HP��0�ȉ��̎��A�����ɂ���
			if (hpbar.getValue() <= 0) {
				enabled = false;
			}
		}
	}
	//�`��
	void render() {
		if (enabled) {
			CCharactorX::render();
			hpbar.render();
		}
	}
	//�Փˏ���
	void onCollision(CBase *p) {
		CEffect effect;	//�G�t�F�N�g�̍쐬
		switch (p->getType()) {
		case EBeamP:	//�Փ˂��v���C���[�̃r�[���̎�
			//�r�[���̃_���[�W�����Z
			hpbar.setValue(hpbar.getValue() - ((CBeam*)(p))->hp);
			//�G�t�F�N�g�X�^�[�g
			effect.Start(Particle, p->getPos());
			break;
		}
	}
	//�ď����ݒ�i���X�|���p�j
	void reset() {
		//HP�o�[�̏�����
		hpbar.setMVSCP(E_HP, 2.0f, CVector4D(1.0f, 0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.5f, 0.0f));
		//�R���C�_���ēx�Փ˃��X�g�֒ǉ�
		CTaskManager::GetInstance()->addCollision(&collider);
		//�L���ɂ���
		enabled = true;
		m_rot = CVector3D(0.0f, 0.0f, 0.0f);
		targettime = 0;
		fbtime = E_FB;
	}

};

class CEnemy1 : public CEnemyBase {
public:

	void update() {
//8		//�ړ���̐ݒ�
		setTarget();
//8		//�e�𔭎�
		shot();
//8		//�ړ�
		m_pos += forward * speed;
		//�X�V����
		CEnemyBase::update();
	}

};

class CEnemy2 : public CEnemyBase {
public:

	void update() {
		//�ړ���̐ݒ�
		setTarget();
		//�e�𔭎�
		shot();
		//�ړ�
		m_pos += forward * speed;
		//�X�V����
		CEnemyBase::update();
	}

};

class CRespawn : public CBase {
public:
	int time;	//���X�|������܂ł̎���
	EObjectType type;	//�G�̃^�C�v
	CEnemyBase *penemy;	//�G�̃C���X�^���X
	CRespawn() : time(0), type(ENone), penemy(0) {}
	~CRespawn() {
		release();
	}
	//�쐬�����G�̍폜
	void release() {
		if (penemy) {
			delete penemy;
			penemy = 0;
		}
	}
	//	���X�|���ꏊ�̏����ݒ�
	//	type�F�G�̃^�C�v	pos:���W�̒l
	void init(EObjectType type, CVector3D pos) {
		//�ꏊ�̍��W�ݒ�
		m_pos = pos;
		switch (type) {
		case EEnemy1:	//�G�P�̎�
			//�G�쐬
			penemy = new CEnemy1();
			penemy->Load("gundam3.s.x");
			penemy->m_pos = m_pos;
			penemy->setType(EEnemy1);
			break;
		case EEnemy2:	//�G�Q�̎�
			//�G�쐬
			penemy = new CEnemy2();
			penemy->Load("gund3.x");
			penemy->m_pos = m_pos;
			penemy->setType(EEnemy2);
			break;
		}
		//���X�|�����Ԑݒ�
		time = RESPAWN_TIME;
	}

	void update() {
		//�G�͗L���H
		if (penemy->getEnabled()) {
			penemy->update();
		}
		else {
			//���X�|�����Ԃ�0�ȉ�
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
//�Q�[���V�[��
class CScenegame {
public:
	//��ԑJ��
	enum EStatus {
		Init,	//��������
		Game,	//�Q�[����
		Down,	//�_�E����
		Respawn	//���X�|��
	};
	//�}�b�v
	CMap map;
	//�v���C���[
	CPlayer	Player;
	//�G���X�|���n�_
	CRespawn *prespawn;
	//�Q�[���̏��
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
		case Init:	//������
//1			//�}�b�v������
			map.init();
//3			//�v���C���[���f���f�[�^�ǂݍ��݂Ə�����
			Player.Load("sazabi.x");
			Player.init(
				CVector3D(0.0f, 2.0f, 0.0f),
				CVector3D(0.0f, 0.0f, 0.0f),
				CVector3D(0.8f, 0.8f, 0.8f));
			
//6			//�G��z�u
			prespawn = new CRespawn();
			prespawn->init(EEnemy1, CVector3D(-10.0f, 2.0f, 45.0f));
			gettm()->GetInstance()->add(prespawn);
			prespawn = new CRespawn();
			prespawn->init(EEnemy2, CVector3D(20.0f, 2.0f, 30.0f));
			gettm()->GetInstance()->add(prespawn);

			//�G�t�F�N�g�f�ޓǂݍ���
			Particle.Load("particle.obj");
			//�X�e�[�^�X���Q�[����
			status = Game;
			break;
		case Game:	//�Q�[����
//2			//�J�����̐ݒ�
			setcamera();

//3			//�v���C���[�̍X�V�i�ŏ��j
			Player.update();
			
			//�r�[����Փ˂̍X�V
			gettm()->update();
//1			//�}�b�v�̍X�V�i�Ō�j
			map.update();

			//�J�����s��𔽉f
			glLoadMatrixf(CCamera::getCamera()->getMatrix().f);
//1			//�}�b�v�̕`��
			map.render();
//3			//�v���C���[�̕`��
			Player.render();
			
			//�r�[���Ȃǂ̕`��
			gettm()->render();
			//�v���C���[��HP��0�ȉ�
			if (Player.hpbar.getValue() <= 0) {
				status = Down;	//���X�|���҂�
			}
			break;
		case Down:	//���X�|���҂�
			setcamera();
			gettm()->update();
			//�J�����s��𔽉f
			glLoadMatrixf(CCamera::getCamera()->getMatrix().f);
			map.render();
			gettm()->render();
			if (CKey::once('Z')) {
				status = Respawn;
			}

			break;
		case Respawn:	//���X�|��
			Player.reset();
			status = Game;
			break;
		}
	}
	//	�J��������
	//	J�L�[�F��������	L�L�[�F�E������
	void setcamera() {
		CVector3D cam_pos(0.0f, 0.5f, -1.0f);	//�J�����|�W�V�����̕���������
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
		cam_pos = Player.m_pos + cam_matrix * rotx * cam_pos * 4.0f;	//�J�����|�W�V�����̍��W������
		//�J�����̍s��v�Z�i�r���[�s��j
		CCamera::getCamera()->LookAt(cam_pos, Player.getPos(), CVector3D(0.0f, 1.0f, 0.0f));
	}

};

//�Q�[���V�[�����쐬
CScenegame scenegame;

/* display�֐�
1�b�Ԃ�60����s�����
*/
void display() {
	//�e�o�b�t�@�[���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//�s��̏�����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�Q�[���V�[���̍X�V
	scenegame.update();

	//��ʂɕ\��
	glutSwapBuffers();
}

//�֐��̃v���g�^�C�v�錾
void reshape(int, int);
void idle();

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);	//�f�B�X�v���C���[�h�ݒ�
	//�E�B���h�E�̐ݒ�
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Hello 3DProgramming");	//�E�B���h�E�쐬
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);	//�N���A�F�𔒂ɐݒ�

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

//���C�g�̐ݒ�
	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//���b�V���V�F�[�_�[�p
	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//�u�����h�̗L����

	//�e��֐��ݒ�
	glutDisplayFunc(display);	//�`�掞�̊֐����w��
	glutReshapeFunc(reshape);	//�E�B���h�E�ό`���̊֐����w��
	glutIdleFunc(idle);			//�ҋ@���̊֐����w��

	//���C�����[�v
	glutMainLoop();

	return;
}

/*�E�B���h�E�T�C�Y�ύX���̏���
void reshape(int width, int height)
width:��ʕ�
height:��ʍ���
*/
void reshape(int width, int height) {
	glViewport(0, 0, width, height);	//��ʂ̕`��G���A�̎w��
	CCamera::getCamera()->SetSize(width, height);
	glMatrixMode(GL_PROJECTION);		//�s����v���W�F�N�V�������[�h�֕ύX
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
}

LARGE_INTEGER last_time;	//�O��̃J�E���^�l
//�P�b�ԂɂU�O��`�悷��悤�ɒ��߂���
void idle() {
	LARGE_INTEGER freq;		//��b������̃J�E���^��
	LARGE_INTEGER time;		//����̃J�E���^�l

	//��b�Ԃ̃J�E���^�����擾
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//���݂̃V�X�e���̃J�E���g�����擾
		QueryPerformanceCounter(&time);

		//���̃J�E���g-�O��̃J�E���g < 1�b������̃J�E���g����60�Ŋ���(1/60�b������̃J�E���g��)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//�`�悷��֐����Ă�
	display();
}
