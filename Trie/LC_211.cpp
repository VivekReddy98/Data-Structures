/*
Problem: https://leetcode.com/problems/add-and-search-word-data-structure-design/
*/

#include <iostream>
#include <unordered_map>
#include <memory>
#include <stack>

using namespace std;

#define WILDCARD '.'

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
    bool regexsearch(const string& word, int index, shared_ptr<TrieNode> node){
        shared_ptr<TrieNode> temploop;
        shared_ptr<TrieNode> temp = node->search(word.at(index));

        if(index==word.length()-1 && temp){
           if (temp->isWord) return true;
           else return false;
        }
        else if (index==word.length()-1 && !temp){

           if (word.at(index) != WILDCARD) return false;

           for(auto it = node->childMap.begin(); it != node->childMap.end(); it++){
             temploop = it->second;
             if (temploop->isWord){
               return true;
             }
           }
           return false;
        }


        if (word.at(index) != WILDCARD && !temp){
           return false;
        }
        else if (temp){
           return regexsearch(word, ++index, temp);
        }
        else{
           if (node->childMap.empty()) return false;
           for(auto it = node->childMap.begin(); it != node->childMap.end(); it++){
              temploop = it->second;
              if (regexsearch(word, index+1, temploop)){
                return true;
              }
           }
           return false;
        }
      }
};

class WordDictionary {

    Trie* help;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        help = new Trie();
    }

    ~WordDictionary() {
        delete help;
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
       help.insert(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
       return help->regexsearch(word, 0, help->root);
    }
};
