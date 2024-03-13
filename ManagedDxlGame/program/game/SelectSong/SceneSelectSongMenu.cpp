#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/SceneManager.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlaySong.h"


namespace {

	const int _LEVEL_NUM = 4; // 難易度の数
	const int _PLAYLIST_X_POS = 895;
	const int _PLAYLIST_Y_POS = 70;
	const int _LEVELLIST_X_POS = 310;
	const int _LEVELLIST_Y_POS = 580;

	const int _LEVELSHAPES_X_POS = 335;  // 難易度文字列を囲う図形

	// プレイシーンに飛ぶ前に表示する、選択した曲名の X軸
	const int _SELECTED_SONG_TEXT_POS_X = 355;
	const int _SELECTED_SONG_TEXT_POS_Y = 120;

	const int _SELECTED_LEVEL_TEXT_POS_X = 580;
	const int _SELECTED_LEVEL_TEXT_POS_Y = 250;

	const int _START_TEXT_POS_X = 445;
	const int _BACK_TEXT_POS_X = 785;
	const int _STARTBACK_TEXT_POS_Y = 450;

	const int _BIGSIZE_TITLE_POS_X = 330;
	const int _BIGSIZE_TITLE_POS_Y = 380;

	// 曲タイトル初期位置オフセット
	const int _SONGTITLE_POS_X = 1050;

	// 選択中文字列座標移動
	const int _NOWSELECTINGSONG_POS_X = _SONGTITLE_POS_X - 15;

	// 難易度未選択状態の色
	const int _DEFAULT_SONG_COLOR = GetColor(255, 255, 255);

	// 選択中難易度の枠の色
	const int _NOWSELECTINGSONG_COLOR = GetColor(255, 0, 0);

	const int _FINALCHECK_DIMSCREEN_ALPHA = 50;
}


const char* SelectSongMenu::_SONG_TITLE[PLAYLIST_NUM] =
{
	"交響曲第9番",
	"BadApple!!",
	"裏表ラバーズ" ,
	"残酷な天使のテーゼ"
};

const char* SelectSongMenu::_SONG_GENRE[PLAYLIST_NUM] =
{
	"クラシック",
	"東方Vocal",
	"ボーカロイド",
	"アニソン"
};

const char* SelectSongMenu::_SONG_GENRE_ALL_LIST[GENRE_NUM] =
{
	"クラシック",
	"J-POP",
	"アニソン",
	"東方Vocal",
	"ボーカロイド",
	"ロック",
	"ゲームミュージック"
};

const char* SelectSongMenu::_SONG_LEVELS[4] =
{
	"EASY",
	"BASIC",
	"HARD",
	"ABYSS"
};


// 入力----------------------------------------------------------------------------------------------------
void SelectSongMenu::SelectingSongByInput() {

	if (_songSelect) {

		// 上キー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
		{
			StopSoundMem(songList[_songIndex]);
			// 再生位置を初期位置に戻す
			SetCurrentPositionSoundMem(0, songList[_songIndex]);

			_songIndex--;

			if (_songIndex < 0) 
				_songIndex = PLAYLIST_NUM - 1;
		}
		// 下キー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
		{
			StopSoundMem(songList[_songIndex]);
			// 再生位置を初期位置に戻す
			SetCurrentPositionSoundMem(0, songList[_songIndex]);

			_songIndex++;

			if (_songIndex >= PLAYLIST_NUM) 
				_songIndex = 0;
		}
	}
}


void SelectSongMenu::PickOneSongByInput() {

	// 選択中の曲ループ再生
	PlaySoundMem(songList[_songIndex], DX_PLAYTYPE_LOOP, false);

	bool _soundPlayed = false;

	// 決定キーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1))
	{
		// 曲選択中なら難易度選択に移行する
		if (_songSelect) {
			_levelSelect = true;
			_songSelect = false;
		}
		// 難易度選択中なら最終確認文字列を表示
		else if (_levelSelect)
		{
			_showFinalCheck_beforeStartPlaySong = true;
			_levelSelect = false;
		}
		// 最終確認中ならプレイシーンに遷移
		else if (_showFinalCheck_beforeStartPlaySong)
		{
			if (!_soundPlayed) {
				PlaySoundMem(titleToSelectMenu_hdl, DX_PLAYTYPE_BACK, TRUE);
				_soundPlayed = true;
			}

			_moveToPlayScene = true;

			MoveToScenePlaySong();
		}
	}

	if (_moveToPlayScene)
		_soundPlayed = false;
}



void SelectSongMenu::BackToPreviousByInput() {

	// キャンセルキーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0))
	{
		// 難易度選択中なら曲選択に戻る
		if (_levelSelect) {

			_levelIndex = 0;
			_levelSelect = false;
			_songSelect = true;
		}
		else if (_showFinalCheck_beforeStartPlaySong) {

			// 最終確認画面を表示中なら難易度選択に戻る
			_showFinalCheck_beforeStartPlaySong = false;
			_levelSelect = true;
		}
	}
}



void SelectSongMenu::SelectingLevelByInput() {

	if (_levelSelect) {

		// 難易度選択中なら難易度のインデックスを減らす
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT))
		{
			_levelIndex--;
			if (_levelIndex < 0)
				_levelIndex = _LEVEL_NUM - 1;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT))
		{
			_levelIndex++;
			if (_levelIndex >= _LEVEL_NUM)
				_levelIndex = 0;
		}
	}
}

