 #include <stdlib.h>
 #include <stddef.h>
 #include <limits.h>

 /*The BBTree procedures are from: Balanced Search Trees Made Simple.  Arne Anderson 1993*/

 typedef struct Node {
   struct Node *left;
   struct Node *right;
   int level;
   int value;
 } Node;

 Node *bottom;

 typedef enum BOOL {
   FALSE = 0,
   TRUE = 1
 } BOOL;

 void init_sentinel() {
   bottom = (Node *)malloc(sizeof(Node));
   bottom->left = bottom;
   bottom->right = bottom;
   bottom->level = 0;
   bottom->value = INT_MIN;
 }

 void skew(Node **t) {
   Node *temp;
   if ((*t)->left->level == (*t)->level) {
     temp = *t;
     *t = (*t)->left;
     temp->left = (*t)->right;
     (*t)->right = temp;
   }
 }

 void split(Node **t) {
   Node *temp;
   if ((*t)->right->right->level == (*t)->level) {
     temp = *t;
     *t = (*t)->right;
     temp->right = (*t)->left;
     (*t)->left = temp;
     (*t)->level++;
   }
 }

 /*insert - OK is set to FALSE if we find a duplicate */
 void insert(Node **t, int value, BOOL *ok) {
   if (*t == bottom) {
     *t = (Node *)malloc(sizeof(Node));
     (*t)->value = value;
     (*t)->right = bottom;
     (*t)->left = bottom;
     (*t)->level = 1;
     *ok = TRUE;
   }
   else {
     if (value < (*t)->value) {
       insert(&((*t)->left), value, ok);
     }
     else if (value > (*t)->value) {
       insert(&((*t)->right), value, ok);
     }
     else {
       *ok = FALSE;
     }
     skew(t);
     split(t);
   }
 }

 int next(Node *t, int value) {
   /* - Find the node with the value passed
    *
    * - If a right child doesn't exist then return the parent
    *
    * - If a right child does exist, set that as the root and move left
    *   until we reach the bottom
    */
   int parent = t->value; 
   while (t != bottom) {  
     if (value < t->value) {
       parent = t->value;
       t = t->left;
     }
     else if (value == t->value) {
       break;
     }    
     else {
       t = t->right;
     }
   }
    
   t = t->right;
   while (t != bottom) {  
     parent = t->value;
     t = t->left;
   }

   return parent;
 }

 void dump(Node *t) {
   if (t != bottom) {
     dump(t->left);
     printf("%d ", t->value);
     dump(t->right);
   }
 }

 int dblLinear(int n) { 
   int i = 0; 
   int b;
   Node *t;
   int last;
   BOOL ok = FALSE;

   init_sentinel();
   t = bottom;

   last = 1;
   insert(&t, last, &ok);
  
   for (i = 0; i < n; i++) {
     b = last * 2 + 1;
     insert(&t, b, &ok);
     b = last * 3 + 1;
     insert(&t, b, &ok);
     last = next(t, last);
   }

   return last;
 }
