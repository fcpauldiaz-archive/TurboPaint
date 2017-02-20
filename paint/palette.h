
void paintFewPalette();
void paintFullPalette();
void paintColorPickerOne();
void paintColorPickerTwo();

void paintCanvas() {
  int i, j;
  for (i=0; i < 800; i++) {
    for (j=140; j < 600; j++) {
      putPixel(i, j, 255);
    }
  }
}
//paints the available palette
void paintPalette(int full) {
  FILE *f;
  forceDraw = 1;
  if (full == 1) {
    paintFullPalette();
  }
  else {
    paintFewPalette();
  }
  paintColorPickerOne(COLOR_FILL_1);
  paintColorPickerTwo(COLOR_FILL_2);
  forceDraw  = 0;
}

//PAINT FEW COLORS
void paintFewPalette() {
 int i, j, color;
  color = 0;

  for(j=526; j < 794; color = color + 5) {
    for(i=30; i < 50;i++){
      putPixelWidth(j, i, color, 10);
    }
    j = j + 10;
  }

  for(j=526; j < 794; color = color + 5) {
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
  for (j=526; j < 794; color++) {
    for (i=30; i < 40; i++) {
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for (j=526; j < 794; color++) {
    for (i=41; i < 50; i++){ 
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for (j=526; j < 794; color++) {
    for (i=51; i < 60; i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for (j=526; j < 794; color++) {
    for (i=61; i < 70; i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  for (j=526; j < 724; color++) { 
    for (i=71; i < 80; i++){
      putPixelWidthX(j, i, color, 5);
    }
    j = j + 5;
  }
  //prints 255 colors
}

void paintColorPickerOne(int color) {
  forceDraw = 1;
  paintRectangle(526, 95, 565, 130, 0, color, 2);
  forceDraw = 0;
}

void paintColorPickerTwo(int color) {
  forceDraw = 1;
  paintRectangle(568, 95, 610, 130, 0, color, 2);
  forceDraw = 0;
}