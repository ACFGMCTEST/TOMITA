#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "UI\CScoreBoard.h"
#include "../CScene.h"
#include"../CountDown/CCountDown.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"
#include "../../Sound/CSound.h"

class CGameScene : public CScene{
public:


	CPause mPause;
	CSceneModel mSceneModel;
	CMap mMap;
	CSound mBgm;//BGM
	
	bool firstaction=false;

	/*��ʕΈ�*/
	enum E_TRANSTION{
		E_COUNTDOWN, //�J�E���g�_�E��
		E_ACTIVE,//
		E_PAUSE,//�|�[�Y��
	};
	static E_TRANSTION eTransition;

	/*���*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	E_STATE eState;
	bool pause = false;

	CGameScene();
	~CGameScene();

	void TransitionManager();
	//�J��Ԃ����s����鏈��
	void Update();
	//�~�j�}�b�v

	/*�}�b�v�ォ��̎��_*/
	void RenderMiniMap();
};

#endif
