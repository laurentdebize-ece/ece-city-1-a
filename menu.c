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
        int X = GetMouseX();
        int Y = GetMouseY();

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

        if ((X >= 100) && (X <= 450) && (Y <= 550) && (Y >= 400)){
            DrawRectangleLines(100, 400, 350, 150, BLACK);
        }
        if ((X >= 580) && (X <= 900) && (Y <= 550) && (Y >= 400)){
            DrawRectangleLines(580, 400, 350, 150, BLACK);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) ){
            if ((X >= 100) && (X <= 450) && (Y <= 550) && (Y >= 400)){
                return 1;
            }
            if ((X >= 580) && (X <= 900) && (Y <= 550) && (Y >= 400)){
                return 1;
            }
        }

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
