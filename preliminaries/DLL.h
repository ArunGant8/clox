#ifndef __dll_h__
#define __dll_h__

typedef struct node *link;

typedef struct node {
    char *word;
    link next;
    link prev;
} node_t;

typedef node_t *dlist;

dlist create();
void destroy(dlist);
dlist add(char *word, dlist list, int l);
int find(char *word, dlist list);
int equals(char *w1, char *w2);
int del(char *word, dlist list);

#endif
