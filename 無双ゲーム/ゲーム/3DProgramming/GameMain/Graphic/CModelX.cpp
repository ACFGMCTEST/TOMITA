#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

#include <string.h>	//������֐��̃C���N���[�h

#include "CModelX.h"
#include "../../Light/CLight.h"

void CModelX::Load(char *file) {
	mAnimaFlag = true;
	//
	//�t�@�C���T�C�Y���擾����
	//
	//int fd = open(file, O_RDONLY);	//�t�@�C�����I�[�v������
	//if (fd == -1) {	//�G���[�`�F�b�N
	//	printf("open error\n");
	//	return;
	//}
	//struct stat statBuf;
	//fstat(fd, &statBuf);	//�t�@�C���̏����擾����
	//close(fd);	//�t�@�C�����N���[�Y����
	//int size = statBuf.st_size;	//�t�@�C���̃T�C�Y���擾����
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	FILE *fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char *buf = mpPointer = new char[size + 1];	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
	fread(buf, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
	fclose(fp);	//�t�@�C�����N���[�Y����

	CModelXFrame *p = new CModelXFrame();
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	mFrame.push_back(p);
	bool AnimationSetFlag = false; //AnimationSet����������ꍇ������̂ň��݂̂ɂ���

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
		//17
		//template �ǂݔ�΂�
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material �̎�
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//�P�ꂪFrame�̏ꍇ
		else if (strcmp(mToken, "Frame") == 0) {
			//20
			//�t���[�����擾
			GetToken();
			if (!strchr(mToken, '{')) {

				//�t���[�����������
				if (FindFrame(mToken) == 0) {
					//�t���[�����쐬����
					p->mChild.push_back(new CModelXFrame(this));
					//				new CModelXFrame(this);
				}
				////�t���[�����쐬����
				//�폜new CModelXFrame(this);
			}
			else {
				SkipNode();
				GetToken(); //}
			}
		}
		//�P�ꂪAnimationSet�̏ꍇ
		else if (strcmp(mToken, "AnimationSet") == 0 && !AnimationSetFlag) {
			new CAnimationSet(this);
			AnimationSetFlag = true;
		}
	}

	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������

	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	SetSkinWeightFrameIndex();
	CreateVertexBuffer();

	mShader.load("skinmesh.vert", "skinmesh.flag");
}

