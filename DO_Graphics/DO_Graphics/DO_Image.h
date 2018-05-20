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
	bool static_ = false;//ͼƬ�Ƿ�̬

	DO_Window *win;
	DO_Image();
public:
	double angle;
	float zoom;
	short R, G, B, A;//��ɫ��ͨ����alpha��͸����ͨ����
	int width, height;
	SDL_PixelFormat *format;

	DO_Image(DO_Window *w) :image(NULL), angle(0), zoom(100.00), R(255), G(255), B(255), A(255), win(w){}

	bool Load_static(char p[22]);//��ȡ��̬ͼƬ�������޸����أ�
	bool Load(char p[22]);//��ȡ��̬ͼƬ�������޸����أ�
	bool Load(int x,int y);//���سɻ�����һ��ʼ�ǿյģ�����SDL_SetRenderTarget����
	bool setPixel(int x, int y, short r, short g, short b, short a);//���ز���
	bool getPixel(int x, int y, short &r, short &g, short &b, short &a);
	bool setPixels(std::function<void(int x, int y, Uint32 *pixel)>);

	void Draw(int x, int y, int cx = -1, int cy = -1);//����Ҫ�ĳɷ�װ����DO_Window
	                      //�����(cx,cy)����ת���ģ�����ͼ��׼���޹أ�
	SDL_Texture *gett();

	void setRGB(short r, short g, short b);//����ɫ��
	void setAlpha(short a);//����͸����
	short getR();
	short getG();
	short getB();
	int PtoL(int x,int y);//���㵽�ߡ��������ص�����ϵ����ת��Ϊ�ڴ������е��±�
	~DO_Image();
};