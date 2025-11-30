// ===== [SAHIL RAJ] Dynamic TaskList & Memory Management =====

typedef struct {
    Task *items;
    int size;
    int capacity;
} TaskList;

void initTaskList(TaskList *list) {
    list->capacity = 10;
    list->size = 0;
    list->items = (Task *)malloc(list->capacity * sizeof(Task));
    if (!list->items) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void ensureCapacity(TaskList *list) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        Task *newArr = (Task *)realloc(list->items, list->capacity * sizeof(Task));
        if (!newArr) {
            printf("Reallocation failed!\n");
            exit(1);
        }
        list->items = newArr;
    }
}

void addTaskToList(TaskList *list, Task t) {
    ensureCapacity(list);
    list->items[list->size++] = t;
}
