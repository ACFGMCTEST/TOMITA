#include "CModelObj.h"
#include <stdio.h>
#include <string.h>
#include "../Collision/CCollider3.h"

void CModelObj::LoadFile(char* filename) {
	//printf 画面へ文字を出力する　\n 改行
//	printf("CModelObj::lodafile\n");
	//%s 文字列の指定
//	printf("File Name %s\n", filename);
	//200文字分の配列を作成
	char buf[200];
	char p[4][16];
	CVector4 v;
	CTriangle t;
//	CMaterial m;
	//FILE ファイルポインタ
	FILE *fp;
	//fopen ファイルのオープン "r" 読み込みのみ
	fp = fopen(filename, "r");
	if (fp) {
		//fgets ファイルから1行入力する 最後になるとNULLを返す
		//sizeof(buf) bufのサイズを返す
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			//			printf("%s", buf);
			sscanf(buf, "%s %s %s %s\n", p[0], p[1], p[2], p[3]);
			if (strcmp(p[0], "mtllib") == 0){
//				printf("%s", p[1]);
//				mMaterialManager.loadfile(p[1]);
//				return;
			}
			if (strcmp(p[0], "v") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorV.push_back(v);
			}
			if (strcmp(p[0], "vn") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorN.push_back(v);
			}
			if (strcmp(p[0], "usemtl") == 0) {
//				m = mMaterialManager.mMaterial[p[1]];
			}
			if (strcmp(p[0], "f") == 0) {
				//t.diffuse[0] = m.mDiffuse[0];
				//t.diffuse[1] = m.mDiffuse[1];
				//t.diffuse[2] = m.mDiffuse[2];
				//t.diffuse[3] = m.mDiffuse[3];
				int v, n;
				sscanf(p[1], "%d//%d", &v, &n);
				t.mVertex[0] = mVectorV[--v];
				sscanf(p[2], "%d//%d", &v, &n);
				t.mVertex[1] = mVectorV[--v];
				sscanf(p[3], "%d//%d", &v, &n);
				t.mVertex[2] = mVectorV[--v];

				t.mNormal = mVectorN[--n];
				mTriangle.push_back(t);
			}
		}
		mVectorV.clear();
		mVectorN.clear();
//		mMaterialManager.mMaterial.clear();
		fclose(fp);
	}
}

void CModelObj::Render() {
	for each (CTriangle triangle in mTriangle)
	{
		triangle.Render();
	}
}

void CModelObj::AddCollisionManager() {
	for each (CTriangle triangle in mTriangle)
	{
		//三角形コライダを生成する
		new CCollider3Triangle(triangle.mVertex[0], triangle.mVertex[1], triangle.mVertex[2]);
	}
}
