#include "menu.h"
#include "raylib.h"


void modeJeu(int * choixmode) // la fonction prendra en entrée : int *choixmode
{
    bool fin;

    Texture2D texture = LoadTexture("../images/Menu/imgmenu2.png");

    while (!WindowShouldClose() && !fin)
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        int X = GetMouseX();
        int Y = GetMouseY();

        DrawTexture(texture, 0, 0, WHITE);

        DrawText("ECE CITY", 320, 12, 70, BROWN);

        DrawRectangle(325, 200, 350, 110, BROWN);
        DrawRectangle(100, 400, 350, 150, BEIGE);
        DrawRectangle(580, 400, 350, 150, BEIGE);

        DrawRectangleLines(325, 200, 350, 110, WHITE);
        DrawRectangleLines(100, 400, 350, 150, YELLOW);
        DrawRectangleLines(580, 400, 350, 150, YELLOW);

        DrawText("MODE DE JEU", 360, 230, 40, WHITE);
        DrawText("COMMUNISTE", 135, 450, 40, YELLOW);
        DrawText("CAPITALISTE", 615, 450, 40, YELLOW);


        switch (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            case 0: { // le boutton de la souris n'est pas enfoncé, on met en évidence la case

                if ((X >= 100) && (X <= 450) && (Y <= 550) && (Y >= 400)){
                    DrawRectangleLines(100, 400, 350, 150, BROWN);
                }
                if ((X >= 580) && (X <= 900) && (Y <= 550) && (Y >= 400)){
                    DrawRectangleLines(580, 400, 350, 150, BROWN);
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
}


void accueil(int *choixMode){
    bool fin;

    Texture2D texture = LoadTexture("../images/Menu/accueil2.png");

    while (!WindowShouldClose() && !fin)
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        int X = GetMouseX();
        int Y = GetMouseY();

        DrawTexture(texture, 0, 0, WHITE);
        DrawText("ECE CITY", 320, 12, 70, BROWN);

        DrawRectangle( 330, 300, 350,110, LIGHTGRAY );
        DrawRectangleLines(330,300,350,110,WHITE);
        DrawText("JOUER", 390, 320, 70, WHITE);

        switch (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            case 0: {
                if((X >= 330) && (X <= 680) && (Y <= 410) && (Y >= 300)){
                    DrawRectangleLines(330,300,350,110,BROWN);
                }
            }break;
            case 1: {
                if((X >= 330) && (X <= 680) && (Y <= 410) && (Y >= 300)) {
                    modeJeu(choixMode);
                    fin = true;
                }
            }break;

        }
        EndDrawing();

    }
    UnloadTexture(texture);
}
