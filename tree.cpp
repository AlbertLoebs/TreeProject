#include <iostream>

#include "WordTree.h"

using namespace std;

int main() 
{
    WordTree tree;
    string str = "";
    char choice;

    cout << "Menu:\na: add\nd: print number of distinct words\no: print the number of occurrrances\np: print tree alphabetically\nr: remove\nt: print total number of words inserted\nq: quit\n";

     do {
        cout << "Enter a choice: ";
        cin >> choice;
        
        if (choice == 'a') {
            cout << "Enter string to add : ";
            cin >> str;
            tree.add(str);
        } else if (choice == 'd') {
            cout << "Distinct: " << tree.distinctWords() << endl;
        } else if (choice == 'o') {
            cout << "Enter string to search : ";
            cin >> str;
            cout << "Total " << str << "s: " << tree.findOccurrences(str) << endl;
        } else if (choice == 'p') {
            cout << endl;
            tree.print();
        } else if (choice == 'r') {
            cout << "Enter string to remove : ";
            cin >> str;
            int BeforeDelete = tree.findOccurrences(str);

        if (BeforeDelete != 0) {
            cout << "Removing " << str << endl;
            tree.remove(str);
        }

        if (BeforeDelete == 0) {
            cout << "Removing " << str << endl;
            cout << str << " not found" << endl;
        }
        } else if (choice == 't') {
            cout << "Total: " << tree.totalWords() << endl;
        }
    } while (choice != 'q');

    return 0;
}
