#include "character.h"
#include "raymath.h"

Character::Character(int window_width, int window_height) :
    window_width(window_width),
    window_height(window_height)
{
    width = texture.width / maxNumberOfFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * width),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if(!getIsAlive()) return; // if is not alive don't do anything for the character

    /* CHECK IF A KEY IS PRESSED FOR MOVEMENT*/
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0; // TO MOVE THE MAP X TO THE LEFT
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // TO MOVE THE MAP X TO THE RIGHT
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0; // TO MOVE THE MAP X UP
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0; // TO MOVE THE MAP X DOWN

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if(characterDirection > 0.f)
    {
        origin = Vector2{0.f, weapon.height * scale};
        offset = Vector2{35.f, 55.f};
        
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = 30.f;
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 30.f : rotation = 0.f;
    }
    else
    {
        origin = Vector2{weapon.width * scale, weapon.height * scale};
        offset = Vector2{25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };   
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -30.f : rotation = 0.f;   
    }

    // Drawings the weapon
    Rectangle source{0.0, 0.0, static_cast<float>(weapon.width) * characterDirection, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);    
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f)
    {
        setIsAlive(false);
    }
}