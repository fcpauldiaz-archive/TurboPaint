/**
 * Pablo Diaz 6/02/2017
 * Universidad del Valle de Guatemala
 * Paint en C++ y assembler de Intel
 * manejador de archivos bmp
 */
#ifndef __DOS_H
  #include <dos.h>
#endif 

typedef unsigned char  byte;
typedef unsigned short word;
typedef struct tagBITMAP {
  word width;
  word height;
  char palette[256*3];
  byte *data;
} BITMAP;

void skipf(FILE *fp, int num_bytes);
void changePalette(char far *palette);

void openBMP(int x, int y, char *file, BITMAP *bitmap) {
  FILE *filepointer;
  long index;
  word numberColor;
  int i, j, ti;
  //open file
  if ((filepointer = fopen(file, "rb")) == NULL) {
    exit(1);
  }

  //validates bmp
  if(fgetc(filepointer)!= 'B' || fgetc(filepointer) != 'M'){
    fclose(filepointer);
    exit(1);
  }
  //reads image size and color
  //Lee el tamaño de la imagen y el número de colores.
  skipf(filepointer,16);
    fread(&bitmap->width,sizeof(word), 1, filepointer);
    skipf(filepointer,2);
    fread(&bitmap->height,sizeof(word), 1, filepointer);
    skipf(filepointer,22);
    fread(&numberColor,sizeof(word), 1, filepointer);
    skipf(filepointer,6);

    // 8-bit file
    if(numberColor==0) numberColor = 256;

    //Lee la información de la paleta.
    for(index=0;index<numberColor;index++){
      bitmap->palette[(int)(index*3+2)] = fgetc(filepointer) >> 2;
      bitmap->palette[(int)(index*3+1)] = fgetc(filepointer) >> 2;
      bitmap->palette[(int)(index*3+0)] = fgetc(filepointer) >> 2;
      fgetc(filepointer);
    }

  changePalette(bitmap->palette);
  //Lee el bitmap
  for(j=(bitmap->height + y);j>=0;j--){
    for(i=0; i<(bitmap->width); i++){
      putPixel(i+x, j, fgetc(filepointer));
    }
  }
  fclose(filepointer);
}

//ignores byes
void skipf(FILE *filepointer, int num_bytes){
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(filepointer);
}

//sets the screen colors
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
void getPalette ( char far *palette){
  asm {
    les dx, [palette]
    mov ax, 0x1017
    mov bx, 0
    mov cx, 256
    int 0x10
  }
}

void saveImage(int x, int y, int width, int height, char file[]){
  FILE *fp;
  int count, i, j, tempi;
  unsigned char pixel, ch;
  unsigned long headerBuf[13];
  unsigned long palette[256];
  char headerInfo[2] = "BM";
  //opens file
  fp = fopen(file, "wb");
  fwrite(headerInfo, sizeof(headerInfo[0]),2,fp);
  x--; y--;
  
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
  headerBuf[11] = 16;                          // colors
  headerBuf[12] = 16;                          // important colors
  fwrite(headerBuf, sizeof(headerBuf[0]), 13, fp);
  //set palette
  getPalette(palette);
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
  fwrite(palette, sizeof(unsigned long), 256, fp);
 
  for(j=(y+height); j>=y; j--){
    for(i=x; i<=(width+x)-1; i++){
     pixel=getPixel(i, j);
     fwrite(&pixel,1,1,fp);
    }
  }
  fclose(fp);
}

void loadImage(int x, int y,char *file, BITMAP *bitmap){
  FILE *fp;
  long index;
  word colorNum;
  int i,j, tempi;

  //opens file
  if((fp = fopen(file, "rb"))==NULL){
    exit(1);
  }

  //validates bmpt
  if(fgetc(fp)!= 'B' || fgetc(fp) != 'M'){
    fclose(fp);
    exit(1);
  }

  //read image
  skipf(fp,16);
  fread(&bitmap->width,sizeof(word), 1, fp);
  skipf(fp,2);
  fread(&bitmap->height,sizeof(word), 1, fp);
  skipf(fp,22);
  fread(&colorNum,sizeof(word), 1, fp);
  skipf(fp,6);

    //Sets bits
    if(colorNum==0) colorNum = 256;
  
    //reads palette
    for(index=0;index<colorNum;index++){
      bitmap->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
      bitmap->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
      bitmap->palette[(int)(index*3+0)] = fgetc(fp) >> 2;
      fgetc(fp);
    }

  changePalette(bitmap->palette);
  for(j=(bitmap->height+y);j>=y;j--){
    for(i=0; i<(bitmap->width); i++){
      putPixel(i+x, j, fgetc(fp));
    }
  }
  fclose(fp);
}
