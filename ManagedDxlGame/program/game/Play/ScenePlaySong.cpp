#include "../library/tnl_sequence.h"
#include "ScenePlaySong.h"
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


JudgeZone judgeZone[4];
Timer* PlaySong::_timer;


namespace {

	const int _COVERALBUM_POS_X1 = 320;
	const int _COVERALBUM_POS_X2 = 960;

	const char* songName;     // 曲名
	const char* songLevel;    // 難易度

	const float _PERFORMANCE_DURATION = 4.0f;  // 曲情報表示時間
}


// 初期処理----------------------------------------------------------------------------------------------------
PlaySong::PlaySong(const char* title, const char* level, const int index, const int levelIdx) {

	RevertAllChanges();
	Destroy();

	songName = title;
	songLevel = level;
	_songIndex = index;	   // 選択曲タイトルとカバーアルバムで共有
	_levelIndex = levelIdx;

	_songDuration = static_cast<float>(GetSoundTotalTime(songList[_songIndex]));  // 曲の長さ取得

	LoadImages();
	SetSongBPM();

	// スコア・コンボオブジェクト生成-------------------------------------------------------
	_scoreCombo = new ScoreCombo();
	_scoreCombo->SetScoreComboRef(_scoreCombo);

	// 判定エリアオブジェクト生成-----------------------------------------------------------
	judgeZone->InitJudgeZone();
	judgeZone->SetScoreComboRef(_scoreCombo);

	// ノーツ系各種初期化----------------------------------------------------------------
	NoteDataCsv::GetInstance().InitNoteKeyValue();
	LoadSelectedSongNotes();
	_normal_noteRef = dynamic_cast<NormalNote*>(_normal_downcastRef);
	_long_noteRef = dynamic_cast<LongNote*>(_long_downcastRef);

	// タイマー、ポーズオプションオブジェクト生成-------------------------------------------
	_timer = new Timer();
	_pauseOption = new PauseOption();
}


int coverAlbum_hdl[PlaySong::_COVERALBUM_NUM];


void PlaySong::LoadImages() {

	// 著作権の関係上画像は表示しない

	coverAlbum_hdl[0] = LoadGraph("");/*"graphics/symphonyNo9.jpg"*/
	coverAlbum_hdl[1] = LoadGraph("");//graphics/badApple.jpg
	coverAlbum_hdl[2] = LoadGraph("");//graphics/two-facedLovers.jpg
	coverAlbum_hdl[3] = LoadGraph("");//graphics/cruel_angel's _thesis.jpg
}


void PlaySong::SetSongBPM() {

	if (_songIndex == 0)	   _songBpm = 125;
	else if (_songIndex == 1)  _songBpm = 130;
	else if (_songIndex == 2)  _songBpm = 140;
	else if (_songIndex == 2)  _songBpm = 110;
}


void PlaySong::LoadSelectedSongNotes() {

	switch (_songIndex)
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


// 各種機能----------------------------------------------------------------------------------------------------
bool PlaySong::_isRetryGame;
bool PlaySong::_moveToSongSelect;
bool PlaySong::_isPaused = false;
bool PlaySong::_moveToResult = false;
int PlaySong::_songIndex = 0; // 曲番号
int PlaySong::_currentState = 0;  // メニュー画面のステート状態


void PlaySong::RevertAllChanges()
{
	StopSoundMem(songList[_songIndex]);
	SetCurrentPositionSoundMem(0, songList[_songIndex]);
	ClearDrawScreen();

	_isPaused = false;
	_isRetryGame = false;
	_moveToResult = false;
	_moveToSongSelect = false;

	_currentState = 0;
}


void PlaySong::BackToSelectSongMenu()
{
	if (_moveToSongSelect) {

		RevertAllChanges();

		// 選曲シーンへ
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
	}
}


void PlaySong::RetryGame()
{
	if (_isRetryGame) {

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new PlaySong(
			SelectSongMenu::_SONG_TITLE[_songIndex],   //選択曲
			SelectSongMenu::_SONG_LEVELS[_levelIndex], //選択難易度、
			_songIndex,
			_levelIndex)
		); // 選んだ曲の番号 を PlaySongシーンに渡す
	}
}


void PlaySong::MoveToResult()
{
	if (_moveToResult) {

		SetFontSize(50);
		DrawString(400, 360, "Move to Result", -1);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			RevertAllChanges();
			DeleteSoundMem(songList[_songIndex]);

			_moveToResult = false;

			auto mgr = SceneManager::GetInstance();
			mgr->SceneChange(new Result(
				_scoreCombo->_myScore,
				_scoreCombo->_myCombo,
				_scoreCombo->_perfectCount,
				_scoreCombo->_greatCount,
				_scoreCombo->_goodCount,
				_scoreCombo->_poorCount,
				_scoreCombo->_missCount,
				songName,
				songLevel)
			); // 選んだ曲の番号 を PlaySongシーンに渡す
		}
	}
}


