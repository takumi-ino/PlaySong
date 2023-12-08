#pragma once
#include <chrono>
#include "../Pause/PauseOption.h"


class Timer {
public:

	Timer() : isPaused(false) {}

	void Start();

	void Pause();

	void Resume();

	void Reset();

	double Elapsed();

	void UpdateDeltaTime();

	const double GetDeltaTime();

public:

	bool isPaused;

	double currentTime; // タイマー
	double deltaTime;
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point paused_time;
	std::chrono::high_resolution_clock::time_point lastFrameTime;
};