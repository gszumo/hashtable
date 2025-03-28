#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFF)

typedef struct {
    char name[MAX_NAME];
    int age;
    // ... other fields later, maybe
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
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t---<deleted>\n", i);
        } else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
    return;
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }
    if (hash_table[index] != NULL) {
        return false;
    }
    hash_table[index] = p;
    return true;
}

person *hash_table_lookup(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return NULL;
        }
        if (hash_table[try] == DELETED_NODE) {
            continue;
        }
        if (hash_table[try] != NULL && 
            strncmp(hash_table[try]->name, name, MAX_NAME) == 0) {
            return hash_table[try];
        }
    }
    // if (hash_table[index] != NULL && 
    //     strncmp(hash_table[index]->name, name, MAX_NAME) == 0) {
    //     return hash_table[index];
    // }
    return NULL;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return NULL;
        }
        if (hash_table[try] == DELETED_NODE) {
            continue;
        }
        if (hash_table[try] != NULL && 
            strncmp(hash_table[try]->name, name, MAX_NAME) == 0) {
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    // if (hash_table[index] != NULL && 
    //     strncmp(hash_table[index]->name, name, MAX_NAME) == 0) {
    //     person *tmp = hash_table[index];
    //     hash_table[index] = NULL;
    //     return tmp;
    // }
    return NULL;
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