#include <stdio.h>
#include <ctype.h>
#include <string.h>

void ex1(){

    FILE *source_ex1;
    FILE *con_ex1;
    FILE *vaw_ex1;
    source_ex1= fopen("source_ex1.txt","r");
    vaw_ex1= fopen("vaw_ex1.txt","w");
    con_ex1= fopen("con_ex1.txt","w");

    char charc_ex1, charc_ex1_pw1, charc_ex1_pw2;
    int letter_ex1=0, vaw_int_ex1=0,con_int_ex1=0, space_ex1 = 0, word=0;


    while (fscanf(source_ex1, "%c",&charc_ex1) != EOF){


        if (charc_ex1 == 'o' || charc_ex1 == 'O' || 
            charc_ex1 == 'A' || charc_ex1 == 'a'||
            charc_ex1 == 'I' || charc_ex1 == 'i'|| 
            charc_ex1 == 'e' || charc_ex1 == 'E' ||
            charc_ex1 == 'U' || charc_ex1 == 'u'){
            fprintf(vaw_ex1,"%c", charc_ex1);

            //PW:
            vaw_int_ex1+=1;
            letter_ex1+=1;
            //done

        } else {
            if (charc_ex1 != ' '){
                if (charc_ex1 >= 65 && charc_ex1 <= 90 || 
                    charc_ex1 >= 97 && charc_ex1 <= 122){
                    fprintf(con_ex1,"%c", charc_ex1);

                    //PW:
                    con_int_ex1+=1;
                    letter_ex1+=1;
                    //done

                }             
            } 
        }
    } 

    //PW:
    rewind(source_ex1);
    char prev_ex1= ' ';
    while((charc_ex1 = fgetc(source_ex1)) != EOF){
        if (isalnum(charc_ex1) && !isalnum(prev_ex1)){
            word+=1;
        }
        prev_ex1 = charc_ex1;
    }


    printf("\n letters: %d, vawoles: %d, concenents: %d, words: %d \n",letter_ex1,vaw_int_ex1,con_int_ex1, word);
    //done

    fclose(source_ex1);
    fclose(con_ex1);
    fclose(vaw_ex1);
    return;
}

void ex2(){

    FILE *F1_ex2;
    FILE *F2_ex2;
    FILE *F3_ex2;

    F1_ex2 = fopen("F1_ex2.txt","r");
    F2_ex2 = fopen("F2_ex2.txt","r");
    F3_ex2 = fopen("F3_ex2.txt","w");

    int int1_ex2, int2_ex2, cmp_int_1,cmp_int_2;
    int1_ex2 = fscanf(F1_ex2, "%d",&cmp_int_1);
    int2_ex2 = fscanf(F2_ex2, "%d",&cmp_int_2);
    
    while (int1_ex2 != EOF && int2_ex2 != EOF){
        if (cmp_int_1 > cmp_int_2){
            fprintf(F3_ex2,"%d ", cmp_int_2);
            int2_ex2 = fscanf(F2_ex2, "%d",&cmp_int_2);
        } else {
            fprintf(F3_ex2,"%d ", cmp_int_1);
            int1_ex2 = fscanf(F1_ex2, "%d",&cmp_int_1);
        }
    }
    while(int1_ex2 != EOF){
        fprintf(F3_ex2,"%d ", cmp_int_1);
        int1_ex2 = fscanf(F1_ex2, "%d",&cmp_int_1);
    }
    while (int2_ex2 != EOF){
        fprintf(F3_ex2,"%d ", cmp_int_2);
        int2_ex2 = fscanf(F2_ex2, "%d",&cmp_int_2);
    }
    fclose(F1_ex2);
    fclose(F2_ex2);
    fclose(F3_ex2);
    return;
}

void ex3(){   
    
    
    FILE *F_ex3;
    int int_ex3, counter_ex3=0;
    
    F_ex3 = fopen("F_ex3.txt","w");

    for (int i = 0 ; i <= 100; i++){
        fprintf(F_ex3,"%d ",i);
    }
    fclose(F_ex3);
    F_ex3 = fopen("F_ex3.txt","r");

    while(fscanf(F_ex3,"%d",&int_ex3)==1){
        if (int_ex3%2!=0){
            counter_ex3++;
        }
    }
    if (counter_ex3==0){
        printf("\n the file comtain even integers only.");
    } else{
        printf("\n the file comtain even integers with odd entegers.");
    }
    fclose(F_ex3);
    
    
    return;
}

void ex4(){

    FILE *copy_ex4;
    FILE *paste_ex4;
    char charc_ex4;

    copy_ex4 = fopen("copy_ex4.txt","r");
    paste_ex4 = fopen("paste_ex4.txt","w");

    while(fscanf(copy_ex4, "%c",&charc_ex4) != EOF){
        fprintf(paste_ex4,"%c",charc_ex4);
    }

    fclose(copy_ex4);
    fclose(paste_ex4);
    return;
}


