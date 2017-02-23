
#include <time.h>

int tmp;

void ellipse(float xc, float yc, float x, float y, int color, int width);
int searchCoord(int x1, int y2);

void savePixel(int x1, int y1, int x2, int y2, int width);

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
//NOT WORKING
void draw_line_antialias(
  unsigned int x1, unsigned int y1,
  unsigned int x2, unsigned int y2,
  int color)
{
  double dx = (double)x2 - (double)x1;
  double dy = (double)y2 - (double)y1;
  int steep = fabs(dy) > fabs(dx);
  double gradient, intery;
  int xend, yend, xpxl1, ypxl1, xpxl2, ypxl2;
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
      if (forceDraw == 1 || 
          pixels_x > x1_Draw && 
          pixels_x < x2_Draw &&  
          pixels_y > y1_Draw &&  
          pixels_y < y2_Draw)
        putPixelWidth((int)pixels_x, (int)pixels_y,color, width);
    }
  } else {
    steps = fabs(dy);
    x = dx/(float)steps;
    y = dy/(float)steps;
    for (i=0; i < steps; i++) {
      pixels_x = pixels_x + x;
      pixels_y = pixels_y + y;
      if (forceDraw == 1 || 
          pixels_x > x1_Draw && 
          pixels_x < x2_Draw &&  
          pixels_y > y1_Draw &&  
          pixels_y < y2_Draw)
        putPixelWidth((int)pixels_x, (int)pixels_y,color, width);
    }
  }
}

//REPAINT THE PIXELS SAVED IN FILE
//THIS BECOMES INNEFICIENT WITH MORE WIDTH LINE
//https://www.tutorialspoint.com/computer_graphics/line_generation_algorithm.htm
void reDrawLine(int x1, int y1, int x2, int y2, int width) {
  int i, j, k;
  int sdx, sdy;
  float x, y;
  float pixels_x,  pixels_y;
  int dx = x2 - x1;
  int dy = y2 - y1;
  float steps;
  char line[20];
  int pixel;
  FILE *file;
  file = fopen("paint/pixels.txt", "r");

  //decides direction to paint
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
      if (forceDraw == 1 || 
          pixels_x > x1_Draw && 
          pixels_x < x2_Draw &&  
          pixels_y > y1_Draw &&  
          pixels_y < y2_Draw)
         for (k = 0; k < width; k++) {
          for ( j = 0; j < width; j++) {
            sscanf(fgets(line,sizeof(line),file), "%i", &pixel);
            putPixel((int)pixels_x + j, (int)pixels_y + k, pixel);
          }
        }
    }
  } else {
    steps = fabs(dy);
    x = dx/(float)steps;
    y = dy/(float)steps;
    for (i=0; i < steps; i++) {
      pixels_x = pixels_x + x;
      pixels_y = pixels_y + y;
      if (forceDraw == 1 || 
          pixels_x > x1_Draw && 
          pixels_x < x2_Draw &&  
          pixels_y > y1_Draw &&  
          pixels_y < y2_Draw)
      for (k = 0; k < width; k++) {
          for ( j = 0; j < width; j++) {
            sscanf(fgets(line,sizeof(line),file), "%i", &pixel);
            putPixel((int)pixels_x + j, (int)pixels_y + k, pixel);
          }
        }
    }
  }
  fclose(file);
}

void savePixel(int x1, int y1, int x2, int y2, int width) {
  int i, j, k;
  int sdx, sdy;
  float x, y;
  float pixels_x,  pixels_y;
  int dx = x2 - x1;
  int dy = y2 - y1;
  float steps;
  FILE *file;

  //decides direction to paint
  file = fopen("paint/pixels.txt","w");
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
        for (k = 0; k < width; k++) {
          for ( j = 0; j < width; j++) {
            fprintf(file, "%i\n", getPixel(pixels_x + j, pixels_y + k)); 
          }
        }

    }
  } else {
    steps = fabs(dy);
    x = dx/(float)steps;
    y = dy/(float)steps;
    for (i=0; i < steps; i++) {
      pixels_x = pixels_x + x;
      pixels_y = pixels_y + y;
      if (forceDraw == 1 || pixels_x > x1_Draw && pixels_x < x2_Draw &&  pixels_y > y1_Draw &&  pixels_y < y2_Draw)
        for (k = 0; k < width; k++) {
          for ( j = 0; j < width; j++) {
            fprintf(file, "%i\n", getPixel(pixels_x + j, pixels_y + k)); 
          }
        }
    }
  }
  fclose(file);
}



