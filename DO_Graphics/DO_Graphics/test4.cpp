#include "time.h"
#include "DO_Graphics.h"

using namespace std;
int main(int argc, char *argv[])
{
	DO_Window win(640, 480, "µãÄ£ºý", "simhei.ttf", 16);
	DO_Text t; t.Init(&win, 32);
	DO_Image ima(&win);
	DO_Image bj(&win); DO_Image pic(&win);
	DO_Image po(&win); po.Load_dynamic(10,10);
	bj.Load_target(300, 300); pic.Load_dynamic("gg.png");
	DO_Image mo(&win);
	mo.Load_static("objects.png");
	ima.Load_dynamic(300,300);
	srand(time(0));
	//for(int i=1;i<=1000;i++)ima.setPixel(1+rand()%300, 1+rand()%300, rand()%256, 0xff, 0xff, 0xff);
	short r, g, b, a=0;
	double alpha = 0;
	//mo.setPixel(1,1,0,255,0,255);
	//SDL_SetTextureBlendMode(mo.gett(), SDL_BLENDMODE_MOD);
	po.setPixel(3,3,255,245,255,0);
	while (win.BeginDraw())
	{
		if (win.KeyDown("space"))alpha += 0.01;
		//pic.setAlpha(a);
		mo.setAlpha(alpha);
		mo.Draw(250,250);
		po.setPixel(3, 3, 255, 245, 255, alpha);
		pic.Draw(150,150);
		po.Draw(50, 50);

		//win.SetDrawColor(255,255,0,alpha);
		win.DrawLine(0, 0, 100, alpha);

		t.Draw(0,0);
		
		win.EndDraw();
	}
	//SDL_PIXELFORMAT_RGB888
	return 0;
}