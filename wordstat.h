#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printResult();
void processStr();
void chopdigits();
int helpMenu(); 

struct node {

char* word;
int num;
int csnum;
struct node *next;
struct node *neighbor;
struct node *prevneighbor;
};


