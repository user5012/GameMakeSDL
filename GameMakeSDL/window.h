#pragma once
#include <SDL.h>
#include <iostream>
class window
{
public:
	window();
	~window();
	bool loadMedia();
	void Resize(SDL_Event& e);
	void KeyListener(SDL_Event& e);
	void ChangeWinMode();
	void update();
	void popup(SDL_Event& e);
	void drawRect(int red, int green, int blue, int width, int height, int x, int y);
	void updaterect(int* x, int* y);

private:
	SDL_Window* sdlwindow = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Event e;
	enum class WindowMode
	{
		Windowed,
		FullScreen
	};
	WindowMode winMode = WindowMode::Windowed;
	SDL_Renderer* renderer = NULL;

};

