#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct date {
  int year;
  int month;
  int day;
};

struct client {
  int ID;
  char password[50];
  char tel[11];
  struct date DOB;
  char address[100];
  char first_name[100];
  char last_name[100];
};

struct account {
  int clientID;
  int ID;
  float balance;
  char type;
  int blocked;
};


void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}


void date_today() {
  FILE *date_file;
  date_file = fopen("date.dat", "wb");
  if (date_file == NULL) {
    printf("<erorr> failed to open a date file.\n ");
    return;
  }
  time_t t = time(NULL);
  struct tm *now = localtime(&t);
  struct date today;
  today.year  = now->tm_year + 1900;
  today.month = now->tm_mon + 1;
  today.day   = now->tm_mday;
  fwrite(&today, sizeof(struct date), 1, date_file);
  fclose(date_file);
  return;
}



void save_clients_except(int id) {
  FILE *client_file = fopen("clients.dat", "rb");
  if (client_file == NULL) { printf("<erorr> failed to open client file.\n"); return; }
  FILE *temp_file = fopen("temp_clients.dat", "wb");
  if (temp_file == NULL) { printf("<erorr> failed to open temp file.\n"); fclose(client_file); return; }
  struct client temp_clt;
  while (fread(&temp_clt, sizeof(struct client), 1, client_file) == 1) {
    if (temp_clt.ID != id) {
      fwrite(&temp_clt, sizeof(struct client), 1, temp_file);
    }
  }
  fclose(temp_file);
  fclose(client_file);
  remove("clients.dat");
  rename("temp_clients.dat", "clients.dat");
}



int check_id(int id) {
  FILE *ID_file;
  ID_file = fopen("clients.dat", "rb");
  if (ID_file == NULL) {
    printf("<erorr> failed to open a client file.\n ");
    return -1;
  } 
  struct client clt_ID_ckeck;
  while(fread(&clt_ID_ckeck, sizeof(struct client),1,ID_file)==1){
    if (id == clt_ID_ckeck.ID){
      fclose(ID_file);
      return 1;
    }
  }
  fclose(ID_file);
  return 0;
}

int check_account_id(int id) {
  FILE *ID_file_acnt;
  ID_file_acnt = fopen("accounts.dat", "rb");
  if (ID_file_acnt == NULL) {
    return 0;
  } 
  struct account acnt_ID_ckeck;
  while(fread(&acnt_ID_ckeck, sizeof(struct account),1,ID_file_acnt)==1){
    if (id == acnt_ID_ckeck.ID){
      fclose(ID_file_acnt);
      return 1;
    }
  }
  fclose(ID_file_acnt);
  return 0;
}

int check_age(struct date DOB) {
  FILE *today_file;
  today_file = fopen("date.dat", "rb");
  if (today_file == NULL) {
    printf("<erorr> failed to open a date file.\n ");
    return -1;
  }
  struct date today;
  fread(&today, sizeof(struct date), 1, today_file);

  int age = today.year - DOB.year;
  if (today.month < DOB.month) {
    age -= 1;
  } else if (today.month == DOB.month && today.day < DOB.day) {
    age -= 1;
  }
  fclose(today_file);
  if (age >= 18) {
    return 1;
  } else {
    return 0;
  }
}

int check_phone_number(char tel[11]) {
  if (strlen(tel)<10){return 2;}
  for (int i = 0;i < strlen(tel);i++){
    if (!isdigit(tel[i])){
      return 3;
    }
  }
  FILE *client_file;
  struct client check_tel_struct;
  client_file = fopen("clients.dat", "rb");
  if (client_file == NULL) { return 0; }
  while (fread(&check_tel_struct, sizeof(struct client), 1, client_file) == 1) {
    if (strcmp(tel, check_tel_struct.tel) == 0) {
      fclose(client_file);
      return 1;
    }
  }
  fclose(client_file);
  return 0;
}

