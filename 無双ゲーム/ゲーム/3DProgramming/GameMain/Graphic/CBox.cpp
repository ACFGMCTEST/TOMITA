#include "CBox.h"
#include "../Vector/CVector3.h"
#include "../../Light/CLight.h"
#include "../Graphic/CLoadTexManager.h"
#include "../Scene/GameScene/Map/CMap.h"
/*�{�b�N�X�̒��_�������߂�@�ʐ� * �l�p�`���_��*/
#define BOX_VER_SIZE	6 * 4

/*�@���̃x�N�g��*/
#define BOX_NORMAL_X1	-0.0f,0.5f,0.5f
#define BOX_NORMAL_X2	0.0f,0.5f,0.5f

#define BOX_NORMAL_Y1	0.0f,-1.0f,0.0f
#define BOX_NORMAL_Y2	0.0f,1.0f,0.0f

#define BOX_NORMAL_Z1	0.5f,0.5f,0.0f
#define BOX_NORMAL_Z2	0.5f,0.5f,0.0f

/*
 SetVertex
 ���_���W��ݒ肷��
 x1 < x2 X���̉����Ə��
 y1 < y2 Y���̉����Ə��
 z1 < z2 Z���̉����Ə��
*/
///*�S�Ẵ����_�[�p*/

/* �V�F�[�_�[�g���������Ɏg��
myVer =�@ �������������
i = �z��ԍ�
Ver = ������钸�_�ԍ�
Normal = �������@���ԍ�
*/
void SetMyVertex(CBoxVertex *myVer,int *i,CVector3 Ver ,CVector3 Normal){

	//���_�z��ɐݒ肵�A�@����ݒ肷��
	myVer[*i].mPosition = Ver;
	myVer[*i++].mNormal = Normal;

}

void CBox::SetVertex(float x1, float x2, float y1, float y2, float z1, float z2) {
	//���_�C���f�b�N�X���g�킸�A�S�Ă̖ʃf�[�^���쐬
	CBoxVertex *myVertex;
	//���_�������_�z��쐬
	myVertex = new CBoxVertex[BOX_VER_SIZE];
	int VerNum = 0;
	mSizeX1 = x1;
	mSizeX2 = x2;
	mSizeY1 = y1;
	mSizeY2 = y2;
	mSizeZ1 = z1;
	mSizeZ2 = z2;
	CVector3 v0, v1, v2, v3;




	//�E
	v0.x = x1; v0.y = y2; v0.z = z1;
	v1.x = x1; v1.y = y1; v1.z = z1;
	v2.x = x1; v2.y = y1; v2.z = z2;
	v3.x = x1; v3.y = y2; v3.z = z2;
	mRect[E_x1].SetVertex(v0, v1, v2, v3);
	mRect[E_x1].SetNormal(BOX_NORMAL_X1);


	SetMyVertex(myVertex, &VerNum, v0, mRect[E_x1].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_x1].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_x1].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_x1].mNormal);
	//��
	v0.x = x2; v0.y = y2; v0.z = z2;
	v1.x = x2; v1.y = y1; v1.z = z2;
	v2.x = x2; v2.y = y1; v2.z = z1;
	v3.x = x2; v3.y = y2; v3.z = z1;
	mRect[E_x2].SetVertex(v0, v1, v2, v3);
	mRect[E_x2].SetNormal(BOX_NORMAL_X2);

	SetMyVertex(myVertex, &VerNum, v0, mRect[E_x2].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_x2].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_x2].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_x2].mNormal);


	//��
	v0 = CVector3(x1, y1, z1);
	v1 = CVector3(x1, y1, z2);
	v2 = CVector3(x2, y1, z2);
	v3 = CVector3(x2, y1, z1);
	mRect[E_y1].SetVertex(v0, v1, v2, v3);
	mRect[E_y1].SetNormal(BOX_NORMAL_Y1);

	SetMyVertex(myVertex, &VerNum, v0, mRect[E_y1].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_y1].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_y1].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_y1].mNormal);
	//��
	v0 = CVector3(x1, y2, z1);
	v1 = CVector3(x1, y2, z2);
	v2 = CVector3(x2, y2, z2);
	v3 = CVector3(x2, y2, z1);
	mRect[E_y2].SetVertex(v0, v1, v2, v3);
	mRect[E_y2].SetNormal(BOX_NORMAL_Y2);


	SetMyVertex(myVertex, &VerNum, v0, mRect[E_y2].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_y2].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_y2].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_y2].mNormal);


	//���
	v0.x = x2; v0.y = y2; v0.z = z1;
	v1.x = x2; v1.y = y1; v1.z = z1;
	v2.x = x1; v2.y = y1; v2.z = z1;
	v3.x = x1; v3.y = y2; v3.z = z1;
	mRect[E_z1].SetVertex(v0, v1, v2, v3);
	mRect[E_z1].SetNormal(BOX_NORMAL_Z1);

	SetMyVertex(myVertex, &VerNum, v0, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_z2].mNormal);

	//�O
	v0.x = x1; v0.y = y2; v0.z = z2;
	v1.x = x1; v1.y = y1; v1.z = z2;
	v2.x = x2; v2.y = y1; v2.z = z2;
	v3.x = x2; v3.y = y2; v3.z = z2;
	mRect[E_z2].SetVertex(v0, v1, v2, v3);
	mRect[E_z2].SetNormal(BOX_NORMAL_Z2);
	SetMyVertex(myVertex, &VerNum, v0, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v1, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v2, mRect[E_z2].mNormal);
	SetMyVertex(myVertex, &VerNum, v3, mRect[E_z2].mNormal);
}

