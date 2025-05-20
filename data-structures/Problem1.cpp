#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct StackNode {
    char* url;
    StackNode* next;

    StackNode(const char* u) {
        url = new char[strlen(u) + 1];
        strcpy(url, u);
        next = nullptr;
    }

    ~StackNode() {
        delete[] url;
    }
};


class Stack {
private:
    StackNode* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!isEmpty()) pop();
    }

    void push(const char* url) {
        StackNode* node = new StackNode(url);
        node->next = topNode;
        topNode = node;
    }

    char* top() {
        if (topNode) return topNode->url;
        return nullptr;
    }

    void pop() {
        if (topNode) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void clear() {
        while (!isEmpty()) pop();
    }

    int size() const {
        int count = 0;
        StackNode* temp = topNode;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void printStack() const {
    StackNode* nodes[100]; 
    int count = 0;
    StackNode* temp = topNode;
    while (temp) {
        nodes[count++] = temp;
        temp = temp->next;
    }
    for (int i = count - 1; i >= 0; --i) {
        cout << "\"" << nodes[i]->url << "\"";
        if (i != 0) cout << ", ";
    }
}

};


class BrowserHistory {
private:
    Stack backStack;
    Stack forwardStack;
    char* currentUrl;

public:
    BrowserHistory() : currentUrl(nullptr) {}

    ~BrowserHistory() {
        if (currentUrl) delete[] currentUrl;
    }

void visit(const char* url) {
    if (currentUrl) {
        backStack.push(currentUrl);
        delete[] currentUrl;
    }
    forwardStack.clear();
    currentUrl = new char[strlen(url) + 1];
    strcpy(currentUrl, url);
    printState("visit(\"" + string(url) + "\")");
}

void goBack() {
    if (backStack.size() < 1) {
        cout << "Cannot go back.\n";
        return;
    }
    forwardStack.push(currentUrl);
    currentUrl = new char[strlen(backStack.top()) + 1];
    strcpy(currentUrl, backStack.top());
    backStack.pop();
    printState("goBack()");
}

void goForward() {
    if (forwardStack.isEmpty()) {
        cout << "Cannot go forward.\n";
        return;
    }
    backStack.push(currentUrl);
    currentUrl = new char[strlen(forwardStack.top()) + 1];
    strcpy(currentUrl, forwardStack.top());
    forwardStack.pop();
    printState("goForward()");
}


    void printState(const string& action) {
    cout << action << ":\n";
    cout << "○ backStack: [";
    backStack.printStack();
    cout << "]\n○ forwardStack: [";
    forwardStack.printStack();
    cout << "]\n○ currentUrl: \"" << (currentUrl ? currentUrl : "") << "\"\n";
}

};

int main() {
    BrowserHistory bh;
    ifstream input("Problem1.txt"); 

    if (!input.is_open()) {
        cout << "Failed to open input file!" << endl;
        return 1;
    }

    string command, url;
    while (input >> command) {
        if (command == "visit") {
            input.ignore();
            getline(input, url);
            bh.visit(url.c_str());
        } else if (command == "back") {
            bh.goBack();
        } else if (command == "forward") {
            bh.goForward();
        }
    }

    input.close();
    return 0;
}
