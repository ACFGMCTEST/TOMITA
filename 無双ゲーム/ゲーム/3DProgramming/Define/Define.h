/*
マクロ置き場
*/

#define DISP_X  800
#define DISP_Y  600

/*FPS設定*/
#define FPS 60
#define UP_KEY VK_UP
#define DOWN_KEY VK_DOWN
#define RIGHT_KEY VK_RIGHT
#define LEFT_KEY VK_LEFT

/*キー入力*/
#define KEY_JUMP VK_SPACE
#define KEY_ATTACK VK_CONTROL
#define KEY_AVOID VK_SHIFT
#define KEY_SKILL 'E'
#define SOUNDFILE "../Sound/"

//#define MAP_ARRAY_X 15 //マップ数
//#define MAP_ARRAY_Z 27 //マップ数 


#define MAPCHIP_SIZE 2.0f //１マスの大きさ
//タイトルカメラXY
#define CAMERA_X 11
#define CAMERA_Y 22
/*デリートして０を返す*/
#define P_DELETE(p) if(p){delete p;p = nullptr;}
#define P_ARRAY_DELETE(p) if(p){delete[] p;p = nullptr;}


/*色の設定値*/
#define WHITE_COLOR 1.0f,1.0f,1.0f,1.0f //白
#define BLACK_COLOR 0.0f, 0.0f, 0.0f, 1.0f//黒色
#define GRAY_COLOR	0.5f, 0.5f, 0.5f, 1.0f//灰色
#define SKELETON_BLACK_COLOR	0.0f, 0.0f, 0.0f, 0.9f//灰色
#define DARK_GRAY_COLOR	0.5f, 0.5f, 0.5f, 1.0f//灰色
#define RED_COLOR 1.0f,0.0f,0.0f,1.0f//赤色
#define YELLOW_COLOR 1.0f,1.0f,0.0f,1.0f//黄色
#define GREEN_COLOR 0.0f,1.0f,0.0f,1.0f//緑色
#define CYAN_COLOR 0.0f,1.0f,1.0f,1.0f//青緑
#define BLUE_COLOR 0.0f,0.0f,1.0f,1.0f//青色
#define PURPLE_COLOR 1.0f,0.0f,1.0f,1.0f//紫


#define LIGHTBLUE_COLOR 0.2f,0.2f,1.0f,1.0f//水色
#define PINK_COLOR 1.0f,0.5f,0.5f,1.0f     //桃色
#define YELLOW_COLOR 1.0f,1.0f,0.0f,1.0f   //黄色

#define BEIGE_COLOR 0.2,0.2f,0.1f,1.0f//肌色 
#define PURPLE_COLOR 1.0f,0.0f,1.0f,1.0f//紫色

#define NOTHING_COLOR 0.0f,0.0f,0.0f,0.0f //未設定
#define NO_A_BLACK_COLOR	0.0f, 0.0f, 0.0f	//フェード処理用アルファはフロートで適当に入れてください
#define	NO_A_GRAY_COLOR  0.5f, 0.5f, 0.5f	//フェード処理用アルファはフロートで適当に入れてください
#define	NO_A_WHITE_COLOR 1.0f, 1.0f, 1.0f	//フェード処理用アルファはフロートで適当に入れてください


#define RE_COLOR	1.0f, 0.0f, 0.0f	//フェード処理用アルファはフロートで適当に入れてください
#define	GR_COLOR 0.0f, 1.0f, 0.0f	//フェード処理用アルファはフロートで適当に入れてください
#define BLE_COLOR	0.0f, 0.0f, 1.0f	//フェード処理用アルファはフロートで適当に入れてください


/*Keyマクロ*/
#define ENTER_KEY VK_RETURN

/*2Dの時の画面サイズ*/
#define DISP_2D_X 400 //横幅
#define DISP_2D_Y 300 //縦幅


//仮絵の奴

#define TEST_CG  0, 0, 900, 200
#define BACK_POS -400.0f, -240.0f, -300.0f, -300.0f

//戻るボタンの設定
#define BACK_CG	  0,0,300,300
#define BACK_RECT -35.0f, 35.0f, 35.0f, -35.0f
#define BACK_POS CVector2(-365, -265)



/*スコアの上限ここまでいくとシーンが変わる*/
#define LIMIT_SCORE 50

/*角度*/
#define ANGLE_360 360//角度
#define ANGLE_315 315//角度
#define ANGLE_270 270//角度
#define ANGLE_225 225//角度
#define ANGLE_180 180//角度
#define ANGLE_135 135//角度
#define ANGLE_125 125//角度
#define ANGLE_90 90 //角度
#define ANGLE_45 45 //角度
#define ANGLE_5 5//角度
#define ANGLE_1 1//角度
//360度越した場合 ||  マイナスの場合 角度に直す
#define LIMIT_ANGLE(i)	if(i >= ANGLE_360) i -= ANGLE_360; \
						if (i < 0) i += ANGLE_360;

/*重力*/
#define GRA_INIT_TIME_COUNT 1.0f//重力加速度の時間_初期値
#define GRA_ADJUSTMENT 0.03f//調整用
#define GRA_ACCELERA  0.98f * GRA_ADJUSTMENT//重力加速度
#define GRA_TIME_UP 0.3f//重力の加速時間
#define GRAVITY(time) (GRA_ACCELERA * time) //最終的sにかかる力
/*モデルのファイルの場所*/
#define MODEL_FILE "../Graphic\\3dModel\\"

/*ウインドウのポジション*/
extern int WinPosX;
extern int WinPosY;

#define STR(var) #var   //引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数