/*���ׂĂ�UV�𓯂���*/
void CBox::AllUV(CTexture *t, int left, int top, int right, int bottom){
	mRect[E_z1].SetUv(t, left, top, right, bottom);
	mRect[E_z2].SetUv(t, left, top, right, bottom);

	mRect[E_x2].SetUv(t, left, top, right, bottom);
	mRect[E_x1].SetUv(t, left, top, right, bottom);


	mRect[E_y2].SetUv(t, left, top, right, bottom);
	mRect[E_y1].SetUv(t, left, top, right, bottom);

}


/*�e�N�X�`���ݒ�*/
void CBox::SetTex(E_TexBox eTexState){
	switch (eTexState)
	{
#define SIZE(i) 256 * i//�����������{�b�N�X�c����
#define REVERSE(left,top,right,bottom) left,bottom,right,top
	case E_TexBox::E_SKY_BOX:
		mRect[E_y1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, SIZE(1), 0, SIZE(2), SIZE(1));
		mRect[E_y2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, SIZE(1), SIZE(2), SIZE(2), SIZE(3));

		mRect[E_x1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE( 0 , SIZE(1), SIZE(1), SIZE(2)));
		mRect[E_z2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(1), SIZE(1), SIZE(2), SIZE(2)));
		mRect[E_x2].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(2), SIZE(1), SIZE(3), SIZE(2)));
		mRect[E_z1].SetUv(CLoadTexManager::GetInstance()->mpSkyBox, REVERSE(SIZE(3), SIZE(1), SIZE(4), SIZE(2)));
		
		SetColor(WHITE_COLOR);
		break;
	}
}

void CBox::Render() {
	glPushMatrix();	//���݂̃��f���r���[�s��̑ޔ�
	//�s��̍쐬
	C3DBase::UpdateMatrix();
	////��]


	//�s��ŉ�]�ړ�������
	glMultMatrixf(C3DBase::mMatrix.f);
	//�O�p�|���S����`�悷��
	for (int i = 0; i < BOX_FACE_NUM; i++) {
		/*�}�g���b�N���{�b�N�X�ɍ��킹��*/
		mRect[i].mMatrix = mMatrix;
		mRect[i].Render();
	}
	glPopMatrix();	//���f���r���[�s���ޔ������l�ɖ߂�
}

void CBox::Render2() {
	glPushMatrix();	//���݂̃��f���r���[�s��̑ޔ�
	//�s��̍쐬
	C3DBase::UpdateMatrix();
	//�s��ŉ�]�ړ�������
	glMultMatrixf(mMatrix.f);
	//�O�p�|���S����`�悷��
	for (int i = 0; i < 4; i++) {
		mRect[i].Render();
	}
	glPopMatrix();	//���f���r���[�s���ޔ������l�ɖ߂�
}

void CBox::RenderTop() {
	glPushMatrix();	//���݂̃��f���r���[�s��̑ޔ�
	//�s��̍쐬
	C3DBase::UpdateMatrix();
	//�s��ŉ�]�ړ�������
	glMultMatrixf(mMatrix.f);
	//�O�p�|���S����`�悷��
	mRect[E_y2].Render();
	glPopMatrix();	//���f���r���[�s���ޔ������l�ɖ߂�
}

/*�傫����ς���֐�
float Double �́@�{��������
*/
void CBox::SizeDouble(float Double){
	SetVertex(mSizeX1*Double, mSizeX2*Double,mSizeY1 * Double, mSizeY2 * Double,mSizeZ1 * Double, mSizeZ2 * Double);

}


/*�e�N�X�`�����X�N���[���֐�*/
void CBox::TexSideScroll(float speed){
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].TexSideScroll(speed);
	}
}


/*�e�N�X�`���c�X�N���[���֐�*/
void CBox::TexVerticalScroll(float speed){
	for (int i = 0; i < BOX_FACE_NUM; i++)
	{
		mRect[i].TexVerticalScroll(speed);
	}
}
