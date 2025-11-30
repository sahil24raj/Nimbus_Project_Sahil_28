// =====(Dhananjay Saxena Add Task with Assignment =====

int nextTaskId = 1;   // global task ID counter

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

    t.completed   = 0;
    t.dependencyId = -1;
    t.isRecurring = 0;

    addTaskToList(list, t);   // Student 4 ka function use ho raha hai
    printf("Task added with ID %d\n", t.id);
}
