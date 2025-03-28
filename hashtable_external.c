/*
Understanding and implementing a Hash Table (in C). 
https://www.youtube.com/watch?v=2Ti5yvumFTU
* What is a hash table, and how do I implement one? 
  Hash tables are a fundamental data structure that all student programmers 
  need to have in their toolbox. 

The video describes the basics of hash tables, why they're useful, and 
how you implement them in C. 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
    char name[MAX_NAME];
    int age;
    // ... other fields later, maybe
    struct peroson *next;
    {
        /* data */
    };
    
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
    return;
}

void print_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t ", i);
            person *tmp = hash_table[i];
            while (tmp != NULL) {
                printf("\t%i\t%s\n", i, tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End\n");
    return;
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        tmp = tmp->next;
    }
    return tmp;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strncmp(tmp->name, name, MAX_NAME) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        return NULL;
    }
    if (prev == NULL) {
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}

int main() {
    init_hash_table();
    print_table();

    person jacob = {.name = "Jacob", .age = 256};
    person kate = {.name = "Kate", .age = 27};
    person mpho = {.name = "Mpho", .age = 30};
    person sarah = {.name = "Sarah", .age = 19};
    person jane = {.name = "Jane", .age = 23};
    person maren = {.name = "Maren", .age = 25};
    person bill = {.name = "Bill", .age = 21};
    person edna = {.name = "Edna", .age = 15};
    person eliza = {.name = "Eliza", .age = 34};
    person robert = {.name = "Robert", .age = 1};

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&jane);
    hash_table_insert(&maren);
    hash_table_insert(&bill);
    hash_table_insert(&edna);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);

    print_table();

    hash_table_delete("Mpho");
    person *tmp = hash_table_lookup("Mpho");
    if (tmp == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %s\n", tmp->name);
    }
    tmp = hash_table_lookup("George");
    if (tmp == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %s\n", tmp->name);
    }

    print_table();

    return 0;
}