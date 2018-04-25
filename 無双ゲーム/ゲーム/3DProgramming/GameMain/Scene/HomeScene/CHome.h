#ifndef HOME_HPP
#define HOME_HPP
#include "../TitleScene/CTitle.h"
#include "../GameMain\Graphic\CRectangle2.h"
#include "../GameMain\Scene\CScene.h"


/*�z�[����ʂ̃N���X*/
class CHome :public CTitle{
private:
	/*�|���S��*/
	CRectangle2 mSelectButton;
	CRectangle2 mModelChangeButton;
	CRectangle2 mSelectCursor;
	/*�e�N�X�`��*/
	CTexture	mTexSelectButton;
	CTexture	mTexModelChangeButton;
	CTexture	mTexStageCursor;

	/*�V�[�����f�p*/
	bool mFlagScene;

	/*�I���������̊֐�*/
	void Select();
	/*���肳�ꂽ�ꍇ*/
	void SelectDecision();


	
public:

	/*�V�[���J�� ���f �}�l�[�W���[�ŌĂяo��*/
	bool SceneFlag();
	eSceneNo eScene;//�V�[���ȍ~�ϐ�

	CHome();
	~CHome();
	void Update();
	void Render();

};
#endif
