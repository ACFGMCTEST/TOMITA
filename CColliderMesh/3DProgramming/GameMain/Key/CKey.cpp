#include "CKey.h"

bool CKey::flg[256];

CInput CKey::Input;//初期化

bool CKey::push(char k) {
	//Input.Update();
	if (KEY(k) || Input.ChangeInputKey(k)){
		return true;
	}
	return false;
	
}

bool CKey::once(char k) {
	
	if (KEY(k) || CInput::ChangeInputKey(k)){
		if (flg[k]) {
			return false;
		}
		else {
			flg[k] = true;
			return true;
		}
	}
	else {
		flg[k] = false;
	}
	return false;
}

/*一度のボタンに複数機能を入れる関数*/
bool CKey::Onces(char k) {

	if (KEY(k) || CInput::ChangeInputKey(k)) {
		if (OnceFlag[k]) {
			return false;
		}
		else {
			OnceFlag[k] = true;
			return true;
		}
	}
	else {
		OnceFlag[k] = false;
	}
	return false;
}

/*一度のボタンに複数機能を入れる関数*/
bool CKey::Pushs(char k) {

	if (KEY(k) || CInput::ChangeInputKey(k)){
		return true;
	}
	return false;
}