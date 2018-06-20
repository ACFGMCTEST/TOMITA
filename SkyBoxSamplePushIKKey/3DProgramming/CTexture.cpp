
#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include "glut.h"
//#include "glpng.h"
#include "CTexture.h"
#include "BmpFormat.h"
//#include "png.h"


//SDL�C���N���[�h�iPNG�t�@�C�����́j
//#include "SDL_image.h"

CTexture::CTexture() : m_data(NULL),m_bufID(0){
}
CTexture::~CTexture() {
	Release();
}

bool CTexture::loadBmp(char *path){
	FILE *fp = fopen(path,"rb");
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER info;
	fseek(fp,0,SEEK_SET);
	fread(&header,sizeof(BITMAPFILEHEADER),1,fp);
	
	fread(&info,sizeof(BITMAPINFOHEADER),1,fp);
	
	m_width = info.biWidth;
	m_height = info.biHeight;

	int w = (m_width*3);
	w= (w%4==0) ? w : (w/4)*4+1;

	//imgSize = info.biSizeImage;
	m_imgSize = header.bfSize - header.bfOffBits;
	m_data = new unsigned char[m_imgSize+4];
	for(int i=0;i<m_height;i++) {
		fread(&m_data[(m_height-i-1)*m_width*3],w,1,fp);

	}
	
	//fread(data,info.biSizeImage,1,fp);

	fclose(fp);

	m_internalFormat = GL_RGB;
	if(info.biBitCount==24) {
		m_format = GL_BGR_EXT;
	}else {
		delete[] m_data;
		return false;
	}
	
	
	glGenTextures(1,&m_bufID);
	glBindTexture(GL_TEXTURE_2D,m_bufID);
	glTexImage2D(GL_TEXTURE_2D,0,m_internalFormat,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_data);
	glBindTexture(GL_TEXTURE_2D,0);

	

	delete[] m_data;

	return true;
}

//bool CTexture::loadPng(char *path){
//	pngInfo info;
//	m_bufID = pngBind (path, PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
//	if(m_bufID==0) return false;
//	m_width = info.Width;
//	m_height = info.Height;
//
//	return true;
//
//}

bool CTexture::Load(char *path){
	FILE* fp = NULL;
	if(!(fp = fopen(path,"rb"))) {
		printf("�t�@�C�����ǂݍ��߂܂���[%s]",path);
		return false;
	}
	unsigned char crc[4];
	fread(crc,4,1,fp);
	if(crc[0]==0x42 && crc[1]==0x4D) {
		fclose(fp);
		return loadBmp(path);
	}
	//else if(crc[1]==0x50 && crc[2]==0x4E && crc[3]==0x47) {
	//	fclose(fp);
	//	return loadPng(path);
	//}
	else {
		fclose(fp);
		return loadTga(path);
	}
	return false;
}

void CTexture::MapTexture() {
	

	//glRasterPos2f(-1.0f,-1.0f);
	glBindTexture(GL_TEXTURE_2D,m_bufID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

	glEnable(GL_TEXTURE_2D);
}

void CTexture::UnmapTexture() {
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}
void CTexture::Draw( void )
{
	glRasterPos2f(0.0f,0.0f);
	glDrawPixels(m_width,m_height,m_format,GL_UNSIGNED_BYTE,m_data);
};

void CTexture::Release() {
	if(m_bufID!=0)
		glDeleteTextures(1,&m_bufID);
}


/*
�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
*/
bool CTexture::loadTga(char* filename) {
	/*
	TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
	*/
	struct STgaheader {
		unsigned char	dummy1[12];
		unsigned short	width;		//��
		unsigned short	height;	//����
		unsigned char	depth;	//�r�b�g�̐[��
		unsigned char	dummy2;
	} header;
	//�摜�f�[�^
	unsigned char* data;
	//�t�@�C���|�C���^�̍쐬
	FILE *fp;
	//�t�@�C���I�[�v��
	fp = fopen(filename, "rb");
	//�G���[�̂Ƃ��̓��^�[��
	if (!fp) {
		printf("file not found:%s\n", filename);
		return false;
	}
	//�w�b�_����ǂݍ���
	fread(&header, sizeof(header), 1, fp);
	//�摜�f�[�^�̃o�C�g�����v�Z����
	int length = header.width * header.height * header.depth / 8;
	//�摜�f�[�^�̊i�[�̈���m��
	data = new unsigned char[length];
	//�摜�f�[�^���w�b�_�̑�������ǂݍ���
	fread(data, length, 1, fp);
	//�摜�t�@�C���̃N���[�Y
	fclose(fp);

	//�e�N�X�`���f�[�^�̍쐬
	glGenTextures(1, &m_bufID);
	glBindTexture(GL_TEXTURE_2D, m_bufID);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (header.depth == 32)
		//�A���t�@�L��̃e�N�X�`���쐬
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, header.width,
		header.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
	else
		//�A���t�@�����̃e�N�X�`���쐬
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width,
		header.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	//�i�[�̈�����
	delete[] data;

	return true;
}
