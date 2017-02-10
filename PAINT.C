/**
 * Pablo Diaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <time.h>

#include "paint/graphic.h"
#include "paint/mouse.h";
#include "paint/bmpfiles.h";
#include "paint/buttons.h";
#include "paint/shapes.h";

#define MAX_X 800
#define MAX_Y 600

void main() {
  int x, y, buffer, xtemp, ytemp;
  int button, selectedBtn;
  int selectedWidth; //select width of line
  BITMAP bitmap;
  //el primer parametro es el modo
  //del registro BX
  if (!SVGA(0x103, MAX_X, MAX_Y)) {
    printf("\r\n SVGA Error\r\n");
    return;
  }

  putPixel(50, 50, 1);
  initMouse();
  validateMouse(MAX_X, MAX_Y);
  getMouse(&x, &y, &buffer);

  openBMP(0, 0, "paint/pfondo.bmp",&bitmap);
  drawLine(50, 300, 750, 300, 15, 10);
  //paintCanvas();
  while (1) {
    repaintMouse(&x, &y, &buffer, &xtemp, &ytemp);

    if (buffer == 1) {

      //close button
      if (x >= 768 && x <= 795 &&
          y >= 0 && y <= 26 ) {
          exitSVGA();
          break;
      }
    }
  }
  
}