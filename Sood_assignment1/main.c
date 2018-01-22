//
//  main.c
//  OS_Assign1
//
//  Created by Ritesh Sood on 1/21/18.
//  Copyright © 2018 Ritesh Sood. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {

    char *word;
    int count;
    struct Node* left;
    struct Node* right;
    
} Node;


void inOrderInsert(Node* leaf, Node* str)
{
    int check = strcmp(leaf->word, str->word);
    if ( check > 0 )
    {
        if ( leaf->left != NULL )
            inOrderInsert(leaf->left, str);
        else
            leaf->left = str;
    }
    else if ( check < 0 )
    {
        if ( leaf->right != NULL )
            inOrderInsert(leaf->right, str);
        else
            leaf->right = str;
    }
    else if ( check == 0)
    {
        leaf->count += 1;
        free(str->word);
        free(str);
    }
}

void insertWord(Node *root, char* str){
    
    Node* newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->count = 1;
    newNode->word = (char*) malloc(sizeof(str)*sizeof(char));
    strcpy(newNode->word, str);
    
    if(root == NULL)
    {
        newNode->count++;
        root = newNode;
    }
    else
        inOrderInsert(root, newNode);
}

void inOrderPrint(Node *leaf, FILE *oFile){
    
    if(leaf->left != NULL)
        inOrderPrint(leaf->left, oFile);
    
    fprintf(oFile, "%s : %d\n", leaf->word, leaf->count);
    
    if(leaf->right != NULL)
        inOrderPrint(leaf->right, oFile);
        
}


int main(int argc, char **argv) {
    
    FILE *fptr;
    FILE *oFptr;
    char fileName[] = "input02.txt";
    char outFile[] = "output01.txt";
    fptr = fopen(fileName, "r");
    oFptr = fopen(outFile, "w");
    
    char str1[15];
    Node *root;
    root = (struct Node *) malloc(sizeof(struct Node));
    root->left = NULL;
    root->right = NULL;
    root->count = 0;
    
    fscanf(fptr, "%s", str1);
    root->word = (char*) malloc(sizeof(str1)*sizeof(char));
    strcpy(root->word, str1);
    
    do {
        
        insertWord(root, str1);
        
    } while(fscanf(fptr, "%s", str1) != EOF);
    
    fclose(fptr);
    
    inOrderPrint(root, oFptr);
    
    fclose(oFptr);
    
    exit(0);
}
