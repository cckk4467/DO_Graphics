#include "DO_Image.h"
#include <cstring>
#include<iostream>
using namespace std;
#define ShowError(x,y) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, x, y,  win->window)

bool DO_Image::Load_texture(SDL_Texture *ye)
{
	if (image != NULL)return false;
	image = ye;
	Uint32 form;
	SDL_QueryTexture(image, &form, 0, &width, &height);
	format = SDL_AllocFormat(form);

	status = 1;
	return true;
}

bool DO_Image::Load_static(char p[22])
{
	if (image != NULL)return false;
	image = IMG_LoadTexture(win->rend, p);
	if (image == NULL)ShowError("DO_Image::Load_static", "image==NULL");
	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(image, 0, 0, &width, &height);
	status = 2;
	format = SDL_GetWindowSurface(win->window)->format;
	return image != NULL;
}

bool DO_Image::Load_dynamic(char p[22])
{
	if (image != NULL)return false;
	format = SDL_GetWindowSurface(win->window)->format;

	SDL_Surface *sur1 = IMG_Load(p);
	if (sur1 == NULL) { ShowError("Load_dynamic", "failed load"); return 0;}

	SDL_Surface *sur = SDL_ConvertSurface(sur1, format, NULL);
	image = SDL_CreateTexture(win->rend, format->format, SDL_TEXTUREACCESS_STREAMING, sur->w, sur->h);
	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);

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
	status = 3;
	return image != NULL;
}

bool DO_Image::Load_dynamic(int x, int y)
{
	if (image != NULL)return false;

	format = SDL_GetWindowSurface(win->window)->format;
	image = SDL_CreateTexture(win->rend, format->format, SDL_TEXTUREACCESS_STREAMING, x, y);
	width = x;
	height = y;
	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);

	status = 4;
	return true;
}

bool DO_Image::Load_target(int x, int y)
{
	if (image != NULL)return false;

	format = SDL_GetWindowSurface(win->window)->format;
	image = SDL_CreateTexture(win->rend, format->format, SDL_TEXTUREACCESS_TARGET, x, y);
	width = x;
	height = y;
	status = 5;
	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
	return true;
}

bool DO_Image::setPixel(int x, int y, short r, short g, short b, short a)
{
	if (status != 3 && status != 4)return false;
	if (x > width || y > height || x < 1 || y < 1) { ShowError("setPixel", "range is over [1-width,1-heigh]"); return false; }

	void* mPixels;
	int mPitch;

	int de = SDL_LockTexture(image, NULL, &mPixels, &mPitch);
	if (de == -1)exit(0);

	Uint32 *p = (Uint32*)mPixels;
	p[x - 1 + (y - 1) * width] = SDL_MapRGBA(format, r, g, b, a);
	
	SDL_UnlockTexture(image);
	return true;

}

bool DO_Image::getPixel(int x, int y, short &r, short &g, short &b, short &a)
{
	if (status != 3 && status != 4)return false;
	if (x > width || y > height || x < 1 || y < 1) { ShowError("getPixel", "range is over [1-width,1-heigh]"); return false; }

	void* mPixels;
	int mPitch;

	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	Uint32 *p = (Uint32*)mPixels;

	Uint8 rr, gg, bb, aa;
	Uint32 ge = p[PtoL(x, y)];
	SDL_GetRGBA(ge, format, &rr, &gg, &bb, &aa);

	a = (short)aa; r = (short)rr; g = (short)gg; b = (short)bb;
	SDL_UnlockTexture(image);
	return true;
}

bool DO_Image::setPixels(std::function<void(int x, int y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a)> solve)
{
	if (status != 3 && status != 4)return false;

	void* mPixels;
	Uint32 *copyP = new Uint32[width * height];
	int mPitch;
	Uint8 r = 0, g = 0, b = 0, a = 0;

	SDL_LockTexture(image, NULL, &mPixels, &mPitch);

	memcpy(copyP, mPixels, width * height * 4);

	Uint32 *p = (Uint32*)mPixels;

	for (int i = 1; i <= width; i++) 

		for (int j = 1; j <= height; j++)
		{
			SDL_GetRGBA(p[PtoL(i, j)], format, &r, &g, &b, &a);
			solve(i, j, r, g, b, a);
			copyP[PtoL(i, j)] = SDL_MapRGBA(format, r, g, b, a);
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
	r.x = x - r.w * zoom / 200.0;
	r.y = y - r.h * zoom / 200.0;
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
	int ee = SDL_SetTextureAlphaMod(image, a);
	if (ee == -1)ShowError("SetAlpha Error","Do you use Load(¡°x¡±) to load a piicture?");
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

inline int DO_Image::PtoL(int x, int y)
{
	if (status != 3 && status != 4) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "DO_Image::PtoL", "static_ = true",  win->window); return -1; }
	if (x > width || y > height) { SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
															"DO_Image::PtoL", 
															"x y > limit", win->window); return -1; }
	return x - 1 + (y - 1) * width;
}

DO_Image::~DO_Image()
{
	SDL_DestroyTexture(image);
}
