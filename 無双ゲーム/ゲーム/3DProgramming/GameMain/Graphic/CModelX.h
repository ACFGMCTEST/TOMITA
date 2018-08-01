#ifndef CMODELX_H	//�C���N���[�h�K�[�h
#define CMODELX_H

#include "glew.h"
#include "glut.h"
#include <string>

#define MODEL_FILE "sample.blend.x"	//���̓t�@�C����
//#define MODEL_FILE "���O�i.x"	//���̓t�@�C����
//#define MODEL_FILE "x\\00_Mesh1P.x"	//���̓t�@�C����

//�̈������}�N����
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = 0;}
#define SAFE_DELETE(a) { if(a) delete a; a = 0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <vector>	//vector�N���X�̃C���N���[�h�i���I�z��j
//#include "CMatrix44.h"	//�}�g���N�X�N���X�̃C���N���[�h
//#include "CTexture.h"	//�e�N�X�`���̃C���N���[�h
//#include "CVector2.h"
//#include "CShader.h"

#include "../Matrix/CMatrix44.h"
#include "../Graphic/CTexture.h"
#include "../Vector/CVector2.h"
#include "CShader.h"

class CMyVertex {
public:
	CVector3 mPosition;
	CVector3 mNormal;
	CVector2 mTextureCoords;
	float mBoneWeight[4];
	float mBoneIndex[4];

	CMyVertex() {
		for (int i = 0; i < 4; i++) {
			mBoneIndex[i] = 0;
			mBoneWeight[i] = 0.0f;
		}
		mBoneWeight[0] = 1.0f;
	}
};

class CModelX;	// CModelX�N���X�̐錾

/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey {
public:
	//����
	float mTime;
	//�s��
	CMatrix44 mMatrix;
};

/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation {
public:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�

	int mKeyNum;	//�L�[���i���Ԑ��j
	CAnimationKey *mpKey;	//�L�[�̔z��

	CAnimation(CModelX *model);

	~CAnimation() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
public:
	//�A�j���[�V������
	char *mpName;
	//�A�j���[�V����
	std::vector<CAnimation*> mAnimation;

	//14S
	float mTime;	//���ݎ���
	float mWeight;	//�d��
	float mMaxTime;	//�ő厞��
	//14E

	CAnimationSet(CModelX *model);

	~CAnimationSet() {
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (int i = 0; i < mAnimation.size(); i++) {
			delete mAnimation[i];
		}
	}
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
public:
	char *mpFrameName;	//�t���[����
	int mFrameIndex;	//�t���[���ԍ�
	int mIndexNum;	//���_�ԍ���
	int *mpIndex;	//���_�ԍ��z��
	float *mpWeight;	//���_�E�F�C�g�z��
	CMatrix44 mOffset;	//�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX *model);

	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};
/*
CMaterial
�}�e���A���N���X
*/
class CMaterial {
public:
	char *mpName;	//�}�e���A����
	float mDiffuse[4];
	float mColorRGBA[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`���t�@�C����
	char *mpTextureFilename;
	//18
	//�e�N�X�`��ID
	GLuint mTextureId;

	CMaterial(CModelX *model);

	~CMaterial() {
		SAFE_DELETE_ARRAY(mpName);
		SAFE_DELETE_ARRAY(mpTextureFilename);
	}
	//�}�e���A����K�p����
	void SetMaterial();
	//18
	//�}�e���A���𖳌��ɂ���
	void UnSetMaterial();

	//Add Shader
	void SetShader(CShader *shader);
};

//CMesh�N���X�̒�`
class CMesh {
public:
	int mVertexNum;		//���_��
	CVector3 *mpVertex;	//���_�f�[�^
	int mFaceNum;		//�ʐ�
	int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
	int mNormalNum;		//�@����
	CVector3 *mpNormal;	//�@���f�[�^
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ����i�ʐ��j
	int *mpMaterialIndex;	//�}�e���A���ԍ�

	//�}�e���A���f�[�^
	std::vector<CMaterial*> mMaterial;
	std::vector<int> mMaterialVertexCount;
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*> mSkinWeights;
	//16
	CVector3 *mpAnimateVertex;	//�A�j���[�V�����p���_
	CVector3 *mpAnimateNormal;	//�A�j���[�V�����p�@��
	//19
	//�e�N�X�`�����W�f�[�^
	CVector2 *mpTextureCoords;
	//Add Shader
	GLuint	  mMyVertexBuffer;
	int       mMyVertexNum;
	//	CMatrix44 mTransformMatrix[155];

	float mRed, mGreen, mBlue, mAlpha; //rgba�F���

	//�R���X�g���N�^
	CMesh()
		: mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		//16
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		//19
		, mpTextureCoords(0)
		, mMyVertexNum(0)
		, mMyVertexBuffer(0)
		, mRed(0.0f), mGreen(0.0f), mBlue(0.0f), mAlpha(0.0f)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//16
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		//19
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++) {
			delete mSkinWeights[i];
		}
		glDeleteBuffers(1, &mMyVertexBuffer);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX *model);
	//�`��
	void Render();
	void Render(CModelX *model, CMatrix44 transformMatrix[], int transformMatrixSize);
	//16
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX *model);
	void CreateVertexBuffer();
};