void add_client() {
  FILE *client_file;
  struct client clt;
  struct client check_id_struct;

  printf(" <menu/client_manegment/add_client> enter your year of berth. \n <enter> ");
  if (scanf("%d", &clt.DOB.year) != 1) {
    printf("<erorr> invalid input.\n");
    while (getchar() != '\n');
    add_client();
    return;
  }
  while (getchar() != '\n');

  printf(" <menu/client_manegment/add_client> enter your month of berth. \n <enter> ");
  if (scanf("%d", &clt.DOB.month) != 1) {
    printf("<erorr> invalid input.\n");
    while (getchar() != '\n');
    add_client();
    return;
  }
  while (getchar() != '\n');

  printf(" <menu/client_manegment/add_client> enter your day of berth. \n <enter> ");
  if (scanf("%d", &clt.DOB.day) != 1) {
    printf("<erorr> invalid input.\n");
    while (getchar() != '\n');
    add_client();
    return;
  }
  while (getchar() != '\n');

  printf(" <menu/client_manegment/add_client> enter your first name. \n <enter> ");
  fgets(clt.first_name, sizeof(clt.first_name), stdin);
  clt.first_name[strcspn(clt.first_name, "\n")] = '\0';

  printf(" <menu/client_manegment/add_client> enter your last name. \n <enter> ");
  fgets(clt.last_name, sizeof(clt.last_name), stdin);
  clt.last_name[strcspn(clt.last_name, "\n")] = '\0';

  printf(" <menu/client_manegment/add_client> enter your address. \n <enter> ");
  fgets(clt.address, sizeof(clt.address), stdin);
  clt.address[strcspn(clt.address, "\n")] = '\0';

  while (1) {
    printf(" <menu/client_manegment/add_client> enter your phone number (10 digits only). \n <enter> ");
    scanf("%s", clt.tel);
    while (getchar() != '\n');
    if (check_phone_number(clt.tel) == 0) {
      break;
    } else if (check_phone_number(clt.tel) == 1){
      printf(" <erorr> this phone number is used. \n");
    } else {
      printf(" <erorr> invalid number. \n");
    }
  }

  int random_id;
    while (1) {
      random_id = (rand() % 1000000000) + 1000000000;
        if (check_id(random_id)!= 1) {
          break;
        }
      }
  clt.ID = random_id;
  char temp_password[50];
  printf("<menu/client_manegment/add_client> your ID is %d\n", clt.ID);
  while (1) {
    printf("<menu/client_manegment/add_client> enter your password (the max is 49 characters). \n <enter> ");
    scanf("%49s", clt.password);
    printf("<menu/client_manegment/add_client> enter your password again. \n <enter> ");
    scanf("%49s", temp_password);
    if (strcmp(clt.password, temp_password) == 0) {
      break;
    } else {
      printf(" <erorr> not the same password. \n");
    }
  }

  client_file = fopen("clients.dat", "ab");
  if (client_file == NULL) { printf("<erorr> failed to open client file.\n"); return; }
  fwrite(&clt, sizeof(struct client), 1, client_file);
  fclose(client_file);
  printf("<menu/client_manegment/add_client> a new client added.\n");
  return;
}

void search_client() {
  struct client client_search;
  int id_search;
  char password_search[50];

  printf(" <menu/client_manegment/search_client> enter your ID.\n <enter> ");
  if (scanf("%d", &id_search) != 1) {
    printf(" <e> invalid ID.\n");
    while (getchar() != '\n');
    search_client();
    return;
  }
  while (getchar() != '\n');

  printf(" <menu/client_manegment/search_client> enter your password.\n <enter> ");
  fgets(password_search, sizeof(password_search), stdin);
  password_search[strcspn(password_search, "\n")] = '\0';

  FILE *client_file;
  client_file = fopen("clients.dat", "rb");
  if (client_file == NULL) { return; }
  while (fread(&client_search, sizeof(struct client), 1, client_file) == 1) {
    if (client_search.ID == id_search && strcmp(client_search.password, password_search) == 0) {
      printf(" <menu/client_manegment/search_client> client have been found.\n ");
      printf("\n> ID: %d.\n> password: %s.\n> full name: %s %s.\n> address: %s.\n> phone number: %s.\n> date of berth: %d-%d-%d.\n",
        client_search.ID, client_search.password,
        client_search.first_name, client_search.last_name,
        client_search.address, client_search.tel,
        client_search.DOB.year, client_search.DOB.month, client_search.DOB.day);
      fclose(client_file);
      return;
    }
  }
  printf(" <menu/client_manegment/search_client> client have not been found.\n ");
  fclose(client_file);
  return;
}

