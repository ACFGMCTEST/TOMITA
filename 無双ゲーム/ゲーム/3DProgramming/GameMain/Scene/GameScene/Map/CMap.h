#ifndef MAP_HPP
#define MAP_HPP

#include "../../../Collision/CCollisionManager.h"
#include "../../../Graphic/CModelObj.h"

/*�}�b�v*/
class CMap{

private:
	CMatrix44 m44;//���̂���
	CModelObj mGround;//Obj�t�@�C��
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