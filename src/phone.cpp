#include "phone.hpp"

App::App(std::string path)
{
    ifstream input(path);
    if (!input)
    {
        cout << "ERROR::OPEN FILE" << endl;
        return;
    }

    string line;
    while (getline(input, line))
    {
        istringstream iss(line);
        info currentInfo;
        getline(iss, currentInfo.name, ',');
        getline(iss, currentInfo.number, ',');
        getline(iss, currentInfo.address);
        infos[currentInfo.name] = currentInfo;
        infos2[currentInfo.number] = currentInfo;
        tree.insert(currentInfo.number);
    }
    input.close();
    cout << "SUCCESS::LOAD FILE" << endl;
}

string App::getAddress(string name)
{
    auto it = this->infos.find(name);
    if (it != this->infos.end())
    {
        return it->second.address;
    }
    else
    {
        return "ERROR::ADDRESS NOT FOUND";
    }
}

string App::getNumber(string name)
{
    auto it = this->infos.find(name);
    if (it != this->infos.end())
    {
        return it->second.number;
    }
    else
    {
        return "ERROR::NUMBER NOT FOUND";
    }
}

bool App::deleteName(string name)
{
    auto it = this->infos.find(name);
    if (it != this->infos.end())
    {
        infos.erase(it);
    }
    return true;
}

bool App::insert(string name, string number, string address)
{
    auto it = this->infos.find(name);
    if (it == this->infos.end())
    {
        info newinfo = {name, number, address};
        this->infos[name] = newinfo;
    }
    else
    {
        infos[name].address = address;
        infos[name].number = number;
    }
    return true;
}

