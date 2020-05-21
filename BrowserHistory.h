#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node() = delete;
    Node(T element):data(element), next(nullptr), prev(nullptr){

    }
};

class hyperlinkDetails {
public:
    string address;
    size_t sizeOfPage;

    hyperlinkDetails(string url, size_t page_):address(url), sizeOfPage(page_){
    }
    hyperlinkDetails() {
    }
};



class BrowserHistory {
public:
    BrowserHistory();
    ~BrowserHistory();
    void visitSite(string url, size_t filesize);
    void backButton();
    void forwardButton();
    void readFile(string fileName);
    string currentUrl();
    size_t currentPageSize();
    size_t getHistoryLength();
    void remove(Node<hyperlinkDetails>* removeNode);

private:
    Node<hyperlinkDetails>* head;
    Node<hyperlinkDetails>* tail;
    size_t length = 0;
    size_t counter = 0;
    Node<hyperlinkDetails>* tracer;
};

BrowserHistory::BrowserHistory() {
    head = new Node<hyperlinkDetails>(hyperlinkDetails());
    tail = new Node<hyperlinkDetails>(hyperlinkDetails());

    head->next = tail;
    tail->prev = head;
}

BrowserHistory::~BrowserHistory() {
    delete head;
    delete tail;
}
void BrowserHistory::forwardButton() {
    if (tracer->next == tail) {
        cout << "NO page exists." << endl;
    }
    else {
        tracer = tracer->next;
        counter--;
    }
}
void BrowserHistory::backButton() {
    if (tracer->prev == head) {
        cout << "NO previous page exists." << endl;
    }
    else {
        tracer = tracer->prev;
        counter++;
    }

}

void BrowserHistory::visitSite(string url, size_t filesize) {

    hyperlinkDetails New;
    New.address = url;
    New.sizeOfPage = filesize;

    if (counter > 0)
    {
        while (counter >= 0 && counter != 0) {
            remove(tail->prev);
            counter--;
        }
    }

    Node<hyperlinkDetails> * newNode = new Node<hyperlinkDetails>(New);
    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
    tracer = newNode;
}

string BrowserHistory::currentUrl()
{
    if (head->next == tail) {
    return"";
    }
    return tracer->data.address;
}

size_t BrowserHistory::currentPageSize()
{
    return tracer->data.sizeOfPage;
}

size_t BrowserHistory::getHistoryLength()
{
    length = 0;
    Node<hyperlinkDetails>* tracerSecondary = head->next;

    while (tracerSecondary != tail)
    {
        tracerSecondary = tracerSecondary->next;
        length++;
    }

    return length;
}

void BrowserHistory::remove(Node<hyperlinkDetails>* removeNode)
{
    if (head->next == tail) {
        cout << "An error has occurred." << endl;
    }

    if (removeNode == head || removeNode == tail) {
        cout << "An error has occurred." << endl;
    }

    Node<hyperlinkDetails>* nextNode = removeNode->next;
    Node<hyperlinkDetails>* prevNode = removeNode->prev;

    nextNode->prev = prevNode;
    prevNode->next = nextNode;
}

void BrowserHistory::readFile(string filename)
{
string a, b;
size_t c;
ifstream actionKey(filename);

while (actionKey >> a) {

if (a == "visit") {
actionKey >> b >> c;
visitSite(b, c);
}
else if(a == "forward"){
forwardButton();
}
else if (a == "back") {
backButton();
}
}
}


