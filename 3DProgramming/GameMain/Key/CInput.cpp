#include <Windows.h>
#include <stdio.h>
#include "../../Define/Define.h"
#include "CInput.h"
int CInput::mButtonNum;
int CInput::mAxisNum;
const unsigned char* CInput::mpButtons = 0;
const float *CInput::mpPositions = 0;
#define TRUE_POS_NONBER 0.3f //有効にする範囲

CInput::CInput() {
	mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);//ボタン
	mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);//キー入力
}

void CInput::Update() {

	mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
	mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);
	
#ifdef _DEBUG

	for (int i = 0; i < mButtonNum; i++) {
		printf(" %d ", mpButtons[i]);
	}
	printf("\n");
	for (int i = 0; i < mAxisNum; i++) {
		printf(" %f ", mpPositions[i]);
	}
	printf("\n");

#endif
}
/*キー入力変換関数*/
char CInput::ChangeInputKey(char k){
	switch (k)
	{
	case VK_RETURN://エンターキー
		return InputButton((int)E_ENTER);
		break;
	case KEY_ATTACK://攻撃ボタン
		return InputButton((int)E_ATTACK);
		break;
	case VK_ESCAPE://ポーズボタン
		return InputButton((int)E_PAUSE);
		break;
	/*スティック*/
	case 'W'://Wボタン
		return InputStick((int)E_STICK1_UP, -TRUE_POS_NONBER);
		break;
	case 'D'://Dボタン
		return InputStick((int)E_STICK1_RIGHT,TRUE_POS_NONBER);
		break;
	case 'S'://Sボタン
		return InputStick((int)E_STICK1_DOWN,TRUE_POS_NONBER);
		break;
	case 'A'://Aボタン
		return InputStick((int)E_STICK1_LEFT, -TRUE_POS_NONBER);
		break;
	/*スティック2*/
	case VK_UP:
		return InputStick((int)E_STICK2_UP, -TRUE_POS_NONBER);
		break;
	case VK_DOWN:
		return InputStick((int)E_STICK2_DOWN, TRUE_POS_NONBER);
		break;
	case VK_RIGHT:
		return InputStick((int)E_STICK2_RIGHT, TRUE_POS_NONBER);
		break;
	case VK_LEFT:
		return InputStick((int)E_STICK2_LEFT, -TRUE_POS_NONBER);
		break;
	};
	return NULL;
}

/*キー判断*/
bool CInput::InputButton(int kazu){

	mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
	mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);
	if (mpButtons != 0){
		if (mpButtons[kazu] != 0){
			return true;
		}
	}
	return false;
}
bool CInput::InputStick(int i,float max){
	mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
	mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);

	if (mpPositions != 0){
		/*左か上か*/
		if (max <= 0){
			if (mpPositions[i] <= -TRUE_POS_NONBER){
				return true;
			}
		}
		/*右か下か*/
		else
		{
			if (mpPositions[i] >= TRUE_POS_NONBER){
				return true;
			}
		}
	}

	return false;
}

