#ifndef PDA_H_INCLUDED
#define PDA_H_INCLUDED

using namespace std;
ifstream f ("PDA.in");

string word;

int states_number , transitions_number , first_state , number_final_states;

vector <int> final_states;
vector< pair< int, pair< char,pair < char, vector< char > > > > > PDA[100];



void read_word()
{
    char letter , stack_symbol;
    string stack_alph;
    int x, q1, q2;

    f >> word;
    f >> states_number >> transitions_number;
    f >> first_state >> number_final_states;

    for (int i = 0; i < number_final_states; i++)
    {
        f >> x;
        final_states.push_back(x);
    }


    for (int i = 1; i <= transitions_number; i++)
    {
        vector <char> q;

        f >> q1 >> q2;
        f >> letter >> stack_symbol;
        f >> stack_alph;

        for (int j = 0; j < stack_alph.length(); j++)
        {
            q.push_back(stack_alph[j]);
        }

        PDA[q1].push_back(make_pair(q2,make_pair(letter,make_pair(stack_symbol,q))));
    }
}


void show_PDA()   /// displaying the PDA word from file
{
    for (int i = 0; i < states_number;i++)
    {
        for (int j = 0; j < PDA[i].size(); j++)
        {
            cout << i << " -> " << PDA[i][j].first << " : " <<PDA[i][j].second.first <<", " << PDA[i][j].second.second.first << " / ";

            for (int k = 0; k < PDA[i][j].second.second.second.size(); k++)
                cout<<PDA[i][j].second.second.second[k];

            cout<<"\n";
        }
    }
}


/* verifying function for the acceptance of the give word
-- recursive */

void PDA_method(vector< pair< int, pair< char,pair < char, vector< char > > > > > PDA[],
                stack <char> stackk, int state, bool &answer, string chr, vector <int> final_states)
{
    int i, poz;

    if(chr.length() == 0 && stackk.empty())  ///imposing the method we want to use:
                                            /// emptying the stack as long as the word
        for(i = 0; i < final_states.size(); i++)
            if(state == final_states[i])     /// if we reach the final state answer will become false
            {
                answer = true;
                return;
            }
    for(i=0;i < PDA[state].size();i++)
    {
        stack <char> aux;  /// using an additional stack

        aux = stackk;

        if (PDA[state][i].second.first == '0' && PDA[state][i].second.second.first == stackk.top())
        {
            aux.pop();

            for(poz = PDA[state][i].second.second.second.size() - 1; poz >= 0; poz--)

                if(PDA[state][i].second.second.second[poz] != '0')
                    aux.push(PDA[state][i].second.second.second[poz]);

            PDA_method(PDA,aux,PDA[state][i].first,answer,chr,final_states);
        }
        else

            if(PDA[state][i].second.first == chr[0] && PDA[state][i].second.second.first == stackk.top())
            {
                aux.pop();

                for(int poz = PDA[state][i].second.second.second.size() - 1; poz >= 0; poz--)

                    if(PDA[state][i].second.second.second[poz] != '0')
                        aux.push(PDA[state][i].second.second.second[poz]);

                PDA_method(PDA,aux,PDA[state][i].first,answer,chr.substr(1,chr.length()),final_states);
            }
    }
}


#endif // PDA_H_INCLUDED
