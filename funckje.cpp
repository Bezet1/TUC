#include "model.h"

void przypisywanie_wartosci_wejsc(map<int, int> &mapa, string linia) {
    
    istringstream liniaStream(linia);
    string pojedynczy;
    while (!liniaStream.eof()) {
        liniaStream >> pojedynczy;
        int dwukropek = pojedynczy.find(":");
        string wezel = pojedynczy.substr(0, dwukropek);
        string wartosc = pojedynczy.substr(dwukropek + 1);

        mapa[stoi(wezel)] = stoi(wartosc);
    }
}

void reset_mapy(map<int, int> &mapa, vector<int> &outy) {
    for (auto &mapa_poj : mapa) {
        mapa_poj.second = 9;
    }
    
    for (auto &out_poj: outy) {
        mapa[out_poj] = 5;
    }

}

void czytanie_pliku_1(ifstream& plik1, vector<Bramka>& bramki, map<int, int>& mapa, vector<int>& OUTy) {
    string IN;
    string OUT;

    getline(plik1, IN);
    getline(plik1, OUT);
    
    istringstream INstream(IN);
    string pojedynczy;

    INstream >> pojedynczy;

    while (!INstream.eof()) {
        INstream >> pojedynczy;
        mapa[stoi(pojedynczy)] = 9;
    }
    
    istringstream OUTstream(OUT);
    OUTstream >> pojedynczy;

    while (!OUTstream.eof()) {
        OUTstream >> pojedynczy;
        mapa[stoi(pojedynczy)] = 5;

        OUTy.push_back(stoi(pojedynczy));
    }

    string kolejnelinie;
    while (!plik1.eof()) {
        getline(plik1, kolejnelinie);

        istringstream liniaStream(kolejnelinie);
        string pojedynczy;
        liniaStream >> pojedynczy;

        Bramka nowaBramka;
        nowaBramka.Typbramki = pojedynczy;

        while (!liniaStream.eof()) {

            liniaStream >> pojedynczy;

            if (mapa[stoi(pojedynczy)] != 5) {
                mapa[stoi(pojedynczy)] = 9;
            }
                
            nowaBramka.Numery.push_back(stoi(pojedynczy));
        }
        nowaBramka.Numery.pop_back();

        nowaBramka.IndexWyjscia = stoi(pojedynczy);
        nowaBramka.wartoscWyjscia = mapa[stoi(pojedynczy)];
        bramki.push_back(nowaBramka);
    }
}

void czytanie_pliku_2(ifstream& plik, vector<string> &wektor) {
    while (!plik.eof()) {
        string linia;
        getline(plik, linia);
        wektor.push_back(linia);
    }
}

// AND gate
bool AND(vector<bool>& inputs) {
    bool output = true;
    for (int i = 0; i < inputs.size(); i++) {
        output = output && inputs[i];
        //if (output == false)
           // break;
    }
    return output;
}

// OR gate
bool OR(vector<bool>& inputs) {
    bool output = false;
    for (int i = 0; i < inputs.size(); i++) {
        output = output || inputs[i];
        //if (output == true)
        // break;
    }
    return output;
}

// NOT gate
bool NOT(vector<bool>& inputs) {
    if (inputs.size() == 1) //NOT przyjmuje jedno wejœcie!
        return !inputs[0];
}

// NAND gate
bool NAND(vector<bool>& inputs) {
    return !AND(inputs);
}

// NOR gate
bool NOR(vector<bool>& inputs) {
    return !OR(inputs);
}

// XOR gate
bool XOR(vector<bool>& inputs) {
    int counter = 0;
    for (int i = 0; i < inputs.size(); i++) {
        if (counter > 1)
            break;
        if (inputs[i] == true)
            counter++;
    }
    if (counter == 1)
        return true;
    else
        return false;
}
// vector <int> liczby = {1,2,3}
// liczby.push_back(4);


// XNOR gate
bool XNOR(vector<bool>& inputs) {
    return !XOR(inputs);
}
void zapisz_do_pliku(ofstream& plik, string linia, vector<int>& outy, map<int,int>& mapa) {
    plik << "IN: " << linia << " OUT: ";
    for (auto &poj_out : outy) {
        plik << poj_out << ":" << mapa[poj_out] << " ";
    }
    plik << "\n";
   
}

int wylicz_wartosci(vector<Bramka> const& wektor, map<int, int>& mapa, int numer_wezla) {
    vector<bool> znanewejscia;
    set<int> zerojeden = { 0, 1 };
    if (mapa[numer_wezla] == 1 || mapa[numer_wezla] == 0) {
        return 2;
    }

    //szuka bramki z numerem podanym w funcki
    for (auto &pojedynczy_wektor : wektor) {
        if (pojedynczy_wektor.IndexWyjscia == numer_wezla) {
            //przechodzi po wejciach
            for (int wejscie : pojedynczy_wektor.Numery) {
                //sprawdza czy wejscie ma juz wartosc

                if (zerojeden.find(mapa[wejscie]) == zerojeden.end()) {
                    znanewejscia.clear();
                    int x = wylicz_wartosci(wektor, mapa, wejscie);
                }
            }

            for (int wejscie : pojedynczy_wektor.Numery) {
                znanewejscia.push_back(mapa[wejscie]);
            }

            if (!pojedynczy_wektor.Typbramki.compare("AND")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = AND(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("NAND")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = NAND(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("OR")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = OR(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("NOR")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = NOR(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("XOR")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = XOR(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("XNOR")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = XNOR(znanewejscia);
            }
            if (!pojedynczy_wektor.Typbramki.compare("NOT")) {
                mapa[pojedynczy_wektor.IndexWyjscia] = NOT(znanewejscia);
            }
            znanewejscia.clear();

        }

    }
    return mapa[numer_wezla];
}