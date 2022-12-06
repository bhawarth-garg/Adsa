// Binomial Heap

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int val;
    int degree;
    Node *child;
    Node *sib;
    Node *parent;
};

Node *newNode(int val)
{
    Node *temp = new Node;
    temp->data = val;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

// This function merge two Binomial Trees.
Node *mergeBinomialTrees(Node *b1, Node *b2)
{
    // Make sure b1 is smaller
    if (b1->data > b2->data)
        swap(b1, b2);

    // We basically make larger valued tree
    // a child of smaller valued tree
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

// This function perform union operation on two
// binomial heap i.e. l1 & l2
list<Node *> unionBionomialHeap(list<Node *> l1,
                                list<Node *> l2)
{
    // new heap after merging l1 & l2
    list<Node *> newheap;

    list<Node *>::iterator it1 = l1.begin();
    list<Node *>::iterator it2 = l2.begin();

    while (it1 != l1.end() && it2 != l2.end())
    {
        // if D(l1) <= D(l2)
        if ((*it1)->degree <= (*it2)->degree)
        {
            newheap.push_back(*it1);
            it1++;
        }
        // if D(l1) > D(l2)
        else
        {
            newheap.push_back(*it2);
            it2++;
        }
    }

    while (it1 != l1.end())
    {
        newheap.push_back(*it);
        it1++;
    }

    while (it2 != l2.end())
    {
        newheap.push_back(*it2);
        it2++;
    }
    return newheap;
}

// checking degree of each tree.

list<Node *> checkDegree(list<Node *> newheap)
{
    if (newheap.size() <= 1)
        return newheap;

    //<Node *> unique_heap;
    list<Node *>::iterator it1, it2, it3;
    it1 = it2 = it3 = newheap.begin();

    if (newheap.size() == 2)
    {
        it2 = it1;
        it2++;
        it3 = newheap.end();
    }

    else
    {
        it2++;
        it3 = it2;
        it3++;
    }

    while (it1 != newheap.end())
    {
        // last can not be repeated again
        if (it2 == newheap.end())
            it1++;

        // No need of merging
        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if (it3 != newheap.end())
                it3++;
        }

        // degree of three consecutive Binomial Tree are same in heap( leave the first one as it is)
        else if (it3 != newheap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }

        // degree of two Binomial Tree are same in heap
        else if ((*it1)->degree == (*it2)->degree)
        {
            Node *temp;
            *it1 = mergeBinomialTrees(*it1, *it2);
            it2 = newheap.erase(it2);
            if (it3 != newheap.end())
                it3++;
        }
    }
    return newheap;
}

// inserting a Binomial Tree into binomial heap
list<Node *> insertATreeInHeap(list<Node *> bheap, Node *root)
{
    list<Node *> temp;

    // inserting of node at 1st position.
    temp.push_front(root);

    // union operation
    temp = unionBionomialHeap(bheap, temp);

    return checkDegree(temp);
}

list<Node *> removeMinFromBHeap(Node *tree)
{
    list<Node *> heap;
    Node *temp = tree->child;
    Node *sibling;

    // making a binomial heap from Binomial Tree
    while (temp)
    {
        sibling = temp;
        temp = temp->sib;
        sibling->sib = NULL;
        heap.push_front(sibling);
    }
    return heap;
}

// inserting a key into the binomial heap
list<Node *> insert(list<Node *> head, int key)
{
    Node *temp = newNode(key);
    return insertATreeInHeap(head, temp);
}

// return pointer of minimum value Node
// present in the binomial heap
Node *getMin(list<Node *> bheap)
{
    list<Node *>::iterator it = bheap.begin();
    Node *temp = *it;
    while (it != bheap.end())
    {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node *> extractMin(list<Node *> bheap)
{
    list<Node *> newheap;
    Node *temp;

    // temp contains the pointer of minimum value
    // element in heap
    temp = getMin(bheap);
    list<Node *>::iterator it;
    it = bheap.begin();
    while (it != bheap.end())
    {
        if (*it != temp)
        {
            // inserting all Binomial Tree into new
            // binomial heap except the Binomial Tree
            // contains minimum element
            newheap.push_back(*it);
        }
        it++;
    }
    list<Node *> modified_heap;
    modified_heap = removeMinFromBHeap(temp);

    newheap = unionBionomialHeap(newheap, modified_heap);
    newheap = checkdegree(newheap);

    return newheap;
}

// print function for Binomial Tree
void printTree(Node *h)
{
    while (h)
    {
        cout << h->data << " ";
        printTree(h->child);
        h = h->sibling;
    }
}

// print function for binomial heap
void printHeap(list<Node *> bheap)
{
    list<Node *>::iterator it;
    it = bheap.begin();
    while (it != bheap.end())
    {
        printTree(*it);
        it++;
    }
}

int main()
{
    list<Node *> bheap;

    // Insert data in the heap
    bheap = insert(bheap, 10);
    bheap = insert(bheap, 20);
    bheap = insert(bheap, 30);

    cout << "Heap elements after insertion:\n";
    printHeap(bheap);

    Node *temp = getMin(bheap);
    cout << "\nMinimum element of heap "
         << temp->data << "\n";

    // Delete minimum element of heap
    bheap = extractMin(bheap);
    cout << "Heap after deletion of minimum element\n";
    printHeap(bheap);

    return 0;
}
