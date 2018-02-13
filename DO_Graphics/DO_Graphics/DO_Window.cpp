#include "DO_Window.h"

bool DO_Window::Init(int w, int h, char *title,char *ttf,int size_font)
{
	window = NULL;
	rend = NULL;

	window = SDL_CreateWindow(title, 233, 233, w, h, SDL_WINDOW_OPENGL);
	rend = SDL_CreateRenderer(window, -1, 0);

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	font = TTF_OpenFont(ttf, size_font);
	font_s = size_font;

	keystate = SDL_GetKeyboardState(NULL);
	ds = DT = 0;
	return false;
}

bool DO_Window::BeginDraw()
{
	SDL_RenderClear(rend);
	SDL_PollEvent(&even);
	if (even.type == SDL_QUIT)
	{
		return 0;
	}
	return 1;
}
#include<iostream>
using namespace std;
void DO_Window::EndDraw()
{
	count++;
	auto fr = SDL_GetPerformanceFrequency();
	auto tj = SDL_GetPerformanceCounter();
	DT = (float)(tj - fs) / fr;
	fs = SDL_GetPerformanceCounter();
	if (tj / SDL_GetPerformanceFrequency() > ds / SDL_GetPerformanceFrequency() + 1)
	{
		ds = SDL_GetPerformanceCounter();
		FPS = count;
		cout << FPS << " " << DT << " " << (float)1 / FPS << endl;
		count = 0;
	}

	SDL_RenderPresent(rend);
}

void DO_Window::SetZoom(float sx, float sy)
{
	SDL_RenderSetScale(rend, sx, sy);
}

int DO_Window::getFPS()
{
	return FPS;
}

float DO_Window::getDT()
{
	return DT < 1 ? DT : 1;
}

bool DO_Window::KeyDown(char * n)
{
	return keystate[SDL_GetScancodeFromName(n)];
}

DO_Window::~DO_Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	TTF_CloseFont(font);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
