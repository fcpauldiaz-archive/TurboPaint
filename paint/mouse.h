/**
 * Pablo Díaz
 * UVG
 * 6/02/2017
 */
unsigned int ** bufferMouse;

#define I   15  //outer color mouse
#define X   17  //inner color mouse

/* mouse form */
static unsigned char pointer[12*16] =
{
  I,I,0,0,0,0,0,0,0,0,0,0,
  I,I,I,0,0,0,0,0,0,0,0,0,
  I,X,I,I,0,0,0,0,0,0,0,0,
  I,X,X,I,I,0,0,0,0,0,0,0,
  I,X,X,X,I,I,0,0,0,0,0,0,
  I,X,X,X,X,I,I,0,0,0,0,0,
  I,X,X,X,X,X,I,I,0,0,0,0,
  I,X,X,X,X,X,X,I,I,0,0,0,
  I,X,X,X,X,X,X,X,I,I,0,0,
  I,X,X,X,X,X,X,X,X,I,I,0,
  I,X,X,X,X,X,I,I,I,I,I,0,
  I,X,X,I,X,X,X,I,I,0,0,0,
  I,X,I,I,I,X,X,I,I,0,0,0,
  I,I,I,0,I,X,X,X,I,0,0,0,
  I,0,0,0,I,I,X,X,I,0,0,0,
  0,0,0,0,I,I,I,I,I,0,0,0,
};


void initMouse() {
  asm {
    MOV AX, 00H
    INT 33H
  }
}

void mouseShow(int x, int y) {
  int i,j;
  bufferMouse = malloc(sizeof(int) * 12);
  for (i= 0; i < 12; i++) {
    bufferMouse[i] = malloc(sizeof(int) * 16);
    for (j=0; j < 16; j++) {
      bufferMouse[i][j] = getPixel(x+i, y+j);
    }
  }

  for (i=0; i < 16; i++) {
    for (j=0; j < 12; j++) {
      if (pointer[12*i+j]!=0){
        putPixel(x + j, y + i, pointer[12*i+j]);
      }
    }
  }
}

// get mouse position
void getMouse(int *x0, int *y0, int *b){
  int x, y, button;
  asm {
    MOV AX, 03H                 //obtains reuslt
    INT 33H         
    AND BX, 0000000000000011B
    MOV button, BX              //saves result
    MOV x, CX             
    MOV y, DX             
  }
  *x0 = x;
  *y0 = y;
  *b = button;
}

// Sets max boundaries for mouse
void validateMouse(int x_limit, int y_limit) {
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
  for (i=0; i < 12; i++) {
    for (j=0; j < 16; j++) {
      putPixel(x+i,y+j,bufferMouse[i][j]);
    }
    free(bufferMouse[i]);
  }
  free(bufferMouse);
}


//update mouse position
void repaintMouse(int *x, int *y, int *b, int *xtemp, int *ytemp) {
  getMouse(x, y, b);
  if (*xtemp != *x || *ytemp != *y) {
    mouseHide(*xtemp, *ytemp);
    mouseShow(*x, *y);
    *xtemp = *x;
    *ytemp = *y;
  }
}



