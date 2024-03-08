#include "../Main.h"
#include "../Result/SceneResult.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "JudgeZone/JudgeZone.h"
#include "Score_Combo/ScoreCombo.h"
#include "Pause/PauseOption.h"
#include "Timer/Timer.h"
#include "Note/Notes.h"
#include "Note/Normal/NormalNote.h"
#include "Note/Long/LongNote.h"
#include "Note/LoadCSV/NoteDataCsv.h"
#include "ScenePlaySong.h"


JudgeZone judgeZone[4];
Timer* PlaySong::_timer;


namespace {

	const int _COVERALBUM_POS_X1 = 320;
	const int _COVERALBUM_POS_X2 = 960;

	const char* songName;     // 曲名
	const char* songLevel;    // 難易度
}



PlaySong::PlaySong(const char* title, const char* level, const int index, const int levelIdx) {

	songName = title;
	songLevel = level;
	songIndex = index;	   // 選択曲タイトルとカバーアルバムで共有
	levelIndex = levelIdx;

	songDuration = static_cast<float>(GetSoundTotalTime(songList[songIndex]));  // 曲の長さ取得

	LoadImages();
	SetSongBPM();

	// スコア・コンボオブジェクト生成-------------------------------------------------------
	_scoreCombo = new ScoreCombo();
	_scoreCombo->SetScoreComboRef(_scoreCombo);

	// 判定エリアオブジェクト生成-----------------------------------------------------------
	judgeZone->InitJudgeZone();
	judgeZone->SetScoreComboRef(_scoreCombo);

	// ノーツ系各種初期化----------------------------------------------------------------
	NoteDataCsv::GetInstance().SetNoteKeyValue();
	LoadSelectedSongNotes();
	_normal_noteRef = dynamic_cast<NormalNote*>(_normal_downcastRef);
	_long_noteRef = dynamic_cast<LongNote*>(_long_downcastRef);

	// タイマー、ポーズオプションオブジェクト生成-------------------------------------------
	_timer = new Timer();
	_pauseOption = new PauseOption();
}


int coverAlbum_hdl[PlaySong::COVERALBUM_NUM];


void PlaySong::LoadImages() {

	// 著作権の関係上画像は表示しない

	coverAlbum_hdl[0] = LoadGraph("");/*"graphics/symphonyNo9.jpg"*/
	coverAlbum_hdl[1] = LoadGraph("");//graphics/badApple.jpg
	coverAlbum_hdl[2] = LoadGraph("");//graphics/two-facedLovers.jpg
	coverAlbum_hdl[3] = LoadGraph("");//graphics/cruel_angel's _thesis.jpg
}


void PlaySong::SetSongBPM() {

	if (songIndex == 0)	  	  songBpm = 125;
	else if (songIndex == 1)  songBpm = 130;
	else if (songIndex == 2)  songBpm = 140;
	else if (songIndex == 2)  songBpm = 110;

	spawnNotesDuration = 60.0 / songBpm;
}


void PlaySong::LoadSelectedSongNotes() {

	switch (songIndex)
	{
	case 0:
	{
		_normal_downcastRef = new NormalNote("交響曲第9番");
		_long_downcastRef = new LongNote("交響曲第9番");
		break;
	}
	case 1:
	{
		_normal_downcastRef = new NormalNote("BadApple!!");
		_long_downcastRef = new LongNote("BadApple!!");
		break;
	}
	case 2:
	{
		_normal_downcastRef = new NormalNote("裏表ラバーズ");
		_long_downcastRef = new LongNote("裏表ラバーズ");
		break;
	}
	case 3:
	{
		_normal_downcastRef = new NormalNote("残酷な天使のテーゼ");
		_long_downcastRef = new LongNote("残酷な天使のテーゼ");
		break;
	}
	}
}


void PlaySong::PlaySongUntilSongEnd() {

	if (!moveToResult)
		PlaySoundMem(songList[songIndex], DX_PLAYTYPE_BACK, FALSE);
	else
		DeleteSoundMem(songList[songIndex]);
}


void PlaySong::RenderMetaData() {

	SetFontSize(25);
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 70, -1, songName); // 曲名
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 95, -1, songLevel); // 難易度
}


void PlaySong::FadeScreenByAlpha() {

	// シーン遷移後、カバーアルバムと曲タイトルがフェードイン

	elapsed = sequence.getProgressTime();
	progress_ratio = elapsed / duration;
	brightnessAlpha = 0;

	if (elapsed >= duration) {  // フェードイン

		isFadeIn = true;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}
	if (isFadeIn && elapsed >= duration) { // フェードアウト

		isFadeIn = false;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}

	brightnessAlpha = isFadeIn ? (brightnessAlpha = 255 * (1 * progress_ratio)) : (brightnessAlpha = 255 * (1 - progress_ratio));
}


void PlaySong::CheckIfSongEndByTimer() {

	_timer->currentTime = _timer->Elapsed();  // タイマー

	if (_timer->currentTime > (songDuration / 1000.0)) {  // 曲が終わったら

		moveToResult = true;  // リザルトへ
	}
}


void PlaySong::ShowSongInfo_BeforeStart() {

	if (moveToResult)
		moveToResult = false;

	FadeScreenByAlpha();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha <= 0)
		brightnessAlpha = 0.f;

	// カバーアルバム
	DrawExtendGraph(_COVERALBUM_POS_X1, 70, _COVERALBUM_POS_X2, 620, coverAlbum_hdl[songIndex], false);
	SetFontSize(75);
	DrawStringEx(DXE_WINDOW_WIDTH / 3, 625, -1, songName); // 曲名
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha == 0) {

		showInfo_beforeStart_playSong = false;
		elapsed = 0.f;
		progress_ratio = 0.f;

		_timer->Start();

		_timer->Reset();
		currentState = 1;
	}
}


