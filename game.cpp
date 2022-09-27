#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Screen dimensions
int WIDTH = 1280;
int HEIGHT = 720;

// Override base class with your custom functionality
class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		// Name your application
		sAppName = "Name Me";
	}

public:
    // Called once at the start
	bool OnUserCreate() override
	{

		return true;
	}

    // Called once per frame
	bool OnUserUpdate(float fElapsedTime) override
	{

		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(x % 256, y * 255, 0));
		return true;
	}
};



int main()
{
	Game game;
	if (game.Construct(WIDTH, HEIGHT, 1, 1))
		game.Start();
	return 0;
}