#include "DO_Graphics.h"
#include<cmath>
#include<iostream>
#include "SDL_syswm.h"
using namespace std;
int main2(int argc, char *argv[])
{
	DO_Window w(1000, 618, "dodou", "simhei.ttf", 32);
	DO_Image p(&w);
	DO_Image s(&w);
	DO_Image zt(&w);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(w.window, &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

	int cx = GetSystemMetrics(SM_CXFIXEDFRAME);
	int cy = GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);
	HRGN rgn = CreateEllipticRgn(0 + cx, 0 + cy, 200 + cx, 200 + cy);
	SetWindowRgn(hwnd, rgn, true);
	SetWindowPos(hwnd, 0, 0, 0 , 200, 200, 0);
	p.Load_static("ze.png");
	s.Load_static("gay.png");
	zt.Load_static("wr.png");
	
	double an = 0; 
	w.SetWorkingImage(NULL);
	//SDL_SetWindowPosition();
	//SDL_SetWindowShape();
	//SDL_GetWindowPosition();
	//SDL_SetWindowBrightness(w.window,2.33);
	//SDL_SetWindowOpacity(w.window,2.33);
	int x, y;

	//失效透明色键代码QAQ
	/*LONG nRet = ::GetWindowLong(hwnd, GWL_EXSTYLE);
	nRet = nRet | WS_EX_LAYERED;
	::SetWindowLong(hwnd, GWL_EXSTYLE, nRet);
	cout << SetLayeredWindowAttributes(hwnd, RGB(0, 255, 255), 123, LWA_COLORKEY);*/

	zt.setAlpha(0);
	DO_Text t; t.Init(&w, 32); t.addT(255, 255, 255, "-1S");
	DO_Text t2; t2.Init(&w, 15); t2.addT(255, 255, 255, "我喝水都要侮辱你的仙人:)");
	t2.setAlpha(0);
	while (w.BeginDraw())
	{
		w.SetDrawColor(0, 0, 0, 255);
		SDL_RenderClear(w.rend);
		//w.SetDrawColor(0, 255, 255, 255);
		//w.DrawRectangle(20, 20, 70, 70);
		an += 0.005;
		if (w.KeyDown("space"))an+=0.009;
		p.angle = an;
		s.angle = an;
		p.Draw(90, 80);
		s.Draw(90, 80);
		zt.Draw(80, 140);
		t.Draw(90, 80);
		t2.Draw(00, 30 + (an - 255)*0.5);
		if (an <= 255)
		{
			s.setAlpha(255 - an);
			t.setAlpha(255 - an);
			p.setAlpha(an);
		}
		else
		{
			zt.setAlpha(an - 255);
			p.setAlpha(255 * 2 - an);
			t2.setAlpha(an - 255);
			t2.setRGB(an - 233, an - 123, an - 255);
		}
		SDL_SetWindowPosition(w.window, an, an);
		SDL_GetWindowPosition(w.window, &x, &y);
		//cout << x << "       " << y << endl;
		w.EndDraw();
	}
	return 0;
}