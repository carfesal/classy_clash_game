#include "raylib.h"

class Character
{
public:
    Vector2 getWorldPos() { return world_pos; }
    void setScreenPos(int windWidth, int windHeight);
    void tick(float deltaTime);
    void stopCharacterMovement();

    Character();
private:
    Texture2D texture{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("resources/characters/knight_run_spritesheet.png")};
    Texture2D idle{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Vector2 screen_pos{};
    Vector2 world_pos{};
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
    Vector2 worldPosLastFrame{};
};