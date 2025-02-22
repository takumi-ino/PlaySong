#include "Main.h"
#include "../game/Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "../game/Title/SceneTitle.h"
#include "SelectSong/SceneSelectSongMenu.h"


SelectSongMenu* _selectSongMenu = nullptr;

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行
void gameStart() {
	srand(100);

	SetDrawScreen(DX_SCREEN_BACK);	
	// ウィンドウサイズ変更可能にする関数
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	ChangeWindowMode(true);
	// ウィンドウ名設定
	SetWindowText("Play Song");

	// フォント追加
	tnl::AddFontTTF("851Gkktt_005.ttf");
	SetFontSize(30);

	// 収録曲の全ジャンル数を先にカウント
	_selectSongMenu = new SelectSongMenu();
	_selectSongMenu->SongGenreTotalCount();

	// サウンドロード
	SoundManager::GetInstance()->LoadPlayListSongs();
	SoundManager::GetInstance()->LoadBGM();
	SoundManager::GetInstance()->LoadSE();

	// タイトルシーンセット
	SceneManager::GetInstance(new Title());
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行
void gameMain(float deltaTime) {

	// フォント変更
	ChangeFont("851ゴチカクット", DX_CHARSET_DEFAULT);	

	SetMultiThreadFlag(TRUE);

	// シーン遷移   各シーンのインスタンスを管理・制御
	SceneManager::GetInstance()->Update(deltaTime); 

	//SetFontSize(30);
    //DrawStringEx(10, 690, -1, "%f.2", GetFPS());
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行
void gameEnd() {

	delete _selectSongMenu;
	_selectSongMenu = nullptr;

	SceneManager::GetInstance()->Destroy();
}