/*
Universidad del Valle de Guatemala
Autor: Henzer Garcia 12538
Proyecto 1: PAINT
Archivo: Paint.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <time.h>

int vert[20][2];

#include "lib/Ass.h"
#include "lib/Clip.h"
#include "lib/Text.h"
#include "lib/Fig.h"
#include "lib/IO.h"
#include "lib/Gui.h"
#include "lib/BMP.h"



void main(){
	int i, j, z;
	int selectedButton, btn, grosor, tempGrosor, selectedColor, tempColor, selectedPattern, tempPattern;
	int num_vertices = 3;
	int vertices[6] = {5,100,20,50,300,4};
	int x, y, b, tempx, tempy, x1, y1, radiox, radioy, color1, color2, cont;
	
	Node *start;
	FILE *fontFile;
	unsigned char font[58][16*16];
	unsigned char backspace[16][16];
	BITMAP bmp;
	
	//getchar();

	if( !setVideoSVGA(v800x600x256, 800, 600)){
		printf("\r\nError inicializacion de SVGA.\r\n");
		return;
	}


	//getchar();

	//drawImage(0,0,&bmp);
	//getchar();

	//Se abre el archivo con la fuente
	if((fontFile = fopen ("lib/font.fnt","rb"))==NULL){
		printf("\r\nError.-Fuente no encontrada.\r\n");
		return;
	}
	for(x=0; x<58; x++){
		fread(&font[x], 1, 16*16, fontFile);
	}
	fclose(fontFile);
	setDimensions(16,16);
	

	//Establece las funciones para la utilizacion del mouse
	setMouse();
	setBoundariesMouse(800, 600);
	getMouse(&x, &y, &b);
	//showMouse(x, y);

	loadImage(0, 0, "lib/fondo.bmp",&bmp);
	//loadPalette("Paint/palette3.bmp",&bmp);
	showInterface();
	
	//CONFIGURACION INICIAL
	selectedButton = LOAD;									//Se establece como herramienta por defecto la LINEA
	paintSelectedButton(selectedButton, SELECTED_COLOR);	

	grosor = GROSOR1;										//Se establece como grossor por defecto el 1
	paintSelectedGrossor(grosor, SELECTED_COLOR);			

	selectedColor = COLOR1;									//Se establece el color por defecto al 1
	paintSelectedColor(selectedColor, SELECTED_COLOR);		

	color1 = 31; color2 = 31;
	paintColor(1, color1);
	paintColor(2, color2);

	selectedPattern = 0;

	while(1){
		refreshMouse(&x, &y, &b, &tempx, &tempy);
		//printf("C: %d\n", color1);
		//printf("X: %d  Y: %d B: %d\n", x, y, b);
		if(b==1){
			//Hizo click en las herramientas
			if(x>15 && x<135 && y>25 && y<305){
				//GUARDAR
				if(x>15 && x<55 && y>25 & y<65){
					btn = SAVE;
					hideMouse(x, y);
					saveImage(150, 0, 640, 600, "lib/a.bmp");
					showMouse(x, y);
				} 

				//LOAD
				if(x>55 && x<95 && y>25 & y<65){
					hideMouse(x, y);
					loadImage(150, 0, "lib/a.bmp",&bmp);
					showMouse(x, y);
					btn = LOAD;
				}

				//NEW
				if(x>95 && x<135 && y>25 & y<65){
					hideMouse(x, y);
					save_undo();
					showCanvas();
					showMouse(x, y);
					btn = NEW;
				} 

				

				//PENCIL
				if(x>15 && x<55 && y>65 & y<105) btn = PENCIL;

				//LINE
				if(x>55 && x<95 && y>65 & y<105) btn = LINE;

				//ERASER
				if(x>95 && x<135 && y>65 & y<105) btn = ERASER;

				//RECTANGLE
				if(x>15 && x<55 && y>105 & y<145) btn = RECTANGLE;

				//RECTANGLE FILL
				if(x>55 && x<95 && y>105 & y<145) btn = RECTANGLE_FILL;

				//BUCKET 
				if(x>95 && x<135 && y>105 & y<145) btn = BUCKET;

				//ELLIPSE
				if(x>15 && x<55 && y>145 & y<185) btn = ELLIPSE;

				//ELLIPSE FILL
				if(x>55 && x<95 && y>145 & y<185) btn = ELLIPSE_FILL;

				//COPY
				if(x>95 && x<135 && y>145 & y<185) btn = COPY;

				//CIRCLE
				if(x>15 && x<55 && y>185 & y<225) btn = CIRCLE;

				//CIRCLE FILL
				if(x>55 && x<95 && y>185 & y<225) btn = CIRCLE_FILL;

				//CUT
				if(x>95 && x<135 && y>185 && y<225) btn = CUT;

				//POLYGON
				if(x>15 && x<55 && y>225 && y<265) btn = POLYGON;

				//POLYGON FILL
				if(x>55 && x<95 && y>225 && y<265) btn = POLYGON_FILL;

				//PEGAR
				if(x>95 && x<135 && y>225 & y<265) btn = PASTE;

				//RECOGE COLOR
				if(x>15 && x<55 && y>265 & y<305) btn = DROPPER;

				//TEXTO
				if(x>55 && x<95 && y>265 & y<305) btn = TEXT;

				//UNDO
				if(x>95 && x<135 && y>265 & y<305){
					hideMouse(x, y);
					undo();
					showMouse(x, y);
					btn = UNDO;
				}

				if(btn!=selectedButton){
					hideMouse(x, y);
					paintSelectedButton(selectedButton, -54);
					paintSelectedButton(btn, SELECTED_COLOR);
					selectedButton = btn;
					showMouse(x, y);
				}
			}
			//Hizo click en los grosores
			if(x>8 && x<91 && y>315 && y<330){
				if(x>8 && x<24)  tempGrosor = GROSOR1;
				if(x>24 && x<40) tempGrosor = GROSOR2;
				if(x>40 && x<56) tempGrosor = GROSOR3;
				if(x>56 && x<72) tempGrosor = GROSOR4;
				if(x>72 && x<91) tempGrosor = GROSOR5;

				if(tempGrosor != grosor){
					hideMouse(x, y);
					paintSelectedGrossor(grosor, -54);
					paintSelectedGrossor(tempGrosor, SELECTED_COLOR);
					grosor = tempGrosor;
					showMouse(x, y);
				}
			}
			//Hizo click en las casillas para los colores
			if(x>90 && x<130 && y>385 && y<465){
				if(y>385 && y<425)  tempColor = COLOR1;
				if(y>425 && y<465) tempColor = COLOR2;

				if(tempColor != selectedColor){
					hideMouse(x, y);
					paintSelectedColor(selectedColor, -54);
					paintSelectedColor(tempColor, SELECTED_COLOR);
					selectedColor = tempColor;
					showMouse(x, y);
				}
				selectedPattern = 0;
			}

			//Hizo click en la paleta de colores
			if(x>20 && x<85 && y>330 && y<587){
				hideMouse(x, y);
				if(selectedColor == 1){
					color1 = getPixel(x, y);
					printf("%d\n", color1);
					paintColor(selectedColor, color1);
				}else{
					color2 = getPixel(x, y);
					paintColor(selectedColor, color2);
				}
				showMouse(x, y);
				selectedPattern = 0;
			}

			//Hizo click en los patrones.
			if(x>95 && x<135 && y>505 && y<585){
				if(y>505 && y<545) tempPattern = PATTERN1;
				if(y>545 && y<585) tempPattern = PATTERN2;

				if(tempPattern != selectedPattern){
					hideMouse(x, y);
					paintSelectedPattern(selectedPattern, -54);
					paintSelectedPattern(tempPattern, SELECTED_COLOR);
					selectedPattern = tempPattern;
					showMouse(x, y);
				}
			}

			//Canvas
			if(x>150 && y>0){

				switch(selectedButton){
					case LINE:
						x1 = x;
						y1 = y;
						getMouse(&x,&y,&b);
						while(b==1){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						line(x1,y1,x,y,color1,grosor);
						showMouse(x, y);
						break;

					case PENCIL:
						hideMouse(x, y);
						tempx = x;
						tempy = y;
						save_undo();
						while(b==1 && x>100  && y>20){
							line(x, y, tempx, tempy, color1, grosor);
							tempx=x; tempy = y;
							getMouse(&x,&y,&b);
						}
						showMouse(x, y);
						tempx=x; tempy=y;
						break;
					case CIRCLE:
						x1 = x;
						y1 = y;
						while(b==1){
							radiox = sqrt(pow(x-x1, 2) + pow(y-y1, 2));
							radioy = radiox;
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						ellipse(x1,y1,radiox, radioy,color1,grosor);
						showMouse(x, y);
						break;

					case CIRCLE_FILL:
						x1 = x;
						y1 = y;
						while(b==1){
							radiox = sqrt(pow(x-x1, 2) + pow(y-y1, 2));
							radioy = radiox;
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						ellipseFilled(x1,y1,radiox, radioy,color1, color2, grosor);
						showMouse(x, y);
						break;
					case COPY:
						x1 = x;
						y1 = y;
						while(b==1){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x,y);
						copy_file(x1, y1, x, y);
						showMouse(x,y);
						break;
					case CUT:
						x1 = x;
						y1 = y;
						while(b==1){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x,y);
						save_undo();
						cut_file(x1, y1, x, y);
						showMouse(x,y);
						break;
					case PASTE:
						hideMouse(x,y);
						save_undo();
						paste_file(x, y);
						showMouse(x,y);
						break;

					case ELLIPSE:
						x1 = x;
						y1 = y;
						while(b==1){
							radiox = abs(x-x1);
							radioy = abs(y-y1);
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						ellipse(x1,y1, radiox, radioy, color1, grosor);
						showMouse(x, y);
						break;

					case ELLIPSE_FILL:
						x1 = x;
						y1 = y;
						while(b==1){
							radiox = abs(x-x1);
							radioy = abs(y-y1);
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						ellipseFilled(x1,y1, radiox, radioy, color1, color2, grosor);
						showMouse(x, y);
						break;

					case RECTANGLE:
						x1=x;
						y1=y;
						while(b==1){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						rectangle(x1, y1 ,x, y, color1, grosor);
						showMouse(x, y);
						break;

					case RECTANGLE_FILL:
						x1=x;
						y1=y;
						while(b==1){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
						}
						hideMouse(x, y);
						save_undo();
						rectangleFilled(x1, y1 ,x, y, color1, color2, grosor);
						showMouse(x, y);
						break;

					case BUCKET:
						hideMouse(x, y);
						save_undo();
						bucketFill(x, y, color1, selectedPattern);
						showMouse(x, y);
						break;
					case SPRAY:
						save_undo();
						spray(x,y,color1);
						break;
					case ERASER:
						tempx = x;
						tempy = y;
						hideMouse(x, y);
						save_undo();
						showMouse(x, y);
						while(b==1 && x>100  && y>20){
							hideMouse(x, y);
							line(x, y, tempx, tempy, -2, 30);
							showMouse(x, y);
							tempx=x; tempy = y;
							getMouse(&x,&y,&b);
						}
						tempx=x; tempy=y;
						break;
					case TEXT:
						hideMouse(x,y);
						save_undo();
						printText(x, y, color1, font);
						showMouse(x, y);
						tempx=x; tempy=y;
						break;
					case POLYGON:
						x1 = x; y1 = y;
						i = x; j = y;

						hideMouse(x, y);
						save_undo();
						showMouse(x, y);
						start = (Node*) malloc(sizeof(Node));
						start->x = x;
						start->y = y;

						start->next = NULL;

						cont = 0;
						while(b!=2){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
							while(b!=1 && b!=2){
								refreshMouse(&x, &y, &b, &tempx, &tempy);
							}
							if(b==1){
								push(x, y, &start);
								hideMouse(x, y);
								line(x1, y1, x, y, 0, 1);
								showMouse(x, y);
								cont++;
							}else{
								hideMouse(x, y);
								line(i, j, x1, y1, 0, 1);
								showMouse(x, y);
								cont++;
							}
							x1 = x;
							y1 = y;
							
						}
						break;
					case POLYGON_FILL:
						x1 = x; y1 = y;
						i = x; j = y;

						hideMouse(x, y);
						save_undo();
						showMouse(x, y);
						cont = 0;
						while(b!=2){
							refreshMouse(&x, &y, &b, &tempx, &tempy);
							while(b!=1 && b!=2){
								refreshMouse(&x, &y, &b, &tempx, &tempy);
							}
							if(b==1){
								hideMouse(x, y);
								vert[cont][0] = x; 
								vert[cont][1] = y;
								line(x1, y1, x, y, 0, 1);
								showMouse(x, y);
								cont++;
							}else{
								hideMouse(x, y);
								vert[cont][0] = i; 
								vert[cont][1] = j;
								line(i, j, x1, y1, 0, 1);
								showMouse(x, y);
							}
							x1 = x;
							y1 = y;
						}
						vert[0][0] = 100;
						vert[0][1] = 100;

						vert[1][0] = 200;
						vert[1][1] = 200;

						vert[2][0] = 300;
						vert[2][1] = 300;

						vert[3][0] = 100;
						vert[3][1] = 100;
						cont = 3;
						scanline(cont, color1, grosor);


						break;
					case DROPPER:
						hideMouse(x, y);
						if(selectedColor == 1){
							color1 = getPixel(x, y);
							paintColor(selectedColor, color1);
						}else{
							color2 = getPixel(x, y);
							paintColor(selectedColor, color2);
						}
						showMouse(x, y);
						break;
					case UNDO:
						break;

				}
			}
			//AYUDA
			if(x<15 && y<20){
				hideMouse(x,y);
				copy_file(0, 0, 800, 600);

				loadImage(0, 0, "lib/ayuda.bmp",&bmp);
				showMouse(x,y);
				b=0;
				while(b!=1){
					refreshMouse(&x, &y, &b, &tempx, &tempy);
				}

				hideMouse(x,y);
				paste_file(0, 0);
				showMouse(x,y);

			}

		}

	}

	line(5,5, 300,300, 0, 1);

	

	polygon(3, vertices, 0, 1);


	circle(100, 100, 100, 0, 1);
	circle(400, 400, 40, 0, 1);
	circle(300, 300, 20, 0, 1);

	//Espera que se presione alguna tecla para salir
	getchar();
	unSetVideoSVGA();


}
