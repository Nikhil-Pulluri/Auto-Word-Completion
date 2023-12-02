#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node 
{
    char data;
    bool end;
    vector<Node*> children;
};

Node* create(char c) 
{
    Node* newNode = new Node;
    newNode->data = c;
    newNode->end = false;
    return newNode;
}

Node* child_locator(Node* current, char c) 
{
    for (int i = 0; i < current->children.size(); i++) 
    { 
        Node* temp1 = current->children[i];
        if (temp1->data == c) 
        {
            return temp1;
        }
    }
    return NULL;
}

void insert(Node* root, string s) // Time Complexity: O(L), L = Length of the string
{
    Node* current = root;
    if (s.length() == 0) 
    {
        current->end = true; // an empty word
        return;
    }
    for (int i = 0; i < s.length(); i++) 
    {
        Node* child = child_locator(current, s[i]);
        if (child != NULL) 
        {
            current = child;
        }
        else 
        {
            Node* tmp = create(s[i]);
            current->children.push_back(tmp);
            current = tmp;
        }
        if (i == s.length() - 1)
            current->end = true;
    }
}

bool word_search(Node* root, string s) // Time Complexity: O(L), L = Length of the string
{
    Node* current = root;
    while (current != NULL) 
    {
        for (int i = 0; i < s.length(); i++) 
        {
            Node* temp1 = child_locator(current, s[i]);
            if (temp1 == NULL)
                return false;
            current = temp1;
        }
        if (current->end)
            return true;
        else
            return false;
    }
    return false;
}

void TRIE_Traversal(Node* current, char* s, vector<string>& res, bool& loop) // Time Complexity: O(k*h),
{                                                                            //  k = number of suggestions
    char k[100] = { 0 };                                                     // h = Height of the tree
    char aa[2] = { 0 };
    if (loop) 
    {
        if (current != NULL) 
        {
            if (current->end == true) 
            {
                res.push_back(s);
                if (res.size() >= 100)
                    loop = false;
            }
            vector<Node*> child = current->children;
            for (int j = 0; j < child.size() && loop; j++) 
            {
                strcpy(k, s);
                aa[0] = child[j]->data;
                aa[1] = '\0';
                strcat(k, aa);
                if (loop)
                {
                    TRIE_Traversal(child[j], k, res, loop);
                }
                    
            }
        }
    }
}

void auto_start(Node* root, string s, vector<string>& res) 
{
    Node* current = root;
    for (int i = 0; i < s.length(); i++) 
    {
        Node* tmp = child_locator(current, s[i]);
        if (tmp == NULL)
            return;
        current = tmp;                 
    }
    char c[100];
    strcpy(c, s.c_str());
    bool loop = true;
    TRIE_Traversal(current, c, res, loop);
    return;
}

void Dictionary_loading(Node* root, string fn) // Time Complexity: O(n*m)
{                                              // n = Number of words in the dictionary
    ifstream dictionary;                       // m = Average lenght of all the words in the dictionary
    dictionary.open(fn.c_str());
    if (!dictionary.is_open()) 
    {
        cout << "Could not open Dictionary file" << endl;
        return;
    }
    while (!dictionary.eof()) 
    {
        char s[100];
        dictionary >> s;
        insert(root, s);
    }
    dictionary.close();
    return;
}


int main() 
{
    Node* root = create(' ');
    char mode;
    cout << "Loading the dictionary file" << endl;
    auto start = high_resolution_clock::now();
    Dictionary_loading(root, "dictionary.txt");

    auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << "Total words in the dictionary: 235887" << endl;
                cout << "Execution time for loading the dixtioanry: " << duration.count() << " milliseconds\n" << endl << endl;
    while (1) 
    {
        cout << endl
            << endl;
        cout << "Welcome to the Auto Complete Application \n#The fastest searching Tool" << endl << endl;
        cout << "Interactive mode, press " << endl;
        cout << "1: Auto Complete Word Feature - Suggestion of words" << endl;
        cout << "2: Spell Checking Utility" << endl;
        cout << "3: Quit the application" << endl
            << endl;
        cin >> mode;

        switch (mode) 
        {
        case '1': 
        {
            string s;
            cout << "Enter the prefix word : ";
            cin >> s;
            auto start = high_resolution_clock::now();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            vector<string> listOfWords;
            auto_start(root, s, listOfWords);
                cout << "Auto complete :" << endl;
                for (int i = 0; i < listOfWords.size(); i++) {
                    cout << " \t     " << listOfWords[i] << endl;
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);

                cout << "Total words suggested : " << listOfWords.size() << endl;

                cout << "Execution time: " << duration.count() << " milliseconds\n" << endl << endl;

            char select;
            cout << "Do you wish to use the application? (y/n)" << endl;
            cin >> select;
            if(select == 'y')
            {
                cout << endl << endl << "Redirecting to the main menu.." << endl;
                continue;
            }
            else{
                cout << "Quiting the applciation" << endl;
                cout << "Thank you for using our services!" << endl;
                return 0;
            }
                
        }
        

        case '2':
        {
            string spell;
            cout << "Enter the word for spell checking: ";
            cin >> spell;

            auto start = high_resolution_clock::now();

            bool result = word_search(root, spell);

            if(result)
            {
                cout << "The entered word is correct!" << endl;
            }
            else
            {
                cout << "The entered word is incorrect!" << endl;
            }

            auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);

                cout << "Execution time: " << duration.count() << " milliseconds\n" << endl << endl;

            char select;
            cout << "Do you wish to use the application? (y/n)" << endl;
            cin >> select;
            if(select == 'y')
            {
                cout << endl << endl << "Redirecting to the main menu.." << endl << endl << endl;
                continue;
            }
            else{
                cout << "Quiting the applciation" << endl;
                cout << "Thank you for using our services!" << endl;
                return 0;
            }
        }

        case '3':
            delete root;
            return 0;
        default:
            cout << "Invalid input!";
            cout << "\nEnter either 1,2 or 3.." << endl;
            continue;
        }
    }
}