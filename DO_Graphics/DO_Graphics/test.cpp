#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
using namespace std;
#define PI 3.14159
float f(float x)
{
	return (1 - cos(x * 1 * PI) * (1 - PI)) + x;
}
float f2(float x)
{
	return x - sin(x * 2 * PI) / (2 * PI);
}
int main(int argc, char *argv[])
{

	DO_Window win;
	win.Init(1000,618,"dodou", "simhei.ttf", 32);

	/*DO_Text i;
	i.Init(&win, 32);
	i.addT(0xff, 0xff, 0xff, "共产主义好！"); i.addT(0xff, 0xff, 0xff, "个球");*/
	DO_Image i(&win);
	cout << i.Load("gay.png") << endl;

	DO_Image j(&win);
	j.Load(300, 300);
	cout << SDL_SetRenderTarget(win.rend, j.gett()) << endl;
	i.zoom = 50;
	i.Draw(233,233);
	SDL_SetRenderTarget(win.rend, NULL);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	float y = 255;
	while (win.BeginDraw())
	{
		//i.setAlpha(y);
		y -= win.getDT() * 10;
		j.Draw(y, 233); y += win.getDT()*100;
		SDL_SetRenderDrawColor(win.rend,233,23,23,23);
		win.EndDraw();
	}

	return 0;
}