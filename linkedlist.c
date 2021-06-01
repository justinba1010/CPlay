/*
 * =====================================================================================
 *
 *       Filename:  linkedlist.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/14/2021 08:36:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

struct node {
  int data;
  struct node *next;
};

int main(void) {
  struct node *head, *next;
  head = malloc(sizeof(struct node));
  next = malloc(sizeof(struct node));
  head->data = 3;
  head->next = next;
  next->data = 5;
  next->next = NULL;
  printf("%d; %d; %p\n", head->data, head->next->data, head);
  return 0;
}
