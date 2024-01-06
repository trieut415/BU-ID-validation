#include "IDvalidation.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set> 
#include <unordered_map> 
using namespace std;

int idCheck() {
    ifstream inputFile("BigData.txt");  // Read from the text file
    if (!inputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return 1;
    }

    char ch, nextCh;
    int runSum;
    int totalCount = 0;
    bool IDmatch;                                                               // set to true in the case that it's exactly 8 digits

    while (inputFile.get(ch)) {                                                 // go character by character
        IDmatch = false;
        if (ch == 'U') {                                                        // begin loop in the case that U is found
            runSum = 0;                                                         // reset value of runSum
            for (int i = 1; i <= 8; i++) {
                if (!inputFile.get(nextCh)) {
                    break;                                                      // break if end of file is reached
                }
                if (isdigit(nextCh)) {
                    runSum += nextCh - '0';                                      // convert ASCII value of the digit to int
                } else {
                    runSum = 0;                                                 // reset runSum if a non-digit is encountered
                    break;                                                      // break if a non-digit is encountered
                }
                if (i == 8) {                                                   // detected exactly 8 numbers
                    IDmatch = true;
                }
            }
                                                                                // Check if the next character is a non-digit
            if (!isdigit(inputFile.peek()) && IDmatch) {
                totalCount += 1;                                                 // Increment totalCount only if the next character is a non-digit
            }
        }
    }
    inputFile.close();
    return totalCount;
}
//**************//

//using trie as primary data structure to store the dictionary values, and search through a trie to string match the words

class TrieNode {
    public:
        unordered_map<char, shared_ptr<TrieNode>> children;
        bool fullWord;
        TrieNode();
};

TrieNode::TrieNode() {
    fullWord = false;
}

class Trie {
    private: 
        shared_ptr<TrieNode> root; 
    public:
        Trie();
        shared_ptr<TrieNode> getRoot();
        bool search(const string& inWord);       
        void insert(const string& inWord);
};

Trie::Trie() {
    root = make_shared<TrieNode>();
}

void Trie::insert(const string& inWord) { //insert to the trie in the case that the element isn't already in the trie
    shared_ptr<TrieNode> node = root;
    for (char character : inWord) {
        if (node->children.find(character) == node->children.end()) {
            node->children[character] = make_shared<TrieNode>();
        }
        node = node->children[character];
    }
    node->fullWord = true;
}

bool Trie::search(const string& inWord) {
    shared_ptr<TrieNode> node = root;
    for (char character : inWord) {
        if (node->children.find(character) == node->children.end()) {
            return false;
        }
        node = node->children[character];
    }
    return ((node != nullptr) && (node->fullWord));
}

shared_ptr<TrieNode> Trie::getRoot() {
    return root;
}
