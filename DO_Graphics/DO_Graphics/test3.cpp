#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	DO_Window w(1000, 618, "dodou", "simhei.ttf", 32);
	DO_Image p(&w);
	p.Load_dynamic("1.png");

	DO_Image light(&w);
	light.Load_dynamic(100,100);
	//w.SetWorkingImage(&light);
	w.SetDrawColor(127, 127, 5, 255);
	/*for (int i = 0; i <= 1000; i++)
		for (int j = 0; j <= 1000; j++)
			w.DrawPoint(i,j);*/
	light.setPixels([&](int x, int y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a) {
		r = 0;
		b = 127;
		g = 127;
		a = 255;
	});
	w.SetWorkingImage(NULL);
	w.SetDrawColor(0,0,0,255);
	//SDL_SetTextureBlendMode(light.gett(), SDL_BLENDMODE_MOD);

	//p.setPixel(233, 233, 255, 255, 0, 255);
	while (w.BeginDraw())
	{
		
		p.Draw(200, 200);
		light.Draw(200, 200);
		w.EndDraw();
	}
	return 0;
}