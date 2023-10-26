#include <string>
#include <iostream>
using namespace std;

class Trie {
    class TrieNode {
        bool isEntry = false;
        TrieNode* children[26];
        int count = 0;
    public:


        const bool& GetIsEntry() {
            return isEntry;
        }

        bool& SetIsEntry(const bool& e) {
            return isEntry = e;
        }

        int& IncCount() {
            return ++count;
        }

        int& GetCount() {
            return count;
        }

        TrieNode* GetChild(const int &ind) {
            if(ind < 0 || ind > 25) return nullptr;
            return children[ind];
        }

        TrieNode* AddChild(TrieNode* node, const int &ind) {
            if(ind > 25 || ind < 0) return nullptr;
            return children[ind] = node;
        }

        void DeleteChild(const int &ind) {
            children[ind] = nullptr;
        }

        bool InspectChildren() {
            for(int i = 0; i < 26; i++) {
                if(children[i] != nullptr) {
                    return false;
                }
            }
            return true;
        }
    };

    int LetterToIndex(const char& ltr) {
        return static_cast<int>(ltr - 97);
    }

    TrieNode* Search(TrieNode* curr, const string &target, const int &index) {
        if(index == static_cast<int>(target.length())) {
            if(curr->GetIsEntry()) return curr;
            else return nullptr;
        }
        const char nextLtr = target.at(index);
        const int nextInd = LetterToIndex(nextLtr);
        TrieNode* nextChild = curr->GetChild(nextInd);
        if(nextChild != nullptr) return Search(nextChild, target, index + 1);
        return nullptr;
    }

    void Add(TrieNode* curr, const string &val, const int &index) {
        if(index == static_cast<int>(val.length())) {
            curr->SetIsEntry(true);
            curr->IncCount();
            return;
        }
        const char nextLtr = tolower(val.at(index));
        const int nextInd = LetterToIndex(nextLtr);
        TrieNode* nextChild = curr->GetChild(nextInd);
        if(nextChild == nullptr) {
            TrieNode* newChild = curr->AddChild(new TrieNode(), nextInd);
            Add(newChild, val, index + 1);
            return;
        }
        Add(nextChild, val, index + 1);
    }

    bool RemoveNode(TrieNode* curr, const string &target, const int &index) {
        if(index == static_cast<int>(target.length()) && curr->GetIsEntry()) curr->SetIsEntry(false);
        else {
            const char nextLtr = target.at(index);
            const int nextInd = LetterToIndex(nextLtr);
            TrieNode* nextChild = curr->GetChild(nextInd);
            if(nextChild != nullptr && RemoveNode(nextChild, target, index + 1)) {
                curr->DeleteChild(nextInd); 
            }
        }

        if(curr->GetIsEntry()) {
            return false;
        } 

        return curr->InspectChildren();
    }

    TrieNode* Erase(TrieNode* curr) {
        for(int i = 0; i < 26; i++) {
            if(curr->GetChild(i)) {
                Erase(curr->GetChild(i));
            }
        }
        delete curr;
        return nullptr;
    }

    bool SanitizeString(const string &val) {
        for(auto c: val) {
            if(!isalpha(c)) return false;
        }
        return true;
    }

public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        root = Erase(root);
    }

    TrieNode* Find(const string &target) {
        return Search(root, target, 0);
    }

    bool Insert(const string &val) {
        if(SanitizeString(val)) {
            Add(root, val, 0);
            return true;
        }
        return false;
    }

    void Remove(const string &val) {
        RemoveNode(root, val, 0);
    }
};

int main() {
    Trie* words = new Trie();
    bool res = words->Insert("Hello");
    if(res) cout << "hello added" << endl;
    res = words->Insert("ello");
    if(res) cout << "ello added" << endl;
    auto findResult = words->Find("hello");
    if(findResult != nullptr) {
        cout << "hello was found in the Trie!" << endl;
    } else {
        cout << "the Trie is not functioning correctly!" << endl;
    }

    // add non alpha string
    res = words->Insert("hey12");
    if(!res) {
        cout << "tried to enter non alpha word" << endl;
    }

    // remove word
    words->Remove("hello");
    findResult = words->Find("hello");
    if(findResult == nullptr) {
        cout << "hello was removed from the Trie" << endl;
    }
    delete words;
};