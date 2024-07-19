#include <iostream>
#include <vector>
#include <algorithm>
#include "AVL.h"

using namespace std;

//parsing inputs
int main() {
    AVL obj;
    int numCommands;
    cin >> numCommands;
    cin.ignore();

    for (int i = 0; i < numCommands; ++i) {
        string command;
        getline(cin, command);

        if (command.substr(0, 6) == "insert") {
            size_t firstQuote = command.find("\"");
            size_t lastQuote = command.rfind("\"");
            if (firstQuote != string::npos && lastQuote != string::npos && firstQuote != lastQuote) {
                string name = command.substr(firstQuote + 1, lastQuote - firstQuote - 1); // Remove quotation marks
                string ufId = command.substr(lastQuote + 2); // Assuming a space follows the last quote
                obj.insert(name, ufId);
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (command.substr(0, 6) == "remove") {
            string ufId = command.substr(7); // Assuming a space follows "remove"
            obj.remove(ufId);
        } else if (command.substr(0, 6) == "search") {
            string param = command.substr(7); // Assuming a space follows "search"
            if (param[0] == '\"') {
                param = param.substr(1, param.length() - 2); // Remove quotation marks
                obj.searchByName(param);
            } else {
                obj.search(param);
            }
        } else if (command == "printInorder") {
            obj.printInorder();
        } else if (command == "printPreorder") {
            obj.printPreorder();
        } else if (command == "printPostorder") {
            obj.printPostorder();
        } else if (command == "printLevelCount") {
            obj.printLevelCount();
        } else if (command.substr(0, 12) == "removeInorder") {
            int n = stoi(command.substr(13)); // Assuming a space follows "removeInorder"
            obj.removeInorder(n);
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}