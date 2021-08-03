#pragma once
#include "SpriteComponent.h"
#include <vector>

class ExplosionAnimSpriteComponent : public SpriteComponent
{
public:
    ExplosionAnimSpriteComponent(class Actor* owner, int drawOrder, bool isBlue, class TurnManager* tm);
    ~ExplosionAnimSpriteComponent();
    void Update(float deltaTime) override;
    void SetAnimTextures(const std::vector<SDL_Texture*>& texture);

private:
    class TurnManager* mTurnManager;
    std::vector<SDL_Texture*> mAnimTextures;
    float mCurrFrame;
    float mAnimFPS;
};