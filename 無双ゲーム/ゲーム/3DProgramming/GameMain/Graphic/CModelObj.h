#ifndef OBJ_H
#define OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include "glut.h"
#include "CTexture.h"
#include "../Vector/CVector3.h"
#include "../Vector/CVector2.h"
#include "../Matrix/CMatrix44.h"
#include "../Graphic/CTriangle.h"
#include <vector>

class CMaterialObj {
public:
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_shininess;
	std::string m_TexDirectory;//�e�N�X�`����Directory
	CTexture *m_pTex;

public:
	CMaterialObj();
	void Map();
	void Unmap();
	void Release();
};

class CModelObj {
private:
	std::vector<CTriangle> mTriangle; //�O�p�`
	CMaterialObj m_material;//�}�e���A��
	CMatrix44	 mMatrix;//�s��
	CVector3	 *m_pVertexAry;//���_��
	CVector3	 *m_pNormalAry;//�@����
	CVector2	 *m_pTexCoordAry;//�e�N�X�`���̎Q�ƈʒu

	std::string m_TexDirectory;//�e�N�X�`����Directory

	int			m_vertexNum;//���_��



	bool	LoadMaterial(char *path);
public:

	CModelObj();
	~CModelObj();
	/*�e�N�X�`���̃f�B���N�g�����w�肷��*/
	void	TexDirectory(const char *path) { 
		m_TexDirectory = path; 
		m_material.m_TexDirectory = path; 
	}
	/*�t�@�C���ǂݍ���*/
	bool	Load(const char *path);
	/*�`�揈��*/
	void	Render();
	/*�e�N�X�`���J��*/
	void	Release();
	//����̃I�[�o�[���C�h
	CModelObj& operator=(const CModelObj &c) {
		m_vertexNum = c.m_vertexNum;
		m_material = c.m_material;

		if (m_pVertexAry) {
			delete[] m_pVertexAry;
		}
		//�`��p���_�z����쐬
		m_pVertexAry = new CVector3[c.m_vertexNum];
		memcpy(m_pVertexAry, c.m_pVertexAry, sizeof(CVector3) * c.m_vertexNum);

		if (m_pNormalAry) {
			delete[] m_pNormalAry;
		}
		//�`��p�@���z����쐬
		m_pNormalAry = new CVector3[c.m_vertexNum];
		memcpy(m_pNormalAry, c.m_pNormalAry, sizeof(CVector3) * c.m_vertexNum);

		if (m_pTexCoordAry) {
			delete[] m_pTexCoordAry;
			//�`��p�@���z����쐬
			m_pTexCoordAry = new CVector2[c.m_vertexNum];
			memcpy(m_pTexCoordAry, c.m_pTexCoordAry, sizeof(CVector2) * c.m_vertexNum);
		}
		return (*this);
	}

	/*�O�p�`�����蔻��ǉ�*/
	void CModelObj::AddCollisionManager();
};


#endif