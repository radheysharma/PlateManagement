#include "rbt.h"

RBT::RBT() {
    root = nullptr;
    found = 0;          //flag to check if a plate number exists in the tree
    amount = 0;         //revenue amount
    srand(time(0));     //using current time as a seed to generate random values
}

void RBT::leftRotate(Node *x) {
    /*
        Function to perform Left Rotation on x
            r               r
            |               |
            x               y
           / \             / \
          a   y    -->    x   b
             / \         / \
            z   b       a   z
    */
    Node *y = x -> right;
    Node *z = x -> right = y -> left;
    y -> left = x;
    y -> parent = x -> parent;
    x -> parent = y;
    if(nullptr != z)
        z -> parent = x;
    if(y -> parent == nullptr)
        root = y;
    else if(y -> parent -> left == x)
        y -> parent -> left = y;
    else
        y -> parent -> right = y;
}

void RBT::rightRotate(Node *y) {
    /*
        Function to perform Right Rotation on y
            r               r
            |               |
            x               y
           / \             / \
          a   y    <--    x   b
             / \         / \
            z   b       a   z
    */
    Node *x = y -> left;
    Node *z = y -> left = x -> right;
    x -> right = y;
    x -> parent = y -> parent;
    y -> parent = x;
    if(nullptr != z)
        z -> parent = y;
    if(x -> parent == nullptr)
        root = x;
    else if(x -> parent -> left == y)
        x -> parent -> left = x;
    else
        x -> parent -> right = x;
}

//Function to assign a plateNum to a node
void RBT::setPlate(Node *node, string plate) {
    node -> plateNum[0] = plate[0];
    node -> plateNum[1] = plate[1];
    node -> plateNum[2] = plate[2];
    node -> plateNum[3] = plate[3];
}

//Function to print plateNum of a node
// void RBT::printPlate(Node *node) {
//     cout << node -> plateNum[0];
//     cout << node -> plateNum[1];
//     cout << node -> plateNum[2];
//     cout << node -> plateNum[3];
// }

//Function to compare two plateNums
int RBT::pltCompare(string a, string b) {
    for(int i = 0; i < 4; ++i) {
        if(a[i] > b[i]) {
            return -1;
        }
        else if(a[i] < b[i]) {
            return 1;
        }
    }
    return 0;
}

//Function to print Inorder traversal of tree
// void RBT::inordPrintRBT(Node *node){
//     if(nullptr != node) {
//         inordPrintRBT(node -> left);
//         cout << " " ;
//         printPlate(node);
//         cout << ((node -> red) ? 'r':'b') << " ";
//         inordPrintRBT(node -> right);
//     }
//     else cout << " . ";
// }

//Function to print Preorder traversal of tree
// void RBT::preordPrintRBT(Node *node){
//     if(nullptr == node)
//         cout << " . ";
//     else {
//         printPlate(node);
//         cout << ((node -> red) ? 'r':'b') << " (";
//         preordPrintRBT(node -> left);
//         cout << ", ";
//         preordPrintRBT(node -> right);
//         cout << ")";
//     }
// }

//Helper Function to do Search and Insert (only if boolean insert is set to 1)
Node* RBT::searchInsert(string plate, Node *node, bool insert) {
    if(nullptr == root) {       //Root Case
        if(insert) {
            root = new Node();
            setPlate(root, plate);
        }
        return root;
    }
    else if(nullptr == node) {  //Did not find node in tree
        return node;
    }
    else if(pltCompare(plate, node -> plateNum) == 0) {     //Found node in tree
        found = 1;
        return node;
    }
    else if(pltCompare(plate, node -> plateNum) == -1) {    //perform searchInsert in the Right sub-Tree
        if(nullptr == node -> right && insert) {
            Node *temp = new Node();
            setPlate(temp, plate);
            temp -> parent = node;
            node -> right = temp;
            return node -> right;
        }
        return searchInsert(plate, node -> right, insert);
    }
    else {                                                  //perform searchInsert in the Left sub-Tree
        if(nullptr == node -> left && insert) {
            Node *temp = new Node();
            setPlate(temp, plate);
            temp -> parent = node;
            node -> left = temp;
            return node -> left;
        }
        return searchInsert(plate, node -> left, insert);
    }
}

//Helper Function to fix violations for insertion
void RBT::fixInsert(Node *node) {
    if(root == node)        //if node is root, make it black
        node -> red = 0;
    else if(node -> red && node -> parent -> red)   //consecutive red nodes violation cases
    {
        Node *grPrnt = node -> parent -> parent;    //grandparent node
        Node *prnt = node -> parent;                //parent node
        Node *uncle = (grPrnt -> left == node -> parent) ? grPrnt -> right : grPrnt -> left;    //parent node's sibling

        //coloring case, uncle is red
        if(nullptr != uncle && uncle -> red) {
            grPrnt -> red ^= 1;
            prnt -> red ^= 1;
            uncle -> red ^= 1;
            fixInsert(grPrnt);
        }

        //Rotation cases
        //RLb case
        else if(grPrnt -> right == prnt && prnt -> left == node) {
            rightRotate(prnt);
            fixInsert(prnt);
        }
        //LRb case
        else if(grPrnt -> left == prnt && prnt -> right == node) {
            leftRotate(prnt);
            fixInsert(prnt);
        }

        //Rotation and coloring cases
        //RRb case
        else if(grPrnt -> right == prnt && prnt -> right == node) {
            leftRotate(grPrnt);
            grPrnt -> red ^= 1;
            prnt -> red ^= 1;
            fixInsert(prnt);
        }
        //LLb case
        else if(grPrnt -> left == prnt && prnt -> left == node) {
            rightRotate(grPrnt);
            grPrnt -> red ^= 1;
            prnt -> red ^= 1;
            fixInsert(prnt);
        }
    }
}