void edit_client() {
  struct client client_edit;
  int id_edit;
  char password_edit[50];
  int edit_check_var = 0;

  printf(" <menu/client_manegment/edit_client> enter your ID.\n <enter> ");
  if (scanf("%d", &id_edit) != 1) {
    printf(" <e> invalid ID.\n");
    while (getchar() != '\n');
    edit_client();
    return;
  }

  printf(" <menu/client_manegment/edit_client> enter your password.\n <enter> ");
  while (getchar() != '\n');
  fgets(password_edit, sizeof(password_edit), stdin);
  password_edit[strcspn(password_edit, "\n")] = '\0';

  FILE *client_file = fopen("clients.dat", "rb");
  if (client_file == NULL) { printf("<erorr> failed to open a client file.\n"); return; }
  int client_been_found_var = 0;
  while (fread(&client_edit, sizeof(struct client), 1, client_file) == 1) {
    if (client_edit.ID == id_edit && strcmp(client_edit.password, password_edit) == 0) {
      printf(" <menu/client_manegment/edit_client> client have been found.\n");
      client_been_found_var = 1;
      fclose(client_file);
      break;
    }
  }

  if (client_been_found_var != 1) {
    printf(" <menu/client_manegment/edit_client> client have not been found.\n");
    while (getchar() != '\n');
    edit_client();
    return;
  }

  printf("what you want to edit:\n 1 > password.\n 2 > first name.\n 3 > last name.\n 4 > phone number.\n 5 > address.\n 6 > date of berth.\n <enter> ");
  int mode;
  while (1) {
    if (scanf("%d", &mode) != 1) {
      printf(" <e> invalid ID.\n");
      while (getchar() != '\n');
      continue;
    } else {
      while (getchar() != '\n');
      break;
    }
  }

  switch (mode) {
    case 1:
      while (1) {
        edit_check_var = 0;
        printf("<menu/client_manegment/edit_client> enter your new password (the max is 49 characters). \n <enter> ");
        scanf("%49s", client_edit.password);
        while (getchar() != '\n');
        printf("<menu/client_manegment/edit_client> are you sure this is your new password %s? enter 1 for yes, 0 for no, -1 for exit. \n <enter> ", client_edit.password);
        if (scanf("%d", &edit_check_var) != 1) {
          printf(" <erorr> invalid input.\n");
          while (getchar() != '\n');
          continue;
        }
        while (getchar() != '\n');
        if (edit_check_var == -1) { return; }
        else if (edit_check_var == 0) { continue; }
        printf("<menu/client_manegment/edit_client> password have been edited. \n");
        break;
      }
      break;

    case 2:
      while (1) {
        edit_check_var = 0;
        printf("<menu/client_manegment/edit_client> enter your new first name. \n <enter> ");
        fgets(client_edit.first_name, sizeof(client_edit.first_name), stdin);
        client_edit.first_name[strcspn(client_edit.first_name, "\n")] = '\0';
        printf("<menu/client_manegment/edit_client> are you sure this is your new first name %s? enter 1 for yes, 0 for no, -1 to exit.\n <enter> ", client_edit.first_name);
        if (scanf("%d", &edit_check_var) != 1) {
          printf(" <erorr> invalid input.\n");
          while (getchar() != '\n');
          continue;
        }
        if (edit_check_var == -1) { return; }
        else if (edit_check_var == 0) { continue; }
        while (getchar() != '\n');
        printf("<menu/client_manegment/edit_client> first name have been edited. \n");
        break;
      }
      break;

    case 3:
      while (1) {
        edit_check_var = 0;
        printf("<menu/client_manegment/edit_client> enter your new last name. \n <enter> ");
        fgets(client_edit.last_name, sizeof(client_edit.last_name), stdin);
        client_edit.last_name[strcspn(client_edit.last_name, "\n")] = '\0';
        printf("<menu/client_manegment/edit_client> are you sure this is your new last name %s? enter 1 for yes, 0 for no, -1 to exit.\n <enter> ", client_edit.last_name);
        if (scanf("%d", &edit_check_var) != 1) {
          printf(" <erorr> invalid input.\n");
          while (getchar() != '\n');
          continue;
        }
        if (edit_check_var == -1) { return; }
        else if (edit_check_var == 0) { continue; }
        while (getchar() != '\n');
        printf("<menu/client_manegment/edit_client> last name have been edited. \n");
        break;
      }
      break;

    case 4:
      while (1) {
        edit_check_var = 0;
 
        while (1) {
          printf("<menu/client_manegment/edit_client> enter your new phone number. \n <enter> ");
          fgets(client_edit.tel, sizeof(client_edit.tel), stdin);
          client_edit.tel[strcspn(client_edit.tel, "\n")] = '\0';
          if (check_phone_number(client_edit.tel) == 0) {
             break;
          } else if (check_phone_number(client_edit.tel) == 1){
             printf(" <erorr> this phone number is used. \n");
          } else {
            printf(" <erorr> invalid number. \n");
          }
        }

        printf("<menu/client_manegment/edit_client> are you sure this is your new phone number %s? enter 1 for yes, 0 for no, -1 to exit.\n <enter> ", client_edit.tel);
        if (scanf("%d", &edit_check_var) != 1) {
          printf(" <erorr> invalid input.\n");
          while (getchar() != '\n');
          continue;
        }
        if (edit_check_var == -1) { return; }
        else if (edit_check_var == 0) { continue; }
        while (getchar() != '\n');
        printf("<menu/client_manegment/edit_client> phone number address have been edited. \n");
        break;
      }
      break;

    case 5:
      while (1) {
        edit_check_var = 0;
        printf("<menu/client_manegment/edit_client> enter your new address. \n <enter> ");
        fgets(client_edit.address, sizeof(client_edit.address), stdin);
        client_edit.address[strcspn(client_edit.address, "\n")] = '\0';
        printf("<menu/client_manegment/edit_client> are you sure this is your new address %s? enter 1 for yes, 0 for no, -1 to exit.\n <enter> ", client_edit.address);
        if (scanf("%d", &edit_check_var) != 1) {
          printf(" <erorr> invalid input.\n");
          while (getchar() != '\n');
          continue;
        }
        if (edit_check_var == -1) { return; }
        else if (edit_check_var == 0) { continue; }
        while (getchar() != '\n');
        printf("<menu/client_manegment/edit_client> address have been edited. \n");
        break;
      }
      break;

    case 6:
      while (1) {
        int mode2 = 0;
        printf(" <menu/client_manegment/edit_client> what you want to edit:\n-1 > exit.\n 1 > year of berth.\n 2 > month of berth.\n 3 > day of berth.\n <enter> ");
        while (1) {
          if (scanf("%d", &mode2) != 1) {
            printf(" <e> invalid ID.\n");
            while (getchar() != '\n');
            continue;
          } else {
            while (getchar() != '\n');
            break;
          }
        }

        switch (mode2) {
          case -1:
            return;
          case 1:
            while (1) {
              edit_check_var = 0;
              printf("<menu/client_manegment/edit_client> enter your new year of berth.\n <enter> ");
              if (scanf("%d", &client_edit.DOB.year) != 1) {
                printf("<erorr> invalid input.\n");
                while (getchar() != '\n');
              }
              printf("<menu/client_manegment/edit_client> are you sure this is your new year of berth %d? enter 1 for yes, 0 for no, -1 for exit. \n <enter> ", client_edit.DOB.year);
              if (scanf("%d", &edit_check_var) != 1) {
                printf(" <erorr> invalid input.\n");
                while (getchar() != '\n');
                continue;
              }
              if (edit_check_var == -1) { return; }
              else if (edit_check_var == 0) { continue; }
              while (getchar() != '\n');
              printf("<menu/client_manegment/edit_client> year of berth have been edited. \n");
              break;
            }
            break;

          case 2:
            while (1) {
              edit_check_var = 0;
              printf("<menu/client_manegment/edit_client> enter your new month of berth. \n <enter> ");
              if (scanf("%d", &client_edit.DOB.month) != 1) {
                printf("<erorr> invalid input.\n");
                while (getchar() != '\n');
              }
              printf("<menu/client_manegment/edit_client> are you sure this is your new month of berth %d? enter 1 for yes, 0 for no, -1 for exit. \n <enter> ", client_edit.DOB.month);
              if (scanf("%d", &edit_check_var) != 1) {
                printf(" <erorr> invalid input.\n");
                while (getchar() != '\n');
                continue;
              }
              if (edit_check_var == -1) { return; }
              else if (edit_check_var == 0) { continue; }
              while (getchar() != '\n');
              printf("<menu/client_manegment/edit_client> month of berth have been edited. \n");
              break;
            }
            break;

          case 3:
            while (1) {
              edit_check_var = 0;
              printf("<menu/client_manegment/edit_client> enter your new day of berth. \n <enter> ");
              if (scanf("%d", &client_edit.DOB.day) != 1) {
                printf("<erorr> invalid input.\n");
                while (getchar() != '\n');
              }
              printf("<menu/client_manegment/edit_client> are you sure this is your new day of berth %d? enter 1 for yes, 0 for no, -1 for exit. \n <enter> ", client_edit.DOB.day);
              if (scanf("%d", &edit_check_var) != 1) {
                printf(" <erorr> invalid input.\n");
                while (getchar() != '\n');
                continue;
              }
              if (edit_check_var == -1) { return; }
              else if (edit_check_var == 0) { continue; }
              while (getchar() != '\n');
              printf("<menu/client_manegment/edit_client> day of berth have been edited. \n");
              break;
            }
            break;

          default:
            printf(" <erorr> invalid mode.\n");
            continue;
        }
        break;
      }
      break;

    default:
      printf(" <erorr> invalid mode.\n");
      edit_client();
      return;
  }

  save_clients_except(client_edit.ID);
  FILE *append_file = fopen("clients.dat", "ab");
  if (append_file == NULL) { printf("<erorr> failed to open a client file.\n"); return; }
  fwrite(&client_edit, sizeof(struct client), 1, append_file);
  fclose(append_file);
  return;
}

