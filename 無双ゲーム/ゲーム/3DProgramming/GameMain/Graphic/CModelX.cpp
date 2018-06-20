#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

#include <string.h>	//文字列関数のインクルード

#include "CModelX.h"
#include "../../Light/CLight.h"

void CModelX::Load(char *file) {
	mAnimaFlag = true;
	//
	//ファイルサイズを取得する
	//
	//int fd = open(file, O_RDONLY);	//ファイルをオープンする
	//if (fd == -1) {	//エラーチェック
	//	printf("open error\n");
	//	return;
	//}
	//struct stat statBuf;
	//fstat(fd, &statBuf);	//ファイルの情報を取得する
	//close(fd);	//ファイルをクローズする
	//int size = statBuf.st_size;	//ファイルのサイズを取得する
	//
	//ファイルから3Dモデルのデータを読み込む
	//
	FILE *fp;	//ファイルポインタ変数の作成
	fp = fopen(file, "rb");	//ファイルをオープンする
	if (fp == NULL) {	//エラーチェック
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char *buf = mpPointer = new char[size + 1];	//ファイルサイズ+1バイト分の領域を確保
	fread(buf, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
	buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
	fclose(fp);	//ファイルをクローズする

	CModelXFrame *p = new CModelXFrame();
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	mFrame.push_back(p);
	bool AnimationSetFlag = false; //AnimationSetが複数ある場合があるので一回のみにする

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();	//単語の取得
		//17
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material の時
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0) {
			//20
			//フレーム名取得
			GetToken();
			if (!strchr(mToken, '{')) {

				//フレームが無ければ
				if (FindFrame(mToken) == 0) {
					//フレームを作成する
					p->mChild.push_back(new CModelXFrame(this));
					//				new CModelXFrame(this);
				}
				////フレームを作成する
				//削除new CModelXFrame(this);
			}
			else {
				SkipNode();
				GetToken(); //}
			}
		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0 && !AnimationSetFlag) {
			new CAnimationSet(this);
			AnimationSetFlag = true;
		}
	}

	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する

	//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();
	CreateVertexBuffer();

	mShader.load("skinmesh.vert", "skinmesh.flag");
}

/*アニメーションがないバージョン*/
void CModelX::NoAnimaLoad(char *file) {

	FILE *fp;	//ファイルポインタ変数の作成
	fp = fopen(file, "rb");	//ファイルをオープンする
	if (fp == NULL) {	//エラーチェック
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char *buf = mpPointer = new char[size + 1];	//ファイルサイズ+1バイト分の領域を確保
	fread(buf, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
	buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
	fclose(fp);	//ファイルをクローズする

	CModelXFrame *p = new CModelXFrame();
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	mFrame.push_back(p);

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();	//単語の取得
					//17
					//template 読み飛ばし
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material の時
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0) {
			//20
			//フレーム名取得
			GetToken();
			if (!strchr(mToken, '{')) {

				//フレームが無ければ
				if (FindFrame(mToken) == 0) {
					//フレームを作成する
					p->mChild.push_back(new CModelXFrame(this));
					//				new CModelXFrame(this);
				}
				////フレームを作成する
				//削除new CModelXFrame(this);
			}
			else {
				SkipNode();
				GetToken(); //}
			}
		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する

							//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();
	CreateVertexBuffer();

	mFrame[0]->Animate(&CMatrix44());

	mShader.load("skinmesh.vert", "skinmesh.flag");
}



/*
GetToken
文字列データから、単語を1つ取得する
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//タブ(\t)改行(\r)(\n)，；”以外の文字になるまで読み飛ばす
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p)) p++;

	if (*p == '{' || *p == '}') {
		*q++ = *p++;	//{または}ならmTokenに代入し次の文字へ
	}
	else {
		//タブ(\t)改行(\r)(\n)，；”}の文字になるまでmTokenに代入する
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mTokenの最後に\0を代入
	mpPointer = p;	//次の読み込むポイントを更新する
	//もしmTokenが//の場合は、コメントなので改行まで読み飛ばす
	if (!strcmp("//", mToken)) {
		//改行まで読み飛ばす
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//読み込み位置の更新
		mpPointer = p;
		//単語を取得する（再帰呼び出し）
		GetToken();
	}
}

/*
SkipNode
ノードを読み飛ばす
*/
void CModelX::SkipNode() {
	//文字が終わったら終了
	while (*mpPointer != '\0') {
		GetToken();	//次の単語取得
		//{が見つかったら終了
		if (strchr(mToken, '{')) break;
	}
	int count = 1;
	//文字が終わるか、カウントが0になったら終了
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//次の単語取得
		//{を見つけるとカウントアップ
		if (strchr(mToken, '{')) count++;
		//}を見つけるとカウントダウン
		else if (strchr(mToken, '}')) count--;
	}
}
/*
GetFloatToken
単語を浮動小数点型のデータで返す
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//文字列をfloat型へ変換
	return atof(mToken);
}
/*
GetIntToken
単語を整数型のデータで返す
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}

/*色セット*/
void CModelX::SetColor(float r, float g, float b, float a){
	//マテリアル配列のイテレータ作成
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		(*itr)->mDiffuse[0] = r;
		(*itr)->mDiffuse[1] = g;
		(*itr)->mDiffuse[2] = b;
		(*itr)->mDiffuse[3] = a;
	}
}
/*色が設定されているか判断*/
bool CModelX::ColorFlag(){
	if (mFrame[0]->mMesh.mRed == 0.0f &&
		mFrame[0]->mMesh.mGreen == 0.0f &&
		mFrame[0]->mMesh.mBlue == 0.0f &&
		mFrame[0]->mMesh.mAlpha == 0.0f){
		return false;
	}
	else
	{
		return true;
	}
}
/*
Render
全てのフレームの描画処理を呼び出す
*/
void CModelX::Render() {

	for (int i = 0; i < mFrame.size(); i++) {
		if(mAnimaFlag)	mFrame[i]->Render();
		else {
			mFrame[i]->NoaAnimaRender();
		}
		//if (ColorFlag())glMaterialfv(GL_FRONT, GL_DIFFUSE, CVector3(mRed, mGreen, mBlue, mAlpha});//色の設定
	}
}


