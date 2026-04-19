#include "list.h"

int main(){
    printf(" Implementation of a Linked List program with user library.\n");
    int data, index;
    LL* head = NULL;
    while(1){
        int mode = 1;
        printf(" choose mode:\n -> 1 : create new linked list.\n -> 2 : print all the data in linked list.\n -> 3 : add data at index.\n -> 4 : delete data at the index.\n -> 5 : search data.\n -> 6 : count the etemnt.\n >>> ");
        scanf("%d",&mode);
        switch(mode){
            case 1:
                clearing_memory(head);
                printf("enter your fist data >>> ");
                scanf("%d",&data);
                head = cnode(data);
                break;
            case 2: 
                printf("the data in your lined list:\n");
                printll(head);
                break;
            case 3:
                printf("enter your data >>> ");
                scanf("%d",&data);
                printf("enter the index >>> ");
                scanf("%d",&index);
                if (index == 0){
                    head = inodeb(head, data);
                } else if (index == cnodee(head)){                
                    inodee(head,data);
                } else {
                    inodem(head,data,index);
                }
                break;
            case 4:
                printf("enter the index >>> ");
                scanf("%d",&index);
                head = dnode(head,index);
                break;
            case 5:
                printf("enter the data >>> ");
                scanf("%d",&data);
                if (snode(head,data)){
                    printf("data has been found!\n");
                } else {
                    printf("data has not been found!\n");
                }
                break;
            case 6: 
                int size = cnodee(head);
                if (size == 0){
                    printf("linked list is empty.\n");
                } else {
                    printf("the number of element is: %d\n",size);
                }
                break;
            default: printf("invalid mode.\n"); 
        }
    }
    return 0;
}