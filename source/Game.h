#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

const float WIDTH = 1024.0f + 100.0f;
const float HEIGHT = 768.0f;
const float UPPER_LEFT_X = 100.0f;
const float UPPER_LEFT_Y = 100.0f;
const int LEAST_FRAME_TICKS = 16;
const float DELTA_TIME_UPPER_LIMIT = 0.05f;
const int PLAYER_STEP = 2;
const int DISTRIBUTE_BOMB_TURN = 3;
//const float PATH_SCALE = 0.001f;
//const Vector2 PATH_SLIDE = Vector2(0.0f, 0.0f);
const int MAX_PENDING_BOMB_NUM = 3;
const int INITIAL_PENDING_BOMB_NUM = 3;
const float EXPLOSION_ANIM_FPS = 16.0f;
const int INITIAL_HIT_POINT = 2;
const int INITIAL_FIELD_NUM = 16;
const Vector2 FIELD_POSITION[] = {
  Vector2(WIDTH/7, HEIGHT/7),
  Vector2(WIDTH*1/3, HEIGHT*1/4),
  Vector2(WIDTH*4/7, HEIGHT*2/9),
  Vector2(WIDTH*3/4, HEIGHT*1/7),
  Vector2(WIDTH*8/9, HEIGHT*2/9),
  Vector2(WIDTH*1/6, HEIGHT*5/9),
  Vector2(WIDTH*2/7, HEIGHT*3/7),
  Vector2(WIDTH*5/9, HEIGHT*4/9),
  Vector2(WIDTH*4/5, HEIGHT*1/3),
  Vector2(WIDTH*1/8, HEIGHT*5/6),
  Vector2(WIDTH*1/3, HEIGHT*2/3),
  Vector2(WIDTH*3/5, HEIGHT*3/5),
  Vector2(WIDTH*8/9, HEIGHT*2/3),
  Vector2(WIDTH*1/3, HEIGHT*7/8),
  Vector2(WIDTH*3/5, HEIGHT*6/7),
  Vector2(WIDTH*6/7, HEIGHT*5/6)
};
const std::pair<int,int> PATH_EDGES[] = {
  {1,0}, {2,1}, {3,2}, {4,3}, {5,0}, {6,1}, {7,2}, {8,4}, {6,5}, {7,6}, {8,7},
  {9,5}, {10,9}, {10,7}, {11,8}, {12,8}, {12,11}, {10,13}, {11,14}, {15,12}, {14,13}, {15,14}
};
const int INITIAL_FIELD_FOR_1 = 0;
const int INITIAL_FIELD_FOR_2 = 15;

const Vector2 PENDING_BOMB_NUM_POSITION = Vector2(WIDTH * 8/9, HEIGHT * 1/9);

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
  
  // game specific
  void AddField(class Field* field);
  void RemoveField(class Field* field);
  std::vector<class Field*> GetFields() {return mFields;}

  void AddPath(class Path* path);
  void RemovePath(class Path* path);
  std::vector<class Path*> GetPaths() { return mPaths;}

  void AddSettedBomb(class Bomb* bomb);
  void RemoveSettedBomb(class Bomb* bomb);
  std::vector<class Bomb*> GetSettedBombs() {return mSettedBombs;}

  void SetIsRunning(bool flag){mIsRunning = flag;}

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
  bool mIsRunning;
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
  std::vector<class Field*> mFields;
  std::vector<class Path*> mPaths;
  std::vector<class Bomb*> mSettedBombs;
  std::vector<class AnimeSpriteComponent*> mExplosionAnime;
};