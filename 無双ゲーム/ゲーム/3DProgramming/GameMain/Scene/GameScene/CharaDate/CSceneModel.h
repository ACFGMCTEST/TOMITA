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
	CModelX mModPlayer;//���f���ǂݍ��ݗp
	CModelX mModSlime;//���f���ǂݍ��ݗp
	CModelX mModKingSlime;//���f���ǂݍ��ݗp

	float mMouseInitCount;//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	float mLagTime;//lag�ɂ��o�O�������
public:

	static CPlayer *mpPlayer; //�A�N�Z�X�p �L�����N�^�[����Ɏg������ �ÓI��
	


	/*���ׂẴ��f���L�����폜*/
	void ModelAllKill();

	/*�v���C���[�ǉ��֐�*/
	void PlayerAdd();//�v���C���|
	/*�G�l�~�[*/
	void SlimeAdd ();//�X���C���ǉ�
	/*�L���O�G�l�~�[*/
	void KingSlimeAdd();//�L���O�X���C���ǉ�

	CSceneModel();
	~CSceneModel();

	void Init();
	void Update();
	void Render();
};
#endif