#include "raylib.h"
#include "raymath.h"


#define W_WIDTH 384
#define W_HEIGHT 384
#define W_NAME "Classy Clash"

int createWindow(int width, int height, char* name)
{
    InitWindow(width, height, name);
}


int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, W_NAME);
    SetTargetFPS(60);    

    Texture2D map = LoadTexture("resources/classy_class_world_map.png");
    Vector2 map_pos{0.0, 0.0};

    
    Texture2D character_running = LoadTexture("resources/characters/knight_run_spritesheet.png");
    Texture2D character_idle = LoadTexture("resources/characters/knight_idle_spritesheet.png");
    Texture2D character = LoadTexture("resources/characters/knight_idle_spritesheet.png");
    
    Vector2 character_pos{
        (float)W_WIDTH/2.0f - 4.0f * (0.5f * (float)character.width/6.0f),
        (float)W_HEIGHT/2.0f - 4.0f * (0.5f * (float)character.height)
    };
    // 1.f: facing right, -1.f: facing left
    float characterDirection{1.f};
    float speed{4.0};

    //Animation of the character 
    float runningTime{};
    int frame{};
    const int maxNumberOfFrames{6};
    const float updateTime{1.f/12.f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction {};

        /* CHECK IF A KEY IS PRESSED FOR MOVEMENT*/
        if (IsKeyDown(KEY_A)) direction.x -= 1.0; // TO MOVE THE MAP X TO THE LEFT
        if (IsKeyDown(KEY_D)) direction.x += 1.0;// TO MOVE THE MAP X TO THE RIGHT
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;// TO MOVE THE MAP X UP
        if (IsKeyDown(KEY_S)) direction.y += 1.0;// TO MOVE THE MAP X DOWN
        
        
        if(Vector2Length(direction) != 0.0)
        {
             // TO NORMALIZE THE VECTOR Vector2Normalize
             //VECTOR2SCALE IS THE VECTOR TIMES A FLOAT
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed)); // TO SUBSTRACT VETORS
            direction.x < 0.f ? characterDirection = -1.f : characterDirection = 1.f;
            character = character_running;
        }else 
        {
            character = character_idle;
        }

        // drawing the map
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);

        //updating the character animation 
        runningTime += GetFrameTime();

        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;

            if (frame > maxNumberOfFrames) frame = 0;
            
        }

        // drawing the character
        Rectangle source{frame * (float) character.width/6.f, 0.0,characterDirection * (float) character.width/6.f, (float)character.height};
        Rectangle dest{character_pos.x, character_pos.y, 4.0f * (float)character.width/6.0, 4.0f * (float)character.height};
        DrawTexturePro(character, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    
    UnloadTexture(map);
}


