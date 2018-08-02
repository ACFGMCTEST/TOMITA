#ifndef MAIN_HPP
#define MAIN_HPP

#include "CharaDate/CSceneModel.h"
#include "Map/CMap.h"
#include "../CScene.h"
#include "Pause/CPause.h"
#include "Tutorial\CTutorial.h"


class CGameScene : public CScene{
private:
	CRectangle2 mPauze;//�|�[�Y
	CRectangle2 mMainBack;//�Q�[���ɖ߂�
	CRectangle2 mStageSelectBack;//�X�e�[�W�Z���N�g�ɖ߂�
public:
	static bool mEnterEventFlag;//true�ŃA�b�v�f�[�g��~,



	/*���*/
	enum E_STATE{
		E_INIT,
		E_MAIN,
		E_END
	};
	static E_STATE eState;


	CGameScene();
	~CGameScene();
	/*�X�V*/
	void Update();
	/*�~�j�}�b�v����ɕ\���������*/
	void MiniMapRender();
};

#endif
