#include "../Result/SceneResult.h"
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlaySong.h"
#include "../Manager/SoundManager.h"
#include "../Main.h"


Result::Result(int score, int maxCombo, int Perfect, int Great, int Good,
	int Poor, int Miss, const char* songName, const char* songLevel) {

	LoadMyPastHighScore();
	CheckIfNeed_OverwriteHighScore();

	isResultScene = true;

	_scoreInt = score;

	_score = std::to_string(score);
	_maxCombo = std::to_string(maxCombo);
	_Perfect = std::to_string(Perfect);
	_Great = std::to_string(Great);
	_Good = std::to_string(Good);
	_Poor = std::to_string(Poor);
	_Miss = std::to_string(Miss);

	_songName = const_cast<char*>(songName);
	_songLevel = const_cast<char*>(songLevel);
	_rank = GetRank(score);

	PlaySoundMem(result_BGM_hdl, DX_PLAYTYPE_BACK, false);
}


const char* Result::GetRank(int resultScore) {

	// 文字列の連結は両方のオペランドが std::string型である必要がある

	const char* c;

	if (resultScore >= 100000) c = "∞";
	else if (resultScore >= 95000) c = "S+";
	else if (resultScore >= 90000) c = "S";
	else if (resultScore >= 85000) c = "A+";
	else if (resultScore >= 80000) c = "A";
	else if (resultScore >= 75000) c = "B+";
	else if (resultScore >= 70000) c = "B";
	else if (resultScore >= 60000) c = "C";
	else if (resultScore >= 50000) c = "D";
	else if (resultScore >= 40000) c = "E";
	else c = "F";

	return c;
}


void Result::LoadMyPastHighScore()  {

	FILE* fp = nullptr;
	errno_t error = fopen_s(&fp, "scoreData/scoreData.bin.", "wb");

	// 既にハイスコアデータがあるかの確認
	if (error == 0) {

		fread(&_highScoreInt, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {

		//  ファイルが存在しない場合はハイスコアを0に設定
		_highScoreInt = 0;
	}
}


void Result::CheckIfNeed_OverwriteHighScore() {

	// 新しいスコアと古いスコアを比較、高い方のみ更新
	if (_scoreInt > _highScoreInt) {

		_highScoreInt = _scoreInt;
		_highScore = std::to_string(_highScoreInt);

		FILE* fp = nullptr;
		errno_t error = fopen_s(&fp, "scoreData/scoreData.bin.", "wb");

		if (error == 0) {

			fwrite(&_highScore, sizeof(int), 1, fp);
			fwrite(&_songName, sizeof(int), 1, fp);
			fwrite(&_maxCombo, sizeof(int), 1, fp);
			fwrite(&_rank, sizeof(int), 1, fp);

			fwrite(&_Perfect, sizeof(int), 1, fp);
			fwrite(&_Great, sizeof(int), 1, fp);
			fwrite(&_Good, sizeof(int), 1, fp);
			fwrite(&_Poor, sizeof(int), 1, fp);
			fwrite(&_Miss, sizeof(int), 1, fp);
			
			fclose(fp);
		}

		DrawStringEx(DXE_WINDOW_WIDTH / 1.2f, DXE_WINDOW_HEIGHT / 1.5f, -1, (_highScore).c_str());
		DrawStringEx(DXE_WINDOW_WIDTH / 1.2f, DXE_WINDOW_HEIGHT / 1.45f, -1, "New Record!!");
	}
}


void Result::DrawResult(const float x, const float y, const int fontSize, const std::string& text, const std::string& value) {

	SetFontSize(fontSize);
	DrawStringEx(x, y, -1, text.c_str());

	if (!value.empty()) {

		DrawStringEx(x, y + fontSize * 0.5f, -1, value.c_str());
	}
}


void Result::Render() {

	DrawResult(DXE_WINDOW_WIDTH / 5.2f, DXE_WINDOW_HEIGHT / 2.8f, 22, "PERFECT");
	DrawResult(DXE_WINDOW_WIDTH / 3.1f, DXE_WINDOW_HEIGHT / 3.3f, 22, "GREAT");
	DrawResult(DXE_WINDOW_WIDTH / 2.15f, DXE_WINDOW_HEIGHT / 4.0f, 22, "GOOD");
	DrawResult(DXE_WINDOW_WIDTH / 1.55f, DXE_WINDOW_HEIGHT / 3.3f, 22, "POOR");
	DrawResult(DXE_WINDOW_WIDTH / 1.3f, DXE_WINDOW_HEIGHT / 2.8f, 22, "MISS");
	DrawResult(DXE_WINDOW_WIDTH / 1.2f, DXE_WINDOW_HEIGHT / 1.7f, 22, "MAX COMBO");

	DrawResult(DXE_WINDOW_WIDTH / 5.2f, DXE_WINDOW_HEIGHT / 2.5f, 66, (_Perfect).c_str());
	DrawResult(DXE_WINDOW_WIDTH / 3.1f, DXE_WINDOW_HEIGHT / 3.0f, 66, (_Great).c_str());
	DrawResult(DXE_WINDOW_WIDTH / 2.15f, DXE_WINDOW_HEIGHT / 3.5f, 66, (_Good).c_str());
	DrawResult(DXE_WINDOW_WIDTH / 1.55f, DXE_WINDOW_HEIGHT / 3.0f, 66, (_Poor).c_str());
	DrawResult(DXE_WINDOW_WIDTH / 1.3f, DXE_WINDOW_HEIGHT / 2.5f, 66, (_Miss).c_str());
	DrawResult(DXE_WINDOW_WIDTH / 1.2f, DXE_WINDOW_HEIGHT / 1.55f, 66, (_maxCombo).c_str());

	DrawResult(DXE_WINDOW_WIDTH / 2.35f, DXE_WINDOW_HEIGHT / 2.2f, 35, "S C O R E");
	DrawResult(DXE_WINDOW_WIDTH / 2.35f, DXE_WINDOW_HEIGHT / 1.9f, 99, _score);

	DrawResult(DXE_WINDOW_WIDTH / 2.2f, DXE_WINDOW_HEIGHT / 1.4f, 150, _rank);

	DrawResult(50, DXE_WINDOW_HEIGHT / 1.3f, 40, _songName);
	DrawResult(50, DXE_WINDOW_HEIGHT / 1.2f, 40, _songLevel);
}


void Result::Update(float deltaTime) {
	
	sequence.update(deltaTime);
}


bool Result::SeqIdle(float deltaTime) {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		StopSoundMem(result_BGM_hdl);
		// 再生位置を初期位置に戻す
		SetCurrentPositionSoundMem(0, result_BGM_hdl);

		PlaySong::moveToResult = false;
		isResultScene = false;
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new Title());
	}

	return true;
}