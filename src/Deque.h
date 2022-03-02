#pragma once

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Deque node srtucture
 */
typedef struct DequeNode {
    struct DequeNode* next;
    struct DequeNode* prev;
    void* data;
} DequeNode;

/**
 * @brief Deque srtucture
 */
typedef struct Deque {
    DequeNode* first;
    DequeNode* last;
    int size;
} Deque;

/**
 * @brief Creates empty deque
 * 
 * @return empty deque
 */
static inline Deque Deque_Create()
{
    return (Deque){ NULL, NULL, 0 };
}

/**
 * @brief Pushes data to the front of the deque
 * 
 * @param deque pointer to a deque
 * @param data pointer to data
 */
void Deque_PushFront(Deque* deque, void* data);

/**
 * @brief Pushes data to the back of the deque
 * 
 * @param deque pointer to a deque
 * @param data pointer to data
 */
void Deque_PushBack(Deque* deque, void* data);

/**
 * @brief Returns data from the front of th deque and removes it from deque
 * 
 * @param deque pointer to a deque
 * @return data or NULL if deque is empty
 */
void* Deque_PopFront(Deque* deque);

/**
 * @brief Returns data from the back of th deque and removes it from deque
 * 
 * @param deque pointer to a deque
 * @return data or NULL if deque is empty
 */
void* Deque_PopBack(Deque* deque);

/**
 * @brief Returns data from the front of th deque
 * 
 * @param deque pointer to a deque
 * @return data or NULL if deque is empty
 */
void* Deque_PeekFront(const Deque* deque);

/**
 * @brief Returns data from the back of th deque
 * 
 * @param deque pointer to a deque
 * @return data or NULL if deque is empty
 */
void* Deque_PeekBack(const Deque* deque);

/**
 * @brief Checks if deque is empty
 * 
 * @param deque pointer to a deque
 * @return 1 if empty, 0 if not empty
 */
int Deque_IsEmpty(const Deque* deque);

/**
 * @brief Deletes deque, frees all of the members.
 * 
 * @param deque pointer to deque
 */
void Deque_Delete(Deque* deque);

/**
 * @brief Function type for data conversion to string.
 *        Takes in pointer to data that needs to be printed.
 * 
 * @return heap allocated string
 */
typedef char* ToStringFunc(void*);

/**
 * @brief Prints deque content to stream
 * 
 * @param deque pointer to a deque to be printed
 * @param toStringFunc pointer to a function of type `ToStringFunc`,
 *                     if NULL - default function is used
 * @param stream where to print
 */
void Deque_Print(const Deque* deque, ToStringFunc* toStringFunc, FILE* stream);