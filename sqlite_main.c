#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommand;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_COMMAND
} PrepareResult;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT
} StatementType;

typedef struct {
    StatementType type; // type ==> {STATEMENT_SELECT || STATEMENT_INSERT}
} Statement;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));

    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

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

void clean_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommand meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_COMMAND;
}

void execute_command(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("This is where insert code goes...\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where select code goes...\n");
            break;
    }
} 

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

