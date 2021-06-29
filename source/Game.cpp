#include "Game.h"
#include <math.h>
const int thickness = 15;
const float paddleH = 100.0f;
const int width = 1024;
const int height = 768;
const int upperLeftX = 100;
const int upperLeftY = 100;
const int PaddleSize = 200;
const float PaddleSpeed = 300.0;

Game::Game()
:mWindow(nullptr), mlsRunning(true)
{
  
}

bool Game::Initialize()
{
  // SDL_Init returns integer, and if the return is not 0, initialization was falid.
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if(sdlResult != 0){
  // SDL_GetError returns C-style error mesage
    SDL_Log("can't initialize SDL: %s", SDL_GetError());
    return false;
  }

  // make SDL_Window (as pointer)
  mWindow = SDL_CreateWindow(
      "Time Bomb",
      upperLeftX, // x-cordinate of a upper left point of a window.
      upperLeftY, // y-cordinate
      width, // width of a window
      height, // height of a window
      0 // flag
  );
  // if SDL_CreateWindow failed, return false.
  if(!mWindow){
      SDL_Log("failed to create a window. : %s", SDL_GetError());
      return false;
  }
  
  // make SDL_Renderer (as pointer)
  mRenderer = SDL_CreateRenderer(
    mWindow,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // use GPU and vertical synclonization.
  if(!mRenderer){
    SDL_Log("failed to create a renderer. : %s", SDL_GetError());
    return false;
  }

  mBallPos.x = width;
  mBallPos.y = height/2;
  mPaddlePos.x = 0;
  mPaddlePos.y = height/2;
  // initialize ball velocity vector
  mBallVel.x = -200.f;
  mBallVel.y = 235.0f;
  return true;
}

void Game::RunLoop()
{
  while(mlsRunning)
  {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::ProcessInput()
{
  SDL_Event event; // includes information of a value in queue.
  while(SDL_PollEvent(&event)) // PollEvent returns true if there is an event in the queue.
  {
    switch(event.type) // includes the type of event.
    {
      case SDL_QUIT:
        mlsRunning = false;
        break;
    }
  }
  
  const Uint8* state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_ESCAPE])
  {
    mlsRunning = false;
  }
  
  // update paddle difference organizer
  mPaddleDir = 0;
  if(state[SDL_SCANCODE_W]) mPaddleDir -= 1;
  if(state[SDL_SCANCODE_S]) mPaddleDir += 1;
}

void Game::UpdateGame()
{
  //frame lowerlimitting
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
  {};
  // elapsed time from the before frame (mili second to second)
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
  // update the time
  mTicksCount = SDL_GetTicks();
  
  //frame upperlimittng
  if(deltaTime > 0.05f) deltaTime = 0.05f;
  
  // update Paddle Position
  if(mPaddleDir != 0)
  {
    mPaddlePos.y += mPaddleDir * PaddleSpeed * deltaTime;
    if(mPaddlePos.y < (PaddleSize/2.0f + thickness))
    {
      mPaddlePos.y = PaddleSize/2.0f + thickness;
    }
    else if(mPaddlePos.y > height - PaddleSize/2.0f - thickness)
    {
      mPaddlePos.y = height - PaddleSize/2.0f - thickness;
    }
  }
  
  // collision detect
  float diff = abs(mBallPos.y - mPaddlePos.y);
  if(mBallPos.y <= thickness && mBallVel.y < 0.0f) mBallVel.y *= -1;
  if(mBallPos.y >= height - thickness && mBallVel.y > 0.0f) mBallVel.y *= -1;
  if(mBallPos.x >= width - thickness && mBallVel.x > 0.0f) mBallVel.x *= -1;
  if(diff <= PaddleSize/2.0f && mBallPos.x <= thickness && mBallPos.x >= 0 && mBallVel.x < 0.0f) mBallVel.x *= -1;
  
  //update ball position
  mBallPos.x += mBallVel.x * deltaTime;
  mBallPos.y += mBallVel.y * deltaTime;
}

void Game::GenerateOutput()
{
  // set the color
  SDL_SetRenderDrawColor(
    mRenderer, // renderer pointer
    0, // r
    0, // g
    255, // b
    255); // alpha
  
  // clear (reset) buffa
  SDL_RenderClear(mRenderer);
  
  // Draw wall
  SDL_SetRenderDrawColor(
     mRenderer,
     255,
     255,
     255,
     255
  );
  
  // need padding?
  // create wall
  SDL_Rect upsidewall{0, 0, static_cast<int>(width), thickness};
  SDL_Rect downsidewall{0, static_cast<int>(height)-thickness, static_cast<int>(width), thickness};
  SDL_Rect rightsidewall{static_cast<int>(width)-thickness, 0, thickness, static_cast<int>(height)};
  
  SDL_RenderFillRect(mRenderer, &upsidewall); // color the wall
  SDL_RenderFillRect(mRenderer, &downsidewall);
  SDL_RenderFillRect(mRenderer, &rightsidewall);
  
  // create paddle and ball
  SDL_Rect ball{
    static_cast<int>(mBallPos.x - thickness/2),
    static_cast<int>(mBallPos.y - thickness/2),
    thickness,
    thickness
  };
  SDL_Rect paddle{
    static_cast<int>(mPaddlePos.x - thickness/2),
    static_cast<int>(mPaddlePos.y - PaddleSize/2),
    thickness,
    PaddleSize
  };
  
  SDL_RenderFillRect(mRenderer, &ball);
  SDL_RenderFillRect(mRenderer, &paddle);
  
  // change front buffa with back buffa
  SDL_RenderPresent(mRenderer);
}


void Game::Shutdown(){
  SDL_DestroyWindow(mWindow);
  SDL_DestroyRenderer(mRenderer);
  SDL_Quit();
};
