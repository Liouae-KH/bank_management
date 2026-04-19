#include <stdlib.h>
#include <stdio.h>

typedef struct LL {
    int data;
    struct LL* link;
} LL;


//printing linked lis
void printll(LL *ptr){
    while(ptr!=NULL){
        printf("%d\n",ptr->data);
        ptr=ptr->link;
    }
    return;
}




void clearing_memory(LL* delete_LL){
    LL* next_node = NULL;
    while (delete_LL != NULL) {
        next_node = delete_LL->link;     
        free(delete_LL);
        delete_LL = next_node; 
    }
    return;
}




  // Create NODE "CNODE"
LL* cnode(int data){
    LL* head = malloc(sizeof(LL));
    head->link=NULL;
    head->data=data;
    return head;
}





    //Insert NODE at the Begining  "INODEB"
LL* inodeb(LL* head, int data){
    LL* temp_ILLB = cnode(data);
    temp_ILLB->link = head;
    head=temp_ILLB;
    return head;
}




    // Counting NODE Elements
int cnodee(LL* walker){
    int counter = 0;  
    while(walker!=NULL){
        walker=walker->link;
        counter++;
    }
    return counter;
}




    //Insert NODE at the Mid  "INODEM"
void inodem(LL* head, int data, int index){
    if (head == NULL){
        printf("empty linked list.\n");
        return;
    }
    if (index > cnodee(head)){
        printf("invalid index.\n");
        return;
    }
    LL* walker = head;
    for(int i = 0; i < index -1; i++){
            walker=walker->link;
    }
    LL* temp_ILLM = cnode(data);
    temp_ILLM->link=walker->link;
    walker->link= temp_ILLM;
    return;
}




    // Insert NODE at the End "ENODEE"
void inodee(LL* head, int data){
    if(head == NULL) return;
    LL* walker = head;
    while(walker->link!=NULL){
        walker=walker->link;
    }
    LL* temp_ILLE = cnode(data);
    walker->link=temp_ILLE;
    return;
}




  // Delete NODE "DNODE"
LL* dnode(LL* head,int index){
    if (head == NULL){
        printf("empty linked list.\n");
        return head;
    }
    LL* walker = head;
    if (index > cnodee(head)){
        printf("invalid index.\n");
        return head;
    }
    if (index == 0){
        head=walker->link;
        free(walker);
        return head;
    }
    
    for(int i = 0; i < index -1; i++){
            walker=walker->link;
    }
    LL* temp_M=walker->link;
    walker->link=temp_M->link;
    free(temp_M);
    return head;
}





int snode(LL* head, int key){
    LL* walker = head;
    while(walker!=NULL){
        if (walker->data == key){
            return 1;
        }
        walker=walker->link;
    }
    return 0;
}