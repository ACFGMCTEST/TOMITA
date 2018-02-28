//�V�[���̃v���O���~���O�i�V�[���}�l�[�W���[�j
#ifndef CSCENE_HPP
#define CSCENE_HPP
#include "../Define/define.h"
#include "glut.h"
#include <stdio.h>

enum eSceneNo{
	E_TITLE,
	E_HOME,
	E_QUEST,
	E_SHOP,
	E_ITEM,
	E_OPTION,
	E_GAMEMAIN,
	E_GAMECLEAR,
	E_GAMEOVER,
};

//eSceneNo eSceneNo_Predictive_Conversion;//�\���ϊ��p

class CScene{
public:
	//�V�[�����ɐݒ�@���т͗���̏���

	static int State; //�����Ǘ�


		virtual	void Update(){};	//virtual�@
		virtual	void Render(){};
		virtual	void Init(){};
		

		friend class CSceneManager;
		friend class CTitleScene;
};

#endif