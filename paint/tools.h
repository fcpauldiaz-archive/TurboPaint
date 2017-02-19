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
void bucket(int x, int y, char fillColor, char clickColor){
  node_t *link, *nextNode, *remove;
  int calcX, calcY;

  //node decl
  link = (node_t*) malloc(sizeof(node_t));
  link->val_x = x;
  link->val_y = y;
  link->next = NULL;
  nextNode = link;

  while(link != NULL) {

    putPixel(x, y, fillColor);
    //left
    calcX = x-1;
    if (getPixel(calcX, y) == clickColor && (x > 0 && x < 800 && (calcY) > 140 && (calcY) < 600)) {
      putPixel(calcX, y, fillColor);
      setNextNode(&nextNode, calcX, y);
    }
    //up
    calcY = y+1;
    if (getPixel(x, calcY) == clickColor && (x > 0 && x < 800 && (calcY) > 140 && (calcY) < 600)) {
      putPixel(x, calcY, fillColor);
      setNextNode(&nextNode, x, calcY);
    }
    //down
    calcY = y-1;
    if(getPixel(x, calcY) == clickColor && (x>0 && x<800 && (calcY) > 140 && (calcY)<600)){
      putPixel(x, calcY, fillColor);
      setNextNode(&nextNode, x, calcY);
    }
    //right
    calcX = x+1;
    if(getPixel(calcX, y) == clickColor && (x>0 && x<800 && (calcY)>140 && (calcY)<600)){
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
  if (y > 600 || y < 140 || x < 0 || x > 800)
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
    if (x1 > 800 || x < 0 || y > 600 || y < 140) break;
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