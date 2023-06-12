#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "base_character.h"

class Character : public BaseCharacter
{
public:
    Character(int window_width, int window_height);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int window_width{};
    int window_height{};
    Texture2D weapon{LoadTexture("resources/characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif