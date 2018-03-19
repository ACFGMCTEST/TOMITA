/*作成者　冨田健斗*/
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

int WinPosX, WinPosY;//main.cppで設定

CSceneManager Main;
/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Main.SceneMain();

	CMouse::GetInstance()->Update();
	//画面に表示
//	glutSwapBuffers();
}


//
//
//
//
////関数のプロトタイプ宣言
//void reshape(int, int);
//void idle();
//
//void main(int argc, char* argv[]) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);	//ディスプレイモード設定
//	//ウィンドウの設定
//	glutInitWindowSize(DISP_X,DISP_Y,);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Hello 3DProgramming");	//ウィンドウ作成
//	glClearColor(0.5f, 0.5f, 0.5f, 1.f);	//クリア色を白に設定
//
//	glewInit();
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//
////ライトの設定
//	//固定シェーダー用
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	//メッシュシェーダー用
////	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
////	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));
//
//	//各種関数設定
//	glutDisplayFunc(display);	//描画時の関数を指定
//	glutReshapeFunc(reshape);	//ウィンドウ変形時の関数を指定
//	glutIdleFunc(idle);			//待機時の関数を指定
//
//	//メインループ
//	glutMainLoop();
//
//	return;
//}
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
//	CCamera::getCamera()->SetSize(width, height);
	glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	glLoadIdentity();
	gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
//	gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
	//CMouse::GetInstance()->Access(window);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(DISP_X, DISP_Y, "Hello World", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(DISP_X, DISP_Y, "Hello World", NULL, NULL);
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
		// GLEW の初期化に失敗した
//		std::cerr << "Can't initialize GLEW" << std::endl;
		return 1;
	}
	// 垂直同期のタイミングを待つ  
	//glfwSwapInterval(1); 


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// ウィンドウのサイズ変更時に呼び出す処理の登録
	//glfwSetWindowSizeCallback(window, reshape);
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

	//static GLfloat lightDiffuse[3] = { 1.0, 1.0, 1.0 }; //拡散光
	//static GLfloat lightAmbient[3] = { 0.25, 0.25, 0.25 }; //環境光
	//static GLfloat lightSpecular[3] = { 1.0, 1.0, 1.0 }; //鏡面光
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reshape(window, winX,winY);

		idle();
		/* Render here */
		//		glClear(GL_COLOR_BUFFER_BIT);

//		display();
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
