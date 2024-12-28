#include "maze.hpp"
#include "phone.hpp"
//#include "app.hpp"
//#include "cal.hpp"


/*
int main()
{

    Maze maze;

    while (!WindowShouldClose()) 
    {
        maze.render();
    }

    CloseWindow();

    return 0;
}
*/

/*
int main()
{

    use();

    return 0;
}
*/

/*
int main() {
    Data data;

    // 加载哈夫曼编码规则
    data.loadHuffmanCodes("../res/huffman_codes.txt");

    // 解码加密文件并写入解码后的内容到输出文件
    data.decodeAndWriteToFile("../res/encrypted_test.enc", "../res/decrypted_test.txt");

    cout << "Decryption complete!" << endl;
    return 0;
}
*/

/*
void performCalculation(const std::string& num1, const std::string& num2, char operation, std::string& result) {
    Int a1(num1);
    Int a2(num2);
    Int calcResult("");

    switch (operation) {
        case '+':
            calcResult = a1 + a2;
            break;
        case '-':
            calcResult = a1 - a2;
            break;
        case '*':
            calcResult = a1 * a2;
            break;
        case '/':
            try {
                calcResult = a1 / a2;
            } catch (std::invalid_argument& e) {
                result = "Error: " + std::string(e.what());
                return;
            }
            break;
        default:
            result = "Unsupported operation!";
            return;
    }

    // 将计算结果转换为字符串
    std::ostringstream oss;
    oss << calcResult;
    result = oss.str();  // 将结果转化为字符串并传递
}

// 主函数：图形界面
int main() {
    // 初始化raylib窗口
    const int screenWidth = 400;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Calculator");

    SetTargetFPS(60);  // 设置帧率为60

    // 初始化输入数字
    std::string num1 = "";
    std::string num2 = "";
    char currentOp = ' ';
    std::string result = "";

    // 按钮位置和大小
    Rectangle buttons[16];
    int buttonWidth = 80;
    int buttonHeight = 60;
    for (int i = 0; i < 16; ++i) {
        buttons[i].width = buttonWidth;
        buttons[i].height = buttonHeight;
        buttons[i].x = (i % 4) * buttonWidth + 10;  // 水平位置
        buttons[i].y = (i / 4) * buttonHeight + 180;  // 垂直位置
    }

    const char* buttonLabels[16] = {
        "1", "2", "3", "+",
        "4", "5", "6", "-",
        "7", "8", "9", "*",
        "0", "=", "/", "C"
    };

    while (!WindowShouldClose()) {
        // 处理输入
        if (IsKeyPressed(KEY_ZERO)) num1 += "0";
        if (IsKeyPressed(KEY_ONE)) num1 += "1";
        if (IsKeyPressed(KEY_TWO)) num1 += "2";
        if (IsKeyPressed(KEY_THREE)) num1 += "3";
        if (IsKeyPressed(KEY_FOUR)) num1 += "4";
        if (IsKeyPressed(KEY_FIVE)) num1 += "5";
        if (IsKeyPressed(KEY_SIX)) num1 += "6";
        if (IsKeyPressed(KEY_SEVEN)) num1 += "7";
        if (IsKeyPressed(KEY_EIGHT)) num1 += "8";
        if (IsKeyPressed(KEY_NINE)) num1 += "9";

        // 检测按钮点击
        for (int i = 0; i < 16; ++i) {
            if (CheckCollisionPointRec(GetMousePosition(), buttons[i])) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    std::string label = buttonLabels[i];

                    if (label == "=") {
                        // 执行计算
                        performCalculation(num1, num2, currentOp, result);
                        num1 = "";  // 清空输入框
                        num2 = "";
                        currentOp = ' ';  // 重置操作符
                    } else if (label == "C") {
                        // 清除操作
                        num1 = "";
                        num2 = "";
                        currentOp = ' ';
                        result = "";  // 清空结果
                    } else if (label == "+" || label == "-" || label == "*" || label == "/") {
                        // 设置操作符
                        if (currentOp == ' ') {
                            currentOp = label[0];
                            num2 = num1;
                            num1 = "";
                        }
                    } else {
                        // 输入数字
                        num1 += label;
                    }
                }
            }
        }

        // 绘制
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Simple Calculator", 10, 10, 20, DARKGRAY);
        DrawText("Enter numbers and operation", 10, 40, 20, DARKGRAY);

        DrawText(("Num1: " + num1).c_str(), 10, 80, 20, BLACK);
        if (currentOp != ' ') {
            DrawText(("Op: " + std::string(1, currentOp)).c_str(), 10, 120, 20, BLACK);
        }
        DrawText(("Num2: " + num2).c_str(), 10, 160, 20, BLACK);

        if(result!="")
            cout << result << endl;
        DrawText(("Result: " + result).c_str(), 10, 60, 20, BLUE);  // 显示结果

        // 绘制按钮
        for (int i = 0; i < 16; ++i) {
            DrawRectangleRec(buttons[i], LIGHTGRAY);
            DrawText(buttonLabels[i], buttons[i].x + 25, buttons[i].y + 20, 20, BLACK);
        }

        EndDrawing();
    }

    // 关闭窗口
    CloseWindow();

    return 0;
}
*/