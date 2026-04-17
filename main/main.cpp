#include "raylib.h"


class Game {
    Camera2D camera;
    Texture2D python_tex;
    Texture2D cpp_tex;

    Vector2 player;
    constexpr static int image_size = 100;
    constexpr static int offset = 200;
    float ground_y_border;
    int player_velocity;

public:
    Game() {
        Image python_img = LoadImage("assets/python-guy.png");
        ImageResize(&python_img, image_size, image_size);
        python_tex = LoadTextureFromImage(python_img);
        UnloadImage(python_img);

        Image cpp_img = LoadImage("assets/cpp-guy.png");
        ImageResize(&cpp_img, image_size, image_size);
        cpp_tex = LoadTextureFromImage(cpp_img);
        UnloadImage(cpp_img);

        ground_y_border = static_cast<float>(GetScreenHeight()) / 5 * 4;
        player = { offset, ground_y_border - image_size };

        camera = { 0 };
        camera.target = (Vector2){ player.x, 0 };
        camera.offset = (Vector2){ offset, 0 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        player_velocity = 0;
    }

    void movePlayerDown() {
        player_velocity -= 5;
    }

    void movePlayerUp() {
        player_velocity += 25;
    }

    void updatePlayerPos() {
        player.y -= player_velocity--;

        if (player.y > ground_y_border - image_size) {
            player.y = ground_y_border - image_size;
            player_velocity = 0;
        }
    }

    void updateCameraTarget() {
        camera.target = (Vector2){ player.x, 0 };
    }

    void drawGame() {
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginMode2D(camera);

                DrawRectangle(camera.target.x - GetScreenWidth(), ground_y_border
                             , GetScreenWidth() * 2, ground_y_border, RAYWHITE);

                DrawTextureV( python_tex, player, WHITE);

                DrawTextureV( cpp_tex, { 0, 0 }, WHITE);

            EndMode2D();

        EndDrawing();
    }
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "Bullet hand");

    Game game = Game();

    HideCursor();

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement

        // constexpr static int rand = 4;
        // camera.offset.y += GetRandomValue(-rand, rand);
        // camera.offset.x += GetRandomValue(-rand, rand);
        // camera.rotation += static_cast<float>(GetRandomValue(-rand, rand)) / 10;

        if (IsKeyDown(KEY_DOWN) | IsKeyDown(KEY_J)) game.movePlayerDown();
        if (IsKeyPressed(KEY_UP) | IsKeyPressed(KEY_K)) game.movePlayerUp();

        game.updatePlayerPos();
        game.updateCameraTarget();

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------

        game.drawGame();

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