void delete_client() {
  struct client client_delete;
  int id_delete;
  char password_delete[50];

  printf(" <menu/client_manegment/delete_client> enter your ID.\n <enter> ");
  if (scanf("%d", &id_delete) != 1) {
    printf(" <e> invalid ID.\n");
    while (getchar() != '\n');
    delete_client();
    return;
  }

  printf(" <menu/client_manegment/delete_client> enter your password.\n <enter> ");
  while (getchar() != '\n');
  fgets(password_delete, sizeof(password_delete), stdin);
  password_delete[strcspn(password_delete, "\n")] = '\0';

  FILE *client_file_delete = fopen("clients.dat", "rb");
  if (client_file_delete == NULL) { printf("<erorr> failed to open a client file.\n"); return; }
  int client_been_found_var = 0;
  while (fread(&client_delete, sizeof(struct client), 1, client_file_delete) == 1) {
    if (client_delete.ID == id_delete && strcmp(client_delete.password, password_delete) == 0) {
      client_been_found_var = 1;
      fclose(client_file_delete);
      break;
    }
  }

  if (client_been_found_var != 1) {
    printf(" <menu/client_manegment/delete_client> client have not been found.\n");
    fclose(client_file_delete);
    return;
  }

  save_clients_except(client_delete.ID);
  printf(" <menu/client_manegment/delete_client> client have been deleted.\n");
  return;
}


