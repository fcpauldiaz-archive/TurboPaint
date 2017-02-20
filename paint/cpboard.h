

void saveUndo() {
  FILE *f;
  int i, j;
  f = fopen("paint/undo.txt", "w");
  
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
}

void undo() {
  int x, y, x1, y1, pixelColor;
  long i, j, counter;
  FILE *f, *f2;
  char line[20]; //alocate space for line;
  counter = 0;
  f = fopen("paint/undo.txt", "r");
  
  for (j=140; j<= 600; j++) {
    // Se recorren los pixeles en x
    for (i=0; i <= 800; i++) {
      // Se escribe en el archivo el color obtenido
      sscanf(fgets(line,sizeof(line), f), "%i", &pixelColor);
      if (pixelColor == 6969) {
        printf("%d\n", counter);
        break;
      }
      putPixel(i, j, pixelColor);
    }
  }
  i = 0;
  
  //attempt to make nUndos
  /*
  printf("%d\n", counter);
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
  printf("%d\n", rename("paint/undo2.txt", "paint/undo.txt"));*/
  fclose(f);
}