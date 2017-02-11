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
  int button, selectedBtn, tempColor;
  int x1, y1, tempx, tempy;
  int selectedWidth, colorFill; //select width of line
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
  colorFill = 1;

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

      //COLOR FILL SELECTED 1
      if (x >= 526 && x <= 565 && y >= 95 && y <= 130) colorFill = 1;
      //COLOR FILL SELECTED 2     
      if (x >= 568 && x <= 620 && y >= 95 && y <= 130) colorFill = 2;

      //COLOR PICKER 
      if (x >= 526 && x <= 794 && y >= 30 && y <= 90) {
        printf("%s\n", "test");
        mouseHide(x, y);
        tempColor = getPixel(x, y);
        if (colorFill == 1) {
          paintColorPickerOne(tempColor);
        }
        else {
          paintColorPickerTwo(tempColor);
        }
        mouseShow(x, y);
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
            x1 = x;
            y1 = y;
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            drawRectangle(x1, y1, x, y, 180, 5);
            mouseShow(x, y);
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
  