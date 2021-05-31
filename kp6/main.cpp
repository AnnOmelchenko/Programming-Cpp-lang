#include <iostream>
#include "string.h"
#include "Btree.h"
using namespace std;

void BtreeByWeight::insert(Traveler traveler){
    if(root != NULL)
    {
        insert(traveler, root);
    }
    else
    {
        root = new node;
        root->traveler = traveler;
        root->left = NULL;
        root->right = NULL;
        Head = root;
    }
}
void BtreeByWeight::insert(Traveler traveler, node *leaf){
    if (traveler.baggage.weight < leaf->traveler.baggage.weight) {
        if (leaf->left != NULL)
            insert(traveler, leaf->left);
        else {
            leaf->left = new node;
            leaf->left->traveler = traveler;
            leaf->left->left = NULL;    //Sets the left child of the child node to null
            leaf->left->right = NULL;   //Sets the right child of the child node to null
        }
    } else if (traveler.baggage.weight >= leaf->traveler.baggage.weight) {
        if (leaf->right != NULL)
            insert(traveler, leaf->right);
        else {
            leaf->right = new node;
            leaf->right->traveler = traveler;
            leaf->right->left = NULL;  //Sets the left child of the child node to null
            leaf->right->right = NULL; //Sets the right child of the child node to null
        }
    }
}

void BtreeByWeight::showTree() {
    if (Head != NULL){
        show(Head, 0);
    }
    else{
        cout << "Tree is empty \n";
    }
}

