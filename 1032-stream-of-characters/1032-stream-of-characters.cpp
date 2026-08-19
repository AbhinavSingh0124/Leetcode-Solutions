#include <vector>
#include <string>

struct TrieNode {
    TrieNode* children[26] = {nullptr};
    bool isWord = false;
};

class StreamChecker {
private:
    TrieNode* root;
    std::string history;
    int maxWordLen = 0;

    void insertReversed(const std::string& word) {
        TrieNode* curr = root;
        for (int i = word.length() - 1; i >= 0; --i) {
            int idx = word[i] - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
        }
        curr->isWord = true;
    }

public:
    StreamChecker(std::vector<std::string>& words) {
        root = new TrieNode();
        for (const std::string& word : words) {
            insertReversed(word);
            maxWordLen = std::max(maxWordLen, (int)word.length());
        }
    }
    
    bool query(char letter) {
        history.push_back(letter);
        
        TrieNode* curr = root;
        int len = history.length();
        int limit = std::max(0, len - maxWordLen);
        
        // Traverse backwards from the latest character
        for (int i = len - 1; i >= limit; --i) {
            int idx = history[i] - 'a';
            if (!curr->children[idx]) {
                return false;
            }
            curr = curr->children[idx];
            if (curr->isWord) {
                return true;
            }
        }
        
        return false;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */