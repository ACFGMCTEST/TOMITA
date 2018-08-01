/*
*�^�X�N�̃v���O����
*�S���� �y�c���l
*/
#ifndef TASK_HPP
#define TASK_HPP
#include <stdio.h>
#include <assert.h>
#include "../../Define/Define.h"

class CColBase;

class  CTask
{
public:

	int mNumber;//�����̐����ԍ�
	CTask *mpNext;
	CTask *mpPrev;

	bool mKillFlag;  //�t���O�������Ă�����̂�����
	bool mCharaFlag; //�L�����N�^�[�̃t���O�������Ă�����̂ɂ�Col����
	bool mRenderFlag;

	CTask *mpParent;//�e ��������^�X�N��̂��̂ɃA�N�Z�X���Ă���
	float mValue; //���݂g�o




	//���҂����f
	enum E_NAME{
		E_3D_EFFECT,//�RD�̃G�t�F�N�g
		E_PLAYER,//�v���C��
		E_SLIME,//�X���C��
		E_KING_SLIME,//�L���O�X���C��
		E_BILLBOARD,//�r���{�[�h
		E_2D,//�Q�c�\���̂���
	};
	E_NAME eName;//�l�[��
	/*�X�e�[�^�X���g�m�F*/
	void NamePrint() {
		printf("%s\n", eName);
	}

	/*�����蔻��̌`*/
	enum EType {
		COL_BOX,//�{�b�N�X
		COL_SPHEPE,//��
		COL_CAPSULE,		//�J�v�Z���R���C�_
		COL_TRIANGLE,	//�O�p�`�R���C�_

	};
	EType mType;



	CTask();
	virtual ~CTask();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void MiniMapRender();
	virtual bool Collision(CColBase* p1, CColBase* p2) { return false; };

};


#endif
