/**
 * Pablo Diaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 * manejador de archivos bmp
 */

typedef struct bmp {
  int width;
  int height;
  char palette[256*3];
  char *data;
} BITMAP;

void ignoreLine(FILE *fp, int num_bytes);
void changePalette(char far *palette);

void openFileBMP(int x, int y, char *file, BITMAP *bmpFile) {
  FILE *fileC;
  int idx;
  int cantColors;
  int i, j, ti;
  //open file
  if ((fileC = fopen(file, "rb")) == NULL) {
    exit(1);
  }

  //bmp header first validation 2 bytes
  if(fgetc(fileC)!= 'B' || fgetc(fileC) != 'M'){
    fclose(fileC);
    exit(1);
  }
  //reads image size and color
  //skips header until width
  ignoreLine(fileC,16);
  //get width from bmp format
  fread(&bmpFile->width, 2, 1, fileC);
  //ignore the resting 2 bytes of widht
  ignoreLine(fileC,2);
  //get height from bmp
  fread(&bmpFile->height, 2, 1, fileC);
  //ignore resting bytes until quantity fo colors for palette
  ignoreLine(fileC,22);
  //get quantity of colors in 2 bytes
  fread(&cantColors, 2, 1, fileC);
  //ignore the resting 2 bytes and the 4 bytes from important colors
  ignoreLine(fileC,6);

  // 256 colors, in case it is saved in other format
  if (cantColors == 0) {
    cantColors = 256;
  }

  //reads information of palette
  for (idx=0; idx < cantColors; idx++){
    bmpFile->palette[idx*3+2] = fgetc(fileC) / 4;
    bmpFile->palette[idx*3+1] = fgetc(fileC) / 4;
    bmpFile->palette[idx*3] = fgetc(fileC) / 4;
    fgetc(fileC);
  }

  changePalette(bmpFile->palette);
  //reads only the pixels from bmp file
  for(j = (bmpFile->height + y); j >=0 ;j--){
    for(i=0; i < bmpFile->width ; i++){
      putPixel(i+x, j, fgetc(fileC));
    }
  }
  fclose(fileC);
}

//ignores byes
void ignoreLine(FILE *file, int cantBytes){
   int i;
   for (i=0; i<cantBytes; i++) {
      fgetc(file);
   }
}

//sets the screen colors
//https://github.com/corbindavenport/cobalt/blob/master/CDROOT/COBALT/SOURCE/BLACKOUT/ASM/BANNER.ASM
void changePalette(char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1012
    mov bx, 0
    mov cx, 256
    int 0x10
  }
}

//get palette
void activatePalette ( char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1017
    mov bx, 0
    mov cx, 256
    int 0x10
  }
}

void saveImage(int x, int y, int width, int height, char file[]){
  FILE * fileSave;
  int count, i, j, tempi;
  unsigned char pixel, ch;
  unsigned long headerBuf[13];
  long palette[256];
  char headerInfo[2] = "BM";
  //opens file
  fileSave = fopen(file, "wb");
  fwrite(headerInfo, sizeof(headerInfo[0]), 2, fileSave);
  x--; y--;                                   //improve file image at save
  headerBuf[0] = width * height + 1024 + 54;  //size
  headerBuf[1] = 0;                           // reserved
  headerBuf[2] = 1024 + 54;                   // offset
  headerBuf[3] = 40;                          // size header
  headerBuf[4] = width;                       // width
  headerBuf[5] = height;                      // height
  headerBuf[6] = 0x80001;                     // planes
  headerBuf[7] = 0;                           // compression
  headerBuf[8] = width*height;                // actual size
  headerBuf[9] = 0;             
  headerBuf[10] = 0;            
  headerBuf[11] = 256;                          // colors
  headerBuf[12] = 256;                          // important colors
  fwrite(headerBuf, sizeof(headerBuf[0]), 13,  fileSave);
  activatePalette(palette);
  palette[0] = 0;
  palette[1] = 0x8;
  palette[2] = 0x800;
  palette[3] = 0x808;
  palette[4] = 0x80000;
  palette[5] = 0x80008;
  palette[6] = 0x80400;
  palette[7] = 0xC0C0C;
  palette[8] = 0x80808;
  palette[9] = 0xFF;
  palette[10] = 0xFF00;
  palette[11] = 0xFFFF;
  palette[12] = 0xFF0000;
  palette[13] = 0xFF00FF;
  palette[14] = 0xFFFF00;
  palette[15] = 0xFFFFFF;
  fwrite(palette, sizeof(long), 255,  fileSave);
 
  for(j=(y+height); j>=y; j--){
    for(i=x; i<=(width+x)-1; i++){
     pixel=getPixel(i, j);
     fwrite(&pixel,1,1, fileSave);
    }
  }
  fclose( fileSave);
}

void loadImage(int x, int y,char *file, BITMAP *bitmap){
  FILE *fileSave;
  int idx;
  int cantColors;
  int i, j;

  //opens file
  if((fileSave = fopen(file, "rb"))==NULL){
    exit(1);
  }

  //validates bmpt
  if(fgetc(fileSave)!= 'B' || fgetc(fileSave) != 'M'){
    fclose(fileSave);
    exit(1);
  }

  //read image
    //reads image size and color
  //skips header until width
  ignoreLine(fileSave,16);
  //get width from bmp format
  fread(&bitmap->width, 2, 1, fileSave);
  //ignore the resting 2 bytes of widht
  ignoreLine(fileSave,2);
  //get height from bmp
  fread(&bitmap->height, 2, 1, fileSave);
  //ignore resting bytes until quantity fo colors for palette
  ignoreLine(fileSave,22);
  //get quantity of colors in 2 bytes
  fread(&cantColors, 2, 1, fileSave);
  //ignore the resting 2 bytes and the 4 bytes from important colors
  ignoreLine(fileSave,6);

  if (cantColors == 0) {
    cantColors = 256;
  }
  
  //reads palette
  for(idx=0; idx < cantColors;idx++){
    bitmap->palette[idx*3+2] = fgetc(fileSave) / 4;
    bitmap->palette[idx*3+1] = fgetc(fileSave) / 4;
    bitmap->palette[idx*3] = fgetc(fileSave) / 4;
    fgetc(fileSave);
  }

  changePalette(bitmap->palette);
  for(j=(bitmap->height+y);j>=y;j--){
    for(i=0; i<(bitmap->width); i++){
      putPixel(i+x, j, fgetc(fileSave));
    }
  }
  fclose(fileSave);
}