/*�A�j���[�V�������Ȃ��o�[�W����*/
void CModelX::NoAnimaLoad(char *file) {

	FILE *fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char *buf = mpPointer = new char[size + 1];	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
	fread(buf, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
	fclose(fp);	//�t�@�C�����N���[�Y����

	CModelXFrame *p = new CModelXFrame();
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	mFrame.push_back(p);

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();	//�P��̎擾
					//17
					//template �ǂݔ�΂�
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Material �̎�
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//�P�ꂪFrame�̏ꍇ
		else if (strcmp(mToken, "Frame") == 0) {
			//20
			//�t���[�����擾
			GetToken();
			if (!strchr(mToken, '{')) {

				//�t���[�����������
				if (FindFrame(mToken) == 0) {
					//�t���[�����쐬����
					p->mChild.push_back(new CModelXFrame(this));
					//				new CModelXFrame(this);
				}
				////�t���[�����쐬����
				//�폜new CModelXFrame(this);
			}
			else {
				SkipNode();
				GetToken(); //}
			}
		}
		//�P�ꂪAnimationSet�̏ꍇ
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������

							//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	SetSkinWeightFrameIndex();
	CreateVertexBuffer();

	mFrame[0]->Animate(&CMatrix44());

	mShader.load("skinmesh.vert", "skinmesh.flag");
}



/*
GetToken
������f�[�^����A�P���1�擾����
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//�^�u(\t)���s(\r)(\n)�C�G�h�ȊO�̕����ɂȂ�܂œǂݔ�΂�
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p)) p++;

	if (*p == '{' || *p == '}') {
		*q++ = *p++;	//{�܂���}�Ȃ�mToken�ɑ�������̕�����
	}
	else {
		//�^�u(\t)���s(\r)(\n)�C�G�h}�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mToken�̍Ō��\0����
	mpPointer = p;	//���̓ǂݍ��ރ|�C���g���X�V����
	//����mToken��//�̏ꍇ�́A�R�����g�Ȃ̂ŉ��s�܂œǂݔ�΂�
	if (!strcmp("//", mToken)) {
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p)) p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����i�ċA�Ăяo���j
		GetToken();
	}
}

/*
SkipNode
�m�[�h��ǂݔ�΂�
*/
void CModelX::SkipNode() {
	//�������I�������I��
	while (*mpPointer != '\0') {
		GetToken();	//���̒P��擾
		//{������������I��
		if (strchr(mToken, '{')) break;
	}
	int count = 1;
	//�������I��邩�A�J�E���g��0�ɂȂ�����I��
	while (*mpPointer != '\0' && count > 0) {
		GetToken();	//���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{')) count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}')) count--;
	}
}
/*
GetFloatToken
�P��𕂓������_�^�̃f�[�^�ŕԂ�
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}
/*
GetIntToken
�P��𐮐��^�̃f�[�^�ŕԂ�
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}

/*�F�Z�b�g*/
void CModelX::SetColor(float r, float g, float b, float a){
	//�}�e���A���z��̃C�e���[�^�쐬
	std::vector<CMaterial*>::iterator itr;
	//�}�e���A���z���擪���珇�Ɍ���
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		(*itr)->mDiffuse[0] = r;
		(*itr)->mDiffuse[1] = g;
		(*itr)->mDiffuse[2] = b;
		(*itr)->mDiffuse[3] = a;
	}
}
/*�F���ݒ肳��Ă��邩���f*/
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
�S�Ẵt���[���̕`�揈�����Ăяo��
*/
void CModelX::Render() {

	for (int i = 0; i < mFrame.size(); i++) {
		if(mAnimaFlag)	mFrame[i]->Render();
		else {
			mFrame[i]->NoaAnimaRender();
		}
		//if (ColorFlag())glMaterialfv(GL_FRONT, GL_DIFFUSE, CVector3(mRed, mGreen, mBlue, mAlpha});//�F�̐ݒ�
	}
}


/*
AnimateFrame
�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
*/
void CModelX::AnimateFrame() {
	//�A�j���[�V�����œK�p�����t���[����
	//�ϊ��s����[���N���A����
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//�Y������t���[���̕ϊ��s����[���N���A����
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix44));
		}
	}
	//�A�j���[�V�����ɊY������t���[���̕ϊ��s���
	//�A�j���[�V�����̃f�[�^�Őݒ肷��
	for (int i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0) continue;
		//�t���[�����iAnimation���j�J��Ԃ�
		for (int j = 0; j < anim->mAnimation.size(); j++) {
			//�t���[�����擾����
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrame[animation->mFrameIndex];
			//�L�[���Ȃ��ꍇ�͔�΂�
			if (animation->mpKey == 0) continue;
			//���Ԃ��擾
			float time = anim->mTime;
			//�ŏ��̎��Ԃ�菬�����ꍇ
			if (time < animation->mpKey[0].mTime) {
				//�ϊ��s���0�R�}�ڂ̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[0].mMatrix * anim->mWeight;
			}
			//�Ō�̎��Ԃ��傫���ꍇ
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime) {
				//�ϊ��s����Ō�̃R�}�̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * anim->mWeight;
			}
			else {
				//���Ԃ̓r���̏ꍇ
				for (int k = 1; k < animation->mKeyNum; k++) {
					//�ϊ��s����A���`��ԂɂčX�V
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
�X�L���E�F�C�g�Ƀt���[���ԍ���ݒ肷��
*/
void CModelX::SetSkinWeightFrameIndex() {
	//�t���[�������J��Ԃ�
	for (int i = 0; i < mFrame.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//�X�L���E�F�C�g���J��Ԃ�
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++) {
				//�t���[�����̃t���[�����擾����
				CModelXFrame* frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//�t���[���ԍ���ݒ肷��
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}
//16
/*
AnimateVertex
���_�ɃA�j���[�V������K�p����
*/
void CModelX::AnimateVertex() {
	//�t���[�������J��Ԃ�
	for (int i = 0; i < mFrame.size(); i++) {
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//���_���A�j���[�V�����ōX�V����
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}
//17
/*
FindMaterial
�}�e���A�����ɊY������}�e���A����ԋp����
*/
CMaterial* CModelX::FindMaterial(char* name) {
	//�}�e���A���z��̃C�e���[�^�쐬
	std::vector<CMaterial*>::iterator itr;
	//�}�e���A���z���擪���珇�Ɍ���
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		//���O����v����΃}�e���A���̃|�C���^��ԋp
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}
	}
	//��������NULL��ԋp
	return NULL;
}
//18
/*
FindTexture
name�ɊY������t�@�C���������e�N�X�`������������
�ԋp����
*/
CTexture* CModelX::FindTexture(char* name) {

	//�e�N�X�`���z��̃C�e���[�^�쐬
	std::vector<CTexture*>::iterator itr;
	
	//�e�N�X�`���z��̐擪���珇�Ɍ���
	for (itr = mTexture.begin(); itr != mTexture.end(); itr++) {
		

		//���O����v����΃e�N�X�`���̃|�C���^��ԋp
		if (strcmp(name, (*itr)->mpName) == 0) {
			return *itr;
		}

		
	}
	//��������NULL��ԋp
	return NULL;
}


/*
FindFrame
�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	/*�n���}�[�����������f�o�b�N*/



	//�C�e���[�^�̍쐬
	std::vector<CModelXFrame*>::iterator itr;
	//�擪����Ō�܂ŌJ��Ԃ�
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++) {
		//���O����v�������H
		if (strcmp(name, (*itr)->mpName) == 0) {
			//��v�����炻�̃A�h���X��Ԃ�
			return *itr;
		}
	}
	//��v����t���[�������ꍇ��NULL��Ԃ�
	return NULL;
}
/*
AddAnimationSet
�A�j���[�V�����Z�b�g��ǉ����܂�
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
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.identity();
	//20
	////���̒P��i�t���[�����̗\��j���擾����
	//�폜model->GetToken(); // frame name
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�������R�s�[����
	strcpy(mpName, model->mToken);
	//���̒P��i{�̗\��j���擾����
	model->GetToken();  // {
	//�����������Ȃ�����I���
	while (*model->mpPointer != '\0') {
		//���̒P��擾
		model->GetToken(); // Frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}')) break;
		//�V�ȃt���[���̏ꍇ�́A�q�t���[���ɒǉ�
		if (strcmp(model->mToken, "Frame") == 0) {
			//20
			//�t���[�����擾
			model->GetToken();
			if (!strchr(model->mToken, '{')) {

				//�t���[�����������
				if (model->FindFrame(model->mToken) == 0) {
					//�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
					mChild.push_back(new CModelXFrame(model));
				}
				////�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
				//�폜mChild.push_back(new CModelXFrame(model));
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
			//��L�ȊO�̗v�f�͓ǂݔ�΂�
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
���b�V���̖ʐ���0�ȏ�Ȃ�`�悷��
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}
/*�A�j���[�V�����Ȃ��o�[�W����*/
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
�����s��̍쐬
*/
void CModelXFrame::Animate(CMatrix44* parent) {
	//�e����̕ϊ��s��ɁA�����̕ϊ��s����|����
	mCombinedMatrix = (*parent) * mTransformMatrix; //�����s��v�Z
	//�q�t���[���̍����s����쐬����
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
Mesh�̃f�[�^����荞��
*/
void CMesh::Init(CModelX *model) {
	model->GetToken();	// { or ���O
	if (!strchr(model->mToken, '{')) {
		//���O�̏ꍇ�A����{
		model->GetToken();	// {
	}
	//���_���̎擾
	mVertexNum = model->GetIntToken();
	//���_�����G���A�m��
	mpVertex = new CVector3[mVertexNum];
	//16
	mpAnimateVertex = new CVector3[mVertexNum];
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].x = model->GetFloatToken();
		mpVertex[i].y = model->GetFloatToken();
		mpVertex[i].z = model->GetFloatToken();
	}

	mFaceNum = model->GetIntToken();	//�ʐ��ǂݍ���
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3) {
		model->GetToken();	//���_���ǂݔ�΂�
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	//�����������Ȃ�����I���
	while (*model->mpPointer != '\0') {
		model->GetToken();	//MeshNormals
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}')) break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();	// {
			//�@���f�[�^�����擾
			mNormalNum = model->GetIntToken();
			//�@���̃f�[�^��z��Ɏ�荞��
			CVector3 *pNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].x = model->GetFloatToken();
				pNormal[i].y = model->GetFloatToken();
				pNormal[i].z = model->GetFloatToken();
			}
			//�@����=�ʐ��~�R
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//���_���ɖ@���f�[�^��ݒ肷��
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
		// MeshMaterialList�̂Ƃ�
		else if (strcmp(model->mToken, "MeshMaterialList") == 0) {
			model->GetToken(); // {
			mMaterialNum = model->GetIntToken();	// Material�̐�
			mMaterialIndexNum = model->GetIntToken();	// FaceNum
			//�}�e���A���C���f�b�N�X�̍쐬
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++) {
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//�}�e���A���f�[�^�̍쐬
			for (int i = 0; i < mMaterialNum; i++) {
				model->GetToken();	// Material
				//if (strcmp(model->mToken, "Material") == 0) {
				//	mMaterial.push_back(new CMaterial(model));
				//}
				//17S
				if (strcmp(model->mToken, "Material") == 0) {
					// �V�K
					mMaterial.push_back(new CMaterial(model));
				}
				else {
					// {  ���o
					model->GetToken();	//MaterialName
					mMaterial.push_back(model->FindMaterial(model->mToken));
					model->GetToken();	// }
				}
				//17E
			}
			model->GetToken();	// } //End of MeshMaterialList
		}
		//SkinWeights�̂Ƃ�
		else if (strcmp(model->mToken, "SkinWeights") == 0) {
			//CSkinWeights�N���X�̃C���X�^���X���쐬���A�z��ɒǉ�
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		//19
		//�e�N�X�`�����W�̎�
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0) {
			model->GetToken();	// {
			//�e�N�X�`�����W�����擾
			int textureCoordsNum = model->GetIntToken();
			//�e�N�X�`�����W�̃f�[�^��z��Ɏ�荞��
			mpTextureCoords = new CVector2[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i].x = model->GetFloatToken();
				mpTextureCoords[i].y = model->GetFloatToken();
			}
			model->GetToken();	// }
		}
		else {
			//�ȊO�̃m�[�h�͓ǂݔ�΂�
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
��ʂɕ`�悷��
*/
void CMesh::Render() {

	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̔z���L���ɂ��� */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̔z���L���ɂ��� */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//16
	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̏ꏊ���w�肷�� */
	//glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	//glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);


	////16
	///* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̏ꏊ���w�肷�� */
	//glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	//glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	//19
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/* ���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷�� */
	for (int i = 0; i < mFaceNum; i++) {
		//�}�e���A����K�p����
		mMaterial[mpMaterialIndex[i]]->SetMaterial();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		//19
		//�}�e���A������������
		mMaterial[mpMaterialIndex[i]]->UnSetMaterial();
	}

	/* ���_�f�[�^�C�@���f�[�^�C�e�N�X�`�����W�̔z��𖳌��ɂ��� */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CMesh::Render(CModelX *model, CMatrix44 transformMatrix[], int transformMatrixSize) {
	//�V�F�[�_�[��L���ɂ���
	model->mShader.enable();
	/*
	���C�g�ݒ�
	*/
	CVector3 vec = CLight::getLight(0)->getDir();
	vec *= -1;
	int lightId = glGetUniformLocation(model->mShader.getProgram(), "LightVec");  //���C�g�̌�����ݒ�
	glUniform3fv(lightId, 1, (float*)&vec);
	glUniform3fv(glGetUniformLocation(model->mShader.getProgram(), "LightAmbientColor"), 1, (float*)&(CLight::getLight(0)->getAmbientColor()));
	glUniform3fv(glGetUniformLocation(model->mShader.getProgram(), "LightDiffuseColor"), 1, (float*)&(CLight::getLight(0)->getDiffuseColor()));
	//�X�L�����b�V���s��ݒ�
	int MatrixLocation = glGetUniformLocation(model->mShader.getProgram(), "Transforms");
	glUniformMatrix4fv(MatrixLocation, transformMatrixSize, GL_FALSE, transformMatrix[0].f);
	/*
	���[���h�g�����X�t�H�[��
	*/
	int worldId = glGetUniformLocation(model->mShader.getProgram(), "WorldMatrix");
	glUniformMatrix4fv(worldId, 1, GL_FALSE, model->mFrame[0]->mCombinedMatrix.f);

	//���_�o�b�t�@���o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBuffer);
	//���_���W�̈ʒu��ݒ�
	int idx = 0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�@���x�N�g���̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(CMyVertex), (void*)idx);
	//�e�N�X�`���}�b�s���O�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector3);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CMyVertex), (void*)idx);

	//�X�L���E�F�C�g�f�[�^�̈ʒu��ݒ�
	idx += sizeof(CVector2);
	int  weightLoc = glGetAttribLocation(model->mShader.getProgram(), "weights");
	glEnableVertexAttribArray(weightLoc);
	glVertexAttribPointer(weightLoc, 4, GL_FLOAT, GL_TRUE, sizeof(CMyVertex), (void*)idx);
	//�X�L���E�F�C�g�̃C���f�b�N�X�f�[�^�̈ʒu��ݒ�
	idx += sizeof(float)* 4;
	int  indexLoc = glGetAttribLocation(model->mShader.getProgram(), "indices");
	glEnableVertexAttribArray(indexLoc);
	glVertexAttribPointer(indexLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CMyVertex), (void*)idx);


	//�}�e���A�����ɒ��_��`�悵�܂�
	int k = 0;

	for (int i = 0; i < mMaterial.size(); i++) {
		mMaterial[i]->SetShader(&model->mShader);
		//�O�p�`�`��A�J�n���_�ԍ��A�`��Ɏg�p���钸�_��
		glDrawArrays(GL_TRIANGLES, k, mMaterialVertexCount[i]);	//DrawArrays:VertexIndex�Ȃ�
		k += mMaterialVertexCount[i];
		mMaterial[i]->UnSetMaterial();
	}

	//�����ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//���_�o�b�t�@�̃o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//�V�F�[�_�[�𖳌��ɂ���
	model->mShader.disable();
}

