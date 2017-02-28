/**
 * Pablo Díaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 */

long resolY, resolX;
char currentPage;
int forceDraw = 0;

int SVGA(int size, int w, int h){
  resolY = h;
  resolX = w;
  //https://es.wikipedia.org/wiki/Int_10h
  asm {
    MOV AX, 4F02H  //stablish svga mode
    MOV BX, [size] //size of screen
    INT 10H        //interrupt screen       
  }
}


void exitSVGA() {
  asm {
    MOV AX, 0003H
    XOR BX, BX
    INT 10H
  }
}

//This sets the page of 
//the SVGA memory to currently write.
void setPage(char page){
  asm {
    MOV AL, [page]
    CMP[currentPage], AL
    JE dontChangePage
    MOV [currentPage], AL
    MOV AX, 4F05H   //VESA CHANGE PAGE
    XOR BX, BX      //BX IS = 0
    XOR DX, DX      //DX IS = 0
    MOV DL, [page]  //SAVE PAGE IN D REGISTER
    INT 10H
  }
  dontChangePage:;
}

//http://www.intel-assembler.it/portale/5/programming-vga-card-asm-c/programming-vga-card-asm-c.asp
//https://courses.engr.illinois.edu/ece390/archive/f97/lecture/svga.txt
void putPixel(int x, int y, char drawcolor){
  long memoryPosition;
  int pixelOffset;
  char page;

  //verify limits
  if (x > resolX || x < 0 || y > resolY || y < 0) {
    return;
  }

  memoryPosition = (y * resolX) + x;
  page = memoryPosition / 65536;
  pixelOffset = memoryPosition - (page / 65536);
 
  //change to correct page
  if (page != currentPage){
    setPage(page);
    currentPage = page;
  }

  asm {
    MOV AX, 0A000H
    MOV ES, AX
    MOV DI, [pixelOffset]
    MOV AL, [drawcolor]
    MOV ES:[DI], AL
  }
}

//paint a pixel with more width
void putPixelWidth(int x, int y, int color, int width) {
  int i, j;
  for (i = 0; i < width; i++) {
    for ( j = 0; j < width; j++) {
      putPixel(x + j, y + i, color);
    }
  }
}

//paint a pixel with more width
//only apply width on X
void putPixelWidthX(int x, int y, int color, int width) {
  int i, j;
  for (i = 0; i < width; i++) {
    for ( j = 0; j < width; j++) {
      putPixel(x + j, y, color);
    }
  }
}

// turbo c
// colors
// http://www.setha.info/ict-turbocpp/84-ict-turbocpp-0019.html
char getPixel(int x, int y) {
  long positionMem;
  int offsetPixel;
  char page, color;

  positionMem = (y * resolX) + x;
  page = positionMem / 65536;
  offsetPixel = positionMem - (page / 65536);

  if (page != currentPage) {
    setPage(page);
    currentPage = page;
  }
  asm {
    MOV AX, 0A000H
    MOV ES, AX
    MOV DI, [offsetPixel]
    MOV AL, ES: [DI]
    MOV [color], AL
  }
  return color;
}