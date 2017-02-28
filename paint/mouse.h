/**
 * Pablo Díaz
 * UVG
 * 6/02/2017
 */
unsigned int ** bufferMouse;

#define O   12  //outer color mouse
#define I   0  //inner color mouse
#define mouseWidth 13
#define mouseHeight 16


/* mouse form */
static unsigned char mouse[mouseWidth * mouseHeight] =
{
  O,O,O,0,0,0,0,0,0,0,0,0,0,
  O,O,O,O,0,0,0,0,0,0,0,0,0,
  O,O,I,O,O,0,0,0,0,0,0,0,0,
  O,O,I,I,O,O,0,0,0,0,0,0,0,
  O,O,I,I,I,O,O,0,0,0,0,0,0,
  O,O,I,I,I,I,O,O,0,0,0,0,0,
  O,O,I,I,I,I,I,O,O,0,0,0,0,
  O,O,I,I,I,I,I,I,O,O,0,0,0,
  O,O,I,I,I,I,I,I,I,O,O,0,0,
  O,O,I,I,I,I,I,I,I,I,O,O,0,
  O,O,I,I,I,I,I,I,O,O,O,O,0,
  O,O,I,I,I,I,I,I,O,O,0,0,0,
  O,O,O,O,O,O,I,I,O,O,0,0,0,
  O,O,O,O,O,O,I,I,I,O,0,0,0,
  0,0,0,0,O,O,O,I,I,O,0,0,0,
  0,0,0,0,0,O,O,O,O,O,0,0,0,
};


void initMouse() {
  asm {
    MOV AX, 00H
    INT 33H
  }
}

void mouseShow(int x, int y) {
  int i,j;
  //allocates memory and returns pointer to it
  //receives size to allocate
  bufferMouse = malloc(sizeof(int) * mouseWidth);
  for (i= 0; i < mouseWidth; i++) {
    bufferMouse[i] = malloc(sizeof(int) * mouseHeight);
    for (j=0; j < mouseHeight; j++) {
      bufferMouse[i][j] = getPixel(x+i, y+j);
    }
  }

  for (i=0; i < mouseHeight; i++) {
    for (j=0; j < mouseWidth; j++) {
      if (mouse[mouseWidth*i+j]!=0){
        putPixel(x + j, y + i, mouse[mouseWidth*i+j]);
      }
    }
  }
}

// get mouse state
// https://courses.engr.illinois.edu/ece390/books/labmanual/io-devices-mouse.html
void getMouse(int *mouse_x, int *mouse_y, int *clicked){
  int posx, posy, click_button;
  asm {
    MOV AX, 03H                 
    INT 33H         
    AND BX, 11B                 //obtains reuslt
    MOV click_button, BX             
    MOV posx, CX             
    MOV posy, DX             
  }
  *mouse_x = posx;
  *mouse_y = posy;
  *clicked = click_button;             //saves result
}

// adapts mouse to screen size
void adaptMouse(int x_limit, int y_limit) {
  asm {
    PUSH AX
    PUSH CX
    PUSH DX
    MOV AX,07h
    XOR CX,CX
    MOV DX,SS:[x_limit]
    INT 33h
    MOV AX,08h
    XOR CX,CX
    MOV DX,SS:[y_limit]
    INT  33h
    POP DX
    POP CX
    POP AX
  }
}

// Hides mouse from screen
void mouseHide(int x, int y) {
  int i,j;
  for (i=0; i < mouseWidth; i++) {
    for (j=0; j < mouseHeight; j++) {
      putPixel(x+i,y+j,bufferMouse[i][j]);
    }
    //deallocates the memory, receives pointer
    free(bufferMouse[i]);
  }
  //deallocates the memory, receives pointer
  free(bufferMouse);
}


//update mouse position
void repaintMouse(int *x, int *y, int *clicked, int *xtemp, int *ytemp) {
  getMouse(x, y, clicked);
  if (*xtemp != *x || *ytemp != *y) {
    mouseHide(*xtemp, *ytemp);
    mouseShow(*x, *y);
    *xtemp = *x;
    *ytemp = *y;
  }
}



