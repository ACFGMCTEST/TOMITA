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
	std::string m_TexDirectory;//テクスチャのDirectory
	CTexture *m_pTex;

public:
	CMaterialObj();
	void Map();
	void Unmap();
	void Release();
};

class CModelObj {
private:
	std::vector<CTriangle> mTriangle; //三角形
	CMaterialObj m_material;//マテリアル
	CMatrix44	 mMatrix;//行列
	CVector3	 *m_pVertexAry;//頂点数
	CVector3	 *m_pNormalAry;//法線数
	CVector2	 *m_pTexCoordAry;//テクスチャの参照位置

	std::string m_TexDirectory;//テクスチャのDirectory

	int			m_vertexNum;//頂点数



	bool	LoadMaterial(char *path);
public:

	CModelObj();
	~CModelObj();
	/*テクスチャのディレクトリを指定する*/
	void	TexDirectory(const char *path) { 
		m_TexDirectory = path; 
		m_material.m_TexDirectory = path; 
	}
	/*ファイル読み込み*/
	bool	Load(const char *path);
	/*描画処理*/
	void	Render();
	/*テクスチャ開放*/
	void	Release();
	//代入のオーバーライド
	CModelObj& operator=(const CModelObj &c) {
		m_vertexNum = c.m_vertexNum;
		m_material = c.m_material;

		if (m_pVertexAry) {
			delete[] m_pVertexAry;
		}
		//描画用頂点配列を作成
		m_pVertexAry = new CVector3[c.m_vertexNum];
		memcpy(m_pVertexAry, c.m_pVertexAry, sizeof(CVector3) * c.m_vertexNum);

		if (m_pNormalAry) {
			delete[] m_pNormalAry;
		}
		//描画用法線配列を作成
		m_pNormalAry = new CVector3[c.m_vertexNum];
		memcpy(m_pNormalAry, c.m_pNormalAry, sizeof(CVector3) * c.m_vertexNum);

		if (m_pTexCoordAry) {
			delete[] m_pTexCoordAry;
			//描画用法線配列を作成
			m_pTexCoordAry = new CVector2[c.m_vertexNum];
			memcpy(m_pTexCoordAry, c.m_pTexCoordAry, sizeof(CVector2) * c.m_vertexNum);
		}
		return (*this);
	}

	/*三角形当たり判定追加*/
	void CModelObj::AddCollisionManager();
};


#endif