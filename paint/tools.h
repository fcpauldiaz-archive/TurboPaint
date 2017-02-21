//linked list 
//http://www.learn-c.org/en/Linked_lists
typedef struct node {
    int val_x;
    int val_y;
    struct node * next;
} node_t;

void setNextNode(node_t ** next_node, int x, int y);

//bucket algorithim
//Third try to implement
//stack overflow problems
void bucket(int x, int y, char fillColor, char clickColor, int pattern){
  node_t *link, *nextNode, *remove;
  int calcX, calcY;

  //node decl
  link = (node_t*) malloc(sizeof(node_t));
  link->val_x = x;
  link->val_y = y;
  link->next = NULL;
  nextNode = link;

  while(link != NULL) {

    if (pattern == 1) {
      fillColor = getPixel(678 + x%30, 95 + y%35);
    } else if (pattern == 2) {
      fillColor = getPixel(718 + x%30, 95 + y%35);
    }
    else if (pattern == 3) {
      fillColor = getPixel(758 + x%37, 94 + y%36);
    }

    putPixel(x, y, fillColor);
    //left
    calcX = x-1;
    if (getPixel(calcX, y) == clickColor && (x > 0 && x < MAX_X && (calcY) > y1_Draw && (calcY) < MAX_Y)) {
      if (pattern == 1) {
        fillColor = getPixel(678 + x%30, 95 + y%35);
      } else if (pattern == 2) {
        fillColor = getPixel(718 + x%30, 95 + y%35);
      }
      else if (pattern == 3) {
        fillColor = getPixel(758 + x%37, 94 + y%36);
      }


      putPixel(calcX, y, fillColor);
      setNextNode(&nextNode, calcX, y);
    }
    //up
    calcY = y+1;
    if (getPixel(x, calcY) == clickColor && (x > 0 && x < MAX_X && (calcY) > y1_Draw && (calcY) < MAX_Y)) {
      if (pattern == 1) {
        fillColor = getPixel(678 + x%30, 95 + y%35);
      } else if (pattern == 2) {
        fillColor = getPixel(718 + x%30, 95 + y%35);
      }
      else if (pattern == 3) {
        fillColor = getPixel(758 + x%37, 94 + y%36);
      }

      putPixel(x, calcY, fillColor);
      setNextNode(&nextNode, x, calcY);
    }
    //down
    calcY = y-1;
    if(getPixel(x, calcY) == clickColor && (x>0 && x < MAX_X && (calcY) > y1_Draw && (calcY)<MAX_Y)){
      if (pattern == 1) {
        fillColor = getPixel(678 + x%30, 95 + y%35);
      } else if (pattern == 2) {
        fillColor = getPixel(718 + x%30, 95 + y%35);
      }
      else if (pattern == 3) {
        fillColor = getPixel(758 + x%37, 94 + y%36);
      }

      putPixel(x, calcY, fillColor);
      setNextNode(&nextNode, x, calcY);
    }
    //right
    calcX = x+1;
    if(getPixel(calcX, y) == clickColor && (x>0 && x < MAX_X && (calcY)>y1_Draw && (calcY)<MAX_Y)){
      if (pattern == 1) {
        fillColor = getPixel(678 + x%30, 95 + y%35);
      } else if (pattern == 2) {
        fillColor = getPixel(718 + x%30, 95 + y%35);
      }
      else if (pattern == 3) {
        fillColor = getPixel(758 + x%37, 94 + y%36);
      }

      putPixel(calcX, y, fillColor);
      setNextNode(&nextNode, calcX, y);
    }
    
    //remove element
    remove=link;
    link= link->next;
    x=link->val_x;
    y=link->val_y;
    free(remove);
  }
  free(link);
}


/* RECURSIVE ALGORITHIM. STACK OVERFLOW
void bucket(int x, int y, int originalColor, int clickColor, int fillColor) {
  if (y > MAX_Y || y < y1_Draw || x < 0 || x > MAX_X)
    return;
  if (originalColor == clickColor) {
    putPixel(x, y, fillColor);
    bucket(x    , y - 1, originalColor, getPixel(x    , y - 1), fillColor); 
    bucket(x    , y + 1, originalColor, getPixel(x    , y + 1), fillColor);
    bucket(x - 1, y    , originalColor, getPixel(x - 1, y    ), fillColor);
    bucket(x + 1, y    , originalColor, getPixel(x + 1, y    ), fillColor);
  } 
  return;
}*/

/* STACK OVERFLOW
void bucket(int x, int y, int originalColor, int clickColor, int fillColor) {
  int x1, y1;
  int tempColor1, tempColor2, tempColor3, tempColor4;
  x1 = x; y1 = y;
  while(1) {
    if (x1 > MAX_X || x < 0 || y > MAX_Y || y < y1_Draw) break;
    putPixel(x1, y1, fillColor);
    //arriba
    tempColor1 = getPixel(x1, y1 - 1);
    tempColor2 = getPixel(x1, y1 + 1);
    tempColor3 = getPixel(x1 + 1, y1); 
    tempColor4 = getPixel(x1 - 1, y1);
    //arriba
    if (tempColor1 == originalColor) {
      y1 = y1 - 1;
    }
    //abajo
    else if (tempColor2 == originalColor) {
      y1 = y1 + 1;
    }
    //derecha
    else if (tempColor3 == originalColor) {
      x1 = x1 + 1;
    }
    //izquierda
    else if (tempColor4 == originalColor) {
      x1 = x1 - 1;
    }
    else {
      break;
    }

  }

}*/

//set next node
void setNextNode(node_t ** next_node, int x, int y) {
  node_t *node;
  node = (node_t*) malloc(sizeof(node_t));
  node->val_x = x;
  node->val_y = y;
  node->next = NULL;
  (*next_node)->next = node;
  *next_node = (*next_node)->next;
}


//SPRAY TOOL
void paintSpray(int x, int y, int color, int width) {
  putPixel(x - rand()%width, y-rand()%width, color);
}
