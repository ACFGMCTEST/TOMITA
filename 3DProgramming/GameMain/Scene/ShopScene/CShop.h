//�����O��
//�y�c���l
#ifndef CShop_HPP
#define CShop_HPP

#include  "../../Graphic/CRectangle2.h"
#include "../ItemScene/CItem.h"

#define WEAPON_TYPE 4
#define DIGIT 3 //����
//////////num/////////////////////////////////////////////////////////////
#define DOLLAR	 SetUv(mpDollar,0,   0,  100, 100);
#define ZERO	 SetUv(mpNum,   0,   0,  100, 100);
#define ONE		 SetUv(mpNum, 100,   0,  200, 100);
#define TWO		 SetUv(mpNum, 200,   0,  300, 100);
#define THREE	 SetUv(mpNum, 300,   0,  400, 100);
#define FOUR	 SetUv(mpNum, 400,   0,  500, 100);
#define FIVE	 SetUv(mpNum, 500,   0,  600, 100);
#define SIX		 SetUv(mpNum, 600,   0,  700, 100);
#define SEVEN	 SetUv(mpNum, 700,   0,  800, 100);
#define EIGHT	 SetUv(mpNum, 800,   0,  900, 100);
#define NINE	 SetUv(mpNum, 900,   0, 1000, 100);
//////////////////////////////////////////////////////////////////////////
#define DOLLAR_RECT -25.0f, 25.0f, 25.0f, -25.0f
#define NUM_RECT	-25.0f, 25.0f, 25.0f, -25.0f
//////////////////////////////////////////////////////////////////////////
#define DOLLAR_POS  WeaponNameX-60.0f, WeaponNameY+50.0f
#define PRICE_3_POS WeaponNameX-20.0f, WeaponNameY+50.0f
#define PRICE_2_POS WeaponNameX+20.0f, WeaponNameY+50.0f
#define PRICE_1_POS WeaponNameX+60.0f, WeaponNameY+50.0f
//////////////////////////////////////////////////////////////////////////
#define WEAPON_NAME_RECT -75.0f, 25.0f, 75.0f, -25.0f
#define WEAPON_NAME_POS WeaponNameX, WeaponNameY
#define WEAPON_NAME_TEX  0, WeaponNameTexY1, 900, WeaponNameTexY2
//////////////////////////////////////////////////////////////////////////
#define ATK_NUM3_POS - 200, -70
#define ATK_NUM2_POS - 150, -70
#define ATK_NUM1_POS - 100, -70

//����U����&���i
//////////////////////////////////////////////////////////////////////////
#define WEAPON_ATKD	100		//�f�t�H���g�n���}�[
#define WEAPON_ATK0 130
#define WEAPON_ATK1 120
#define WEAPON_ATK2 222
#define WEAPON_ATK3 110

#define WEAPON_PRICE0 200
#define WEAPON_PRICE1 320
#define WEAPON_PRICE2 422
#define WEAPON_PRICE3 510

#define BOARD_Y  90

#define MOVE_SPEED 50

#define NAME_FIRST_SET_MOVE 200.0f

#define NAME_X -300
#define NAME_Y -200

#define NAME_TEX_Y1 0
#define NAME_TEX_Y2 200
//////�w���{�^���̐ݒ�/////////////////////////////////////////////////////////////////////////////////////////
#define BUY_BOX_TEX   0,0,900,200 

#define YES_TEX		  0,  0,900,200 
#define NO_TEX		  0,201,900,400 

#define BUY_BOX_RECT -75.0f, mMoveY, 75.0f, -mMoveY

#define YES_NO_RECT -100.0f, 40, 100.0f, -40

#define ATK_NUM_RECT     -25.0f, mMoveY, 25.0f, -mMoveY

///////�w����ʂ̐ݒ�/////////////////////////////////////////////////////////////////////////////
#define BUY_WINDOW_SIZE -300,200,300,-200 //�w�i�̃T�C�Y

#define P_POS1 CVector2( 340, -260) //�|�P�b�g�}�l�[�̃|�W�V����
#define P_POS2 CVector2( 280, -260)
#define P_POS3 CVector2( 220, -260)

#define MONEY_TEXT_POS CVector2( 120, -260)

