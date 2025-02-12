#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_LEVEL 32      // maximum level for the skip list

// Structure for a node in the skip list 
typedef struct Node {
  int data;
  struct Node *forward[MAX_LEVEL];
} Node;

// Structure for the skip list 
typedef struct SkipList {
  Node *head;
  int level;
} SkipList;

// Function to create a new node
Node *createNode(int data, int level) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(newNode == NULL) {
    perror("memory allocation failed");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  for(int i = 0; i <= level; i++) {
    newNode->forward[i] = NULL;
  }
  return newNode;
}

// function to create a new skip list
SkipList *createSkipList() {
  SkipList *list = (SkipList *)malloc(sizeof(SkipList));
  if(list == NULL) {
    perror("memory allocation failed");
    exit(EXIT_FAILURE);
  }
  list->head = createNode(INT_MIN, MAX_LEVEL);
  list->level = 0;
  return list;
}


// function to generate random level for new node
int randomLevel() {
  int level = 0;
  while(rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
    level++;
  }
  return level;
}


// function to insert value into skip list
void insert(SkipList *list, int data) {
  Node *current = list->head;
  Node *update[MAX_LEVEL + 1];

  for(int i = list ->level; i>= 0; i--) {
    while(current->forward[i] != NULL && current->forward[i]->data < data) {
      current = current->forward[i];
    }
    update[i] = current;
  }
  current = current->forward[0];

  if(current != NULL && current->data == data) {
    return;
  }
  int level = randomLevel();

  if(level > list->level) {
    for(int i = list->level + 1; i <= level; i++) {
      update[i] = list->head;
    }
    list->level = level;
  }
  Node *newNode = createNode(data, level);
  for(int i = 0; i <= level; i++) {
    newNode->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = newNode;
  }
}

// function to search for value in skip list 
Node *search(SkipList *list, int data) {
  Node *current = list->head;

  for(int i = list->level; i>= 0; i--) {
    while(current->forward[i] != NULL && current->forward[i]->data < data) {
      current = current->forward[i];
    }
  }
  current = current->forawrd[0];
  if(current != NULL && current->data == data) {
    return current;
  }
  return NULL;
}

// function to delete value from skip list
void delete(SkipList *list, int data) {
  Node *current = list->head;
  Node *update[MAX_LEVEL + 1];

  for(int i = list->level; i>= 0; i--) {
    while(current->forward[i] != NULL && current->forward[i]->data < data) {
      current = current->forward[i];
    }
    update[i] = current;
  }
  current = current->forward[0];

  if(current != NULL && current->data == data) {
    for(int i = 0; i <= list->level; i++) {
      if(update[i]->forward[i] == current) {
        update[i]->forward[i] = current->forward[i];
      }
    }
    free(current);

    // adjust level of skip list if necessary
    while(list->level > 0 && list->head->forward[list->level] == NULL) {
      list->level--;
    }
  }
}

// function to print skip list for testing
void printSkipList(SkipList *list) {
  for(int i = 0; i <= list->level; i++) {
    Node *current = list->head->forward[i];
    printf("level %d", i);
    while(current != NULL) {
      printf("%d", current->data);
      current = current->forward[i];
    }
    printf("\n");
  }
}

// function to free memory used by the skip list
void freeSkipList(SkipList *list) {
  Node *current = list->head;
  while(current != NULL) {
    Node *next = current->forward[0];
    free(current);
    current = next;
  }
  free(list);
}

int main() {
  srand(time(NULL));

  SkipList *list = createSkipList();

  insert(list, 3);
  insert(list, 6);
  insert(list, 7);
  insert(list, 9);
  insert(list, 10);
  insert(list, 1);
  insert(list, 2);

  printf("skip list: \n");
  printSkipList(list);

  Node *found = search(list, 7);
  if(found != NULL) {
    printf("found: %d\n", found->data);
  } else {
    printf("not found\n");
  }
  delete(list, 7);
  printf("skipList after deleting 7:\n");
  printSkipList(list);
  freeSkipList(list);

  return 0;
}
