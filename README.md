
**README**

# To-Do Reminder in C

Welcome to the To-Do Reminder App! This simple console application helps you manage your tasks efficiently by providing features like adding tasks, deleting tasks, marking tasks as completed, viewing all tasks, and categorizing tasks. The tasks are stored in a text file, and the app uses a menu-driven approach for user interaction.

## Features

1. **Add a Task**
   - Allows users to add a new task with details such as task name, category, due date, due time, and description.
   - Tasks are automatically assigned a unique task number.

2. **Delete a Task**
   - Enables users to delete a specific task by entering its task number.

3. **Mark as Done**
   - Lets users mark a task as completed, changing its status from "Pending" to "Done."

4. **List All Tasks**
   - Displays a comprehensive list of all tasks, including their details such as name, category, due date, due time, and status.

5. **View Tasks by Category**
   - Allows users to view tasks categorized by "Work," "Personal," "Study," or "Other."

6. **Exit**
   - Exits the application.

## Task Information Structure

Tasks are stored using a structure called `mainMenu`, which includes the following information for each task:

- Task Number
- Name of the Task
- Category
- Description
- Due Date
- Due Time
- Completion Status

## Task File Management

The app utilizes two text files: one for storing task information (`TaskList.txt`) and another for keeping track of the task number (`task_number.txt`). The task number is essential for generating unique task IDs.

## Date Validation

The application ensures the validity of the due date input using a `checkValidity` function. It checks if the date is in the correct format (DD/MM/YYYY) and if it falls within a reasonable range.

## Execution

The main function initializes the task number, displays a welcome message and the main menu, and executes the corresponding action based on the user's choice. The application runs in a loop until the user chooses to exit.

## UI Enhancement

The UI is enhanced with boxed text for menu options, providing a visually appealing interface for the user.

## How to Use

1. **Compile and Run**
   - Compile the program using a C compiler.
   - Run the executable.

2. **Main Menu**
   - Choose an option by entering the corresponding number.
   - Follow the prompts to perform tasks such as adding, deleting, marking as done, or viewing tasks.

3. **Task Input**
   - Follow the prompts to input task details such as name, category, due date, due time, and description.

4. **Category View**
   - When viewing tasks by category, tasks are organized under predefined categories or "Other" if no match is found.

5. **Exit**
   - Choose option 6 to exit the application.

Enjoy using the To-Do Reminder App to stay organized and on top of your tasks!
