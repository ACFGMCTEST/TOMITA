#include "CTriangle2.h"	//三角形クラスのヘッダをインクルードする
#include "../Matrix/CMatricx22.h"

void CTriangle2::Render(CVector2 pos) {
	//描画色を設定
	glColor4f(r, g, b, a);
	//三角形の描画
	glBegin(GL_TRIANGLES);	//三角形の頂点指定開始
	glVertex2f(x1 + pos.x, y1 + pos.y);	//頂点１の指定
	glVertex2f(x2 + pos.x, y2 + pos.y);	//頂点２の指定
	glVertex2f(x3 + pos.x, y3 + pos.y);	//頂点３の指定
	glEnd();	//頂点指定終了
}
/*
テクスチャマッピング付きの描画処理
UV[0]:頂点1のU、UV[1]:頂点1のV
UV[2]:頂点2のU、UV[3]:頂点2のV
UV[4]:頂点3のU、UV[5]:頂点3のV
*/
void CTriangle2::Render(CVector2 pos, float uv[]) {
	//描画色を設定
	glColor4f(r, g, b, a);
	//三角形の描画
	glBegin(GL_TRIANGLES);	//三角形の頂点指定開始
	glTexCoord2f(uv[0], uv[1]);			//頂点1のテクスチャマッピング
	glVertex2f(x1 + pos.x, y1 + pos.y);	//頂点１の指定
	glTexCoord2f(uv[2], uv[3]);			//頂点2のテクスチャマッピング
	glVertex2f(x2 + pos.x, y2 + pos.y);	//頂点２の指定
	glTexCoord2f(uv[4], uv[5]);			//頂点3のテクスチャマッピング
	glVertex2f(x3 + pos.x, y3 + pos.y);	//頂点３の指定
	glEnd();	//頂点指定終了

}




void CTriangle2::Render(CVector2 pos, float degree){
	CMatricx22 scale;
	scale.setscale(sinf(degree * M_PI / 180.0f) * 0.5f + 1.0f,
		sinf(degree * M_PI / 180.0f) * 0.5f + 1.0f);

	CVector2 w1 = scale * v1;
	CVector2 w2 = scale * v2;
	CVector2 w3 = scale * v3;

	CMatricx22 rotation;
	rotation.setrotation(degree);
	w1 = rotation * w1;
	w2 = rotation * w2;
	w3 = rotation * w3;

	glColor4f(r, g, b, a);
	glBegin(GL_TRIANGLES);
	glVertex2f(w1.x + pos.x, w1.y + pos.y);
	glVertex2f(w2.x + pos.x, w2.y + pos.y);
	glVertex2f(w3.x + pos.x, w3.y + pos.y);
	glEnd();
}

void CTriangle2::Render(CVector2 pos, float degree, float uv[]){
	/*CMatricx22 scale;
	scale.setscale(sinf(degree * M_PI / 180.0f) * 0.5f + 1.0f,
	sinf(degree * M_PI / 180.0f) * 0.5f + 1.0f);*/

	CVector2 w1 = v1;
	CVector2 w2 = v2;
	CVector2 w3 = v3;

	CMatricx22 rotation;
	rotation.setrotation(degree);
	w1 = rotation * w1;
	w2 = rotation * w2;
	w3 = rotation * w3;

	glColor4f(r, g, b, a);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(uv[0], uv[1]);			//頂点1のテクスチャマッピング
	glVertex2f(w1.x + pos.x, w1.y + pos.y);

	glTexCoord2f(uv[2], uv[3]);			//頂点2のテクスチャマッピング
	glVertex2f(w2.x + pos.x, w2.y + pos.y);

	glTexCoord2f(uv[4], uv[5]);			//頂点3のテクスチャマッピング
	glVertex2f(w3.x + pos.x, w3.y + pos.y);

	glEnd();	//頂点指定終了
}
