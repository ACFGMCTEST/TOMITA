#ifndef MAP_HPP
#define MAP_HPP

#include "../../../Collision/CCollisionManager.h"

/*�}�b�v*/
class CMap{

private:
	CMatrix44 m44;//���̂���
public:
	/*�����蔻��*/
	CCollider *mpGround;//���̂���

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