int check_client_password(int id,char pass[50]) {
  FILE *password_file;
  password_file= fopen("clients.dat","rb");
  if (password_file==NULL){printf(" <erorr> file couldn't be opend.\n");return 0;}
  struct client password_clt;
  while(fread(&password_clt,sizeof(struct client),1,password_file)==1){
    if (strcmp(password_clt.password,pass)==0 && id == password_clt.ID){
      fclose(password_file);
      return 1;
    }
  }
  fclose(password_file);
  return 0;
}

void add_bank_account(int id_entered) {
  FILE *bank_account_file;
  struct account acnt;
  struct client clt_age;
  struct date dob;
  acnt.clientID =  id_entered;
  acnt.balance=00.00;
  acnt.blocked=0;

  FILE *check_age_file;
  check_age_file = fopen("clients.dat","rb");
  if (check_age_file==NULL){printf(" <erorr> there is no clients\n");return;}
  while(fread(&clt_age,sizeof(struct client),1,check_age_file)==1){
    if (clt_age.ID == id_entered){
      dob.year = clt_age.DOB.year;
      dob.month = clt_age.DOB.month;
      dob.day = clt_age.DOB.day;
      fclose(check_age_file);
      break;
    }
  }

  if (check_age(dob)==1){
    printf(" <menu/bank_account_manegment/add_bank_account> you are an adualt please enter you account type.\n > Individual (P).\n > Commercial (C). \n <enter> ");
    char acnt_type;
    while(1){
    while (getchar() != '\n');
    scanf("%c",&acnt_type);
    if (acnt_type=='P'|| acnt_type=='p'|| acnt_type=='C'|| acnt_type=='c'){
      acnt.type=acnt_type;
      break;
    } else {
      printf(" <erorr> invalid type.\n");
    }
  }
  }else if (check_age(dob)==0){
    printf(" <menu/bank_account_manegment/add_bank_account> you are a miner, please enter your guardian bank account ID.or enter -1 to exit.\n <enter> ");
    while(1){
      int gard_id;
      while(1){
        if (scanf("%d",&gard_id)==1){
          break;
        }
        else {
          printf(" <erorr> invalid input.\n");
        while(getchar()!='\n');
          
        }
      }
      if(gard_id==-1){
        return;
      }
      else{
        if (check_id(gard_id)==1){
          break;
        } else if (check_id(gard_id)==0){
          printf(" <erorr> ID not found.\n <enter> ");
        }
      }
    }
  }


  int random_id_acnt;
    while (1) {
      random_id_acnt = (rand() % 100000000) + 200000000;
        if (check_account_id(random_id_acnt)!= 1) {
          break;
        }
      }
  acnt.ID = random_id_acnt;
  printf("<menu/client_manegment/add_bank_account> you bank account ID: %d.\n",random_id_acnt);

  bank_account_file = fopen("accounts.dat", "ab");
  if (bank_account_file == NULL) { printf("<erorr> failed to open an account file.\n"); return; }
  fwrite(&acnt, sizeof(struct account), 1, bank_account_file);
  fclose(bank_account_file);
  printf("<menu/client_manegment/add_bank_account> a new bank account added.\n");
  return;
}

