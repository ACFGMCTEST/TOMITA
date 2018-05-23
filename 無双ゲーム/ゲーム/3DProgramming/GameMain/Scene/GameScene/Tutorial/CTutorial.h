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
		E_TEX_WALK,//�����@
		E_TEX_ATTTACK,//�U��
		E_TEX_JUMP,//�W�����v
		E_TEX_SPECIAL,//�K�E�Z
	};
	CTexture mTex;//�e�N�X�`�����[�h

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