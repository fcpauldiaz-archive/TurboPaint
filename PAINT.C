/**
 * Pablo Diaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>

#define MAX_VERTICES 100
int vertex[MAX_VERTICES][2];
int undoCounter = 0;
int redoCounter = 0;
#include "paint/graphic.h";
#include "paint/mouse.h";
#include "paint/bmpfiles.h";
#include "paint/buttons.h";
#include "paint/shapes.h";
#include "paint/palette.h";
#include "paint/tools.h";
#include "paint/cpboard.h";
#include "paint/pText.h";


void main() {
  int z, x, y, clicked, xtemp, ytemp, edgesCount;
  int button, selectedBtn, tempColor, actualColor1, actualColor2;
  int actualWidth, actualPattern;
  int radio, rdX, rdY;
  int x1, y1, x2, y2, tempx, tempy;
  int sX1, sX2, sY1, sY2;
  char font[58][16*16];
  FILE *fontF;
  int selectedWidth, colorFill; //select width of line
  
  BITMAP bitmap;
  //el primer parametro es el modo
  //del registro BX
  if (!SVGA(0x103, MAX_X, MAX_Y)) {
    printf("\r\n SVGA Error\r\n");
    return;
  }
  
  initMouse();
  adaptMouse(MAX_X, MAX_Y);

  if((fontF = fopen ("paint/fuente.fnt","rb"))== NULL){
    return;
  }
  for(x=0; x<58; x++){
    fread(&font[x], 1, 16*16, fontF);
  }
  fclose(fontF);

  openFileBMP(0, 0, "paint/pfondo.bmp", &bitmap);
  clicked = 0;
  //paintCanvas();
  paintPalette(FULL_PALETTE);
  colorFill = 1;   //initialize selected color pane
  actualColor1 = COLOR_FILL_1;  //initialize paint color
  actualColor2 = COLOR_FILL_2; //initialize paint color
  actualWidth = 1;  //initialize width
  actualPattern = 0; //initialize pattern
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

      //PENCIL
      if (x >= 2 && x <= 50 && y >= 75 && y <= 171) {
        button = PENCIL;
      }

      //GET COLOR
      if (x >= 51 && x <= 100 && y >= 72 && y <= 120) button = PICKER;
      //SPRAY TOOL
      if (x >= 109 && x <= 143 && y >= 29 && y <= 82) button = SPRAY;
      
      //width1
      if (x >= 262 && x <= 314 && y >= 41 && y <= 61) actualWidth = WIDTH1;
      //width 2
      if (x >= 262 && x <= 314 && y >= 62 && y <= 80) actualWidth = WIDTH2;
      //width 3
      if (x >= 262 && x <= 314 && y >= 81 && y <= 99) actualWidth = WIDTH3;
      //width 4
      if (x >= 262 && x <= 314 && y >= 100 && y <= 120) actualWidth = WIDTH4;


      //NEW
      if (x >= 94 && x <= 113 && y >= 0 && y <= 25) {
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

      //BUCKET FILL
      if (x >= 2 && x <= 53 && y >= 32 && y <= 74) button = BUCKET;

      if (x >= 83 && x <= 123 && y >= 101 && y <= 147) button = TEXT;
      //SAVE IMAGE
      if (x >= 11 && x <= 36 && y >= 0 && y <= 25) {
        mouseHide(x, y);
        saveImage(0, 140, 800, 460, "paint/image.bmp");
        mouseShow(x, y);
      }
      //LOAD IMAGE
      if (x >= 52 && x <= 79 && y >= 2 && y <= 23) {
        mouseHide(x, y);
        loadImage(0, 140, "paint/image.bmp", &bitmap);
        openFileBMP(0, 0, "paint/header.bmp", &bitmap);
        paintPalette(FULL_PALETTE);
        mouseShow(x, y);

      }
      //COPY
      if (x >= 152 && x <= 188 && y >= 77 && y <= 119) button = COPY;
      //PASTE
      if (x >= 203 && x <= 243 && y >= 33 && y <= 83) button = PASTE;
      //CUT
      if (x >= 154 && x <= 196 && y >= 31 && y <= 74) button = CUT;

      //REDO
      if (x >= 189 && x <= 221 && y >= 81 && y <= 120) {
        mouseHide(x, y);
        saveUndo();
        redo();
        mouseShow(x, y);


      }
      //HELP
      if (x >= 734 && x <= 750 && y >= 0 && y <= 25) {
        openFileBMP(0, 0, "paint/help.bmp", &bitmap);
        paintPalette(FULL_PALETTE);
      }

      //PATTERN 1
      if (x >= 678 && x <= 710 && y >= 94 && y <= 130) actualPattern = 1;
      //PATTERN 2
      if (x >= 718 && x <= 756 && y >= 94 && y <= 130) actualPattern = 2;
      //PATTERN 3
      if (x >= 758 && x <= 795 && y >= 95 && y <= 130) actualPattern = 3;
      //undo
      if (x >= 224 && x <= 260 && y >= 81 && y <= 119) {
        mouseHide(x, y);
        saveRedo();
        undo();
        mouseShow(x, y);
      }
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
          actualPattern = 0;
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
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            getMouse(&x,&y,&clicked);
            while(clicked==1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              //this could repaint the line in real time
              //but it ereases everything else
              savePixel(x1, y1, x, y, actualWidth);
              drawLine(x1, y1, x, y, actualColor1, actualWidth);
              reDrawLine(x1, y1, x, y, actualWidth);
            }
            mouseHide(x, y);
            drawLine(x1,y1,x,y, actualColor1, actualWidth);
            //delete file for animation
            remove("paint/pixels.txt");
            mouseShow(x, y);
            x1 = x; y1 = y; 
            break;
          case RECTANGLE:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              //savePixelRectangle(x1, y1, x, y, actualWidth);
              //drawRectangle(x1, y1, x, y, actualColor1, actualWidth);
              //reDrawRectangle(x1, y1, x, y, actualWidth);
            }
            mouseHide(x, y);
            drawRectangle(x1, y1, x, y, actualColor1, actualWidth);
            saveRedo();
            //remove("paint/pixels.txt");
            mouseShow(x, y);
            break;
          case CIRCLE:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
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
            saveRedo();
            mouseShow(x, y);
            break;
          case ELLIPSE:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            while (clicked == 1) {
              rdX = fabs(x - x1);
              rdY = fabs(y - y1);
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            drawEllipse(x1, y1, rdX, rdY, actualColor1, actualWidth);
            saveRedo();
            mouseShow(x, y);
            break;
          case PAINT_RECTANGLE:
            x1 = x; y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
              //savePixelRectangle(x1, y1, x, y, actualWidth);
              //drawRectangle(x1, y1, x, y, actualColor1, actualWidth);
              //reDrawRectangle(x1, y1, x, y, actualWidth);
            }
            mouseHide(x, y);
            paintRectangle(x1, y1, x, y, actualColor1, actualColor2, actualWidth);
            saveRedo();
            //remove("paint/pixels.txt");
            mouseShow(x, y);
            break;
          case PAINT_CIRCLE:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
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
            saveRedo();
            mouseShow(x, y);
            break;
          case PAINT_ELLIPSE:
            x1 = x;
            y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            while (clicked == 1) {
              rdX = fabs(x - x1);
              rdY = fabs(y - y1);
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            paintEllipse(x1, y1, rdX, rdY, actualColor1, actualColor2, actualWidth);
            saveRedo();
            mouseShow(x, y);
            break;
          case POLYGON:
            x1 = x; y1 = y;
            x2 = x; y2 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
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
            //saveUndo();
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
                drawLine(x1, y1, x, y, actualColor1, 1);
                mouseShow(x, y);
                
              } else {
                mouseHide(x, y);
                if (searchCoord(x2, y2) == 0) {
                  vertex[edgesCount][0] = x2; //final position
                  vertex[edgesCount][1] = y2; //final position
                }
                drawLine(x2, y2, x1, y1, actualColor1, 1);
                mouseShow(x, y);
              }
              x1 = x;
              y1 = y;
            }
            mouseHide(x, y);
            scanLine(edgesCount, actualColor2, actualWidth);
            mouseShow(x, y);
            xtemp = x; ytemp = y;
            break;
          case ERASER:
            xtemp = x;
            ytemp = y;
            mouseHide(x, y);
            saveUndo();
            while (clicked == 1 && y >= 140) {
              drawLine(x, y, xtemp, ytemp, 255, actualWidth);
              xtemp = x; ytemp = y;
              getMouse(&x, &y, &clicked);
            }
            saveRedo();
            mouseShow(x, y);
            xtemp = x; ytemp = y;
            break;
          case BUCKET:
            mouseHide(x, y);
            saveUndo();
            bucket(x, y, actualColor2, getPixel(x, y), actualPattern);
            saveRedo();
            mouseShow(x, y);
            break;
          case PENCIL:
            mouseHide(x, y);
            saveUndo();
            x1 = x; y1 = y;
            while(clicked == 1 && y >= 140) {
              drawLine(x, y, x1, y1, actualColor1, actualWidth);
              x1 = x; y1 = y;
              getMouse(&x, &y, &clicked);
            }
            saveRedo();
            mouseShow(x, y);
            xtemp = x; ytemp = y;
            break;
          case PICKER:
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
            break;
          case SPRAY:
            mouseHide(x, y);
            saveUndo();
            while(clicked == 1){
              getMouse(&x, &y, &clicked); 
              paintSpray(x, y, actualColor1, actualWidth);
            }
            saveRedo();
            mouseShow(x, y);
            xtemp = x; ytemp = y;
            break;
          case COPY:
            x1 = x; y1 = y;
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            copyPixels(x1, y1, x, y);
            mouseShow(x, y);
            break;
          case PASTE:
            mouseHide(x, y);
            saveUndo();
            pastePixels(x, y);
            mouseShow(x, y);
            break;
          case CUT:
            x1 = x; y1 = y;
            mouseHide(x, y);
            saveUndo();
            mouseShow(x, y);
            while (clicked == 1) {
              repaintMouse(&x, &y, &clicked, &xtemp, &ytemp);
            }
            mouseHide(x, y);
            cutPixels(x1, y1, x, y);
            mouseShow(x, y);
            break;
          case TEXT:
            mouseHide(x, y);
            saveUndo();
            showText(x, y, actualColor1, font);
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
  