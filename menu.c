

#include "menu.h"
#include "raylib.h"

int menu(void)

{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Menu");
    Texture2D texture = LoadTexture("../imgmenu.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, BLACK);
        DrawTexture(texture, 0, 0, WHITE);
        DrawRectangle(100, 50, 350, 150, GRAY);
        DrawRectangle(550, 50, 350, 150, GRAY);

        DrawText("COMMUNISTE", 135, 100, 40, YELLOW);
        DrawText("CAPITALISTE", 585, 100, 40, YELLOW);



        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
