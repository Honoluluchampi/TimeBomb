#include "Game.h"
#include <math.h>

const int thickness = 15;
//const float paddleH = 100.0f;
const int width = 1024;
const int height = 768;
const int PaddleSize = 200;
const float PaddleSpeed = 300.0;

Game::Game()
:mlsRunning(true)
{
  
}

bool Game::Initialize()
{
  return true;
}

void Game::RunLoop()
{
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}


void Game::Shutdown(){
};
