// 8 buckets 8 slots

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bucket 8
#define slot 8

// struct for bucket
struct Bucket
{
    int remaining; // how many slots are remaining
    int index[slot];
    int hash[slot];
};

// the 3 arrays of a hashtable
struct HashTable
{
    struct Bucket bucket_table[bucket];
    char *key[bucket * slot];
    int value[bucket * slot];
    int key_val_current_index; // keeps track of how many slots in key and value array are filled
};

struct HashTableCoord
{
    int bucket_index;
    int slot_index;
};

void init(struct HashTable *hashmap)
{
    hashmap->key_val_current_index = 0;

    for (int i = 0; i < bucket; ++i)
    {
        hashmap->bucket_table[i].remaining = 8;
    }

    for (int i = 0; i < bucket; ++i)
    {
        for (int j = 0; j < slot; ++j)
        {
            hashmap->bucket_table[i].hash[j] = 0;
        }
    }

    for (int i = 0; i < bucket; ++i)
    {
        for (int j = 0; j < slot; ++j)
        {
            hashmap->bucket_table[i].index[j] = -1;
        }
    }

    for (int i = 0; i < bucket * slot; ++i)
    {
        hashmap->key[i] = NULL;
    }

    for (int i = 0; i < bucket * slot; ++i)
    {
        hashmap->value[i] = 0;
    }
}

// sdbm - Hash function
// https://stackoverflow.com/a/14409947
int hash_function(char *key)
{
    int hash = 0;

    for (int i = 0; key[i] != '\0'; ++i)
    {
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

int add_key_val(struct HashTable *hashmap, char *key, int value)
{
    hashmap->key[hashmap->key_val_current_index] = key;
    hashmap->value[hashmap->key_val_current_index] = value;

    hashmap->key_val_current_index++;

    return hashmap->key_val_current_index - 1;
}

int add_hashmap(struct HashTable *hashmap, char *key, int value)
{
    int keyhash = hash_function(key);
    int pos = keyhash & (bucket * slot - 1);
    int bucket_index = pos / slot;
    int slot_index = pos & (slot - 1);

    // check if there is room in the bucket
    if (hashmap->bucket_table[bucket_index].remaining == 0)
    {
        // run code to resize hashmap
        printf("You run into a condition which would be normally mitigated by resizing the hashtable. But this is a completely static implementation so that cant happen. Exiting!\n");
        exit(EXIT_FAILURE);
    }

    // once there is room get a index to a free slot
    while (1)
    {
        if (hashmap->bucket_table[bucket_index].hash[slot_index] != 0)
        {
            slot_index++;
            if (slot_index == 8)
            {
                slot_index = 0;
            }

            continue;
        }
        break;
    }

    int index = add_key_val(hashmap, key, value);

    hashmap->bucket_table[bucket_index].hash[slot_index] = keyhash;
    hashmap->bucket_table[bucket_index].index[slot_index] = index;
    hashmap->bucket_table[bucket_index].remaining--;

    return 0;
}

struct HashTableCoord find_stored_hash(struct HashTable *hashmap, char *key)
{
    int keyhash = hash_function(key);
    int pos = keyhash & (bucket * slot - 1);
    int bucket_index = pos / slot;
    int slot_index = pos & (slot - 1);

    int temp = slot_index;
    while (1)
    {
        if (strcmp(hashmap->key[hashmap->bucket_table[bucket_index].index[slot_index]], key))
        {
            // if they are equal strcmp returns 0 and it breaks
            // else slot_index increases to find the correct index
            slot_index++;
            if (slot_index == 8)
            {
                slot_index = 0;
            }

            if (slot_index == temp)
            {
                printf("Not found\n");

                struct HashTableCoord a;
                a.bucket_index = -1;
                a.slot_index = -1;

                return a;
            }

            continue;
        }

        break;
    }

    struct HashTableCoord a;
    a.bucket_index = bucket_index;
    a.slot_index = slot_index;

    return a;
}

int delete_hashmap(struct HashTable *hashmap, char *key)
{
    struct HashTableCoord pos = find_stored_hash(hashmap, key);

    if (pos.bucket_index == -1 || pos.slot_index == -1)
    {
        return 0;
    }

    // check if something is in the bucket, else we can skip
    if (hashmap->bucket_table[pos.bucket_index].remaining == 8)
    {
        // run code to resize hashmap
        printf("Nothing to delete it seems\n");
        return 0;
    }

    // delete it
    hashmap->bucket_table[pos.bucket_index].hash[pos.slot_index] = 0;
    int index = hashmap->bucket_table[pos.bucket_index].index[pos.slot_index];
    hashmap->bucket_table[pos.bucket_index].index[pos.slot_index] = -1;

    // now bring the last entry to the just emptied vaccum
    hashmap->key[index] = hashmap->key[hashmap->key_val_current_index - 1];
    hashmap->value[index] = hashmap->value[hashmap->key_val_current_index - 1]; //because of the remaining variable we simply wont acess this so this is redundant

    hashmap->key_val_current_index--;

    // now goto hashtable and change the entry which references the just moved thing
    struct HashTableCoord xy = find_stored_hash(hashmap, hashmap->key[index]);
    hashmap->bucket_table[xy.bucket_index].index[xy.slot_index] = index;

    hashmap->key[hashmap->key_val_current_index] = NULL;
    hashmap->value[hashmap->key_val_current_index] = 0;

    return 0;
}

int get_hashmap(struct HashTable *hashmap, char *key)
{
    // this function is left as an excercise for you
    // use findStoredHashFunction
    // its simple really
    // you get indexes
    // and use them
    // wont be surp if some of you do it in fewer lines than these comments
    // good luck
}

int main()
{
    struct HashTable hashmap;
    init(&hashmap);
    add_hashmap(&hashmap, "stealth major", 202);
    add_hashmap(&hashmap, "senbonzakura", 2045);
    delete_hashmap(&hashmap, "stealth major");

    return 0;
}
