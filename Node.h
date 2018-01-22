//
//  Node.h
//  PA1
//
//  Created by Sagar Luitel on 1/21/18.
//  Copyright © 2018 Sagar Luitel. All rights reserved.
//

#ifndef Node_h
#define Node_h

struct node
{
    char *data;
    int num;
    struct node *left;
    struct node *right;
};


void insert(char key, struct node **leaf){
    if( *leaf == 0 )
    {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->data = &key;
        /* initialize the children to null */
        (*leaf)->left = 0;
        (*leaf)->right = 0;
    }
    else if(key < (*leaf)->data)
    {
        insert( key, &(*leaf)->left );
    }
    else if(key > (*leaf)->data)
    {
        insert( key, &(*leaf)->right );
    }
}

void Print(struct node *leaf, FILE *outFile){
    
    if(leaf->left != NULL)
        Print(leaf->left, outFile);
    
    fprintf(outFile, "%c : %d\n", leaf->data, leaf->num);
    
    if(leaf->right != NULL)
        Print(leaf->right, outFile);
    
}




#endif /* Node_h */