void ex5(){

    FILE *F1_ex5;
    FILE *F2_ex5;

    F1_ex5 = fopen("F1_ex5.txt","a");
    F2_ex5 = fopen("F2_ex5.txt","r");

    char charc_ex5;
    fprintf(F1_ex5,"\n");
    while(fscanf(F2_ex5,"%c",&charc_ex5)!= EOF){

        fprintf(F1_ex5,"%c",charc_ex5);
    }

    fclose(F2_ex5);
    fclose(F1_ex5);
    return;
}

void ex6()
{
    struct StctEx6{
    char last_name_ex6[50];
    char first_name_ex6[50];
    char telephone_number_ex6[11];
    };
 
    //adding
    void mode1_ex6(){ 
        //FILE *entry_file_ex6;
        
        FILE *EntryFileEx6;
        
        struct StctEx6 EntryEtructEx6;
        while (getchar() != '\n');

        printf("\n enter your last name: ");
        fgets(EntryEtructEx6.last_name_ex6,sizeof(EntryEtructEx6.last_name_ex6),stdin);
        EntryEtructEx6.last_name_ex6[strcspn(EntryEtructEx6.last_name_ex6,"\n")]='\0';
        printf("\n enter your first name: ");
        fgets(EntryEtructEx6.first_name_ex6,sizeof(EntryEtructEx6.first_name_ex6),stdin);
        EntryEtructEx6.first_name_ex6[strcspn(EntryEtructEx6.first_name_ex6,"\n")]='\0';
        printf("\n enter your phone number: ");
        fgets(EntryEtructEx6.telephone_number_ex6,sizeof(EntryEtructEx6.telephone_number_ex6),stdin);
        EntryEtructEx6.telephone_number_ex6[strcspn(EntryEtructEx6.telephone_number_ex6,"\n")]='\0';

        EntryFileEx6 = fopen("entry_ex6.dat","ab");
        fwrite(&EntryEtructEx6,sizeof(struct StctEx6),1,EntryFileEx6);
        fclose(EntryFileEx6);
        printf("\n done.");
        return;
    }

    //editing
    void mode2_ex6(){ 
        FILE *ReadEntryFileEx6;
        struct StctEx6 EntryEtructEx6;
        
        char tel_ex6[11];

        printf("\n enter your phone number: ");
        while (getchar() != '\n');
        scanf("%s",tel_ex6);
        
        int found_entery_ex6=0;
        ReadEntryFileEx6 = fopen("entry_ex6.dat","rb");
        while(fread(&EntryEtructEx6,sizeof(struct StctEx6),1,ReadEntryFileEx6)==1){
            if(strcmp(EntryEtructEx6.telephone_number_ex6,tel_ex6)==0){
                found_entery_ex6=1;
                break;
            }
        }
        if (found_entery_ex6 == 0){
            printf("\n not found.");
            fclose(ReadEntryFileEx6);
            return;
        }
        printf("\n  what you want to edit?\n enter: 1 for editting first name.\n enter: 2 for editting last name.\n enter: 3 for editting phone number name.");
        int mode_entery_ex6;
        while (getchar() != '\n');
        scanf("%d",&mode_entery_ex6);
        switch(mode_entery_ex6){
            case 1:
                while (getchar() != '\n');
                printf("\n enter your new fisrt name > ");
                fgets(EntryEtructEx6.first_name_ex6,sizeof(EntryEtructEx6.first_name_ex6),stdin);
                EntryEtructEx6.first_name_ex6[strcspn(EntryEtructEx6.first_name_ex6,"\n")]='\0';
                break;
        
            case 2:
                while (getchar() != '\n');
                printf("\n enter your new last name > ");
                fgets(EntryEtructEx6.last_name_ex6,sizeof(EntryEtructEx6.last_name_ex6),stdin);
                EntryEtructEx6.last_name_ex6[strcspn(EntryEtructEx6.last_name_ex6,"\n")]='\0';
                break;
        
            case 3:
                while (getchar() != '\n');
                printf("\n enter your phone number: ");
                while (getchar() != '\n');
                scanf("%s",EntryEtructEx6.telephone_number_ex6);
                break;

            default:
                printf("\n invalid input");
                fclose(ReadEntryFileEx6);
                return;
        }

        FILE *ReadEntryFileTempEx6;
        ReadEntryFileTempEx6 = fopen("temp_ex6.dat","wb");
        fwrite(&EntryEtructEx6,sizeof(struct StctEx6),1,ReadEntryFileTempEx6);
        while(fread(&EntryEtructEx6,sizeof(struct StctEx6),1,ReadEntryFileEx6)==1){
            if(strcmp(EntryEtructEx6.telephone_number_ex6,tel_ex6)!=0){
                fwrite(&EntryEtructEx6,sizeof(struct StctEx6),1,ReadEntryFileTempEx6);
            }
        }

        fclose(ReadEntryFileEx6);
        fclose(ReadEntryFileTempEx6);
        remove("entry_ex6.dat");
        rename("temp_ex6.dat","entry_ex6.dat");
        return;
    }


    //searching
    void mode3_ex6(){ 
       FILE *SearchEntryFileEx6;
        struct StctEx6 ReadEntryEtructEx6;
        
        char tel_ex6[11];

        printf("\n enter your phone number: ");
        while (getchar() != '\n');
        scanf("%s",tel_ex6);
        int found_entery_ex6=0;
        SearchEntryFileEx6 = fopen("entry_ex6.dat","rb");
        while(fread(&ReadEntryEtructEx6,sizeof(struct StctEx6),1,SearchEntryFileEx6)==1){
            if(strcmp(ReadEntryEtructEx6.telephone_number_ex6,tel_ex6)==0){
                found_entery_ex6=1;
                break;
            }
        }
        if (found_entery_ex6 == 0){
            printf("\n not found.");} else {
            printf("\n entry has been found:\n fisrt name: %s.\n last name: %s.\n phone number: %s.",
            ReadEntryEtructEx6.first_name_ex6,ReadEntryEtructEx6.last_name_ex6,ReadEntryEtructEx6.telephone_number_ex6);
        }
        fclose(SearchEntryFileEx6);
        return;
    }

    //deleting
    void mode4_ex6(){ 
        FILE *DeleteEntryFileEx6;
        struct StctEx6 ReadEntryEtructEx6;
        
        char tel_ex6[11];

        printf("\n enter your phone number: ");
        while (getchar() != '\n');
        scanf("%s",tel_ex6);
        
        int found_entery_ex6=0;
        DeleteEntryFileEx6 = fopen("entry_ex6.dat","rb");
        while(fread(&ReadEntryEtructEx6,sizeof(struct StctEx6),1,DeleteEntryFileEx6)==1){
            if(strcmp(ReadEntryEtructEx6.telephone_number_ex6,tel_ex6)==0){
                found_entery_ex6=1;
                break;
            }
        }
        if (found_entery_ex6 == 0){
            printf("\n not found.");
            fclose(DeleteEntryFileEx6);
            return;
        }

        FILE *DeleteEntryFileTempEx6;
        DeleteEntryFileTempEx6 = fopen("temp_ex6.dat","wb");
        rewind(DeleteEntryFileEx6);
        while(fread(&ReadEntryEtructEx6,sizeof(struct StctEx6),1,DeleteEntryFileEx6)==1){
            if(strcmp(ReadEntryEtructEx6.telephone_number_ex6,tel_ex6)!=0){
                fwrite(&ReadEntryEtructEx6,sizeof(struct StctEx6),1,DeleteEntryFileTempEx6);
            }
        }

        fclose(DeleteEntryFileEx6);
        fclose(DeleteEntryFileTempEx6);
        remove("entry_ex6.dat");
        rename("temp_ex6.dat","entry_ex6.dat");
        return;
    }


    int mode_ex6=0;
    printf("\n enter your mode: \n1: add.\n2: edit.\n3: search.\n4: detele.\n > ");
    scanf("%d",&mode_ex6);
    switch(mode_ex6){
        case 1:
            mode1_ex6();
            break;
        case 2:
            mode2_ex6();
            break;
        case 3:
            mode3_ex6();
            break;
        case 4:
            mode4_ex6();
            break;
        default:
            printf("\n invalid mode.");
    }
    return;
}