void search_bank_account(int id_acnt_search) {
  FILE *acnt_file;
  acnt_file=fopen("accounts.dat","rb");
  if (acnt_file == NULL) { printf("<menu/client_manegment/search_bank_account> no bank account have been found.\n"); return; }
  
  struct account acnt_search;
  int found = 0;
  while(fread(&acnt_search,sizeof(struct account),1,acnt_file)==1){
    if (acnt_search.clientID==id_acnt_search){
      printf("<menu/client_manegment/search_bank_account> bank account have been found:\n > account ID: %d.\n > client ID: %d.\n > balence: %0.2f.\n > account type: %c.\n",
              acnt_search.ID, acnt_search.clientID, acnt_search.balance,
              acnt_search.type);
                    found = 1;

      if (acnt_search.blocked==1){
        printf(" > account blocked.\n");
      } else {
        printf(" > account not blocked.\n");
      }
    }

  }
  if (!found) {
    printf("<erorr> no accounts found for this client.\n");
  }  fclose(acnt_file);
  return;
}






void edit_bank_account() {
  int accounr_id;
  struct account acnt_edit;

  while(1){
  printf("<menu/account_manegment/edit_bank_account> enter your bank account ID.\n");
  if (scanf("%d", &accounr_id) == 1) {
    break;
  }
  printf("<erorr> invalid input.\n");
  while (getchar() != '\n');
  }

  FILE *acnt_file_edit;
  FILE *acnt_file_temp;

  acnt_file_edit=fopen("accounts.dat","rb");
  if (acnt_file_edit == NULL) { printf("<menu/account_manegment/edit_bank_account> no bank account have been found.\n"); return; }
  while(fread(&acnt_edit,sizeof(struct account),1,acnt_file_edit)==1){
    if (accounr_id==acnt_edit.ID){
      break;
    }
  }

  printf("<menu/account_manegment/edit_bank_account> bank account has been found. enter your new account type.\n    <enter> ");
  while(1){
  scanf(" %c",&acnt_edit.type);
  if(acnt_edit.type=='P' || acnt_edit.type=='p' || acnt_edit.type=='C' || acnt_edit.type=='c'){break;}
  else {
    printf(" <erorr> invalid input. \n <enter> ");
  }
  }
  acnt_file_temp =fopen("accounts_temp.dat","wb");
  fwrite(&acnt_edit,sizeof(struct account),1,acnt_file_temp);
  while(fread(&acnt_edit,sizeof(struct account),1,acnt_file_edit)==1){
    if (accounr_id != acnt_edit.ID){
    fwrite(&acnt_edit, sizeof(struct account), 1, acnt_file_temp);
    }
  }
  remove("accounts.dat");
  rename("accounts_temp.dat","accounts.dat");

  fclose(acnt_file_edit);
  fclose(acnt_file_temp);
    printf("<menu/account_manegment/edit_bank_account> bank account has been edited.\n");
  return;
}







void money_into_account(int mode) {
    struct account acnt_deposit;
    float money_amount = 0.00;  
    int account_id;
    printf("\n enter ur bank account ID: ");
    scanf("%lld",&account_id);

    FILE *acnt_file_money = fopen("accounts.dat", "rb");
    if (acnt_file_money == NULL) {
        printf("<menu/account_management/deposit_money> no bank accounts at this moment.\n");
        return;
    }

    int found = 0;
    struct account temp_account;
    while (fread(&temp_account, sizeof(struct account), 1, acnt_file_money) == 1) {
        if (account_id == temp_account.ID) {
            acnt_deposit = temp_account; 
            found = 1;
            break;
        }
    }
    fclose(acnt_file_money);  

    if (!found) {
        printf("<error> account with ID %d not found.\n", account_id);
        return;
    }

    if (mode == 1) {
        printf("<menu/account_management/deposit_money> bank account has been found. "
               "enter how much money you want to deposit in your account.\n    <enter> ");
    } else if (mode == 2) {
        printf("<menu/account_management/withdraw_money> bank account has been found. "
               "enter how much money you want to withdraw from your account.\n    <enter> ");
    }

    while (1) {
        while (getchar() != '\n');
        if (scanf("%f", &money_amount) == 1) {
            if (mode == 1) {
                acnt_deposit.balance += money_amount;
            } else if (mode == 2) {
                if (acnt_deposit.balance < money_amount) {
                    printf("<error> insufficient funds.\n");
                    continue;  
                }
                acnt_deposit.balance -= money_amount;
            }
            break; 
        } else {
            printf("<error> invalid input.\n <enter> ");
        }
    }

    FILE *acnt_file_original = fopen("accounts.dat", "rb");
    if (acnt_file_original == NULL) {
        printf("<error> could not reopen accounts.dat\n");
        return;
    }

    FILE *acnt_file_temp = fopen("accounts_temp.dat", "wb");
    if (acnt_file_temp == NULL) {
        printf("<error> could not create temporary file\n");
        fclose(acnt_file_original);
        return;
    }

    fwrite(&acnt_deposit, sizeof(struct account), 1, acnt_file_temp);

    while (fread(&temp_account, sizeof(struct account), 1, acnt_file_original) == 1) {
        if (temp_account.ID != account_id) {
            fwrite(&temp_account, sizeof(struct account), 1, acnt_file_temp);
        }
    }

    fclose(acnt_file_original);
    fclose(acnt_file_temp);

    remove("accounts.dat");
    rename("accounts_temp.dat", "accounts.dat");
    if (mode == 1) {
        printf("<menu/account_management/deposit_money> %.2f$ have been added to your account.\n > ID: %d.\n",
               money_amount, account_id);
    } else if (mode == 2) {
        printf("<menu/account_management/withdraw_money> %.2f$ have been taken from your account.\n > ID: %d.\n",
               money_amount, account_id);
    }
}

