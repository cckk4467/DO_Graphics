#include "DO_Text.h"
#include <stdarg.h>

bool DO_Text::Init(DO_Window * win_, int siz)
{
	if (p.size())
	{
		for (auto i = p.begin(); i != p.end(); i++)
		{
			SDL_DestroyTexture(*i);
		}

		p.clear();
	}

	win = win_;
	font = win->font;
	size2 = win->font_s;
	size = siz;
	return font!=NULL;
}

void DO_Text::addT(int r, int g, int b, char *ss, ...)
{
	char buff[128] = "";
	va_list    arglist;
	va_start(arglist, ss);
	_vsnprintf_s(buff, sizeof(buff), ss, arglist);
	va_end(arglist);

	SDL_Texture *t;
	SDL_Color col = { r,g,b };
	SDL_Surface *s = TTF_RenderUTF8_Blended(font, localeToUTF8(buff), col);
	t = SDL_CreateTextureFromSurface(win->rend, s);
	p.push_back(t);
	length += strlen(ss);
	SDL_FreeSurface(s);
}

void DO_Text::setT(int r, int g, int b, char * ss, ...)
{
	if (p.size())
	{
		for (auto i = p.begin(); i != p.end(); i++)
		{
			SDL_DestroyTexture(*i);
		}

		p.clear();
	}

	char buff[128] = "";
	va_list    arglist;
	va_start(arglist, ss);
	_vsnprintf_s(buff, sizeof(buff), ss, arglist);
	va_end(arglist);

	SDL_Texture *t;
	SDL_Color col = { r,g,b };
	SDL_Surface *s = TTF_RenderUTF8_Blended(font, localeToUTF8(buff), col);
	t = SDL_CreateTextureFromSurface(win->rend, s);
	p.push_back(t);
	length += strlen(ss);
	SDL_FreeSurface(s);
}

void DO_Text::Draw(int x, int y)
{
	int xx = x;
	SDL_Rect rec;
	rec.y = y;
	for (auto i = p.begin(); i != p.end(); i++)
	{
		rec.x = xx;
		SDL_QueryTexture(*i, 0, 0, &rec.w, &rec.h);
		rec.w *= (float)size / size2;   rec.h *= (float)size / size2;
		SDL_RenderCopy(win->rend, *i, 0, &rec);
		xx += rec.w + TTF_FontHeight(font) / 25;
	}
}

char * DO_Text::localeToUTF8(char * src)
{
	char *buf = NULL;
	if (buf) {
		free(buf);
		buf = NULL;
	}
	wchar_t *unicode_buf;
	int nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
	unicode_buf = (wchar_t*)malloc((nRetLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);
	nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
	buf = (char*)malloc(nRetLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);
	free(unicode_buf);
	return buf;
}

void DO_Text::setRGB(short r, short g, short b)
{
	for (SDL_Texture *i : p)
		SDL_SetTextureColorMod(i, r, g, b);
	R = r;
	G = g;
	B = b;
}

void DO_Text::setAlpha(short a)
{
	for (SDL_Texture *i : p)
		SDL_SetTextureAlphaMod(i, a);
	A = a;
}

short DO_Text::getR()
{
	return R;
}

short DO_Text::getG()
{
	return G;
}

short DO_Text::getB()
{
	return B;
}

int DO_Text::getlength()
{
	return length;
}

DO_Text::~DO_Text()
{
	for (auto i = p.begin(); i != p.end(); i++)
	{
		SDL_DestroyTexture(*i);
	}

	p.clear();
}
