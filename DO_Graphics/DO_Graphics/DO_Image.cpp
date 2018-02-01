#include "DO_Image.h"
#include <cstring>
#include<iostream>
using namespace std;

bool DO_Image::Load_static(char p[22])
{
	image = IMG_LoadTexture(win->rend, p);

	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(image, 0, 0, &width, &height);
	static_ = true;
	format = SDL_GetWindowSurface(win->window)->format;
	return image != NULL;
}

bool DO_Image::Load(char p[22])
{
	format = SDL_GetWindowSurface(win->window)->format;

	SDL_Surface *sur1 = IMG_Load(p);

	SDL_Surface *sur = SDL_ConvertSurface(sur1, format, NULL);
	image = SDL_CreateTexture(win->rend, SDL_GetWindowPixelFormat(win->window), SDL_TEXTUREACCESS_STREAMING, sur->w, sur->h);

	void* mPixels;
	int mPitch;
	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	memcpy(mPixels, sur->pixels, sur->pitch * sur->h);

	SDL_UnlockTexture(image);

	mPixels = 0;
	width = sur->w;
	height = sur->h;
	SDL_FreeSurface(sur1);
	SDL_FreeSurface(sur);
	return image != NULL;
}

bool DO_Image::Load(int x, int y)
{
	image = SDL_CreateTexture(win->rend, SDL_GetWindowPixelFormat(win->window), SDL_TEXTUREACCESS_TARGET, x, y);

	return false;
}

bool DO_Image::setPixel(int x, int y, short r, short g, short b, short a)
{
	if (static_)return false;
	if (x > width || y > height)return false;

	void* mPixels;
	int mPitch;

	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	Uint32 *p = (Uint32*)mPixels;
	p[x - 1 + (y - 1) * width] = SDL_MapRGBA(format, r, g, b, a);

	SDL_UnlockTexture(image);
	return true;
}

bool DO_Image::getPixel(int x, int y, short &r, short &g, short &b, short &a)
{
	if (static_)return false;
	if (x > width || y > height)return false;

	void* mPixels;
	int mPitch;

	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	Uint32 *p = (Uint32*)mPixels;

	Uint8 rr, gg, bb, aa;
	SDL_GetRGBA(*p, format, &rr, &gg, &bb, &aa);

	a = (short)aa; r = (short)rr; g = (short)gg; b = (short)bb;
	SDL_UnlockTexture(image);
	return true;
}

bool DO_Image::setPixels(std::function<void(int x, int y, Uint32 *pixel)> solve)
{
	void* mPixels;
	Uint32 *copyP = new Uint32[width * height];
	int mPitch;

	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	memcpy(copyP, mPixels, width * height * 4);

	for (int i = 1; i <= width; i++) 

		for (int j = 1; j <= height; j++)
		{
			solve(i, j, copyP);
		}

	memcpy(mPixels, copyP, width * height * 4);

	SDL_UnlockTexture(image);
	delete []copyP;
	return false;
}

void DO_Image::Draw(int x, int y, int cenx, int ceny)
{
	SDL_Rect r;
	SDL_QueryTexture(image, 0, 0, &r.w, &r.h);
	r.x = x - r.w*zoom / 200.0;
	r.y = y - r.h*zoom / 200.0;
	r.w *= zoom / 100.0; r.h *= zoom / 100.0;

	SDL_Point po = { cenx,ceny };
	if (cenx == ceny && cenx == -1)
		SDL_RenderCopyEx(win->rend, image, NULL, &r, angle, 0, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(win->rend, image, NULL, &r, angle, &po, SDL_FLIP_NONE);
}

SDL_Texture * DO_Image::gett()
{
	return image;
}

void DO_Image::setRGB(short r, short g, short b)
{
	SDL_SetTextureColorMod(image, r, g, b);
	R = r;
	G = g;
	B = b;
}

void DO_Image::setAlpha(short a)
{
	SDL_SetTextureAlphaMod(image, a);
	A = a;
}

short DO_Image::getR()
{
	return R;
}

short DO_Image::getG()
{
	return G;
}

short DO_Image::getB()
{
	return B;
}

int DO_Image::PtoL(int x, int y)
{
	if (static_) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DO_Image::PtoL", "static_ = true",  win->window); return -1; }
	if (x > width || y > height) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
															"DO_Image::PtoL", 
															"x y > limit", win->window); return -1; }
	return x - 1 + (y - 1) * width;
}

DO_Image::~DO_Image()
{
	SDL_DestroyTexture(image);
}
