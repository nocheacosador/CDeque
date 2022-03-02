#include "Deque.h"

#include <assert.h>
#include "MemoryAllocation.h"

void Deque_PushFront(Deque* deque, void* data)
{
    assert(deque != NULL);

    // construct new node
    DequeNode* new = (DequeNode*)Malloc(sizeof(DequeNode));
    if (new == NULL) 
    {
        perror("Error while creating new priority queue node");
        return;
    }

    new->data = data;
    new->next = deque->first;
    new->prev = NULL;

    if (deque->first != NULL) deque->first->prev = new;
    if (deque->last == NULL) deque->last = new;
    deque->first = new;

    deque->size++;
}

void Deque_PushBack(Deque* deque, void* data)
{
    assert(deque != NULL);

    // construct new node
    DequeNode* new = (DequeNode*)Malloc(sizeof(DequeNode));
    if (new == NULL) 
    {
        perror("Error while creating new priority queue node");
        return;
    }

    new->data = data;
    new->next = NULL;
    new->prev = deque->last;

    if (deque->last != NULL) deque->last->next = new;
    if (deque->first == NULL) deque->first = new;
    deque->last = new;

    deque->size++;
}

void* Deque_PopFront(Deque* deque)
{
    assert(deque != NULL);
    
    if (deque->first == NULL)
        return NULL;
    
    void* data = deque->first->data;
    DequeNode* toFree = deque->first;
    deque->first = deque->first->next;
    if (deque->first != NULL) deque->first->prev = NULL;
    Free(toFree);
    deque->size--;
    
    if (deque->size == 0)
        deque->last = NULL;

    return data;
}

void* Deque_PopBack(Deque* deque)
{
    assert(deque != NULL);
    
    if (deque->last == NULL)
        return NULL;

    void* data = deque->last->data;
    DequeNode* toFree = deque->last;
    deque->last = deque->last->prev;
    if (deque->last != NULL) deque->last->next = NULL;
    Free(toFree);
    deque->size--;
    
    if (deque->size == 0)
        deque->first = NULL;

    return data;
}

void* Deque_PeekFront(const Deque* deque)
{
    assert(deque != NULL);
    
    if (deque->first == NULL)
        return NULL;

    return deque->first->data;
}

void* Deque_PeekBack(const Deque* deque)
{
    assert(deque != NULL);
    
    if (deque->last == NULL)
        return NULL;
    
    return deque->last->data;
}

int Deque_IsEmpty(const Deque* deque)
{
    assert(deque != NULL);
    return deque->first == NULL;
}

void Deque_Delete(Deque* deque)
{
    while (!Deque_IsEmpty(deque))
        Free(Deque_PopFront(deque));
}

static char* defaultToString(void* data) 
{
    size_t needed = snprintf(NULL, 0, "adress: 0x%p", data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "adress: 0x%p", data);
    return buffer;
}

void Deque_Print(const Deque* deque, ToStringFunc* toStringFunc, FILE* stream)
{
    assert(deque != NULL);
    if (toStringFunc == NULL) toStringFunc = defaultToString;

    for (DequeNode* node = deque->first; node != NULL; node = node->next)
    {
        char* data = toStringFunc(node->data);
        fprintf(stream, "data: %s\n", data);
        Free(data);
    }

    fprintf(stream, "Size: %d\n", deque->size);
}
