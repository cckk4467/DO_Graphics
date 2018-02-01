#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <windows.h>
using std::vector;
#include "DO_Window.h"
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")

class DO_Text
{
private:
	SDL_Texture *image;
	DO_Window *win;
	TTF_Font *font;
	double angle;
	short R, G, B, A;//颜色化通道，alpha（透明度通道）
	vector<SDL_Texture*> p;
	int length,
		size, size2;//目标尺寸，原尺寸

	char*localeToUTF8(char *src);

public:
	DO_Text() :font(NULL), length(0),size(0) {}
	bool Init(DO_Window *win_,  int siz);//初始化，窗口，字体文件，字体大小
	void addT(int r, int g, int b, char *ss, ...);//添加段，rgba（字体颜色，透明度）
	void Draw(int x, int y);//在指定位置渲染
	
	void setRGB(short r, short g, short b);//整体色调
	void setAlpha(short a);//整体透明度
	short getR();
	short getG();
	short getB();
	int getlength();//返回字符串长度（所有段）
	~DO_Text();
};