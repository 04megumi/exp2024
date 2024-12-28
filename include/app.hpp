#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// 哈夫曼树节点结构
struct Node {
    unsigned char ch; // 字符
    int freq;         // 字符频率
    Node* left;       // 左子树
    Node* right;      // 右子树

    Node(unsigned char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; 
    }
};


class Data {
public:
    int times[128] = {0};  // 存储字符频率

    unordered_map<string, unsigned char> reverseHuffmanCodes;  // 反向哈夫曼编码表

    Data();

    Node* buildHuffmanTree();

    void generateHuffmanCodes(Node* root, const string& currentCode, unordered_map<unsigned char, string>& huffmanCodes);

    void printHuffmanCodes(const unordered_map<unsigned char, string>& huffmanCodes);

    void buildAndPrintHuffmanTree();

    void encryptAndWriteToFile(const string& outputPath, const unordered_map<unsigned char, string>& huffmanCodes);

    void saveHuffmanCodesToFile(const string& codeFilePath, const unordered_map<unsigned char, string>& huffmanCodes);

    void loadHuffmanCodes(const string& codeFilePath);

    void decodeAndWriteToFile(const string& encryptedFilePath, const string& outputFilePath);

private:
    string path;  // 文件路径
};


