#pragma once

class Timer
{
public:

	 Timer() {}
	~Timer() {}

	void Update();
	double GetDeltaTime() {return deltaTime;}

private:

	double startTime = 0.0;
	double preTime = 0.0;
	double deltaTime = 0.0;

};

