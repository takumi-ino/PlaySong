#include "DxLib.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/SceneManager.h"
#include "../Title/SceneTitle.h"
#include "../Main.h"
#include "../SelectSong/SceneSelectSongMenu.h"
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
	const int _defaultSongXPos = 1050;

	// 選択中文字列座標移動
	const int nowSelectedSong_offsetX = _defaultSongXPos - 15;

	// 難易度未選択状態の色
	const int defaultSong_color = GetColor(255, 255, 255);

	// 選択中難易度の枠の色
	const int nowSelectedSong_color = GetColor(255, 0, 0);
}


int genreCount[GENRE_NUM];

const char* SelectSongMenu::_songTitle[PLAYLIST_NUM] =
{
	"交響曲第9番",
	"BadApple!!",
	"裏表ラバーズ" ,
	"残酷な天使のテーゼ"
};

const char* SelectSongMenu::_songGenre[PLAYLIST_NUM] =
{
	"クラシック",
	"東方Vocal",
	"ボーカロイド",
	"アニソン"
};

const char* SelectSongMenu::_songGenreRefAll[GENRE_NUM] =
{
	"クラシック",
	"J-POP",
	"アニソン",
	"東方Vocal",
	"ボーカロイド",
	"ロック",
	"ゲームミュージック"
};

const char* SelectSongMenu::_songLevels[4] =
{
	"EASY",
	"BASIC",
	"HARD",
	"ABYSS"
};


// 入力----------------------------------------------------------------------------------------------------
void SelectSongMenu::SelectingSongByInput() {

	if (songSelect) {

		// 上キー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
		{
			StopSoundMem(songList[songIndex]);
			// 再生位置を初期位置に戻す
			SetCurrentPositionSoundMem(0, songList[songIndex]);

			songIndex--;

			if (songIndex < 0) 
				songIndex = PLAYLIST_NUM - 1;
		}
		// 下キー
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
		{
			StopSoundMem(songList[songIndex]);
			// 再生位置を初期位置に戻す
			SetCurrentPositionSoundMem(0, songList[songIndex]);

			songIndex++;

			if (songIndex >= PLAYLIST_NUM) 
				songIndex = 0;
		}
	}
}


void SelectSongMenu::PickOneSongByInput() {

	// 選択中の曲ループ再生
	PlaySoundMem(songList[songIndex], DX_PLAYTYPE_LOOP, false);

	bool soundPlayed = false;

	// 決定キーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1))
	{
		// 曲選択中なら難易度選択に移行する
		if (songSelect) {
			levelSelect = true;
			songSelect = false;
		}
		// 難易度選択中なら最終確認文字列を表示
		else if (levelSelect)
		{
			show_finalCheck_before_startPlaySong = true;
			levelSelect = false;
		}
		// 最終確認中ならプレイシーンに遷移
		else if (show_finalCheck_before_startPlaySong)
		{
			if (!soundPlayed) {
				PlaySoundMem(titleToSelectMenu_hdl, DX_PLAYTYPE_BACK, TRUE);
				soundPlayed = true;
			}

			moveToPlayScene = true;

			MoveToScenePlaySong();
		}
	}

	if (moveToPlayScene)
		soundPlayed = false;
}



void SelectSongMenu::BackToPreviousByInput() {

	// キャンセルキーが押された場合
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0))
	{
		// 難易度選択中なら曲選択に戻る
		if (levelSelect) {

			levelIndex = 0;
			levelSelect = false;
			songSelect = true;
		}
		else if (show_finalCheck_before_startPlaySong) {

			// 最終確認画面を表示中なら難易度選択に戻る
			show_finalCheck_before_startPlaySong = false;
			levelSelect = true;
		}
	}
}



void SelectSongMenu::SelectingLevelByInput() {

	if (levelSelect) {

		// 難易度選択中なら難易度のインデックスを減らす
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT))
		{
			levelIndex--;
			if (levelIndex < 0)
				levelIndex = _LEVEL_NUM - 1;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT))
		{
			levelIndex++;
			if (levelIndex >= _LEVEL_NUM)
				levelIndex = 0;
		}
	}
}

