// ===== (Dhananjay Saxena )Listing, Sorting & Filtering =====

void printTask(Task t, User users[], int userCount) {
    char assigneeName[MAX_NAME] = "Unknown";
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == t.assigneeId) {
            strcpy(assigneeName, users[i].name);
            break;
        }
    }
    printf("ID:%d | %s | Assignee:%s | P:%d | D:%s | Est:%.1f | Tags:%s | %s\n",
           t.id, t.title, assigneeName, t.priority, t.deadline,
           t.estimatedHours, t.tags,
           t.completed ? "DONE" : "PENDING");
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
