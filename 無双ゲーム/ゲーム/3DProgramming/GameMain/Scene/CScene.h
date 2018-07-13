//�V�[���̃v���O���~���O�i�V�[���}�l�[�W���[�j
#ifndef CSCENE_HPP
#define CSCENE_HPP
#include "../Define/define.h"
#include "glut.h"
#include <stdio.h>

enum eSceneNo{
	E_HOME,//�z�[��
	E_STAGE_SELECT,//�X�e�[�W�Z���N�g
	E_MODEL_CHANGE,//���f���`�F���W
	E_GAMEMAIN,//�Q�[�����C��
};

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