// ----------------------------------------------------------------------------------------------------
void SelectSongMenu::SetDimScreenAtFinalCheck() {

	if (show_finalCheck_before_startPlaySong) {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, dimScreen_alphaSize);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		SetFontSize(100);
		DrawStringEx(_SELECTED_SONG_TEXT_POS_X, _SELECTED_SONG_TEXT_POS_Y, -1,
			_songTitle[songIndex]);   // 選択した曲名

		SetFontSize(50);

		DrawStringEx(_SELECTED_LEVEL_TEXT_POS_X, _SELECTED_LEVEL_TEXT_POS_Y, -1,
			_songLevels[levelIndex]); // 選択した難易度

		DrawStringEx(_START_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Start");
		DrawStringEx(_BACK_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Back");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, dimScreen_alphaSize);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}


void SelectSongMenu::SongGenreTotalCount() {

	// 追加済みプレイリスト
	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// 全曲ジャンル
		for (int j = 0; j < GENRE_NUM; j++)
		{
			// ジャンル名が一致したらカウントを増やす
			if (strcmp(_songGenre[i], _songGenreRefAll[j]) == 0)
			{
				genreCount[j]++;
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
		if (strcmp(_songGenre[songIndex], _songGenreRefAll[i]) == 0)
		{
			SetDrawBright(0, 255, 0); // 色を緑にする
		}

		// ジャンルと曲数を表示する
		DrawFormatString(50, 20 + i * 33, -1, "%s：%d", _songGenreRefAll[i], genreCount[i]);
		SetDrawBright(255, 255, 255); // 色を白に戻す
	}
}


void SelectSongMenu::RenderAndChangeColor_SongTitle() {

	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// 選択中の曲なら色を変える
		if (songSelect && i == songIndex)
		{
			SetDrawBright(255, 255, 0);   // 色を黄色にする
		}
		else {
			SetDrawBright(255, 255, 255); // 色を白に戻す
		}

		// 曲名を表示する
		DrawString(_PLAYLIST_X_POS, _PLAYLIST_Y_POS * (i + 1), _songTitle[i], -1);
	}
}


void SelectSongMenu::RenderAndChangeColor_SongLevel() {

	for (int i = 0; i < _LEVEL_NUM; i++)
	{
		// 選択中の難易度なら色を変える				
		if (levelSelect && i == levelIndex)
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
			_songLevels[i],
			-1
		);
	}
}


void SelectSongMenu::RenderBigSizeTitle_AtCenter() {

	SetDrawBright(255, 255, 255);
	SetFontSize(80);	          //難易度上に選択中の曲のタイトル（大）
	DrawFormatString(_BIGSIZE_TITLE_POS_X, _BIGSIZE_TITLE_POS_Y, -1, _songTitle[songIndex]);

	SetFontSize(40);
	DrawStringEx(1070, 640, -1, "Enter");
	DrawStringEx(10, DXE_WINDOW_HEIGHT - 45, -1, "music select...");
}


void SelectSongMenu::Render() {

	// プレイシーンにまだ飛んでいなければ描画
	if (moveToPlayScene) return;

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
		_songTitle[songIndex],     //選択曲
		_songLevels[levelIndex],  //選択難易度、
		songIndex, levelIndex)); // 選んだ曲の番号 を PlaySongシーンに渡す
}


void SelectSongMenu::Update(float deltaTime) {

	sequence.update(deltaTime);

	SelectingSongByInput();

	PickOneSongByInput();

	BackToPreviousByInput();

	SelectingLevelByInput();

	if (moveToPlayScene) {

		StopSoundMem(songList[songIndex]);
		SetCurrentPositionSoundMem(0, songList[songIndex]);
		songSelect = true;  // また曲選択に戻ってきたときに曲選択から始められるように
	}
}


bool SelectSongMenu::SeqIdle(float deltaTime) {

	return true;
}