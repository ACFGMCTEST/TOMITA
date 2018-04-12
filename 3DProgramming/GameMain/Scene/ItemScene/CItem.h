//�����O��
#ifndef CItem_HPP
#define CItem_HPP
#include "../../Graphic/CRectangle2.h"
#define WEAPON_ATKD	100		//�f�t�H���g�n���}�[
#define WEAPON_ATK0 130
#define WEAPON_ATK1 120
#define WEAPON_ATK2 222
#define WEAPON_ATK3 110

#define TIP_ARRAY 5
#define DIGIT 3

class CItem{
public:

	CRectangle2 mBackGround;		//�w�i
	
	CRectangle2 mCurrentOutfit[TIP_ARRAY];		//���ݑ���
	
	CRectangle2 mCurrentName;		//���ݑ����̖��O

	CRectangle2 mCurrentStatus;		//���ݑ����̃X�e�[�^�X

	CRectangle2 mCurrentIcon;		//�������A�C�R��

	CRectangle2 mOutfitIcon[TIP_ARRAY];	//�����I���A�C�R��

	CRectangle2 mBackButton;	    //�߂�{�^��

	CRectangle2 mCursor;			//�J�[�\��

	CRectangle2 mDecideButton;		//��������{�^��
	
	CRectangle2 mSelectText;		//�������e�L�X�g

	CRectangle2 mSelectPicture;		//�I�𒆂̑����A�C�R���̉��Ɏl�p�`��u��

	CRectangle2 mDecisionButton;    //����{�^��

	CRectangle2 mAtkNo[DIGIT];				//�U���͂̐��l	[3]��3���̈�

	CRectangle2 mPopUp;				//�����m��̂��m�点�\��

	
	CTexture	*mpTexture;
	CTexture	*mpMenu;
	CTexture	*mpNum;
	CTexture	*mpTexCursor;


   enum E_WEAPONLIST
	{
		WEAPON0,//�f�t�H���g�n���}�[
		WEAPON1,//�c�i
		WEAPON2,//�s�R�n��
	};



	bool mPopUpFlag=false;		//�|�b�v�A�b�v�`��t���O
	float mPopTime = FPS;


	float alpha;	//�A���t�@�`�����l�������p
	float alpha2;

	static int mSaveAtk;		//�\���p�̕���U����

	static float mMoney;	//������

	static int   mAtk;      //������̍U����

	static int   mSkillNo;  //�X�L���̔ԍ�

	static int mEquipped;	//���݂̑������


	static int status ;	//����I���̃X�C�b�`�p

	static int mSelectWeapon;	//����I�����̃X�C�b�`�p

	int rectnum;	//�l�p�`�̐�
	int rectx;		//�l�p�`�̂����W
	int recty;		//�l�p�`�̂����W
	int mTexXL;		//�e�N�X�`��X left
	int mTexXR;		//�e�N�X�`��X right


	~CItem();
	CItem();
	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//�X�R�A�p�̐����\���̊֐�
	void Init();
	void Update();
	void Render();

};
#endif
/*












�@�@              �@�� .�^�j)�@�@�@�@�@�@�@�^
	 �@       �@�@���]����k(_             <�@�@�L�����ł��B
	          �@.�f,g�M.�턥��Y�R�@�@�@    �_
		   �@�^ * �@ ����������
		   . L���m�P�@�@�@�M���������
			�@ �@ �@ �@ �@ �@ ���@�����e�
						  �@�@ ���������ҭ�C
							 �@ ���������]�㭁C
					             �������������
			              �@�@�@�@�� .����������
							     �@������������������
							       ������������������������
				�@ �@ �@ �@ �@ �@ ��.������������������������ �C
		   �@ �@ �@ �@ �@ �@ �@ �@ �����������������������������]�.,,,,,�Q___ ,��k�
				    �@ �@ �@ �@ �@ �����������������������������M'''''''''''''''''''''�T �B�L
				 �@�@ �@ �@   �@ �@ ,����������������������������
							  �@ �@ /������@ �@.�M�N�N�f.T�L����Rt�����]!
					  �@ �@ �@ �@ �^���C �@! �@ �@ �@ �@ !. �����@ �_���� ,
			   �@�@ �@ �@ �@ �@ ,�X�C�@ |�����@ �@ �@�@�@�f���'. �@ �@.�M�@,�����C
					  �@  �@ �@{��� �@�@|��!�@�@�@�@ �@ �@�@�S��ʁ@�@�@�@ �M�S����,
						   �@�@ �_ �R �@ }�@/�@�@ �@ �@ �@ �@ �@̈́�ʁ@ �@ �@�@ �M'���
						   �@�@�@ �_�_ٲ �@ �@ �@ �@ �@ �@.�@Ɂ@,��@�@�@�@ �@ �@ �R�@											
							        �R,�_ �@ �@ �@ �@ �@�@�@./ /�@�@�@�@ �@ �@ �@�@�@'.�.
							�@�@�@�@ �n__�M��. �@ �@ �@ �@ / / �@ �@ �@ �@ �@�@�@�@�@ '.�@�
			    �@ �@ �@ �@ �@ �@ �@ / f�L�@�_ʁ@�@�@�@�@ / /�@�@�@�@�@�@�@�@�@�@�@�@�@} �n
					 �@ �@ �@�@ �@ �^.���@��@ �M�f�@�@�@.�^ Ɂ@ �@ �@ �@ �@ �@�@�@�@�@�@�__ .,�f
						      �@ �� ���@�@�@ �@ �@ �@ �� ���@�@�@�@�@�@�@�@�@�@�@�@�@�@{_ �C


*/