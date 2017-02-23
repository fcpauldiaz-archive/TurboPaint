void showText(int x, int y, char color, char font[][16*16]){
  char text;
  int tempx, tempy;
  int x1 = x;
  int y1 = y;
  char erase[16][16];
  
  delay(100);
  text = 0;
  while(text!=13){
    delay(100);
    if(kbhit()) {
      text = getch();
      if (!(x1+16 < MAX_X)&&text!=8) {
        if(y1+18 < MAX_Y) {
          x1 = x;
          y1 += 18;
        } 
      }
      if(text!=13 && text!=8) {
        for(tempx=0; tempx < 16; tempx++) {
          for(tempy=0; tempy < 16; tempy++) {
            erase[tempx][tempy]=getPixel(x1+tempx,y1+tempy);
          }
        }
        putChar(x1, y1, text, color, 0, font);
        x1+=17;
      } else if(text==8 && x1!=x) {
        x1 += -17;
        for(tempx=0; tempx<16; tempx++){
          for(tempy=0; tempy<16; tempy++){
            putPixel(x1+tempx, y1+tempy,erase[tempx][tempy]);
          }
        }
      }
    }
    delay(100);
  }
}
int putChar(int x, int y, int nchar, char color, char masc, char font[][16*16]){
  int charOffs;
  char w, h;
  if(nchar >31 && nchar < 91) {
    charOffs = nchar-32;
  }else if(nchar > 96 && nchar<123){
    charOffs = nchar -2*32;
  }else{
    return 1;
  }
  for(h=0; h<16; h++) {
    for(w=0; w<16; w++) {
      if(font[charOffs][h*16+w] != masc){
        putPixel(x+w, y+h, color);
      }
    }
  }
  return 0;
}
