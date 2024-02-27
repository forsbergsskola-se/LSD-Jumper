#pragma once


class Timer
{
public:
	Timer() {}
	~Timer() {}
	void Update();
	double getDeltaTime();

private:
	double startTime = 0.0;
	double preTime = 0.0;
	double DeltaTime = 0.0;

};

