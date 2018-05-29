#include "CLoadTexManager.h"
#include "../../Define/Define.h"

/*�e�N�X�`���ꏊ �r���{�[�h*/
#define TEX_FILE_HAMMER_EFFECT	TGA_FILE"GameEffect\\HammerEffect3.tga"	//�n���}�[�G�t�F�N�g�ꏊ
#define TEX_FILE_SPARK_EFFECT	TGA_FILE"GameEffect\\spark.tga"			//�S�[���G�t�F�N�g�ꏊ 
/*�e�N�X�`���ꏊ�@�{�b�N�X*/

#define TEX_FILE_BOX			TGA_FILE"Map\\Box.tga"//�{�b�N�X
#define TEX_FILE_SLOPE			TGA_FILE"Map\\Slope.tga"//�{�b�N�X
#define TEX_FILE_FAST_FLOOR		TGA_FILE"Map\\speedUp.tga" //������
#define TEX_FILE_SLOW_FLOOR		TGA_FILE"Map\\speedDown.tga"//������
#define TEX_FILE_NET			TGA_FILE"Map\\net.tga"//��
#define TEX_FILE_WALL			TGA_FILE"Map\\wall.tga"//��


CLoadTexManager *CLoadTexManager::mLoadTexManager = 0;

//GetInstance
CLoadTexManager* CLoadTexManager::GetInstance(){
	if (mLoadTexManager == 0) {
		mLoadTexManager = new CLoadTexManager();
	}
	return mLoadTexManager;
}

CLoadTexManager::CLoadTexManager()
{
	/*�C���X�^���X�쐬*/
	/*�{�b�N�X*/
	mpTile = new CTexture();//�^�C��
	mpBox = new CTexture();//����
	mpFastFloor = new CTexture();//������
	mpSlowFloor = new CTexture();//������
	mpTrampoline = new CTexture();//�g�����|����
	mpSlope = new CTexture();//��
	mpNet = new CTexture();//��
	mpWall = new CTexture();//��
	/*�r���{�[�h*/
	mpSpark = new CTexture();
	mpHammer = new CTexture();


	/*�e�N�X�`�����[�h 	�{�b�N�X*/
	mpTile->Load(TEX_FILE_FAST_FLOOR);//�^�C��
	mpBox->Load(TEX_FILE_BOX);//�{�b�N�X
	mpFastFloor->Load(TEX_FILE_FAST_FLOOR);
	mpSlowFloor->Load(TEX_FILE_SLOW_FLOOR);//������
	//mpTrampoline->Load()//�g�����|����
	mpSlope->Load(TEX_FILE_SLOPE);//��
	mpNet->Load(TEX_FILE_NET);//��
	mpWall->Load(TEX_FILE_WALL);//��


	/*�e�N�X�`�����[�h 	�r���{�[�h*/
	mpSpark->Load(TEX_FILE_SPARK_EFFECT);
	mpHammer->Load(TEX_FILE_HAMMER_EFFECT);
}

CLoadTexManager::~CLoadTexManager()
{
	/*�e�N�X�`���f���[�g�@�{�b�N�X*/
	if (mpTile != 0)P_DELETE(mpTile);						//�^�C��
	if (mpBox != 0)P_DELETE(mpBox);							//�{�b�N�X
	if (mpFastFloor != 0)P_DELETE(mpFastFloor);				//������
	if (mpSlowFloor != 0)P_DELETE(mpSlowFloor);				//������
	if (mpTrampoline != 0)P_DELETE(mpTrampoline);			//�g�����|����
	if (mpSlope != 0)P_DELETE(mpSlope);						//��
	if (mpNet != 0)P_DELETE(mpNet);							//��
	if (mpHammer != 0)P_DELETE(mpHammer);					//��
	/*�e�N�X�`���f���[�g�@�r���{�[�g*/
	if (mpSpark != 0)P_DELETE(mpSpark);						//�Ή�
	if (mpHammer != 0)P_DELETE(mpHammer);					//�n���}�[

}