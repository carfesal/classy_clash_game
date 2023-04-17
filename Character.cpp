#include "character.h"
#include "raymath.h"

Character::Character(int window_width, int window_height)
{
    width = texture.width / maxNumberOfFrames;
    height = texture.height;

    screen_pos = {static_cast<float>(window_width) / 2.0f - scale * (0.5f * width),
                  static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    worldPosLastFrame = world_pos;
    /* CHECK IF A KEY IS PRESSED FOR MOVEMENT*/
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0; // TO MOVE THE MAP X TO THE LEFT
    if (IsKeyDown(KEY_D))
        direction.x += 1.0; // TO MOVE THE MAP X TO THE RIGHT
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0; // TO MOVE THE MAP X UP
    if (IsKeyDown(KEY_S))
        direction.y += 1.0; // TO MOVE THE MAP X DOWN

    if (Vector2Length(direction) != 0.0)
    {
        // TO NORMALIZE THE VECTOR Vector2Normalize
        // VECTOR2SCALE IS THE VECTOR TIMES A FLOAT
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(direction), speed)); // TO SUBSTRACT VETORS
        direction.x < 0.f ? characterDirection = -1.f : characterDirection = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

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

void Character::stopCharacterMovement()
{
    world_pos = worldPosLastFrame;
}