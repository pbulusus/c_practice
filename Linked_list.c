
/*
Author : Praveen Bulusu
Wrote it based on the idea from the computerphile video on linked lists
using pointer to pointer method
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

typedef struct _tnode
{
    char* word;
    struct _tnode* next;;
} tnode;


tnode* create_node(char* word)
{
    tnode* node = (tnode*)malloc(sizeof(tnode));
    node->word = (char*)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(node->word, word);
    node->next  = NULL;
    return node;
}

void add_node(tnode** ptr_root, char word[])
{
    short cond = 1;
    tnode* next;

    while ((*ptr_root != NULL) && ((cond = strcmp(word, (*ptr_root)->word)) > 0))       
        ptr_root = &(*ptr_root)->next;

    if (cond == 0)
    {
        printf("INFO : Item %s already exists.\n", word);
        return;
    }

    next = *ptr_root;
    *ptr_root = create_node(word);
    (*ptr_root)->next = next;
    return;
}

void print_tree(tnode* root)
{
    printf("\n**Printing_List...\n");
    while (root != NULL)
    {
        printf("-%s-\n", root->word);
        root = root->next;
    }
    printf("...END_Printing_List.\n");
}

void delete_node(tnode** ptr_root, char* word)
{
    tnode* temp;
    while(*ptr_root != NULL)
    {
        if (!strcmp(word, (*ptr_root)->word))
        {
            temp = *ptr_root;
            *ptr_root = (*ptr_root)->next;
            free(temp->word);
            free(temp);
            return;
        }
        ptr_root = &(*ptr_root)->next;
    }
    printf("Item to be deleted (%s) NOT FOUND. Or List is empty.\n", word);
}

int main()
{
    tnode* root = NULL;
    char* items[] = {"chips", "wine", "beer", "pizza", "zucchini", "burgers", "burgers", "slaw"};
    //  char* items[] = {"chips", "wine", "beer", "pizza", "zucchini", "burgers", "slaw"};
    unsigned n_items = sizeof(items)/sizeof(char*);
    printf("%d\n", n_items);
    char** ptr_items;
    
    for (ptr_items = items; n_items; --n_items, ++ptr_items)
       add_node(&root, *ptr_items);

    print_tree(root);
    char word[MAXWORD] = "";
    while (1)
    {
        printf("Input Item : ");
        scanf("%s", word);
        if (!isalpha(*word))
            break;
        add_node(&root, word);
    }
    print_tree(root);
    while (1)
    {
        printf("Input Item to be deleted: ");
        scanf("%s", word);
        if (!isalpha(*word))
            break;
        delete_node(&root, word);
    }
    print_tree(root);
    return 0;
}
