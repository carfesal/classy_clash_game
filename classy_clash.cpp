#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"
#include <string>

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
    Enemy enemy1{
        Vector2{800.f, 200.f}, 
        LoadTexture("resources/characters/goblin_idle_spritesheet.png"), 
        LoadTexture("resources/characters/goblin_run_spritesheet.png")
    };

    Enemy enemy2{
        Vector2{400.f, 200.f}, 
        LoadTexture("resources/characters/slime_idle_spritesheet.png"), 
        LoadTexture("resources/characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{&enemy1, &enemy2};

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("resources/nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("resources/nature_tileset/Log.png")}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        map_pos = Vector2Scale(knight.getWorldPos(), -1.f);
        // drawing the map
        DrawTextureEx(map, map_pos, 0.0, map_scale, WHITE);
        
        // Draw the props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        if (!knight.getIsAlive())
        {
            DrawText("You died. GAME OVER", W_WIDTH / 2, W_HEIGHT / 2, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string remaniningKnightHealth = "Health: ";
            remaniningKnightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(remaniningKnightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // checking map bounds 

        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + W_WIDTH > map.width * map_scale ||
            knight.getWorldPos().y + W_HEIGHT > map.height * map_scale)
        {
            knight.stopCharacterMovement();
        }
        
        for (auto prop : props)
        {
            if(CheckCollisionRecs(prop.getCollisionRectangle(knight.getWorldPos()), knight.getCollisionRectangle()))
            {
                knight.stopCharacterMovement();
            }
        }

        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRectangle(), knight.getWeaponCollisionRec()))
                {
                    enemy->setIsAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
}
