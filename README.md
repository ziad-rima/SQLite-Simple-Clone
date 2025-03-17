# 🛠️ Building My Own Database  
This repository documents my journey as I build a database from scratch, inspired by the "build-your-own-x" GitHub repository. The goal is to understand how databases work at a low level.  

## 📌 Project Overview  
- **Project Name:** SQLite Database Clone from Scratch
- **Type:** Relational Database (SQL-based)
- **Language Used:** C
- **Main Goal:** Understand how relational databases work under the hood by implementing a minimal SQLite-like database from scratch. 
- **Inspiration:** build-your-own-x GitHub repository   

## 🚀 Progress Timeline  
### ✅ Phase 1: Understanding Databases (Learning & Planning) 
- [ ] Understanding the high level aspect of databases 
- [ ] Research database fundamentals (storage, indexing, queries)  
        

## 📝 Lessons & Challenges  

### 📌 What I Learned So Far

#### What is a database?
- A database is a structured collection of data that allows for efficient storage, retrieval, and management.
- An example that would well clarify the concept is a library. A library has thousands of books, but they’re not just thrown around randomly. Instead, they’re neatly arranged on shelves, categorized by genre, author, and title so people can quickly find what they need. But databases store information instead of books, like customer details, product inventories, etc. (In fact, they can also store books as data, with authors, genre, etc.)
    
#### Types of databases: 
- There are primarily two types of databases: 
    - Relational Databases (SQL, or Structured Query Language), where data is stored in tables (rows and columns). For example, MySQL
    - Non-Relational Databases (NoSQL), where data cannot be stored neatly into a table. Such as text, images, videos, logs, etc. For example, MongoDB

#### Where do databases exist?
- Pretty much everywhere, we just don't notice them. They work behind the scenes in almost every digital device we use. Some common places where databases exist are:

##### On Mobile Devices
- The contacts app is a mini-database storing names, phone numbers, and emails.
- The photos app organizes pictures with dates, locations, and tags.

##### On the Internet
- Social media platforms like Facebook and Instagram store users, posts, likes, and comments.
- E-commerce sites like Amazon and eBay track products, prices, customers, and orders.

##### In Businesses & Government 
- Banks store customer accounts, balances, and transactions.
- Hospitals keep records of patients, doctors, and medical history.
- Airlines manage flights, tickets, and passenger details.

##### On Personal Computers
- When we save an Excel sheet with names and numbers, that's a simple database.


#### Where are databases physically stored?
- They exist in servers inside data centers (physical locations) or in the cloud (online storage managed by companies like Google, Amazon, or Microsoft).


#### How do databases store data?
- Databases store data in files on disk, using optimized storage structures. For example:
    - Pages & Blocks: where data is stored in a fixed-size blocks. But data inside pages
    can be either fixed-size (like date) or variable-size (like text data).
    - Indexes: extra data structures to make searching faster. 
    ##### Storage Models:
    - Relational (SQL) Storage -> Uses tables with rows and columns
    - Document-based Storage -> Uses JSON-like objects instead of tables
    - Key-Value Storage -> Stores key-value pairs like a python dictionary.

#### How do databases retrieve data?

##### Sequential Scan (Slow):
- Reads all the data one by one until it finds the right record
- E.g., searching for a user in a non-indexed table

##### Indexing (Fast):
- Searching by pointing directly to data
- Types of indexing include B-Trees and Hash Indexes

#### SQLite 

##### What is it?
- A C-language library that implements a small SQL database engine (according to the SQLite Internals documentation)
- It is also used to develop embedded software for devices like television, cameras, etc.

##### More to know 
- Every SQL database engine works in roughly the same way: 
    - Translates the input SQL text into a "prepared statement"
    - Executes the prepared statement to generate a result 

- What is a prepared statement?
    - It is an object that represents the steps needed to accomplish the input SQL. In other words,
    it is the SQL statement translated into a form that is more easily understood by the compiler.

