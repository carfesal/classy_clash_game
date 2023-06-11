
#ifndef BASE_CHARACTER_H // to avoid the compiler keeps compiling this file
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter(); 
        Vector2 getWorldPos() { return world_pos; }
        virtual void tick(float deltaTime);
        void stopCharacterMovement();
        Rectangle getCollisionRectangle();
        virtual Vector2 getScreenPos() = 0;
    protected:
        Texture2D texture{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("resources/characters/knight_run_spritesheet.png")};
        Texture2D idle{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
        Vector2 world_pos{};
        Vector2 worldPosLastFrame{};
        // 1.f: facing right, -1.f: facing left
        float characterDirection{1.f};
        // Animation of the character
        float runningTime{};
        int frame{};
        int maxNumberOfFrames{6};
        float updateTime{1.f / 12.f};
        float speed{4.f};
        float width;
        float height;
        float scale{4.0f};
        Vector2 velocity;
};

#endif