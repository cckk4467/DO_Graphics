#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <functional>
#include "DO_Window.h"
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

class DO_Image
{
private:
	SDL_Texture *image;
	bool static_ = false;//图片是否静态

	DO_Window *win;
	DO_Image();
public:
	double angle;
	float zoom;
	short R, G, B, A;//颜色化通道，alpha（透明度通道）
	int width, height;
	SDL_PixelFormat *format;

	DO_Image(DO_Window *w) :image(NULL), angle(0), zoom(100.00), R(255), G(255), B(255), A(255), win(w){}

	bool Load_static(char p[22]);//获取静态图片（不能修改像素）
	bool Load(char p[22]);//获取动态图片（允许修改像素）
	bool Load(int x,int y);//加载成画布，一开始是空的，用于SDL_SetRenderTarget操作
	bool setPixel(int x, int y, short r, short g, short b, short a);//像素操作
	bool getPixel(int x, int y, short &r, short &g, short &b, short &a);
	bool setPixels(std::function<void(int x, int y, Uint32 *pixel)>);

	void Draw(int x, int y, int cx = -1, int cy = -1);//这里要改成封装过的DO_Window
	                      //这里的(cx,cy)是旋转中心，跟绘图基准点无关！
	SDL_Texture *gett();

	void setRGB(short r, short g, short b);//整体色调
	void setAlpha(short a);//整体透明度
	short getR();
	short getG();
	short getB();
	int PtoL(int x,int y);//“点到线”，即像素的坐标系坐标转化为内存数组中的下标
	~DO_Image();
};