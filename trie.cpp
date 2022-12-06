#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node
{
    Node *links[26];
    bool flag = false;

    bool containsWord(char c)
    {
        return (links[c - 'a'] != NULL);
    }
    void AddWord(char c, Node *node)
    {
        links[c - 'a'] = node;
    }
    Node *getNode(char c)
    {
        return links[c - 'a'];
    }
    void setEnd()
    {
        flag = true;
    }
    bool isEnd()
    {
        if (flag == false)
        {
            return false;
        }
        return true;
    }
};

int main()
{
    int q;
    cout << "Enter no. of Queries: ";
    cin >> q;

    Node *root = new Node();
    vector<string> s(q);
    for (int i = 0; i < q; i++)
    {
        cin >> s[i];
    }

    for (int i = 0; i < q; i++)
    {
        cout << "Enter choice( 1 for search and 2 for insertion):";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            Node *node = root;
            int j;
            for (j = 0; j < s[i].length(); j++)
            {
                if (!node->containsWord(s[i][j]))
                {
                    break;
                }
                node = node->getNode(s[i][j]);
            }
            if (j < s[i].length() && !node->isEnd())
            {
                cout << s[i] << " is not present in Trie" << endl;
            }
            else
            {
                cout << s[i] << " is present in Trie" << endl;
            }
        }
        else if (choice == 2)
        {
            Node *node = root;
            for (int j = 0; j < s[i].length(); j++)
            {
                if (!node->containsWord(s[i][j]))
                {
                    node->AddWord(s[i][j], new Node());
                }
                node = node->getNode(s[i][j]);
            }
            node->setEnd();
            cout << s[i] << " is added to Trie" << endl;
        }
        else
        {
            cout << "Invalid Input" << endl;
            i--;
        }
    }
}