

void saveUndo() {
  FILE *f, *f2;
  int i, j, pixelColor;
  char line[20];
  char buf[25];
  sprintf(buf, "paint/undo-%i.txt", undoCounter);
  if (ACTIVATE_UNDO == 1) {
    f = fopen(buf, "w");
    // Se escribe las dimensiones para recorrer el archivo
    for (j=140; j <= 600; j++){
      // Se recorren los pixeles en x
      for (i=0; i <= 800; i++){
        // Se escribe en el archivo el color obtenido
        fprintf(f, "%i\n", getPixel(i,j));
      }
    }
    //finish save undo
    fprintf(f, "%i\n", 6969); 
    // Se cierra el archivo
    fclose(f);
    undoCounter = undoCounter + 1;
  }

}

void undo() {
  int x, y, x1, y1, pixelColor;
  long i, j, counter;
  FILE *f, *f2;
  char line[20]; //alocate space for line;
  char buf[25];
  undoCounter = undoCounter - 1;
  sprintf(buf, "paint/undo-%i.txt", undoCounter);
  counter = 0;
  if (ACTIVATE_UNDO == 1) {
    f = fopen(buf, "r");
    
    for (j=140; j<= 600; j++) {
      // Se recorren los pixeles en x
      for (i=0; i <= 800; i++) {
        // Se escribe en el archivo el color obtenido
        sscanf(fgets(line,sizeof(line), f), "%i", &pixelColor);
        if (pixelColor == 6969) {
          break;
        }
        putPixel(i, j, pixelColor);
      }
    }
    i = 0;
    fclose(f);

  }
}
//copy the pixels in a certain location
void copyPixels(int x1, int y1, int x2, int y2) {
  FILE *f, *f2;
  int i, j, pixelColor;
  char line[20];
  f = fopen("paint/copy.txt", "w");
  // write dimensions
  fprintf(f, "%i\n", abs(x2 - x1));
  fprintf(f, "%i\n", abs(y2 - y1));
  //y pixels
  for (j=y1; j <= y2; j++){
    // x pixels
    for (i=x1; i <= x2; i++){
      // write color to file
      fprintf(f, "%i\n", getPixel(i,j));
    }
  }
  //finish save pixels
  fprintf(f, "%i\n", 6969); 
  // Se cierra el archivo
  fclose(f);
}
//paste 
void pastePixels(int x1, int y1) {
  int x, y, dx, dy, pixelColor;
  long i, j, counter;
  FILE *f, *f2;
  char line[20]; //alocate space for line;
  
  counter = 0;
  x = 0; y = 0;
  f = fopen("paint/copy.txt", "r");
  sscanf(fgets(line,sizeof(line),f), "%i", &dx);
  sscanf(fgets(line,sizeof(line),f), "%i", &dy);
    // Mientras hayan lineas en el archivo
  while(fgets(line,sizeof(line),f) != NULL){
    // Se recorre y
    if (y < dy){
      // Se recorre x
      if (x < dx){
        int i;
        // Se obtiene el color de la linea como union de caracteres
        sscanf(line, "%i", &i);
        // Se determina si esta dentro del canvas para poder pintar
        if (x1 + x<800 && y1 + y<600){
          // Pinta el pixel
          //putPixelThickSave(x1 + x, y1 + y, i, 1, f);
          putPixel(x1 + x, y1 + y, i);
        }
        x += 1;
      }else{
        x = 0;
        y += 1;
      }
    }
  }
  fclose(f);

}