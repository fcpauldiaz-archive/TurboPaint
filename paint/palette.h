
void paintFewPalette();
void paintFullPalette();

void paintCanvas() {
  int i, j;
  for (i=0; i < 800; i++) {
    for (j=140; j < 600 ;j++) {
      putPixel(i, j, 255);
    }
  }
}
//paints the available palette
void paintPalette(int full) {
  if (full == 1) {
    paintFullPalette();
  }
  else {
    paintFewPalette();
  }
}

//PAINT FEW COLORS
void paintFewPalette() {
 int i, j, color;
  color = 0;

  for(j=526; j < 794; color = color + 5){
    for(i=30; i < 50;i++){
      putPixelWidth(j, i, color, 10);
    }
    j = j + 10;
  }

  for(j=526; j < 794; color = color + 5){
    for(i=61; i < 80;i++){
      putPixelWidth(j, i, color, 10);
    }
    j = j + 10;
  }
  //prints 270 colors
  //printf("%d\n", color);
}

//PAINT THE 256 COLORS
void paintFullPalette() {
  int i, j, color;
  color = 0;
  for(j=526; j < 794;color++){
    for(i=30; i < 40;i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for(j=526; j < 794; color++){
    for(i=41; i<50;i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for(j=526; j < 794; color++){
    for(i=51; i<60;i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for(j=526; j < 794; color++){
    for(i=61; i < 70;i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for(j=526; j < 724; color++){
    for(i=71; i<80;i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  //prints 255 colors
}