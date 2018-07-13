#ifndef TEX_H
#define TEX_H

#include <stdio.h>	//�t�@�C���̓��͂Ɏg�p
#include "glut.h"
#include <string.h>
/*tag�ۊǏꏊ*/
#define TGA_FILE "../Graphic\\TexFile\\"
#define ALL_SCENE_TEX_FILE "AllScene\\"
#define TEX_CURSOR_FILE TGA_FILE ALL_SCENE_TEX_FILE"cursor.tga"
#define TEX_STAGE_CURSOR_FILE TGA_FILE ALL_SCENE_TEX_FILE"SelectCursor.tga"
#define TEX_BG_FILE			TGA_FILE"Title\\TitleBG.tga"
/*�e�N�X�`���̃T�C�Y*/
#define TEX_BG_X		2400
#define TEX_BG_Y		600
#define TEX_CURSOR_X	80
#define TEX_CURSOR_Y	130
#define TEX_STAGE_CURSOR_X	65
#define TEX_STAGE_CURSOR_Y	55
#define TEX_BUTTON_X	300
#define TEX_BUTTON_Y	44

/*�e�N�X�`���̃t�F�[�h�X�s�[�h*/
#define FADE_SPEED 0.03f
/*�e�N�X�`���̃A���t�@�l�̃}�b�N�X*/
#define ALPHA_MAX 1.0f

/*�e�N�X�`���̃T�C�Y���_�w��*/
struct STexVer{
	float left;
	float top;
	float right;
	float bottom;
	/*�T�C�Y�R���X�g���N�^*/
	STexVer(float x0, float y0, float x1, float y1) :
		left(x0), top(y0), right(x1), bottom(y1){}
	STexVer(){}

};
/*
TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;		//��
	unsigned short	height;	//����
	unsigned char	depth;	//�r�b�g�̐[��
	unsigned char	dummy2;
};

/*�e�N�X�`���N���X*/
class CTexture {
public:


	//�e�N�X�`��ID
	GLuint id;
	//TGA�t�@�C���̃w�b�_���
	STgaheader header;
	//�t�@�C����
	char* mpName;

	unsigned char *m_data;
	int	m_width;
	int m_height;
	int m_internalFormat;
	int m_format;
	unsigned int m_imgSize;
	int m_type;

	unsigned int m_bufID;
	bool loadBmp(char *path);
	bool loadPng(char *path);
	bool loadTga(char *path);
public:
	CTexture();
	~CTexture();
	CTexture(char *file)
		: id(0)
		, mpName(0) {
		Load(file);
	}
	bool Load(char *path);
	void MapTexture();
	void UnmapTexture();
	void Release();
	void Draw();
};
#endif