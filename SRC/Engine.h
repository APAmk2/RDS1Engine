#pragma once

class RDS1Engine
{
public:
	RDS1Engine();
	~RDS1Engine();

	bool Init(); // Since we can't return anything from constructor - APAMk2

	bool MainLoop();
	void HandleInput(SDL_Event* event);
private:
	bool ProcessRender();
};