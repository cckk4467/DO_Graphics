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
	short status = 0;//ͼƬ���Եڼ��ַ�ʽ����

	DO_Window *win;

	DO_Image();
public:
	double angle;
	float zoom;
	short R = 255, G = 255, B = 255, A = 255;//��ɫ��ͨ����alpha��͸����ͨ����
	int width = 0, height = 0;
	SDL_PixelFormat *format = NULL;

	DO_Image(DO_Window *w) :image(NULL), angle(0), zoom(100.00), R(255), G(255), B(255), A(255), win(w){}

	/*������sdl������أ������޸����أ�status = 1
	����:p�ļ���*/
	bool Load_texture(SDL_Texture *); 

	/*��ȡ��̬ͼƬ�������޸����أ�status = 2
	����:p�ļ���*/
	bool Load_static(char p[22]);

	/*��ȡ��̬ͼƬ�������޸����أ�,���ļ��м��� status = 3
	����:p�ļ���*/
	bool Load_dynamic(char p[22]);

	/*��ȡ��̬ͼƬ�������޸����أ�,����һ��ָ����С�Ŀ�IMAGE status = 4
	����:x �����꣬y ������*/
	bool Load_dynamic(int x,int y);

	/*���سɻ����������޸����أ���һ��ʼ�ǿյģ�����SDL_SetRenderTarget���� status = 5
	����:x �����꣬y ������*/
	bool Load_target(int x,int y);

	/*�������أ�ֻ�ܲ��� ��Load_dynamic������IMAGE
	����:x �����꣬y ������ r��g��b��a ��ɫͨ��
	ע�����귶Χ��(1-w,1-h)*/
	bool setPixel(int x, int y, short r, short g, short b, short a);

	/*��ȡ���أ�ֻ�ܲ��� ��Load_dynamic������IMAGE
	����:x �����꣬y ������ r��g��b��a ��ɫͨ��
	ע�����귶Χ��(1-w,1-h)*/
	bool getPixel(int x, int y, short &r, short &g, short &b, short &a);

	/*����һ�����أ�ֻ�ܲ��� ��Load_dynamic������IMAGE
	����:x �����꣬y ������ r��g��b��a ��ɫͨ��*/
	bool setPixels(std::function<void(int x, int y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a)>);

	/*��(x,y)λ�û�ͼ��ע�⣬���������IMAGE����������λ�ã��������Ͻ�
	�����(cx,cy)����ת���ģ�����ͼ��׼���޹أ�*/
	void Draw(int x, int y, int cx = -1, int cy = -1);
	                      
	SDL_Texture *gett();

	/*��������ɫ��*/
	void setRGB(short r, short g, short b);

	/*��������͸����*/
	void setAlpha(short a);
	short getR();
	short getG();
	short getB();

	/*���㵽�ߡ��������ص�����ϵ����ת��Ϊ�ڴ������е��±�*/
	int PtoL(int x,int y);
	~DO_Image();
};