#include "DO_Window.h"
#include "DO_Image.h"

DO_Window::DO_Window(int w, int h, char *title,char *ttf,int size_font)
{
	window = NULL;
	rend = NULL;

	window = SDL_CreateWindow(title, 233, 233, w, h, SDL_WINDOW_OPENGL);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	font = TTF_OpenFont(ttf, size_font);
	font_s = size_font;

	keystate = SDL_GetKeyboardState(NULL);
	ds = DT = 0;

	SDL_GetWindowSurface(window)->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	return;
}

bool DO_Window::BeginDraw()
{
	SetWorkingImage(NULL);
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

bool DO_Window::SetWorkingImage(DO_Image *image)
{
	if (SDL_SetRenderTarget(rend, image ? image->gett() : NULL) == -1)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error:", "DO_Window::SetWorkingImage Fail", window);
	return true;
}

void DO_Window::DrawLine(int x, int y, int x2, int y2)
{
	SDL_RenderDrawLine(rend, x, y, x2, y2);
}

void DO_Window::DrawPoint(int x, int y)
{
	SDL_RenderDrawPoint(rend, x, y);
}

void DO_Window::DrawRectangle(int x, int y, int x2, int y2, bool fill)
{
	SDL_Rect r = { x,y,x2,y2 };
	if (fill)
	{
		SDL_RenderFillRect(rend, &r);
	}
	else
	{
		SDL_RenderDrawRect(rend, &r);
	}
}

void DO_Window::SetDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(rend, r, g, b, a);
}

void DO_Window::GetDrawColor(short & r, short & g, short & b, short & a)
{
	Uint8 rr, gg, bb, aa;
	SDL_GetRenderDrawColor(rend, &rr, &gg, &bb, &aa);
	a = (short)aa; r = (short)rr; g = (short)gg; b = (short)bb;
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