/*
AnimateFrame
フレームの変換行列をアニメーションデータで更新する
*/
void CModelX::AnimateFrame() {
	//アニメーションで適用されるフレームの
	//変換行列をゼロクリアする
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0) continue;
		//フレーム分（Animation分）繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix44));
		}
	}
	//アニメーションに該当するフレームの変換行列を
	//アニメーションのデータで設定する
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0) continue;
		//フレーム分（Animation分）繰り返す
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			//フレームを取得する
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrame[animation->mFrameIndex];
			//キーがない場合は飛ばず
			if (animation->mpKey == 0) continue;
			//時間を取得
			float time = anim->mTime;
			//最初の時間より小さい場合
			if (time < animation->mpKey[0].mTime) {
				//変換行列を0コマ目の行列で更新
				frame->mTransformMatrix += animation->mpKey[0].mMatrix * anim->mWeight;
			}
			//最後の時間より大きい場合
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime) {
				//変換行列を最後のコマの行列で更新
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * anim->mWeight;
			}
			else {
				//時間の途中の場合
				for (int k = 1; k < animation->mKeyNum; k++) {
					//変換行列を、線形補間にて更新
					if (time < animation->mpKey[k].mTime &&
						animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime) {
						float r = (animation->mpKey[k].mTime - time) / (animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix +=
							(animation->mpKey[k - 1].mMatrix * r + animation->mpKey[k].mMatrix * (1 - r)) * anim->mWeight;
						break;
					}
				}
			}
		}
	}
#ifdef _DEBUG
	//for (int i = 0; i < mFrame.size(); i++) {
	//	printf("Frame:%s\n", mFrame[i]->mpName);
	//	for (int j = 0; j < 16; j++) {
	//		printf("%10f", mFrame[i]->mTransformMatrix.f[j]);
	//		if (j % 4 == 3) printf("\n");
	//	}
	//}
#endif

	//Set mCombinedMatrix mSkinningMatrix
	//	mFrame[0]->Animate(world);
}
//16
/*
SetSkinWeightFrameIndex
スキンウェイトにフレーム番号を設定する
*/
void CModelX::SetSkinWeightFrameIndex() {
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//スキンウェイト分繰り返し
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++) {
				//フレーム名のフレームを取得する
				CModelXFrame* frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//フレーム番号を設定する
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}
//16
/*
AnimateVertex
頂点にアニメーションを適用する
*/
void CModelX::AnimateVertex() {
	//フレーム数分繰り返し
	for (int i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}
//17
/*
FindMaterial
マテリアル名に該当するマテリアルを返却する
*/
CMaterial* CModelX::FindMaterial(char* name) {
	//マテリアル配列のイテレータ作成
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列を先頭から順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}
	}
	//無い時はNULLを返却
	return NULL;
}
//18
/*
FindTexture
nameに該当するファイル名を持つテクスチャを検索して
返却する
*/
CTexture* CModelX::FindTexture(char* name) {

	//テクスチャ配列のイテレータ作成
	std::vector<CTexture*>::iterator itr;
	
	//テクスチャ配列の先頭から順に検索
	for (itr = mTexture.begin(); itr != mTexture.end(); itr++) {
		

		//名前が一致すればテクスチャのポインタを返却
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}

		
	}
	//無い時はNULLを返却
	return NULL;
}


