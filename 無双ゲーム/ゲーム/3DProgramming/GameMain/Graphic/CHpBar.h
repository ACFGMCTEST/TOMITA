#ifndef CHPBAR_H
#define CHPBAR_H
#include "CBillBoard.h"
#include "../Camera/CCamera.h"
#include "../Task/CTask.h"
class CHpBar : public CTask{
public:
	CBillBoard mFrame;//�t���[��
	CBillBoard mGauge;//�Q�[�W
	float mMax; //�ő�g�o
	float mValue; //���݂g�o
	float mWidth, mHeight; //���ƍ���
	/*�R���X�g���N�^*/
	CHpBar(){
		CTask::eName = CTask::E_BILLBOARD; 
	}
	/*�ݒ�*/
	void Init(CCamera *pCamera,float max, float value, float widht, float height,
		CVector3 *pos, CVector3 *rot,CVector3 ajust);
	void Init(CCamera *pCamera, float max, float value, float widht, float height,
		CVector3 *pos,CVector3 ajust);
	/*�e�N�X�`���ݒ�*/
	void SetTex(CTexture *frameName, CTexture *gaugeName, STexVer ver);
	void Update();
	void Render();
};

#endif