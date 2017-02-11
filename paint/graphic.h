/**
 * Pablo Díaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 */

long resolY, resolX;
long screenX, screenY, numberOfPages;
char currentPage;

int SVGA(int mode, long w, long h){
  resolY = h;
  resolX = w;
  numberOfPages = ((resolX*resolY)/65536L);
  screenX = resolX-1;
  screenY = resolY-1;
  //https://es.wikipedia.org/wiki/Int_10h
  asm {
    MOV AX, 4F02H  //establecer modo supervga
    MOV BX, [mode] //size of screen
    INT 10H        //interrupt screen       
    CMP AX, 004FH //test success
    JNE Error
  }
  //retornar boolean
  return(1);
  Error:;
  return(0);
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
    MOV AX, 4F05H   //read window
    XOR BX, BX 
    XOR DX, DX
    MOV DL, [page]
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
  if (x > screenX || x <0 || y > screenY || y < 0) {
    return;
  }

  memoryPosition = (y * resolX) + x;
  page = memoryPosition >> 16;
  pixelOffset = memoryPosition - (page << 16);
 
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
  page = positionMem >> 16;
  offsetPixel = positionMem - (page << 16);

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