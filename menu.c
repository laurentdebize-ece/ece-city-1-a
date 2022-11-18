#include "menu.h"
#include "raylib.h"

int modeJeu(void)

{
    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Menu");
    Texture2D texture = LoadTexture("../imgmenu.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, 0, 0, WHITE);

        DrawRectangle(325, 70, 350, 110, BROWN);
        DrawRectangle(100, 400, 350, 150, GRAY);
        DrawRectangle(580, 400, 350, 150, GRAY);

        DrawRectangleLines(325, 70, 350, 110, WHITE);
        DrawRectangleLines(100, 400, 350, 150, YELLOW);
        DrawRectangleLines(580, 400, 350, 150, YELLOW);

        DrawText("MODE DE JEU", 360, 100, 40, WHITE);
        DrawText("COMMUNISTE", 135, 450, 40, YELLOW);
        DrawText("CAPITALISTE", 615, 450, 40, YELLOW);

        // bool IsMouseButtonPressed(int button);


        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
