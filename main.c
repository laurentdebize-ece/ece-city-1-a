#include "map.h"

void initialiserMap(Map map[45][30],HUD hud[6]){

    for (int i=0;i<45;i++){
        for (int j=0;j<30;j++){
            map[i][j].etat=0;
        }
    }
    for (int i=0;i<6;i++){
        hud[i].etat=0;
    }
}

void sourisCase(Map map[45][30],HUD hud[6],int mouseX,int mouseY,int tailleW,int tailleH,int W,int H,ALLEGRO_COLOR white,ALLEGRO_FONT *gameFont,int clickGauche){
    for (int i=0;i<6;i++){
        if (mouseX>hud[i].x && mouseX<tailleW-hud[i].x && mouseY>hud[i].y && mouseY<tailleH+tailleH/1.5*(i+1)){
            al_draw_filled_rectangle(hud[i].x,hud[i].y,tailleW-hud[i].x,tailleH+tailleH/1.5*(i+1),white);
        }
    }
    for (int i=0;i<45;i++){
        for (int j=0;j<30;j++){
            al_draw_filled_rectangle(tailleW+W*i,tailleH+H*j,tailleW+W*(i+1),tailleH+H*(j+1), white);

            if (map[i][j].etat !=0){
                al_draw_filled_rectangle(tailleW+W*i,tailleH+H*j,tailleW+W*(i+1),tailleH+H*(j+1), al_map_rgb(255,0,0));}
            if (mouseX>tailleW+W*i && mouseX<tailleW+W*(i+1) && mouseY>tailleH+H*j && mouseY<tailleH+H*(j+1)){
                al_draw_filled_rectangle(tailleW+W*i,tailleH+H*j,tailleW+W*(i+1),tailleH+H*(j+1),white);
                al_draw_textf(gameFont,al_map_rgb(0, 0, 0) , tailleW + W / 2 + W * i, tailleH + H / 2 + H * j, 1, "%d", map[i][j].etat);
                if(clickGauche == 1) {
                    for (int k=0;k<6;k++){
                        if (hud[k].etat==1){
                            map[i][j].etat=k;
                            hud[k].etat=0;
                        }



                    }
                }
            }
        }
    }

}


void Hud(HUD hud[6],int tailleW,int tailleH,int ClickGauche,int mouseX,int mouseY){

    for (int i=0;i<6;i++){
        hud[i].x=tailleW/6;
        hud[i].y=tailleH+tailleH/1.5*i;
        al_draw_rectangle(tailleW/6,tailleH+tailleH/1.5*i,tailleW-tailleW/6,tailleH+tailleH/1.5*(i+1), al_map_rgb(0,0,0),3);

    }
    if (ClickGauche==1){
        for (int i=0;i<6;i++) {
            if (mouseX > hud[i].x && mouseX < tailleW - hud[i].x && mouseY > hud[i].y &&
                mouseY < tailleH + tailleH / 1.5 * (i + 1)) {
                hud[i].etat = 1;
            }
        }
    }


}

int main() {
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_TIMER *times;
    Map map[45][30];
    HUD hud[6];
    srand(time(NULL));

    ///INITIALISATION D'ALLEGRO
    assert(al_init());
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(910, 610);
    int height = al_get_display_height(display);
    int width = al_get_display_width(display);
    ALLEGRO_FONT *gameFont = al_load_ttf_font("/Users/nelkavakdjian/CLionProjects/untitled10/MagicCardsNormal.ttf", 30, ALLEGRO_ALIGN_LEFT);
    int tailleH=(height)/6;
    int tailleW=(width)/9;
    int H=(height-2*tailleH)/30;
    int W=(width-2*tailleW)/45;
    float mouse_x = 0, mouse_y = 0;

    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    times = al_create_timer(0.02);
    int isEnd = 0;
    ALLEGRO_EVENT_QUEUE* queue;
    queue = al_create_event_queue();
    assert(queue);
    ALLEGRO_EVENT event = {0};
    initialiserMap(map,hud);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(times));
    al_start_timer(times);
    while (!isEnd) {
        al_get_mouse_state(&mouse_state);
        al_wait_for_event(queue, &event); // on pioche un événement dès qu'il y en a un
        switch (event.type) { // en fonction de son type (événement de souris, du clavier...), on agit
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                isEnd = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        isEnd = 1;
                        break;
                }
                break;

        }
        Hud(hud,tailleW,tailleH,mouse_state.buttons,mouse_state.x,mouse_state.y);
        sourisCase(map,hud,mouse_state.x,mouse_state.y,tailleW,tailleH,W,H,white,gameFont,mouse_state.buttons);
        for (int i=0;i<6;i++){
            printf("%d\n",hud[i].etat);
        }
        //al_draw_rectangle(mouse_x-W/2,mouse_y-H/2,mouse_x+W/2,mouse_y+H/2,white,3);
        for (int i = 0; i < 31; i++) {
            al_draw_line(tailleW, tailleH + i * H, width - tailleW-36, tailleH + i * H, black, 1);
        }
        for (int i = 0; i < 46; i++) {
            al_draw_line(tailleW + i * W, tailleH, tailleW + i * W, height - tailleH, black, 1);
        }

        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 30; j++) {
                //al_draw_textf(gameFont, white, tailleW + W / 2 + W * i, tailleH + H / 2 + H * j, 1, "%d", j);
                //al_draw_circle(tailleW+tailleW/2+tailleW*i,tailleH+tailleH/2+tailleH*j,30,white,3);
            }
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,255));

    }
    al_destroy_event_queue(queue);





    return 0;
}
