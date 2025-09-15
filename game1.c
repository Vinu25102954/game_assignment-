#include <stdio.h>
char arr[10] = {'0','1','2','3','4','5','6','7','8','9'};
void showBoard();
int main(){
    int player = 1;
    int choice, i;
    char mark; // x or 0
    
do{
 //code
 showBoard();
 player = (player % 2);
} while ( i == -1);
  
   
   return 0;
}
void showBoard(){
    printf("\tTIC-TAC-TOE\n");
    printf("    |       |       \n");
    printf("    |       |       \n");
    printf(" %c  |   %c   |   %c  \n",arr[1],arr[2],arr[3]);
    printf("----|-------|-------\n");
    printf("    |       |       \n");
    printf("    |       |       \n");
    printf(" %c  |   %c   |   %c  \n",arr[4],arr[5],arr[6]);
    printf("----|-------|-------\n");
    printf("    |       |       \n");
    printf("    |       |       \n");
    printf(" %c  |   %c   |   %c  \n",arr[7],arr[8],arr[9]);
    printf("    |       |       \n");
}
