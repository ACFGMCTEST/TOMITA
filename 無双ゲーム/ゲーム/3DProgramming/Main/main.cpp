#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include "GLFW/glfw3.h"
#include "../Light/CLight.h"
#include "../GameMain/Scene/CSceneManager.h"
#include "../Define/define.h"
#include "../GameMain/Key/CMouse.h"
/*ライト設定*/
#define LIGHT_SET_DIR 0,-1,1 //拡散光
#define LIGHT_SET_AMB 0.9f, 0.9f, 0.9f //環境光
#define LIGHT_SET_COL 1.0f, 1.0f, 1.0f //カラー
#define LIGHT_POS  0.0f, 0.1f, 0.0f, 0.0f //ポジション


CSceneManager Main;

int WinPosX, WinPosY;
/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Main.SceneMain();

	CMouse::GetInstance()->Update();
}


int winX, winY;
//
/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(GLFWwindow* window, int width, int height) {
	winX = width; winY = height;
	glViewport(0, 0, width, height);	//画面の描画エリアの指定

	glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 2000.0);


}
//
LARGE_INTEGER last_time;	//前回のカウンタ値
//１秒間に６０回描画するように調節する
void idle() {
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値

	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//描画する関数を呼ぶ
	display();
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(DISP_X, DISP_Y, "BlowOffBlow", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// GLEW を初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	
	reshape(window, DISP_X,DISP_Y);

	glfwSetFramebufferSizeCallback(window, reshape);

	//メッシュシェーダー用
	CLight::getLight(0)->setDir(CVector3(LIGHT_SET_DIR).GetNormalize());
	CLight::getLight(0)->setColor(CVector3(LIGHT_SET_AMB), CVector3(LIGHT_SET_COL));

	//ライトの設定
	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static GLfloat lightPosition[4] = { LIGHT_POS }; //光源の位置

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reshape(window, winX,winY);

		idle();
		/*マウス取得*/
		double mx, my;
		glfwGetCursorPos(window, &mx, &my);
		mx = mx - winX / 2;
		my = -my + winY / 2;
		CMouse::GetInstance()->mPos = CVector2(mx, my);

		/*クリックされている*/
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
			if (!CMouse::GetInstance()->mLeftFlag)CMouse::GetInstance()->mOneLeftFlag = true;//一回だけ有効
			else CMouse::GetInstance()->mOneLeftFlag = false;//一回だけ有効
			CMouse::GetInstance()->mLeftFlag = true;//ずっと有効
		}
		else{
			CMouse::GetInstance()->mLeftFlag = false;
			CMouse::GetInstance()->mOneLeftFlag = false;//一回だけ有効
		}

		/*window座標取得*/
		glfwGetWindowPos(window, &WinPosX, &WinPosY);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
