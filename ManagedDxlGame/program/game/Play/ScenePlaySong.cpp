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

	const char* songName;     // �Ȗ�
	const char* songLevel;    // ��Փx
}


PlaySong::PlaySong(const char* title, const char* level, const int index, const int levelIdx) {

	RevertAllChanges();

	songName = title;
	songLevel = level;
	songIndex = index;	   // �I���ȃ^�C�g���ƃJ�o�[�A���o���ŋ��L
	levelIndex = levelIdx;

	songDuration = static_cast<float>(GetSoundTotalTime(songList[songIndex]));  // �Ȃ̒����擾

	LoadImages();
	SetSongBPM();

	// �X�R�A�E�R���{�I�u�W�F�N�g����-------------------------------------------------------
	_scoreCombo = new ScoreCombo();
	_scoreCombo->SetScoreComboRef(_scoreCombo);

	// ����G���A�I�u�W�F�N�g����-----------------------------------------------------------
	judgeZone->InitJudgeZone();
	judgeZone->SetScoreComboRef(_scoreCombo);

	// �m�[�c�n�e�평����----------------------------------------------------------------
	NoteDataCsv::GetInstance().SetNoteKeyValue();
	LoadSelectedSongNotes();
	_normal_noteRef = dynamic_cast<NormalNote*>(_normal_downcastRef);
	_long_noteRef = dynamic_cast<LongNote*>(_long_downcastRef);

	// �^�C�}�[�A�|�[�Y�I�v�V�����I�u�W�F�N�g����-------------------------------------------
	_timer = new Timer();
	_pauseOption = new PauseOption();
}


int coverAlbum_hdl[PlaySong::COVERALBUM_NUM];


void PlaySong::LoadImages() {

	// ���쌠�̊֌W��摜�͕\�����Ȃ�

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


void PlaySong::PlaySongUntilSongEnd() {

	if (!moveToResult)
		PlaySoundMem(songList[songIndex], DX_PLAYTYPE_BACK, FALSE);
	else
		DeleteSoundMem(songList[songIndex]);
}


void PlaySong::RenderMetaData() {

	SetFontSize(25);
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 70, -1, songName);  // �Ȗ�
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 95, -1, songLevel); // ��Փx
}


void PlaySong::FadeScreenByAlpha() {

	// �V�[���J�ڌ�A�J�o�[�A���o���Ƌȃ^�C�g�����t�F�[�h�C��

	elapsed = sequence.getProgressTime();
	progress_ratio = elapsed / duration;
	brightnessAlpha = 0;

	if (elapsed >= duration) {  // �t�F�[�h�C��

		isFadeIn = true;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}
	if (isFadeIn && elapsed >= duration) { // �t�F�[�h�A�E�g

		isFadeIn = false;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}

	brightnessAlpha = isFadeIn ? (brightnessAlpha = 255 * (1 * progress_ratio)) : (brightnessAlpha = 255 * (1 - progress_ratio));
}


void PlaySong::CheckIfSongEndByTimer() {

	_timer->currentTime = _timer->Elapsed();  // �^�C�}�[

	if (_timer->currentTime > (songDuration / 1000.0)) {  // �Ȃ��I�������

		moveToResult = true;  // ���U���g��
	}
}


void PlaySong::ShowSongInfo_BeforeStart() {

	if (moveToResult)
		moveToResult = false;

	FadeScreenByAlpha();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightnessAlpha));

	if (brightnessAlpha <= 0)
		brightnessAlpha = 0.f;

	// �J�o�[�A���o��
	DrawExtendGraph(_COVERALBUM_POS_X1, 70, _COVERALBUM_POS_X2, 620, coverAlbum_hdl[songIndex], false);
	SetFontSize(75);
	DrawStringEx(DXE_WINDOW_WIDTH / 3, 625, -1, songName); // �Ȗ�
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
int PlaySong::songIndex = 0; // �Ȕԍ�
int PlaySong::currentState = 0;  // ���j���[��ʂ̃X�e�[�g���


