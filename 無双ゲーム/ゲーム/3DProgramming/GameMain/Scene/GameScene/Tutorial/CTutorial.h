#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//�����̐�

class CTutorial{
private:
	/*�|���S��*/
	CRectangle2 mOperation[ARRAY_OPERA];//�����������
	/*�e�N�X�`��*/

	/*�e�N�X�`���̔z��ԍ�*/
	enum E_TEX{
	E_TEX_RULE,			//0�ԃ��[��
	E_TEX_MOVE,			//1�Ԉړ�����
	E_TEX_CAMERA_KEY,	//2�ԃJ�����L�[����
	E_TEX_CAMERA_MOUSE,	//3�ԃJ�����}�E�X����
	E_TEX_ATTACK_PUSH,	//4�ԍU������
	E_TEX_ATACK_LONG,	//5�ԍU�����ߐ���
	E_TEX_PAUZE,		//6�ԃ|�[�Y����
	};
	CTexture mTex;//�e�N�X�`�����[�h

	bool mFlagUv;//�A�b�v�f�[�g�Œ���ւ��邽�߂Ɏg��

public:
	/*��ԃV�[�� ���ݕ\������UI*/
	enum E_TUTORIAL_STATE{
		E_RULE, //���[������
		E_WALK,//��������
		E_CAMERA,//�J�����̐���
		E_ATTACK,//�������
		E_PAUZE,//�|�[�Y����
		E_ARRAY,//enum�̐�
	};
	E_TUTORIAL_STATE eTutoState;//Tutorial�̌��݂̏��

	CTutorial();
	~CTutorial();

	void Init();
	void Update();
	void Render();

};

#endif