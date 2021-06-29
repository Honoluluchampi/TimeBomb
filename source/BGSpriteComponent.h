#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
  // is this default value of drawOrder is appropriate? 100?
  BGSpriteComponent(class Actor* owner, int drawOrder = 10);
  // Update/draw overriden from parent
  void Update(float deltaTime) override;
  void Draw(SDL_Renderer* renderer) override;
  // Set the textures used for the background
  void SetBGTextures(const std::vector<SDL_Texture*>& textures);
  // Set the screen size and SCROLL SPEED
  void SetScreenSize(const Vector2& size) { mScreenSize = size; }
  void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
  float GetScrollSpeed() const { return mScrollSpeed;}
  
private:
  struct BGTexture
  {
    SDL_Texture* mTexture;
    Vector2 mOffset;
  };
  std::vector<BGTexture> mBGTextures;
  Vector2 mScreenSize;
  float mScrollSpeed;
};

