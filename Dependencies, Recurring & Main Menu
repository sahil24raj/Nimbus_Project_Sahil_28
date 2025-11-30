//==== Mahak Rawat====//

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

// --- User Management ---

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

// --- Main Menu (uses sare students ke functions) ---

int main() {
    TaskList tasks;
    initTaskList(&tasks);     // Student 4

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
            case 3: addTask(&tasks, users, userCount); break;          // S1
            case 4: listAllTasks(&tasks, users, userCount); break;     // S2
            case 5: sortByPriority(&tasks); listAllTasks(&tasks, users, userCount); break;  // S2
            case 6: sortByDeadline(&tasks); listAllTasks(&tasks, users, userCount); break;  // S2 & S5
            case 7: filterByUser(&tasks, users, userCount); break;     // S2
            case 8: filterByTag(&tasks, users, userCount); break;      // S2
            case 9: markTaskComplete(&tasks); break;                   // S3
            case 10: editTask(&tasks); break;                          // S5
            case 11: productivityReport(&tasks, users, userCount); break; // S3
            case 12: setDependency(&tasks); break;                     // S6
            case 13: showDependencies(&tasks); break;                  // S6
            case 14: setRecurring(&tasks); break;                      // S6
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free(tasks.items);
    return 0;
}
