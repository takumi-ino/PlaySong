#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"
#include <string>


class Result : public Scenes {
public:

	Result(){}
	Result(int score, int maxCombo, int Perfect, int Great, int Good,
		int Poor, int Miss, const char* songName, const char* songLevel);

	void Render() override;
	void Update(float deltaTime) override;

	const char* GetRank(int resultScore) ;

private:

	void LoadMyPastHighScore();

	void CheckIfNeed_OverwriteHighScore();

	tnl::Sequence<Result> sequence = tnl::Sequence<Result>(this, &Result::SeqIdle);
	bool SeqIdle(float deltaTime);

private:

	int _highScoreInt;

	int _scoreInt;
	int _PerfectInt;
	int _GreatInt;
	int _GoodInt;
	int _PoorInt;
	int _MissInt;

	int _maxComboInt;

	char* _songName;
	char* _songLevel;
	const char* _rank;

	std::string _score;
	std::string _highScore;
	std:: string _maxCombo;
	std::string _Perfect;
	std::string _Great;
	std::string _Good;
	std::string _Poor;
	std::string _Miss;


	bool isResultScene = true;
};