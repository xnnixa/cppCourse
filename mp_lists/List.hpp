/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() : head_(nullptr), tail_(nullptr), length_(0) {}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  // @TODO: graded in MP3.1
  if (tail_ != nullptr)
  {
    return List<T>::ListIterator(tail_->next);
  }
  else
  {
    return nullptr;
  }
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  /// @todo Graded in MP3.1
  ListNode *temp;
  ListNode *current = head_;

  if (head_ == nullptr || tail_ == nullptr)
  {
    return;
  }

  while (current != nullptr)
  {
    temp = current->next;
    delete current;
    current = temp;
  }

  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  newNode->next = head_;
  newNode->prev = nullptr;

  if (head_ != nullptr)
  {
    head_->prev = newNode;
  }

  if (tail_ == nullptr)
  {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  newNode->next = nullptr;
  newNode->prev = tail_;

  if (tail_ == nullptr)
  {
    head_ = newNode;
  }
  else
  {
    tail_->next = newNode;
  }

  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{
  /// @todo Graded in MP3.1
  ListNode *curr = start;

  if (curr == nullptr)
  {
    return nullptr;
  }

  for (int i = 0; i < splitPoint && curr != nullptr; i++)
  {
    curr = curr->next;
  }

  if (curr->prev != nullptr)
  {
    curr->prev->next = nullptr;
    curr->prev = nullptr;
  }

  return curr;
}

/**
 * Modifies List using the rules for a TripleRotate.
 *
 * This function will to a wrapped rotation to the left on every three
 * elements in the list starting for the first three elements. If the
 * end of the list has a set of 1 or 2 elements, no rotation all be done
 * on the last 1 or 2 elements.
 *
 * You may NOT allocate ANY new ListNodes!
 */
template <typename T>
void List<T>::tripleRotate()
{
  // @todo Graded in MP3.1
    if (length_ < 3) return;

    ListNode* current = head_;
    ListNode* newHead = nullptr;
    ListNode* lastOfPrevTrio = nullptr;
    ListNode* lastNodesStart = nullptr;

    while (current && current->next && current->next->next) {
        ListNode* first = current;
        ListNode* second = current->next;
        ListNode* third = current->next->next;
        current = third->next;
        second->next = third;
        third->next = first;
        if (!newHead) {
            newHead = second;
        }
        if (lastOfPrevTrio) {
            lastOfPrevTrio->next = second;
        }
        lastOfPrevTrio = first;
    }

    if (current) {
        lastNodesStart = current;
    }

    if (lastNodesStart) {
        lastOfPrevTrio->next = lastNodesStart;
        while (lastNodesStart->next) {
            lastNodesStart = lastNodesStart->next;
        }
        tail_ = lastNodesStart;
    } else {
        lastOfPrevTrio->next = nullptr;
        tail_ = lastOfPrevTrio;
    }

    head_ = newHead;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  /// @todo Graded in MP3.2
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != nullptr)
  {
    while (tail_->next != nullptr)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2
  return nullptr;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  /// @todo Graded in MP3.2
  return nullptr;
}
