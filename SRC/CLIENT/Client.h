#pragma once

class RDS1Client
{
public:
	RDS1Client();
	~RDS1Client();

	bool Init(); // Since we can't return anything from constructor - APAMk2

	bool MainLoop();
	void HandleInput(SDL_Event* event);
private:
	bool ProcessRender();
};