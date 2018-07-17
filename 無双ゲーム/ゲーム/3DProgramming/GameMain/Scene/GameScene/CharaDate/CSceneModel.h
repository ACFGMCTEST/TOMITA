#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "Player\CPlayer.h"


#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

class CSceneModel{
private:
	static CSceneModel *mpSceneModel;
	CModelX mModPlayer;//���f���ǂݍ��ݗp
	CModelX mModSlime;//���f���ǂݍ��ݗp
	CModelX mModKingSlime;//���f���ǂݍ��ݗp

	float mMouseInitCount;//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	float mLagTime;//lag�ɂ��o�O�������

	CSceneModel();
public:
	static CSceneModel *GetInstance(); //GetInstance
	static CPlayer *mpPlayer; //�A�N�Z�X�p �L�����N�^�[����Ɏg������ �ÓI��

	static int mEnemyCount;//�}�b�v��ɂ���G�l�~�[�̐�



	/*�v���C���[�ǉ��֐�*/
	void PlayerAdd();//�v���C���|
	/*�G�l�~�[*/
	void SlimeInit();//�X���C���ǉ�
	/*���X�|�[���w�肵��Add*/
	void SlimeAdd(char *RespawnM44Name,CVector3 ajustPos);
	/*�L���O�G�l�~�[*/
	void KingSlimeInit();
	void KingSlimeAdd();//�L���O�X���C���ǉ�

	~CSceneModel();

	void Init(); 
};
#endif