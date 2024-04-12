/**
 * @file list.cpp
 * Singly Linked List (lab_gdb).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include "list.h"
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    ListNode *temp = head;
    while (temp != nullptr)
    {
        ListNode *nextNode = temp->next;
        delete temp;
        temp = nullptr;
        temp = nextNode;
    }
    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const &ndata)
{
    ListNode *newNode = new ListNode(ndata);
    newNode->next = head;
    head = newNode;
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T &ndata)
{
    // @todo Graded in lab_gdb
    ListNode *temp = head;

    if (temp == nullptr)
    {
        head = new ListNode(ndata);
        length++;
        return;
    }

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new ListNode(ndata);
    length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    head = reverse(head, NULL, length);
}

/**
 * Helper function to recursively reverse the enitre sequence of
 * linked memory inside a List.
 *
 * @param curr The current node we are reversing
 * @param prev The node that should be placed before the current node in the
 * final reversed list
 * @param len The length of the remaining list to be reversed
 */
template <class T>
typename List<T>::ListNode *List<T>::reverse(ListNode *curr, ListNode *prev, int len)
{
    if (curr == nullptr || len <= 0)
    {
        return prev;  // prev will be the new head of the reversed segment
    }

    ListNode *next = curr->next;  // store next node, as curr next will change
    curr->next = prev;            // reverse the link

    // move to the next node in the original list, update prev to current, decrease length
    return reverse(next, curr, len - 1);
}

/**
 * Shuffles the current list by applying a perfect shuffle once. This entails
 * splitting the list in half, then interleaving the two halves.
 * For example:
 * start : < 1, 2, 3, 4, 5 >
 * split : < 1, 2, 3 >    < 4, 5 >
 * final : < 1, 4, 2, 5, 3 >
 */
template <class T>
void List<T>::shuffle()
{
    // @todo Graded in lab_gdb

    // Find the center, and split the list in half
    // one should point at the start of the first half-list
    // two should point at the start of the second half-list

    //early exit
    if (head == nullptr || head->next == nullptr)
        return;

    //initialize pointers
    ListNode *one = head;
    ListNode *two = head;
    ListNode *prev = nullptr;

    //advance two to the start of the second half and prev to end of the first half
    for (int i = 0; i < length / 2; i++) {
        prev = two;
        two = two->next;
    }

    // split list into two halves
    if (prev) {
        prev->next = nullptr;
    }

    //initialize for interleaving
    ListNode *temp = nullptr;
    ListNode *firstIter = one;
    ListNode *secondIter = two;

    //interleave
    while (firstIter != nullptr && secondIter != nullptr) {
        temp = firstIter->next;
        firstIter->next = secondIter;
        firstIter = temp;

        temp = secondIter->next;
        secondIter->next = firstIter;
        secondIter = temp;
    }
}