void use()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Phonebook App");

    string inputName = "";
    string inputNumber = "";
    string inputAddress = "";
    string output = "";
    App phonebook("../res/phone.txt");

    ScreenState currentState = MAIN_MENU;

    Vector2 buttonPos = { 200, 100 };  
    Vector2 outputPos = { 200, 550 };
    Vector2 inputPos = { 200, 150 };
    float buttonWidth = 300;
    float buttonHeight = 50;
    float buttonSpacing = 60; 

    char cur = 'a'; // 'a' name, 'b' number, 'c' address

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            case MAIN_MENU:
                DrawText("Phonebook App", 200, 50, 30, DARKGRAY);

                buttonPos.y = 100;  
                
                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentState = NAME_QUERY;
                }
                DrawRectangle(buttonPos.x, buttonPos.y, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText("Query by Name", buttonPos.x + 50, buttonPos.y + 15, 20, DARKBLUE);
                
                buttonPos.y += buttonHeight + buttonSpacing; 
                
                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentState = NUMBER_QUERY;
                }
                DrawRectangle(buttonPos.x, buttonPos.y, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText("Query by Phone", buttonPos.x + 50, buttonPos.y + 15, 20, DARKBLUE);
                
                buttonPos.y += buttonHeight + buttonSpacing;
                
                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentState = NAME_DELETE;
                }
                DrawRectangle(buttonPos.x, buttonPos.y, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText("Delete by Name", buttonPos.x + 50, buttonPos.y + 15, 20, DARKBLUE);
                
                buttonPos.y += buttonHeight + buttonSpacing;
                
                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentState = NAME_INSERT;
                }
                DrawRectangle(buttonPos.x, buttonPos.y, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText("Insert by Name", buttonPos.x + 50, buttonPos.y + 15, 20, DARKBLUE);

                break;

            case NAME_QUERY:
                output = "";
                DrawText("Enter Name to Query:", 200, 50, 20, DARKGRAY);
                DrawRectangle(buttonPos.x, buttonPos.y-300, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText(inputName.c_str(), inputPos.x, inputPos.y, 20, DARKBLUE);

                
                if (IsKeyPressed(KEY_ENTER)) {
                    string address = phonebook.getAddress(inputName.c_str());
                    string number = phonebook.getNumber(inputName.c_str());
                    output = "Name: " + inputName +  "\nNumber: " + number + "\nAddress: " + address;
                    currentState = MAIN_MENU; 
                    inputName = "";
                }

                if (IsKeyPressed(KEY_BACKSPACE) && inputName.length() > 0) {
                    inputName.pop_back();
                }
                for (int key = KEY_A; key <= KEY_Z; key++) {
                    if (IsKeyPressed(key)) {
                        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                            inputName += char(key);
                        } else {
                            inputName += char(key + 32);
                        }
                    }
                }
                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key)) {
                        inputName += char(key);
                    }
                }
                break;

            case NUMBER_QUERY:
                output = "";
                DrawText("Enter Phone Number to Query:", 200, 50, 20, DARKGRAY);
                DrawRectangle(buttonPos.x, buttonPos.y-300, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText(inputNumber.c_str(), inputPos.x, inputPos.y, 20, DARKBLUE);
                
                for(int i=0;i<phonebook.numbers.size();i++)
                {
                    cout << phonebook.numbers[i] << endl;
                    DrawText(phonebook.numbers[i].c_str(), inputPos.x, inputPos.y+20*(i+1), 20, DARKBLUE);
                }

                // 查询操作
                if (IsKeyPressed(KEY_ENTER)) {
                    info curInfo = phonebook.infos2[inputNumber];
                    output = "Name: " + curInfo.name + "\nAddress: " + curInfo.address;
                    currentState = MAIN_MENU;
                    inputNumber = "";
                }

                // 输入处理
                if (IsKeyPressed(KEY_BACKSPACE) && inputNumber.length() > 0) {
                    inputNumber.pop_back();
                    phonebook.numbers = phonebook.tree.search(inputNumber);
                    
                }
                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key))
                    {
                        inputNumber += char(key);
                        phonebook.numbers = phonebook.tree.search(inputNumber);
                    }
                }
                break;

            case NAME_DELETE:
                output = "";
                DrawText("Enter Name to Delete:", 200, 50, 20, DARKGRAY);
                DrawRectangle(buttonPos.x, buttonPos.y-300, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawText(inputName.c_str(), inputPos.x, inputPos.y, 20, DARKBLUE);

                if (IsKeyPressed(KEY_ENTER)) {
                    if (phonebook.deleteName(inputName.c_str())) {
                        output = "SUCCESS::DELETE NAME";
                    } else {
                        output = "FAIL::DELETE NAME.";
                    }
                    inputName = "";
                    currentState = MAIN_MENU;  
                }

                if (IsKeyPressed(KEY_BACKSPACE) && inputName.length() > 0) {
                    inputName.pop_back();
                }

                for (int key = KEY_A; key <= KEY_Z; key++) {
                    if (IsKeyPressed(key)) {
                        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                            inputName += char(key);
                        } else {
                            inputName += char(key + 32);
                        }
                    }
                }
                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key)) {
                        inputName += char(key);
                    }
                }

                break;

            case NAME_INSERT:
                output = "";
                DrawRectangle(buttonPos.x, buttonPos.y-350, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawRectangle(buttonPos.x, buttonPos.y-250, buttonWidth, buttonHeight, LIGHTGRAY);
                DrawRectangle(buttonPos.x, buttonPos.y-150, buttonWidth, buttonHeight, LIGHTGRAY);

                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y-350, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    cur = 'a';
                    cout << cur << endl;
                }

                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y-250, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    cur = 'b';
                    cout << cur << endl;
                }

                if (CheckCollisionPointRec(GetMousePosition(), {buttonPos.x, buttonPos.y-150, buttonWidth, buttonHeight}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    cur = 'c';
                    cout << cur << endl;
                }

                DrawText("Enter Name to Insert:", 200, 50, 20, DARKGRAY);
                DrawText(inputName.c_str(), inputPos.x, inputPos.y-50, 20, DARKBLUE);

                DrawText("Enter Phone Number:", 200, 150, 20, DARKGRAY);
                DrawText(inputNumber.c_str(), inputPos.x, inputPos.y + 50, 20, DARKBLUE);

                DrawText("Enter Address:", 200, 250, 20, DARKGRAY);
                DrawText(inputAddress.c_str(), inputPos.x, inputPos.y + 150, 20, DARKBLUE);

                if (IsKeyPressed(KEY_ENTER)) {
                    if (phonebook.insert(inputName, inputNumber, inputAddress)) {
                        output = "Entry inserted successfully.";
                    } else {
                        output = "Failed to insert entry.";
                    }
                    currentState = MAIN_MENU;  // 插入后返回主菜单
                    inputName = "";
                }

                if (IsKeyPressed(KEY_BACKSPACE) && inputName.length() > 0) {
                    inputName.pop_back();
                }

                for (int key = KEY_A; key <= KEY_Z; key++) {
                    if (IsKeyPressed(key)) {
                        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                            if(cur=='a')
                                inputName += char(key);
                            if(cur=='c')
                                inputAddress += char(key);
                        } else {
                            if(cur=='a')
                                inputName += char(key+32);
                            if(cur=='c')
                                inputAddress += char(key+32);
                        }
                        cout << inputName << endl << inputNumber << endl << inputAddress << endl;
                    }
                }

                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key)) {
                        if(cur=='a')
                            inputName += char(key);
                        if(cur=='b')
                            inputNumber += char(key);
                        if(cur=='c')
                            inputAddress += char(key);
                    }
                }

                break;
        }

       
        if (!output.empty()) {
            DrawText(output.c_str(), outputPos.x, outputPos.y, 20, DARKGREEN);
        }

        EndDrawing();
    }

    CloseWindow();
}

void dfs(vector<string> &ans, string &temp, TrieNode *cur)
{
    if (cur->End) {
        ans.push_back(temp);
        return;
    }

    for (char a = '0'; a <= '9'; a++) {
        if (cur->children.find(a) != cur->children.end()) {
            temp += a; // 添加当前字符
            dfs(ans, temp, cur->children[a]); // 递归
            temp.pop_back(); // 回溯
        }
    }
}

vector<string> Trile::search(const string &number)
{
    vector<string> ans;
    string temp;
    TrieNode* cur = root;
    for(auto num : number)
    {
        //cout << num << " ";
        if(cur->children.find(num) == cur->children.end())
            return ans;
        temp.push_back(num);
        cur = cur->children[num];
    }
    dfs(ans, temp, cur);
    return ans;
}

void Trile::insert(const string &number)
{
    TrieNode* cur = root;
    for(char c : number)
    {
        if(cur->children.find(c) == cur->children.end())
            cur->children[c] = new TrieNode();
        cur = cur->children[c];
    }
    cur -> End = true;
}




