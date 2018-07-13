#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP

#include "../../../Graphic/CRectangle2.h"
#define ARRAY_OPERA 2//�����̐�
class CTutorial{
private:
	static CTutorial *mpTutorial;
	CVector3 mPos;//�͂��߂̃|�W�V����
	CTutorial();

	/*�\������e�L�X�g���я�*/
	enum ESTATE {
		ALL_ENE_KILL,	//���ׂĂ̓G��|��
		MOVE,		//�ړ��ƃJ��������
		BLOW_OFF,	//������΂������̐���
		ATTACK_AVOID,	//�U���Ɖ�����
		HIGH_HILL_SLI,	//����X���C���|���U��
		JUMP,		//�W�����v����
		PUSH_OFF,	//���䂩��˂����Ƃ������̐���
		KING_KILL,	//�e�ʓ|��
		SPECIAL_ATTACK,	//�K�E�Z����
		ARRAY
	};
	ESTATE eState;//Tutorial�̌��݂̏��
	/*�|���S��*/
	CRectangle2 mRect;//�����������
	CRectangle2 mBG;//�����w�iBG
	/*�e�N�X�`��*/
	CTexture mTex;
	CTexture mTexBG;
	/*�e�N�X�`���̎�ނ킯*/
	STexVer mVer[ARRAY];
	/*�^�C��*/
	float mTime;
	bool mFlagUv;//�A�b�v�f�[�g�Œ���ւ��邽�߂Ɏg��
public:
	static CTutorial *GetInstance();

	~CTutorial();

	void Init();
	/*�����؂�ւ�*/
	void Change();
	void Update();
	void Render();
};

#endif