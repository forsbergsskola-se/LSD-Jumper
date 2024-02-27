#pragma once

class Application 
{
public:
	Application();
	~Application();

	bool Create();
	void Destroy();
	void Run();
	void Update();
	void Render();


};