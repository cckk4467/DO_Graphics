#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
using namespace std;
int main3(int argc, char *argv[])
{
	DO_Window w(1000, 618, "dodou", "simhei.ttf", 32);
	DO_Image p(&w);
	p.Load_dynamic("gg.png");

	//p.setPixel(233, 233, 255, 255, 0, 255);
	while (w.BeginDraw())
	{
		//w.SetWorkingImage(&p);
		w.SetDrawColor(255, 255, 255, 255);
		w.DrawLine(1, 1, 500, 500);
		//w.SetWorkingImage(NULL);
		p.Draw(0, 233);
		SDL_Rect r = { 0, 0, 100, 100 };
		//SDL_RenderDrawRect(w.rend, &r);
		w.DrawRectangle(0, 0, 100, 100, true);
		w.EndDraw();
	}
	return 0;
}