#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm> 
#include <random>    
#include <chrono>   

#define PI 3.14159265

using namespace std;

static string IMG_FOLDER = "img\\";
static string CONFIG_FOLDER = "config\\";
static string SOUND_FOLDER = "sound\\";
static string DISTRICT_FOLDER = "Districts\\";
static string STATION_FOLDER = "Stations\\";
static string PLAYER_FOLDER = "Players\\";
static string QUESTION_FOLDER = "questions\\";
static string DICE_FOLDER = "dice\\";
static string TURN_FOLDER = "Turn\\";
static string WINSCREEN_FOLDER = "WinScreen\\";
static string MENU_FOLDER = "Menu\\";
static string BUTTON_FOLDER = "Buttons\\";
static string FONT_FOLDER = "font\\";
static string FIELD_FOLDER = "fields\\";
static string TITLESCREEN_FOLDER = "TitleScreen\\";
static string TAXES_FOLDER = "Taxes\\";

struct int2
{
	int x;
	int y;

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(int2 b) 
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(int2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(int2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	int2 operator*(int2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this; //Returns instance of the current class (After the modifications)
	}

	int2 operator/(int2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator==(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct float2
{
	//!!!IMPORTANT!!!
	float x;
	float y; 

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(float2 b)
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(float2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(float2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	float2 operator*(float2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this; //Returns instance of the current class (After the modifications)
	}

	float2 operator/(float2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(float2 a)
	{
		if (x == a.x && y == a.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator==(float2 a)
	{
		if (x == a.x && y == a.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct Drawable 
{
	SDL_Texture* texture;
	SDL_Rect rect; //dstRect;
};

struct DrawableSrcRect : Drawable
{
	SDL_Rect srcRect;
};
struct DrawableWithOpacity : Drawable
{
	int opacity = 0;
	int changePerFrame = 0;
};
struct DrawableWithRotation : Drawable
{
	double angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};


enum SOUND 
{
	BACKGORUND_MUSIC
};

enum COLOR
{
	NONE = 0,
	DARK = 1,
	LIGHT = 2,
	BLUE = 3,
	RED = 4,
	ORANGE = 5,
	PINK = 6,
	YELLOW = 7,
	LIGHT_GREEN = 8,
	DARK_CYAN = 9,
	PURPLE = 10
	
};