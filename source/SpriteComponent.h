#pragma once
#include "Component.h"
#include <SDL2/SDL.h>
#include "Math.h"

const bool MANUAL_POSITIONING = true;
const bool MANUAL_SCALING = true;

class SpriteComponent: public Component
{
public:
  //the lesser the drawOrder of the component, the later it will be drawn
  SpriteComponent(class Actor* owner, int drawOrder = 100, bool isManualPosition = false, bool isManualScale = false);
  ~SpriteComponent();
  
  // drawing function is special to sprite component, so Draw should be
  // defined in this header file , not component.hpp
  virtual void Draw(SDL_Renderer* renderer);
  
  virtual void SetTexture(SDL_Texture* texture);
  void SetPosition(const Vector2 position){mPosition = position;}
  void SetScale(const float scale){ mScaleX = scale; mScaleY = scale;}
  void SetScale(const float scalex, const float scaley){mScaleX = scalex; mScaleY = scaley;}
  
  Vector2 GetPosition() const { return mPosition; }
  float GetScale() const { return mScaleX; }
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
  bool mManualPosition;
  bool mManualScale;
  Vector2 mPosition;
  float mScaleX;
  float mScaleY;
};
