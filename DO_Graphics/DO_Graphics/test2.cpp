#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	DO_Window w(1000, 618, "dodou", "simhei.ttf", 32);
	DO_Image p(&w);
	p.Load("gg.png");
	
	//p.setPixel(233, 233, 255, 255, 0, 255);
	while (w.BeginDraw())
	{
		//w.SetWorkingImage(&p);
		w.SetDrawColor(255, 255, 255, 255);
		w.DrawLine(1, 1, 500, 500);
		//w.SetWorkingImage(NULL);
		p.Draw(0, 233);
		w.EndDraw();
	}
	return 0;
}