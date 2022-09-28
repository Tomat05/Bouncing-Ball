#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

class Ball {
    public:
        float ballY = 50;
        float ballX = 50;
        float ballSpeedY = 300;
        float ballSpeedX = 300;
};

const int NUMBALLS = 10;
Ball balls[NUMBALLS];


class Game : public olc::PixelGameEngine {
 public:
	Game() { sAppName = "Ball lol"; }

 private:
	float timer = 0;
	int frames = 0;
	int fps;

	// float ballY = 50;
    // float ballX = 50;
    // float ballSpeedY = 300;
    // float ballSpeedX = 300;

 public:
	bool OnUserCreate() override {
        for (int i = 0; i < NUMBALLS; i++)
        {
            balls[i].ballSpeedX = balls[i].ballSpeedX + (rand() % 200 + 1);
            balls[i].ballSpeedY = balls[i].ballSpeedY + (rand() % 200 + 1);
        }
               
    	return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
    	timer += fElapsedTime;
    	frames++;
    	if (timer > 1.0) {
      		fps = frames;
      		frames = 0;
      		timer -= 1;
    	}

    	processes();
    	outputs();

    	if (GetKey(olc::Key::ESCAPE).bPressed) {
    		return false;
    	} else {
      		return true;
    	}
	}

	void processes() {
        for (int i = 0; i < NUMBALLS; i++)
        {
            balls[i].ballY += balls[i].ballSpeedY * GetElapsedTime();
		    balls[i].ballX += balls[i].ballSpeedX * GetElapsedTime(); 

		    if (balls[i].ballY >= HEIGHT - 35 || balls[i].ballY <= 35) {
			    balls[i].ballSpeedY = -balls[i].ballSpeedY;
		    }

    	    if (balls[i].ballX >= WIDTH - 35 || balls[i].ballX <= 35) {
        	    balls[i].ballSpeedX = -balls[i].ballSpeedX;
    	    }
        }
  	}

  	void outputs() {
    	SetPixelMode(olc::Pixel::NORMAL);

    	Clear(olc::BLACK);

        for (int i = 0; i < NUMBALLS; i++)
        {
            FillCircle(balls[i].ballX, balls[i].ballY, 20, olc::RED);
        }

    	DrawLine(15, 15, WIDTH - 15, 15, olc::WHITE);
    	DrawLine(WIDTH - 15, 15, WIDTH - 15, HEIGHT - 15, olc::WHITE);
    	DrawLine(WIDTH - 15, HEIGHT - 15, 15, HEIGHT - 15, olc::WHITE);
    	DrawLine(15, HEIGHT - 15, 15, 15, olc::WHITE);

    	if (fps > 0) {
      		auto fpsPosition = olc::vi2d(10, 10);
      		DrawStringDecal(fpsPosition, "FPS " + std::to_string(fps));
    	}
  	}

  	bool OnUserDestroy() override {
    	std::cout << "Closing game" << std::endl;
    	return true;
  	}
};

int main() {
  	Game game;
  	if (game.Construct(WIDTH, HEIGHT, 1, 1)) game.Start();
  	return 0;
}