bool PlaySong::isPaused = false;
bool PlaySong::moveToResult = false;
int PlaySong::songIndex = 0; // 曲番号
int PlaySong::currentState = 0;  // メニュー画面のステート状態


void PlaySong::Render() {

	// フェードイン後、曲情報を表示。それまで他の処理は無効
	switch (currentState)
	{
	case 0:

		if (showInfo_beforeStart_playSong) {

			ShowSongInfo_BeforeStart();
		}
		break;
	case 1:

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P) ||
			tnl::Input::IsPadDownTrigger(ePad::KEY_4)) {

			isPaused = true;
		}

		if (!isPaused) {

			if (!moveToResult)
				PlaySongUntilSongEnd();  // 音源

			//SetFontSize(35); // タイマー表示(左上)
			//std::string time = std::to_string(_timer->currentTime);
			//DrawString(50, 50, time.c_str(), -1);

			StopSoundMem(pause_BGM_hdl);  // ポーズ画面BGM停止
			SetCurrentPositionSoundMem(0, pause_BGM_hdl);


			RenderMetaData(); // 曲情報描画

			_scoreCombo->RenderCombo(); // コンボ描画
			_scoreCombo->RenderScore(); // スコア描画

			// 曲が終わったら問答無用でリザルトへ
			CheckIfSongEndByTimer();

			judgeZone->RenderMap(); // 全体エリア描画
			judgeZone->RenderJudgeZones();

			//　ノーツ及び当たり判定エリア処理。この関数内で全て行っている。
			_normal_noteRef->UpdateNotes(_timer->currentTime, GetDeltaTime());
			_long_noteRef->UpdateNotes(_timer->currentTime, GetDeltaTime());

			DrawStringEx(5, 5, -1, "PAUSE：P");
			break;
		}
		else
		{
			_timer->Pause();	// ポーズが開始されたときの時間を記録

			PlaySoundMem(pause_BGM_hdl, DX_PLAYTYPE_LOOP, false);

			StopSoundMem(songList[songIndex]);  // 音源一時停止

			if (!_pauseOption->showOption) {

				_pauseOption->UpdatePauseMenuCursor_ByInput();

				// 右半分に表示の備考
				_pauseOption->RenderMenuItems_AndDescriptions();

				// 決定キーが押された場合
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

					_pauseOption->PickMenuItemByInput();
				}
			}
			else {   // オプションを開いている時の処理

				_pauseOption->UpdatePauseOptionCursor_ByInput();

				_pauseOption->ChangePauseOptionColor();

				_pauseOption->GoNextOrGoBack();

				_pauseOption->AdjustVolumeByInput();

				// low, medium, highの色 
				int eff1_color = -1, eff2_color = -1, eff3_color = -1;


				if (_pauseOption->selectEffectColor) { // low, medium, highの文字列の色の変更

					_pauseOption->UpdateSelectEffectCursor_ByInput();
					_pauseOption->ChangeSelectEffectColorAndBrightness(eff1_color, eff2_color, eff3_color);
				}

				SetFontSize(33);
				_pauseOption->RenderAdjustVolumeFunc();
				_pauseOption->RenderLowMediumHighWord(eff1_color, eff2_color, eff3_color);
			}
		}
		showInfo_beforeStart_playSong = true;
		break;
	case 2:
		moveToSongSelect = true;
		break;
	}
}



void PlaySong::Update(float delta_time) {

	sequence.update(delta_time);

	_timer->UpdateDeltaTime();
	_timer->GetDeltaTime();

	deltaTime_ref = delta_time;

	if (moveToSongSelect) {

		ResetGame();

		// 選曲シーンへ
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
	}

	if (PauseOption::isRetryGame) {

		ResetGame();

		PauseOption::isRetryGame = false;

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new PlaySong(
			SelectSongMenu::_songTitle[songIndex],   //選択曲
			SelectSongMenu::_songLevels[levelIndex], //選択難易度、
			songIndex,
			levelIndex)
		); // 選んだ曲の番号 を PlaySongシーンに渡す
	}

	if (moveToResult) {

		SetFontSize(50);
		DrawString(400, 360, "Move to Result", -1);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			ResetGame();

			auto mgr = SceneManager::GetInstance();
			mgr->SceneChange(new Result(
				_scoreCombo->myScore,
				_scoreCombo->myCombo,
				_scoreCombo->perfect_count,
				_scoreCombo->great_count,
				_scoreCombo->good_count,
				_scoreCombo->poor_count,
				_scoreCombo->miss_count,
				songName,
				songLevel)
			); // 選んだ曲の番号 を PlaySongシーンに渡す
		}
	}
}


bool PlaySong::SeqIdle(float delta_time) {
	return true;
}


void PlaySong::ResetGame()
{
	StopSoundMem(songList[songIndex]);
	SetCurrentPositionSoundMem(0, songList[songIndex]);
	ClearDrawScreen();

	isPaused = false;
	moveToResult = false;
	moveToSongSelect = false;

	Destroy();
}


void PlaySong::Destroy() {

	delete _scoreCombo;
	_scoreCombo = nullptr;

	delete _pauseOption;
	_pauseOption = nullptr;

	delete _normal_downcastRef;
	_normal_downcastRef = nullptr;

	_long_downcastRef = nullptr;
	delete _long_downcastRef;
}