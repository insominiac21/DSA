#include <stdio.h>
#include <stdlib.h>

int heap[1000];
int size = 0;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(int index) {
    int parent = (index - 1) / 2;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    while (index > 0 && heap[index] > heap[parent]) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }

    while (index < size) {
        int largest = index;
        left = 2 * index + 1;
        right = 2 * index + 2;

        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            swap(&heap[index], &heap[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void insert(int priority) {
    heap[size] = priority;
    size++;
    heapify(size - 1);
    printf("%d\n", heap[0]);
}

void remove_max() {
    if (size == 0) {
        printf("No jobs available\n");
        return;
    }

    heap[0] = heap[size - 1];
    size--;
    heapify(0);

    if (size > 0)
        printf("%d\n", heap[0]);
    else
        printf("No jobs available\n");
}

void modify_priority(int old_priority, int new_priority) {
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (heap[i] == old_priority) {
            heap[i] = new_priority;
            heapify(i);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("%d\n", heap[0]);
    } else {
        printf("No jobs available\n");
    }
}

void cancel_job(int priority) {
    int found = 0;

    for (int i = 0; i < size; i++) {
        if (heap[i] == priority) {
            heap[i] = heap[size - 1];
            size--;
            heapify(i);
            found = 1;
            break;
        }
    }

    if (found) {
        if (size > 0)
            printf("%d\n", heap[0]);
        else
            printf("No jobs available\n");
    } else {
        printf("No jobs available\n");
    }
}

void list_jobs() {
    if (size == 0) {
        printf("No jobs available\n");
        return;
    }

    int temp[1000];
    for (int i = 0; i < size; i++) {
        temp[i] = heap[i];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                swap(&temp[j], &temp[j + 1]);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", temp[i]);
    }
    printf("\n");
}

int main() {
    int N;
    printf("Enter operations.");
    scanf("%d", &N);

    while(N--) {
        printf("1 Add a new job with priority x.\n2 Complete the job with the highest priority.\n3  Modify a job's priority from old_priority to new_priority.\n4 List all jobs in descending order of priority\n5 Cancel the job with priority x.\n");
        int operation;
        scanf("%d", &operation);

        if (operation == 1) {
            int x;
            scanf("%d", &x);
            insert(x);

        } else if (operation == 2) {
            remove_max();

        } else if (operation == 3) {
            int old_priority, new_priority;
            scanf("%d %d", &old_priority, &new_priority);
            modify_priority(old_priority, new_priority);

        } else if (operation == 5) {
            int x;
            scanf("%d", &x);
            cancel_job(x);

        } else if (operation == 4) {
            list_jobs();
        }
    }

    return 0;
}
