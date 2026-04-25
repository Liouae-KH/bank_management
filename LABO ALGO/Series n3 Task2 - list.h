
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode* next;
};

// Creates a new node with given data
struct ListNode* list_create_node(int data) {
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode->next = NULL;
    newNode->data = data;
    return newNode;
}

// Appends a node at the end of the list
void list_append(struct ListNode** head, int data) {
    if (*head == NULL) {
        *head = list_create_node(data);
        return;
    }
    struct ListNode* walker = *head;
    while (walker->next != NULL)
        walker = walker->next;
    walker->next = list_create_node(data);
}

// Inserts a node at the beginning of the list
void list_prepend(struct ListNode** head, int data) {
    struct ListNode* newNode = list_create_node(data);
    newNode->next = *head;
    *head = newNode;
}

// Prints all elements of the list
void list_display(struct ListNode* head) {
    struct ListNode* ptr = head;
    while (ptr != NULL) {
        printf("%d->", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
    return;
}

// Searches for a key in the list (returns 1 if found, 0 otherwise)
int list_search(struct ListNode* head, int key) {
    struct ListNode* walker = head;
    while (walker != NULL) {
        if (walker->data == key)
            return 1;
        walker = walker->next;
    }
    return 0;
}

// Returns the number of nodes in the list
int list_count(struct ListNode* head) {
    int counter = 0;
    struct ListNode* walker = head;
    while (walker != NULL) {
        walker = walker->next;
        counter++;
    }
    return counter;
}

// Deletes the node at the given index (0‑based)
void list_delete_at(struct ListNode** head, int index) {
    if (*head == NULL) {
        printf("empty linked list.\n");
        return;
    }
    int total = list_count(*head);
    if (index >= total) {
        printf("invalid index.\n");
        return;
    }
    struct ListNode* walker = *head;
    if (index == 0) {
        *head = walker->next;
        free(walker);
        return;
    }
    for (int i = 0; i < index - 1; i++)
        walker = walker->next;
    struct ListNode* temp = walker->next;
    walker->next = temp->next;
    free(temp);
}

// all nodes and sets head to NULL
void list_clear(struct ListNode** head) {
    struct ListNode* delete_ptr = *head;
    struct ListNode* next_node = NULL;
    while (delete_ptr != NULL) {
        next_node = delete_ptr->next;
        free(delete_ptr);
        delete_ptr = next_node;
    }
    *head = NULL;
}



void list_insert_at(struct ListNode** head, int data, int index) {
    int total = list_count(*head);
    if (index < 0 || index > total) {
        printf("invalid index.\n");
        return;
    }
    if (index == 0) {
        list_prepend(head, data);
        return;
    }
    if (index == total) {
        list_append(head, data);
        return;
    }
    struct ListNode* walker = *head;
    for (int i = 0; i < index - 1; i++)
        walker = walker->next;
    struct ListNode* newNode = list_create_node(data);
    newNode->next = walker->next;
    walker->next = newNode;
}