//insertion function
bool RBT::insert(string plate, bool cust) {
    Node *temp = searchInsert(plate, root, 1);
    if(found) {
        return found = 0;   //reset flag to 0 and return 0 i.e., no insertion
    }
    else {
        temp -> custom = cust;
        fixInsert(temp);
    }
    return 1;
}

//function to find predecessor of a node
Node* RBT::predecessor(Node *node) {
    if(nullptr == node) {
        return node;
    }
    Node *temp;
    if(nullptr != node -> left) {   //if left child exists, predecessor is max node in left subtree
        temp = node -> left;
        while(nullptr != temp -> right) {
            temp = temp -> right;
        }
    }
    else {  //if left child does not exist, predecessor is the first parent node with lower plateNum
        temp = node -> parent;
        while(nullptr != temp && (pltCompare(temp -> plateNum, node -> plateNum) == -1)) {
            temp = temp -> parent;
        }
    }
    return temp;
}

//function to find successor of a node
Node* RBT::successor(Node *node) {
    if(nullptr == node) {
        return node;
    }
    Node *temp;
    if(nullptr != node -> right) {  //if right child exists, successor is min node in right subtree
        temp = node -> right;
        while(nullptr != temp -> left) {
            temp = temp -> left;
        }
    }
    else {  //if right child does not exist, successor is the first parent node with greater plateNum
        temp = node -> parent;
        while(nullptr != temp && (pltCompare(temp -> plateNum, node -> plateNum) == 1)) {
            temp = temp -> parent;
        }
    }
    return temp;
}

//Helper function to do transplants when deleting a node
void RBT::transplant(Node* u, Node* v) {
    if(root == u) {
        root = v;
    }
    else if(u == u -> parent -> left) {
        u -> parent -> left = v;
    }
    else {
        u -> parent -> right = v;
    }
    if(nullptr != v)
        v -> parent = u -> parent;
}

//Helper function to fix deletion violations
void RBT::fixDelete(Node *node) {
    if(node == root) {
        node -> red = 0;
        return;
    }
    Node *prnt = node -> parent;        //parent node
    bool l = (node == prnt -> left);    //boolean to store is node is left child of parent node
    Node *sibling = (l) ? prnt -> right : prnt -> left;     //sibling node

    //violation cases
    //sibling is red
    if(sibling -> red) {
        bool temp = prnt -> red;
        prnt -> red = sibling -> red;
        sibling -> red = temp;
        (l) ? leftRotate(prnt) : rightRotate(prnt);
        fixDelete(node);
    }
    else {  //sibling is black
        //both children of sibling are black or nil
        if((nullptr == sibling -> left || !(sibling -> left -> red)) && (nullptr == sibling -> right || !(sibling -> right -> red))) {
            sibling -> red = 1;
            if(prnt -> red) {   //subcase: parent is red
                prnt -> red = 0;
                return;
            }
            else {              //subcase: parent is black
                fixDelete(prnt);
            }
        }
        else {  //atleast one child of sibling is red
            Node *near = (l) ? sibling -> left : sibling -> right;  //child of sibling node which is visually closer to double black node
            Node *far = (l) ? sibling -> right : sibling -> left;   //child of sibling node which is visually far from double black node
            if(nullptr == far || !(far -> red)) {   //case, when far child is black
                //swap color of sibling and near child
                sibling -> red = 1;
                near -> red = 0;
                //rotate sibling in opp direction from double black node
                (l) ? rightRotate(sibling) : leftRotate(sibling);
            }
            {   //case, when near child is black or both children are red
                //swap parent and sibling's color
                sibling -> red = prnt -> red;
                prnt -> red = 0;        //sibling is black
                //rotate parent in direction of double black node
                (l) ? leftRotate(prnt) : rightRotate(prnt);
                //change color of far red child to black
                far -> red = 0;
            }
        }
    }
}

