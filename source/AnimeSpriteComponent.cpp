#include "AnimeSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
  :SpriteComponent(owner, drawOrder), mCurrFrame(0.0f), mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
  SpriteComponent::Update(deltaTime);
  
  if(mAnimTextures.size() > 0)
  {
    // update current frame considering framerate and deltatime
    mCurrFrame += mAnimFPS * deltaTime;
    
    // if necessary, rewind the current frame
    while (mCurrFrame >= mAnimTextures.size())
    {
      mCurrFrame -= mAnimTextures.size();
    }
    
    // set the current texture
    SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
  }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
  mAnimTextures = textures;
  if (mAnimTextures.size() > 0)
  {
    //Set the active texture to first frame
    mCurrFrame = 0.0f;
    SetTexture(mAnimTextures[0]);
  }
}
