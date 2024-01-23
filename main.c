#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// https://cstack.github.io/db_tutorial/parts/part1.html

typedef struct
{
    char *data;
    int inputLength;
    int dataLength;
} InpBuf;

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
        printf(inputBuffer->data);
        printf("\n");
        if (strcmp(inputBuffer->data, "E") == 0)
        {
            printf("closing....\n");
            break;
        }
        else
        {
            printf("unrecognised command...\n");
        }
    }
    free(inputBuffer->data);
    free(inputBuffer);
}