#pragma once
#include <vector>
#include "SpriteComponent.h"

class AnimSpriteComponent:public SpriteComponent
{
public:
  AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
  // update every frame (override from component)
  void Update(float deltaTime) override;
  // set the texture
  void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
  // set and get FPS
  float GetAnimFPS() const{return mAnimFPS;}
  void SetAnimFPS(float fps){ mAnimFPS = fps;}
  
private:
  // all texuture for animation
  std::vector<SDL_Texture*> mAnimTextures;
  // the frame being displayed now
  float mCurrFrame;
  float mAnimFPS; // We can controll FPS !
};