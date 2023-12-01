#include <iostream>
#include <string>
using namespace std;


// pomocna funkcia na vytvorenie universe
string make_universe(int n) {
    string U;
    for (int i = 0; i <= n; i++) {
        U += to_string(i);
    }
    return U;
}


// vytvori jednoprvkovu mnozinu
string make_set(char x) {
    string x_str;
    x_str += x;
    return x_str;
}


// najde mnozinu, v ktorej sa nachadza prvok x
string* find(string x, string* sets) {
    for (int i = 0; !sets[i].empty(); i++) {
        if (sets[i].find(x) != string::npos) {
            return &sets[i];
        }
    }
    return nullptr;
}


// vrati dlzku pola mnozin, potrebne pri merge
int get_length(string* sets) {
    int i = 0;
    for(int j = 0; !sets[j].empty(); j++){
        i++;
    }
    return i;
}


// pomocna funkcia na vypis mnoziny, pouzival som pri debugovani
void print_set(string* set){
    int i = get_length(set);
    for (int j = 0; j < i; j++){
        cout << set[j] << " ";
    }
    cout << endl;
}


// spoji dve mnoziny
string* merge(string* p1, string* p2,string* sets) {

    //spojim prvky mnozin
    *p1 += *p2;
    int index_to_remove = p2 - sets;

    // prekopirujem ostatne mnoziny
    for (int i = index_to_remove; sets[i + 1] != ""; i++) {
        sets[i] = sets[i + 1];
    }

    // zistim dlzku noveho pola mnozin
    int i = get_length(sets);

    // vytvorim nove pole mnozin
    string* new_sets = new string[(i - 1)];
    for (int j = 0; j < i-1; j++){
        new_sets[j] = sets[j];
    }

    //zmazem stare pole mnozin
    delete[] sets;
    return new_sets;
}


// vrati najmensi prvok v mnozine, potrebne pre planovaci algoritmus
int small(string* set){
    char smallest = (*set)[0];
    return smallest - '0';
}










