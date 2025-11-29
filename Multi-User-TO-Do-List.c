
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 20
#define MAX_NAME 50
#define MAX_TITLE 100
#define MAX_TAG 50

// =================== Student 4: Dynamic Array & Memory ===================

typedef struct {
    int year, month, day;
} Date;

typedef struct {
    int id;
    char name[MAX_NAME];
} User;

typedef struct {
    int id;
    char title[MAX_TITLE];
    int assigneeId;          // user id
    int priority;            // 1 (high) - 5 (low)
    char deadline[11];       // "YYYY-MM-DD"
    float estimatedHours;
    char tags[MAX_TAG];
    int completed;           // 0 = no, 1 = yes
    int dependencyId;        // -1 if none
    int isRecurring;         // 0/1
} Task;

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

// =================== Student 5: Date Parsing & Searching & Editing ===================

Date parseDate(const char *s) {
    Date d;
    sscanf(s, "%d-%d-%d", &d.year, &d.month, &d.day);
    return d;
}

int compareDate(Date a, Date b) {
    if (a.year != b.year) return (a.year < b.year) ? -1 : 1;
    if (a.month != b.month) return (a.month < b.month) ? -1 : 1;
    if (a.day != b.day) return (a.day < b.day) ? -1 : 1;
    return 0;
}

int findTaskIndexById(TaskList *list, int id) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].id == id) return i;
    }
    return -1;
}

void editTask(TaskList *list) {
    int id;
    printf("Enter task ID to edit: ");
    scanf("%d", &id);
    getchar(); // clear \n

    int idx = findTaskIndexById(list, id);
    if (idx == -1) {
        printf("Task not found.\n");
        return;
    }

    Task *t = &list->items[idx];
    printf("Editing Task ID %d\n", t->id);

    printf("New title (current: %s): ", t->title);
    fgets(t->title, MAX_TITLE, stdin);
    t->title[strcspn(t->title, "\n")] = 0;

    printf("New priority (1-5, current: %d): ", t->priority);
    scanf("%d", &t->priority);
    getchar();

    printf("New deadline YYYY-MM-DD (current: %s): ", t->deadline);
    fgets(t->deadline, 11, stdin);
    t->deadline[strcspn(t->deadline, "\n")] = 0;
    getchar(); // remove extra \n if any

    printf("New tags (current: %s): ", t->tags);
    fgets(t->tags, MAX_TAG, stdin);
    t->tags[strcspn(t->tags, "\n")] = 0;

    printf("Task updated successfully.\n");
}

// =================== Student 1: Add Task with Assignment ===================

int nextTaskId = 1;

void addTask(TaskList *list, User users[], int userCount) {
    if (userCount == 0) {
        printf("No users added yet. Add a user first.\n");
        return;
    }

    Task t;
    t.id = nextTaskId++;

    getchar(); // clear input buffer
    printf("Enter task title: ");
    fgets(t.title, MAX_TITLE, stdin);
    t.title[strcspn(t.title, "\n")] = 0;

    printf("Available Users:\n");
    for (int i = 0; i < userCount; i++) {
        printf("  %d. %s (ID=%d)\n", i + 1, users[i].name, users[i].id);
    }
    printf("Enter assignee user ID: ");
    scanf("%d", &t.assigneeId);

    printf("Enter priority (1=High, 5=Low): ");
    scanf("%d", &t.priority);

    printf("Enter deadline (YYYY-MM-DD): ");
    scanf("%10s", t.deadline);

    printf("Enter estimated time (hours): ");
    scanf("%f", &t.estimatedHours);
    getchar();

    printf("Enter tags (e.g. bug,feature,urgent): ");
    fgets(t.tags, MAX_TAG, stdin);
    t.tags[strcspn(t.tags, "\n")] = 0;

    t.completed = 0;
    t.dependencyId = -1;
    t.isRecurring = 0;

    addTaskToList(list, t);
    printf("Task added with ID %d\n", t.id);
}

// =================== Student 2: Listing, Sorting, Filtering ===================

void printTask(Task t, User users[], int userCount) {
    char assigneeName[MAX_NAME] = "Unknown";
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == t.assigneeId) {
            strcpy(assigneeName, users[i].name);
            break;
        }
    }
    printf("ID:%d | %s | Assignee:%s | P:%d | D:%s | Est:%.1f | Tags:%s | %s\n",
           t.id, t.title, assigneeName, t.priority, t.deadline, t.estimatedHours,
           t.tags, t.completed ? "DONE" : "PENDING");
}

void listAllTasks(TaskList *list, User users[], int userCount) {
    if (list->size == 0) {
        printf("No tasks.\n");
        return;
    }
    for (int i = 0; i < list->size; i++) {
        printTask(list->items[i], users, userCount);
    }
}

void sortByPriority(TaskList *list) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            if (list->items[j].priority > list->items[j + 1].priority) {
                Task temp = list->items[j];
                list->items[j] = list->items[j + 1];
                list->items[j + 1] = temp;
            }
        }
    }
}

void sortByDeadline(TaskList *list) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            Date d1 = parseDate(list->items[j].deadline);
            Date d2 = parseDate(list->items[j + 1].deadline);
            if (compareDate(d1, d2) > 0) {
                Task temp = list->items[j];
                list->items[j] = list->items[j + 1];
                list->items[j + 1] = temp;
            }
        }
    }
}

