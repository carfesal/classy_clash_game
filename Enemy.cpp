#include "enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) :
    world_pos(pos),
    texture(idle_texture),
    idle(idle_texture),
    run(run_texture)
{
    width = texture.width / maxNumberOfFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = world_pos;

    // updating the character animation
    runningTime += deltaTime;

    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;

        if (frame > maxNumberOfFrames)
            frame = 0;
    }

    // drawing the character
    Rectangle source{frame * width, 0.0, characterDirection * width, height};
    Rectangle dest{screen_pos.x, screen_pos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Enemy::stopCharacterMovement()
{
    world_pos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRectangle()
{
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        width * scale,
        height * scale
    };
}