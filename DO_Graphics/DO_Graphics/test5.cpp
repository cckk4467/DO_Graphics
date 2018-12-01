#include "time.h"
#include "DO_Graphics.h"
#include <iostream>
#include <cmath>
#include <bitset>
#define PI 3.1415926
using namespace std;
float get_distance(SDL_Point p1, SDL_Point p2)
{
	int dist_x = p2.x - p1.x;
	int dist_y = p2.y - p1.y;

	float distance = SDL_sqrt(dist_x*dist_x + dist_y*dist_y);

	return distance;
}
/*网上抄的生成一种超圆超无违和感的粒子Texture的算法:)*/
SDL_Texture* create_glow_ball(SDL_Renderer* renderer, int radius, int r, int g, int b, int dim)
{
	float relative_dist = 0;
	float distance = 0;
	int alpha = 0;

	SDL_Point p = { 0, 0 };
	SDL_Point p_mid = { radius, radius };
	SDL_Texture* texture = NULL;

	if (dim < 0)
	{
		dim = 4.0;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, radius * 2, radius * 2);
	if (!texture)
	{
		throw SDL_GetError();
	}

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	//HUOM!!! JOS RENDERBLENDMODE ON PÄÄLLÄ, HOHTOPALLON LAATU HEIKKENEE

	for (int y = 0; y < 2 * radius; y++)
	{
		for (int x = 0; x < 2 * radius; x++)
		{
			p.x = x;
			p.y = y;

			distance = get_distance(p, p_mid);

			if (distance <= radius)
			{
				relative_dist = distance / radius*dim + 0.5;
				alpha = 255 / (relative_dist*relative_dist) / 4;
			}
			else
			{
				alpha = 0;
			}

			SDL_SetRenderDrawColor(renderer, r, g, b, alpha);

			if (SDL_RenderDrawPoint(renderer, x, y) != 0)
			{
				throw SDL_GetError();
			}
		}
	}

	SDL_SetRenderTarget(renderer, NULL);

	return texture;
}
double cloudx[300], cloudy[300], alp[300],ang[300];
int js = 0;
int main5(int argc, char *argv[])
{
	DO_Window win(640, 480, "点模糊", "simhei.ttf", 16);
	DO_Image ima(&win);
	srand(time(0));
	//ima.Load_texture(create_particle(win.rend,255,255,255,255,20));
	double a = 0.001;
	//ima.Load_static("smoke.png");
	ima.Load_texture(create_glow_ball(win.rend,255,128,128,128,1));
	win.SetDrawColor(0,0,0,255);


	for(int o=1;o<200;o++)
	{
		cloudx[js] = 200 + rand() % 100;
		cloudy[js] = 200 + rand() % 100;
		alp[js] = 10 + rand() % 10;
		ang[js++] = o * 18 / 180.0 * PI;
	}
	ima.setRGB(128, 128, 128);
	while (win.BeginDraw())
	{
		if (win.KeyDown("space"))a += 0.001;
		for (int i = 0; i < js; i++)
		{
			ima.setAlpha(alp[i]);
			ima.angle += 0.0001*(int)(rand()%10);
			ima.Draw(cloudx[i], cloudy[i]);
			cloudx[i] += 0.009 * cos(ang[i]);
			cloudy[i] -= 0.009 * sin(ang[i]);
			if (win.KeyDown("space"))ang[i] += 0.001;
			if (win.KeyDown("D"))alp[i] += 0.1;
		}

		win.EndDraw();
	}
	//SDL_PIXELFORMAT_RGB888
	return 0;
}