#define PS_POS1 CVector2(  60, 100) //�I�𒆂̉��i�|�W�V����
#define PS_POS2 CVector2(  00, 100)
#define PS_POS3 CVector2( -60, 100)

class CShop{
public:

	CItem mItem;								//�A�C�e��

	CRectangle2 mBackGround;	             	 //�w�i

	CRectangle2 mWeaponName[WEAPON_TYPE];		 //����̖��O
	//CRectangle2 mNamePlate [WEAPON_TYPE];		 //����̖��O(Board��)

	CRectangle2 mWeaponAtk3;					 //�U����3����
	CRectangle2 mWeaponAtk2;					 //�U����2����
	CRectangle2 mWeaponAtk1;					 //�U����1����

	CRectangle2 mDollar[WEAPON_TYPE];		     //���i�̉��ɕt���遐�}�[�N
	CRectangle2 mPrice3[WEAPON_TYPE];	    	 //�l�i3����
	CRectangle2 mPrice2[WEAPON_TYPE];	     	 //�l�i2����
	CRectangle2 mPrice1[WEAPON_TYPE];		     //�l�i1����

	CRectangle2 mPocketMoney[DIGIT];             //�������̕\��
	CRectangle2 mPriceSave[DIGIT];			 //�I�𒆂̉��i

	CRectangle2 mBoard[WEAPON_TYPE];	     //�v�f���������p�̂��M
	CRectangle2 mSoldOutTex[WEAPON_TYPE];	     //�v�f���������p�̂��M

	CRectangle2 mBackButton;					 //�߂�{�^��

	CRectangle2 mCursor;						 //�J�[�\��

	////��������w���֌W
	CRectangle2 mBuy;							 //�w���{�^��

	CRectangle2 mBuyShadow;

	CRectangle2 mText;					         //�m�F�p�e�L�X�g

	CRectangle2 mYes;							 //�C�G�X�{�^��

	CRectangle2 mNo;						     //�m�[�{�^��

	CRectangle2 mSmoke;							 //�������̍��F���ۂ����

	CRectangle2 mPocketMoneyText;					//������

	/////////////////////////////////////////////////////////////////////////////////

	int mMoney=999;								 //�������i���j

	float mWeaponPos0 = 0;						 //����{�[�h�̃|�W�V����
	float mWeaponPos1 = 650;
	float mWeaponPos2 = 1300;
	float mWeaponPos3 = 1950;

	const float mcDefaultHidden = 25.0f;		 //�ꎞ�I�ɉB������Default���l

	float mMoveY = 25.0f;					     //���j���[�ύX���̏㉺�ύX�p

	const float mcBoardX = 300;				     //�{�[�h�̃f�t�H���g�T�C�Y
	const float mcBoardY = 210;

	const float mcBoardSubX = 90;
	const float mcBoardSubY = 65;

	float mBoardX = mcBoardX*10;				 //����̃{�[�h�T�C�Y
	float mBoardY = mcBoardY*10;

	int mWeapnNo;						//����i���o�[
	int mPrice   [WEAPON_TYPE];			//�A�C�e���̉��i
	int mPriceSelect;					//�I�𒆂̃A�C�e���̉��i

	int mWeapnAtk[WEAPON_TYPE];         //����U����

	static bool mSoldOut[WEAPON_TYPE];
	//bool mBuyFlag[WEAPON_TYPE];


	bool mHiddenFlag = false;			//�B��Flag
	static bool mBuyScene ;				//�w��scene

	enum E_WEAPON
	{
		WEAPON0,//�݂��ɂ�
		WEAPON1,//�c�i
		WEAPON2,//�s�R�n��
		WEAPON3,//�������-
	};

	CTexture	*mpTexture;
	CTexture	*mpWeaponName;
	CTexture	*mpDollar;
	CTexture	*mpNum;
	CTexture    *mpBuyButton;
	CTexture	*mpTexCursor;
	int status;

	~CShop();
	CShop();
	void Number(int Score, CRectangle2 &odifit, CRectangle2 &twdifit, CRectangle2 &thdifit);//�X�R�A�p�̐����\���̊֐�
	void Init();
	void Update();
	void Render();
	void AllMove(bool zeroover);
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