//16
/*
AnimateVertex
���_�ɃA�j���[�V������K�p
*/
void CMesh::AnimateVertex(CModelX *model) {
	//�A�j���[�V�����p�̒��_�G���A�N���A
	memset(mpAnimateVertex, 0, sizeof(CVector3)* mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)* mNormalNum);
	//�X�L���E�F�C�g���J��Ԃ�
	for (int i = 0; i < mSkinWeights.size(); i++) {
		//�t���[���ԍ��擾
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//�t���[�������s��ɃI�t�Z�b�g�s�������
		CMatrix44 mSkinningMatrix = model->mFrame[frameIndex]->mCombinedMatrix * mSkinWeights[i]->mOffset;
		//���_�����J��Ԃ�
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//���_�ԍ��擾
			int index = mSkinWeights[i]->mpIndex[j];
			//�d�ݎ擾
			float weight = mSkinWeights[i]->mpWeight[j];
			//���_�Ɩ@�����X�V����
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//�@���𐳋K������
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}

/*
���_�o�b�t�@���쐬����
*/
void CMesh::CreateVertexBuffer() {
	//���b�V�����Ɉ��쐬����΂悢
	if (mMyVertexBuffer > 0)
		return;

	if (mVertexNum > 0) {
		//���_�C���f�b�N�X���g�킸�A�S�Ă̖ʃf�[�^���쐬
		CMyVertex *pmyVertex, *vec;
		//���_���v�Z
		mMyVertexNum = mFaceNum * 3;
		//���_�������_�z��쐬
		pmyVertex = new CMyVertex[mMyVertexNum];
		vec = new CMyVertex[mVertexNum];
		for (int j = 0; j < mVertexNum; j++) {
			//���_���W�ݒ�
			vec[j].mPosition = mpVertex[j];
			//�e�N�X�`���}�b�s���O�ݒ�
			if (mpTextureCoords != NULL)
				vec[j].mTextureCoords = mpTextureCoords[j];
			vec[j].mBoneWeight[0] = 1.0f;
		}
		int wi = 0;
		//�X�L���E�F�C�g�ݒ�
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
		//�}�e���A���ԍ��̏����ɖʂ̒��_��ݒ�
		for (int i = 0; i < mMaterial.size(); i++) {
			int w = k;
			for (int j = 0; j < mMaterialIndexNum; j++) {
				if (mpMaterialIndex[j] == i) {
					//���_�z��ɐݒ肵�A�@����ݒ肷��
					pmyVertex[k] = vec[mpVertexIndex[j * 3]];
					pmyVertex[k++].mNormal = mpNormal[j * 3];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 1]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 1];

					pmyVertex[k] = vec[mpVertexIndex[j * 3 + 2]];
					pmyVertex[k++].mNormal = mpNormal[j * 3 + 2];

				}
			}
			//�}�e���A�����̒��_����ǉ�����
			mMaterialVertexCount.push_back(k - w);
		}

		//���_�o�b�t�@�̍쐬
		glGenBuffers(1, &mMyVertexBuffer);
		//���_�o�b�t�@���o�C���h
		glBindBuffer(GL_ARRAY_BUFFER, mMyVertexBuffer);
		//�o�C���h�����o�b�t�@�Ƀf�[�^��]��
		glBufferData(GL_ARRAY_BUFFER, sizeof(CMyVertex)*mMyVertexNum, pmyVertex, GL_STATIC_DRAW);
		//�o�C���h����
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//�z����
		delete[] pmyVertex;
		delete[] vec;
		pmyVertex = NULL;
	}
}



