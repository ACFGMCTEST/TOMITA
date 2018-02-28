
#ifndef MAP_HPP
#define MAP_HPP

#include "../../../Graphic/CShader.h"
#include "../../../../Base/CBase.h"
#include "../../../Graphic/CBox.h"
#include "../../../../Define/Define.h"
#include <iostream>
#include <vector>
#include "../../../Task/CTaskManager.h"
#include "../../../Collision/CCollider.h"
#include "../../../Csv/CCsv.h"

/*�e�N�X�`���T�C�Y*/
#define GROUND_CG -DISP_2D_X,DISP_2D_Y,DISP_2D_X,-DISP_2D_Y

/*�z�񂩂�|�W�V����*/
#define POS_Z(z) z * (MAPCHIP_SIZE*2) - CMap::mMapZ/2 * (MAPCHIP_SIZE*2)
#define POS_X(x) x * (MAPCHIP_SIZE*2) - CMap::mMapX/2 * (MAPCHIP_SIZE*2)
#define ARRAY_POS(x,y,z) CVector4(POS_X(x),y,POS_Z(z)) //�z����ɏ�������

class CMap{
public:
	/*�}�b�v�f�[�^�i�[�p*/
	static CCsv mCsvMapData;			//�}�b�v�f�[�^
	/*�}�b�v�̍��W�l*/
	static int mMapX;
	static int mMapZ;

	/*VboId���ݎg���Ă��Ȃ� ���K�͂̂��̂Ȃ̂�*/
	//GLuint VboId[3];

	static CCollider *mpGoalPlayer;//�A�N�Z�X�p
	static CCollider *mpGoalEnemy; //�A�N�Z�X�p
	static int mGoalCount;//�S�[���̃J�E���g

	CTaskManager mMapTaskManager;//�}�b�v�̃^�X�N�}�l�[�W���[
	CBox mWallBox; //����
	/*�^�C���̃e�N�X�`��*/
	CTexture mTexTile;

	/*�{�b�N�X�̓_���*/
	std::vector<CVector3> mVer;
	std::vector<CVector3> mNormal;
	/*�{�b�N�X�F���*/
	float mDiffuse[4];
	float *mColorRGBA[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];

	GLuint mTextureId;			//�e�N�X�`��ID
	CShader mShader;			//�V�F�[�_
	GLuint	mMyVertexBuffer;	//Add Shader


	class MyColor4
	{
	public:
		float r, g, b, a;
		MyColor4(){}
		MyColor4(float cr, float cg, float cb, float ca) : r(cr), g(cg), b(cb), a(ca){}
	};
	std::vector<MyColor4> mColor;
	int mArrayCount;

	enum  E_PLANE
	{
		E_GROUND,
		E_WALL_LEFT,
		E_WALL_RIGHT,
		E_WALL_UP,
		E_WALL_DOWN,
		E_WALL_ARRAY
	};
	CCollider *mpColPlane[E_WALL_ARRAY];



	class CTile : public CTask{
	public:

		//CRectangle mRect[4];
		CRectangle mRect;
		float pos[3];
		CVector3 mPos;
		CMatrix44 matrix;



		CTile(CVector3 pos,CTexture &t){

			//�e�N�X�`���ǂݍ���
			/*������*/
			mPos = CVector3(0.0f, 0.0f, 0.0f);

			CVector3 v0(-MAPCHIP_SIZE, 0.0f, -MAPCHIP_SIZE);
			CVector3 v1(-MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE);
			CVector3 v2(MAPCHIP_SIZE, 0.0f, MAPCHIP_SIZE);
			CVector3 v3(MAPCHIP_SIZE, 0.0f, -MAPCHIP_SIZE);

			mRect.SetVertex(v0, v1, v2, v3);
			mRect.SetNormal(0.0f, 1.0f, 0.0f);

			mRect.SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			/*���Ԃ����߂�*/
			ePriority = CTask::E_GROUND;
				 

			/*�ʒu����*/
			mPos = pos;
			/*�F�ݒ�*/
			mRect.SetDiffuse(WHITE_COLOR);
			/*�e�N�X�`���ݒ�*/
			mRect.SetUv(&t, GROUND_CG);
			mRect.SetUvRot();//�e�N�X�`������]
		}

		//�f�X�g���N�^
		~CTile(){
		}
		
		void Render(){
			glPushMatrix();
			matrix.translate(mPos);
			glMultMatrixf(matrix.f);

			mRect.Render();

			glPopMatrix();
		}
	};


	/*�}�b�v�f�[�^�����Ǘ�
	�z��ԍ��̋@�\�ꗗ
	0	���n
	1	�W�����v��
	2	������
	3	������
	4	�v���C���[
	5	����
	6	�S�[������
	7	�S�[������
	8	��
	9	����
	A	����������
	*/
	enum E_MAP
	{
		E_FLOOR_0 = '0',	//����ȏꏊ
		E_Trampoline_1,		//�W�����v��
		E_FAST_FLOOR_2,		//�������@
		E_SLOW_FLOOR_3,		//������
		E_PLAYER_4,			//�v���C���[
		E_AI_5,				//����
		E_GOAL_PLAYER_6,	//�S�[������
		E_GOAL_ENEMY_7,		//�S�[������
		E_SLOP_8,			//��
		E_SLOP_END_9,			//��[
		E_HIGH_BOX_A = 'A',		//��������

	};
	E_MAP eState = E_FLOOR_0;

	/*���W�Ɏw�肳�ꂽ������Ԃ�*/
	static E_MAP MapState(int x, int z);
	/*���W�l�����݂̃}�b�v����͂ݏo���ĂȂ������f*/
 	static bool FlagMapLimit(int x, int z);
	/*���W�Ɏw�肵�����̂��������ꍇ true��Ԃ�*/
	static bool FlagMapMacth(int x, int z, E_MAP state);
	//static char mNowMapDate[MAP_ARRAY_Z][MAP_ARRAY_X]; //���̃}�b�v�f�[�^

	void Init();
	/*MAP�v�f���擾�֐�*/
	int MapArray(CCsv &csv, int Nonber);
	/*�}�b�v�����z�u�֐�*/
	void MapInit(CCsv &csv);
	/*�����蔻��̏�����*/
	void ColInit();

	/*�v���C���[�̏������X�|�[���|�W�V����*/
	static CVector3 PlayerFirstPos();
	/*�G�l�~�[�̏������X�|�[���|�W�V����*/
	static CVector3 EnemyFirstPos();
	/*�S�[���̃|�W�V����(�G�l�~�[)*/
	static CVector3 GoalEnemyFirstPos();
	/*�S�[���̃|�W�V����(�v���C���[)*/
	static CVector3 GoalPlayerFirstPos();


	/*�|�W�V��������z��*/
	static int ArrayX(float x);
	/*�|�W�V��������z��*/
	static int ArrayZ(float z);



	CMap();
	~CMap();
	void Update();
	void Render();


};

#endif