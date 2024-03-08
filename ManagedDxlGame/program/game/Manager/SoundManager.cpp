#include "SoundManager.h"


// ���݂̎��^�Ȑ�
int songList[PLAYLIST_NUM];

int titleToSelectMenu_hdl = 0;
int title_BGM_hdl = 0;
int pause_BGM_hdl = 0;
int result_BGM_hdl = 0;
int tap_hdl = 0;


//  �� songList[] ��ScenePlaySong�� coverAlbum_hdl�z��Ə��Ԃ����킹�Ă�������
void SoundManager::LoadPlayListSongs() {

	// �y��
	songList[0] = LoadSoundMem("sound/playList/�����ȑ�9��.mp3");
	songList[1] = LoadSoundMem("sound/playList/BadApple!!.mp3");
	songList[2] = LoadSoundMem("sound/playList/���\���o�[�Y.mp3");
	songList[3] = LoadSoundMem("sound/playList/�c���ȓV�g�̃e�[�[(Instrumental).mp3");
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