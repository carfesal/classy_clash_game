#include "enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    world_pos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture; 
    width = texture.width / maxNumberOfFrames;
    height = texture.height;
    speed = 3.f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(world_pos, target->getWorldPos());
}

void Enemy::tick(float deltaTime)
{
    // get to target
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    // BaseCharacter::tick(deltaTime);
}
