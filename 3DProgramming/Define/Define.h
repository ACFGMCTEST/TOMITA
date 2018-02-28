/*
�}�N���u����
*/
#define COLLISION_ARRAY_SIZE 500 //
#define CANNONBALL_ARRAY_SIZE 4//�C�e��
#define FIRE_INTERVAL 20
#define TANKENEMY_ARRAY_SIZE 4//
#define DISP_X  800
#define DISP_Y  600

/*FPS�ݒ�*/
#define FPS 60
#define UP_KEY VK_UP
#define DOWN_KEY VK_DOWN
#define RIGHT_KEY VK_RIGHT
#define LEFT_KEY VK_LEFT

/*�L�[����*/
#define KEY_JUMP VK_SPACE
#define KEY_ATTACK VK_SHIFT
#define KEY_SKILL 'E'
#define SOUNDFILE "../Sound/"

//#define MAP_ARRAY_X 15 //�}�b�v��
//#define MAP_ARRAY_Z 27 //�}�b�v�� 


#define MAPCHIP_SIZE 2.5f //�P�}�X�̑傫��
//�^�C�g���J����XY
#define CAMERA_X 11
#define CAMERA_Y 22
/*�f���[�g���ĂO��Ԃ�*/
#define P_DELETE(p) if(p){delete p;p = nullptr;}
#define P_ARRAY_DELETE(p) if(p){delete[] p;p = nullptr;}


/*�F�̐ݒ�l*/
#define WHITE_COLOR 1.0f,1.0f,1.0f,1.0f //��
#define BLACK_COLOR 0.0f, 0.0f, 0.0f, 1.0f//���F
#define GRAY_COLOR	0.5f, 0.5f, 0.5f, 1.0f//�D�F
#define SKELETON_BLACK_COLOR	0.0f, 0.0f, 0.0f, 0.9f//�D�F
#define DARK_GRAY_COLOR	0.5f, 0.5f, 0.5f, 1.0f//�D�F

#define RED_COLOR 1.0f,0.0f,0.0f,1.0f//�ԐF
#define YELLOW_COLOR 1.0f,1.0f,0.0f,1.0f//���F
#define GREEN_COLOR 0.0f,1.0f,0.0f,1.0f//�ΐF
#define CYAN_COLOR 0.0f,1.0f,1.0f,1.0f//��
#define BLUE_COLOR 0.0f,0.0f,1.0f,1.0f//�F
#define PURPLE_COLOR 1.0f,0.0f,1.0f,1.0f//��


#define LIGHTBLUE_COLOR 0.2f,0.2f,1.0f,1.0f//���F
#define PINK_COLOR 1.0f,0.5f,0.5f,1.0f     //���F
#define YELLOW_COLOR 1.0f,1.0f,0.0f,1.0f   //���F

#define BEIGE_COLOR 0.2,0.2f,0.1f,1.0f//���F 
#define PURPLE_COLOR 1.0f,0.0f,1.0f,1.0f//���F

#define NOTHING_COLOR 0.0f,0.0f,0.0f,0.0f //���ݒ�
#define B_COLOR	0.0f, 0.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define	W_COLOR 1.0f, 1.0f, 1.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������


#define RE_COLOR	1.0f, 0.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define	GR_COLOR 0.0f, 1.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define BLE_COLOR	0.0f, 0.0f, 1.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������


/*Key�}�N��*/
#define ENTER_KEY VK_RETURN

/*2D�̎��̉�ʃT�C�Y*/
#define DISP_2D_X 400 //����
#define DISP_2D_Y 300 //�c��

/*�T�C�Y�}�N��*/
#define BG_SIZE -DISP_X,DISP_Y,DISP_X,-DISP_Y //�w�i�̃T�C�Y
#define CURSOR_SIZE -10.0f,10.0f,10.0f,-10.0f//�J�[�\���̃T�C�Y

/*�E�C���h�E�|�W�V����*/
extern int WinPosX,WinPosY;//main.cpp�Őݒ�


//���G�̓z

#define  TEST_CG  0, 0, 900, 200
#define BACK_POS -400.0f, -240.0f, -300.0f, -300.0f

//�߂�{�^���̐ݒ�
#define BACK_CG	  0,0,300,300
#define BACK_RECT -35.0f, 35.0f, 35.0f, -35.0f
#define BACK_POS CVector2(-365, -265)



/*�X�R�A�̏�������܂ł����ƃV�[�����ς��*/
#define LIMIT_SCORE 50

/*�p�x*/
#define ANGLE_360 360//�p�x
#define ANGLE_315 315//�p�x
#define ANGLE_270 270//�p�x
#define ANGLE_180 180//�p�x
#define ANGLE_125 125//�p�x
#define ANGLE_90 90 //�p�x
#define ANGLE_45 45 //�p�x
#define ANGLE_5 5//�p�x
#define ANGLE_1 1//�p�x

/*�d��*/
#define GRA_INIT_TIME_COUNT 1.0f//�d�͉����x�̎���_�����l
#define GRA_ACCELERA  0.98f * 0.06f//�d�͉����x
#define GRA_TIME_UP 0.3f//�d�͂̉�������
#define GRA_ADJUSTMENT 1.0f//�����p
#define GRAVITY(time) (GRA_ACCELERA * time * GRA_ADJUSTMENT) //�ŏI�I�ɂ������