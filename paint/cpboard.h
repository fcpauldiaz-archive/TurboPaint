

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
  // Se escribe las dimensiones para recorrer el archivo
  for (j=y1; j <= y2; j++){
    // Se recorren los pixeles en x
    for (i=x1; i <= x2; i++){
      // Se escribe en el archivo el color obtenido
      fprintf(f, "%i\n", getPixel(i,j));
    }
  }
  //finish save pixels
  fprintf(f, "%i\n", 6969); 
  // Se cierra el archivo
  fclose(f);
}