#pragma once

class RDS1Server
{
public:
	RDS1Server();
	~RDS1Server();

	bool Init(); // Since we can't return anything from constructor - APAMk2

	bool MainLoop();
	void HandleInput(SDL_Event* event);
private:
	bool ProcessRender();
};