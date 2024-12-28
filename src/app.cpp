#include "app.hpp"

Data::Data() : path("../res/test.txt") {
    ifstream input(this->path);
    string line;
    while (getline(input, line)) {
        for (char c : line) {
            times[static_cast<unsigned char>(c)]++;  // 统计字符频率
        }
    }
    input.close();
}

// 构建哈夫曼树
Node* Data::buildHuffmanTree() {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // 将每个字符及其频率作为叶子节点插入堆中
    for (int i = 0; i < 128; ++i) {
        if (times[i] > 0) {  // 只处理出现过的字符
            minHeap.push(new Node(i, times[i]));
        }
    }

    // 合并节点直到只剩下一个节点
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // 创建新节点，频率是两个子节点频率之和
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // 将新节点插回堆中
        minHeap.push(newNode);
    }

    // 返回最终的哈夫曼树根节点
    return minHeap.top();
}

// 生成哈夫曼编码
void Data::generateHuffmanCodes(Node* root, const string& currentCode, unordered_map<unsigned char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {  // 叶子节点
        huffmanCodes[root->ch] = currentCode;
    }

    // 递归左子树
    generateHuffmanCodes(root->left, currentCode + "0", huffmanCodes);

    // 递归右子树
    generateHuffmanCodes(root->right, currentCode + "1", huffmanCodes);
}

// 打印哈夫曼编码
void Data::printHuffmanCodes(const unordered_map<unsigned char, string>& huffmanCodes) {
    cout << "Huffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// 构建并打印哈夫曼树的编码
void Data::buildAndPrintHuffmanTree() {
    Node* root = buildHuffmanTree();
    unordered_map<unsigned char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);
    printHuffmanCodes(huffmanCodes);

    // 加密并写入文件
    string encryptedFilePath = "../res/encrypted_test.enc"; // 设置加密后的文件路径
    encryptAndWriteToFile(encryptedFilePath, huffmanCodes);

    // 保存哈夫曼编码规则
    string codeFilePath = "../res/huffman_codes.txt"; // 哈夫曼编码规则文件路径
    saveHuffmanCodesToFile(codeFilePath, huffmanCodes);
}

// 加密文本并写入文件
void Data::encryptAndWriteToFile(const string& outputPath, const unordered_map<unsigned char, string>& huffmanCodes) {
    ifstream input("../res/test.txt");
    if (!input) {
        cerr << "Error: Could not open the input file!" << endl;
        return;
    }

    ofstream output(outputPath);
    if (!output) {
        cerr << "Error: Could not open the output file!" << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        for (char c : line) {
            // 检查当前字符是否有对应的哈夫曼编码
            if (huffmanCodes.find(static_cast<unsigned char>(c)) != huffmanCodes.end()) {
                string code = huffmanCodes.at(static_cast<unsigned char>(c));
                output << code;  // 将编码写入文件
            } else {
                cerr << "Error: No Huffman code found for character '" << int(static_cast<unsigned char>(c)) << "'!" << endl;
            }
        }
        output << endl;
    }

    input.close();
    output.close();
}

// 将哈夫曼编码规则保存到文件
void Data::saveHuffmanCodesToFile(const string& codeFilePath, const unordered_map<unsigned char, string>& huffmanCodes) {
    ofstream codeFile(codeFilePath);
    for (const auto& pair : huffmanCodes) {
        // 保存每个字符的哈夫曼编码规则
        codeFile << pair.first << ": " << pair.second << endl;
    }
    codeFile.close();
}

void Data::loadHuffmanCodes(const string& codeFilePath) {
    ifstream codeFile(codeFilePath);
    if (!codeFile) {
        cerr << "Error: Could not open Huffman code file!" << endl;
        return;
    }

    string line;
    while (getline(codeFile, line)) {
        string code;
        unsigned char ch;
        size_t delimiterPos = line.find(":");

        if (delimiterPos != string::npos) {
            // 取出字符部分，并将其直接转换为 unsigned char 类型
            string charStr = line.substr(0, delimiterPos);
            if (charStr.size() == 1) {
                ch = static_cast<unsigned char>(charStr[0]);  // 直接用字符转换为 unsigned char
            } else {
                cerr << "Error: Invalid character format in Huffman code file!" << endl;
                continue;
            }

            // 获取编码部分，去除多余空白
            code = line.substr(delimiterPos + 1);
            reverseHuffmanCodes[code] = ch;  // 将编码和字符存入反向哈夫曼映射
        }
    }

    codeFile.close();
}

void Data::decodeAndWriteToFile(const string& encryptedFilePath, const string& outputFilePath) {
    ifstream input(encryptedFilePath, ios::binary);
    if (!input) {
        cerr << "Error: Could not open encrypted file!" << endl;
        return;
    }

    ofstream output(outputFilePath);
    if (!output) {
        cerr << "Error: Could not open output file!" << endl;
        return;
    }

    string encodedData = "";
    char byte;
    while (input.get(byte)) {
        // 将每个字节转换为二进制字符串
        bitset<8> bits(byte);
        encodedData += bits.to_string();  // 将二进制位追加到总数据串中
    }

    string currentCode = "";
    for (char bit : encodedData) {
        currentCode += bit;  // 将每个位追加到当前编码中
        if (reverseHuffmanCodes.find(currentCode) != reverseHuffmanCodes.end()) {
            unsigned char decodedChar = reverseHuffmanCodes[currentCode];
            output.put(decodedChar);  // 将解码后的字符写入输出文件
            currentCode = "";  // 重置当前编码，开始匹配下一个字符
        }
    }

    input.close();
    output.close();
}


