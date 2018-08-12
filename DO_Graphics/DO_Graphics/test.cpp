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
float f3(float x, float a)
{
	auto f = [](float x, float a)->float { return cos(a * PI * (x - 0.5 + 1 / (2 * a))); };
	return 1 / f(0, a) * -f(x, a) / 2 + 0.5;
}
int main1(int argc, char *argv[])
{

	DO_Window win(1000,618,"dodou", "simhei.ttf", 32);

	/*DO_Text i;
	i.Init(&win, 32);
	i.addT(0xff, 0xff, 0xff, "共产主义好！"); i.addT(0xff, 0xff, 0xff, "个球");*/
	DO_Image i(&win);
	cout << i.Load_dynamic("gay.png") << endl;

	DO_Image j(&win);
	j.Load_target(300, 300);
	cout << SDL_SetRenderTarget(win.rend, j.gett()) << endl;
	i.zoom = 50;
	i.Draw(233,233);
	SDL_SetRenderTarget(win.rend, NULL);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	double y = 0.0;
	while (win.BeginDraw())
	{
		//i.setAlpha(y);
		j.Draw(f3(y,1.2)*100, 233); 
		if (win.KeyDown("h"))y += win.getDT();
		if (win.KeyDown("r"))y = 0;
		//cout << f3(y, 1.5) << " " <<  y << endl; 
		if (y > 1)y = 1.0001;
		SDL_SetRenderDrawColor(win.rend, 233, 23, 23, 23);
		win.EndDraw();
	}

	return 0;
}