/*
FindFrame
フレーム名に該当するフレームのアドレスを返す
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	/*ハンマーン装備調整デバック*/



	//イテレータの作成
	std::vector<CModelXFrame*>::iterator itr;
	//先頭から最後まで繰り返す
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++) {
		//名前が一致したか？
		if (strcmp(name, (*itr)->mpName) == 0) {
			//一致したらそのアドレスを返す
			return *itr;
		}
	}
	//一致するフレーム無い場合はNULLを返す
	return NULL;
}
/*
AddAnimationSet
アニメーションセットを追加します
*/
int count = 0;
void CModelX::AddAnimationSet(char *file) {
	Load(file);
}

void CModelX::CreateVertexBuffer() {
	for (int i = 0; i < mFrame.size(); i++) {
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			mFrame[i]->mMesh.CreateVertexBuffer();
		}
	}
}

/*
CModelXFrame
*/
CModelXFrame::CModelXFrame(CModelX* model) {
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.identity();
	//20
	////次の単語（フレーム名の予定）を取得する
	//削除model->GetToken(); // frame name
	//フレーム名分エリアを確保する
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名をコピーする
	strcpy(mpName, model->mToken);
	//次の単語（{の予定）を取得する
	model->GetToken();  // {
	//文字が無くなったら終わり
	while (*model->mpPointer != '\0') {
		//次の単語取得
		model->GetToken(); // Frame
		//}かっこの場合は終了
		if (strchr(model->mToken, '}')) break;
		//新なフレームの場合は、子フレームに追加
		if (strcmp(model->mToken, "Frame") == 0) {
			//20
			//フレーム名取得
			model->GetToken();
			if (!strchr(model->mToken, '{')) {

				//フレームが無ければ
				if (model->FindFrame(model->mToken) == 0) {
					//フレームを作成し、子フレームの配列に追加
					mChild.push_back(new CModelXFrame(model));
				}
				////フレームを作成し、子フレームの配列に追加
				//削除mChild.push_back(new CModelXFrame(model));
			}
			else {
				model->SkipNode();
				model->GetToken(); //}
			}
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0) {
			model->GetToken(); // {
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++) {
				mTransformMatrix.f[i] = model->GetFloatToken();
			}
			model->GetToken(); // }
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mMesh.Init(model);
			if (mMesh.mFaceNum > 0) {
				model->mMesh.push_back(&mMesh);
			}
		}
		else {
			//上記以外の要素は読み飛ばす
			model->SkipNode();
		}
	}
#ifdef _DEBUG
	//printf("%s\n", mpName);
	//for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++) {
	//	printf("%10f", mTransformMatrix.f[i]);
	//	if ((i+1) % 4 == 0) printf("\n");
	//}
#endif
}
/*
Render
メッシュの面数が0以上なら描画する
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}
/*アニメーションないバージョン*/
void CModelXFrame::NoaAnimaRender() {
	if (mMesh.mFaceNum != 0) {
		glPushMatrix();
		glMultMatrixf(mCombinedMatrix.f);
		mMesh.Render();
		glPopMatrix();
	}
}

/*
Animate
合成行列の作成
*/
void CModelXFrame::Animate(CMatrix44* parent) {
	//親からの変換行列に、自分の変換行列を掛ける
	mCombinedMatrix = (*parent) * mTransformMatrix; //合成行列計算
	//子フレームの合成行列を作成する
	for (int i = 0; i < mChild.size(); i++) {
		mChild[i]->Animate(&mCombinedMatrix);
	}
#ifdef _DEBUG
	//printf("%s\n", mpName);
	//for (int i = 0; i < ARRAY_SIZE(mCombinedMatrix.f); i++) {
	//	printf("%10f", mCombinedMatrix.f[i]);
	//	if ((i+1) % 4 == 0) printf("\n");
	//}
#endif
}


