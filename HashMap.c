#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LOAD_FACTOR 0.7
#define INITIAL_SIZE 10

typedef struct KeyValue {
    char *key;
    int val;
    struct KeyValue *next;
} bucket;

typedef struct {
    bucket **table;
    int size;
    int count;
} Hashmap;

typedef unsigned int uint;

uint hash(const char*key, int size) {
    uint hash=0;
    while (*key) {
        hash= hash<<5 + *key++;
    }
    return hash%size;
}

void resizeHashmap(Hashmap *map) {
    int newSize= map->size*2;
    bucket **newTable=calloc(newSize, sizeof(bucket*));
    for (int i=0; i<map->size; ++i) {
        bucket *current=map->table[i];
        while (current!=NULL) {
            uint newIndex=hash(current->key,newSize);
            bucket *next=current->next;
            current->next=newTable[newIndex]; // sets the next pointer of the current bucket to point to the head of the existing entries(if any) at the newIndex in the new table
            newTable[newIndex]=current; // sets the current bucket as the head of the linked list at "newIndex" in the new table
        }
    }
    free(map->table);
    map->table=newTable;
    map->size=newSize;
}

void insert(Hashmap *map, const char *key, int value) {
    if ((float)(map->count+1)/map->size>LOAD_FACTOR) {
        resizeHashmap(map);
    }
    bucket *newEntry=malloc(sizeof(bucket));
    newEntry->key=strdup(key);
    newEntry->val=value;
    newEntry->next=NULL;
    uint index=hash(key,map->size);
    if (map->table[index]==NULL) {
        map->table[index]=newEntry;
        map->count++;
    }
    else {
        bucket *current=map->table[index];
        while(current!=NULL) {
            if ((strcmp(current->key,key))==0) {
                current->val=value;
                free(newEntry->key);
                free(newEntry);
                return;
            }
            current=current->next;
        }
        current->next=newEntry;
        map->count++;
    }
}

void delete(Hashmap *map, const char*key) {
    uint index=hash(key,map->size);
    if (map->table[index]==NULL) {
        printf("No value for key %s\n",key);
        return;
    }
    else {
        bucket *current=map->table[index];
        bucket *prev=NULL;
        while (current!=NULL) {
            if (strcmp(current->key,key)==0) {
                if (prev==NULL) {
                    map->table[index]=current->next;
                    free(current->key);
                    free(current);
                    return;
                }
                else {
                    prev->next=current->next;
                    free(current->key);
                    free(current);
                    return;
                }
            }
            prev=current;
            current=current->next;
        }
    }
}

int retrieve(Hashmap *map, const char *key) {
    uint index=hash(key,map->size);
    bucket *current=map->table[index];
    while (current!=NULL) {
        if (strcmp(current->key,key)==0) {
            return current->val;
        }
        current=current->next;
    }
    printf("No such key present in Hashmap\n");
    return false;
}

Hashmap* generateHashmap() {
    Hashmap *map=malloc(sizeof(Hashmap));
    map->table=calloc(INITIAL_SIZE,sizeof(bucket*));
    map->count=0;
    map->size=INITIAL_SIZE;
    return map;
}

void freeHashmap(Hashmap *map) {
    for (int i=0; i<map->size; ++i) {
        bucket *current=map->table[i];
        while (current!=NULL) {
            bucket *temp=current;
            current=current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->table);
    free(map);
}


int main() {
    Hashmap *map=generateHashmap(); 
    return 0;
}


