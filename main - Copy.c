#include <stdio.h>
#include <stdlib.h>
#include "list - Copy.h"

int main() {
    struct Node* head = NULL;

    addNode(&head, 10); 
    addNodeAtBeginning(&head, 5); 

    if (head != NULL) {
        addNodeAfter(head, 7); 
    }

    addNode(&head, 20);

    printf("Linked List: ");
    displayList(head);

    int key = 20;
    if (search(head, key)) {
        printf("%d found in the list.\n", key);
    } else {
        printf("%d not found in the list.\n", key);
    }

    freeList(&head);

    return 0;
}