void transfere_funds(int sender_ID) {
    int reciver_ID = 0;
    FILE* transfere_funds_file;
    struct account acnt_trens;
    struct account acnt_reciv;

    printf("<menu/account_management/transfere_money> enter the reciver ID: ");
    while(1){
        if (scanf("%d",&reciver_ID)==1){
          break;
        }
        else {
          printf(" <erorr> invalid input.\n");
        while(getchar()!='\n');
        }
    }
    float amount= 0.00;
    if (check_account_id(reciver_ID) == 1){printf("\n <menu/account_management/transfere_money> account have been found. ");}
    printf("\n <menu/account_management/transfere_money>the amount of moeny you want to transfere: ");
     while(1){
        if (scanf("%f",&amount)==1){
          break;
        }
        else {
          printf(" <erorr> invalid input.\n");
        while(getchar()!='\n');
        }}
    int can_trnsf=0;
    transfere_funds_file = fopen("accounts.dat","rb+");
    while(fread(&acnt_trens, sizeof(struct account),1,transfere_funds_file)==1){
        if(acnt_trens.ID == sender_ID){
            if (acnt_trens.balance >= amount){
                can_trnsf =1;
                acnt_trens.balance-=amount;
                break;
            } else {printf("\n <error> you dont have all that moeny! \n");
            break;
        }
        }
    }
    rewind(transfere_funds_file); 
    while(fread(&acnt_reciv, sizeof(struct account),1,transfere_funds_file)==1){
        if(acnt_reciv.ID == reciver_ID){
            acnt_reciv.balance+=amount;
            break;
        }
    }
rewind(transfere_funds_file);

    FILE* temp_trens_file;
    temp_trens_file = fopen ("accounts_temp.dat","wb+");
    struct account temp_reader;
    fwrite(&temp_reader,sizeof(struct account),1,temp_trens_file);
    while(fread(&temp_reader,sizeof(struct account),1,transfere_funds_file)==1){
         if (temp_reader.ID == sender_ID) {
        temp_reader.balance -= amount;
    }
    else if (temp_reader.ID == reciver_ID) {
        temp_reader.balance += amount;
    }
    fwrite(&temp_reader, sizeof(struct account), 1, temp_trens_file);
    }
    
    fclose(transfere_funds_file);
    fclose(temp_trens_file);
    printf(" <menu/account_management/transfere_money> transfere done! \n");
    remove("accounts.dat");
    rename("accounts_temp.dat", "accounts.dat");
  return;
}


void block_account(int enter_id) {

  printf(" <menu/account_management/block_account> are you sure tou want to block the account? enter y for yes or n for no.");
  char check;
  scanf("%c",&check);
  if (check != 'y'){return;}


  FILE *acnt_file_block;
  struct account acmt_block;
  acnt_file_block = fopen("accounts.dat","rb");
  while (fread(&acmt_block,sizeof(struct account),1,acnt_file_block)){
    if (acmt_block.ID == enter_id){
      acmt_block.blocked = 1;
      break;
    }
  }
  rewind(acnt_file_block);
  FILE *acnt_file_block_temp;
  acnt_file_block_temp = fopen("accounts_temp.dat","wb");
  fwrite(&acmt_block,sizeof(struct account),1,acnt_file_block_temp);
  while(fread(&acmt_block,sizeof(struct account),1,acnt_file_block)){

    if (enter_id != acmt_block.ID){
  fwrite(&acmt_block,sizeof(struct account),1,acnt_file_block_temp);
  }}
fclose(acnt_file_block);
fclose(acnt_file_block_temp);
remove("accounts.dat");
rename("accounts_temp.dat","accounts.dat");
  return;
}

