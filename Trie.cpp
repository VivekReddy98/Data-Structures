/*
  Author : Vivek Reddy
  Date   : May'20
  DS     : Trie Data Structure, Using Smart Pointers
  Methods: Insert, Search, Delete
*/

#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

class TrieNode
{
  public:
    char val;
    bool isWord;
    std::unordered_map<char, shared_ptr<TrieNode>> childMap;

    TrieNode(const char c, const bool isW) {
      cout << "Node Created: " << this->val << endl;
      val = c;
      isWord = isW;
    }

    ~TrieNode(){
      cout << "Node Deleted: " << this->val << endl;
    }

    TrieNode(TrieNode* temp) {
      cout << "Node Copied: " << temp->val << endl;
      this->val = temp->val;
      this->isWord = temp->isWord;
      this->childMap =temp->childMap;
    }

    TrieNode(const TrieNode &temp){
       cout<<"Copy constructor called "<<endl;
       cout << "Node Copied: " << temp.val << endl;
       this->val = temp.val;
       this->isWord = temp.isWord;
       this->childMap =temp.childMap;
    }

    TrieNode& operator = (const TrieNode &temp){
        cout<<"Assignment operator called "<<endl;
        this->val = temp.val;
        this->isWord = temp.isWord;
        this->childMap =temp.childMap;
        return *this;
    }

    shared_ptr<TrieNode> search(char c){
      cout << "Node Searched in " << this->val << " which is: " << c << endl;
      if (childMap.find(c) == childMap.end()) return shared_ptr<TrieNode>(nullptr);
      else{
        auto it = childMap.find(c);
        return it->second;
      }
    }

    void add(char c, bool isWord){
       cout << "Node Inserted in " << this->val << " which is: " << c << endl;
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
      else{
        return false;
      }
    }

    bool canDelete(){
      return childMap.empty();
    }
};

class Trie{
    shared_ptr<TrieNode> root;

public:
    Trie(): root(new TrieNode(' ', false)) {}

    void insert(const string& word){
        shared_ptr<TrieNode> temp = root;
        shared_ptr<TrieNode> temploop;
        char c;

        for(int i = 0; i < word.length(); i++){
           c = word.at(i);
           temploop = temp->search(c);
           if (temploop) {
              temp = temploop;
           }
           else{
             if (i == word.length()-1){
               temp->add(c, true);
             }
             else{
               temp->add(c, false);
             }
             temp = temp->search(c);
           }
        }
    }

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
      return true;
    }


    void erase(const string& word){
      shared_ptr<TrieNode> temp = root;
      shared_ptr<TrieNode> temploop;
      char c;
      int i;
      for(i = 0; i < word.length(); i++){
         c = word.at(i);
         temploop = temp->search(c);
         if (!temploop){
           if (temploop->canDelete()) {
               temp->erase(word.at(--i));
               break;
           }
           temp = temploop;
         }
         else{
           cout << "Word Doesn't Exist in the Trie" << endl;
           return ;
         }
      }

    if (i == word.length()) temp->isWord = false;
   }
};



int main()
{
    // TrieNode TN('v', false);

    Trie* ptrTrie = new Trie();

    cout << ptrTrie->search("vivek") << endl;

    // ptrTrie->erase("vivek");

    ptrTrie->insert("vivek");

    cout << ptrTrie->search("vivek") << endl;
    cout << ptrTrie->search("reddy") << endl;
    //
    // ptrTrie->erase("vivek");

    cout << "Test 1 Completed : " << endl;
    ptrTrie->insert("viv");
    ptrTrie->insert("vi");
    // ptrTrie->insert("vivek");

    cout << ptrTrie->search("vivek") << endl;
    cout << ptrTrie->search("vi") << endl;
    cout << ptrTrie->search("vivek") << endl;

    // ptrTrie->erase("vi");
    // cout << ptrTrie->search("vivek") << endl;

    delete ptrTrie;
}
