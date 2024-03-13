#pragma once
#include "../Manager/Scene/SceneBase.h"


class Result : public Scenes 
{
public:

	Result(){}
	Result(
		int score, 
		int maxCombo,
		int Perfect,
		int Great,
		int Good,
		int Poor, 
		int Miss, 
		const char* songName,
		const char* songLevel
	);

	void Render() override;
	void Update(float deltaTime) override;

private:

	const char* GetRank(int resultScore);  // スコアに応じたランクを返す

	void LoadMyPastHighScore();            // 過去のハイスコアをロード

	void CheckIfNeed_OverwriteHighScore(); // ハイスコアを必要に応じて更新

	void DrawResult(                       // 各種テキストに応じて描画
		const float x, 
		const float y,
		const int fontSize, 
		const std::string text,
		const int value = -1
    );

private:

	// 総合スコア----------------------------------------
	int         _score{};
	int         _highScore{};
	int         _maxCombo{};

	// 各種スコア----------------------------------------
	int         _perfect{};
	int         _great{};
	int         _good{};
	int         _poor{};
	int         _miss{};

	// ----------------------------------------
	char*       _songName{};    // 曲名
	char*       _songLevel{};   // 難易度
	const char* _rank{};        // ランク

	// ----------------------------------------
	bool        _isResultScene = true;
};