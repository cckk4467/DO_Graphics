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
	bool Init(DO_Window *win_,  int siz);//��ʼ�������ڣ������ļ��������С
	void addT(int r, int g, int b, char *ss, ...);//��ӶΣ�rgba��������ɫ��͸���ȣ�
	void Draw(int x, int y);//��ָ��λ����Ⱦ
	
	void setRGB(short r, short g, short b);//����ɫ��
	void setAlpha(short a);//����͸����
	short getR();
	short getG();
	short getB();
	int getlength();//�����ַ������ȣ����жΣ�
	~DO_Text();
};