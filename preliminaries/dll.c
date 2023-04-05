#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

int main(int argc, char *argv[])
{
    //while (true) {
    //    printf("You have three options:");
    //}
    int c = 0;
    int l = 0;
    char *input = NULL;
    dlist mylist = NULL;
    mylist = create();
    while (1) {
        printf("You have four choices (-1 to exit):\n");
        printf("1. Add an element to a DLL:\n");
        printf("2. Find an element in a DLL:\n");
        printf("3. Delete an element from a DLL:\n");
        printf("4. Print the DLL:\n");
        printf("Enter your choice:\n");
        scanf("%d", &c);
        switch (c) {
            case 1:
                printf("Enter the length of the word to be added:\n");
                scanf("%d", &l);
                input = malloc((l+1) * sizeof(char));
                if (input != NULL) {
                    printf("Enter the word to be added:\n");
                    scanf("%s", input);
                    mylist = add(input, mylist, l);
                }
                break;
            case 2:
                printf("Enter the length of the word to search:\n");
                scanf("%d", &l);
                input = malloc((l+1) * sizeof(char));
                if (input != NULL) {
                    printf("Enter the word to search:\n");
                    scanf("%s", input);
                    int pos = find(input, mylist);
                    if (pos == -1)
                        printf("Word not found in list.\n");
                    else
                        printf("Word %s found at position %d\n", input, pos);
                }
                break;
            case 3:
                printf("Enter the length of the word to delete:\n");
                scanf("%d", &l);
                input = malloc((l+1) * sizeof(char));
                if (input != NULL) {
                    printf("Enter the word to delete:\n");
                    scanf("%s", input);
                    int res = del(input, mylist);
                    if (!res)
                        printf("Deletion successful.\n");
                }
                break;
            case 4:
                if (*(mylist->word) == '\0')
                    printf("List empty, nothing to print.\n");
                else {
                    dlist temp = mylist;
                    while (temp != NULL) {
                        printf("%s -> ", temp->word);
                        temp = temp->next;
                    }
                    printf("\b\b\b\b    \n");
                }
                break;
            case -1:
                destroy(mylist);
                return 0;
                break;
            default:
                printf("Wrong input! Try again..\n");
        } 
    }
    return 0;
}

dlist create() {
    dlist list = malloc(sizeof(*list));
    if (list == NULL) {
        printf("CREATE: Failed to allocate memory \n");
        return NULL;
    }
    list->word = malloc(sizeof(char));
    *(list->word) = ' ';
    list->next = NULL;
    list->prev = NULL;
    return list;
}

void destroy(dlist list) {
    if (list == NULL)
        return;
    if (list->next == NULL) {
        free(list);
        return;
    }
    if (list->next->next == NULL) {
        free(list->next);
        free(list);
        return;
    }
    while (list->next->next != NULL) {
        list = list->next;
    }
    while (list->prev != NULL) {
        free(list->next);
        list = list->prev;
    }
    free(list);
    return;
}

dlist add(char *word, dlist list, int l) {
    // add means add at end
    if (list == NULL) {
        // We do not give an error, we create a list instead.
        list = create();
        list->word = malloc((l+1) * sizeof(char));
        list->word = word;
    } else if (*(list->word) == ' ') {
        list->word = malloc((l+1) * sizeof(char));
        list->word = word;
    } else {
        dlist temp = list;
        while (temp->next != NULL)
            temp = temp->next;
        dlist newnode = malloc(sizeof(newnode));
        if (newnode == NULL) {
            printf("ADD: Failed to allocate memory for new node\n");
            return NULL;
        }
        newnode->word = word;
        temp->next = newnode;
        newnode->next = NULL;
        newnode->prev = temp;
    }
    return list;
}

int find(char *word, dlist list) {
    // returns index if found, else -1
    if (list == NULL) {
        printf("FIND: Empty list passed as argument.\n");
        return -1;
    }
    dlist temp = list;
    int i = 0;
    while (temp->next != NULL) {
        if (equals(temp->word, word))
            return i;
        temp = temp->next;
        i++;
    }
    if (equals(temp->word, word))
        return i;
    return -1;
}

int del(char *word, dlist list) {
    if (list == NULL) {
        printf("DEL: Cannot delete from empty list.\n");
        return 1;
    }
    int pos = find(word, list);
    if (pos == -1) {
        printf("DEL: Word not found.\n");
        return 1;
    }
    dlist temp = list;
    for (int i = 0; i < pos-1; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        list->word = malloc(sizeof(char));
        *(list->word) = ' ';
        return 0;
    }
    if (temp->next->next == NULL)
        temp->next = NULL;
    else {
        temp->next = temp->next->next;
        temp->next->prev = temp;
    }
    return 0;
}

int equals(char *w1, char *w2) {
    int i = 0;
    while (w1[i] != '\0') { // we are making the assumption that strings end in '\0'
        if (w1[i] == w2[i]) {
            i++;
            continue;
        }
        return 0;
    }
    return (w2[i] == '\0');
}
