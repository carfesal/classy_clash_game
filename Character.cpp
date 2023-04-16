#include "character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width / maxNumberOfFrames;
    height = texture.height;
}

void Character::setScreenPos(int windWidth, int windHeight) // a way to implement the function  outside the class
{
    screen_pos = {(float)windWidth / 2.0f - 4.0f * (0.5f * width),
                  (float)windHeight / 2.0f - 4.0f * (0.5f * height)};
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
    Rectangle dest{screen_pos.x, screen_pos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::stopCharacterMovement()
{
    world_pos = worldPosLastFrame;
}