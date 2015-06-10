void camera_atualiza(camera *cam) {
  IplImage *image = cvQueryFrame(cam->capture);

  if(image)
    camera_converte(cam, image);
}

float maximo(float f_r, float f_g, float f_b){

  float MAX;

  MAX = f_b;  
  
  if(f_r > MAX)  
    MAX = f_r;  
  
  if(f_g > MAX)  
    MAX = f_g;  

  return MAX;
}

float minimo(float f_r, float f_g, float f_b){

  float MIN;

  MIN = f_b;
  
  if(f_r < MIN)
    MIN = f_r;  
  
  if(f_g < MIN)  
    MIN = f_g;

  return MIN;
}

Cursor converte_HSV(camera *cam, Cursor mouse){

  float cy = 0;
  float cx = 0;
  float cn = 0;

  // Pegar os pixels RGB (BGR em OpenCV!)

  for(int y = 0; y < cam->altura; y++){
    for(int x = 0; x < cam->largura; x++) {

      int r = cam->quadro[y][x][0];
      int g = cam->quadro[y][x][1];
      int b = cam->quadro[y][x][2];

      // De int para float

      float vermelho = r * 1.0;
      float verde = g * 1.0;
      float azul = b * 1.0;

      // Garantindo que não ultapassem de 1.0

      float f_r = vermelho / 255;
      float f_g = verde / 255;
      float f_b = azul / 255;

      float H;

      float MAX = maximo(f_r, f_g, f_b);

      float MIN = minimo(f_r, f_g, f_b);

      float DELTA = MAX - MIN;

      float V = MAX * 100;

      float S;

      if(MAX != 0)
        S = (DELTA / MAX) * 100;

      else {
        S = 0;
        H = 0;
        V = V * 1.0;
        
        return mouse;
      }

      if(f_r == MAX){
        H = (f_g - f_b)/DELTA;
      }

      else if(f_g == MAX){
        H = 60 * (((f_b - f_r)/DELTA) + 2) ;
      }

      else{
        H = 60 * (((f_r - f_g) / DELTA) + 4);
      }

      if(H < 0)
        H += 360;

      // De float para int

      int iH = H * 1.0;
      int iS = S * 1.0;
      int iV = V * 1.0;

      if(iH >= 30 && iS >= 50 && iV >= 70){
        cx += x;
        cy += y;
        cn += 1;
      }
    }
  }

  mouse.x = 2 * (cx / cn);
  mouse.y = 2 * (cy / cn);

  return mouse;
}