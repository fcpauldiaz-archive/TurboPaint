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
    if(numberColor==0){
      numberColor = 256;
    }

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

      if(i+x==300 && j ==300)
        printf("C: %d\n", getPixel(i+x,y));
      //bitmap->data[(word)index+x]=(byte)fgetc(filepointer);
    }
  }
  fclose(filepointer);
}

//---------------------------------------------------------
// Ignora cierta información.
//---------------------------------------------------------
void skipf(FILE *filepointer, int num_bytes){
   int i;
   for (i=0; i<num_bytes; i++)
      fgetc(filepointer);
}

//---------------------------------------------------------
// Determina la paleta.
//---------------------------------------------------------
void changePalette(char far *palette){
  asm {
  les dx, [palette]
  mov ax, 0x1012
  mov bx, 0
  mov cx, 256
  int 0x10
    }
}

//---------------------------------------------------------
// Obtiene la paleta.
//---------------------------------------------------------
void getPalette ( char far *palette){
   asm {
  les dx, [palette]
  mov ax, 0x1017
  mov bx, 0
  mov cx, 256
  int 0x10
       }
}
//---------------------------------------------------------
// Dibuja en pantalla un bitmap específico.
//---------------------------------------------------------
void drawImage(int x, int y, BITMAP *bitmap){
  int vx, vy;

  for(vy=0; vy<bitmap->height; vy++){
    for(vx=0; vx<bitmap->width; vx++){
      //if(bitmap->data[(vy*bitmap->width)+vx]=!15){
        putPixel(x+vx, y+vy, bitmap->data[(vy*bitmap->width)+vx]);
      //}
    }
  }
}

//---------------------------------------------------------
// Regresa en un arreglo una imagen.
//---------------------------------------------------------
void getImage(int x, int y, int width, int height, char *bitmap){
  int vx, vy;
  for(vy=0; vy<height; vy++){
    for(vx=0; vx<width; vx++){
      bitmap[(vy*width)+vx] = getPixel(x+vx, y+vy);
    }
  }
}