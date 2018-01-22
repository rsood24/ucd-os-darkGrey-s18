//
//  main.c
//  OS_Assign1
//
//  The program reads in words from a file,
//  stores them into a binary tree. It keeps
//  track of how many times each word appeared
//  in the file. It writes all of the words to
//  an output file in alphabetical order. Next
//  to the words it displays the number of times
//  they appeared.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////
// The node struct represnts what each node on    //
// the binary tree will look like. It has a char  //
// string to hold the word we are inserting. An   //
// int count to track the amount of times that    //
// word appears. Two left and right Node pointers //
// to point to subtree nodes.                     //
////////////////////////////////////////////////////
typedef struct Node {

    char *word;
    int count;
    struct Node* left;
    struct Node* right;
    
} Node;

////////////////////////////////////////////////////////
// inOrderInsert does an in-order recursive traversal //
// through the binary tree and inserts the word.      //
// If the word already has a node on the tree, the    //
// function increments the count for that node.       //
// It also frees the node which was allocated in      //
// insertWord, if it already exists.                  //
////////////////////////////////////////////////////////
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

/////////////////////////////////////////
// insertWord allocates a new node     //
// using malloc and then call on       //
// inOrderInsert and passes in the new //
// node to be stored onto the tree.    //
/////////////////////////////////////////
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

////////////////////////////////////////////
// inOrderFree does an inorder traversal  //
// throught the tree and frees every node //
// from memory.                           //
////////////////////////////////////////////
void inOrderFree(Node *leaf){
    
    if(leaf->left != NULL)
        inOrderFree(leaf->left);
    
    free(leaf->word);
    free(leaf);
    
    if(leaf->right != NULL)
        inOrderFree(leaf->right);
    
}

//////////////////////////////////////////////
// inOrderPrint does an inorder traversal   //
// through the tree and writes the contents //
// of each node to an output file.          //
//////////////////////////////////////////////

void inOrderPrint(Node *leaf, FILE *oFile){
    
    if(leaf->left != NULL)
        inOrderPrint(leaf->left, oFile);
    
    fprintf(oFile, "%s : %d\n", leaf->word, leaf->count);
    
    if(leaf->right != NULL)
        inOrderPrint(leaf->right, oFile);
    
}

//////////////////////////////////////////////
// main opens a file to read from and a     //
// file to write to. This is where memory   //
// is allocated for a root node. A do while //
// loop steps through the file and inserts  //
// each word into the tree.                 //
//////////////////////////////////////////////
int main(int argc, char **argv) {
    
    FILE *fptr;
    FILE *oFptr;
    char fileName[] = "/Users/riteshsood/Desktop/os/input02.txt";
    char outFile[] = "/Users/riteshsood/Desktop/os/output01.txt";
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
    inOrderFree(root);
    
    fclose(oFptr);
    
    exit(0);
}

