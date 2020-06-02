/*
  Author : Vivek Reddy
  Date   : May'20
  DS     : Trie Data Structure, Using Smart Pointers
  Methods: Insert, Search, Erase, startsWith
  Complexity: O(String length) for each
*/

#include <iostream>
#include <unordered_map>
#include <memory>
#include <stack>

using namespace std;

// TrieNode Class, Made with Node Specific Fucntions
class TrieNode{
  public:
    bool isRoot;
    char val;
    bool isWord;

    unordered_map<char, shared_ptr<TrieNode>> childMap;

    TrieNode(): val(' '), isWord(false), isRoot(true)  {}

    TrieNode(const char& c, const bool& isW): val(c), isWord(isW), isRoot(false)  {}

    ~TrieNode() {cout << "Node Deleted: " << this->val << endl;}

    bool canDelete() {return !this->isWord && !this->isRoot && this->childMap.empty();}

    TrieNode(TrieNode* temp) {
      // cout << "Node Copied: " << temp->val << endl;
      this->val = temp->val;
      this->isWord = temp->isWord;
      this->childMap = temp->childMap;
    }

    shared_ptr<TrieNode> search(char c){
      // cout << "Node Searched in " << this->val << " which is: " << c << endl;
      if (childMap.find(c) == childMap.end()) return shared_ptr<TrieNode>(nullptr);
      else{
        auto it = childMap.find(c);
        return it->second;
      }
    }

    void add(char c, bool isWord){
       cout << "Node Inserted in " << this->val << " which is: "<< c << " isWord: " << isWord << endl;
       if (childMap.find(c) == childMap.end())
       {
         auto sptr = std::make_shared<TrieNode>(new TrieNode(c, isWord));
         childMap[c] = sptr;
       }
    }

    bool erase(char c){
      // Delete a Node Deletes all its children. So consult with child nodes before killing them :(
      cout << "Node Erased in " << this->val << " which is: " << c << endl;
      if (childMap.find(c) != childMap.end())
      {
        childMap.erase(c);
        return true;
      }
      else return false;
    }
};

class Trie{

    shared_ptr<TrieNode> root;

public:
    Trie(): root(new TrieNode()) {}

    // Inserts a Word into the Trie
    void insert(const string& word){
        shared_ptr<TrieNode> temp = root;
        shared_ptr<TrieNode> temploop;
        char c;

        for(int i = 0; i < word.length(); i++){
           c = word.at(i);
           temploop = temp->search(c);
           if (temploop) {temp = temploop;}
           else {
             temp->add(c, false);
             temp = temp->search(c);
           }
        }

        temp->isWord = true;
    }

    // Returns True if Present & False if isn't
    bool search(const string& word){
      shared_ptr<TrieNode> temp = root;
      shared_ptr<TrieNode> temploop;
      char c;

      for(int i = 0; i < word.length(); i++){
         c = word.at(i);
         temploop = temp->search(c);
         if (!temploop) {
            return false;
         }
         else{
           temp = temploop;
         }
      }
      return temp->isWord;
    }

    // Removes an element from the Trie.
    void erase(const string& word){
      shared_ptr<TrieNode> temp = root;
      char c;
      int i;

      stack<shared_ptr<TrieNode>> stk;

      stk.push(root);
      for(i = 0; i < word.length(); i++){
         c = word.at(i);
         temp = temp->search(c);
         if (!temp){
           cout << "Word Doesn't Exist in the Trie" << endl;
           return ;
         }
         stk.push(temp);
      }

      stk.top()->isWord = false;
      bool canRemove = stk.top()->canDelete();

      while (canRemove){
         c = stk.top()->val;
         stk.pop();
         stk.top()->erase(c);
         canRemove = stk.top()->canDelete();
      }
   }

   bool startsWith(const string& word){
      shared_ptr<TrieNode> temp = root;
      shared_ptr<TrieNode> temploop;
      char c;

      int i = 0;
      for (i = 0; i < word.length(); i++){
         c = word.at(i);
         temploop = temp->search(c);
         if (!temploop){
            return false;
         }
         temp = temploop;
      }

      return true;
   }

};


int main()
{
    // TrieNode TN('v', false);
    std::unique_ptr<Trie> ptrTrie (new Trie());

    ptrTrie->insert("vivek");
    cout << ptrTrie->search("vivek")  << endl;

    ptrTrie->insert("viv");
    ptrTrie->insert("vi");
    ptrTrie->erase("vivek");

    cout << ptrTrie->search("vi")  << endl;
    cout << ptrTrie->search("viv")  << endl;
    cout << ptrTrie->search("vive")  << endl;
    cout << ptrTrie->search("vivek")  << endl;

    ptrTrie->insert("vile");
    ptrTrie->insert("villify");
    ptrTrie->insert("villa");

    cout << ptrTrie->search("villify")  << endl;

    ptrTrie->erase("villify");

    cout << ptrTrie->search("villify")  << endl;
    cout << ptrTrie->search("villa")  << endl;
    cout << ptrTrie->search("vile")  << endl;

}
