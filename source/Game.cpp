#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "Field.h"
#include "TBPlayer.h"
#include "TurnManager.h"
#include "Path.h"
#include <iostream>
#include "Bomb.h"
#include "Players.h"

Game::Game()
:mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
{
}

// Game::LoadData() is game specific 

void Game::UnloadData()
{
  // Delete Actors
  while(!mActors.empty()){
    delete mActors.back();
  }
  // Destroy textures
  for(auto i: mTextures)
  {
    SDL_DestroyTexture(i.second);
  }
  mTextures.clear();
}

// ___________general functions______________

bool Game::Initialize()
{
  // SDL_Init returns integer, and if the return is not 0, initializing was falid.
  int sdlResult = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  if(sdlResult != 0){
  // SDL_GetError returns C-style error mesage
    SDL_Log("can't initialize SDL: %s", SDL_GetError());
    return false;
  }
  
  // make SDL_Window (as pointer)
  mWindow = SDL_CreateWindow(
    "Time Bomb",
    UPPER_LEFT_X, // x-cordinate of a upper left point of a window.
    UPPER_LEFT_Y, // y-cordinate
    WIDTH, // width of a window
    HEIGHT, // height of a window
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
  
  // initialize SDL_image
  if(IMG_Init(IMG_INIT_PNG) == 0)
  {
    SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
    return false;
  }
  
  LoadData();
  
  mTicksCount = SDL_GetTicks();
  
  return true;
}

void Game::RunLoop()
{
  while(mIsRunning)
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
        mIsRunning = false;
        break;
      
      default :
        mUpdatingActors = true;
        for(auto actor : mActors)
        {
          actor->ProcessInput(event);
        }
        mUpdatingActors = false;
    }
  }
  
  const Uint8* state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_ESCAPE])
  {
    mIsRunning = false;
  }
}

void Game::UpdateGame()
{
  //frame lowerlimitting
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + LEAST_FRAME_TICKS))
  {};
  // elapsed time from the before frame (mili second to second)
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
  // update the time
  mTicksCount = SDL_GetTicks();
  
  //frame upperlimittng
  if(deltaTime > DELTA_TIME_UPPER_LIMIT) deltaTime = DELTA_TIME_UPPER_LIMIT;
  
  // Update all actors
  mUpdatingActors = true;
  for(const auto& actor : mActors) actor->Update(deltaTime);
  // mActors to explicitly chosed actors
  // for(auto actor : mSettedBombs) actor -> Update(deltaTime);
  // mTurnManager->Update(deltaTime);
  // if(mTBPlayer1 != nullptr) mTBPlayer1->Update(deltaTime);
  // if(mTBPlayer2 != nullptr) mTBPlayer2->Update(deltaTime);
  // for(auto field : mFields) field->Update(deltaTime);
  // mUpdatingActors = false;
  
  // move penidingActors to Actors
  for(auto pending:mPendingActors) mActors.emplace_back(pending);
  mPendingActors.clear();
  
  // list up dead actors
  std::vector<Actor*> deadActors;
  for(auto actor : mActors)
  {
    if(actor -> GetState() == Actor::EDead) deadActors.emplace_back(actor);
  }
  
  // remove dead actors
  for (auto actor : deadActors) delete actor;
}

void Game::GenerateOutput()
{
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  SDL_RenderClear(mRenderer);
  
  for(auto sprite : mSprites)
  {
    sprite->Draw(mRenderer);
  }
  SDL_RenderPresent(mRenderer);
}

void Game::Shutdown(){
  UnloadData();
  IMG_Quit();
  SDL_DestroyWindow(mWindow);
  SDL_DestroyRenderer(mRenderer);
  SDL_Quit();
}

// file -> surface -> texture
SDL_Texture* Game::GetTexture(const std::string& fileName)
{
  SDL_Texture* tex = nullptr;
  // is the texture already in the map?
  auto iter = mTextures.find(fileName); // search the filename
  if(iter != mTextures.end())
  {
    tex = iter -> second;
  }
  else
  {
    // load the image from file
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if(!surf)
    {
      SDL_Log("Failed to load texture file %s", fileName.c_str());
      return nullptr;
    }
    
    // create texture from surface
    tex = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf); // remove?
    if(!tex)
    {
      SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
      return nullptr;
    }
    
    mTextures.emplace(fileName.c_str(), tex);
  }
  return tex;
}

void Game::AddActor(Actor* actor)
{
  if(mUpdatingActors) mPendingActors.emplace_back(actor);
  else mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
  // is it in pending actors?
  auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
  if(iter != mPendingActors.end())
  {
    // move it onto the end of mPendingActors
    std::iter_swap(iter, mPendingActors.end() -1);
    mPendingActors.pop_back();
  }
  // is it in active actors?
  iter = std::find(mActors.begin(),mActors.end(),actor);
  if(iter != mActors.end())
  {
    std::iter_swap(iter, mActors.end() -1);
    mActors.pop_back();
  }
}

void Game::AddSprite(class SpriteComponent* sprite)
{
  // find the insertion point
  int myDrawOrder = sprite->GetDrawOrder();
  auto iter = mSprites.begin(); // mSprites is the list of component
  for (; iter != mSprites.end(); iter++)
  {
    if(myDrawOrder < (*iter)->GetDrawOrder())
    {
      break;
    }
  }
  mSprites.insert(iter,sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
  auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
  mSprites.erase(iter);
}
