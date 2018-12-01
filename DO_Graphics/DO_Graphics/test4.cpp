#include "time.h"
#include "DO_Graphics.h"
#include <iostream>
#include <cmath>
#include <bitset>
#define PI 3.1415926
using namespace std;
int cx=150, cy=150;
bitset<300 * 300> bj;
int gay(DO_Image *a,int x, int y,float dis)
{
	if (bj[a->PtoL(x, y)])return 0;
	bj[a->PtoL(x, y)] = 1;
	float dist = hypot(150 - x, 150 - y);
	short r, g, b, al;
	a->getPixel(cx, cy, r, g, b, al); al = 255;
	a->setPixel(x, y, r, g, b, (float)al*max(1 - dist / dis, 0));
	if (dist >= dis)return 0;
	gay(a, x + 1, y, dis);
	gay(a, x, y + 1, dis);
	gay(a, x - 1, y, dis);
	gay(a, x, y - 1, dis);
	return 0;
}
int main4(int argc, char *argv[])
{
	DO_Window win(640, 480, "点模糊", "simhei.ttf", 16);
	DO_Image ima(&win);
	ima.Load_dynamic(30, 30);
	srand(time(0));
	double r = ima.getR(), g = ima.getG(), b = ima.getB(), a=1;
	bj.reset();
	ima.setPixels([&](int x, int y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a)
	{
		r = 0 * max(1 - hypot(x - 15, y - 15) / 16, 0);
		g = 255;
		b = 255;
		a = 255.0*max(1 - hypot(x - 15, y - 15) / 16, 0);
	});//这就是点模糊我能写的最高效率的代码了，cpu在循环体跑20fps哈哈哈，配合setrgb、setalpha可以写个不错的粒子系统了
	//gay(&ima, 150, 150, 100);
	while (win.BeginDraw())
	{
		if (win.KeyDown("space"))a+=0.01;
		//ima.setPixel(150, 150, 255, 255, 255, a);
		//for (int i = 1; i <= a; i+=10)ima.Draw(200+i*cos(a/100),200-i*sin(a/100));
		//ima.setAlpha(a);
		ima.Draw(200, 200);
		ima.setRGB(255,255-a,255-1);
		//ima.zoom = a;
		win.EndDraw();
	}
	//SDL_PIXELFORMAT_RGB888
	return 0;
}