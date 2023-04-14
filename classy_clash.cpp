#include "raylib.h"
#include "raymath.h"

#define W_WIDTH 384
#define W_HEIGHT 384
#define W_NAME "Classy Clash"

int createWindow(int width, int height, char *name)
{
    InitWindow(width, height, name);
}

class Character
{
public:
    Vector2 getWorldPos() { return world_pos; }
    void setScreenPos(int windWidth, int windHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("resources/characters/knight_run_spritesheet.png")};
    Texture2D idle{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Vector2 screen_pos {};
    Vector2 world_pos {};
    // 1.f: facing right, -1.f: facing left
    float characterDirection{1.f};
    // Animation of the character
    float runningTime{};
    int frame{};
    const int maxNumberOfFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

void Character::setScreenPos(int windWidth, int windHeight) // a way to implement the function  outside the class
{
    screen_pos = {
        (float)windWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)windHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
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
    Rectangle source{frame * (float)texture.width / 6.f, 0.0, characterDirection * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screen_pos.x, screen_pos.y, 4.0f * (float)texture.width / 6.0, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, W_NAME);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("resources/classy_class_world_map.png");
    Vector2 map_pos{0.0, 0.0};    

    Character knight;
    knight.setScreenPos(W_WIDTH, W_HEIGHT);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        map_pos = Vector2Scale(knight.getWorldPos(), -1.f);
        // drawing the map
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
}
