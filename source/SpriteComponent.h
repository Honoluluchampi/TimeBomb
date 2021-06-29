#pragma once
#include "Component.h"
#include <SDL2/SDL.h>

class SpriteComponent: public Component
{
public:
  //the lesser the drawOrder of the component, the later it will be drawn
  SpriteComponent(class Actor* owner, int drawOrder = 100);
  ~SpriteComponent();
  
  // drawing function is special to sprite component, so Draw should be
  // defined in this header file , not component.hpp
  virtual void Draw(SDL_Renderer* renderer);
  
  virtual void SetTexture(SDL_Texture* texture);
  
  int GetDrawOrder() const { return mDrawOrder; }
  int GetTexHeight() const { return mTexHeight; }
  int GetTexWidth() const { return mTexWidth; }
  
protected:
  //Texture
  SDL_Texture* mTexture;
  int mTexWidth;
  int mTexHeight;
  //drawing order
  int mDrawOrder;
};
