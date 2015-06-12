int Jogo(){
    bool desenha = false, encontro = false, encontro2 = false;
    int x_estrela = 0, x_planeta = 0;
    double mouse_x, mouse_y, dist_x, dist_y;

    /* ---------------------- */

    Cursor mouse;
    NaveEspacial nave;
    Projeteis balas[NUM_BALAS];
    NavesInimigas inimigos[NUM_INIMIGOS];
    Projeteis balas_inimigas[NUM_BALAS];

    /* ---- Inicialização da nave ---- */

    nave.tamanho_x = al_get_bitmap_width(Ship);
    nave.tamanho_y = al_get_bitmap_height(Ship);
    nave.angulo = 0;
    nave.vidas = 1000;
    nave.borda_x = nave.tamanho_x / 2;
    nave.borda_y = nave.tamanho_y / 2;
    nave.largura = 110;
    nave.altura = 110;
    nave.x = LARG / 2;
    nave.y = ALT / 2;
    nave.pontos = 0;

    srand(time(NULL));

    InitBalas(balas, NUM_BALAS);
    InitBalas(balas_inimigas, NUM_BALAS);
    InitInimigos(inimigos, NUM_INIMIGOS, nave);

    /* ---------------------- */

    al_hide_mouse_cursor(janela);
    al_start_timer(timer);

    /* ---------------------- */

    while(1){

        while(!al_is_event_queue_empty(fila_eventos_Tela1)){

            ALLEGRO_EVENT evento_Jogo;
            al_wait_for_event(fila_eventos_Tela1, &evento_Jogo);

            if(evento_Jogo.type == ALLEGRO_EVENT_KEY_DOWN){
                if(evento_Jogo.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    return 4;
                }
            }

            else if(evento_Jogo.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                return 4;
            }

            else if(evento_Jogo.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(evento_Jogo.mouse.button & 1){
                    AtiraBalas(balas, NUM_BALAS, nave);
                }
            }

            else if(evento_Jogo.type == ALLEGRO_EVENT_TIMER){

                if(x_planeta <= -1280){
                    x_planeta = 1280;
                }

                x_planeta -= 2;

                if(nave.x < mouse.x){
                    nave.dist_x = mouse.x - nave.x;
                }

                if(nave.x > mouse.x){
                    nave.dist_x = nave.x - mouse.x;
                }

                if (nave.y < mouse.y){
                    nave.dist_y = mouse.y - nave.y;
                }

                if(nave.y > mouse.y){
                    nave.dist_y = nave.y - mouse.y;
                }

                if(nave.dist_x < 100 && nave.dist_y < 100)
                    encontro = true;
                else
                    encontro = false;

                if(nave.dist_y > nave.dist_x && encontro == false){

                    if(nave.y < mouse.y){
                        nave.y += 7;
                    }

                    if(nave.y > mouse.y){
                        nave.y -= 7;
                    }

                    if(nave.x < mouse.x){
                        nave.x += nave.dist_x / (nave.dist_y / 7);
                    }

                    if(nave.x > mouse.x){
                        nave.x -= nave.dist_x / (nave.dist_y / 7);
                    }

                }

                if(nave.dist_y < nave.dist_x && encontro == false){

                    if(nave.y <= mouse.y){
                        nave.y += nave.dist_y / (nave.dist_x / 7);
                    }

                    if(nave.y > mouse.y){
                        nave.y -= nave.dist_y / (nave.dist_x / 7);
                    }

                    if(nave.x <= mouse.x){
                        nave.x += 7;
                    }

                    if(nave.x > mouse.x){
                        nave.x -= 7;
                    }

                }

                //Rotação da nave

                double dist_x2 = mouse.x - nave.x;
                double dist_y2 = mouse.y - nave.y;
                nave.angulo = atan2(dist_y2, dist_x2) + 89.4;

                for(int w = 0; w < NUM_INIMIGOS; w++){
                    double dist_x3 = nave.x - inimigos[w].x;
                    double dist_y3 = nave.y - inimigos[w].y;
                    inimigos[w].angulo = atan2(dist_y3, dist_x3) + 89.4;
                }

                for(int contador_bala = 0; contador_bala < 10; contador_bala++){
                    AtiraBalas(balas, NUM_BALAS, nave);
                }

                for(int contador_bala2 = 0; contador_bala2 < 10; contador_bala2++){
                    AtiraBalasInimigas(balas_inimigas, NUM_BALAS, inimigos);
                }

                AtualizarBalas(balas, NUM_BALAS);
                AtualizarBalas(balas_inimigas, NUM_BALAS);
                LiberaInimigos(inimigos, NUM_INIMIGOS);
                AtualizarInimigos(inimigos, NUM_INIMIGOS, nave);
                InimigoColidido(inimigos, NUM_INIMIGOS, nave);
                nave.vidas -= InimigoColidido(inimigos, NUM_INIMIGOS, nave);
                nave.pontos += BalaColidida(balas, NUM_BALAS, inimigos, NUM_INIMIGOS, nave);

                if(nave.vidas <= 0)
                    return 3;

                desenha = true;
            }

            if(desenha && al_is_event_queue_empty(fila_eventos_Tela1)){

                //----------- Câmera ------------//

                camera_atualiza(cam);
                mouse = converte_HSV(cam, mouse);

                //------------------------------//

                al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARG -20, 40, ALLEGRO_ALIGN_RIGHT, "%d", nave.pontos);
                al_draw_textf(fonte1, al_map_rgb(255, 255, 255), LARG -20, 10, ALLEGRO_ALIGN_RIGHT, "PONTOS");
                DesenhaHud(nave);
                DesenhaNave(nave);
                DesenhaBalas(balas, NUM_BALAS, nave);
                DesenhaBalasInimigas(balas_inimigas, NUM_BALAS, inimigos);
                DesenhaInimigos(inimigos, NUM_INIMIGOS, nave);
                al_draw_bitmap(Mira, mouse.x, mouse.y, 0);
                al_flip_display();
                al_draw_bitmap(Tela1, 0, 0, 0);
                al_draw_bitmap(Estrela, x_estrela, 0, 0);
                al_draw_bitmap(Planeta, x_planeta, 0, 0);

                desenha = false;
            }
        }
    }

    al_stop_timer(timer);
    al_unregister_event_source(fila_eventos_Tela1, al_get_display_event_source(janela));
    al_unregister_event_source(fila_eventos_Tela1, al_get_timer_event_source(timer));
    al_unregister_event_source(fila_eventos_Tela1, al_get_keyboard_event_source());
    al_unregister_event_source(fila_eventos_Tela1, al_get_mouse_event_source());
}
