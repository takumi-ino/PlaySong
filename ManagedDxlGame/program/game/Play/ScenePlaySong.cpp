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

	const char* songName;     // �Ȗ�
	const char* songLevel;    // ��Փx

	const float _PERFORMANCE_DURATION = 4.0f;  // �ȏ��\������
}


// ��������----------------------------------------------------------------------------------------------------
PlaySong::PlaySong(const char* title, const char* level, const int index, const int levelIdx) {

	RevertAllChanges();
	Destroy();

	songName = title;
	songLevel = level;
	_songIndex = index;	   // �I���ȃ^�C�g���ƃJ�o�[�A���o���ŋ��L
	_levelIndex = levelIdx;

	_songDuration = static_cast<float>(GetSoundTotalTime(songList[_songIndex]));  // �Ȃ̒����擾

	LoadImages();
	SetSongBPM();

	// �X�R�A�E�R���{�I�u�W�F�N�g����-------------------------------------------------------
	_scoreCombo = new ScoreCombo();
	_scoreCombo->SetScoreComboRef(_scoreCombo);

	// ����G���A�I�u�W�F�N�g����-----------------------------------------------------------
	judgeZone->InitJudgeZone();
	judgeZone->SetScoreComboRef(_scoreCombo);

	// �m�[�c�n�e�평����----------------------------------------------------------------
	NoteDataCsv::GetInstance().InitNoteKeyValue();
	LoadSelectedSongNotes();
	_normal_noteRef = dynamic_cast<NormalNote*>(_normal_downcastRef);
	_long_noteRef = dynamic_cast<LongNote*>(_long_downcastRef);

	// �^�C�}�[�A�|�[�Y�I�v�V�����I�u�W�F�N�g����-------------------------------------------
	_timer = new Timer();
	_pauseOption = new PauseOption();
}


int coverAlbum_hdl[PlaySong::_COVERALBUM_NUM];


void PlaySong::LoadImages() {

	// ���쌠�̊֌W��摜�͕\�����Ȃ�

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
		_normal_downcastRef = new NormalNote("�����ȑ�9��");
		_long_downcastRef = new LongNote("�����ȑ�9��");
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
		_normal_downcastRef = new NormalNote("���\���o�[�Y");
		_long_downcastRef = new LongNote("���\���o�[�Y");
		break;
	}
	case 3:
	{
		_normal_downcastRef = new NormalNote("�c���ȓV�g�̃e�[�[");
		_long_downcastRef = new LongNote("�c���ȓV�g�̃e�[�[");
		break;
	}
	}
}


// �e��@�\----------------------------------------------------------------------------------------------------
bool PlaySong::_isRetryGame;
bool PlaySong::_moveToSongSelect;
bool PlaySong::_isPaused = false;
bool PlaySong::_moveToResult = false;
int PlaySong::_songIndex = 0; // �Ȕԍ�
int PlaySong::_currentState = 0;  // ���j���[��ʂ̃X�e�[�g���


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

		// �I�ȃV�[����
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
	}
}


