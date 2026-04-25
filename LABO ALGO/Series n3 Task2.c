#include "Series n3 Task2 - list.h"

int main() {
    printf(" Implementation of a Linked List program with user library.\n");
    int data, index;
    struct ListNode* head = NULL;  

    while (1) {
        int mode = 1;
        printf(" choose mode:\n -> 1 : create new linked list.\n -> 2 : print all the data in linked list.\n -> 3 : add data at index.\n -> 4 : delete data at the index.\n -> 5 : search data.\n -> 6 : count the element.\n >>> ");
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                list_clear(&head);                   
                printf("enter your first data >>> ");
                scanf("%d", &data);
                head = list_create_node(data);        
                break;

            case 2:
                printf("the data in your linked list:\n");
                list_display(head);                    
                break;

            case 3:
                printf("enter your data >>> ");
                scanf("%d", &data);
                printf("enter the index >>> ");
                scanf("%d", &index);
                list_insert_at(&head, data, index);    
                break;

            case 4:
                printf("enter the index >>> ");
                scanf("%d", &index);
                list_delete_at(&head, index);          
                break;

            case 5:
                printf("enter the data >>> ");
                scanf("%d", &data);
                if (list_search(head, data)) {        
                    printf("data has been found!\n");
                } else {
                    printf("data has not been found!\n");
                }
                break;

            case 6:
                int size = list_count(head);        
                if (size == 0) {
                    printf("linked list is empty.\n");
                } else {
                    printf("the number of elements is: %d\n", size);
                }
                break;

            default:
                printf("invalid mode.\n");
        }
    }
    return 0;
}
