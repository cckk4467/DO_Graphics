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
	Uint64 ds, fs;//����fps�ĸ�������
	int FPS,  //����ˢ����
		count;//FPS������
	float DT;//1/FPS ʵʱ��¼
	const Uint8 *keystate;
	DO_Window() :window(NULL), rend(NULL), font(NULL) {}
public:
	SDL_Window *window;
	SDL_Renderer *rend;
	SDL_Event even;
	TTF_Font *font;
	int font_s;//���������С

	DO_Window(int w, int h, char *title, char *ttf, int size_font);
	
	bool BeginDraw();
	void EndDraw();
	void SetZoom(float sx, float sy);
	int getFPS();//��ȡ��Ļˢ����
	float getDT();//��ȡ��ʱ��Ļˢ���ʵ���,����֮֡���ʱ���
	bool KeyDown(char *n);

	//Render���λ�ͼ
	bool SetWorkingImage(DO_Image *image);
	/*asdasd*/
	void DrawLine(int x, int y, int x2, int y2);
	void DrawPoint(int x, int y);
	void DrawRectangle(int x, int y, int x2, int y2, bool fill = true);
	void SetDrawColor(int r,int g,int b,int a);
	void GetDrawColor(short &r, short &g, short &b, short &a);
	~DO_Window();
};