/*
CMesh
*/
/*
Init
Meshのデータを取り込む
*/
void CMesh::Init(CModelX *model) {
	model->GetToken();	// { or 名前
	if (!strchr(model->mToken, '{')) {
		//名前の場合、次が{
		model->GetToken();	// {
	}
	//頂点数の取得
	mVertexNum = model->GetIntToken();
	//頂点数分エリア確保
	mpVertex = new CVector3[mVertexNum];
	//16
	mpAnimateVertex = new CVector3[mVertexNum];
	//頂点数分データを取り込む
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].x = model->GetFloatToken();
		mpVertex[i].y = model->GetFloatToken();
		mpVertex[i].z = model->GetFloatToken();
	}

	mFaceNum = model->GetIntToken();	//面数読み込み
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();	//頂点数読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	//文字が無くなったら終わり
	while (*model->mpPointer != '\0') {
		model->GetToken();	//MeshNormals
		//}かっこの場合は終了
		if (strchr(model->mToken, '}')) break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();	// {
			//法線データ数を取得
			mNormalNum = model->GetIntToken();
			//法線のデータを配列に取り込む
			CVector3 *pNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].x = model->GetFloatToken();
				pNormal[i].y = model->GetFloatToken();
				pNormal[i].z = model->GetFloatToken();
			}
			//法線数=面数×３
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//頂点毎に法線データを設定する
			mpNormal = new CVector3[mNormalNum];
			mpAnimateNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken(); // 3
				ni = model->GetIntToken();
				//				mpNormal[mpVertexIndex[i]] = pNormal[ni];
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				//				mpNormal[mpVertexIndex[i + 1]] = pNormal[ni];
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				//				mpNormal[mpVertexIndex[i + 2]] = pNormal[ni];
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[] pNormal;
			model->GetToken();	// }
		}
		// MeshMaterialListのとき
		else if (strcmp(model->mToken, "MeshMaterialList") == 0) {
			model->GetToken(); // {
			mMaterialNum = model->GetIntToken();	// Materialの数
			mMaterialIndexNum = model->GetIntToken();	// FaceNum
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//マテリアルデータの作成
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();	// Material
				//if (strcmp(model->mToken, "Material") == 0) {
				//	mMaterial.push_back(new CMaterial(model));
				//}
				//17S
				if (strcmp(model->mToken, "Material") == 0) {
					// 新規
					mMaterial.push_back(new CMaterial(model));
				}
				else {
					// {  既出
					model->GetToken();	//MaterialName
					mMaterial.push_back(model->FindMaterial(model->mToken));
					model->GetToken();	// }
				}
				//17E
			}
			model->GetToken();	// } //End of MeshMaterialList
		}
		//SkinWeightsのとき
		else if (strcmp(model->mToken, "SkinWeights") == 0) {
			//CSkinWeightsクラスのインスタンスを作成し、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		//19
		//テクスチャ座標の時
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0) {
			model->GetToken();	// {
			//テクスチャ座標数を取得
			int textureCoordsNum = model->GetIntToken();
			//テクスチャ座標のデータを配列に取り込む
			mpTextureCoords = new CVector2[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i].x = model->GetFloatToken();
				mpTextureCoords[i].y = model->GetFloatToken();
			}
			model->GetToken();	// }
		}
		else {
			//以外のノードは読み飛ばし
			model->SkipNode();
		}
	}

#ifdef _DEBUG
	//printf("NormalNum:%d\n", mNormalNum);
	//for (int i = 0; i < mNormalNum ; i++) {
	//	printf("%10f%10f%10f\n", mpNormal[i].x, mpNormal[i].y, mpNormal[i].z);
	//}
