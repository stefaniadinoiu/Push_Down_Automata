#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <string>
#include "PDA.h"

/// am ales metoda de vidare a stivei si a cuvantului


int main()
{
    read_word();

    cout << word << " " << "\n";
    cout << word.length() << "\n";

    show_PDA();

    bool answer = false;

    stack <char> stackk;

    stackk.push('Z');

    PDA_method(PDA,stackk,first_state,answer,word,final_states);
    cout << "\n";

    if (answer)
        cout << "ACCEPTED!\n";
    else
        cout << "REJECTED!\n";
    return 0;
}
