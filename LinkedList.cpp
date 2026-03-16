// traversal
int findLength(ListNode* head) {
    int length = 0;
    ListNode* current = head;
    while (current != nullptr) {
        length += 1;
        current = current->next;
    }
    return length;
}

// deleting target
ListNode* deleteNode(ListNode* head, int target) {
    if (head->val == target) {
        return head->next;
    }
    
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        if (curr->val == target) {
            prev->next = curr->next;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    return head;
}

// fast and slow pointer 
// can be used to detect the cycle -> both fast and slow will eventually point to the same node
// median problems --> it will point to median node if no of nodes are odd and 2nd medial node if they are even
ListNode* fastAndSlow(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// reverse the linked list
// test for palindrome (go to middle using slow and fast pointer, then reverse the LL uisng slow ponter and then compare)
ListNode* reverse(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
