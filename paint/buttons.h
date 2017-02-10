
#define LINE 1
#define PENCIL 2
#define CIRCLE 3
#define CIRCLE_FILL 4
#define ELLIPSE 5
#define ELLIPSE_FILL 6
#define RECTANGLE 7
#define RECTANGLE_FILL 8
#define BUCKET 9
#define SPRAY 10
#define ERASER 11
#define TEXT 12
#define POLYGON 13
#define POLYGON_FILL 14
#define DROPPER 15
#define SAVE 16
#define LOAD 17
#define NEW 18
#define CUT 19
#define COPY 20
#define PASTE 21
#define UNDO 22
#define SELECTED_COLOR 23

void paintCanvas() {
  int i, j;
  for (i=0; i < 800; i++) {
    for (j=140; j < 600 ;j++) {
      putPixel(i, j, -1);
    }
  }
}
