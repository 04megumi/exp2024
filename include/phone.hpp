#ifndef PHONE_HPP
#define PHONE_HPP

#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>
#include <raylib.h>
using namespace std;

struct info
{
    std::string name;
    std::string number;
    std::string address;
};


enum ScreenState {
    MAIN_MENU,
    NAME_QUERY,
    NUMBER_QUERY,
    NAME_DELETE,
    NAME_INSERT
};

void use();

class TrieNode
{
public:
    unordered_map<char, TriNode*> children;
    bool End;

    TrieNode() : End(false) {};
};

class Trile
{
private:
    TrieNode* root;
public:
    Trile() {root = new TrieNode();}

    void insert (const string& number);

    vector<string> search(const string& number);
};

class App
{
public:
    App(std::string path);
    string getAddress(string name);
    string getNumber(string name);
    bool deleteName(string name);
    bool insert(string name, string number, string address);

    friend void use();

private:
    unordered_map<std::string, info> infos;
};




#endif