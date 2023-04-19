#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 position, Texture2D texture) :
    world_pos(position),
    texture(texture)     // to initialize properties of the class
{

}

void Prop::render(Vector2 knight_pos)
{
    Vector2 screenPos {Vector2Subtract(world_pos, knight_pos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRectangle(Vector2 knight_pos)
{
    Vector2 screenPos {Vector2Subtract(world_pos, knight_pos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}