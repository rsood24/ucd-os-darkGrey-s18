//SAGAR LUITEL
//OS
//PA1
 
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

int main(int argc, char **argv) {
 
    FILE *fileP;
    fileP = fopen("input02.txt", "r");
    
    FILE *outFileP;
    outFileP = fopen("myOutput02.txt", "w");
    
    char word[20];  //string
    char a;
    int i = 0;
    struct node *root = NULL;
    root->left = NULL;
    root->right = NULL;
    root->num = 0;
    
    while (!feof(fileP)) {
        a = fgetc(fileP);
        if(a != ' '){
            word[i] = a;
        }
        else {
             insert(word, &root);
            i = 0;
            
        }
        i++;
    }
    
    Print(root, outFileP);
    
    fclose(fileP);
    fclose(outFileP);
    
    exit(0);
}

