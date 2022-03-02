#include <stdio.h>
#include <string.h>
#include "MemoryAllocation.h"
#include "Deque.h"

int* HeapInt(int val)
{
    int* ptr = (int*)Malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

char* IntToString(void* data)
{
    size_t needed = snprintf(NULL, 0, "%d", *(int*)data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "%d", *(int*)data);
    return buffer;
}

int main()
{
    Deque deque = Deque_Create();

    char buf[1024];
    int run = 1;
    while (run)
    {
        printf("> ");
        scanf("%1023s", buf);

        if (!strcmp("push_front", buf))
        {
            int data;
            scanf("%d", &data);

            Deque_PushFront(&deque, HeapInt(data));
        }
        else if (!strcmp("push_back", buf))
        {
            int data;
            scanf("%d", &data);

            Deque_PushBack(&deque, HeapInt(data));
        }
        else if (!strcmp("pop_front", buf))
        {
            int* data = (int*)Deque_PopFront(&deque);

            if (data == NULL) 
                puts("NULL");
            else
            {
                printf("%d\n", *data);
                Free(data);
            }
        }
        else if (!strcmp("pop_back", buf))
        {
            int* data = (int*)Deque_PopBack(&deque);

            if (data == NULL) 
                puts("NULL");
            else
            {
                printf("%d\n", *data);
                Free(data);
            }
        }
        else if (!strcmp("peek_front", buf))
        {
            int* data = (int*)Deque_PeekFront(&deque);

            if (data == NULL) 
                puts("NULL");
            else
                printf("%d\n", *data);
        }
        else if (!strcmp("peek_back", buf))
        {
            int* data = (int*)Deque_PeekBack(&deque);

            if (data == NULL) 
                puts("NULL");
            else
                printf("%d\n", *data);
        }
        else if (!strcmp("is_empty", buf))
        {
            puts( Deque_IsEmpty(&deque) ? "true" : "false" );
        }
        else if (!strcmp("print", buf))
        {
            puts("Deque:");
            Deque_Print(&deque, IntToString, stdout);
        }
        else if (!strcmp("quit", buf))
        {
            puts("Bye.");
            run = 0;
        }
        else
        {
            printf("Unknown command: '%s'\n", buf);
        }
    }

    Deque_Delete(&deque);

    PrintMemoryAllocationReport();
}