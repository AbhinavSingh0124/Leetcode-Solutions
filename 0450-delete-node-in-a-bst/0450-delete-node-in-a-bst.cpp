class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        // 1. Search for the node to delete
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // 2. Found the node! Handle deletion cases:

            // Case 1 & 2: No left child or no right child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            // Case 3: Node has two children
            // Find the minimum node in the right subtree (inorder successor)
            TreeNode* minNode = findMin(root->right);
            root->val = minNode->val; // Copy value
            
            // Delete the successor node from the right subtree
            root->right = deleteNode(root->right, minNode->val);
        }

        return root;
    }

private:
    TreeNode* findMin(TreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
};