/*
Material�f�[�^�̓ǂݍ��݂Ɛݒ�
*/
CMaterial::CMaterial(CModelX *model)
: mpName(0)
, mpTextureFilename(0)
//18
, mTextureId(0)
{
	//17
	//CModelX�Ƀ}�e���A����ǉ�����
	model->mMaterial.push_back(this);

	model->GetToken(); // { ? Name
	if (strcmp(model->mToken, "{") != 0) {
		//{�łȂ��Ƃ��̓}�e���A����
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
		//�e�N�X�`������̏ꍇ�A�e�N�X�`���t�@�C�����擾
		model->GetToken(); // {
		model->GetToken(); // filename

		/*�e�N�X�`���̏ꏊ�w��Ȃ��ꍇ*/
		if (model->mTexDirectory.empty()) {
			mpTextureFilename = new char[strlen(model->mToken) + 1];
			strcpy(mpTextureFilename, model->mToken);
		}
		/*����ꍇ*/
		else {
			mpTextureFilename = new char[model->mTexDirectory.size() + strlen(model->mToken) + 1];
			strcpy(mpTextureFilename, model->mTexDirectory.c_str());
			strcat(mpTextureFilename, model->mToken);
		}


		//�e�N�X�`���t�@�C�����Ńe�N�X�`������������
		CTexture *p = model->FindTexture(mpTextureFilename);
		//�e�N�X�`�����݂鎞
		if (p) {
			//�e�N�X�`��ID���擾
			mTextureId = p->id;
		}
		else {
			//�����ꍇ�A�e�N�X�`���ǂݍ���
			p = new CTexture(mpTextureFilename);
			if (p->mpName) {
				//�e�N�X�`���z��ɒǉ�
				model->mTexture.push_back(p);
				//�e�N�X�`��ID���擾
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
�}�e���A����K�p����
*/
void CMaterial::SetMaterial() {
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//19
	//�e�N�X�`�����L��ꍇ
	if (mTextureId > 0) {
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		//�e�N�X�`���}�b�s���O�̃f�[�^��L���ɂ���
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

//Add Shader
/*
�}�e���A���̃f�[�^���V�F�[�_�[�ɐݒ肷��
*/
void CMaterial::SetShader(CShader *shader) {

	int AmbientId = glGetUniformLocation(shader->getProgram(), "Ambient");  //�J���[�ݒ�
	glUniform4fv(AmbientId, 1, (GLfloat*)mDiffuse);

	int DiffuseId = glGetUniformLocation(shader->getProgram(), "Diffuse");  //�J���[�ݒ�
	glUniform4fv(DiffuseId, 1, (GLfloat*)mDiffuse);

	int ColorRGAB_ID = glGetUniformLocation(shader->getProgram(), "ColorRGBA");  //�J���[�ݒ�@�d�˂ăJ���[�̕\��
	glUniform4fv(ColorRGAB_ID, 1, (GLfloat*)mColorRGBA);

	int PowId = glGetUniformLocation(shader->getProgram(), "Pow");  //������ݒ�
	glUniform1f(PowId, mPower);

	int SpecularId = glGetUniformLocation(shader->getProgram(), "Specular");  //�J���[�ݒ�
	glUniform3fv(SpecularId, 1, (GLfloat*)mSpecular);

	int EmissiveId = glGetUniformLocation(shader->getProgram(), "Emissive");  //�J���[�ݒ�
	glUniform3fv(EmissiveId, 1, (GLfloat*)mEmissive);
	GLint samplerId = glGetUniformLocation(shader->getProgram(), "Sampler");
	GLint textureFlg = glGetUniformLocation(shader->getProgram(), "TextureFlg");
	if (mTextureId > 0) {
		//�e�N�X�`������
		SetMaterial();
		glUniform1i(samplerId, 0);//GL_TEXTURE1��K�p
		glUniform1i(textureFlg, 0);//GL_TEXTURE1��K�p
	}
	else
	{
		//�e�N�X�`���Ȃ�
		glUniform1i(textureFlg, -1);//GL_TEXTURE1��K�p
	}
}

/*
UnSetMaterial
�e�N�X�`���}�b�s���O�𖳌��ɂ���
*/
void CMaterial::UnSetMaterial() {
	//�e�N�X�`�����L�鎞
	if (mTextureId > 0) {
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);
		//�e�N�X�`���}�b�s���O�̃f�[�^�𖳌��ɂ���
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
CSkinWeights
�X�L���E�F�C�g�̓ǂݍ���
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
	//�t���[�����G���A�m�ہA�ݒ�
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//���_�ԍ����擾
	mIndexNum = model->GetIntToken();
	//���_�ԍ�����0�𒴂���
	if (mIndexNum > 0) {
		//���_�ԍ��ƒ��_�E�F�C�g�̃G���A�m��
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//���_�ԍ��擾
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//���_�E�F�C�g�擾
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
#ifdef _DEBUG
	else {
		printf("SwinWeight indexNum : 0 Frame Name:%s\n", mpFrameName);
	}
#endif
	//�I�t�Z�b�g�s��擾
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
	//�A�j���[�V�����̖��O��ޔ�
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);

	model->GetToken(); // {

	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or Animation


		if (strchr(model->mToken, '}')) {
			model->GetToken(); // AnimationSet������ꍇ��΂�
			//break;
		}

		if (strcmp(model->mToken, "Animation") == 0) {
			//Animation�v�f�ǂݍ���
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//�I�����Ԑݒ�
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

	//�L�[�̔z���ۑ����Ă����z��
	CMatrix44 *key[4] = { 0, 0, 0, 0 };
	//���Ԃ̔z���ۑ����Ă����z��
	float *time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0') {
		model->GetToken(); // } or AnimationKey
		

		if (strchr(model->mToken, '}')) {
			break;
		}
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->GetToken(); // {
			//�f�[�^�̃^�C�v�擾
			int type = model->GetIntToken();
			//���Ԑ��擾
			mKeyNum = model->GetIntToken();
			switch (type) {
			case 0: // Rotation Quaternion
				//�s��̔z������Ԑ����m��
				key[type] = new CMatrix44[mKeyNum];
				//���Ԃ̔z������Ԑ����m��
				time[type] = new float[mKeyNum];
				//���Ԑ����J��Ԃ�
				for (int i = 0; i < mKeyNum; i++) {
					//���Ԏ擾
					time[type][i] = model->GetFloatToken();
					model->GetToken(); // 4��ǂݔ�΂�
					//w,x,y,z���擾
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//�N�H�[�^�j�I�������]�s��ɕϊ�
					key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1: //�g��E�k���̍s��쐬
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
			case 2: //�ړ��̍s��쐬
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
			case 4: //�s��f�[�^���擾
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
	//�s��f�[�^�ł͂Ȃ���
	if (mpKey == 0) {
		//���Ԑ����L�[���쐬
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//���Ԑݒ�
			mpKey[i].mTime = time[2][i]; // Time
			//�s��쐬 Position * Rotation * Size
			mpKey[i].mMatrix = key[2][i] * key[0][i] * key[1][i];
		}
	}
	//�m�ۂ����G���A���
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
/*�A�j���̃X�s�[�h*/
#define ANIMA_SPEED 60 * 4
/*
Init
����������
*/
void CModelXS::Init(CModelX *model) {
	mpModel = model;
	//�A�j���[�V�����p�����[�^������
	mAnimationIndex = 0;	//�ŏ��̃A�j���[�V�����ɂ��܂�
	mAnimationLoopFlg = true;	//�A�j���[�V�������J��Ԃ�
	mAnimationFrameSize = ANIMA_SPEED;	//�t���[���̃T�C�Y�w��
	mAnimationTime = 0.0f;	//�ŏ��̃R�}�ɂ��܂�
	mpModel->mAnimationSet[0]->mWeight = 1.0f;
	//�{�[�������s��̔z��쐬
	mpCombinedMatrix = new CMatrix44[model->mFrame.size()];
	//���b�V�����A�X�L�����b�V���s����쐬
	mpMeshSkinMatrix = new CMeshSkinMatrix[model->mMesh.size()];
	//���b�V�����̃X�L�����b�V���s��̔z����쐬
	for (int i = 0; i < model->mMesh.size(); i++) {
		mpMeshSkinMatrix[i].mSize = model->mMesh[i]->mSkinWeights.size() + 1;
		mpMeshSkinMatrix[i].mpSkinnedMatrix = new CMatrix44[mpMeshSkinMatrix[i].mSize];
	}
}

/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:true �J��Ԃ�
framesize�F�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CModelXS::ChangeAnimation(int index, bool loop, float framesize) {
	mAnimaFlag = true;
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index){
		return;
	}
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index;
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̎��Ԃ��ŏ��ɂ���
	mAnimationTime = 0.0f;
}

/*
Update
�X�V����
matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CModelXS::Update(CMatrix44 &matrix) {
	////���݂̃A�j���[�V�����ƈقȂ�Ƃ�
	//if (mpModel->mAnimationIndex != mAnimationIndex) {
	//	mpModel->mAnimationSet[mpModel->mAnimationIndex]->mWeight = 0.0f;
	//	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
	//	mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationTime;
	//	mpModel->mAnimationIndex = mAnimationIndex;
	//}
	/*�A�j���[�V�����̃t���O�������Ă��Ȃ��Ƃ��͂��Ȃ�*/
	if (mAnimaFlag) {
		//�Ō�܂ōĐ����Ă��Ȃ�
		if (mAnimationTime <= mpModel->mAnimationSet[mAnimationIndex]->mMaxTime) {
			//���Ԃ�i�߂�
			mAnimationTime += mpModel->mAnimationSet[mAnimationIndex]->mMaxTime
				/ mAnimationFrameSize;
		}
		else {
			//�J��Ԃ��̏ꍇ�́A���Ԃ�0�ɖ߂�
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
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->Animate(&matrix);
	//�t���[���̍����s���ޔ�����

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
	mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//���b�V�����̃X�L�����b�V���s��z���ݒ肷��
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
	for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
	//�X�L�����b�V���̍s��z���ޔ�����
	mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
	= mpCombinedMatrix[ mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex] * mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
	}
	}
	*/
}

void CModelXS::UpdateSkinMatrix(CMatrix44 &matrix) {
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->Animate(&matrix);
	//�t���[���̍����s���ޔ�����

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//���b�V�����̃X�L�����b�V���s��z���ݒ肷��
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
		for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
			//�X�L�����b�V���̍s��z���ޔ�����
			mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
				= mpCombinedMatrix[mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex] * mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
		}
	}
}

/*MATRIX�̃A�b�v�f�[�g*/
void CModelXS::MatrixUpdate(CMatrix44 &matrix){
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->Animate(&matrix);
	//�t���[���̍����s���ޔ�����

	for (int i = 0; i < mpModel->mFrame.size(); i++) {
		mpCombinedMatrix[i] = mpModel->mFrame[i]->mCombinedMatrix;
	}
	//���b�V�����̃X�L�����b�V���s��z���ݒ肷��
	for (int i = 0; i < mpModel->mMesh.size(); i++) {
		for (int j = 0; j < mpModel->mMesh[i]->mSkinWeights.size(); j++) {
			//�X�L�����b�V���̍s��z���ޔ�����
			mpMeshSkinMatrix[i].mpSkinnedMatrix[j + 1]
				= mpCombinedMatrix[mpModel->mMesh[i]->mSkinWeights[j]->mFrameIndex]
				* mpModel->mMesh[i]->mSkinWeights[j]->mOffset;
		}
	}
}
/*
�`�悷��
*/
void CModelXS::Render() {
	/*�`�悷��*/
	if (mRenderFlag) {
		//���b�V�����ɕ`�悷��
		for (int i = 0; i < mpModel->mMesh.size(); i++) {
			//���f���A�X�L�����b�V���s��z��A�X�L�����b�V���s��z��v�f��
			mpModel->mMesh[i]->Render(mpModel, mpMeshSkinMatrix[i].mpSkinnedMatrix, mpMeshSkinMatrix[i].mSize);
		}
	}
}

