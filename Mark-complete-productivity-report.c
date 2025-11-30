// =====[SAHIL RAJ ] Mark Complete & Productivity Report =====

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
