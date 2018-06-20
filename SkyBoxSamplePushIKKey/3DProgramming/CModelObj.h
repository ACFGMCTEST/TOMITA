#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "glew.h"
#include "glut.h"
#include "CTexture.h"
#include "CModel.h"
class CMaterialObj {
public:
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_shininess;
	CTexture *m_pTex;

public:
	CMaterialObj();
	void Map();
	void Unmap();
	void Release();
};

class CModelObj {
//class CModelObj : public CModel {
private:
protected:
public:
	CVector3D*	m_pVertexAry;
	CVector3D*	m_pNormalAry;
	CVector2D*	m_pTexCoordAry;
	int			m_vertexNum;
	CMaterialObj	m_material;
	
	bool	LoadMaterial(char *path);
public:
	
	CModelObj();
	~CModelObj();
	bool	Load(const char *path);
	void	RenderM(CMatrix &m);
	void	Release();

	//代入のオーバーライド
	CModelObj& operator=(const CModelObj &c) {
		m_vertexNum = c.m_vertexNum;
		m_material = c.m_material;

		if (m_pVertexAry) {
			delete[] m_pVertexAry;
		}
		//描画用頂点配列を作成
		m_pVertexAry = new CVector3D[c.m_vertexNum];
		memcpy(m_pVertexAry, c.m_pVertexAry, sizeof(CVector3D) * c.m_vertexNum);

		if (m_pNormalAry) {
			delete[] m_pNormalAry;
		}
		//描画用法線配列を作成
		m_pNormalAry = new CVector3D[c.m_vertexNum];
		memcpy(m_pNormalAry, c.m_pNormalAry, sizeof(CVector3D) * c.m_vertexNum);

		if (m_pTexCoordAry) {
			delete[] m_pTexCoordAry;
			//描画用法線配列を作成
			m_pTexCoordAry = new CVector2D[c.m_vertexNum];
			memcpy(m_pTexCoordAry, c.m_pTexCoordAry, sizeof(CVector2D) * c.m_vertexNum);
		}
		return (*this);
	}

};