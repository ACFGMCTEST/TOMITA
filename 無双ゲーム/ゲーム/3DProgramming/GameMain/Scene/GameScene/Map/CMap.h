#ifndef MAP_HPP
#define MAP_HPP
#include "../../../Graphic/CModelX.h"
#include "../../../Graphic/CBox.h"
#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"

/*�}�b�v*/
class CMap{

private:
	CMatrix44 m44;//���̂���
	CModelX mGroundX;//X�t�@�C���`��p
	CModelObj mGround;//Obj�t�@�C��
	CBox mSkyBox;//�w�i
	
public:
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