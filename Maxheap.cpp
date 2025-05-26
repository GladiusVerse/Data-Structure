#include <stdio.h>

int maxHeap[100];
int dataCount = 1;

int getParentIndex(int index) {
    return index / 2;
}

int getLeftIndex(int index) {
    return index * 2;
}

int getRightIndex(int index) {
    return index * 2 + 1;
}

void viewHeap() {
    if (dataCount <= 1) {
        printf("Your Heap is Empty. Insert more data!\n\n");
    } else {
        for (int i = 1; i < dataCount; i++) {
            printf("Heap[%2d] = %d\n", i, maxHeap[i]);
        }
        puts("");
    }
}

void swapValue(int parentIndex, int currIndex) {
    int temp = maxHeap[parentIndex];
    maxHeap[parentIndex] = maxHeap[currIndex];
    maxHeap[currIndex] = temp;
}

void HeapUp(int index) {
    if (index <= 1) return;

    int parentIndex = getParentIndex(index);
    if (maxHeap[parentIndex] >= maxHeap[index]) return;

    swapValue(parentIndex, index);
    HeapUp(parentIndex);
}

void HeapDown(int index) {
    if (index >= dataCount) return;

    int largest = index;
    int leftValue = getLeftIndex(index);
    int rightValue = getRightIndex(index);

    if (leftValue < dataCount && maxHeap[leftValue] > maxHeap[largest]) {
        largest = leftValue;
    }

    if (rightValue < dataCount && maxHeap[rightValue] > maxHeap[largest]) {
        largest = rightValue;
    }

    if (largest == index) return;

    swapValue(largest, index);
    HeapDown(largest);
}

void push(int input) {
    maxHeap[dataCount] = input;
    HeapUp(dataCount);
    dataCount++;
}

int pop() {
    int removed = maxHeap[1];
    swapValue(1, dataCount - 1);
    dataCount--;
    HeapDown(1);
    return removed;
}

void createMenu() {
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Exit\n");
}

int main() {
    int input = -1, num;
    do {
        printf("Data:\n");
        viewHeap();
        createMenu();

        do {
            printf("Input your choice: ");
            scanf("%d", &input);
            getchar();
        } while (input < 1 || input > 3);

        switch (input) {
            case 1:
                printf("What data should be inputted into the heap? ");
                scanf("%d", &num);
                getchar();
                push(num);
                printf("%d has been inputted into the heap\n\n", num);
                break;
            case 2:
                if (dataCount <= 1) {
                    printf("Your heap is empty. Insert more data!\n\n");
                } else {
                    printf("%d has been deleted\n\n", pop());
                }
                break;
        }
    } while (input != 3);

    return 0;
}
