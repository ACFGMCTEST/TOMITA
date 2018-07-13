//シーンのプログラミング（シーンマネージャー）
#ifndef CSCENE_HPP
#define CSCENE_HPP
#include "../Define/define.h"
#include "glut.h"
#include <stdio.h>

enum eSceneNo{
	E_HOME,//ホーム
	E_STAGE_SELECT,//ステージセレクト
	E_MODEL_CHANGE,//モデルチェンジ
	E_GAMEMAIN,//ゲームメイン
};

class CScene{
public:
	//シーン毎に設定　並びは流れの順番

	static int State; //属性管理


		virtual	void Update(){};	//virtual　
		virtual	void Render(){};
		virtual	void Init(){};
		

		friend class CSceneManager;
		friend class CTitleScene;
};

#endif