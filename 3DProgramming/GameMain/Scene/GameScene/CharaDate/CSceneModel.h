#ifndef SCENEMODEL_HPP
#define SCENEMODEL_HPP

#include "../../../Graphic/CModelX.h"
#include "../../../Matrix/CMatrix44.h"
#include "../../../Camera/CCamera.h"
#include "../Map/Goal/CGoal.h"
#include "CXCharPlayer.h"

#include "../../../Graphic/CRectangle2.h"
#include "../../../Task/CTaskManager.h"
#include "../Puck/CXPuck.h"

class CSceneModel{
private:
	float mMouseInitCount;//�}�E�X�������ʒu�ɖ߂�܂ł̎���
	float mLagTime;//lag�ɂ��o�O�������
public:

	//�G�L�����̃C���X�^���X
	static CXCharPlayer *mCharcter; //�A�N�Z�X�p �L�����N�^�[����Ɏg������ �ÓI��


	CMatrix44 mMatrix;

	CModelX mModel;//���f���ǂݍ��ݗp
	CModelX mModelE;//���f���ǂݍ��ݗp
	CModelX mModelPuck;//���f���ǂݍ��ݗp
	
	CModelX mModelGoal;//���f���ǂݍ��ݗp�v���C���[
	CModelX mModelEGoal;//���f���ǂݍ��ݗp�G�l�~�[

	CVector3 mPosition; //�ʒu�@

	
	/*�p�b�N�A�N�Z�X�p�@�G�l�~�[�Ŏg��*/
	static CXPuck *mpPuck;


	//�G�l�~�[���f��

	/*�L�����ǉ�����
	�����|�W�V�������߂�
	*/
	void CSceneModel::CPlayerAdd(CVector3 PlayerPos, CModelX *model);
	void CSceneModel::CEnemyAdd(CVector3 EnemyPos, CModelX *model);
	void CSceneModel::CPuckAdd(CVector3 PuckPos, CModelX *model);
	void CSceneModel::CGoalPlayerAdd(CVector3 GoalPos, CModelX *model);
	void CSceneModel::CGoalEnemyAdd(CVector3 GoalPos, CModelX *model);
//	CTaskManager mModelTaskManager;
	CSceneModel();
	~CSceneModel();

	void Init();
	void Update();
	void UpdateEffect();
	void Render();
};
#endif