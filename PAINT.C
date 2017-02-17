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

#define MAX_VERTICES 100
int vertex[MAX_VERTICES][2];

#include "paint/graphic.h"
#include "paint/mouse.h";
#include "paint/bmpfiles.h";
#include "paint/buttons.h";
#include "paint/shapes.h";
#include "paint/palette.h";




void main() {
  int z, x, y, clicked, xtemp, ytemp, edgesCount;
  int button, selectedBtn, tempColor, actualColor1, actualColor2;
  int actualWidth;
  int radio, rdX, rdY;
  int x1, y1, x2, y2, tempx, tempy;
  
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

  openBMP(0, 0, "paint/pfondo.bmp", &bitmap);
  clicked = 0;
  //paintCanvas();
  paintPalette(FULL_PALETTE);
  colorFill = 1;    //initialize selected color pane
  actualColor1 = COLOR_FILL_1;  //initialize paint color
  actualColor2 = COLOR_FILL_2; //initialize paint color
  actualWidth = 1;  //initialize width
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
      //CIRCLE CLICKED
      if (x >= 326 && x <= 363 && y >= 48 && y <= 81) {
        button = CIRCLE;
      }
      //ELLIPSE CLICKED
      if (x >= 364 && x <= 430 && y >= 82 && y <= 118) {
        button = ELLIPSE;
      }
      //START
      if (x >= 392 && x <= 430 && y >= 48 && y <= 81) {
        button = POLYGON;
      }

      //CIRCLE PAINT
      if (x >= 432 && x <= 472 && y >= 41 && y <= 82) {
        button = PAINT_CIRCLE;
      }
      //RECTANGLE PAINT
      if (x >= 431 && x <= 472 && y >= 83 && y <= 117) {
        button = PAINT_RECTANGLE;
      }
      //OVAL PAINT
      if (x >= 473 && x <= 529 && y >= 41 && y <= 82) {
        button = PAINT_ELLIPSE;
      }
      //STAR PAINT
      if (x >= 473 && x <= 529 && y >= 83 && y <= 117) {
        button = PAINT_POLYGON;
      }
      
      //width1
      if (x >= 262 && x <= 314 && y >= 41 && y <= 61) actualWidth = WIDTH1;
      //width 2
      if (x >= 262 && x <= 314 && y >= 62 && y <= 80) actualWidth = WIDTH2;
      //width 3
      if (x >= 262 && x <= 314 && y >= 81 && y <= 99) actualWidth = WIDTH3;
      //width 4
      if (x >= 262 && x <= 314 && y >= 100 && y <= 120) actualWidth = WIDTH4;


      //NEW
      if (x >= 95 && x <= 123 && y >= 0 && y <= 25) {
        paintCanvas();
      }

      //ERASER
      if (x >= 54 && x <= 94 && y >= 32 && y <= 71) {
        button = ERASER;
      }

      //COLOR FILL SELECTED 1
      if (x >= 526 && x <= 565 && y >= 95 && y <= 130) colorFill = 1;
      //COLOR FILL SELECTED 2     
      if (x >= 568 && x <= 620 && y >= 95 && y <= 130) colorFill = 2;

      //COLOR PICKER 
      if (x >= 526 && x <= 794 && y >= 30 && y <= 90) {
        mouseHide(x, y);
        tempColor = getPixel(x, y);
        if (colorFill == 1) {
          actualColor1 = tempColor;
          paintColorPickerOne(tempColor);
        }
        else {
          actualColor2 = tempColor;
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
            drawLine(x1,y1,x,y, actualColor1, actualWidth);
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
            drawRectangle(x1, y1, x, y, actualColor1, actualWidth);
            mouseShow(x, y);
            break;
          case CIRCLE:
            x1 = x;
            y1 = y;
            while (clicked == 1) {
              radio = sqrt(pow(x-x1, 2) + pow(y-y1, 2));
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            radio = radio/2;
            if (x1 < x ) {
              x1 = x1 + radio;
            }
            if (x1 > x)  {
              x1 = x1 - radio;
            }
            if (y1 < y ) {
              y1 = y1 + radio;
            }
            if (y1 > y ) {
              y1 = y - radio;
            }
            mouseHide(x, y);
            drawCircle(x1, y1, radio, actualColor1, actualWidth);
            mouseShow(x, y);
            break;
          case ELLIPSE:
            x1 = x;
            y1 = y;
            while (clicked == 1) {
              rdX = fabs(x - x1);
              rdY = fabs(y - y1);
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            drawEllipse(x1, y1, rdX, rdY, actualColor1, actualWidth);
            mouseShow(x, y);
            break;
          case PAINT_RECTANGLE:
            x1 = x; y1 = y;
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            paintRectangle(x1, y1, x, y, actualColor1, actualColor2, actualWidth);
            mouseShow(x, y);
            break;
          case PAINT_CIRCLE:
            x1 = x;
            y1 = y;
            while (clicked == 1) {
              radio = sqrt(pow(x-x1, 2) + pow(y-y1, 2));
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            radio = radio/2;
            if (x1 < x ) {
              x1 = x1 + radio;
            }
            if (x1 > x)  {
              x1 = x1 - radio;
            }
            if (y1 < y ) {
              y1 = y1 + radio;
            }
            if (y1 > y ) {
              y1 = y - radio;
            }
            mouseHide(x, y);
            paintCircle(x1, y1, radio, actualColor1, actualColor2, actualWidth);
            mouseShow(x, y);
            break;
          case PAINT_ELLIPSE:
            x1 = x;
            y1 = y;
            while (clicked == 1) {
              rdX = fabs(x - x1);
              rdY = fabs(y - y1);
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            paintEllipse(x1, y1, rdX, rdY, actualColor1, actualColor2, actualWidth);
            mouseShow(x, y);
            break;
          case POLYGON:
            x1 = x; y1 = y;
            x2 = x; y2 = y;
            while(clicked != 2) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              while(clicked !=1 && clicked !=2 ) { 
                repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              }
              if(clicked == 1) {
                mouseHide(x, y);
                drawLine(x1, y1, x, y, actualColor1, actualWidth);
                mouseShow(x, y);
              }else{
                mouseHide(x, y);
                drawLine(x2, y2, x1, y1, actualColor1, actualWidth);
                mouseShow(x, y);
              }
              x1 = x;
              y1 = y;
            }
            break;
          case PAINT_POLYGON:
            x1 = x; y1= y;
            x2 = x; y2 = y;
            edgesCount = 0;
            while (clicked != 2) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              while(clicked != 1 && clicked != 2){
                repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              }
             if(clicked == 1) {
                mouseHide(x, y);
                //edgesCount is the vertex number
                if (searchCoord(x, y) == 0) {
                  vertex[edgesCount][0] = x; //original position
                  vertex[edgesCount][1] = y; //original position
                  edgesCount++;
                }
                drawLine(x1, y1, x, y, 0, 1);
                mouseShow(x, y);
                
              } else {
                mouseHide(x, y);
                if (searchCoord(x2, y2) == 0) {
                  vertex[edgesCount][0] = x2; //final position
                  vertex[edgesCount][1] = y2; //final position
                }
                drawLine(x2, y2, x1, y1, 0, 1);
                mouseShow(x, y);
              }
              x1 = x;
              y1 = y;
            }
            mouseHide(x, y);
            scanLine(edgesCount, actualColor2, actualWidth);
            mouseShow(x, y);
            break;
          case ERASER:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            while (clicked == 1 && y >= 140) {
              drawLine(x, y, x1, y1, 255, actualWidth);
              x1 = x; y1 = y;
              getMouse(&x, &y, &clicked);
            }
            
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
  