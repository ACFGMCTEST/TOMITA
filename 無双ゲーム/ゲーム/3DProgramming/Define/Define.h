/*
�}�N���u����
*/

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
#define KEY_ATTACK VK_CONTROL
#define KEY_AVOID VK_SHIFT
#define KEY_SKILL 'E'
#define SOUNDFILE "../Sound/"

//#define MAP_ARRAY_X 15 //�}�b�v��
//#define MAP_ARRAY_Z 27 //�}�b�v�� 


#define MAPCHIP_SIZE 2.0f //�P�}�X�̑傫��
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
#define NO_A_BLACK_COLOR	0.0f, 0.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define	NO_A_GRAY_COLOR  0.5f, 0.5f, 0.5f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define	NO_A_WHITE_COLOR 1.0f, 1.0f, 1.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������


#define RE_COLOR	1.0f, 0.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define	GR_COLOR 0.0f, 1.0f, 0.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������
#define BLE_COLOR	0.0f, 0.0f, 1.0f	//�t�F�[�h�����p�A���t�@�̓t���[�g�œK���ɓ���Ă�������


/*Key�}�N��*/
#define ENTER_KEY VK_RETURN

/*2D�̎��̉�ʃT�C�Y*/
#define DISP_2D_X 400 //����
#define DISP_2D_Y 300 //�c��


//���G�̓z

#define TEST_CG  0, 0, 900, 200
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
#define ANGLE_225 225//�p�x
#define ANGLE_180 180//�p�x
#define ANGLE_135 135//�p�x
#define ANGLE_125 125//�p�x
#define ANGLE_90 90 //�p�x
#define ANGLE_45 45 //�p�x
#define ANGLE_5 5//�p�x
#define ANGLE_1 1//�p�x
//360�x�z�����ꍇ ||  �}�C�i�X�̏ꍇ �p�x�ɒ���
#define LIMIT_ANGLE(i)	if(i >= ANGLE_360) i -= ANGLE_360; \
						if (i < 0) i += ANGLE_360;

/*�d��*/
#define GRA_INIT_TIME_COUNT 1.0f//�d�͉����x�̎���_�����l
#define GRA_ADJUSTMENT 0.03f//�����p
#define GRA_ACCELERA  0.98f * GRA_ADJUSTMENT//�d�͉����x
#define GRA_TIME_UP 0.3f//�d�͂̉�������
#define GRAVITY(time) (GRA_ACCELERA * time) //�ŏI�Is�ɂ������
/*���f���̃t�@�C���̏ꏊ*/
#define MODEL_FILE "../Graphic\\3dModel\\"

/*�E�C���h�E�̃|�W�V����*/
extern int WinPosX;
extern int WinPosY;

#define STR(var) #var   //�����ɂ����ϐ���ϐ��������������񃊃e�����Ƃ��ĕԂ��}�N���֐