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
	short status = 0;//图片是以第几种方式加载

	DO_Window *win;

	DO_Image();
public:
	double angle;
	float zoom;
	short R = 255, G = 255, B = 255, A = 255;//颜色化通道，alpha（透明度通道）
	int width = 0, height = 0;
	SDL_PixelFormat *format = NULL;

	DO_Image(DO_Window *w) :image(NULL), angle(0), zoom(100.00), R(255), G(255), B(255), A(255), win(w){}

	/*从现有sdl纹理加载（不能修改像素）status = 1
	参数:p文件名*/
	bool Load_texture(SDL_Texture *); 

	/*获取静态图片（不能修改像素）status = 2
	参数:p文件名*/
	bool Load_static(char p[22]);

	/*获取动态图片（允许修改像素）,从文件中加载 status = 3
	参数:p文件名*/
	bool Load_dynamic(char p[22]);

	/*获取动态图片（允许修改像素）,创建一个指定大小的空IMAGE status = 4
	参数:x 横坐标，y 纵坐标*/
	bool Load_dynamic(int x,int y);

	/*加载成画布（不能修改像素），一开始是空的，可用SDL_SetRenderTarget操作 status = 5
	参数:x 横坐标，y 纵坐标*/
	bool Load_target(int x,int y);

	/*设置像素，只能操作 用Load_dynamic创建的IMAGE
	参数:x 横坐标，y 纵坐标 r、g、b、a 颜色通道
	注意坐标范围是(1-w,1-h)*/
	bool setPixel(int x, int y, short r, short g, short b, short a);

	/*获取像素，只能操作 用Load_dynamic创建的IMAGE
	参数:x 横坐标，y 纵坐标 r、g、b、a 颜色通道
	注意坐标范围是(1-w,1-h)*/
	bool getPixel(int x, int y, short &r, short &g, short &b, short &a);

	/*设置一堆像素，只能操作 用Load_dynamic创建的IMAGE
	参数:x 横坐标，y 纵坐标 r、g、b、a 颜色通道*/
	bool setPixels(std::function<void(int x, int y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a)>);

	/*在(x,y)位置绘图，注意，这个坐标是IMAGE的中心所在位置！不是左上角
	这里的(cx,cy)是旋转中心，跟绘图基准点无关！*/
	void Draw(int x, int y, int cx = -1, int cy = -1);
	                      
	SDL_Texture *gett();

	/*设置整体色调*/
	void setRGB(short r, short g, short b);

	/*设置整体透明度*/
	void setAlpha(short a);
	short getR();
	short getG();
	short getB();

	/*“点到线”，即像素的坐标系坐标转化为内存数组中的下标*/
	int PtoL(int x,int y);
	~DO_Image();
};