#endif
}
/*
Render
画面に描画する
*/
void CMesh::Render() {

	/* 頂点データ，法線データ，テクスチャ座標の配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	/* 頂点データ，法線データ，テクスチャ座標の配列を有効にする */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//16
	/* 頂点データ，法線データ，テクスチャ座標の場所を指定する */
	//glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	//glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);


	////16
	///* 頂点データ，法線データ，テクスチャ座標の場所を指定する */
	//glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	//glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	//19
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/* 頂点のインデックスの場所を指定して図形を描画する */
	for (int i = 0; i < mFaceNum; i++) {
		//マテリアルを適用する
		mMaterial[mpMaterialIndex[i]]->SetMaterial();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		//19
		//マテリアルを解除する
		mMaterial[mpMaterialIndex[i]]->UnSetMaterial();
	}

	/* 頂点データ，法線データ，テクスチャ座標の配列を無効にする */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CMesh::Render(CModelX *model, CMatrix44 transformMatrix[], int transformMatrixSize) {
	//シェーダーを有効にする
	model->mShader.enable();
	/*
	ライト設定
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	int lightId = glGetUniformLocation(model->mShader.getProgram(), "LightVec");  //ライトの向きを設定
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(model->mShader.getProgram(), "LightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	glUniform3fv(glGetUniformLocation(model->mShader.getProgram(), "LightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//スキンメッシュ行列設定
	int MatrixLocation = glGetUniformLocation(model->mShader.getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, transformMatrixSize, GL_FALSE, transformMatrix[0].f);
	/*
	ワールドトランスフォーム
	*/
	int worldId = glGetUniformLocation(model->mShader.getProgram(), "WorldMatrix");
	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	//頂点バッファをバインドする
	glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBuffer);
	//頂点座標の位置を設定
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//法線ベクトルの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//テクスチャマッピングデータの位置を設定
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//スキンウェイトデータの位置を設定
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(model->mShader.getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//スキンウェイトのインデックスデータの位置を設定
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(model->mShader.getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);


	//マテリアル毎に頂点を描画します
	int k = 0;

	for (int i = 0; i < mMaterial.size(); i++) {
		mMaterial[i]->SetShader(&model->mShader);
		//三角形描画、開始頂点番号、描画に使用する頂点数
		glDrawArrays(GL_TRIANGLES, k, mMaterialVertexCount[i]);	//DrawArrays:VertexIndexなし
		k += mMaterialVertexCount[i];
		mMaterial[i]->UnSetMaterial();
	}

	//無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//頂点バッファのバインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//シェーダーを無効にする
	model->mShader.disable();
}

//16
/*
AnimateVertex
頂点にアニメーションを適用
*/
void CMesh::AnimateVertex(CModelX *model) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector3)* mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)* mNormalNum);
	//スキンウェイト分繰り返し
	for (int i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合成
		CMatrix44 mSkinningMatrix = model->mFrame[frameIndex]->mCombinedMatrix * mSkinWeights[i]->mOffset;
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}

/*
頂点バッファを作成する
*/
void CMesh::CreateVertexBuffer() {
	//メッシュ毎に一回作成すればよい
	if (mMyVertexBuffer > 0)
		return;

	if (mVertexNum > 0) {
		//頂点インデックスを使わず、全ての面データを作成
		CMyVertex *pmyVertex, *vec;
		//頂点数計算
		mMyVertexNum = mFaceNum * 3;
		//頂点数分頂点配列作成
		pmyVertex = new CMyVertex[mMyVertexNum];
		vec = new CMyVertex[mVertexNum];
		for (int j = 0; j < mVertexNum; j++) {
			//頂点座標設定
			vec[j].mPosition = mpVertex[j];
			//テクスチャマッピング設定
			if (mpTextureCoords != NULL)
				vec[j].mTextureCoords = mpTextureCoords[j];
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//スキンウェイト設定
		for (int k = 0; k < mSkinWeights.size(); k++) {
			for (int l = 0; l < mSkinWeights[k]->mIndexNum; l++) {
				int idx = mSkinWeights[k]->mpIndex[l];
				for (int m = 0; m < 4; m++) {
					if (vec[idx].mBoneIndex[m] == 0) {
						vec[idx].mBoneIndex[m] = k + 1;
						vec[idx].mBoneWeight[m] = mSkinWeights[k]->mpWeight[l];
						break;
					}
				}
			}
		}

		int k = 0;
		//マテリアル番号の昇順に面の頂点を設定
		for (int i = 0; i < mMaterial.size(); i++) {
			int w = k;
			for (int j = 0; j < mMaterialIndexNum; j++) {
				if (mpMaterialIndex[j] == i) {
					//頂点配列に設定し、法線を設定する
					pmyVertex[k] = vec[mpVertexIndex[j * 3]];
					pmyVertex[k++].mNormal = mpNormal[j * 3];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 1]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 1];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 2]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 2];

				}
			}
			//マテリアル毎の頂点数を追加する
			mMaterialVertexCount.push_back(k - w);
		}

		//頂点バッファの作成
		glGenBuffers(1, &mMyVertexBuffer);
		//頂点バッファをバインド
		glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBuffer);
		//バインドしたバッファにデータを転送
		glBufferData(GL_ARRAY_BUFFER, sizeof(CMyVertex)*mMyVertexNum, pmyVertex, GL_STATIC_DRAW);
		//バインド解除
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//配列解放
		delete[] pmyVertex;
		delete[] vec;
		pmyVertex = NULL;
	}
}



