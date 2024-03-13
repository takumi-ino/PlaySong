#pragma once
#include <chrono>


class Timer {
public:

	Timer() : _isPaused(false) {}

	void Start();      // 開始

	void Pause();      // 一時停止

	void Resume();     // 再開

	void Reset();      // リセット

	double Elapsed();  // 経過

public:

	bool   _isPaused{};

	double _currentTime{};

	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _pausedTime;
};