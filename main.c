#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// https://cstack.github.io/db_tutorial/parts/part1.html

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

typedef struct
{
    char *data;
    int inputLength;
    int dataLength;
} InpBuf;

void execute_statment(Statement *statement)
{
    switch (statement->type)
    {
    case STATEMENT_SELECT:
        printf("SELECT STATEMENT");
        break;

    case STATEMENT_INSERT:
        printf("INSERT STATEMENT");
        break;
    }
}

MetaCommandResult do_meta_command(InpBuf *input_buffer)
{
    if (strcmp(input_buffer->data, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepStat(InpBuf *buffer, Statement *statment)
{
    if (strncmp(buffer->data, "INSERT", 6) == 0)
    {
        return PREPARE_SUCCESS;
    }
}

InpBuf *newBuffer(int length)
{
    if (length > 0)
    {
        InpBuf *buffer = (InpBuf *)malloc(sizeof(InpBuf));
        buffer->inputLength = 0;
        buffer->dataLength = length;
        buffer->data = (char *)malloc(length * sizeof(char));

        return buffer;
    }
    else
    {
        printf("buffer must be > 0\n");
    }
}

void readInput(InpBuf *buffer)
{
    ssize_t read = getline(&(buffer->data), &(buffer->dataLength), stdin);

    if (read <= 0)
    {
        printf("Error reading input\n");
    }

    buffer->inputLength = read - 1;
    buffer->data[read - 1] = 0;
}

void prompt()
{
    printf("Enter a command:\n1. E - Exit Program\n");
}

int main()
{
    InpBuf *inputBuffer = newBuffer(5);
    while (1)
    {
        prompt();
        readInput(inputBuffer);
        if (strcmp(inputBuffer->data[0], ".") == 0)
        {
            switch (do_meta_command(inputBuffer)) // case: META_COMMAND_SUCCESS
            {
            case META_COMMAND_UNRECOGNIZED_COMMAND:
                printf("unrecognized command");
                break;
            }
        }

        Statement statment;
        switch (prepStat(inputBuffer, &statment))
        {
        case PREPARE_SUCCESS:
            execute_statment(&statment);
            break;
        }
    }
    free(inputBuffer->data);
    free(inputBuffer);
}
