#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"

/*�}�b�v*/
class CMap{

private:
	static CMap *mMap;
	CMatrix44 m44;//���̂���
	CModelX mGroundX;//X�t�@�C���`��p
	CModelObj mGround;//Obj�t�@�C��
	CModelObj mSky;//�w�i
	
public:
	CMatrix44 mRespawn;//���X�|�[������s��
	static CMap *GetInstance();
	CMap(){};
	~CMap(){};
	/*������*/
	void Init();
	/*�X�V*/
	void Update();
	/*�`��*/
	void Render();


};

#endif