void PlaySong::ActivatePauseMenu()
{
	switch (_currentState)
	{
	case 1:

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P) ||
			tnl::Input::IsPadDownTrigger(ePad::KEY_4)) {

			_isPaused = true;
		}

		if (!_isPaused) {

			if (!_moveToResult) {

				PlaySongUntilSongEnd();  // 音源
			}

			// ポーズ画面BGM停止
			StopSoundMem(pause_BGM_hdl);
			SetCurrentPositionSoundMem(0, pause_BGM_hdl);

			// 曲が終わったら問答無用でリザルトへ
			CheckIfSongEndByTimer();

			// ノーツ及び当たり判定エリア処理。この関数内で全て行う
			_normal_noteRef->UpdateNotes(_timer->_currentTime, GetDeltaTime());
			_long_noteRef->UpdateNotes(_timer->_currentTime, GetDeltaTime());
		}
		else
		{
			_timer->Pause();	// ポーズが開始されたときの時間を記録

			PlaySoundMem(pause_BGM_hdl, DX_PLAYTYPE_LOOP, false);

			StopSoundMem(songList[_songIndex]);  // 音源一時停止

			if (!_pauseOption->_showOption) {

				_pauseOption->UpdatePauseMenuCursor_ByInput();

				// 決定キーが押された場合
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

					_pauseOption->PickMenuItemByInput();
				}
			}
			else {   // オプションを開いている時の処理

				_pauseOption->UpdateDetailOptionCursor_ByInput();

				_pauseOption->ChangePauseOptionColor();

				_pauseOption->GoNextOrGoBack();

				_pauseOption->AdjustVolumeByInput();
			}
		}

		_showInfo_beforeStartGame = true;
		break;
	}
}


void PlaySong::PlaySongUntilSongEnd() {

	if (!_moveToResult)
		PlaySoundMem(songList[_songIndex], DX_PLAYTYPE_BACK, FALSE);
	else
		DeleteSoundMem(songList[_songIndex]);
}


void PlaySong::FadeScreenByAlpha() {

	// シーン遷移後、カバーアルバムと曲タイトルがフェードイン

	_elapsed = sequence.getProgressTime();
	_progress_ratio = _elapsed / _PERFORMANCE_DURATION;
	brightnessAlpha = 0;

	if (_elapsed >= _PERFORMANCE_DURATION) {  // フェードイン

		_isFadeIn = true;
		_elapsed = 0.f;
		_progress_ratio = 0.f;
	}
	if (_isFadeIn && _elapsed >= _PERFORMANCE_DURATION) { // フェードアウト

		_isFadeIn = false;
		_elapsed = 0.f;
		_progress_ratio = 0.f;
	}

	brightnessAlpha = _isFadeIn ? 
		(brightnessAlpha = 255.f * (1.f * _progress_ratio)) : 
		(brightnessAlpha = 255.f * (1.f - _progress_ratio));
}


void PlaySong::CheckIfSongEndByTimer() {

	_timer->_currentTime = _timer->Elapsed();  // タイマー

	if (_timer->_currentTime > (_songDuration / 1000.0)) {  // 曲が終わったら

		_moveToResult = true;  // リザルトへ
	}
}


void PlaySong::ShowSongInfo_BeforeStart() {

	if (_moveToResult)
		_moveToResult = false;

	FadeScreenByAlpha();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha <= 0)
		brightnessAlpha = 0.f;

	// カバーアルバム
	DrawExtendGraph(_COVERALBUM_POS_X1, 70, _COVERALBUM_POS_X2, 620, coverAlbum_hdl[_songIndex], false);
	SetFontSize(75);
	DrawStringEx(DXE_WINDOW_WIDTH / 3, 625, -1, songName); // 曲名
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha == 0) {

		_showInfo_beforeStartGame = false;
		_elapsed = 0.f;
		_progress_ratio = 0.f;

		_timer->Start();

		_timer->Reset();
		_currentState = 1;
	}
}


// 描画--------------------------------------------------------------------------------
void PlaySong::RenderMetaData() {

	SetFontSize(25);
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 70, -1, songName);  // 曲名
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 95, -1, songLevel); // 難易度
}


void PlaySong::Render() {

	// フェードイン後、曲情報を表示。それまで他の処理は無効
	switch (_currentState)
	{
	case 0:

		if (_showInfo_beforeStartGame) {

			ShowSongInfo_BeforeStart();
		}

		break;
	case 1:

		if (!_isPaused) {

			//SetFontSize(35); // タイマー表示(左上)
			//std::string time = std::to_string(_timer->currentTime);
			//DrawString(50, 50, time.c_str(), -1);

			RenderMetaData(); // 曲情報描画

			_scoreCombo->RenderCombo();    // コンボ描画
			_scoreCombo->RenderScore();    // スコア描画

			judgeZone->RenderMap();        // 全体エリア描画
			judgeZone->RenderJudgeZones();

			DrawString(5, 5, "PAUSE：P", -1);
		}
		else {

			if (!_pauseOption->_showOption) {

				// 右半分に表示の備考
				_pauseOption->RenderMenuItems_AndDescriptions();
			}
			else {

				// low, medium, highの色 
				int eff1_color = -1, eff2_color = -1, eff3_color = -1;

				if (_pauseOption->_isSelectEffectColor) {

					_pauseOption->AdjustScreenBrightnessByInput();
					_pauseOption->ChangeSelectEffectColorAndBrightness(eff1_color, eff2_color, eff3_color);
				}

				SetFontSize(33);
				_pauseOption->RenderAdjustVolumeObject();
				_pauseOption->RenderBrightnessLevels(eff1_color, eff2_color, eff3_color);
			}
		}
		break;
	}
}



// 更新--------------------------------------------------------------------------------
void PlaySong::Update(float delta_time) {

	sequence.update(delta_time);

	_deltaTime = delta_time;

	ActivatePauseMenu();

	BackToSelectSongMenu();

	RetryGame();

	MoveToResult();

}


void PlaySong::Destroy() {

	delete _pauseOption;
	_pauseOption = nullptr;

	delete _normal_downcastRef;
	_normal_downcastRef = nullptr;

	_long_downcastRef = nullptr;
	delete _long_downcastRef;
}