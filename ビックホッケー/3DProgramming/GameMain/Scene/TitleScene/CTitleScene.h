//�^�C�g���̃v���O���~���O
//�S���ҁ@�����O�� && �y�c���l

#ifndef TITLESCENE_HPP
#define TITLESCENE_HPP

#include "../Define/define.h"
#include "CTitle.h"
#include "../../Scene/CScene.h"


class CTitleScene :public CScene{
private:
	CTitle mTitle;

	~CTitleScene();
	void Update();
public:
	CTitleScene();
};
#endif