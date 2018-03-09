//
//  main.c
//  tree
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include <stdio.h>
#include "AVLTree.h"
//#include "ADTTree.h"
void PrintTree(SearchTree T);
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
  
    
    return 0;
}


/**
 中序遍历：先遍历左树再遍历右树
 */
void
PrintTree(SearchTree T){
    if(T != NULL){
        PrintTree(T->left);
        printf("%d",T->element);
        PrintTree(T->right);
    }
}
