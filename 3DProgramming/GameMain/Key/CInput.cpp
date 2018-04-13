#include <Windows.h>
#include <stdio.h>
#include "../../Define/Define.h"
#include "CInput.h"
int CInput::mButtonNum;
int CInput::mAxisNum;
const unsigned char* CInput::mpButtons = 0;
const float *CInput::mpPositions = 0;
#define TRUE_POS_NONBER 0.3f //�L���ɂ���͈�

CInput::CInput() {
	mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);//�{�^��
	mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);//�L�[����
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
/*�L�[���͕ϊ��֐�*/
char CInput::ChangeInputKey(char k){
	switch (k)
	{
	case VK_RETURN://�G���^�[�L�[
		return InputButton((int)E_ENTER);
		break;
	case KEY_ATTACK://�U���{�^��
		return InputButton((int)E_ATTACK);
		break;
	case VK_ESCAPE://�|�[�Y�{�^��
		return InputButton((int)E_PAUSE);
		break;
	/*�X�e�B�b�N*/
	case 'W'://W�{�^��
		return InputStick((int)E_STICK1_UP, -TRUE_POS_NONBER);
		break;
	case 'D'://D�{�^��
		return InputStick((int)E_STICK1_RIGHT,TRUE_POS_NONBER);
		break;
	case 'S'://S�{�^��
		return InputStick((int)E_STICK1_DOWN,TRUE_POS_NONBER);
		break;
	case 'A'://A�{�^��
		return InputStick((int)E_STICK1_LEFT, -TRUE_POS_NONBER);
		break;
	/*�X�e�B�b�N2*/
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

/*�L�[���f*/
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
		/*�����ォ*/
		if (max <= 0){
			if (mpPositions[i] <= -TRUE_POS_NONBER){
				return true;
			}
		}
		/*�E������*/
		else
		{
			if (mpPositions[i] >= TRUE_POS_NONBER){
				return true;
			}
		}
	}

	return false;
}

