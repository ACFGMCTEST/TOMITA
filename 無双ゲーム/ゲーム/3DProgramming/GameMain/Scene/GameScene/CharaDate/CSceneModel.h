#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "CXCharPlayer.h"

#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"

/*���f�����W�߂��N���X*/
class CSceneModel{
private:
	float mMouseInitCount;//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	float mLagTime;//lag�ɂ��o�O�������

	static CXCharPlayer *mpPlayer; //�A�N�Z�X�p �L�����N�^�[����Ɏg������ �ÓI��

	CModelX mModel;//���f���ǂݍ��ݗp

	/*�L�����ǉ�����
	�����|�W�V�������߂�
	*/
	void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model);
	void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model);
	CTaskManager mModelTaskManager;
public:

	CSceneModel();
	~CSceneModel();

	/*�v���C���[�̏��֐�*/
	static CXCharPlayer Player();
	/*Model�̃������J������*/
	void ModelAllKill();

	void Update();
	void UpdateEffect();
	void Render();
};
#endif