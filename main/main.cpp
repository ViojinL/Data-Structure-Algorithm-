#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum TokenType { INTEGER = 1, IDENTIFIER = 2, ILLEGAL = 3 };

static inline bool isDigit03(char c) { return c >= '0' && c <= '3'; }
static inline bool isDigit123(char c) { return c >= '1' && c <= '3'; }
static inline bool isLetterABC(char c) { return c >= 'a' && c <= 'c'; }


pair<int, string> lex_analyzer(const string &lexeme) {
    if (lexeme.empty()) return {ILLEGAL, lexeme};

    enum State { START, INT_ZERO, INT_NZ, ID, DEAD };
    State s = START;

    for (size_t i = 0; i < lexeme.size(); ++i) {
        char c = lexeme[i];
        switch (s) {
            case START:
                if (c == '0') s = INT_ZERO;                       // 只能是单独的0
                else if (isDigit123(c)) s = INT_NZ;                // 非零整数前导位
                else if (isLetterABC(c)) s = ID;                  
                else s = DEAD;
                break;
            case INT_ZERO:
               
                s = DEAD;
                break;
            case INT_NZ:
                if (isDigit03(c)) s = INT_NZ;                    
                else s = DEAD;
                break;
            case ID:
                if (isLetterABC(c) || isDigit03(c)) s = ID;       
                else s = DEAD;
                break;
            case DEAD:
                
                break;
        }

        if (s == DEAD) {

            return {ILLEGAL, lexeme};
        }
    }

    if (s == INT_ZERO || s == INT_NZ) return {INTEGER, lexeme};
    if (s == ID) return {IDENTIFIER, lexeme};
    return {ILLEGAL, lexeme};
}


vector<pair<int, string>> process_input(const string &line) {
    vector<pair<int, string>> results;
    stringstream ss(line);
    string tok;
    while (ss >> tok) {
        results.push_back(lex_analyzer(tok));
    }
    return results;
}


void print_results(const vector<pair<int, string>> &res) {
    for (const auto &p : res) {
        cout << "<" << p.first << ", " << p.second << ">" << endl;
    }
}


void test() {
    
    cout << "=== 测试1：学号后5位 ===" << endl;
    cout << "请输入学号后5位：" << endl;
    string input1; getline(cin, input1);
    cout << "分析结果：" << endl;
    print_results(process_input(input1));

   
    cout << "\n=== 测试2：姓氏首字母+学号后2位 ===" << endl;
    cout << "请输入姓氏首字母+学号后2位：" << endl;
    string input2; getline(cin, input2);
    cout << "分析结果：" << endl;
    print_results(process_input(input2));

   
    cout << "\n=== 测试3：多个词（含标识符和整数） ===" << endl;
    cout << "请输入多个词（空格分隔）：" << endl;
    string input3; getline(cin, input3);
    cout << "分析结果：" << endl;
    print_results(process_input(input3));

   
    cout << "\n=== 测试4：多个词（含非法词） ===" << endl;
    cout << "请输入多个词（空格分隔，含非法词）：" << endl;
    string input4; getline(cin, input4);
    cout << "分析结果：" << endl;
    print_results(process_input(input4));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    test();
    return 0;
}
