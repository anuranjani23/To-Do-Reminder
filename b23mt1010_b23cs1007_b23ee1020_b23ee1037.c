#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// File names and constants
#define FILENAME "TaskList.txt"
#define TASK_NUMBER_FILE "task_number.txt"
#define MAX_LENGTH_OF_TASKS 100
#define MAX_NUMBER_OF_TASKS 100

void initializeTaskNumber();
void addTask();
void deleteTask();
void markAsCompleted();
void viewTasksByCategory();
void viewTask();
void printBoxedText(const char *text);

// Structure to store task information
struct mainMenu
{
    int taskNumber;
    char nameOftheTask[MAX_LENGTH_OF_TASKS];
    char category[MAX_LENGTH_OF_TASKS];
    char description[100];
    char dueDate[11];
    char dueTime[12];
    char complete[10];
};

// to track the number of tasks
int numOfTask = 0;
int main()
{
    int choiceNumber;

    // Initialize task number from file
    initializeTaskNumber();

    // Display welcome message and main menu
    printf("----------------------------------\n");
    printf("Hello!\n");
    printf("Step into our to-do wonderland, where forgetting is forbidden, and procrastination is politely asked to leave.\n");
    printf("Let the ticking of Tasks begin!\n");
    printf("----------------------------------\n");
    printf("╔════════════════════════════════╗\n");
    printf("║       TO-DO REMINDER APP       ║\n");
    printf("╚════════════════════════════════╝\n");
    printf("----------------------------------\n");
    printf("=========== MAIN MENU ============\n");
    printf("----------------------------------\n");
    printBoxedText("1. Add a Task");
    printBoxedText("2. Delete a Task");
    printBoxedText("3. Mark as Done");
    printBoxedText("4. List All Tasks");
    printBoxedText("5. View Tasks by Category");
    printBoxedText("6. Exit");

    // Execute corresponding action based on user choice
    do
    {
        printf("                                                                    \n");
        printf("Kindly choose your preference by specifying the corresponding number: ");
        scanf(" %d", &choiceNumber);
        while (getchar() != '\n')
            ;
        if (choiceNumber == 1)
        {
            addTask();
        }
        else if (choiceNumber == 2)
        {
            deleteTask();
        }
        else if (choiceNumber == 3)
        {
            markAsCompleted();
        }
        else if (choiceNumber == 4)
        {
            viewTask();
        }
        else if (choiceNumber == 5)
        {
            viewTasksByCategory();
        }
        else if (choiceNumber == 6)
        {
            printf("        \n");
            printf("Goodbye!\n");
            printf("        \n");
        }

        if (choiceNumber <= 0 || choiceNumber > 6)
        {
            printf("Your choice seems to be an invalid input. Please try again!\n");
        }

    } while (choiceNumber != 6);

    return 0;
}

int isValid = 1;
// Function to check if a year is a leap year
int isLeapYear(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}
// Function to check the validity of a date
int checkValidity(const char *dueDate)
{
    if (strlen(dueDate) != 10 || dueDate[2] != '/' || dueDate[5] != '/')
    {
        isValid = 0;
    }
    int day, month, year;
    if (sscanf(dueDate, "%d/%d/%d", &day, &month, &year) != 3)
    {
        isValid = 0; // Not all three components (day, month, year) were successfully parsed
    }
    if (day < 0 || month < 0 || year < 0)
    {
        isValid = 0;
    }
    if (month < 1 || month > 12)
    {
        isValid = 0;
    }
    int maxDaysValidity[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > maxDaysValidity[month - 1] && !isLeapYear(year))
    {
        isValid = 0;
    }
    if (month == 2 && !isLeapYear(year) && (day > 29))
    {
        isValid = 0;
    }
    if (year < 2023 || year > 2100)
    {
        isValid = 0;
    }
    return isValid;
}

// Function to initialize task number from a file or create a new one
void initializeTaskNumber()
{
    FILE *idFile = fopen(TASK_NUMBER_FILE, "r");
    if (idFile == NULL)
    {
        FILE *newIdFile = fopen(TASK_NUMBER_FILE, "w");
        if (newIdFile != NULL)
        {
            fprintf(newIdFile, "0");
            fclose(newIdFile);
        }
        else
        {
            printf("Error initializing task number.\n");
        }
    }
    else
    {
        fclose(idFile);
    }
}