void delete_bank_account(int enter_id) {

  
  printf(" <menu/account_management/delete_account> are you sure tou want to block the account? enter y for yes or n for no.");
  char check;
  scanf("%c",&check);
  if (check != 'y'){return;}


  FILE *acnt_file_delete;
  FILE *acnt_file_delete_temp;
  struct account acmt_delete;

  acnt_file_delete = fopen("accounts.dat","rb");
  acnt_file_delete_temp = fopen("accounts_temp.dat","wb");
  while(fread(&acmt_delete,sizeof(struct account),1,acnt_file_delete)){

    if (enter_id != acmt_delete.ID){
  fwrite(&acmt_delete,sizeof(struct account),1,acnt_file_delete_temp);
  }
fclose(acnt_file_delete);
fclose(acnt_file_delete_temp);
remove("accounts.dat");
rename("accounts_temp.dat","accounts.dat");
  return;
}}


void client_manegment() {
  int mode;
  printf("<menu/client_manegment> enter : \n-1 -> back to main menu.\n 1 -> add client.\n 2 -> search client.\n 3 -> edit client.\n 4 -> delete client.\n <enter> ");
  scanf("%d", &mode);
  switch (mode) {
    case -1:
      return;
    case 1:
      clearScreen();
      add_client();
      break;
    case 2:
      clearScreen();
      search_client();
      break;
    case 3:
      clearScreen();
      edit_client();
      break;
    case 4:
      clearScreen();
      delete_client();
      break;
    default:
      printf("<erorr> invalid mode.\n");
      client_manegment();
      return;
  }
  return;
}



void bank_account_manegment() {
  int enter_id;
  char enter_password[50];
  int mode;
  while (getchar() != '\n');

  printf("<menu/<bank_account_manegment> \n -> enter -1 back to main menu.\n -> enter your client ID.\n <enter> ");
  if (scanf("%d", &enter_id) != 1) {
    printf("<erorr> invalid input.\n");
    while (getchar() != '\n');
    bank_account_manegment();
    return;
  }
  if (check_id(enter_id) != 1 && enter_id != -1) {
    printf("<erorr> ID not found.\n");
    bank_account_manegment();
    return;
  } else if (enter_id == -1) {
    return;
  }

  printf("<menu/bank_account_manegment> \n -> enter -1 back to main menu. \n -> enter your password.\n <enter> ");
  scanf("%49s", enter_password);
  while (getchar() != '\n');
  if (strcmp(enter_password,"-1")==0){return;}
  if (check_client_password(enter_id,enter_password) != 1) {
    printf("<erorr> incorrect password .\n");
    bank_account_manegment();
    return;
  }
while(1){
  printf("<menu/bank_account_manegment> enter: \n-1 -> back to main menu. \n 1 -> add a bank account to this client.\n 2 -> search accounts in this client.\n 3 -> edit account.\n 4 -> deposit money into an account.\n 5 -> transfere funds between accounts. \n 6 -> withdraw money from an account.\n 7 -> block an account. \n 8 -> delete account.\n <enter> ");
  scanf("%d", &mode);
  while (getchar() != '\n');
  switch (mode) {
    case -1:
      return;
    case 1:
      clearScreen();
      add_bank_account(enter_id);
      break;
    case 2:
      clearScreen();
      search_bank_account(enter_id);
      break;
    case 3:
      clearScreen();
      edit_bank_account();
      break;
    case 4:
      clearScreen();
      money_into_account(1);
      break;
    case 5:
      clearScreen();
      transfere_funds(enter_id);
      break;
    case 6:
      clearScreen();
      money_into_account(2);
      break;
    case 7:
      clearScreen();
      block_account(enter_id);
      break;
    case 8:
      clearScreen();
      delete_bank_account(enter_id);
      break;
    default:
      printf("<erorr> invalid mode.\n");
  }
}
  return;
}

int main() {
  srand(time(NULL));
  int mode;
  date_today();

  while (1) {
    printf("<menu> enter : \n 1 -> client manegment.\n 2 -> bank account manegent.\n <enter> ");
    scanf("%d", &mode);
    switch (mode) {
      case 1:
        clearScreen();
        client_manegment();
        break;
      case 2:
        clearScreen();
        bank_account_manegment();
        break;
      default:
        printf("<erorr> invalid mode.\n");
    }
  }
  return 0;
}
