#pragma once


constexpr static int PLAYLIST_NUM = 4; //���݂̃v���C���X�g��

// �ȃn���h��--------------
extern int songList[];
extern int coverAlbum_hdl[];
// SE ---------------------
extern int titleToSelectMenu_hdl;
extern int tap_hdl;
// BMG ---------------------
extern int title_BGM_hdl;
extern int pause_BGM_hdl;
extern int result_BGM_hdl;


class SoundManager
{
public:

	static SoundManager* GetInstance() {

		static SoundManager* instance;

		return instance;
	}

	void LoadPlayListSongs();  // �v���C���X�g�ꗗ���[�h
	void Destroy();            // �v���C���X�g hdl ���

	void LoadSE();	           // SE���[�h
	void LoadBGM();            // BGM���[�h

private:

	SoundManager(){}
};