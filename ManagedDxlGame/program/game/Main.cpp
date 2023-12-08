#include "Main.h"
#include "DxLib.h"
#include "Play/ScenePlaySong.h"
#include "../game/Manager/SceneManager.h"
#include "../game/Title/SceneTitle.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "SelectSong/SceneSelectSongMenu.h"
#include "Result/SceneResult.h"
#include "Manager/SoundManager.h"


SelectSongMenu* _selectSongMenu = nullptr;

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s
void gameStart() {
	srand(100);


	SetDrawScreen(DX_SCREEN_BACK);	
	// �E�B���h�E�T�C�Y�ύX�\�ɂ���֐�
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	ChangeWindowMode(true);
	// �E�B���h�E���ݒ�
	SetWindowText("Play Song");


	// �t�H���g�ǉ�
	tnl::AddFontTTF("851Gkktt_005.ttf");
	SetFontSize(30);

	// ���^�Ȃ̑S�W�����������ɃJ�E���g
	_selectSongMenu = new SelectSongMenu();
	_selectSongMenu->SongGenreTotalCount();

	// �T�E���h���[�h
	SoundManager::GetInstance()->LoadPlayListSongs();
	SoundManager::GetInstance()->LoadBGM();
	SoundManager::GetInstance()->LoadSE();

	// �^�C�g���V�[���Z�b�g
	SceneManager::GetInstance(new Title());
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s
void gameMain(float deltaTime) {

	// �t�H���g�ύX
	ChangeFont("851�S�`�J�N�b�g", DX_CHARSET_DEFAULT);	

	SetMultiThreadFlag(TRUE);

	// �V�[���J��   �e�V�[���̃C���X�^���X���Ǘ��E����
	SceneManager::GetInstance()->Update(deltaTime); 
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s
void gameEnd() {

	delete _selectSongMenu;
	_selectSongMenu = nullptr;

	SoundManager::GetInstance()->Destroy();
	SceneManager::GetInstance()->Destroy();
}