- SQLite implements a prepared statement through the Bytecode method, where the input SQL is translated into virtual machine language, then run by a virtual machine interpreter.

- When a SQL statement is ready, SQLite parses it into a parse tree and compiles it into a bytecode program.
- This bytecode is then executed by SQLite's Virtual Database Engine (VDBE), which interprets and processes the statement efficiently.  

###### The Whole Process
- Tokenizing → SQLite breaks the SQL query into tokens.
- SQL Parsing → SQLite analyzes the SQL syntax and creates a parse tree.
- Compilation → The parse tree is converted into VDBE bytecode (low-level instructions for SQLite’s virtual machine or simply opcodes).
- Prepared Statement Created → The resulting bytecode program is stored in an internal structure, making it a prepared statement.
- Execution → The VDBE interprets and runs the bytecode, executing the SQL operation.

- The bytecode program in SQLite consists of multiple instructions.
- Each instruction has: 
    - An opcode (operation code) → tells the SQLite what to do
    - 5 operands (P1, P2, P3, P4, P5) →  extra data for the instruction

- Example opcodes (for a `SELECT` query):
```sql
OpenRead    0       # Open table
Integer     1       # Load value '1' into a register
SeekRowid   0       # Move to the row where id = 1
Column      0       # Extract the 'name' column
ResultRow   0       # Return the result
Halt               # Stop execution
```

- The VDBE (Virtual Database Engine) executes the instruction and perform operations on one or more tables or indexes, each table or index is stored in a data structure called a B-Tree (check references). 

- B-tree stores data efficiently in a balanced tree structure.
- Each node in the tree is a page in memory or disk.
- Searching, inserting, and deleting data is efficient (logarithmic time complexity).
- B-tree issues commands to the `Pager`

- Pager manages reading/writing pages from the database file.
- keeps recently-used pages cached in memory to improve performance.
- Decides when dirty pages (modified pages) should be written back to disk.

- OS Interface is the lowest layer that interacts with the operating system.
- Handles file I/O, locking (to prevent corruption), and memory allocation.

#### What is a REPL?
- A REPL (Read-Evaluate-Print Loop) is a type of interactive programming environment where you can type commands, see results immediately, and keep going in a loop. 

##### How it works exactly?
- Read -> takes the user's input (a command or a SQL query/instruction in our case).
- Evaluate -> processes the command (executes it).
- Print -> shows the result of the command.
- Loop -> repeats the process (to take another command).

#### Code Concepts

##### Preprocessor directives

- like `#define`, it defines a constant and assigns it a value. Preprocessor directives are useful because they don't take up memory, they're processed before compilation.

##### Functions

- `strcspn`: finds the first occurrence of any character in a set of characters in a given string and returns the index (position) of that character. If no match is found, it returns the length of the given string.

- `strcmp`: compares two strings, it returns 0 if the strings are exactly the same.

- `getline`: reads a line of text from a given input stream into a buffer or character array. It can read input from stdin, a file stream, or other sources. And it reads one line at a time and stores it in the buffer.
    - function prototype: 
        ```c
        ssize_t getline(char **lineptr, size_t *n, FILE *stream);
        ```
        ```c
        char **lineptr -> a pointer to a buffer, where the input line will be stored.
            if *lineptr is NULL, getline() will allocate memory dynamically.
            if *lineptr is already allocated, getline() may resize it if needed.
        size_t *n -> pointer to the buffers size. 
            if *n is too small, getline() increases its size. 
        FILE *stream -> Input source (e.g., stdin for user input). 
        ``` 
    - `getline()` returns the number of characters that are read in bytes, including the newline character, but not including the terminating null byte ('\0')
    - Meaning I should replace the newline character with the terminating null byte to have a clean string (input).
    - [SOURCE](https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-getline-read-entire-line-from-stream)