// Function to add a new task
void addTask()
{
    if (numOfTask < MAX_NUMBER_OF_TASKS)
    {
        struct mainMenu newTask;
        FILE *file = fopen(FILENAME, "a");

        if (file == NULL)
        {
            printf("Error opening file.\n");
            return;
        }

        FILE *idFile = fopen(TASK_NUMBER_FILE, "r");
        if (idFile == NULL)
        {
            newTask.taskNumber = 0;
        }
        else
        {
            fscanf(idFile, "%d", &newTask.taskNumber);
            newTask.taskNumber++;
            fclose(idFile);
        }

        idFile = fopen(TASK_NUMBER_FILE, "w");
        fprintf(idFile, "%d", newTask.taskNumber);
        fclose(idFile);

        printf("Enter the name of the Task: ");
        scanf(" %[^\n]", newTask.nameOftheTask);

        printf("Enter the Category of the Task (Work/Personal/Study/Other): ");
        scanf(" %[^\n]", newTask.category);

        do
        {
            isValid = 1;
            printf("Enter Due Date (DD/MM/YYYY): ");
            scanf(" %s", newTask.dueDate);

            if (!checkValidity(newTask.dueDate))
            {
                printf("Invalid date format. Please enter the date in DD/MM/YYYY format.\n");
            }

            // Clear the input buffer
            while (getchar() != '\n');
        } while (!checkValidity(newTask.dueDate));

        printf("Enter Due Time (HH:MM AM/PM): ");
        fgets(newTask.dueTime, sizeof(newTask.dueTime), stdin);

        printf("Enter Description (if any): ");
        scanf(" %[^\n]", newTask.description);
        newTask.nameOftheTask[strcspn(newTask.nameOftheTask, "\n")] = '\0';

        strcpy(newTask.complete, "Pending");

        fprintf(file, "%d) Name of the Task: %s\n   Category: %s\n   Description: %s\n   Due date: %s\n   Due time: %s\n   Status: %s\n",
                newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description,
                newTask.dueDate, newTask.dueTime, newTask.complete);

        fclose(file);
        printf("Task added successfully.\n");
    }
    else
    {
        printf("Looks like our Task list is filled, no more room for extras.\n");
    }
}
// Function to delete task
void deleteTask()
{
    int index;
    printf("Enter the Task Number to be deleted: ");
    scanf("%d", &index);

    FILE *file = fopen(FILENAME, "r+");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct mainMenu newTask;
    int newTaskNumber = 1;

    while (fscanf(file, "%d) Name of the Task: %[^\n]\n   Category: %[^\n]\n   Description: %[^\n]\n   Due date: %[^\n]\n   Due time: %[^\n]\n   Status: %[^\n]\n",
                  &newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description, newTask.dueDate, newTask.dueTime, newTask.complete) == 7)
    {
        if (newTask.taskNumber != index)
        {
            // Assign new task_id and write to the temp file
            newTask.taskNumber = newTaskNumber++;
            fprintf(tempFile, "%d) Name of the Task: %s\n   Category: %s\n   Description: %s\n   Due date: %s\n   Due time: %s\n   Status: %s\n",
                    newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description,
                    newTask.dueDate, newTask.dueTime, newTask.complete);
        }
    }

    FILE *idFile = fopen(TASK_NUMBER_FILE, "w");
    fprintf(idFile, "%d", newTaskNumber - 1);
    fclose(idFile);

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    printf("Task deleted successfully.\n");
}
// function to mark as done
void markAsCompleted()
{
    int index;
    printf("Enter the Task number to be marked as Done: ");
    scanf("%d", &index);

    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int currentTaskNumber = 1;
    struct mainMenu newTask;
    int taskCount = 0;

    while (fscanf(file, "%d) Name of the Task: %[^\n]\n   Category: %[^\n]\n   Description: %[^\n]\n   Due date: %[^\n]\n   Due time: %[^\n]\n   Status: %[^\n]\n",
                  &newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description, newTask.dueDate, newTask.dueTime, newTask.complete) == 7)
    {
        taskCount++;

        if (newTask.taskNumber == index)
        {
            strcpy(newTask.complete, "Done");
        }

        fprintf(tempFile, "%d) Name of the Task: %s\n   Category: %s\n   Description: %s\n   Due date: %s\n   Due time: %s\n   Status: %s\n",
                newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description,
                newTask.dueDate, newTask.dueTime, newTask.complete);

        currentTaskNumber++;
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (taskCount == 0 || index > taskCount)
    {
        printf("Error: Task not found. Please enter a valid Task Number.\n");
    }
    else
    {
        printf("The Task was marked as Done!\n");
    }
}
// function to view task
void viewTask()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }

    struct mainMenu newTask;
    int taskCount = 0;

    printf("\n\n===== TASK LIST =====\n");

    while (fscanf(file, "%d) Name of the Task: %[^\n]\n   Category: %[^\n]\n   Description: %[^\n]\n   Due date: %[^\n]\n   Due time: %[^\n]\n   Status: %[^\n]\n",
                  &newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description, newTask.dueDate, newTask.dueTime, newTask.complete) == 7)
    {
        printf("------------------------------------\n");
        printf("Task Number: %d\n", newTask.taskNumber);
        printf("Name of the Task: %s\n", newTask.nameOftheTask);
        printf("Category: %s\n", newTask.category);
        printf("Description: %s\n", newTask.description);
        printf("Due Date: %s\n", newTask.dueDate);
        printf("Due Time: %s\n", newTask.dueTime);
        printf("Status: %s\n", newTask.complete);

        taskCount++;
    }

    fclose(file);

    if (taskCount == 0)
    {
        printf("No tasks found.\n");
    }
}