void BtreeByWeight::show(node *leaf, int level) {
    if(leaf)
    {
        show(leaf->right, level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        {
            cout << leaf->traveler.baggage.weight << endl;
        }
        show(leaf->left, level + 1);
    }
}

void BtreeByTicketId::insert(Traveler traveler){
    if(root != NULL)
    {
        insert(traveler, root);
    }
    else
    {
        root = new node;
        root->traveler = traveler;
        root->left = NULL;
        root->right = NULL;
        Head = root;
    }
}

void BtreeByTicketId::insert(Traveler traveler, node *leaf){
    if (traveler.ticketId < leaf->traveler.ticketId) {
        if (leaf->left != NULL)
            insert(traveler, leaf->left);
        else {
            leaf->left = new node;
            leaf->left->traveler = traveler;
            leaf->left->left = NULL;    //Sets the left child of the child node to null
            leaf->left->right = NULL;   //Sets the right child of the child node to null
        }
    } else if (traveler.ticketId >= leaf->traveler.ticketId) {
        if (leaf->right != NULL)
            insert(traveler, leaf->right);
        else {
            leaf->right = new node;
            leaf->right->traveler = traveler;
            leaf->right->left = NULL;  //Sets the left child of the child node to null
            leaf->right->right = NULL; //Sets the right child of the child node to null
        }
    }
}

void BtreeByTicketId::showTree() {
    if (Head != NULL){
        show(Head, 0);
    }
    else{
        cout << "Tree is empty \n";
    }
}

void BtreeByTicketId::show(node *leaf, int level) {
    if(leaf)
    {
        show(leaf->right, level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        {
            cout << leaf->traveler.ticketId << endl;
        }
        show(leaf->left, level + 1);
    }
}

Btree::Btree()
{
    root = NULL;
    Head = root;
    Quantity = 0;
    Sum = 0;
    AverageValue = 0;
}

void Btree::destroy_tree(node *leaf)
{
    if(leaf != NULL)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void Btree::insert(Traveler traveler, node *leaf)
{
    if(strlen(leaf->traveler.lastName) >= strlen(traveler.lastName))
    {
        if(leaf->left != NULL)
            insert(traveler, leaf->left);
        else
        {
            leaf->left = new node;
            leaf->left->traveler = traveler;
            leaf->left->left = NULL;    //Sets the left child of the child node to null
            leaf->left->right = NULL;   //Sets the right child of the child node to null
        }
    }
    else if(strlen(leaf->traveler.lastName) < strlen(traveler.lastName))
    {
        if(leaf->right != NULL)
            insert(traveler, leaf->right);
        else
        {
            leaf->right = new node;
            leaf->right->traveler = traveler;
            leaf->right->left = NULL;  //Sets the left child of the child node to null
            leaf->right->right = NULL; //Sets the right child of the child node to null
        }
    }
}

void Btree::search(node *leaf)
{
    if(leaf != NULL)
    {
        search(leaf->left);
        search(leaf->right);
        Quantity++;
        Sum += leaf->traveler.ticketId;
    }
}

void Btree::insert(Traveler traveler)
{
    if(root != NULL)
    {
        insert(traveler, root);
    }
    else
    {
        root = new node;
        root->traveler = traveler;
        root->left = NULL;
        root->right = NULL;
        Head = root;
    }
}


void Btree::show(node *leaf, int level)
{
    if(leaf)
    {
        show(leaf->right, level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        {
            cout << leaf->traveler.lastName << endl;
        }
        show(leaf->left, level + 1);
    }
}

void Btree::search()
{
    search(root);
    if (Quantity > 0)
    {
        AverageValue = Sum / Quantity;
        cout << "Average value of id equals to: " << AverageValue << endl;
    }
    else{
        cout << "There is no element in the tree \n";
    }
}

void Btree::destroy_tree()
{
    destroy_tree(Head);
    Head = NULL;
}

void Btree::showTree() {
    if (Head != NULL){
        show(Head, 0);
    }
    else{
        cout << "Tree is empty \n";
        return;
    }
}

void Btree::copyTree(Btree btree) {
    copyTreeRecursive(btree.root);
}

void Btree::copyTreeRecursive(node *leaf) {
    if(leaf != NULL)
    {
        copyTreeRecursive(leaf->left);
        copyTreeRecursive(leaf->right);
        this->insert(leaf->traveler);
    }
}

Btree::~Btree() {

}

int clear(char issue) {
    if (issue == '\n') {
        return 0;
    }
    else {
        while (issue != '\n') {
            issue = getchar();
        }
        return 1;
    }
}

int main()
{
    Btree binaryTree;
    while (true){
        int k;
        cout << "1. Show Tree \n2. Add travelers to the tree \n3. Rewrite tree by weight, show and delete \n4. Rewrite tree by ticket id, show and delete \n5. Search middle value\n";
        scanf("%i", &k);

        if(k == 1) {
            binaryTree.showTree();
            continue;
        }
        else if(k == 2){
            int numberOfElements;
            cout << "Input number of travelers: ";
            scanf("%i", &numberOfElements);

            for (int i = 0; i < numberOfElements; ++i) {
                Traveler traveler;
                cout << "Input lastname of the traveler: ";
                clear(getchar());
                scanf("%100[^\n]", traveler.lastName);
                clear(getchar());
                cout << "Input ticket id of the traveler: ";
                cin >> traveler.ticketId;
                cout << "Input baggage weight of the traveler: ";
                cin >> traveler.baggage.weight;
                cout << "Input quantity of baggage of the traveler: ";
                cin >> traveler.baggage.quantity;
                binaryTree.insert(traveler);

                cout << endl << "Traveler was added successfully \n\n\n";
            }
            continue;
        }
        else if(k == 3){
            if (binaryTree.Head == NULL){
                binaryTree.showTree();
                continue;
            }

            BtreeByWeight btreeByWeight;
            btreeByWeight.copyTree(binaryTree);
            btreeByWeight.showTree();

            cout << endl;
            binaryTree.destroy_tree();
            binaryTree.showTree();
            Btree newBinaryTree;
            binaryTree = newBinaryTree;
            continue;
        }
        else if(k == 4){
            if (binaryTree.Head == NULL){
                binaryTree.showTree();
                continue;
            }

            BtreeByTicketId btreeByTicketId;
            btreeByTicketId.copyTree(binaryTree);
            btreeByTicketId.showTree();

            cout << endl;
            binaryTree.destroy_tree();
            binaryTree.showTree();
            Btree newBinaryTree;
            binaryTree = newBinaryTree;
            continue;
            }
        else if(k == 5){
            binaryTree.search();
            continue;
        }
    }
}