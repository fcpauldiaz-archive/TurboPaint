

void saveUndo() {
  FILE *f, *f2;
  int i, j, pixelColor;
  char line[20];
  if (ACTIVATE_UNDO == 1) {
    f = fopen("paint/undo2.txt", "w");
    f2 = fopen("paint/undo.txt", "r");
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
    while(1) {
      sscanf(fgets(line,sizeof(line), f2), "%i", &pixelColor);
      fprintf(f, "%i\n", pixelColor);
      if (pixelColor == 7070) {
        break;
      }
      
    }
    fclose(f);
    fclose(f2);
    remove("paint/undo.txt");
    rename("paint/undo2.txt", "paint/undo.txt");
  }

}

void undo() {
  int x, y, x1, y1, pixelColor;
  long i, j, counter;
  FILE *f, *f2;
  char line[20]; //alocate space for line;
  counter = 0;
  if (ACTIVATE_UNDO == 1) {
    f = fopen("paint/undo.txt", "r");
    
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
    
    //attempt to make nUndos
    f2 = fopen("paint/undo2.txt", "wb");
    while(1) {
      sscanf(fgets(line,sizeof(line), f), "%i", &pixelColor);
      if ((pixelColor == 6969 && counter == 0) || counter == 1) {
        counter = 1;
        fprintf(f2, "%i\n", pixelColor);
      }
      if (pixelColor == 7070) {
        break;
      }
      
    }
    fclose(f2);
    fclose(f);
    remove("paint/undo.txt");
    rename("paint/undo2.txt", "paint/undo.txt");
  }
}