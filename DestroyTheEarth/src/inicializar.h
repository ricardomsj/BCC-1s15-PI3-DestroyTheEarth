const int LARG = 1280;
const int ALT = 720;
const int FPS = 60;
const int NUM_INIMIGOS = 5;
const int NUM_BALAS = 10;

ALLEGRO_EVENT_QUEUE *fila_eventos_menu = NULL;
ALLEGRO_BITMAP *Menu = NULL;
ALLEGRO_BITMAP *NewGame = NULL;
ALLEGRO_BITMAP *Tutorial = NULL;
ALLEGRO_BITMAP *Sair = NULL;
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos_tuto = NULL;
ALLEGRO_BITMAP *Tuto = NULL;
ALLEGRO_BITMAP *Voltar = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos_over = NULL;
ALLEGRO_BITMAP *GameOver = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos_Tela1 = NULL;
ALLEGRO_BITMAP *Tela1 = NULL;
ALLEGRO_BITMAP *TelaEstrela = NULL;
ALLEGRO_BITMAP *Planeta = NULL;
ALLEGRO_BITMAP *Ship = NULL;
ALLEGRO_BITMAP *Shot = NULL;
ALLEGRO_BITMAP *Hud1 = NULL;
ALLEGRO_BITMAP *Hud2 = NULL;
ALLEGRO_BITMAP *Hud3 = NULL;
ALLEGRO_BITMAP *Hud4 = NULL;
ALLEGRO_BITMAP *Hud5 = NULL;
ALLEGRO_BITMAP *Enemy = NULL;
ALLEGRO_BITMAP *buffer = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer_menu = NULL;
ALLEGRO_TIMER *timer_tuto = NULL;
ALLEGRO_SAMPLE *intro = NULL;
ALLEGRO_SAMPLE *tiro = NULL;
ALLEGRO_FONT *fonte1 = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_BITMAP *Mira = NULL;

typedef struct {
  unsigned char ***quadro;
  int largura, altura;
  CvCapture *capture;
} camera;

camera *cam = NULL;

typedef struct {
    int ID;
    double x;
    double y;
    float tamanho_x;
    float tamanho_y;
    double angulo;
    int vidas;
    int velocidade;
    int borda_x;
    int borda_y;
    int pontos;
    int largura;
    int altura;
    double dist_x;
    double dist_y;
} NaveEspacial;

typedef struct {
    int ID;
    int x;
    int y;
    int velocidade;
    int velocidade_x;
    int velocidade_y;
    bool ativo;
} Projeteis;

typedef struct {
    int ID;
    int x;
    int y;
    int velocidade;
    int velocidade_x;
    int velocidade_y;
    int borda_x;
    int borda_y;
    int largura;
    int altura;
    bool ativo;
    double dist_x;
    double dist_y;
    double angulo;
} NavesInimigas;

typedef struct {
    double x;
    double y;
} Cursor;

/**********************************************************************/

void camera_converte(camera *cam, IplImage *image) {
  char *row = image->imageData;

  for(int y = 0; y < cam->altura; y++) {
    char *pixel = row;

    for(int x = cam->largura - 1; x >= 0; x--) {
      cam->quadro[y][x][2] = *pixel;
      pixel++;

      cam->quadro[y][x][1] = *pixel;
      pixel++;

      cam->quadro[y][x][0] = *pixel;
      pixel++;
    }

    row += image->widthStep;
  }
}

unsigned char ***camera_aloca_matriz(camera *cam) {
  unsigned char ***matriz = malloc(cam->altura * sizeof(unsigned char **));

  for(int y = 0; y < cam->altura; y++) {
    matriz[y] = malloc(cam->largura * sizeof(unsigned char *));

    for(int x = 0; x < cam->largura; x++)
      matriz[y][x] = malloc(3 * sizeof(unsigned char));
  }

  return matriz;
}

camera *camera_inicializa(int i) {
  CvCapture *capture = cvCaptureFromCAM(i);

  if(capture) {
    IplImage *image = cvQueryFrame(capture);

    if(image) {
      cam = malloc(sizeof(camera));

      cam->capture = capture;
      cam->altura = image->height;
      cam->largura = image->width;
      cam->quadro = camera_aloca_matriz(cam);

      camera_converte(cam, image);
    }
    
    else
      cvReleaseCapture(&capture);
  }

  return cam;
}