/*
Materialデータの読み込みと設定
*/
CMaterial::CMaterial(CModelX *model)
: mpName(0)
, mpTextureFilename(0)
//18
, mTextureId(0)
{
	//17
	//CModelXにマテリアルを追加する
	model->mMaterial.push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->mToken, "{") != 0) {
		//{でないときはマテリアル名
		mpName = new char[strlen(model->mToken) + 1];
		strcpy(mpName, model->mToken);
		model->GetToken(); // {
	}
	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();

	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken(); // TextureFilename or }

	if (strcmp(model->mToken, "TextureFilename") == 0) {
		//テクスチャありの場合、テクスチャファイル名取得
		model->GetToken(); // {
		model->GetToken(); // filename

		/*テクスチャの場所指定ない場合*/
		if (model->mTexDirectory.empty()) {
			mpTextureFilename = new char[strlen(model->mToken) + 1];
			strcpy(mpTextureFilename, model->mToken);
		}
		/*ある場合*/
		else {
			mpTextureFilename = new char[model->mTexDirectory.size() + strlen(model->mToken) + 1];
			strcpy(mpTextureFilename, model->mTexDirectory.c_str());
			strcat(mpTextureFilename, model->mToken);
		}


		//テクスチャファイル名でテクスチャを検索する
		CTexture *p = model->FindTexture(mpTextureFilename);
		//テクスチャが在る時
		if (p) {
			//テクスチャIDを取得
			mTextureId = p->id;
		}
		else {
			//無い場合、テクスチャ読み込み
			p = new CTexture(mpTextureFilename);
			if (p->mpName) {
				//テクスチャ配列に追加
				model->mTexture.push_back(p);
				//テクスチャIDを取得
				mTextureId = p->id;
			}
		}
		model->GetToken(); // }
		model->GetToken(); // }
	}
	for (int i = 0; i < 4; i++)
	{
		mColorRGBA[i] = 0;
	}

#ifdef _DEBUG
	//printf("Material\n");
	//printf("Diffuse:%10f %10f %10f %10f\n", mDiffuse[0], mDiffuse[1], mDiffuse[2], mDiffuse[3]);
	//printf("Power:%10f\n", mPower);
	//printf("Specular:%10f %10f %10f %10f\n", mSpecular[0], mSpecular[1], mSpecular[2]);
	//printf("Emissive:%10f %10f %10f %10f\n", mEmissive[0], mEmissive[1], mEmissive[2]);
#endif
}