//CModelXFrame�N���X�̒�`
class CModelXFrame {
public:
	std::vector<CModelXFrame*> mChild;	//�q�t���[���̔z��
	CMatrix44 mTransformMatrix;	//�ϊ��s��
	CMatrix44 mCombinedMatrix;	//�����s��
	char* mpName;	//�t���[�����O
	int mIndex;		//�t���[���ԍ�

	CMesh mMesh;	//Mesh�f�[�^

	//�R���X�g���N�^
	CModelXFrame()
		: mpName(0)
		, mIndex(0) {}

	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame() {
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete *itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	//�`��
	void Render();
	//�A�j���[�V�����Ȃ��o�[�W����
	void NoaAnimaRender();

	//�����s��̍쐬
	void Animate(CMatrix44* parent);
};

/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
public:
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̗̈�
	std::string mTexDirectory;//�ǂݍ��݃t�@�C���ꏊ
	bool mAnimaFlag;//�t���O�A�j���[�V����
	/*�F�Z�b�g*/
	void SetColor(float r, float g, float b, float a);
	/*�F�����邩���f*/
	bool ColorFlag();
	/*�F�̃t�F�[�h�_��*/
	void Flashing(){};

	std::vector<CModelXFrame*> mFrame;	//�t���[���̔z��
	std::vector<CAnimationSet*> mAnimationSet;	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<std::string> mAnimaName;//�A�j���[�V�����̖��O
	//24
	int mAnimationIndex;	//���݂̃A�j���[�V�����ԍ�

	//17
	std::vector<CMaterial*> mMaterial;	//�}�e���A���̔z��
	//18
	std::vector<CTexture*> mTexture;	//�e�N�X�`���̔z��

	CShader mShader;

	std::vector<CMesh*> mMesh;	//Mesh�z��

	CModelX()
		: mpPointer(0), mAnimationIndex(0), mAnimaFlag(false),mTexDirectory("")
	{}
	~CModelX() {
		if (mFrame.size() > 0)
			delete mFrame[0];
		for (int i = 0; i < mAnimationSet.size(); i++) {
			delete mAnimationSet[i];
		}
		//17
		//�}�e���A���̉��
		for (int i = 0; i < mMaterial.size(); i++) {
			delete mMaterial[i];
		}
		//18
		//�e�N�X�`���̉��
		for (int i = 0; i < mTexture.size(); i++) {
			delete mTexture[i];
		}
	}
	//�t�@�C���ꏊ�w��
	void TexDirectory(char *fileName) {mTexDirectory = fileName;}
	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�t�@�C���ǂݍ���
	void NoAnimaLoad(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�����f�[�^�̎擾
	int GetIntToken();
	//�`��
	void Render();
	CModelXFrame* FindFrame(char* name);

	//�t���[���̕ϊ��s��X�V
	void AnimateFrame();
	//16
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();
	//17
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);
	//18
	//�e�N�X�`���̌���
	CTexture* FindTexture(char* name);
	//20
	//�A�j���[�V�����Z�b�g�̒ǉ�
	void AddAnimationSet(char* filename);

	void CreateVertexBuffer();

};
/*
���b�V������
�X�L�����b�V���s��z��̃N���X
*/
class CMeshSkinMatrix {
public:
	CMatrix44 *mpSkinnedMatrix;	//�s��̔z��
	int mSize;	//�s��̗v�f��
	CMeshSkinMatrix()
		: mpSkinnedMatrix(0)
		, mSize(0)
	{}
	~CMeshSkinMatrix() {
		SAFE_DELETE_ARRAY(mpSkinnedMatrix);
	}
};
#include "../Task/CTask.h"

/*
�X�L�����b�V���p
�A�j���[�V��������N���X
*/
class CModelXS : public CTask{
public:
	CModelX *mpModel;	//X���f���f�[�^�ւ̃|�C���^
	CMatrix44 *mpCombinedMatrix;	//�{�[���̍����s��
	CMeshSkinMatrix *mpMeshSkinMatrix;	//���b�V�����̃X�L�����b�V���s��

	bool mAnimaFlag;//�A�j���[�V���������邩���f
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�J��Ԃ�
	bool mRenderFlag;//�`��̃t���O
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
	float mAnimationTime;	//���݂̃A�j���[�V��������

	CModelXS()
		: mpModel(0)
		, mpCombinedMatrix(0)
		, mpMeshSkinMatrix(0)
		, mRenderFlag(true)
		, mAnimaFlag(false)
	{}

	~CModelXS() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
		SAFE_DELETE_ARRAY(mpMeshSkinMatrix);
	}

	//����������
	void Init(CModelX *model);
	//�A�j���[�V�����̕ύX
	//void ChangeAnimation(int index, bool loop, float framesize);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(char *fileName, bool loop, float framesize);
	//�g���܂킵�悤�A�j���[�V�����̕ύX
	void ChangeAnimation(char *fileName, char *fileSecondName, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix44 &m);
	void UpdateSkinMatrix(CMatrix44 &matrix);

	//MATRIX�̂ݍX�V
	void MatrixUpdate(CMatrix44 &m);

	//�`�揈��
	void Render();

	

};

#endif