- `sscanf()`: reads data from _buffer_ into the locations that are given by the third argument (called argument list). Each _argument_ must be a pointer to a variable that corresponds to the type specifier in the _format-string_. It returns the number of fields that were successfully converted and assigned.
    format:
    ```c
        int sscanf(const char *buffer, const char *format, argument-list);
    ```
    - [SOURCE](https://www.ibm.com/docs/en/i/7.3?topic=functions-sscanf-read-data)

- `memcpy()`: copies a block of memory from one location to another. It doesn't care about data types—it just moves bytes. 
    format:
    ```c
        void *memcpy(void * __restrict__dest, const void * __restrict__src, size_t count);
    ```
    - copies the count bytes from the object pointed to by `src` to the object pointed to by `dest`.
    - `count` is the number of bytes to copy.
    - `memcpy()` returns a `void*` pointer to `dest`.
    - [SOURCE](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-memcpy-copy-buffer)

- `strtok()`: 
    format:
    ```c
        char *strtok(char * __restrict__string1, const char * __restrict__string2);
    ```
    - Breaks a character string, pointed to by `string1`, into a sequence of tokens. The tokens are separated from one another by the characters in the string pointed to by `string2`. 
    - [SOURCE](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-strtok-tokenize-string)

- `atoi()`: converts a string of characters to an integer value.
    -[SOURCE](https://www.scaler.com/topics/atoi-function-in-c/)


##### Enum (Enumerations) 
- An enum is a data type that represents a group of constants, with unchangeable values. 
- Syntax:
```c
enum Week {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
```
- Similar to `struct` data types, to declare an `enum` variable in `main()`:
```c
enum Week today;
```   
- And assign a value to it, the value should be one the items inside the `enum`:
```c
enum Week today = SUNDAY;
```
##### Macros
- A macro in C is a symbolic name or constant that represents a value, expression, or code snippet. They are are defined using the `#define` directive, and when encountered, the preprocessor substitutes it with its defined content.
- [SOURCE](https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/)

## My process

- Following through multiple sources and the GitHub repository, I started by creating a REPL (Read-Evaluate-Print Loop), since SQLite starts a REPL when being started from the command line.   

- My initial code was as follows:
```c
#include <stdin.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 1024

void read_input(char* input_buffer) {
    printf("db > ");
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);

    input_buffer[strcspn(input_buffer, "\n")] = 0;
}

int main() {
    char* input_buffer[INPUT_BUFFER_SIZE];

    while (1) {
        read_input(input_buffer);
        
        if (strcmp(input_buffer, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Unrecognized command: %s\n", input_buffer); // just initially
        }
    }
    return 0;
}
``` 
- Then, I changed the process to be more dynamic, hence using pointers and following memory management techniques. 
- I initialized a wrapper around the user input, to make working with it efficient. I declared three variables: 
    - `buffer`: which is the actual input entered by the user.
    - `buffer_length`: this is what stores the size of the allocated memory. 
    - `input_length`: this represents how many characters the user has entered.

```c
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;
``` 
- I built another function, `new_input_buffer()`, which initializes an instance of the InputBuffer, returning a pointer to it. 

```c
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}
```
- The main reason behind building this function was so that I could easily and efficiently manage the buffer (or the user input). For example, `getline()` function works by reading text entered by the user and storing it in a buffer (`input_buffer->buffer` in this case), along with how much memory was allocated for it (`input_buffer->buffer_length`), so, it is useful to store all of this inside a wrapper, or our struct instance (`input_buffer`). In other words, `new_input_buffer` creates a container that holds the buffer and its related information (`buffer_length` and `input_length`). 
- And the `buffer` is just a pointer to an array of characters. If the user enters "hello", for example, `buffer` would be: `buffer → ['h', 'e', 'l', 'l', 'o', '\n', '\0']`. 

- The next step was to create a function that:
    - reads the inputs entered by the user
    - since `getline()` stores the input inside the buffer, and includes the newline character (`\n`). The created function should transform (I'm not sure that's the right word) the buffer to a clean string, by removing the newline character.

```c
void read_input(InputBuffer* input_buffer) {
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input...\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->buffer[bytes_read - 1] = 0;
    input_buffer->input_length = bytes_read - 1;
}
```
- This line: `size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);`:
    - Takes the user's input
    - Stores it in `input_buffer->buffer` (`input_buffer` is an instance of the `InputBuffer` struct)
    - Stores how much memory was allocated for the buffer in bytes in `input_buffer->buffer_length`
    - Removes the newline character, `input_buffer->buffer[bytes_read - 1] = 0`
    - Returns how many characters the user has entered, which I then stored in `input_buffer->input_length` (`input_buffer->input_length = bytes_read - 1`)

- One last function to finish this REPL, a function that frees the memory allocated for both the instance `input_buffer` and the buffer `input_buffer->buffer` whose memory was allocated by `getline()` function.

```c
void clean_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
```

- And this is the `main()` function (similar to the previous version):
```c
int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        printf("db > ");
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0) {
            printf("Exiting...\n");
            clean_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("unrecognized command: %s\n", input_buffer);
        }
    }

    return 0;
}
```

- When I tried to compile the file, it resulted in an error indicating an undefined reference to `getline`. After looking up solutions, I found out that on Windows, the `getline()` function is not part of the standard C library and is not available by default. It's a POSIX-specific function, which means it's  found on Linux and macOS, but not on Windows (MinGW/MSVC).

- There were two solutions to this problem, I either got to use an alternative to `getline()`, which would be `fgets()`, or I could implement `getline()` myself, since it's just a function. I chose to use `fgets()` instead, but there were some necessary changes I needed to implement in order for it to work properly, because:
    - `fgets()` returns a pointer (char*) to the buffer, not a `ssize_t` (which `getline()` does).
    - I should check if `fgets()` returns NULL (which means an error occurred).
    - `fgets()` expects a character buffer, its size, and stdin.
    - Since `getline()` dynamically allocates memory, buffer is initially `NULL`, but `fgets()` needs a valid pre-allocated buffer.

- The changed code: 

```c
void read_input(InputBuffer* input_buffer) {
    if (input_buffer->buffer == NULL) {
        input_buffer->buffer_length = 1024;
        input_buffer->buffer = malloc(input_buffer->buffer_length);
        if (input_buffer->buffer == NULL) {
            printf("Memory allocation failed...\n");
            exit(EXIT_FAILURE);
        }
    }

    if (fgets(input_buffer->buffer, input_buffer->buffer_length, stdin) == NULL) {
        printf("Error reading input...\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = strlen(input_buffer->buffer);
    if (input_buffer->buffer[input_buffer->input_length - 1] == '\n') {
        input_buffer->buffer[input_buffer->input_length - 1] = '\0'; 
        input_buffer->input_length--;
    }
}
```
- Now, the code works as expected.

- What are meta-commands?
    - Meta-commands are non-SQL statement, they start with a dot '.'
    - Following the GitHub repository, I found that it was better if I handled those commands in a separate function

```c
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommand;
```
```c
MetaCommand meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit")) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}
```
- the `meta_command` function handles meta-commands. Initially, it just handles the "exit" command, I will probably add more commands later on. 
- Updated `main()` function:
```c
int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        printf("db > ");
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (meta_command(input_buffer))
            {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized Command: %s\n", input_buffer->buffer);
                    continue; 
            }
        }
    }
    return 0;
}
```

- Next, I need to handle SQL commands, or statements. By converting the command into the internal representation of a statement. Using an `enum` to achieve that. Since `enum` gives us constant values, I can make use of that.
```c
typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT
} StatementType;
```

- Also, I need a way to check if the statement is "prepared", meaning it is converted into the internal representation. For that, another `enum` is useful. 
```c
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;
```

- Lastly, I will make use of `struct` to capture the statement entered by the user:
```c
typedef struct {
    StatementType type;
} Statement;
```

- Now, I'll write a `prepare_statement()` function to "prepare", or convert the statement the user entered into the internal representation of a SQL command:
```c
PrepareResult prepare_statement (InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}
```

- Next comes our `execute_command()` function, which only needs the statement type in order to execute code:
```c
void execute_command(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT) 
            printf("This is where insert code goes...\n");
            break;
        case (STATEMENT_SELECT) {
            printf("This is where select code goes...\n");
            break;
        }
    }
}
```

- Updated `main()` function:
```c
int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        printf("db > ");
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (meta_command(input_buffer))
            {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized Command: %s\n", input_buffer->buffer);
                    continue; 
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_COMMAND):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }
        execute_command(&statement);
        printf("Executed.\n");
    }

    return 0;
}
```

- To summarize what I did in this part:
    - After building the REPL, our interface is now ready to take commands.
    - There are two types of commands: SQL commands and Non-SQL commands (or meta-commands).
    - The point of meta-commands is for the user to interact with the program in order to exit the REPL for example.
    - We made use of `enum` data types so we could have a clear language to handle cases efficiently. 
    - The `enum` data types I used above were: `MetaCommand`, `PrepareResult`, and `StatementType`. Where:
        - `MetaCommand`: Provides a clear language as to whether the command that has been entered by the user is valid (recognized). It has two values: `META_COMMAND_SUCCESS` and `META_COMMAND_UNRECOGNIZED_COMMAND`. It works with `meta_command()` function.
        - `PrepareResult`: Our SQL statement needs to be prepared (compiled, or converted to its internal representation) in order to be executed. To achieve this, I used `enum` data type as a way to check if preparing the statement has been successful. It has two values as well: `PREPARE_SUCCESS` and `PREPARE_UNRECOGNIZED_COMMAND`. It works with `prepare_statement()` function.
        - `StatementType`: The language to which the SQL statement needs to be converted, is simply managed by this `enum` data type. For now, the SQL statement is converted to either `STATEMENT_INSERT` or `STATEMENT_SELECT`, which will then be used to execute the corresponding code.
    - I stored the converted SQL statement in a `struct` data type instance. `Statement` which has a `type` variable of a `StatementType` type. So we can see now that there isn't any actual "conversion," we just store the type of SQL command (`SELECT` or `INSERT` for now) in a variable (`type`) based on user's input.
    - I then created the `execute_command()` function which, based on `type` (`SELECT` or `INSERT`), will execute code.

- Following along with the GitHub repository, we're going to be working with hard-coded table, meaning:
    - The table's structure (columns, data types, etc.) is predefined in the code. 
    - Unlike real databases where we can define multiple tables (e.g, `users`, `orders`, `products`), this database will only have one table that's hardwired into the code.
    - In real databases, we can define column names, types, etc., but for our database, the table's structure is manually written into the program.

- Our table's structure is as follows:

| Column   | Type          |
|----------|--------------|
| id       | integer      |
| username | varchar(32)  |
| email    | varchar(255) |

- It stores users by their id, username, and email.
- We need a row structure to store these information:
```c
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef unsigned __int32 uint32_t;
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;
```

- We already have an `insert` functionality (in `prepare_statement()` function), but it doesn't work as needed. So I'm going to modify it to actually insert the user's information into a Row struct instance:
```c
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(
            input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
            statement->row_to_insert.username, statement->row_to_insert.email;)
        if (args_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        } 
        return PREPARE_SUCCESS;
    }
...
}
```
- `row_to_insert` is actually a Row data structure inside the statement object that stores the values of `id`, `username`, and `email`:
```c
typedef struct {
   StatementType type;
   Row row_to_insert;
} Statement;
```

- Also, I updated the `PrepareResult` enum to include `PREPARE_SYNTAX_ERROR`:
```c
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_COMMAND,
    PREPARE_SYNTAX_ERROR
} PrepareResult;
```

- Now, a single row in the database corresponds to an instance of the `Row` struct (meaning a single row holds `id`, `username`, and `email`).
- I'll be storing rows in "pages" in memory. A "page" here is simply a block of memory. And each page should store as many rows as it can fit. 
- The number of rows a page can store depends on the size of each row. 
- Example: 
    - let's assume a `Row` takes 300 bytes (`4 (id) + 32 (username) + 255 (email) + padding`).
    - A page size is 4 KB (4096 bytes).
    - Then a page can store: 
        4096 / 300 = 13 rows per page
    
    - Once a page is full, a new page is allocated.

- Rows must be serialized into a compact representation, meaning we need to convert the `Row` struct instance into a **linear sequence of bytes** so that it can be efficiently stored in a contiguous memory block (a page).
- Instead of storing rows in memory as individual objects with padding (which wastes space), each row is packed tightly into a page using explicit offsets.

```c
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
```
- This macro calculates the size of a specific attribute inside a struct without requiring an actual instance.
- Breakdown:
    - **(Struct*)0**: 
        - This creates a null pointer to Struct.
        - We don’t allocate memory for an actual struct instance, we just pretend it exists at memory address 0.

    - **((Struct*)0)->Attribute**:
        - This accesses the `Attribute` as if `Struct` was real.
        - No actual memory access happens because `sizeof` only needs to know how much space the attribute would take, not its actual value.
    
    - **sizeof(((Struct*)0)->Attribute)**:
        - This calculates the size of the attribute just like `sizeof(Attribute)` would, but without needing an actual struct instance.

- So this macro gets the size of a struct’s attribute without creating an instance by pretending the struct exists at memory address 0. It's a memory-efficient and safe way to determine field sizes.

```c
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;

const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
```

- `ID_SIZE`, `USERNAME_SIZE`, and `EMAIL_SIZE` store the size of `id`, `username`, and `email` respectively. 
- Offsets, on the other hand, determine where each field starts in memory (packing). 

| Field    | Offset | Size |
|----------|--------|------|
| id       | 0      | 4    |
| username | 4      | 32   |
| email    | 36     | 255  |

- And finally, `Row_Size` stores the total size of a single row.
- This method eliminates padding and fragmentation, ensuring that each row is stored sequentially inside a page. If a page is 4 KB (4096 bytes), it can hold 14 rows (dividing 4096 over `Row_Size` which is 291). 

- I faced an issue regarding size addition:
```c
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
```
- After looking up the problem, I found that the error occurred because `ID_SIZE`, `USERNAME_SIZE`, and `EMAIL_SIZE` are defined using `size_of_attribute`, which relies on `sizeof(((Struct*)0)->Attribute)` and some compilers may not treat `size_of_attribute(Row, id)` as a constant expression when used in a `const` uint32_t declaration.
- So to fix this, I changed the code to:
```c
#define ID_SIZE (size_of_attribute(Row, id))
#define USERNAME_SIZE (size_of_attribute(Row, username))
#define EMAIL_SIZE (size_of_attribute(Row, email))

#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)

#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)
```
- This will probably work as intended. No way to confirm since I haven't completed the functionality yet.

- Next, we should have a function that serializes and deserializes the rows. For that, I'm using `memcpy()` function, which takes in a destination pointer, and a source pointer, in addition to the number of bytes to copy. 
- So, the function that serializes the row is built like this:
```c
void serialize_row(Row* source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}
```
- `destination + ID_OFFSET` moves the pointer to the correct location in the compact buffer. 

- The function that deserializes the row:
```c
void deserialize(void* source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}
```
- Just like before, `source + ID_OFFSET` moves the pointer to the correct location in the compact buffer.

- Offsets are needed because `source` is a _pointer_ to the start of the _entire row in raw memory_. Each field (id, username, email) was stored at a _specific position_ inside this block. When deserializing, we need to retrieve each field from the _same positions_, which requires adding offsets.

- Next, we need a table structure because we're moving beyond just storing a single row. 
- This table will contain:
    - An array of pointers to pages (each page can hold multiple rows).
    - The number of rows inserted. 

```c
const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;
``` 

- Why did we use `void*` pointers? 
    - Each entry in `pages` points to a block of memory (a page) that we allocate dynamically.
    - Each page can hold multiple rows.

- Next, we need a function that tells us where exactly in memory should we insert the row. By taking into account the row number (or the index of the row in the table) and the number of rows per page, we can calculate which page inside the table and at what position within it should this row be inserted. 
```c
void* row_slot(Table* table, uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];
    if (page == NULL) {
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}
```
- `page_num` determines what page in the table we should insert the row into.
- Then, we check if the page exists before we write into it.
- We allocate memory for the page if it's not already allocated.
- `row_offset` gives us the row's position inside the page in row units.
- `byte_offset` gives us the row's position inside the page in bytes. 

- Next thing, I'm going to change the `execute_statement()` to read/write from our table structure, by writing a function for both the insertion and the selection.
```c
typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteResult;
...
ExecuteResult execute_insert(Statement* statement, Table* table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }
    Row* row = &(statement->row_to_insert);
    serialize_row(row, row_slot(table, table->num_rows));
    table->num_rows += 1;
    return EXECUTE_SUCCESS;
}
```
- `serialize_row()` takes a `Row*` (structured data) and converts it into a raw byte format. Then, it stores that raw byte data at the correct memory location computed by `row_slot()`.

```c
ExecuteResult execute_select(Statement* statement, Table* table) {
    Row row; 
    for (uint32_t i = 0; i < table->num_rows; i++) {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}
```
- `print_row()` is a simple function:
```c
void print_row(Row* row) {
    printf("(%d %s %s)\n", row->id, row->username, row->email);
}
```
- I changed `execute_command()` function to work with the new functions:
```c
void execute_command(Statement* statement, Table* table) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return execute_insert(statement, table);
        case (STATEMENT_SELECT):
            return execute_select(statement, table);
    }
} 
```

- Next, we need to build a function that initializes and frees a table:
```c
Table* new_table() {
    Table* table = (Table*)malloc(sizeof(Table));
    table->num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = NULL;
    }
    return table;
}
```
```c
void free_table(Table* table) {
    for (int i = 0; table->pages[i]; i++) {
        free(table->pages[i]);
    }
    free(table);
}
```

- Now, our program enables us to store and retrieve data in a database.

- In the `Row` struct definition, we allocated 32 bytes for username and 255 bytes for email, but C strings are supposed to end with a null character "`\0`", so I changed the definition to include it:
```c
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];  
    char email[COLUMN_EMAIL_SIZE + 1];    
} Row;
```

- We also have another problem related to user input, we used `sscanf()` to read inputs, but this function doesn't care about the buffer's length, meaning users can enter strings larger than 32 bytes or 255 bytes, the additional bytes will cause a buffer overflow, and it'll start writing into unexpected places in memory. 
- To solve this problem, we can create a function `prepare_insert()` that:
    - Splits the input into tokens using `strtok()` function.
    - Checks every token in terms of size and availability (is a parameter(input) missing?).
    - It also checks whether the id is a positive integer.
    - Safely copies the inputs into `statement->row_to_insert` using `strcpy()` function.

```c
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
    statement->type = STATEMENT_INSERT;

    char* keyword = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL) {
        return PREPARE_SYNTAX_ERROR;
    }

    int id = atoi(id_string);
    if (id < 0) {
        return PREPARE_NEGATIVE_ID;
    }

    if (strlen(username) > COLUMN_USERNAME_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }
    if (strlen(email) > COLUMN_EMAIL_SIZE) {
        return PREPARE_STRING_TOO_LONG;    
    }
    statement->row_to_insert.id = id; 
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARE_SUCCESS;
}
```
- I also modified `prepare_statement()` accordingly:
```c
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        return prepare_insert(input_buffer, statement);
    }
    ...
}
```



## 📚 References  
- ["Build Your Own X"](https://github.com/danistefanovic/build-your-own-x)
- [Tutorial](https://github.com/cstack/db_tutorial) 
- [SQLite Internals](https://www.sqlite.org/index.html)
- [Understand how B-Trees work](https://www.youtube.com/watch?v=K1a2Bk8NrYQ)

