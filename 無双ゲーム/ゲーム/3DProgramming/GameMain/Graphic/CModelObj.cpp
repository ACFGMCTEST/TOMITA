#include "CModelObj.h"
#include <stdio.h>
#include <string.h>
#include "../Collision/ColType/CColTriangle.h"

#define COLOR  0.5f;//
/* objの中身
#
# から行末までコメントです。


mtllib マテリアルファイル名
マテリアルデータを記述したファイル名です。


g グループ名
グループの名前です。


次のg、またはファイル末尾までが1つのグループです。
グループ名が無いと、全体が一つのグループになります。


usemtl マテリアル名
このグループが使用するマテリアル名を指定します。
マテリアル名は、マテリアルファイルに記述してあります。


v X Y Z
頂点の座標値です。


vt U V
テクスチャの座標値です。


vn X Y Z
法線ベクトルの値です。


f 頂点座標値番号/テクスチャ座標値番号/頂点法線ベクトル番号 ...
フェイスの情報です。
3つの数値が / を区切りとして並びます。 この3つの数値が、フェイスの数だけ並びます。
各番号は、1 から始まります。
テクスチャ座標値番号と頂点法線ベクトル番号は、省略可能です。
*/
void CModelObj::LoadFile(char* filename) {
	//printf 画面へ文字を出力する　\n 改行
//	printf("CModelObj::lodafile\n");
	//%s 文字列の指定
//	printf("File Name %s\n", filename);
	//200文字分の配列を作成
	char buf[200];
	char p[4][16];
	CVector4 v;
	CVector2 v2;
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
			/*v:頂点の座標値*/
			if (strcmp(p[0], "v") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorV.push_back(v);
			}
			/*vt:テクスチャの座標値です。*/
			if (strcmp(p[0], "vt") == 0) {
				mFlagTex = true;
				sscanf(p[1], "%f", &v2.x);
				sscanf(p[2], "%f", &v2.y);
				mVectorTex.push_back(v2);
			}
			/*vn:法線ベクトルの値です。*/
			if (strcmp(p[0], "vn") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorN.push_back(v);
			}
			/*usemtl:マテリアル名*/
			if (strcmp(p[0], "usemtl") == 0) {
//				m = mMaterialManager.mMaterial[p[1]];
			}
			/**/
			if (strcmp(p[0], "f") == 0) {
				int v,tex,n;
				/*テクスチャがある場合*/
				if (mFlagTex) {
					sscanf(p[1], "%d/%d/%d", &v, &tex, &n);
					t.mVertex[0] = mVectorV[--v];
					sscanf(p[2], "%d/%d/%d", &v, &tex, &n);
					t.mVertex[1] = mVectorV[--v];
					sscanf(p[3], "%d/%d/%d", &v, &tex,&n);
					t.mVertex[2] = mVectorV[--v];
					///*テクスチャ設定*/
					//t.mUv[0][0] = mVectorTex[--tex].x; t.mUv[0][1] = mVectorTex[tex].y;
					//t.mUv[1][0] = mVectorTex[--tex].x; t.mUv[1][1] = mVectorTex[tex].y;
					//t.mUv[2][0] = mVectorTex[--tex].x; t.mUv[2][1] = mVectorTex[tex].y;
				}/*テクスチャがない場合*/
				else {
					sscanf(p[1], "%d//%d", &v, &n);
					t.mVertex[0] = mVectorV[--v];
					sscanf(p[2], "%d//%d", &v, &n);
					t.mVertex[1] = mVectorV[--v];
					sscanf(p[3], "%d//%d", &v, &n);
					t.mVertex[2] = mVectorV[--v];
				}
				/*法線設定*/
				t.mNormal = mVectorN[--n];
				/*色設定*/
				t.diffuse[0] = t.diffuse[1] = t.diffuse[2] = COLOR;
				/*ポジションを求める*/
				t.mPos = CVector3::TriangleCenter(t.mVertex[0], t.mVertex[1], t.mVertex[2]);

				if (mLeft > t.mPos.x) mLeft = t.mPos.x;
				if (mRight < t.mPos.x) mRight = t.mPos.x;
				if (mTop > t.mPos.z) mTop = t.mPos.z;
				if (mBottom < t.mPos.z) mBottom = t.mPos.z;


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
		new CColTriangle(triangle.mVertex[0], triangle.mVertex[1], triangle.mVertex[2]);
	}
}
