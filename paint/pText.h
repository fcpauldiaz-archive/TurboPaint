#define ENTER 13
#define BACKSPACE 8
#define SIZE_LETTER 16

void showText(int x, int y, char color, char font[][16*16]){
  char charTxt;
  int textX, textY;
  int x1 = x;
  int y1 = y;
  char saveErase[16][16];
  
  charTxt = 0;
  while (charTxt != ENTER) {
    if (kbhit()) { //wait for char to be click
      charTxt = getch();
      if ( !(x1 + SIZE_LETTER < MAX_X) && charTxt != BACKSPACE) {
        if(y1 + SIZE_LETTER < MAX_Y) {
          x1 = x;
          y1 += 18;
        } 
      }
      if(charTxt != ENTER && charTxt != BACKSPACE) {
        for(textX=0; textX < SIZE_LETTER; textX++) {
          for(textY=0; textY < SIZE_LETTER; textY++) {
            saveErase[textX][textY] = getPixel(x1+textX, y1+textY);
          }
        }
        insertChar(x1, y1, charTxt, color, font);
        x1 += SIZE_LETTER + 1;
      } else if( charTxt == BACKSPACE && x1 != x) {
        x1 += - (SIZE_LETTER + 1);
        for (textX=0; textX < SIZE_LETTER; textX++) {
          for (textY=0; textY < SIZE_LETTER; textY++) {
            putPixel(x1 + textX, y1 + textY, saveErase[textX][textY]);
          }
        }
      }
    }
  }
}
int insertChar(int x, int y, int charNumber, char color,  char font[][16*16]){
  int offsetChar;
  char w, h;
  //caps
  if(charNumber > 31 && charNumber < 91) {
    offsetChar = charNumber - 32;
  //no caps
  } else if (charNumber > 96 && charNumber < 123){
    offsetChar = charNumber - 2*32;
  } else {
    return 1;
  }
  for (h=0; h < SIZE_LETTER; h++) {
    for (w=0; w < SIZE_LETTER; w++) {
      if (font[offsetChar][h * SIZE_LETTER + w] != 0){
        putPixel(x+w, y+h, color);
      }
    }
  }
  return 0;
}
