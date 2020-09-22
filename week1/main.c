#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "linkedList.h"

int showMenu(void);
void readFile(FILE *fin, node **root);
node *checkUsername(node *root, elementtype e);
void writeFile(FILE *fin, node *root);
void printNode(node *root);
void saveNewAcount(FILE *fout, elementtype e);

int main(){
  // Common variable
  FILE *fin;
  int select;
  node *root;
  elementtype element;
  // elementtype *account = NULL;
  node *account = NULL;

  // Doc file
  fin = fopen("file.txt", "r+");
  if(fin == NULL){
    puts("Read file errors");
    return 0;
  }
  readFile(fin, &root);
  // Main menu
  do{
    select = showMenu();
    switch(select){
      case 1:
        // Xoa bo nho dem
        getchar();
        printf("Enter username: ");
        scanf("%s", element.user_name);
        // Check username
        while(checkUsername(root, element) != NULL){
          puts("Account is existed!");
          printf("Enter username: ");
          scanf("%s", element.user_name);
        }
        printf("Enter password: ");
        scanf("%s", element.password);
        element.status = 1;
        insertAtEnd(&root, element);
        // printNode(root);
        // writeFile(fin, root);
        saveNewAcount(fin, element);
        fclose(fin);

        break;
      case 2:
        // Xoa bo nho dem
        getchar();
        printf("Enter username: ");
        scanf("%s", element.user_name);
        // Check username
        while((account = checkUsername(root, element)) == NULL){
          puts("Username is error!");
          printf("Enter username: ");
          scanf("%s", element.user_name);
        }
        printf("Enter password: ");
        scanf("%s", element.password);
        // Check password
        int count = 0;
        while(strcmp(account->element.password, element.password) != 0){
          count++;
          if(count == 3){
            printf("***Account is blocked@@\n");
            account->element.status = 0;
            fin = fopen("file.txt", "w");
            writeFile(fin, root);
            fclose(fin);
            break;
          }
          printf("Wrong password! Enter password: ");
          scanf("%s", element.password);
        }
        if(count < 3){
          if(account->element.status == 1){
            account->element.login = 1;
            printf("***Sign in successfully\n");
          }else
            puts("***Account is blocked");
        }
        break;
      case 3:
        // Xoa bo nho dem
        getchar();
        printf("Enter username: ");
        scanf("%s", element.user_name);
        account = checkUsername(root, element);
        if(account == NULL){
          puts("***Can not find this account");
        }else if(account->element.status == 0){
          puts("***Account is blocked");
        }else{
          puts("Account is active");
        }
        break;
      case 4:
        // Xoa bo nho dem
        getchar();
        printf("Enter username: ");
        scanf("%s", element.user_name);
        account = checkUsername(root, element);
        if(account == NULL){
          puts("***Can not find this account");
        }else if(account->element.login == 1){
          account->element.login = 0;
          printf("***Goodbye %s\n", account->element.user_name);
        }else{
          puts("Account is not sign in");
        }
        break;
      default:
        puts("Quit!!!");
        break;
    }
  }while(select == 1 || select == 2 || select == 3 || select == 4);
}

int showMenu(){
  printf("USER MANAGEMENT PROGRAM\n");
  printf("-----------------------------------\n");
  printf("\t1. Register\n");
  printf("\t2. Sign in\n");
  printf("\t3. Search\n");
  printf("\t4. Sign out\n");
  printf("\t0. Quit\n");
  printf("Your choice(1-4, other to quit): ");
  int select;
	scanf("%d", &select);
	puts("=====================================");
	return select;
}

void readFile(FILE *fin, node **root){
  (*root) = freeList(*root);
  elementtype element;
  element.login = 0;
  while(fscanf(fin, "%s%s%d", element.user_name, element.password, &(element.status)) != EOF){
    insertAtEnd(root, element);
  }
}

void writeFile(FILE *fin, node *root){
  node *temp = root;
  while(temp != NULL){
    fprintf(fin, "%s %s %d\n", temp->element.user_name, temp->element.password, temp->element.status);
    temp = temp->next;
  }
}

void saveNewAcount(FILE *fout, elementtype e){
  fprintf(fout, "%s %s %d\n", e.user_name, e.password, e.status);
}

node *checkUsername(node *root, elementtype e){
  node *temp = root;
  while(temp != NULL){
    // printf("***%s", e.user_name);
    // printf("*%s\n", temp->element.user_name);
    if(strcmp(temp->element.user_name, e.user_name) == 0)
      return temp;
    temp = temp->next;
  }
  return NULL;
}
void printNode(node *root){
  node *temp = root;
  while(temp != NULL){
    printf("%s-%s-%d\n", temp->element.user_name, temp->element.password, temp->element.status);
    temp = temp->next;
  }
}

// void signIn()