void camera_libera_matriz(camera *cam, unsigned char ***matriz) {
  for(int y = 0; y < cam->altura; y++) {
    for(int x = 0; x < cam->largura; x++)
      free(matriz[y][x]);

    free(matriz[y]);
  }

  free(matriz);
}

void camera_finaliza(camera *cam) {
  camera_libera_matriz(cam, cam->quadro);

  cvReleaseCapture(&cam->capture);

  free(cam);
}

/**********************************************************************/

bool inicializar(){

    camera *cam = camera_inicializa(0);
  
    if(!cam){
        fprintf(stderr, "%s\n", "Nao foi possivel inicializar camera.");
    return false;
    }

    int largura = cam->largura;
      
    int altura = cam->altura;

    if(!al_init()){
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        camera_finaliza(cam);
    return false;
    }

    if(!al_init_image_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        camera_finaliza(cam);
    return false;
    }

    if(!al_install_keyboard()){
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        camera_finaliza(cam);
    return false;
    }

    if(!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        camera_finaliza(cam);
    return false;
    }

    timer = al_create_timer(1.0 / FPS);

    if(!timer){
        fprintf(stderr, "Falha ao criar timer!\n");
        camera_finaliza(cam);
    return false;
    }

    timer_menu = al_create_timer(1.0 / FPS);

    if(!timer_menu){
        fprintf(stderr, "Falha ao criar timer de menu!\n");
        camera_finaliza(cam);
    return false;
    }

    timer_tuto = al_create_timer(1.0 / FPS);

    if(!timer_tuto){
        fprintf(stderr, "Falha ao criar timer de tutorial!\n");
        camera_finaliza(cam);
    return false;
    }

    fila_eventos_menu = al_create_event_queue();

    if(!fila_eventos_menu){
        fprintf(stderr, "Falha ao criar fila de eventos de menu.\n");
        camera_finaliza(cam);
    return false;
    }

    fila_eventos_tuto = al_create_event_queue();

    if(!fila_eventos_tuto){
        fprintf(stderr, "Falha ao criar fila de eventos de tutorial.\n");
        camera_finaliza(cam);
    return false;
    }

    fila_eventos_over = al_create_event_queue();

    if(!fila_eventos_over){
        fprintf(stderr, "Falha ao criar fila de eventos de tutorial.\n");
    return false;
    }

    fila_eventos_Tela1 = al_create_event_queue();

    if(!fila_eventos_Tela1){
        fprintf(stderr, "Falha ao criar fila de eventos de Tela1.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
    return false;
    }

    janela = al_create_display(LARG, ALT);

    if(!janela){
        fprintf(stderr, "Falha ao criar janela.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
    return false;
    }

    al_set_window_position(janela, 40, 11.5);

    al_set_window_title(janela, "Destroy The Earth");

    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_event_queue(fila_eventos_tuto);
        al_destroy_display(janela);
        return -1;
    }

    // Inicialização do add-on para uso de fontes
    al_init_font_addon();
 
    // Inicialização do add-on para uso de fontes True Type
    if (!al_init_ttf_addon()){
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        camera_finaliza(cam);
        return -1;
    }

    if (!al_install_audio()){
        fprintf(stderr, "Falha ao inicializar áudio.\n");
        camera_finaliza(cam);
        return false;
    }

    if (!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
        camera_finaliza(cam);
        return false;
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "Falha ao alocar canais de áudio.\n");
        camera_finaliza(cam);
        return false;
    }

    tiro = al_load_sample("shot.ogg");

    if (!tiro){
        fprintf(stderr, "Falha ao carregar tiro.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
        return false;
    }

    intro = al_load_sample("intro.ogg");

    if(!intro){
        fprintf(stderr, "Falha ao carregar musica de introducao.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    buffer = al_get_backbuffer(janela);

    if(!buffer){
        fprintf(stderr, "%s\n", "Falha ao criar buffer.");
        camera_finaliza(cam);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
        al_destroy_timer(timer);
    return false;
    }

    Ship = al_load_bitmap("Ship.png");

    if(!Ship){
        fprintf(stderr, "Falha ao carregar imagem de Nave.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Enemy = al_load_bitmap("Enemy.png");

    if(!Enemy){
        fprintf(stderr, "Falha ao carregar imagem de Inimigo.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Mira = al_load_bitmap("Mira.png");

    if(!Mira){
        fprintf(stderr, "Falha ao carregar imagem de Mira.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Shot = al_load_bitmap("Shot.png");

    if(!Shot){
        fprintf(stderr, "Falha ao carregar imagem de Tiro.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Tela1 = al_load_bitmap("Fundo.png");

    if(!Tela1){
        fprintf(stderr, "Falha ao carregar imagem de Galáxia de Andrômeda.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    TelaEstrela = al_load_bitmap("Estrelas.png");

    if(!TelaEstrela){
        fprintf(stderr, "Falha ao carregar imagem do fundo estrelas.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Planeta = al_load_bitmap("Planeta1.png");

    if(!Planeta){
        fprintf(stderr, "Falha ao carregar imagem do fundo planeta1.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Hud1 = al_load_bitmap("1.png");

    if(!Hud1){
        fprintf(stderr, "Falha ao carregar imagem do hud1.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Hud2 = al_load_bitmap("2.png");

    if(!Hud2){
        fprintf(stderr, "Falha ao carregar imagem do hud2.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Hud3 = al_load_bitmap("3.png");

    if(!Hud3){
        fprintf(stderr, "Falha ao carregar imagem do hud3.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Hud4 = al_load_bitmap("4.png");

    if(!Hud4){
        fprintf(stderr, "Falha ao carregar imagem do hud4.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Hud5 = al_load_bitmap("5.png");

    if(!Hud5){
        fprintf(stderr, "Falha ao carregar imagem do hud5.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_display(janela);
    return false;
    }

    Tuto = al_load_bitmap("Tuto.png");

    if(!Tuto){
        fprintf(stderr, "Falha ao carregar imagem de tutorial.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    GameOver = al_load_bitmap("GameOver.png");

    if(!GameOver){
        fprintf(stderr, "Falha ao carregar imagem de game over.\n");
        al_destroy_event_queue(fila_eventos_over);
        al_destroy_display(janela);
    return false;
    }

    Voltar = al_load_bitmap("Voltar.png");

    if(!Voltar){
        fprintf(stderr, "Falha ao carregar imagem de Voltar.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Menu = al_load_bitmap("Menu.png");

    if(!Menu){
        fprintf(stderr, "Falha ao carregar imagem de Menu.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    NewGame = al_load_bitmap("NewGame.png");

    if(!NewGame){
        fprintf(stderr, "Falha ao carregar imagem de NewGame.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Tutorial = al_load_bitmap("Tutorial.png");

    if(!Tutorial){
        fprintf(stderr, "Falha ao carregar imagem de Tutorial.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    Sair = al_load_bitmap("Sair.png");

    if(!Sair){
        fprintf(stderr, "Falha ao carregar imagem de Sair.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_event_queue(fila_eventos_menu);
        al_destroy_event_queue(fila_eventos_Tela1);
        al_destroy_display(janela);
    return false;
    }

    fonte = al_load_ttf_font("Fonte.TTF", 48, 0);

    if(!fonte){
        fprintf(stderr, "Falha ao carregar fonte.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_display(janela);
        return false;
    }

    fonte1 = al_load_ttf_font("Fonte.TTF", 30, 0);
    
    if(!fonte1){
        fprintf(stderr, "Falha ao carregar fonte.\n");
        camera_finaliza(cam);
        al_destroy_timer(timer);
        al_destroy_display(janela);
        return false;
    }

    al_register_event_source(fila_eventos_menu, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos_menu, al_get_mouse_event_source());
    al_register_event_source(fila_eventos_menu, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos_menu, al_get_timer_event_source(timer_menu));

    al_register_event_source(fila_eventos_tuto, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos_tuto, al_get_mouse_event_source());
    al_register_event_source(fila_eventos_tuto, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos_tuto, al_get_timer_event_source(timer_tuto));

    al_register_event_source(fila_eventos_over, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos_over, al_get_mouse_event_source());
    al_register_event_source(fila_eventos_over, al_get_display_event_source(janela));
    
    al_register_event_source(fila_eventos_Tela1, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos_Tela1, al_get_mouse_event_source());
    al_register_event_source(fila_eventos_Tela1, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos_Tela1, al_get_timer_event_source(timer)); 

    return true;
}