/*
SetMaterial
マテリアルを適用する
*/
void CMaterial::SetMaterial() {
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//19
	//テクスチャが有る場合
	if (mTextureId > 0) {
		//テクスチャを使用可能にする
		glEnable(GL_TEXTURE_2D);
		//テクスチャをバインドする
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		//テクスチャマッピングのデータを有効にする
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

//Add Shader
/*
マテリアルのデータをシェーダーに設定する
*/
void CMaterial::SetShader(CShader *shader) {

	int AmbientId = glGetUniformLocation(shader->getProgram(), "Ambient");  //カラー設定
	glUniform4fv(AmbientId, 1, (GLfloat*)mDiffuse);

	int DiffuseId = glGetUniformLocation(shader->getProgram(), "Diffuse");  //カラー設定
	glUniform4fv(DiffuseId, 1, (GLfloat*)mDiffuse);

	int ColorRGAB_ID = glGetUniformLocation(shader->getProgram(), "ColorRGBA");  //カラー設定　重ねてカラーの表示
	glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(shader->getProgram(), "Pow");  //強さを設定
	glUniform1f(PowId, mPower);

	int SpecularId = glGetUniformLocation(shader->getProgram(), "Specular");  //カラー設定
	glUniform3fv(SpecularId, 1, (GLfloat*)mSpecular);

	int EmissiveId = glGetUniformLocation(shader->getProgram(), "Emissive");  //カラー設定
	glUniform3fv(EmissiveId, 1, (GLfloat*)mEmissive);
	GLint samplerId = glGetUniformLocation(shader->getProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(shader->getProgram(), "TextureFlg");
	if (mTextureId > 0) {
		//テクスチャあり
		SetMaterial();
		glUniform1i(samplerId, 0);//GL_TEXTURE1を適用
		glUniform1i(textureFlg, 0);//GL_TEXTURE1を適用
	}
	else
	{
		//テクスチャなし
		glUniform1i(textureFlg, -1);//GL_TEXTURE1を適用
	}
}

/*
UnSetMaterial
テクスチャマッピングを無効にする
*/
void CMaterial::UnSetMaterial() {
	//テクスチャが有る時
	if (mTextureId > 0) {
		//テクスチャのバインドを解く
		glBindTexture(GL_TEXTURE_2D, 0);
		//テクスチャを無効にする
		glDisable(GL_TEXTURE_2D);
		//テクスチャマッピングのデータを無効にする
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
CSkinWeights
スキンウェイトの読み込み
*/
CSkinWeights::CSkinWeights(CModelX *model)
: mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(0)
, mpWeight(0)
{
	model->GetToken();	// {
	model->GetToken();	// FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//頂点番号数取得
	mIndexNum = model->GetIntToken();
	//頂点番号数が0を超える
	if (mIndexNum > 0) {
		//頂点番号と頂点ウェイトのエリア確保
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
#ifdef _DEBUG
	else {
		printf("SwinWeight indexNum : 0 Frame Name:%s\n", mpFrameName);
	}
#endif
	//オフセット行列取得
	for (int i = 0; i < 16; i++) {
		mOffset.f[i] = model->GetFloatToken();
	}
	model->GetToken();	// }

#ifdef _DEBUG
	//printf("\nSkinWeights:%s\n", mpFrameName);
	//for (int i = 0; i < mIndexNum; i++) {
	//	printf("%d %10f\n", mpIndex[i], mpWeight[i]);
	//}
	//for (int i = 0; i < 16; i++) {
	//	printf("%10f", mOffset.f[i]);
	//	if ((i + 1) % 4 == 0) printf("\n");
	//}
#endif
}

/*

CAnimationSet

*/
CAnimationSet::CAnimationSet(CModelX *model)
: mpName(0)
//14S
, mTime(0)
, mWeight(0)
, mMaxTime(0)
//14E
{
	model->mAnimationSet.push_back(this);

	model->GetToken();	// Animation Name
	//アニメーションの名前を退避
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);

	model->GetToken(); // {

	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or Animation


		if (strchr(model->mToken, '}')) {
			model->GetToken(); // AnimationSetがある場合飛ばす
			//break;
		}

		if (strcmp(model->mToken, "Animation") == 0) {
			//Animation要素読み込み
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//終了時間設定
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
#ifdef _DEBUG
	//	printf("AnimationSet:%s\n", mpName);
#endif
}

CAnimation::CAnimation(CModelX *model)
: mpFrameName(0)
, mFrameIndex(0)
, mKeyNum(0)
, mpKey(0)
{
	model->GetToken(); // { or Animation Name
	if (strchr(model->mToken, '{')) {
		model->GetToken(); // {
	}
	else {
		model->GetToken(); // {
		model->GetToken(); // {
	}
	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex = model->FindFrame(model->mToken)->mIndex;
	model->GetToken(); // }

	//キーの配列を保存しておく配列
	CMatrix44 *key[4] = { 0, 0, 0, 0 };
	//時間の配列を保存しておく配列
	float *time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		

		if (strchr(model->mToken, '}')) {
			break;
		}
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->GetToken(); // {
			//データのタイプ取得
			int type = model->GetIntToken();
			//時間数取得
			mKeyNum = model->GetIntToken();
			switch (type) {
			case 0: // Rotation Quaternion
				//行列の配列を時間数分確保
				key[type] = new CMatrix44[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 4を読み飛ばし
					//w,x,y,zを取得
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1: //拡大・縮小の行列作成
				key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken(); // Time
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].m00 = x;
					key[type][i].m11 = y;
					key[type][i].m22 = z;
				}
				break;
			case 2: //移動の行列作成
				key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					time[type][i] = model->GetFloatToken(); // Time
					model->GetToken(); // 3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					CVector3 vec(x, y, z);
					key[type][i].translate(vec);
				}
				break;
			case 4: //行列データを取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					mpKey[i].mTime = model->GetFloatToken(); // Time
					model->GetToken(); // 16
					for (int j = 0; j < 16; j++) {
						mpKey[i].mMatrix.f[j] = model->GetFloatToken();
					}
				}
				break;
			};

			model->GetToken();// }
		
			
		}
		else {
			model->SkipNode();
		}
		
	}
	//行列データではない時
	if (mpKey == 0) {
		//時間数分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//時間設定
			mpKey[i].mTime = time[2][i]; // Time
			//行列作成 Position * Rotation * Size
			mpKey[i].mMatrix = key[2][i] * key[0][i] * key[1][i];
		}
	}
	//確保したエリア解放
	for (int i = 0; i < ARRAY_SIZE(key); i++) {
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}

#ifdef _DEBUG
	//printf("Animation:%s\n", mpFrameName);
	//for (int j = 0; j < 16; j++) {
	//	printf("%10f", mpKey[0].mMatrix.f[j]);
	//	if (j % 4 == 3) printf("\n");
	//}
#endif

}
/*アニメのスピード*/
#define ANIMA_SPEED 60 * 4
/*
Init
初期化処理
*/
void CModelXS::Init(CModelX *model) {
	mpModel = model;
	//アニメーションパラメータ初期化
	mAnimationIndex = 0;	//最初のアニメーションにします
	mAnimationLoopFlg = true;	//アニメーションを繰り返す
	mAnimationFrameSize = ANIMA_SPEED;	//フレームのサイズ指定
	mAnimationTime = 0.0f;	//最初のコマにします
	mpModel->mAnimationSet[0]->mWeight = 1.0f;
	//ボーン合成行列の配列作成
	mpCombinedMatrix = new CMatrix44[model->mFrame.size()];
	//メッシュ分、スキンメッシュ行列を作成
	mpMeshSkinMatrix = new CMeshSkinMatrix[model->mMesh.size()];
	//メッシュ毎のスキンメッシュ行列の配列を作成
	for (int i = 0; i < model->mMesh.size(); i++) {
		mpMeshSkinMatrix[i].mSize = model->mMesh[i]->mSkinWeights.size() + 1;
		mpMeshSkinMatrix[i].mpSkinnedMatrix = new CMatrix44[mpMeshSkinMatrix[i].mSize];
	}
}