void ex7() {
    int channels_ex7 = 0;
    FILE *file_ex7;
    char line_ex7[100]= {'\0'};
    char charc_ex7;
    char string_ex7[50] = {'\0'};
    char result_ex7[100] = {'\0'};

    file_ex7 = fopen("strings_ex7.txt", "w");
    fprintf(file_ex7, "hi\nmy name\nis\nliwa.");
    fclose(file_ex7);

    printf("\nSearching by string (type 1) / by character (type 2): ");
    int mode_ex7;
    scanf(" %d", &mode_ex7);

    file_ex7 = fopen("strings_ex7.txt", "r");

    switch (mode_ex7) {
        case 1:
            printf("\nGive string: ");
            scanf(" %49s", string_ex7);
            while (fgets(line_ex7, sizeof(line_ex7), file_ex7)) {
                line_ex7[strcspn(line_ex7, "\n")] = '\0';
                if (strstr(line_ex7, string_ex7) != NULL) {
                        strcat(result_ex7, line_ex7);
                        channels_ex7++;
                        break;
                    }
            }
            break;
        case 2:
            printf("\nGive character: ");
            scanf(" %c", &charc_ex7);

            while (fgets(line_ex7, sizeof(line_ex7), file_ex7)) {
                for (int i = 0; i < strlen(line_ex7); i++) {
                    if (line_ex7[i] == charc_ex7) {
                        strcat(result_ex7, line_ex7);
                        channels_ex7++;
                        break;
                    }
                }
            }
            break;

        default:
            printf("\nInvalid mode.\n");
            break;
    }

    fclose(file_ex7);

    printf("There are %d channel(s):\n%s", channels_ex7, result_ex7);
    return;
}



int main(){

    ex7();

    return 0;
}