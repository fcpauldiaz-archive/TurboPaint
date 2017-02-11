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
#include "paint/palette.h";

#define MAX_X 800
#define MAX_Y 600

void main() {
  int x, y, clicked, xtemp, ytemp;
  int button, selectedBtn;
  int x1, y1, tempx, tempy;
  int selectedWidth; //select width of line
  BITMAP bitmap;
  //el primer parametro es el modo
  //del registro BX
  if (!SVGA(0x103, MAX_X, MAX_Y)) {
    printf("\r\n SVGA Error\r\n");
    return;
  }
  
  initMouse();
  validateMouse(MAX_X, MAX_Y);
  getMouse(&x, &y, &clicked);

  openBMP(0, 0, "paint/pfondo.bmp",&bitmap);
  clicked = 0;
  //paintCanvas();
  paintPalette(FULL_PALETTE);
  drawLine(90, 300, 50, 250, 15, 10);
  while (1) {
    repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);

    if (clicked == 1) {
      
      //LINE BUTTON SELECTED
      if (x >= 364 && x <= 391 && y >= 48 && y < 81) {
        button = LINE;
        
      }
      //RECTANGLE SELECTED
      if (x >= 326 && x <= 363 && y >= 82 && y <= 118) {
        button = RECTANGLE;
      }      

      if (button != selectedBtn) {
        mouseHide(x, y);
        selectedBtn = button;
        mouseShow(x, y);
        clicked = 0;
      }
      if (y > y1_Draw) {
        switch(selectedBtn) {
          case LINE:
            x1 = x;
            y1 = y;
            getMouse(&x,&y,&clicked);
            while(clicked==1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              //this could repaint the line in real time
              //but it ereases everything else
              //drawLine(x1, y1, x, y, 128, 5);
              //drawLine(x1, y1, x, y, -1, 5);
            }
            mouseHide(x, y);
            drawLine(x1,y1,x,y, 12, 5);
            mouseShow(x, y);
            x1 = x; y1 = y; 
            break;
          case RECTANGLE:

            break;
        }
      }

      //close button
      if (x >= 768 && x <= 795 &&
          y >= 0 && y <= 26 ) {
          clicked = 0;
          exitSVGA();
          break;
      }
    }
  }
}
  