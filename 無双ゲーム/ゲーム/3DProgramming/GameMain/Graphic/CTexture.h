#ifndef TEX_H
#define TEX_H

#include <stdio.h>	//ファイルの入力に使用
#include "glut.h"
#include <string.h>
/*tag保管場所*/
#define TGA_FILE "../Graphic\\TexFile\\"
#define ALL_SCENE_TEX_FILE "AllScene\\"
#define TEX_CURSOR_FILE TGA_FILE ALL_SCENE_TEX_FILE"cursor.tga"
#define TEX_STAGE_CURSOR_FILE TGA_FILE ALL_SCENE_TEX_FILE"SelectCursor.tga"
#define TEX_BG_FILE			TGA_FILE"Title\\TitleBG.tga"
/*テクスチャのサイズ*/
#define TEX_BG_X		2400
#define TEX_BG_Y		600
#define TEX_CURSOR_X	80
#define TEX_CURSOR_Y	130
#define TEX_STAGE_CURSOR_X	65
#define TEX_STAGE_CURSOR_Y	55
#define TEX_BUTTON_X	300
#define TEX_BUTTON_Y	44

/*テクスチャのフェードスピード*/
#define FADE_SPEED 0.03f
/*テクスチャのアルファ値のマックス*/
#define ALPHA_MAX 1.0f

/*テクスチャのサイズ頂点指定*/
struct STexVer{
	float left;
	float top;
	float right;
	float bottom;
	/*サイズコンストラクタ*/
	STexVer(float x0, float y0, float x1, float y1) :
		left(x0), top(y0), right(x1), bottom(y1){}
	STexVer(){}

};
/*
TGAファイルのヘッダフォーマット
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;		//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	dummy2;
};

/*テクスチャクラス*/
class CTexture {
public:


	//テクスチャID
	GLuint id;
	//TGAファイルのヘッダ情報
	STgaheader header;
	//ファイル名
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