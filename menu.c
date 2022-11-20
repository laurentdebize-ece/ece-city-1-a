#include "menu.h"
#include "raylib.h"

int accueil(void){

    const int screenWidth = 1024;
    const int screenHeight = 768;
    bool fin;

    InitWindow(screenWidth, screenHeight, "ACCUEIL");
    Texture2D texture = LoadTexture("../accueil2.png");

    while (!WindowShouldClose() && !fin)
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        int X = GetMouseX();
        int Y = GetMouseY();

        DrawTexture(texture, 0, 0, WHITE);
        DrawText("ECE CITY", 345, 12, 70, WHITE);

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            fin = true;
        }
        EndDrawing();

    }
    UnloadTexture(texture);
    CloseWindow();

    return 0;

}

int modeJeu(int * choixmode) // la fonction prendra en entrée : int *choixmode
{
    const int screenWidth = 1024;
    const int screenHeight = 768;
    bool fin;

    InitWindow(screenWidth, screenHeight, "MENU");
    Texture2D texture = LoadTexture("../imgmenu.png");

    while (!WindowShouldClose() && !fin)
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


        switch (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            case 0: { // le boutton de la souris n'est pas enfoncé, on met en évidence la case

                if ((X >= 100) && (X <= 450) && (Y <= 550) && (Y >= 400)){
                    DrawRectangleLines(100, 400, 350, 150, BLACK);
                }
                if ((X >= 580) && (X <= 900) && (Y <= 550) && (Y >= 400)){
                    DrawRectangleLines(580, 400, 350, 150, BLACK);
                }

            } break;

            case 1: { // on clique sur la souris et on vérifie si le curseur est sur un des rectangles

                if ((X >= 100) && (X <= 450) && (Y <= 550) && (Y >= 400)){
                    *choixmode = 1;
                    fin = true;
                }

                if ((X >= 580) && (X <= 900) && (Y <= 550) && (Y >= 400)){
                    *choixmode = 2;
                    fin = true;
                }

            } break;

        }
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
