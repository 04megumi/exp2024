

#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;

struct Node {
    char n;
    Node* next = nullptr;
};

class Int {
private:
    int len;
    Node* root;

public:
    // 构造函数，接受字符串数据初始化
    Int(string data);

    // 构造函数：用于加、减、乘、除运算
    Int(Node* node);

    // 打印数字
    void print();

    // 加法
    Int operator+(const Int& other);

    // 减法
    Int operator-(const Int& other);

    // 乘法
    Int operator*(const Int& other);

    // 除法
    Int operator/(const Int& other);

private:
    // 辅助函数：翻转链表
    Node* reverse(Node* node);

    Node* subtract(Node* n1, Node* n2);

    int compare(Node* n1, Node* n2);

    friend ostream& operator<<(ostream& os, const Int& obj);

};