#pragma once


constexpr static int PLAYLIST_NUM = 4; //現在のプレイリスト数

// 曲ハンドル--------------
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

	void LoadPlayListSongs();  // プレイリスト一覧ロード
	void Destroy();            // プレイリスト hdl 解放

	void LoadSE();	           // SEロード
	void LoadBGM();            // BGMロード

private:

	SoundManager(){}
};