// ----------------------------------------------------------------------------------------------------
void SelectSongMenu::SetDimScreenAtFinalCheck() {

	if (_showFinalCheck_beforeStartPlaySong) {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _FINALCHECK_DIMSCREEN_ALPHA);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		SetFontSize(100);
		DrawStringEx(_SELECTED_SONG_TEXT_POS_X, _SELECTED_SONG_TEXT_POS_Y, -1,
			_SONG_TITLE[_songIndex]);   // 選択した曲名

		SetFontSize(50);

		DrawStringEx(_SELECTED_LEVEL_TEXT_POS_X, _SELECTED_LEVEL_TEXT_POS_Y, -1,
			_SONG_LEVELS[_levelIndex]); // 選択した難易度

		DrawStringEx(_START_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Start");
		DrawStringEx(_BACK_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Back");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _FINALCHECK_DIMSCREEN_ALPHA);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// 現在収録済みの曲のジャンルごとの総数
int numOfTotalSongs_eachGenre[GENRE_NUM];

void SelectSongMenu::SongGenreTotalCount() {

	// 追加済みプレイリスト
	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// 全曲ジャンル
		for (int j = 0; j < GENRE_NUM; j++)
		{
			// ジャンル名が一致したらカウントを増やす
			if (strcmp(_SONG_GENRE[i], _SONG_GENRE_ALL_LIST[j]) == 0)
			{
				numOfTotalSongs_eachGenre[j]++;
				break; // 一致したらループを抜ける
			}
		}
	}
}

// 描画----------------------------------------------------------------------------------------------------
void SelectSongMenu::RenderTotalSongGenreList() {

	// ジャンルと曲数を表示  左側縦方向
	for (int i = 0; i < GENRE_NUM; i++)
	{
		// 選択中の曲のジャンルなら色を変える
		if (strcmp(_SONG_GENRE[_songIndex], _SONG_GENRE_ALL_LIST[i]) == 0)
		{
			SetDrawBright(0, 255, 0); // 色を緑にする
		}

		// ジャンルと曲数を表示する
		DrawFormatString(50, 20 + i * 33, -1, "%s：%d", _SONG_GENRE_ALL_LIST[i], numOfTotalSongs_eachGenre[i]);
		SetDrawBright(255, 255, 255); // 色を白に戻す
	}
}


void SelectSongMenu::RenderAndChangeColor_SongTitle() {

	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// 選択中の曲なら色を変える
		if (_songSelect && i == _songIndex)
		{
			SetDrawBright(255, 255, 0);   // 色を黄色にする
		}
		else {
			SetDrawBright(255, 255, 255); // 色を白に戻す
		}

		// 曲名を表示する
		DrawString(_PLAYLIST_X_POS, _PLAYLIST_Y_POS * (i + 1), _SONG_TITLE[i], -1);
	}
}


void SelectSongMenu::RenderAndChangeColor_SongLevel() {

	for (int i = 0; i < _LEVEL_NUM; i++)
	{
		// 選択中の難易度なら色を変える				
		if (_levelSelect && i == _levelIndex)
		{
			SetDrawBright(255, 255, 0);   // 色を黄色にする
		}
		else {
			SetDrawBright(255, 255, 255); // 色を白に戻す
		}

		// 難易度を表示する
		DrawOvalAA(
			static_cast<float>(_LEVELSHAPES_X_POS + ((i + 1) * 100)),
			_LEVELLIST_Y_POS,
			50, 50, 8, -1,
			false,
			1
		);

		SetFontSize(15);
		DrawString(
			_LEVELLIST_X_POS + ((i + 1) * 100),
			_LEVELLIST_Y_POS,
			_SONG_LEVELS[i],
			-1
		);
	}
}


void SelectSongMenu::RenderBigSizeTitle_AtCenter() {

	SetDrawBright(255, 255, 255);
	SetFontSize(80);	          //難易度上に選択中の曲のタイトル（大）
	DrawFormatString(_BIGSIZE_TITLE_POS_X, _BIGSIZE_TITLE_POS_Y, -1, _SONG_TITLE[_songIndex]);

	SetFontSize(40);
	DrawStringEx(1070, 640, -1, "Enter");
	DrawStringEx(10, DXE_WINDOW_HEIGHT - 45, -1, "music select...");
}


void SelectSongMenu::Render() {

	// プレイシーンにまだ飛んでいなければ描画
	if (_moveToPlayScene) return;

	SetDimScreenAtFinalCheck();       // 明るさ調整

	RenderTotalSongGenreList();

	RenderAndChangeColor_SongTitle();

	RenderAndChangeColor_SongLevel();

	RenderBigSizeTitle_AtCenter();
}


// 更新----------------------------------------------------------------------------------------------------
void SelectSongMenu::MoveToScenePlaySong()
{
	auto mgr = SceneManager::GetInstance();
	mgr->SceneChange(new PlaySong(
		_SONG_TITLE[_songIndex],     //選択曲
		_SONG_LEVELS[_levelIndex],  //選択難易度、
		_songIndex, _levelIndex)); // 選んだ曲の番号 を PlaySongシーンに渡す
}


void SelectSongMenu::Update(float deltaTime) {

	SelectingSongByInput();

	PickOneSongByInput();

	BackToPreviousByInput();

	SelectingLevelByInput();

	if (_moveToPlayScene) {

		StopSoundMem(songList[_songIndex]);
		SetCurrentPositionSoundMem(0, songList[_songIndex]);
		_songSelect = true;  // また曲選択に戻ってきたときに曲選択から始められるように
	}
}