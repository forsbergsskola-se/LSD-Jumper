#pragma once

class Application;

class State
{
public:

			 State(void) {}
	virtual ~State(void) {}

	virtual bool Create(Application* mainApplication) = 0;
	virtual void Destroy() = 0;
	virtual bool OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;

protected:

	Application* application = nullptr;

};