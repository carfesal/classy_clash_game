#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() { return world_pos; }
    void tick(float deltaTime);
    void stopCharacterMovement();
    Rectangle getCollisionRectangle();
private:
    Texture2D texture;
    Texture2D run;
    Texture2D idle;
    Vector2 screen_pos{};
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
};