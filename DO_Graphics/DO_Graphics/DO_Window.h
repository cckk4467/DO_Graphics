#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_image.lib")
//Declare
class DO_Image;

class DO_Window
{
private:
	Uint64 ds, fs;//计算fps的辅助变量
	int FPS,  //保存刷新率
		count;//FPS计数器
	float DT;//1/FPS 实时记录
	const Uint8 *keystate;
	DO_Window() :window(NULL), rend(NULL), font(NULL) {}
public:
	SDL_Window *window;
	SDL_Renderer *rend;
	SDL_Event even;
	TTF_Font *font;
	int font_s;//读入字体大小

	DO_Window(int w, int h, char *title, char *ttf, int size_font);
	
	bool BeginDraw();
	void EndDraw();
	void SetZoom(float sx, float sy);
	int getFPS();//获取屏幕刷新率
	float getDT();//获取即时屏幕刷新率倒数,即两帧之间的时间差
	bool KeyDown(char *n);

	//Render几何绘图
	bool SetWorkingImage(DO_Image *image);
	/*asdasd*/
	void DrawLine(int x, int y, int x2, int y2);
	void DrawPoint(int x, int y);
	void DrawRectangle(int x, int y, int x2, int y2, bool fill = true);
	void SetDrawColor(int r,int g,int b,int a);
	void GetDrawColor(short &r, short &g, short &b, short &a);
	~DO_Window();
};