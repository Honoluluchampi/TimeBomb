#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

const float WIDTH = 1024.0f;
const float HEIGHT = 768.0f;
const float UPPER_LEFT_X = 100.0f;
const float UPPER_LEFT_Y = 100.0f;
const int INITIAL_FIELD_NUM =4;
const Vector2 FIELD_POSITION[] = {
  Vector2(WIDTH/7, HEIGHT/7),
  Vector2(WIDTH*6/7, HEIGHT*6/7),
  Vector2(WIDTH*2/3, HEIGHT*1/3),
  Vector2(WIDTH*1/3, HEIGHT*2/3),
  Vector2(WIDTH*5/6, HEIGHT/7),
  Vector2(WIDTH/7, HEIGHT*5/6)
};
const int INITIAL_FIELD_FOR_1 = 0;
const int INITIAL_FIELD_FOR_2 = 1;

class Game
{
public:
  
  // Constracter
  Game();
  
  // Initializer
  bool Initialize();
  
  // Game Looper
  void RunLoop();
  
  // ShutDown Game
  void Shutdown();
  
  // Add or Remove Actor
  void AddActor(class Actor* actor);
  void RemoveActor(class Actor* actor);
  
  // Add Sprite
  void AddSprite(class SpriteComponent* sprite);
  void RemoveSprite(class SpriteComponent* sprite);
  
  SDL_Texture* GetTexture(const std::string& filename);
  
  // chapter specific
  void AddField(class Field* field);
  void RemoveField(class Field* field);
  std::vector<class Field*> GetFields() {return mFields;}

private:
  // Helper functions for RunLoop()
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();
  void LoadData();
  void UnloadData();
  
  // map of textures
  std::unordered_map<std::string, SDL_Texture*> mTextures;
  
  // All the sprite components drawn
  std::vector<class SpriteComponent*> mSprites;
  
  // the pointer of Window generated by SDL
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer; // graphic organizer
  
  // continue instractor
  bool mlsRunning;
  // elapsed time from SDL_init
  Uint32 mTicksCount;
  
  // GameObject
  std::vector<class Actor*> mActors;
  std::vector<class Actor*> mPendingActors;
  
  bool mUpdatingActors;
  
  // Game specific
  class TBPlayer* mTBPlayer1;
  class TBPlayer* mTBPlayer2;
  class TurnManager* mTurnManager;
  std::vector<std::vector<class Path*>> mFieldGraph;
  std::vector<class Field*> mFields;
};