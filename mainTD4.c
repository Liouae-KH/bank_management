/*


 void declare_LL(struct LL* walker){
        printf("\n--- Declaring linked list ---\n");

     int the_end=100;
    for (int i = 1; i<=the_end;i++){
        walker->number=i;
        if (i<the_end){
            struct LL* temp = malloc(sizeof(struct LL));
            walker->link=temp;
            walker=temp;
        }else{
            walker->link=NULL;
        }
    }
    printf("\ndone!\n");
    return;
  }
    declare_LL(head);


*/



#include<stdio.h>
#include<stdlib.h>

void tests(){
    struct LL{
        int number;
        struct LL* link;
    };
 
   
void PLL(struct LL *ptr){
    printf("\n--- printing linked list  ---\n");
        
    while(ptr!=NULL){
        printf("\nnode: %d",ptr->number);
        ptr=ptr->link;
    }
    printf("\n\ndone!\n");
    return;
}

   struct LL* head = malloc(sizeof(struct LL));
    head->link=NULL;
    head->number=3;
    struct LL* ILLB(struct LL* head, int data){
        struct LL* temp_ILLB = malloc(sizeof(struct LL));
        temp_ILLB->number=data;
        temp_ILLB->link = head;
        head=temp_ILLB;
        return head;
    }
    head = ILLB(head,1);

    void ILLM(struct LL* head, int data, int index){
    if (head == NULL){printf("\n empty LL.");return;}
        struct LL* walker =head;
        int counter=0;
        while(walker!=NULL){
            walker=walker->link;
            counter++;
        }
        if (index > counter){printf("\n invalid index.");return;}
        walker =head;
        for(int i = 0; i < index -1; i++){
            walker=walker->link;
        }
        struct LL* temp_ILLM = malloc(sizeof(struct LL));
        temp_ILLM->link=walker->link;
        walker->link= temp_ILLM;
        temp_ILLM->number=data;
        return;
    }
    ILLM(head,2,1);

void ILLE(struct LL* head, int data){
    struct LL* walker=head;
    while(walker->link!=NULL){
        walker=walker->link;
    }
    struct LL* temp_ILLE = malloc(sizeof(struct LL));
    temp_ILLE->number=data;
    temp_ILLE->link=NULL;
    walker->link=temp_ILLE;
    return;
}
    ILLE(head,4);


struct LL* DLL(struct LL* head,int index){
    if (head == NULL){printf("\n empty LL.");return head;}
    struct LL* walker =head;
        int counter=0;
        while(walker->link!=NULL){
            walker=walker->link;
            counter++;
        }
    

    if (index > counter){
        printf("\n invalid index.");
        return head;}
    walker =head;
    if (index == 0){
        head=walker->link;
        free(walker);
        return head;
    }
    
    for(int i = 0; i < index -1; i++){
            walker=walker->link;
        }
        struct LL* temp_M=walker->link;
        walker->link=temp_M->link;
        free(temp_M);

    return head;
}//DLL


PLL(head);
head = DLL(head,2);
PLL(head);


void clearing_memory(struct LL* delete_LL){
    printf("\n--- Cleaning up memory ---\n");

    struct LL* next_node = NULL;

    while (delete_LL != NULL) {
        next_node = delete_LL->link;     
        free(delete_LL);
        delete_LL = next_node; 
    }
    printf("\ndone!\n\n");
    head = NULL;
}

    clearing_memory(head);

    return;
}

int main(){tests();return 0;}