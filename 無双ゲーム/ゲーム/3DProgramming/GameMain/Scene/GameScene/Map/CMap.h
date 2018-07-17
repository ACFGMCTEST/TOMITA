#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"
#include "../../../Graphic/CBillBoard.h"

/*�}�b�v�̃{�[���̖��O*/
#define ENEMY_RESP_0 "EnemyResp0"
#define ENEMY_RESP_1 "EnemyResp1"
#define ENEMY_RESP_2 "EnemyResp2"
#define ENEMY_KING_RESP "Armature"

/*�}�b�v*/
class CMap{

private:
	static CMap *mMap;
	CMatrix44 m44;//���̂���

	CModelX mGroundX;//X�t�@�C���`��p
	CModelObj mGround;//Obj�t�@�C��
	CModelObj mSky;//�w�i

	CBillBoard *mpMiniRect;//�~�j�}�b�v�p
	CVector3 mPos;//�|�W�V����
public:
	static CMap *GetInstance();
	CMap() : mPos(0.0f, 0.0f, 0.0f){};
	~CMap(){};
	/*������*/
	void Init();
	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();
	/*�~�j�}�b�v�p�`��*/
	void MiniMapRender();
	/*�~�j�}�b�v�ݒ�*/
	void SetMiniMap();
	/*�����̖��O�̃}�g���b�N��Ԃ�*/
	CMatrix44 Matrix(char *name) {
	return mGroundX.FindFrame(name)->mCombinedMatrix;
	}

};

#endif