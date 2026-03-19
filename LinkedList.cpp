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

// for debug
void read(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;
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


// Flatten a multi-level Doubly Linked List 
// This question can also be solved using recursion

Node* flatten(Node* head) {
    if (head == NULL) return NULL;
    stack<Node*> s;
    Node* d = new Node(-1);
    d->next = head;
    head->prev = d;
    Node* t = d;
    Node* cur = head;
    while (cur) {
        // creating new node and setting pointers
        Node* newNd = new Node(cur->val);
        d->next = newNd;
        newNd->prev = d;
        d = d->next;

        // we are checking if child is present or not
        if (cur->child) {

            // if the child is present then we go inside of that, and put the next node of the current node in stack when everything in child is processed 
            // then we can reach the next node using stack, if the current node is required to put after processing child node, we would have put cur instead of
            // cur->next to come back
            s.push(cur->next);
            cur = cur->child;
        }

        // if no child then just go to next node
        else cur = cur->next;

        // here we are making sure that cur is never null, if there is unprocessed node is stack and we have explored the current child (it's null) 
        // then we will take element out of stack (we put while loop because it can be NULL too) so we keep going inside branch.
        while (!s.empty() && cur == NULL) {
            cur = s.top();
            s.pop();
        }
    }

    // removing the dummy node
    t->next->prev = NULL;
    return t->next;
}

// intersection of two linked List, we are moving the pointer to the opposite end, once it becomes null to offset the difference in length
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* curA = headA;
    ListNode* curB = headB;
    while (curA != curB) {        
        curA = curA->next;
        curB = curB->next;
        if (curA == curB) return curA;

        // here we are throwing at the oppostie end but we can also
        // go to the same end too, it's just gonna take more traversal
        if (!curA) curA = headB;
        if (!curB) curB = headA;
    }
    return curA;
}
