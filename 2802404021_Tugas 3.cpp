#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TABLE_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int hashTable[TABLE_SIZE];
Node* chain[TABLE_SIZE];

int midSquare(int key) {
    int square = key * key;
    int mid = (square / 100) % 100;
    return mid % TABLE_SIZE;
}

int division(int key) {
    return key % TABLE_SIZE;
}

int folding(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % TABLE_SIZE;
}

int digitExtraction(int key) {
    return (key / 10) % TABLE_SIZE;
}

int rotation(int key) {
    int lastDigit = key % 10;
    int rotated = (lastDigit * 1000) + (key / 10);
    return rotated % TABLE_SIZE;
}

void insertLinearProbing(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    while (hashTable[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable[index] = key;
}

void insertChaining(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

void insertRehashing(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    if (hashTable[index] == -1) {
        hashTable[index] = key;
    } else {
        int newHash = (index + 7) % TABLE_SIZE;
        while (hashTable[newHash] != -1) {
            newHash = (newHash + 1) % TABLE_SIZE;
        }
        hashTable[newHash] = key;
    }
}

void initialize() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
        chain[i] = NULL;
    }
}

void display() {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] -> ", i);
        if (hashTable[i] != -1) {
            printf("%d", hashTable[i]);
        } else if (chain[i] != NULL) {
            Node* temp = chain[i];
            while (temp) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

int main() {
    initialize();
    int choice, key, hashChoice;
    int (*hashFunction)(int);
    void (*collisionHandler)(int, int (*)(int));

    while (1) {
        printf("\nPilih Metode Hashing:\n");
        printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n6. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        
        if (choice == 6) break;

        switch (choice) {
            case 1: hashFunction = midSquare; break;
            case 2: hashFunction = division; break;
            case 3: hashFunction = folding; break;
            case 4: hashFunction = digitExtraction; break;
            case 5: hashFunction = rotation; break;
            default: printf("Pilihan tidak valid!\n"); continue;
        }

        printf("Pilih metode penanganan tabrakan:\n");
        printf("1. Linear Probing\n2. Chaining\n3. Rehashing\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &hashChoice);

        switch (hashChoice) {
            case 1: collisionHandler = insertLinearProbing; break;
            case 2: collisionHandler = insertChaining; break;
            case 3: collisionHandler = insertRehashing; break;
            default: printf("Pilihan tidak valid!\n"); continue;
        }

        printf("Masukkan kunci (bilangan bulat): ");
        scanf("%d", &key);
        
        collisionHandler(key, hashFunction);
        display();
    }
    return 0;
}
