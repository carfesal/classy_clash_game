#include "base_character.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::stopCharacterMovement()
{
    world_pos = worldPosLastFrame;
}

void BaseCharacter::tick(float deltaTime)
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

    if (Vector2Length(velocity) != 0.0)
    {
        // TO NORMALIZE THE VECTOR Vector2Normalize
        // VECTOR2SCALE IS THE VECTOR TIMES A FLOAT
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed)); // TO SUBSTRACT VEcTORS
        velocity.x < 0.f ? characterDirection = -1.f : characterDirection = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {0.f, 0.f};

    // drawing the character
    Rectangle source{frame * width, 0.0, characterDirection * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

Rectangle BaseCharacter::getCollisionRectangle()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}