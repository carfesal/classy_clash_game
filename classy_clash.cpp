#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"

#define W_WIDTH 384
#define W_HEIGHT 384
#define W_NAME "Classy Clash"

int createWindow(int width, int height, char *name)
{
    InitWindow(width, height, name);
}

int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, W_NAME);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("resources/classy_class_world_map.png");
    Vector2 map_pos{0.0, 0.0};    
    const float map_scale{4.0f};

    Character knight{W_WIDTH,W_HEIGHT};
    Prop rock{Vector2{0.f,0.f}, LoadTexture("resources/nature_tileset/Rock.png")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        map_pos = Vector2Scale(knight.getWorldPos(), -1.f);
        // drawing the map
        DrawTextureEx(map, map_pos, 0.0, map_scale, WHITE);
        rock.render(knight.getWorldPos());
        knight.tick(GetFrameTime());

        // checking map bounds 

        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + W_WIDTH > map.width * map_scale ||
            knight.getWorldPos().y + W_HEIGHT > map.height * map_scale)
        {
            knight.stopCharacterMovement();
        }

        EndDrawing();
    }

    UnloadTexture(map);
}