void PlaySong::Render() {

	// �t�F�[�h�C����A�ȏ���\���B����܂ő��̏����͖���
	switch (currentState)
	{
	case 0:

		if (showInfo_beforeStart_playSong) {

			ShowSongInfo_BeforeStart();
		}

		break;
	case 1:

		if (!isPaused) {

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

			if (!_pauseOption->showOption) {

				// �E�����ɕ\���̔��l
				_pauseOption->RenderMenuItems_AndDescriptions();
			}
			else {

				// low, medium, high�̐F 
				int eff1_color = -1, eff2_color = -1, eff3_color = -1;

				SetFontSize(33);
				_pauseOption->RenderAdjustVolumeObject();
				_pauseOption->RenderLowMediumHighWord(eff1_color, eff2_color, eff3_color);
			}
		}
		break;
	}
}


bool PlaySong::moveToSongSelect;


void PlaySong::Update(float delta_time) {

	sequence.update(delta_time);


	deltaTime_ref = delta_time;

	switch (currentState)
	{
	case 1:

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P) ||
			tnl::Input::IsPadDownTrigger(ePad::KEY_4)) {

			isPaused = true;
		}

		if (!isPaused) {

			if (!moveToResult) {

				PlaySongUntilSongEnd();  // ����
			}

			// �|�[�Y���BGM��~
			StopSoundMem(pause_BGM_hdl);
			SetCurrentPositionSoundMem(0, pause_BGM_hdl);

			// �Ȃ��I�������ⓚ���p�Ń��U���g��
			CheckIfSongEndByTimer();

			// �m�[�c�y�ѓ����蔻��G���A�����B���̊֐����őS�čs��
			_normal_noteRef->UpdateNotes(_timer->currentTime, GetDeltaTime());
			_long_noteRef->UpdateNotes(_timer->currentTime, GetDeltaTime());
		}
		else
		{
			_timer->Pause();	// �|�[�Y���J�n���ꂽ�Ƃ��̎��Ԃ��L�^

			PlaySoundMem(pause_BGM_hdl, DX_PLAYTYPE_LOOP, false);

			StopSoundMem(songList[songIndex]);  // �����ꎞ��~

			if (!_pauseOption->showOption) {

				_pauseOption->UpdatePauseMenuCursor_ByInput();

				// ����L�[�������ꂽ�ꍇ
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

					_pauseOption->PickMenuItemByInput();
				}
			}
			else {   // �I�v�V�������J���Ă��鎞�̏���

				_pauseOption->UpdatePauseOptionCursor_ByInput();

				_pauseOption->ChangePauseOptionColor();

				_pauseOption->GoNextOrGoBack();

				_pauseOption->AdjustVolumeByInput();

				// low, medium, high�̐F 
				int eff1_color = -1, eff2_color = -1, eff3_color = -1;

				if (_pauseOption->selectEffectColor) { // low, medium, high�̕�����̐F�̕ύX

					_pauseOption->UpdateSelectEffectCursor_ByInput();
					_pauseOption->ChangeSelectEffectColorAndBrightness(eff1_color, eff2_color, eff3_color);
				}
			}
		}

		showInfo_beforeStart_playSong = true;
		break;
	}
}


bool PlaySong::isRetryGame;


bool PlaySong::SeqIdle(float delta_time) {

	if (moveToSongSelect) {

		RevertAllChanges();

		// �I�ȃV�[����
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
	}

	if (isRetryGame) {

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new PlaySong(
			SelectSongMenu::_songTitle[songIndex],   //�I����
			SelectSongMenu::_songLevels[levelIndex], //�I���Փx�A
			songIndex,
			levelIndex)
		); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��
	}

	if (moveToResult) {

		SetFontSize(50);
		DrawString(400, 360, "Move to Result", -1);

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			RevertAllChanges();
			Destroy();

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
			); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��

			delete _scoreCombo;
			_scoreCombo = nullptr;
		}
	}

	return true;
}


void PlaySong::RevertAllChanges()
{
	StopSoundMem(songList[songIndex]);
	SetCurrentPositionSoundMem(0, songList[songIndex]);
	ClearDrawScreen();

	isPaused = false;
	isRetryGame = false;
	moveToResult = false;
	moveToSongSelect = false;

	currentState = 0;
}


void PlaySong::Destroy() {

	delete _pauseOption;
	_pauseOption = nullptr;

	delete _normal_downcastRef;
	_normal_downcastRef = nullptr;

	_long_downcastRef = nullptr;
	delete _long_downcastRef;
}