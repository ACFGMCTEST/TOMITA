#ifndef TITLESCENE_HPP
#define TITLESCENE_HPP

#include "../Define/define.h"
#include "CTitle.h"
#include"../../Sound/CSound.h"
#include"../CScene.h"

//�^�C�g���V�[���̃v���O���~���O
class CTitleScene :public CScene{
private:
	CSound SE_Enter;//�G���^�[�{�^���炷
	CTitle mTitle;//�^�C�g�� 
public:
	void Update();

	CTitleScene();
	~CTitleScene();
};
#endif