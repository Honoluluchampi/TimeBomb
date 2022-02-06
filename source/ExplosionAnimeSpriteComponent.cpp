#include "ExplosionAnimeSpriteComponent.h"
#include "TurnManager.h"
#include "Actor.h"
#include "Game.h"
#include "TurnManager.h"
#include "TimeBombApp.h"
#include <iostream>

ExplosionAnimSpriteComponent::ExplosionAnimSpriteComponent(Actor *owner, int drawOrder, bool isBlue, class TurnManager* tm)
: SpriteComponent(owner, drawOrder), mTurnManager(tm), mAnimFPS(EXPLOSION_ANIM_FPS)
{
    if(isBlue){
        std::vector<SDL_Texture*> anims = {
            owner->GetGame()->GetTexture("Assets/explosion_blue1.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue2.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue3.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue4.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue5.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue6.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_blue7.PNG")
        };
        this->SetAnimTextures(anims);
    }
    else
    {
        std::vector<SDL_Texture*> anims = {
            owner->GetGame()->GetTexture("Assets/explosion_red1.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red2.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red3.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red4.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red5.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red6.PNG"),
            owner->GetGame()->GetTexture("Assets/explosion_red7.PNG")
        };
        this->SetAnimTextures(anims);
    }
}

ExplosionAnimSpriteComponent::~ExplosionAnimSpriteComponent()
{
    mTurnManager->RemoveExplosionAnim(this);
}

void ExplosionAnimSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);
  
  if(mAnimTextures.size() > 0)
  {
    // update current frame considering framerate and deltatime
    mCurrFrame += mAnimFPS * deltaTime;

    // disposable anime sprite
    if(mCurrFrame >= mAnimTextures.size())
    {
        delete this;
        return;
    }
    
    // set the current texture
    SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
  }
}

void ExplosionAnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
  mAnimTextures = textures;
  if (mAnimTextures.size() > 0)
  {
    //Set the active texture to first frame
    mCurrFrame = 0.0f;
    SetTexture(mAnimTextures[0]);
  }
}
