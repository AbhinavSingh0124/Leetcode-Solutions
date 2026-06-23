class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        // If the list is empty or has less than 3 nodes, no reordering is needed
        if (!head || !head->next || !head->next->next) {
            return head;
        }
        
        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even; // Save the start of the even list to connect later
        
        while (even && even->next) {
            odd->next = even->next;   // Link the next odd node
            odd = odd->next;          // Move odd pointer forward
            
            even->next = odd->next;   // Link the next even node
            even = even->next;        // Move even pointer forward
        }
        
        odd->next = evenHead;         // Connect the end of odd list to the start of even list
        return head;
    }
};