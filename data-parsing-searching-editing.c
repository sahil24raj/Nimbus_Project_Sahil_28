// ===== [ZAHID] Date Parsing, Searching, Editing =====

typedef struct {
    int year, month, day;
} Date;

Date parseDate(const char *s) {
    Date d;
    sscanf(s, "%d-%d-%d", &d.year, &d.month, &d.day);
    return d;
}

int compareDate(Date a, Date b) {
    if (a.year  != b.year)  return (a.year  < b.year)  ? -1 : 1;
    if (a.month != b.month) return (a.month < b.month) ? -1 : 1;
    if (a.day   != b.day)   return (a.day   < b.day)   ? -1 : 1;
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
