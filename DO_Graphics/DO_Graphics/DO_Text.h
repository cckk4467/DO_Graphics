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
	short R, G, B, A;//��ɫ��ͨ����alpha��͸����ͨ����
	vector<SDL_Texture*> p;
	int length,
		size, size2;//Ŀ��ߴ磬ԭ�ߴ�

	char*localeToUTF8(char *src);

public:
	DO_Text() :font(NULL), length(0),size(0) {}
	/*��ʼ�������ڣ������ļ��������С*/
	bool Init(DO_Window *win_,  int siz);

	/*����ֶΣ�rgba��������ɫ��͸���ȣ�*/
	void addT(int r, int g, int b, char *ss, ...);

	/*�����ֶΣ�rgba��������ɫ��͸���ȣ� �Ḳ�ǵ�ԭ�е�����(��ʵ����init + addT)*/
	void setT(int r, int g, int b, char *ss, ...);

	/*��ָ��λ����Ⱦ*/
	void Draw(int x, int y);
	
	/*��������ɫ��*/
	void setRGB(short r, short g, short b);

	/*��������͸����*/
	void setAlpha(short a);

	short getR();
	short getG();
	short getB();
	/*�����ַ������ȣ����жΣ�*/
	int getlength();
	~DO_Text();
};