/*
ChangeAnimation
アニメーションを切り替える
index:アニメーションの番号
loop:true 繰り返す
framesize：最後まで再生するのに使用されるフレーム数
*/
void CModelXS::ChangeAnimation(int index, bool loop, float framesize) {
	mAnimaFlag = true;
	//同じ場合は切り替えない
	if (mAnimationIndex == index){
		return;
	}
	//番号、繰り返し、フレーム数を設定
	mAnimationIndex = index;
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//アニメーションの時間を最初にする
	mAnimationTime = 0.0f;
}

/*
Update
更新する
matrix：移動、回転、拡大縮小の行列
*/
void CModelXS::Update(CMatrix44 &matrix) {
	////現在のアニメーションと異なるとき
	//if (mpModel->mAnimationIndex != mAnimationIndex) {
	//	mpModel->mAnimationSet[mpModel->mAnimationIndex]->mWeight = 0.0f;
	//	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
	//	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
	//	mpModel->mAnimationIndex = mAnimationIndex;
	//}
	/*アニメーションのフラグが立っていないときはしない*/
	if (mAnimaFlag) {
		//最後まで再生していない
		if (mAnimationTime <= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
			//時間を進める
			mAnimationTime += mpModel->mAnimationSet[mAnimationIndex]->mMaxTime
				/ mAnimationFrameSize;
		}
		else {
			//繰り返しの場合は、時間を0に戻す
			if (mAnimationLoopFlg) {
				mAnimationTime = 0.0f;
			}
		}


		for (int i = 0; i < mpModel->mAnimationSet.size(); i++)
		{
			mpModel->mAnimationSet[i]->mWeight = 0.0f;
		}
		mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
		mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
		mAnimaFlag = false;
	}
	UpdateSkinMatrix(matrix);
	/*
	//フレームの変換行列をアニメーションで更新する
	mpModel->AnimateFrame();
	//フレームの合成行列を計算する
	mpModel->mFrame[0]->Animate(&matrix);
	//フレームの合成行列を退避する

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
	mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//メッシュ毎のスキンメッシュ行列配列を設定する
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
	for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
	//スキンメッシュの行列配列を退避する
	mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
	= mpCombinedMatrix[ mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex] * mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
	}
	}
	*/
}

void CModelXS::UpdateSkinMatrix(CMatrix44 &matrix) {
	//フレームの変換行列をアニメーションで更新する
	mpModel->AnimateFrame();
	//フレームの合成行列を計算する
	mpModel->mFrame[0]->Animate(&matrix);
	//フレームの合成行列を退避する

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//メッシュ毎のスキンメッシュ行列配列を設定する
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
		for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
			//スキンメッシュの行列配列を退避する
			mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
				= mpCombinedMatrix[mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex] * mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
		}
	}
}

/*MATRIXのアップデート*/
void CModelXS::MatrixUpdate(CMatrix44 &matrix){
	//フレームの変換行列をアニメーションで更新する
	mpModel->AnimateFrame();
	//フレームの合成行列を計算する
	mpModel->mFrame[0]->Animate(&matrix);
	//フレームの合成行列を退避する

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//メッシュ毎のスキンメッシュ行列配列を設定する
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
		for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
			//スキンメッシュの行列配列を退避する
			mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
				= mpCombinedMatrix[mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex]
				* mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
		}
	}
}
/*
描画する
*/
void CModelXS::Render() {
	/*描画する*/
	if (mRenderFlag) {
		//メッシュ毎に描画する
		for (int i = 0; i < mpModel->mMesh.size(); i++) {
			//モデル、スキンメッシュ行列配列、スキンメッシュ行列配列要素数
			mpModel->mMesh[i]->Render(mpModel, mpMeshSkinMatrix[i].mpSkinnedMatrix, mpMeshSkinMatrix[i].mSize);
		}
	}
}

