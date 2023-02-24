#pragma once
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include<sstream>
#include<map>
#include <set>

struct Bramka {
    string Typbramki;
    int IndexWyjscia;
    int wartoscWyjscia;
    vector<int> Numery;
};

bool AND(vector<bool>& inputs);
bool OR(vector<bool>& inputs);
bool NOT(vector<bool>& inputs);
bool NAND(vector<bool>& inputs);
bool NOR(vector<bool>& inputs);
bool XOR(vector<bool>& inputs);
bool XNOR(vector<bool>& inputs);

void czytanie_pliku_1(ifstream& plik1, vector<Bramka>& bramki, map<int, int>& mapa, vector<int>& OUTy);
int wylicz_wartosci(vector<Bramka> const& wektor, map<int, int>& mapa, int numer_wezla);
void czytanie_pliku_2(ifstream& plik1, vector<string> &wektor);
void przypisywanie_wartosci_wejsc(map<int, int>& mapa, string linia);
void zapisz_do_pliku(ofstream& plik, string linia, vector<int>& outy, map<int, int>& mapa);
void reset_mapy(map<int, int> &mapa, vector<int> &outy);