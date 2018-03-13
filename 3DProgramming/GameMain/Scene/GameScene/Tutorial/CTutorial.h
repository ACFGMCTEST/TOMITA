#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//�����̐�

class CTutorial{
private:
	/*�|���S��*/
	CRectangle2 mOperation[ARRAY_OPERA];//�����������
	/*�e�N�X�`��*/
	CTexture mTexFrame;//�g�̃e�N�X�`��
	CTexture mTexOperation;//������������̃e�N�X�`��
	CTexture mTexWalk;//��������
	CTexture mTexCameraKey;//�J��������(���)
	CTexture mTexCameraMouse;//�J��������(���)
	bool mFlagUv;//�A�b�v�f�[�g�Œ���ւ��邽�߂Ɏg��

public:
	/*��ԃV�[�� ���ݕ\������UI*/
	enum E_TUTORIAL_STATE{
		E_RULE, //���[������
		E_WALK,//��������
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