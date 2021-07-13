#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>

const int TEXWIDTH = 0;
const int TEXHEIGHT = 756;

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder, bool isManualPosition, bool isManualScale)
:Component(owner),mTexture(nullptr),mTexWidth(TEXWIDTH),mTexHeight(TEXHEIGHT),
mDrawOrder(drawOrder),mManualPosition(isManualPosition),mManualScale(isManualPosition)
{
  mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
  std::cout << "remove sprite comp" << std::endl;
  mOwner->GetGame()->RemoveSprite(this);
};

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
  if(mTexture)
  {
    SDL_Rect r;
    if(!mManualScale)
    {
      r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
      r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
    }
    else
    {
      r.w = static_cast<int>(mTexWidth * mScale);
      r.h = static_cast<int>(mTexHeight * mScale);
    }
    
    if(!mManualPosition)
    {
      r.x = static_cast<int>(mOwner->GetPosition().x - r.w/2);
      r.y = static_cast<int>(mOwner->GetPosition().y - r.h/2);
    }
    else
    {
      r.x = static_cast<int>(mPosition.x - r.w/2);
      r.y = static_cast<int>(mPosition.y - r.h/2);
    }
    SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,-Math::ToDegrees(mOwner->GetRotation()),nullptr, SDL_FLIP_NONE);
  }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
  mTexture = texture;
  SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
