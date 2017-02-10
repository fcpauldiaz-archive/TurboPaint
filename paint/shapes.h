
#include <time.h>

#define x1_Draw 0
#define y1_Draw 140
#define x2_Draw 800
#define y2_Draw 600

int drawGUI = 1;
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
void drawLine(int x1, int y1, int x2, int y2, int color, int width) {
  int i;
  int sdx, sdy;
  int x, y, px, py;
  int dx = x2 - x1;
  int dy = y2 - y1;

  sdx = sign(dx);
  sdy = sign(dy);

  x = fabs(dy)/2.0;
  y = fabs(dx)/2.0; 

  px = x1;
  py = y1;
 
  if (fabs(dx) >= fabs(dy)){
    for (i=0; i < fabs(dx); i++) {
      y += fabs(dy);
      if ( y >= fabs(dx)){
        y -= fabs(dx);
        py += sdy;
      }
      px += sdx;
      if (px > x1_Draw && px < x2_Draw && py > y1_Draw && py < y2_Draw)
        putPixelWidth(px,py,color, width);
    }
  } else {
    for( i=0; i < fabs(dy);i++) {
      x += fabs(dx);
      if (x >= fabs(dy)){
        x -= fabs(dy);
        px += sdx;
      }
      py += sdy;
      if (px > x1_Draw && px < x2_Draw && py > y1_Draw && py < y2_Draw)
        putPixelWidth(px,py,color, width);
    }
  }
}