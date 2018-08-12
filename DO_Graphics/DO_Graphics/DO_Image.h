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

	/*获取静态图片（不能修改像素）
	参数:p文件名*/
	bool Load_static(char p[22]);

	/*获取动态图片（允许修改像素）,从文件中加载
	参数:p文件名*/
	bool Load_dynamic(char p[22]);

	/*获取动态图片（允许修改像素）,创建一个指定大小的空IMAGE
	参数:x 横坐标，y 纵坐标*/
	bool Load_dynamic(int x,int y);

	/*加载成画布（不能修改像素），一开始是空的，可用SDL_SetRenderTarget操作
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
	bool setPixels(std::function<void(int x, int y, Uint32 *pixel)>);

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