void filterByUser(TaskList *list, User users[], int userCount) {
    int uid;
    printf("Enter user ID to filter: ");
    scanf("%d", &uid);
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].assigneeId == uid) {
            printTask(list->items[i], users, userCount);
            found = 1;
        }
    }
    if (!found) printf("No tasks for this user.\n");
}

void filterByTag(TaskList *list, User users[], int userCount) {
    char searchTag[MAX_TAG];
    getchar();
    printf("Enter tag to filter: ");
    fgets(searchTag, MAX_TAG, stdin);
    searchTag[strcspn(searchTag, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (strstr(list->items[i].tags, searchTag) != NULL) {
            printTask(list->items[i], users, userCount);
            found = 1;
        }
    }
    if (!found) printf("No tasks with this tag.\n");
}

// =================== Student 3: Mark Complete & Productivity Report ===================

void markTaskComplete(TaskList *list) {
    int id;
    printf("Enter task ID to mark complete: ");
    scanf("%d", &id);
    int idx = findTaskIndexById(list, id);
    if (idx == -1) {
        printf("Task not found.\n");
        return;
    }
    list->items[idx].completed = 1;
    printf("Task %d marked as complete.\n", id);
}

void productivityReport(TaskList *list, User users[], int userCount) {
    int counts[MAX_USERS] = {0};

    for (int i = 0; i < list->size; i++) {
        if (list->items[i].completed) {
            int uid = list->items[i].assigneeId;
            for (int j = 0; j < userCount; j++) {
                if (users[j].id == uid) {
                    counts[j]++;
                    break;
                }
            }
        }
    }

    printf("=== Productivity Report (Completed Tasks Per User) ===\n");
    for (int i = 0; i < userCount; i++) {
        printf("%s (ID=%d): %d tasks completed\n",
               users[i].name, users[i].id, counts[i]);
    }
}

// =================== Student 6: Dependencies + Recurring + Main Menu ===================

void setDependency(TaskList *list) {
    int childId, parentId;
    printf("Enter task ID (child): ");
    scanf("%d", &childId);
    printf("Enter dependency task ID (parent): ");
    scanf("%d", &parentId);

    int cIdx = findTaskIndexById(list, childId);
    int pIdx = findTaskIndexById(list, parentId);

    if (cIdx == -1 || pIdx == -1) {
        printf("Invalid task IDs.\n");
        return;
    }

    list->items[cIdx].dependencyId = parentId;
    printf("Task %d now depends on task %d\n", childId, parentId);
}

void showDependencies(TaskList *list) {
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].dependencyId != -1) {
            printf("Task %d depends on Task %d\n",
                   list->items[i].id, list->items[i].dependencyId);
        }
    }
}

void setRecurring(TaskList *list) {
    int id;
    printf("Enter task ID to mark as recurring: ");
    scanf("%d", &id);
    int idx = findTaskIndexById(list, id);
    if (idx == -1) {
        printf("Task not found.\n");
        return;
    }
    list->items[idx].isRecurring = 1;
    printf("Task %d marked as recurring.\n", id);
}

// =================== Extra: User Management ===================

int nextUserId = 1;

void addUser(User users[], int *userCount) {
    if (*userCount >= MAX_USERS) {
        printf("Max users reached.\n");
        return;
    }
    getchar();
    printf("Enter user name: ");
    fgets(users[*userCount].name, MAX_NAME, stdin);
    users[*userCount].name[strcspn(users[*userCount].name, "\n")] = 0;
    users[*userCount].id = nextUserId++;
    printf("User added with ID %d\n", users[*userCount].id);
    (*userCount)++;
}

void listUsers(User users[], int userCount) {
    printf("=== Users ===\n");
    for (int i = 0; i < userCount; i++) {
        printf("ID=%d | %s\n", users[i].id, users[i].name);
    }
}

// =================== MAIN (Student 6) ===================

int main() {
    TaskList tasks;
    initTaskList(&tasks);

    User users[MAX_USERS];
    int userCount = 0;

    int choice;
    do {
        printf("\n===== Multi-user To-Do Manager =====\n");
        printf("1. Add User\n");
        printf("2. List Users\n");
        printf("3. Add Task\n");
        printf("4. List All Tasks\n");
        printf("5. List Tasks (Sorted by Priority)\n");
        printf("6. List Tasks (Sorted by Deadline)\n");
        printf("7. Filter Tasks by User\n");
        printf("8. Filter Tasks by Tag\n");
        printf("9. Mark Task Complete\n");
        printf("10. Edit Task\n");
        printf("11. Productivity Report\n");
        printf("12. Set Dependency\n");
        printf("13. Show Dependencies\n");
        printf("14. Mark Task as Recurring\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addUser(users, &userCount); break;
            case 2: listUsers(users, userCount); break;
            case 3: addTask(&tasks, users, userCount); break;
            case 4: listAllTasks(&tasks, users, userCount); break;
            case 5: sortByPriority(&tasks); listAllTasks(&tasks, users, userCount); break;
            case 6: sortByDeadline(&tasks); listAllTasks(&tasks, users, userCount); break;
            case 7: filterByUser(&tasks, users, userCount); break;
            case 8: filterByTag(&tasks, users, userCount); break;
            case 9: markTaskComplete(&tasks); break;
            case 10: editTask(&tasks); break;
            case 11: productivityReport(&tasks, users, userCount); break;
            case 12: setDependency(&tasks); break;
            case 13: showDependencies(&tasks); break;
            case 14: setRecurring(&tasks); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free(tasks.items);
    return 0;
}
