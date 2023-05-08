#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <cstring>

using namespace std;

struct node {
    char letter;
    vector<node*> children;
    node(char l)
    {
        letter = l;
    }
};

void add_word(char *word, node *slownik);
bool spell_check(const char *word, node *dict);
node *build_dict(FILE *infile);

int main(int argc, char** argv) {
    FILE *infile;
    if (argc == 2)
    {
        infile = fopen(argv[1], "r");
    } else {
        infile = fopen("slownik.txt", "r");
    }
    if (infile == nullptr)
    {
        return 1;
    }
    node *slownik = build_dict(infile);
    cout << spell_check("kot", slownik) << endl;
    return 0;
}

void add_word(char *word, node *slownik)
{
    bool letter_found = false;
    node *curr_node = slownik;
    node* new_letter;
    for (int i = 0; word[i] != '\0'; i++)
    {
        letter_found = false;
        for(int j = 0; j < curr_node->children.size(); j++)
        {
            if (curr_node->children[j]->letter == word[i])
            {
                letter_found = true;
                curr_node = curr_node->children[j];
                break;
            }
        }
        if (!letter_found)
        {
            new_letter = new node(word[i]);
            curr_node->children.push_back(new_letter);
            curr_node = new_letter;
        }
    }
    new_letter = new node('\0');
    curr_node->children.push_back(new_letter);
}

node *build_dict(FILE *infile)
{
    char buffer[40];
    node *slownik = new node('@');
    while(fscanf(infile, "%s", &buffer) != EOF)
    {
        add_word(buffer, slownik);
    }
    return slownik;
}

bool spell_check(const char *word, node *dict)
{
    node *curr_node = dict;
    bool found;
    int word_len = strlen(word);
    for (int i = 0; i <= word_len; i++){
        int children_size = curr_node->children.size();
        found = false;
        for (int j = 0; j < children_size; j++)
        {
            if(curr_node->children[j]->letter == word[i])
            {
                found = true;
                curr_node = curr_node->children[j];
                break; 
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}