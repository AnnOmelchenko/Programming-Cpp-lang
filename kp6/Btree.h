#ifndef BTREE_H
#define BTREE_H

 class Baggage{
public:
    int quantity;
    int weight;
};

class Traveler{
public:
    int ticketId;
    char lastName[100];
    Baggage baggage;
};

struct node
{
    Traveler traveler;
    node *left;
    node *right;
};

class Btree
{
public:
    node *Head;
    int AverageValue;
    int Quantity;
    int Sum;
    Btree();
    ~Btree();

    virtual void insert(Traveler traveler);
    void search();
    void destroy_tree();
    virtual void showTree();
    void copyTree(Btree btree);

protected:
    virtual void insert(Traveler traveler, node *leaf);
    node *root;
    void destroy_tree(node *leaf);
    virtual void show(node *leaf, int level);
    void search(node *leaf);
    void copyTreeRecursive(node *leaf);
};

class BtreeByTicketId : public Btree{
public:
    void insert(Traveler traveler, node *leaf) override;
    void insert(Traveler traveler) override;
    void show(node *leaf, int level) override;
    void showTree() override;
};

class BtreeByWeight : public Btree{
public:
    void insert(Traveler traveler, node *leaf) override;
    void insert(Traveler traveler) override;
    void show(node *leaf, int level) override;
    void showTree() override;
};
#endif
