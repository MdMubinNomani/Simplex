#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

bool inif = false;
bool inelse = false;

bool isNumber(const string &str) {
    return regex_match(str, regex("^-?\\d+$"));
}

bool isBoolean(const string &str) {
    return (str == "true" || str == "false");
}

void translateSimplexToCpp(const string &inputFile, const string &outputFile) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    map<string, string> variables;
    string line;
    int lineNumber = 0;

    if (!inFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    if (!outFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    outFile << "#include <iostream>\nusing namespace std;\nint main() {\n";

    while (getline(inFile, line)) {
        lineNumber++;
        stringstream ss(line);
        string token;
        ss >> token;

        if (token == "set") {
            string varName, equalsSign, restOfLine;
            ss >> varName >> equalsSign;
            getline(ss, restOfLine);
            restOfLine = regex_replace(restOfLine, regex("^\\s+|\\s+$"), "");

            if (equalsSign != "=" || varName.empty() || restOfLine.empty()) {
                cerr << "Error on line " << lineNumber << ": Invalid variable declaration" << endl;
                return;
            }

            if (restOfLine.front() == '\"' && restOfLine.back() == '\"') {
                // String
                variables[varName] = "string";
                outFile << "string " << varName << " = " << restOfLine << ";\n";
            } else if (isNumber(restOfLine)) {
                // Integer
                variables[varName] = "int";
                outFile << "int " << varName << " = " << restOfLine << ";\n";
            } else if (isBoolean(restOfLine)) {
                // Boolean
                variables[varName] = "bool";
                outFile << "bool " << varName << " = " << restOfLine << ";\n";
            } else if (regex_match(restOfLine, regex("^[a-zA-Z_][a-zA-Z0-9_]*(\\s*[\\+\\-\\*/]\\s*[a-zA-Z_][a-zA-Z0-9_]*|\\s*[\\+\\-\\*/]\\s*\\d+)*$"))) {
                istringstream exprStream(restOfLine);
                string varOrNum;
                bool valid = true;
                while (exprStream >> varOrNum) {
                    if (!isNumber(varOrNum) && variables.find(varOrNum) == variables.end() && varOrNum != "+" && varOrNum != "-" && varOrNum != "*" && varOrNum != "/") {
                        valid = false;
                        cerr << "Error on line " << lineNumber << ": Undeclared variable or invalid syntax in arithmetic operation \"" << restOfLine << "\"\n";
                        break;
                    }
                }
                if (!valid) return;

                variables[varName] = "int";
                outFile << "int " << varName << " = " << restOfLine << ";\n";
            } else {
                cerr << "Error on line " << lineNumber << ": Invalid arithmetic or unknown type \"" << restOfLine << "\"\n";
                return;
            }
        } else if (token == "echo") {
            string content;
            getline(ss, content);
            content = regex_replace(content, regex("^\\s+|\\s+$"), "");

            if (content.empty()) {
                cerr << "Error on line " << lineNumber << ": Missing content in echo statement" << endl;
                return;
            }

            if (content.front() == '\"' && content.back() == '\"') {
                outFile << "cout << " << content << ";\n";
            } else if (variables.find(content) != variables.end() && variables[content] != "bool") {
                outFile << "cout << " << content << ";\n";
            } else {
                cerr << "Error on line " << lineNumber << ": Invalid echo content \"" << content << "\"\n";
                return;
            }
        } else if (token == "if") {
            string condition;
            getline(ss, condition, '{');
            condition = regex_replace(condition, regex("^\\s+|\\s+$"), "");

            if (condition.empty()) {
                cerr << "Error on line " << lineNumber << ": Missing condition in if statement" << endl;
                return;
            }

            outFile << "if (" << condition << ") {\n";
            inif = true;
        } else if (token == "else") {
            string nextToken;
            ss >> nextToken;
            if (nextToken != "{") {
                cerr << "Error on line " << lineNumber << ": Missing '{' after else" << endl;
                return;
            }
            outFile << "else {\n";
            inelse = true;
        }
        else if(token == "}") {
            if(inif) {
                inif = false;
                outFile << "}\n";
            }
            else if(inelse){
                inelse = false;
                outFile << "}\n";
            }
            else{
                cerr << "Error on line " << lineNumber << ": invalid parenthesis use \"" << token << "\"\n";
                return;
            }
        }
         else if (!token.empty()) {
            cerr << "Error on line " << lineNumber << ": Unknown statement \"" << token << "\"\n";
            return;
        }
    }

    outFile << "return 0;\n}";
    inFile.close();
    outFile.close();
}



int main() {
    string inputFile = ".\\simplex_code.txt";
    string outputFile = ".\\translated_code.cpp";

    translateSimplexToCpp(inputFile, outputFile);

    cout << "Tokenization Complete.\nVerifying grammar and arithmetic logics ..." << endl;
    cout << "<---------------- Output ----------------->" << endl << endl;

    return 0;
}
