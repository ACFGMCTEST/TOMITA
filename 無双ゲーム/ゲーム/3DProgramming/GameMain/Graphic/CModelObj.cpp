#include "CModelObj.h"
#include <stdio.h>
#include <string.h>
#include "../Collision/ColType/CColTriangle.h"

#define COLOR  0.5f;//
/* obj�̒��g
#
# ����s���܂ŃR�����g�ł��B


mtllib �}�e���A���t�@�C����
�}�e���A���f�[�^���L�q�����t�@�C�����ł��B


g �O���[�v��
�O���[�v�̖��O�ł��B


����g�A�܂��̓t�@�C�������܂ł�1�̃O���[�v�ł��B
�O���[�v���������ƁA�S�̂���̃O���[�v�ɂȂ�܂��B


usemtl �}�e���A����
���̃O���[�v���g�p����}�e���A�������w�肵�܂��B
�}�e���A�����́A�}�e���A���t�@�C���ɋL�q���Ă���܂��B


v X Y Z
���_�̍��W�l�ł��B


vt U V
�e�N�X�`���̍��W�l�ł��B


vn X Y Z
�@���x�N�g���̒l�ł��B


f ���_���W�l�ԍ�/�e�N�X�`�����W�l�ԍ�/���_�@���x�N�g���ԍ� ...
�t�F�C�X�̏��ł��B
3�̐��l�� / ����؂�Ƃ��ĕ��т܂��B ����3�̐��l���A�t�F�C�X�̐��������т܂��B
�e�ԍ��́A1 ����n�܂�܂��B
�e�N�X�`�����W�l�ԍ��ƒ��_�@���x�N�g���ԍ��́A�ȗ��\�ł��B
*/
void CModelObj::LoadFile(char* filename) {
	//printf ��ʂ֕������o�͂���@\n ���s
//	printf("CModelObj::lodafile\n");
	//%s ������̎w��
//	printf("File Name %s\n", filename);
	//200�������̔z����쐬
	char buf[200];
	char p[4][16];
	CVector4 v;
	CVector2 v2;
	CTriangle t;
//	CMaterial m;
	//FILE �t�@�C���|�C���^
	FILE *fp;
	//fopen �t�@�C���̃I�[�v�� "r" �ǂݍ��݂̂�
	fp = fopen(filename, "r");
	if (fp) {
		//fgets �t�@�C������1�s���͂��� �Ō�ɂȂ��NULL��Ԃ�
		//sizeof(buf) buf�̃T�C�Y��Ԃ�
		while (fgets(buf, sizeof(buf), fp) != NULL) {
			//			printf("%s", buf);
			sscanf(buf, "%s %s %s %s\n", p[0], p[1], p[2], p[3]);
			if (strcmp(p[0], "mtllib") == 0){
//				printf("%s", p[1]);
//				mMaterialManager.loadfile(p[1]);
//				return;
			}
			/*v:���_�̍��W�l*/
			if (strcmp(p[0], "v") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorV.push_back(v);
			}
			/*vt:�e�N�X�`���̍��W�l�ł��B*/
			if (strcmp(p[0], "vt") == 0) {
				mFlagTex = true;
				sscanf(p[1], "%f", &v2.x);
				sscanf(p[2], "%f", &v2.y);
				mVectorTex.push_back(v2);
			}
			/*vn:�@���x�N�g���̒l�ł��B*/
			if (strcmp(p[0], "vn") == 0) {
				sscanf(p[1], "%f", &v.x);
				sscanf(p[2], "%f", &v.y);
				sscanf(p[3], "%f", &v.z);
				mVectorN.push_back(v);
			}
			/*usemtl:�}�e���A����*/
			if (strcmp(p[0], "usemtl") == 0) {
//				m = mMaterialManager.mMaterial[p[1]];
			}
			/**/
			if (strcmp(p[0], "f") == 0) {
				int v,tex,n;
				/*�e�N�X�`��������ꍇ*/
				if (mFlagTex) {
					sscanf(p[1], "%d/%d/%d", &v, &tex, &n);
					t.mVertex[0] = mVectorV[--v];
					sscanf(p[2], "%d/%d/%d", &v, &tex, &n);
					t.mVertex[1] = mVectorV[--v];
					sscanf(p[3], "%d/%d/%d", &v, &tex,&n);
					t.mVertex[2] = mVectorV[--v];
					///*�e�N�X�`���ݒ�*/
					//t.mUv[0][0] = mVectorTex[--tex].x; t.mUv[0][1] = mVectorTex[tex].y;
					//t.mUv[1][0] = mVectorTex[--tex].x; t.mUv[1][1] = mVectorTex[tex].y;
					//t.mUv[2][0] = mVectorTex[--tex].x; t.mUv[2][1] = mVectorTex[tex].y;
				}/*�e�N�X�`�����Ȃ��ꍇ*/
				else {
					sscanf(p[1], "%d//%d", &v, &n);
					t.mVertex[0] = mVectorV[--v];
					sscanf(p[2], "%d//%d", &v, &n);
					t.mVertex[1] = mVectorV[--v];
					sscanf(p[3], "%d//%d", &v, &n);
					t.mVertex[2] = mVectorV[--v];
				}
				/*�@���ݒ�*/
				t.mNormal = mVectorN[--n];
				/*�F�ݒ�*/
				t.diffuse[0] = t.diffuse[1] = t.diffuse[2] = COLOR;
				/*�|�W�V���������߂�*/
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
		//�O�p�`�R���C�_�𐶐�����
		new CColTriangle(triangle.mVertex[0], triangle.mVertex[1], triangle.mVertex[2]);
	}
}
