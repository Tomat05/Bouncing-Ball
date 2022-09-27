#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

class Game : public olc::PixelGameEngine {
 public:
  Game() { sAppName = "Ball lol"; }

 private:
  float timer = 0;
  int frames = 0;
  int fps;

  float ballY = 50;
  float ballX = 50;
  float ballSpeedY = 300;
  float ballSpeedX = 300;

 public:
  bool OnUserCreate() override {
    /*
      Load resources here
    */
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {

    ballY += ballSpeedY * GetElapsedTime();
    ballX += ballSpeedX * GetElapsedTime(); 

    if (ballY >= WINDOW_HEIGHT - 35 || ballY <= 35)
    {
        ballSpeedY = -ballSpeedY;
    }

    if (ballX >= WINDOW_WIDTH - 35 || ballX <= 35)
    {
        ballSpeedX = -ballSpeedX;
    }
    

    timer += fElapsedTime;
    frames++;
    if (timer > 1.0) {
      fps = frames;
      frames = 0;
      timer -= 1;
    }

    inputs();
    processes();
    outputs();

    if (GetKey(olc::Key::ESCAPE).bPressed) {
      return false;
    } else {
      return true;
    }
  }

  void inputs() {
    /*
      Game controls goes here
    */

    if (GetKey(olc::Key::SPACE).bHeld) {
      std::cout << "Space!" << std::endl;
    }
    if (GetMouse(0).bHeld) {
      std::cout << "Click!" << std::endl;
    }
  }

  void processes() {
    /*
      Game logic goes here
    */
  }

  void outputs() {
    SetPixelMode(olc::Pixel::NORMAL);

    Clear(olc::DARK_BLUE);

    FillCircle(ballX, ballY, 20, olc::RED);

    DrawLine(15, 15, WINDOW_WIDTH - 15, 15, olc::WHITE);
	DrawLine(WINDOW_WIDTH - 15, 15, WINDOW_WIDTH - 15, WINDOW_HEIGHT - 15, olc::WHITE);
	DrawLine(WINDOW_WIDTH - 15, WINDOW_HEIGHT - 15, 15, WINDOW_HEIGHT - 15, olc::WHITE);
    DrawLine(15, WINDOW_HEIGHT - 15, 15, 15, olc::WHITE);

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
  if (game.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1)) game.Start();
  return 0;
}