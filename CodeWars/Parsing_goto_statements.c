 #include <stddef.h> /* NULL */

 /*I wanted to implement this by avoiding null terminated strings and strings.h*/

 typedef struct Str {
   int len;
   const char *data;
 } Str;

 typedef struct StrList {
   Str *str;
   struct StrList *next;
 } StrList;

 typedef enum FreeListType {
   TSTR, TSTRLIST, TALL
 } FreeListType;

 typedef enum MemoryAction {
   ALLOC, FREEALL
 } MemoryAction;

 typedef struct FreeList {
   FreeListType type;
   union {
     Str *str;
     StrList *strList;
   } data;
   struct FreeList *next;
 } FreeList;

 void *memoryMonitor(MemoryAction action, FreeListType type) {
   static FreeList *freeList = NULL;
   FreeList *fl = NULL;

   switch (action) {
   case ALLOC:
     fl = (FreeList *)malloc(sizeof(FreeList));
     fl->next = freeList;
     freeList = fl;
     fl->type = type;

     switch (type) {
     case TSTR: {
       Str *s = (Str *)malloc(sizeof(Str));
       fl->data.str = s;
       return s;
     }
     case TSTRLIST: {
       StrList *sl = (StrList *)malloc(sizeof(StrList));
       fl->data.strList = sl;
       return sl;
     }
     }
     break;

   case FREEALL:
     while (freeList != NULL) {
       FreeList *x = freeList;
       switch (x->type) {
       case TSTR: {
         free(x->data.str);
         break;
       }
       case TSTRLIST:
       {
         free(x->data.strList);
         break;
       }
       }
       freeList = x->next;
       free(x);
     }
     break;
   }
 }

 StrList *split(Str *s, char at) {
   const char *wp = s->data;
   StrList *list = NULL;
   StrList *head = NULL;
   Str *str = (Str*)memoryMonitor(ALLOC, TSTR);
   int i = 0;
   str->data = s->data;
   str->len = 0;

   for (i = 0; i < s->len; wp++, i++) {
     if (*wp == at) {
       if (list == NULL) {
         list = (StrList*)memoryMonitor(ALLOC, TSTRLIST);
         head = list;
       }
       else {
         list->next = (StrList*)memoryMonitor(ALLOC, TSTRLIST);
         list = list->next;
       }

       list->str = str;
       list->next = NULL;
       str = (Str*)memoryMonitor(ALLOC, TSTR);

       if (i + 1 == s->len)
         str->data == NULL;
       else
         str->data = wp + 1;

       str->len = 0;
     }
     else {
       str->len++;
     }
   }

   if (list == NULL) {
     list = (StrList*)memoryMonitor(ALLOC, TSTRLIST);
     head = list;
   }
   else {
     list->next = (StrList*)memoryMonitor(ALLOC, TSTRLIST);
     list = list->next;
   }

   list->str = str;
   list->next = NULL;

   return head;
 }

 void toStr(const char *s, Str *str) {
   str->data = s;
   str->len = 0;
   while (*s != '\0') {
     str->len++;
     s++;
   }
 }

 int StrEqual(Str *s1, Str *s2) {
   int i = 0;

   if (s1->len != s2->len) {
     return 0;
   }

   for (i = 0; i < s1->len; i++) {
     if (s1->data[i] != s2->data[i]) {
       return 0;
     }
   }

   return 1;
 }

 void concat(StrList **list, StrList *append) {
   if (*list == NULL) {
     *list = append;
   }
   else {
     StrList *wpList = *list;
     StrList *wpAppend = append;

     while (wpList->next != NULL)
       wpList = wpList->next;

     while (wpAppend != NULL) {
       wpList->next = wpAppend;
       wpList = wpList->next;
       wpAppend = wpAppend->next;
     }
   }
 }

 StrList *gotoString(Str *s) {
   StrList *lines = split(s, '\n');
   Str go;
   StrList *line = lines;
   StrList *lsFinal = NULL;

   toStr("goto", &go);

   line = lines;

   while (line != NULL) {
     StrList *parts = split(line->str, ' ');
     StrList *jmp = NULL;

     if (StrEqual(parts->str, &go)) {
       jmp = parts->next;
       if (jmp != NULL) {
         StrList *line2 = lines;
         while (line2 != NULL) {
           StrList *parts2 = split(line2->str, ' ');
           if (StrEqual(parts2->str, jmp->str)) {
             concat(&lsFinal, parts2->next);
             line = line2->next;
             break;
           }
           line2 = line2->next;
         }
       }
     }
     else {
       concat(&lsFinal, parts->next);
       line = line->next;
     }
   }

   return lsFinal;
 }

 char *join(StrList *ls, char c) {
   char *result = NULL;
   int sz = 0;
   int n = 0;
   while (ls != NULL) {
     sz += ls->str->len;
     if (result == NULL) {
       result = (char *)malloc(sizeof(char) * (sz + 1));
       int i;
       for (i = 0; i < ls->str->len; i++) {
         result[n++] = ls->str->data[i];
       }
       result[n] = '\0';
     }
     else {
       sz++;
       result = (char *)realloc(result, sizeof(char) * (sz + 1));
       result[n++] = c;
       int i;
       for (i = 0; i < ls->str->len; i++) {
         result[n++] = ls->str->data[i];
       }
       result[n] = '\0';
     }
     ls = ls->next;
   }
   return result;
 }

 char *parse(const char *s) {
   Str str;
   StrList *ls;
   char *result = NULL;
   toStr(s, &str);
   ls = gotoString(&str);
   result = join(ls, ' ');
   memoryMonitor(FREEALL, TALL);
   return result;
 }