// function to view in box
void printBoxedText(const char *text)
{
    int length = strlen(text);
    printf("╔");
    for (int i = 0; i < length + 2; ++i)
    {
        printf("═");
    }
    printf("╗\n");

    printf("║ %s ║\n", text);

    printf("╚");
    for (int i = 0; i < length + 2; ++i)
    {
        printf("═");
    }
    printf("╝\n");
}

void viewTasksByCategory()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct mainMenu newTask;
    int taskCount = 0;

    printf("\n\n====== TASK LIST BY CATEGORY ======\n");

    // Assuming categories are stored in an array
    const char *categories[] = {"Work", "Personal", "Study", "Other"};
    const int numCategories = sizeof(categories) / sizeof(categories[0]);

    // Loop through each category
    for (int i = 0; i < numCategories; ++i)
    {
        printf("\n");
        char categoryText[MAX_LENGTH_OF_TASKS + 20]; // Adjust size as needed
        snprintf(categoryText, sizeof(categoryText), "Category: %s", categories[i]);
        printf("------------------------------------\n");
        printBoxedText(categoryText);

        // Loop through tasks in the current category
        while (fscanf(file, "%d) Name of the Task: %[^\n]\n   Category: %[^\n]\n   Description: %[^\n]\n   Due date: %[^\n]\n   Due time: %[^\n]\n   Status: %[^\n]\n",
                      &newTask.taskNumber, newTask.nameOftheTask, newTask.category, newTask.description, newTask.dueDate, newTask.dueTime, newTask.complete) == 7)
        {

            int isPreDefined = 0;

            if (strcmp(newTask.category, categories[i]) == 0)
            {
                isPreDefined = 1;
                break;
            }
            if (!isPreDefined)
            {
                strcpy(newTask.category, "Other");
            }
            if (strcmp(newTask.category, categories[i]) == 0)
            {
                printf("Task Number: %d\n", newTask.taskNumber);
                printf("Name of the Task: %s\n", newTask.nameOftheTask);
                printf("Description: %s\n", newTask.description);
                printf("Due Date: %s\n", newTask.dueDate);
                printf("Due Time: %s\n", newTask.dueTime);
                printf("Status: %s\n", newTask.complete);
                printf("------------------------------------\n");

                taskCount++;
            }
        }

        // Reset file pointer for the next category
        fseek(file, 0, SEEK_SET);
    }

    fclose(file);

    if (taskCount == 0)
    {
        printf("No tasks found.\n");
    }
}