void PlaySong::RetryGame()
{
	if (_isRetryGame) {

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new PlaySong(
			SelectSongMenu::_SONG_TITLE[_songIndex],   //�I����
			SelectSongMenu::_SONG_LEVELS[_levelIndex], //�I���Փx�A
			_songIndex,
			_levelIndex)
		); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��
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
			); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��
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

				PlaySongUntilSongEnd();  // ����
			}

			// �|�[�Y���BGM��~
			StopSoundMem(pause_BGM_hdl);
			SetCurrentPositionSoundMem(0, pause_BGM_hdl);

			// �Ȃ��I�������ⓚ���p�Ń��U���g��
			CheckIfSongEndByTimer();

			// �m�[�c�y�ѓ����蔻��G���A�����B���̊֐����őS�čs��
			_normal_noteRef->UpdateNotes(_timer->_currentTime, GetDeltaTime());
			_long_noteRef->UpdateNotes(_timer->_currentTime, GetDeltaTime());
		}
		else
		{
			_timer->Pause();	// �|�[�Y���J�n���ꂽ�Ƃ��̎��Ԃ��L�^

			PlaySoundMem(pause_BGM_hdl, DX_PLAYTYPE_LOOP, false);

			StopSoundMem(songList[_songIndex]);  // �����ꎞ��~

			if (!_pauseOption->_showOption) {

				_pauseOption->UpdatePauseMenuCursor_ByInput();

				// ����L�[�������ꂽ�ꍇ
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

					_pauseOption->PickMenuItemByInput();
				}
			}
			else {   // �I�v�V�������J���Ă��鎞�̏���

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

	// �V�[���J�ڌ�A�J�o�[�A���o���Ƌȃ^�C�g�����t�F�[�h�C��

	_elapsed = sequence.getProgressTime();
	_progress_ratio = _elapsed / _PERFORMANCE_DURATION;
	brightnessAlpha = 0;

	if (_elapsed >= _PERFORMANCE_DURATION) {  // �t�F�[�h�C��

		_isFadeIn = true;
		_elapsed = 0.f;
		_progress_ratio = 0.f;
	}
	if (_isFadeIn && _elapsed >= _PERFORMANCE_DURATION) { // �t�F�[�h�A�E�g

		_isFadeIn = false;
		_elapsed = 0.f;
		_progress_ratio = 0.f;
	}

	brightnessAlpha = _isFadeIn ? 
		(brightnessAlpha = 255.f * (1.f * _progress_ratio)) : 
		(brightnessAlpha = 255.f * (1.f - _progress_ratio));
}


void PlaySong::CheckIfSongEndByTimer() {

	_timer->_currentTime = _timer->Elapsed();  // �^�C�}�[

	if (_timer->_currentTime > (_songDuration / 1000.0)) {  // �Ȃ��I�������

		_moveToResult = true;  // ���U���g��
	}
}


void PlaySong::ShowSongInfo_BeforeStart() {

	if (_moveToResult)
		_moveToResult = false;

	FadeScreenByAlpha();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha <= 0)
		brightnessAlpha = 0.f;

	// �J�o�[�A���o��
	DrawExtendGraph(_COVERALBUM_POS_X1, 70, _COVERALBUM_POS_X2, 620, coverAlbum_hdl[_songIndex], false);
	SetFontSize(75);
	DrawStringEx(DXE_WINDOW_WIDTH / 3, 625, -1, songName); // �Ȗ�
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


// �`��--------------------------------------------------------------------------------
void PlaySong::RenderMetaData() {

	SetFontSize(25);
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 70, -1, songName);  // �Ȗ�
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 95, -1, songLevel); // ��Փx
}


void PlaySong::Render() {

	// �t�F�[�h�C����A�ȏ���\���B����܂ő��̏����͖���
	switch (_currentState)
	{
	case 0:

		if (_showInfo_beforeStartGame) {

			ShowSongInfo_BeforeStart();
		}

		break;
	case 1:

		if (!_isPaused) {

			//SetFontSize(35); // �^�C�}�[�\��(����)
			//std::string time = std::to_string(_timer->currentTime);
			//DrawString(50, 50, time.c_str(), -1);

			RenderMetaData(); // �ȏ��`��

			_scoreCombo->RenderCombo();    // �R���{�`��
			_scoreCombo->RenderScore();    // �X�R�A�`��

			judgeZone->RenderMap();        // �S�̃G���A�`��
			judgeZone->RenderJudgeZones();

			DrawString(5, 5, "PAUSE�FP", -1);
		}
		else {

			if (!_pauseOption->_showOption) {

				// �E�����ɕ\���̔��l
				_pauseOption->RenderMenuItems_AndDescriptions();
			}
			else {

				// low, medium, high�̐F 
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



// �X�V--------------------------------------------------------------------------------
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