//draw rectangle with no fill
void drawRectangle(int x1, int y1, int x2, int y2, int color, int width) {
  drawLine(x1,y1,x2,y1,color,width);
  drawLine(x1,y1+1,x1,y2,color,width);
  drawLine(x2,y1+1,x2,y2,color,width);
  drawLine(x1+1,y2,x2-1,y2,color,width);
}

void savePixelRectangle(int x1, int y1, int x2, int y2, int width) {
  savePixel(x1,y1,x2,y1,width);
  savePixel(x1,y1,x1,y2,width);
  savePixel(x2,y1,x2,y2,width);
  savePixel(x1,y2,x2,y2,width);
}

void reDrawRectangle(int x1, int y1, int x2, int y2, int width) {
  reDrawLine(x1,y1,x2,y1,width);
  reDrawLine(x1,y1+1,x1,y2,width);
  reDrawLine(x2,y1+1,x2,y2,width);
  reDrawLine(x1+1,y2,x2-1,y2,width);
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
//mid point algorithim
//https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void drawCircle(int x0, int y0, int radius, int color, int width) {
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    if (y0 + y >= y1_Draw && y0 + x >= y1_Draw && y0 - y >= y1_Draw && y0 - x >= y1_Draw) {
      //paints the bottom rigth corner
      putPixelWidth(x0 + x, y0 + y, color, width);
      putPixelWidth(x0 + y, y0 + x, color, width);
      //paints the bottom left corner
      putPixelWidth(x0 - y, y0 + x, color, width);
      putPixelWidth(x0 - x, y0 + y, color, width);
      //paints the upper left corner
      putPixelWidth(x0 - x, y0 - y, color, width);
      putPixelWidth(x0 - y, y0 - x, color, width);
      //paints the upper right corner
      putPixelWidth(x0 + y, y0 - x, color, width);
      putPixelWidth(x0 + x, y0 - y, color, width);
    }
    if (err <= 0) {
        y = y + 1;
        err += 2*y + 1;
    }
    if (err > 0) {
        x = x - 1;
        err -= 2*x + 1;
    }
  }
}

