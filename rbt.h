#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct Node {
    string plateNum;
    bool red;
    bool custom;
    Node *left, *right, *parent;
    Node(): plateNum("$$$$"), red(1), custom(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBT {
    private:

    Node *root;
    bool found;
    int amount;

    void leftRotate(Node *x);
    void rightRotate(Node *y);
    void setPlate(Node *node, string plate);
    // void printPlate(Node *node);
    int pltCompare(string a, string b);
    // void inordPrintRBT(Node *node);
    // void preordPrintRBT(Node *node);
    Node* searchInsert(string plate, Node *node, bool insert);
    void fixInsert(Node *node);
    bool insert(string plate, bool cust);
    Node *predecessor(Node *node);
    Node *successor(Node *node);
    void transplant(Node* u, Node* v);
    void fixDelete(Node *node);
    bool deleteNode(string plate, Node *start);
    char random();
    string randomPlate();
    string inRangeInorder(Node *node, string lo, string hi, bool first);

    public:

    RBT();
    string addLicence(string plateNum);
    string addLicence();
    string dropLicence(string plateNum);
    string lookupLicence(string plateNum);
    string lookupPrev(string plateNum);
    string lookupNext(string plateNum);
    string lookupRange(string lo, string hi);
    string revenue();
};
