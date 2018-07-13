#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "../Vector/CVector3.h"
#include "../Matrix/CMatrix44.h"
#include "CTexture.h"
#include "../Camera/CCamera.h"
#include "../Task/CTask.h"

/*���_*/
struct SVer
{
	float left;
	float top;
	float right; 
	float bottom;

	/*�ׂ����ݒ�*/
	SVer(float x1, float y2, float  x2, float y1) :
		left(x1),top(y2),right(x2),bottom(y1){}
	/*���ׂĐݒ�*/
	SVer(float all) :
		left(-all), top(all), right(all), bottom(-all){}
	/*�c���ݒ�*/
	SVer(float x,float y) :
		left(x), top(y), right(x), bottom(y) {} 
};

class CBillBoard : public CTask {
private:
	CCamera *mpCamera;//�r���{�[�h�p
	float mDif[4];//�F�ݒ� rgba�̏���
	CVector3 mNormal;//�@��
public:


	//�l�p�`�̒��_4��
	CVector3 mVertex[4];
	//�ʒu �|�C���^�ō��킹�����
	CVector3 *mpPosition;
	CVector3 *mpRotation;//��]�l
	//�����p�|�W�V���� �|�C���^�ō��킹�邽�ߒ����p
	CVector3 mAjustPos;

	//�����s��
	CMatrix44 mMatrix;
	//�e�N�X�`��
	CTexture *mpTexture;	
	float mUv[4][2];//�e�N�X�`���}�b�s���O
	/*�T�C�Y�ݒ�*/
	void SetVertex(CCamera *pCamera, SVer ver, CVector3 *pos, CVector3 *rot, CVector3 ajust);
	void SetVertex(SVer ver);
	void SetVertex(CCamera *pCamera,SVer ver, CVector3 *pos,CVector3 ajust);
	void SetVertex(CCamera *pCamera, float left, float top, float right, float bottom);
	/*�e�N�X�`���ݒ�*/
	void SetUv(CTexture *t, int left, int top, int right, int bottom);
	/*�R���X�g���N�^*/
	CBillBoard();

	/*�F�ݒ�*/
	void SetColor(float r, float g, float b, float a) {
		mDif[0] = r;
		mDif[1] = g;
		mDif[2] = b;
		mDif[3] = a;
	}
	void Update();
	void BeforePosUpdate();
	void Render();
	void MiniMapRender();


};

#endif
