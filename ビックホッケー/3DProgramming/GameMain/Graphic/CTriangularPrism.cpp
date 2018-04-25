#include "CTriangularPrism.h"
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

#define BOX_NORMAL_Z1	0.5f,0.5f,-0.0f
#define BOX_NORMAL_Z2	0.5f,0.5f,0.0f
/*�@���x�N�g��*/
#define NORMAL_SLANTING 0.5f,1.0f,-0.0f//�΂�
#define NORMAL_BACK		0.5f,0.5f,-0.0f//���
#define NORMAL_BOTTOM	0.0f,1.0f,0.0f//����
#define NORMAL_RIGHT	-0.0f,0.5f,0.5f
#define NORMAL_LEFT		0.0f,0.5f,0.5f

/*�e�N�X�`���T�C�Y*/
#define TEX_SPEED_UP_SIZE		0,0,100,100
#define TEX_SPEED_DOWN_SIZE		0,0,100,100
#define TEX_NET_SIZE			0,0,200*CMap::mMapX,200
#define TEX_WALL_SIZE			0,0,300,300
/*
 SetVertex
 ���_���W��ݒ肷��
 x1 < x2 X���̉����Ə��
 y1 < y2 Y���̉����Ə��
 z1 < z2 Z���̉����Ə��
*/
///*�S�Ẵ����_�[�p*/
void CTriangularPrism::SetVertex(float x1, float x2, float y1, float y2, float z1, float z2) {

	CVector3 v0, v1, v2, v3;

	//��
	v0 = CVector3(x1, y1, z1);
	v1 = CVector3(x1, y1, z2);
	v2 = CVector3(x2, y1, z2);
	v3 = CVector3(x2, y1, z1);
	mRect[E_BOTTOM].SetVertex(v0, v1, v2, v3);
	mRect[E_BOTTOM].SetNormal(NORMAL_BOTTOM);

	//���
	v0.x = x1; v0.y = y2; v0.z = z1;//������
	v1.x = x1; v1.y = y1; v1.z = z1;//�������
	v2.x = x1; v2.y = y1; v2.z = z2;//�����O
	v3.x = x1; v3.y = y2; v3.z = z2;//����O
	mRect[E_BACK].SetVertex(v0, v1, v2, v3);
	mRect[E_BACK].SetNormal(NORMAL_BACK);

	//�΂�
	v0.x = x1; v0.y = y2; v0.z = z1;//�����
	v1.x = x2; v1.y = y1; v1.z = z1;//�E����
	v2.x = x2; v2.y = y1; v2.z = z2;//�E���O
	v3.x = x1; v3.y = y2; v3.z = z2;//�E��O
	mRect[E_SLANTING].SetVertex(v0,v3,v2,v1);
	mRect[E_SLANTING].SetNormal(NORMAL_SLANTING);



	/*�E*/
	v0 = CVector3(x1, y2, z1);
	v1 = CVector3(x1, y1, z1);
	v2 = CVector3(x2, y1, z1);
	mTriangle[E_TRIANGLE_FACE::E_RIGHT].SetVertex(v0, v2, v1);
	mTriangle[E_TRIANGLE_FACE::E_RIGHT].SetNormal(NORMAL_RIGHT);


	/*��*/
	v0 = CVector3(x1, y2, z2);//����O
	v1 = CVector3(x1, y1, z2);//�����O
	v2 = CVector3(x2, y1, z2);//�E���O
	mTriangle[E_TRIANGLE_FACE::E_LEFT].SetVertex(v0, v1, v2);
	mTriangle[E_TRIANGLE_FACE::E_LEFT].SetNormal(NORMAL_LEFT);
}

/*���ׂĂ�UV�𓯂���*/
void CTriangularPrism::AllUV(CTexture *t, int left, int top, int right, int bottom){
	mRect[E_BACK].SetUv(t, left, top, right, bottom);
	mRect[E_SLANTING].SetUv(t, left, top, right, bottom);
	mRect[E_BOTTOM].SetUv(t, left, top, right, bottom);

}

/*�e�N�X�`���ݒ�*/
void CTriangularPrism::SetTex(E_TexBox eTexState){

}


//�F�w��
void CTriangularPrism::SetColor(float r, float g, float b, float a){
	/*�l�p�`*/
	for (int i = 0; i < E_RECT_FACE::E_RECT_ARRAY; i++) {
		mRect[i].SetDiffuse(r, g, b, a);
	}
	/*�O�p�`*/
	for (int i = 0; i < E_TRIANGLE_FACE::E_TRI_ARRAY; i++)
	{
		mTriangle[i].SetDiffuse(r, g, b, a);
	}
}

void CTriangularPrism::Render() {
	glPushMatrix();	//���݂̃��f���r���[�s��̑ޔ�
	//�s��̍쐬
	CBase::UpdateMatrix();
	//�s��ŉ�]�ړ�������
	glMultMatrixf(mMatrix.f);
	//�|���S����`�悷��
	for (int i = 0; i < E_RECT_FACE::E_RECT_ARRAY; i++) {
		/*�}�g���b�N���{�b�N�X�ɍ��킹��*/
		mRect[i].mMatrix = mMatrix;
		mRect[i].Render();
	}
	for (int i = 0; i < E_TRIANGLE_FACE::E_TRI_ARRAY; i++)
	{
		mTriangle[i].mMatrix = mMatrix;
		mTriangle[i].Render();
	}
	glPopMatrix();	//���f���r���[�s���ޔ������l�ɖ߂�
}



/*�傫����ς���֐�
float Double �́@�{��������
*/
void CTriangularPrism::SizeDouble(float Double){


}


/*�e�N�X�`�����X�N���[���֐�*/
void CTriangularPrism::TexSideScroll(float speed){

}


/*�e�N�X�`���c�X�N���[���֐�*/
void CTriangularPrism::TexVerticalScroll(float speed){
	
}
