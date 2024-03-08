#include "SoundManager.h"


// 現在の収録曲数
int songList[PLAYLIST_NUM];

int titleToSelectMenu_hdl = 0;
int title_BGM_hdl = 0;
int pause_BGM_hdl = 0;
int result_BGM_hdl = 0;
int tap_hdl = 0;


//  ※ songList[] はScenePlaySongの coverAlbum_hdl配列と順番を合わせてください
void SoundManager::LoadPlayListSongs() {

	// 楽曲
	songList[0] = LoadSoundMem("sound/playList/交響曲第9番.mp3");
	songList[1] = LoadSoundMem("sound/playList/BadApple!!.mp3");
	songList[2] = LoadSoundMem("sound/playList/裏表ラバーズ.mp3");
	songList[3] = LoadSoundMem("sound/playList/残酷な天使のテーゼ(Instrumental).mp3");
}


void SoundManager::LoadSE() {

	// SE
	titleToSelectMenu_hdl = LoadSoundMem("sound/SE/enter.mp3");
	tap_hdl = LoadSoundMem("sound/SE/tap.mp3");
}


void SoundManager::LoadBGM() {

	// BGM
	title_BGM_hdl = LoadSoundMem("sound/playList/Title_BGM.mp3");
	pause_BGM_hdl = LoadSoundMem("sound/playList/Pause_BGM.mp3");
	result_BGM_hdl = LoadSoundMem("sound/playList/Result_BGM.wav");
}


void SoundManager::Destroy() {

	DeleteSoundMem(songList[0]);
	DeleteSoundMem(songList[1]);
	DeleteSoundMem(songList[2]);
	DeleteSoundMem(songList[3]);
}