//Unaccurate paint circle algorithim
/*
void paintCircle(int x0, int y0, int radius, int color) {
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
      drawLine(x0 + y, y0 + x, x0 - y, y0 + x, color, 1);
      drawLine(x0 - x, y0 + y, x0 + x, y0 + y, color, 1);
      drawLine(x0 - y, y0 - x, x0 + y, y0 - x, color, 1);
      drawLine(x0 + x, y0 - y, x0 - x, y0 - y, color, 1);
      if (err <= 0) {
          y = y + 1;
          err += 2*y + 1;
      }
      if (err > 0) {
          x = x - 1;
          err -= 2*x + 1;
      }
  }
}*/
void paintCircle(int x0, int y0, int radius, int outerColor, int innerColor, int width) {
    int i;
    int x = radius-1;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y) {
        //inner part
        for (i = x0 - x; i <= x0 + x; i++) {
          if (y0 + y >= y1_Draw && y0 - y >= y1_Draw) {
            putPixel(i, y0 + y, innerColor);
            putPixel(i, y0 - y, innerColor);
          }
        }
        //outer part
        for (i = x0 - y; i <= x0 + y; i++) {
          if (y0 + x >= y1_Draw && y0 - x >= y1_Draw) {
            putPixel(i, y0 + x, innerColor);
            putPixel(i, y0 - x, innerColor);
          }
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0) {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
    drawCircle(x0, y0, radius, outerColor, width);
}
//mid point for ellipse
//http://tutsheap.com/c/mid-point-ellipse-drawing-algorithm/
void drawEllipse(float xc, float yc, float rx, float ry, int color, int width) {
  float rxSq = rx * rx;
  float rySq = ry * ry;
  float x = 0, y = ry, p;
  float px = 0, py = 2 * rxSq * y;

  ellipse(xc, yc, x, y, color, width);

  //Region 1, esquinas sup, infr.
  p = rySq - (rxSq * ry) + (0.25 * rxSq);
  while (px < py) {
      x++;
      px = px + 2 * rySq;
      if (p < 0)
          p = p + rySq + px;
      else {
          y--;
          py = py - 2 * rxSq;
          p = p + rySq + px - py;
      }
      ellipse(xc, yc, x, y, color, width);
  }

  //Region 2,  2 esquinas izq, der
  p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
  while (y > 0) {
      y--;
      py = py - 2 * rxSq;
      if (p > 0) {
          p = p + rxSq - py;
      }
      else {
          x++;
          px = px + 2 * rySq;
          p = p + rxSq - py + px;
      }
      ellipse(xc, yc, x, y, color, width);
  }
}
//http://tutsheap.com/c/mid-point-ellipse-drawing-algorithm/
void ellipse(float xc, float yc, float x, float y, int color, int width) {
  //parte de abajo
  putPixelWidth(xc + x, yc + y, color, width); //der
  putPixelWidth(xc - x, yc + y, color, width); //izq
  if (yc - y <= y1_Draw) return; //validate tools
  //parte de arriba
  putPixelWidth(xc + x, yc - y, color, width);  //der
  putPixelWidth(xc - x, yc - y, color, width); //izq
}

void paintEllipse(int x0, int y0, int radiousX, int radiousY, int outerColor, char innerColor, int width) {
  short x_min_limit, x_max_limit, y_min_limit, y_max_limit;
  short sqr;
  short x, y;
  float d;

  y_min_limit = y0-radiousY;
  y_max_limit = y0+radiousY;
  if (y_min_limit < y1_Draw)  
    y_min_limit = y1_Draw;
  if (y_max_limit >= y2_Draw) 
    y_max_limit = y2_Draw;
  for (y=y_min_limit; y <= y_max_limit; y++) {
    d = (y-y0)/(radiousY+0.5); // para que no sea cero
    sqr = sqrt(1.0 - d * d) * (radiousX + 0.5);
    x_min_limit = x0 - sqr;
    x_max_limit = x0 + sqr;
    if (x_min_limit < 0)  
      x_min_limit = 0;
    if (x_max_limit >= x2_Draw) 
      x_max_limit = x2_Draw;
    if (x_max_limit >= x_min_limit){
      drawLine(x_min_limit, y, x_max_limit, y, innerColor, 1);
    }
  }
  drawEllipse(x0,y0, radiousX, radiousY, outerColor, width);

}

// SCAN LINE ALGORITHM
// http://code-heaven.blogspot.com/2009/10/simple-c-program-for-scan-line-polygon.html
void scanLine(int cant_edges, int color, int width) {
  int i,j,k,gd,gm,dy,dx;
  int x,y,temp;
  int xi[100];
  float slope[100];

  vertex[cant_edges][0] = vertex[0][0];
  vertex[cant_edges][1] = vertex[0][1];

  for(i=0; i < cant_edges; i++) {
    //get differential
    dy = vertex[i+1][1] - vertex[i][1];
    dx = vertex[i+1][0] - vertex[i][0];

    if (dy==0) slope[i]=1.0; //set max direction
    if (dx==0) slope[i]=0.0; //set min direction
    //inverse slope
    if ((dy!=0) && (dx!=0)) { 
      slope[i]=(float) dx/dy;
    }
  }

  for (y=0; y < MAX_Y; y++) {
    k=0;
    for (i=0; i < cant_edges; i++) {
      if (((vertex[i][1] <= y) && (vertex[i+1][1]>y)) || ((vertex[i][1]>y) && (vertex[i+1][1]<=y))){
        xi[k]=(int)(vertex[i][0]+slope[i]*(y-vertex[i][1]));
        k++;
      }
    }
    for (j=0; j<k-1; j++) { /*- Arrange x-intersections in order -*/
      for (i=0; i<k-1; i++) {
        //swap values
        if(xi[i] > xi[i+1]) {
          temp = xi[i];
          xi[i] = xi[i+1];
          xi[i+1] = temp;
        }
      }
    }
    for(i=0; i < k;i+=2) {
      drawLine(xi[i],y,xi[i+1]+1,y, color, width);
    }
  }
}

//search only for valid edges of polygon
int searchCoord(int x1, int y1) {
  int i ;
  for (i = 0; i < MAX_VERTICES; i++) {
    if (vertex[i][0] == x1 && vertex[i][1] == y1)
      return 1;
  }
  return 0;
}