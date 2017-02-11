
#include <time.h>

#define x1_Draw 0
#define y1_Draw 140
#define x2_Draw 800
#define y2_Draw 600

int forceDraw = 0;
int tmp;


int ipart_(X) {
  return ((int)(X));
}
int round_(x) { 
  return ipart_(x + 0.5);
}
float fpart_(x) {
 if (x < 0) {
  return 1 - (x - floor(x));
 }
 return x - floor(x);
}

float rfpart_(int X) {
 return (1.0-fpart_(X));
}

int sign(x) {
  if (x < 0) {
    return -1;
  }
  if (x > 0) {
    return 1;
  }
  return 0;
}
 



void plot_(int x, int y, int color) {
  putPixelWidth(x, y, color, 15);
}
void draw_line_antialias(
  unsigned int x1, unsigned int y1,
  unsigned int x2, unsigned int y2,
  int color)
{
  double dx = (double)x2 - (double)x1;
  double dy = (double)y2 - (double)y1;
  int steep = fabs(dy) > fabs(dx);
  double gradient, intery;
  int xend, yend, xgap, xpxl1, ypxl1, xpxl2, ypxl2;
  int x;
  if (steep) {
    tmp = x1; x1 = y1; y1 = tmp; 
    tmp = y2; y2 = x2; x2 = tmp; 
  }
  if (x1 > x2) {
    tmp = x1; x1 = x2; x2 = tmp; 
    tmp = y1; y1 = y2; y2 = tmp; 
  }
  dx = x2 - x1;
  dy = y2 - y1;
  gradient = dy/dx;
  if (dx == 0.0) {
    gradient = 0.0;
  }
  xend = round_(x1);
  yend = y1 + gradient * (xend - x1);
  xgap = rfpart_(x1 + 0.5);
  xpxl1 = xend;
  ypxl1 = ipart_(yend);
  if (steep) {
    plot_(ypxl1, xpxl1, color);
    plot_(ypxl1+1, xpxl1, color);
  }
  else {
    plot_(xpxl1, ypxl1, color);
    plot_(xpxl1, ypxl1+1, color);
  }
  intery = yend + gradient;
  xend = round_(x2);
  yend = y2 + gradient * (xend - x2);
  xgap = fpart_(x2 + 0.5);
  xpxl2 = xend; //this will be used in the main loop
  ypxl2 = ipart_(yend);
  if (steep) {
      plot_(ypxl2  , xpxl2, color);
      plot_(ypxl2+1, xpxl2, color);
    }
  else{
      plot_(xpxl2, ypxl2,  color);
      plot_(xpxl2, ypxl2+1, color);
  }
  
  // main loop
  if (steep) {
    for(x=xpxl1+1; x <= (xpxl2-1); x++) {
      plot_(x, ipart_(intery), color);
      plot_(x, ipart_(intery) + 1, color);
      intery += gradient;
    }
  }
  else {
     for(x=xpxl1+1; x <= (xpxl2-1); x++) {
      plot_(x, ipart_(intery), color);
      plot_(x, ipart_(intery)+1, color);
      intery += gradient;
    }
  }
}
//Digital Differential Analyzer (DDA) algorithm 
//https://www.tutorialspoint.com/computer_graphics/line_generation_algorithm.htm
void drawLine(int x1, int y1, int x2, int y2, int color, int width) {
  int i;
  int sdx, sdy;
  float x, y;
  float pixels_x,  pixels_y;
  int dx = x2 - x1;
  int dy = y2 - y1;
  float steps;
  //decides direction to paint
  sdx = sign(dx);
  sdy = sign(dy);

  x = fabs(dy)/2.0;
  y = fabs(dx)/2.0; 

  pixels_x = x1;
  pixels_y = y1;
  //difference from x is bigger
  if (fabs(dx) >= fabs(dy)){
    steps = fabs(dx);
    x = dx/(float)steps;
    y = dy/(float)steps;
    for (i=0; i < steps; i++) {
      pixels_x = pixels_x + x;
      pixels_y = pixels_y + y;
      if (forceDraw == 1 || pixels_x > x1_Draw && pixels_x < x2_Draw &&  pixels_y > y1_Draw &&  pixels_y < y2_Draw)
        putPixelWidth((int)pixels_x, (int)pixels_y,color, width);
    }
  } else {
    steps = fabs(dy);
    x = dx/(float)steps;
    y = dy/(float)steps;
    for (i=0; i < steps; i++) {
      pixels_x = pixels_x + x;
      pixels_y = pixels_y + y;
      if (forceDraw == 1 || pixels_x > x1_Draw && pixels_x < x2_Draw &&  pixels_y > y1_Draw &&  pixels_y < y2_Draw)
        putPixelWidth((int)pixels_x, (int)pixels_y,color, width);
    }
  }
}

//draw rectangle with no fill
void drawRectangle(int x1, int y1, int x2, int y2, int color, int width) {
  drawLine(x1,y1,x2,y1,color,width);
  drawLine(x1,y1,x1,y2,color,width);
  drawLine(x2,y1,x2,y2,color,width);
  drawLine(x1,y2,x2,y2,color,width);
}

//this results to be innecefient
/*
void paintRectangle(int x1, int y1, int x2, int y2, int outerColor, int innerColor, int width) {
  int i, x3, x4, y3, y4;
  drawRectangle(x1, y1, x2, y2, outerColor, width);
  x3 = x1 + width;
  for (i = x3; i < x2; i++) {
    drawRectangle(i, y1+width, x2-width, y2, innerColor, 1);
  }
}*/

void paintRectangle(int x1, int y1, int x2, int y2, int outerColor, int innerColor, int width) {
  int i;
  for (i = y1; i < y2; i++) {
    drawLine(x1, i, x2, i, innerColor, 1);
  }
  drawRectangle(x1, y1, x2, y2, outerColor, width);
}