//deletion function, same as binary search tree deletion
bool RBT::deleteNode(string plate, Node *start) {
    Node *node = searchInsert(plate, start, 0);

    if(nullptr == node) {       //node not found
        return 0;
    }

    Node *prnt = node -> parent;        //parent node
    bool l = (node == prnt -> left);    //boolean to store is node is left child of parent node
    if(nullptr == node -> left && nullptr == node -> right) {   //leaf node deletion
        if(node -> red) {   //leaf is red
            (l) ? (prnt -> left = nullptr) : (prnt -> right = nullptr);
        }
        else {      //leaf is black
            if(node == root) {
                root = nullptr;
            }
            else {
                fixDelete(node);
                (l) ? (prnt -> left = nullptr) : (prnt -> right = nullptr);
            }
        }
        delete node;
    }

    //single child cases
    //left child is nil
    else if(nullptr == node -> left) {
        transplant(node, node -> right);
        if(!(node -> red) && !(node -> right -> red)) {
            fixDelete(node -> right);
            (l) ? (prnt -> left = nullptr) : (prnt -> right = nullptr);
        }
        else {
            node -> right -> red = 0;
        }
        delete node;
    }
    //right child is nil
    else if(nullptr == node -> right) {
        transplant(node, node -> left);
        if(!(node -> red) && !(node -> left -> red)) {
            fixDelete(node -> left);
            (l) ? (prnt -> left = nullptr) : (prnt -> right = nullptr);
        }
        else {
            node -> left -> red = 0;
        }
        delete node;
    }

    //both children case
    else {
        Node *replacement = predecessor(node);      //replacement is the inorder predecessor of node (can be set as successor)
        string tempPlate = replacement -> plateNum;
        deleteNode(replacement -> plateNum, replacement);
        setPlate(node, tempPlate);
    }
    return 1;
}

//function to generate a random alphanumeric character
char RBT::random() {
    char r = (rand() % 36) + 48;
    if(r > 57) r += 7;
    return r;
}

//function to generate a random plateNum
string RBT::randomPlate() {
    string plateNum;
    do {
        plateNum = "";
        plateNum += random();
        plateNum += random();
        plateNum += random();
        plateNum += random();
    }while(nullptr != searchInsert(plateNum, root, 0));

    return plateNum;
}

//helper funtion for inorder traversing in a given range
string RBT::inRangeInorder(Node *node, string lo, string hi, bool first) {
    string output = "";
    if(nullptr != node && (pltCompare(node -> plateNum, lo) <= 0) && (pltCompare(node -> plateNum, hi) >= 0)) {
        output += inRangeInorder(node -> left, lo, hi, 0);
        if(first)
            output += node -> plateNum;
        else
            output += ", " + node -> plateNum;
        output += inRangeInorder(node -> right, lo, hi, 0);
    }
    return output;
}

//function to insert custom plateNum
string RBT::addLicence(string plateNum) {
    string output = "";
    if(insert(plateNum, 1)) {
        amount += 7;
        output = plateNum + " registered successfully.\n";
    }
    else {
        output = "Failed to register " + plateNum + ": already exists.\n";
    }
    return output;
}

//function to insert random plateNum
string RBT::addLicence() {
    string output = "";
    string plateNum = randomPlate();
    insert(plateNum, 0);
    amount += 4;
    output = plateNum + " created and registered successfully.\n";
    return output;
}

//function to delete plateNum
string RBT::dropLicence(string plateNum) {
    string output = "";
    Node *temp = searchInsert(plateNum, root, 0);
    if(nullptr != temp) {
        amount -= ((temp -> custom) ? 7 : 4);
    }
    if(deleteNode(plateNum, temp)) {
        output =  plateNum + " removed successfully.\n";
    }
    else {
        output = "Failed to remove " + plateNum + ": does not exist.\n";
    }
    return output;
}

//function to search a plateNum
string RBT::lookupLicence(string plateNum) {
    string output = "";
    if(nullptr != searchInsert(plateNum, root, 0)) {
        output = plateNum + " exists.\n";
    }
    else {
        output = plateNum + " does not exist.\n";
    }
    return output;
}

//function to get previous plateNum
string RBT::lookupPrev(string plateNum) {
    string output = "";
    Node *temp = searchInsert(plateNum, root, 0);
    temp = predecessor(temp);
    if(nullptr != temp) {
        output = plateNum + "'s prev is " + temp -> plateNum + ".\n";
    }
    else {
        output = plateNum + "'s prev does not exist.\n";
    }
    return output;
}

//function to get next plateNum
string RBT::lookupNext(string plateNum) {
    string output = "";
    Node *temp = searchInsert(plateNum, root, 0);
    temp = successor(temp);
    if(nullptr != temp) {
        output = plateNum + "'s next is " + temp -> plateNum + ".\n";
    }
    else {
        output = plateNum + "'s next does not exist.\n";
    }
    return output;
}

//function to search in range
string RBT::lookupRange(string lo, string hi) {
    string output = "";
    Node *temp = root;
    while(nullptr != temp && pltCompare(temp -> plateNum, lo) == 1) {
        temp = temp -> right;
    }
    while(nullptr != temp && pltCompare(temp -> plateNum, hi) == -1) {
        temp = temp -> left;
    }
    string plates = inRangeInorder(temp, lo, hi, 1);
    output = "Plate numbers between " + lo + " and " + hi + ": " + plates + ".\n";
    return output;
}

//function to get annual revenue
string RBT::revenue() {
    string output = "";
    output = "Current annual revenue is " + to_string(amount) + " Galleons.\n";
    return output;
}
