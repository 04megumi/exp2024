#include "cal.hpp"

// 构造函数：通过字符串数据初始化数字链表
Int::Int(string data) {
    len = data.size();
    root = nullptr;
    for (char c : data) {
        Node* newNode = new Node();
        newNode->n = c;
        newNode->next = root;
        root = newNode;
    }
}

// 构造函数：用于加、减、乘、除运算
Int::Int(Node* node) {
    root = node;
    len = 0;
    Node* temp = node;
    while (temp != nullptr) {
        len++;
        temp = temp->next;
    }
}

// 打印数字
void Int::print() {
    Node* temp = root;
    while (temp != nullptr) {
        cout << temp->n;
        temp = temp->next;
    }
    cout << endl;
}

// 翻转链表
Node* Int::reverse(Node* node) {
    Node* prev = nullptr;
    Node* curr = node;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// 加法操作
Int Int::operator+(const Int& other) {
    Node* n1 = reverse(root);
    Node* n2 = reverse(other.root);

    Node* result = nullptr;
    Node* tail = nullptr;
    int carry = 0;

    while (n1 != nullptr || n2 != nullptr || carry != 0) {
        int sum = carry;
        if (n1 != nullptr) {
            sum += n1->n - '0';
            n1 = n1->next;
        }
        if (n2 != nullptr) {
            sum += n2->n - '0';
            n2 = n2->next;
        }

        carry = sum / 10;
        Node* newNode = new Node();
        newNode->n = (sum % 10) + '0';

        if (result == nullptr) {
            result = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    return Int(result);
}

// 减法操作
Int Int::operator-(const Int& other) {
    Node* n1 = reverse(root);
    Node* n2 = reverse(other.root);

    Node* result = nullptr;
    Node* tail = nullptr;
    int borrow = 0;

    while (n1 != nullptr || n2 != nullptr) {
        int diff = borrow;
        if (n1 != nullptr) {
            diff += n1->n - '0';
            n1 = n1->next;
        }
        if (n2 != nullptr) {
            diff -= n2->n - '0';
            n2 = n2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        Node* newNode = new Node();
        newNode->n = diff + '0';

        if (result == nullptr) {
            result = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    return Int(result);
}

// 乘法操作
Int Int::operator*(const Int& other) {
    Node* n1 = reverse(root);  // 翻转第一个数字链表
    Node* n2 = reverse(other.root);  // 翻转第二个数字链表

    int len1 = len;  // 第一个数字链表的长度
    int len2 = other.len;  // 第二个数字链表的长度

    int* resultArray = new int[len1 + len2]();  // 创建一个数组存储乘积结果

    Node* result = nullptr;
    Node* tail = nullptr;

    // 遍历两个数字链表，进行乘法操作
    for (int i = 0; i < len1; ++i) {
        Node* n2Copy = n2;  // 保留n2的副本，避免修改原始n2
        for (int j = 0; j < len2; ++j) {
            resultArray[i + j] += (n1->n - '0') * (n2Copy->n - '0');  // 乘法并累加到结果数组
            resultArray[i + j + 1] += resultArray[i + j] / 10;  // 处理进位
            resultArray[i + j] %= 10;  // 保持每位的结果小于10

            n2Copy = n2Copy->next;  // 移动到n2的下一个节点
        }
        n1 = n1->next;  // 移动到n1的下一个节点
    }

    // 将结果数组转换为链表
    for (int i = 0; i < len1 + len2; ++i) {
        if (resultArray[i] == 0 && result == nullptr) continue;  // 跳过前导零

        Node* newNode = new Node();
        newNode->n = resultArray[i] + '0';  // 将数字转换为字符

        if (result == nullptr) {
            result = newNode;  // 初始化链表头
        } else {
            tail->next = newNode;  // 连接新节点
        }
        tail = newNode;  // 更新尾指针
    }

    delete[] resultArray;  // 释放结果数组的内存

    return Int(result);  // 返回计算结果
}

// 除法操作
Int Int::operator/(const Int& other) {
    Node* n1 = reverse(root);  // 被除数（翻转链表）
    Node* n2 = reverse(other.root);  // 除数（翻转链表）

    // 如果除数为0，抛出除以零的异常
    if (n2 == nullptr || (n2->n == '0' && n2->next == nullptr)) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    Node* quotient = nullptr;  // 商的链表
    Node* remainder = nullptr;  // 余数的链表
    Node* tail = nullptr;  // 商链表的尾部指针

    // 遍历被除数的每个节点
    while (n1 != nullptr) {
        // 将余数和当前节点拼接
        Node* newNode = new Node();
        newNode->n = n1->n;  // 把当前位加入余数
        newNode->next = remainder;
        remainder = newNode;

        // 如果余数大于除数，则进行除法运算
        int q = 0;
        while (compare(remainder, n2) >= 0) {  // 余数大于等于除数时
            remainder = subtract(remainder, n2);  // 余数减去除数
            q++;  // 商增加
        }

        // 将商结果加入商链表
        if (q != 0 || quotient != nullptr) {  // 处理前导零
            Node* quotientNode = new Node();
            quotientNode->n = q + '0';  // 商的当前位
            if (quotient == nullptr) {
                quotient = quotientNode;
            } else {
                tail->next = quotientNode;
            }
            tail = quotientNode;
        }

        // 处理下一个节点
        n1 = n1->next;
    }

    // 返回商的链表
    return Int(quotient);  // 返回商的Int对象
}

// 比较两个链表（数字大小）
int Int::compare(Node* n1, Node* n2) {
    int len1 = 0, len2 = 0;
    Node* temp1 = n1;
    Node* temp2 = n2;
    
    // 计算两个链表的长度
    while (temp1 != nullptr) {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2 != nullptr) {
        len2++;
        temp2 = temp2->next;
    }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    // 如果长度相等，逐位比较
    while (n1 != nullptr) {
        if (n1->n > n2->n) return 1;
        if (n1->n < n2->n) return -1;
        n1 = n1->next;
        n2 = n2->next;
    }
    return 0;
}

// 从链表中减去另一个链表（模拟减法）
Node* Int::subtract(Node* n1, Node* n2) {
    Node* result = nullptr;
    Node* tail = nullptr;
    int borrow = 0;

    while (n1 != nullptr || n2 != nullptr) {
        int diff = borrow;

        if (n1 != nullptr) {
            diff += n1->n - '0';
            n1 = n1->next;
        }
        if (n2 != nullptr) {
            diff -= n2->n - '0';
            n2 = n2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        Node* newNode = new Node();
        newNode->n = diff + '0';

        if (result == nullptr) {
            result = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    return result;
}


ostream& operator<<(ostream& os, const Int& obj) {
    Node* temp = obj.root;
    while (temp != nullptr) {
        os << temp->n;
        temp = temp->next;
    }
    return os;
}
