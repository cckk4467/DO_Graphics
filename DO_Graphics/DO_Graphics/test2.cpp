#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	DO_Window w(1000, 618, "dodou", "simhei.ttf", 32);
	DO_Image p(&w);
	p.Load(100, 100);
	w.SetWorkingImage(&p);
	w.SetDrawColor(255, 255, 255, 255);
	w.DrawRectangle(0, 0, 100, 100); 
	w.SetDrawColor(0, 255, 0, 255);
	w.DrawRectangle(30, 30, 60, 60, 0);
	
	double an = 0; 
	w.SetWorkingImage(NULL);
	while (w.BeginDraw())
	{
		w.SetDrawColor(0, 0, 0, 255);
		SDL_RenderClear(w.rend);
		an += 0.001;
		p.angle = an;
		p.Draw(100, 100);
		p.setRGB(123, 123, 123);
		w.EndDraw();
	}
	return 0;
}