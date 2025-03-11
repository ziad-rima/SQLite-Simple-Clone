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
    - [SOURCE](https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-getline-read-entire-line-from-stream)
    - Meaning I should replace the newline character with the terminating null byte to have a clean string (input).

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

- Next, I need to handle SQL commands, or statements. By converting the command into the internal representaton of a statement. Using an `enum` to achieve that. Since `enum` gives us constant values, I can make use of that.
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

## 📚 References  
- ["Build Your Own X"](https://github.com/danistefanovic/build-your-own-x) 
- [SQLite Internals](https://www.sqlite.org/index.html)
- [Understand how B-Trees work](https://www.youtube.com/watch?v=K1a2Bk8NrYQ)

