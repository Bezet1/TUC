#include "model.h"

int main(int argc, char* argv[])
{
    if (argc != 7) {
        cout << "zle uzycie";
        return 0;
    }

    string plik_Wejsciowy1;
    string plik_Wejsciowy2;
    string plik_Wyjsciowy;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-u") == 0) {
            plik_Wejsciowy1 = argv[i + 1];
        }
        if (strcmp(argv[i], "-i") == 0) {
            plik_Wejsciowy2 = argv[i + 1];
        }
        if (strcmp(argv[i], "-o") == 0) {
            plik_Wyjsciowy = argv[i + 1];
        }
    }

    //od nowa plik1
    ifstream plikwejsciowy1(plik_Wejsciowy1);

    //sprawdzanie czy plik1 wejsciowy zostal otwarty poprawnie
    if (!plikwejsciowy1.is_open() or !plikwejsciowy1.good()) {

        cout << "Plik1 nie zostal otwarty poprawnie" << endl;
        return 0;
    }

    ifstream plikwejsciowy2(plik_Wejsciowy2);

    //sprawdzanie czy plik2 wejsciowy zostal otwarty poprawnie
    if (!plikwejsciowy2.is_open() or !plikwejsciowy2.good()) {

        cout << "Plik2 nie zostal otwarty poprawnie" << endl;
        return 0;
    }

    ofstream plikWyjsciowy(plik_Wyjsciowy);

    //sprawdzanie czy plik1 wyjsciowy zostal otwarty poprawnie
    if (!plikWyjsciowy.is_open() or !plikWyjsciowy.good()) {

        cout << "Plik wyjsciowy nie zostal otwarty poprawnie" << endl;
        return 0;
    }

    vector<Bramka> bramki;
    map<int, int> wartosci_wezlow;
    vector<int> OUTy;
    vector<string> linie_plik2;

    czytanie_pliku_1(plikwejsciowy1, bramki, wartosci_wezlow, OUTy);

    czytanie_pliku_2(plikwejsciowy2, linie_plik2);
         
        
    for (auto &pojedyncza_linia : linie_plik2) {

        przypisywanie_wartosci_wejsc(wartosci_wezlow, pojedyncza_linia);
          
        for (auto out_poj : OUTy) {
            int koncowy = wylicz_wartosci(bramki, wartosci_wezlow, out_poj);
            wartosci_wezlow[out_poj] = koncowy;
        }

        zapisz_do_pliku(plikWyjsciowy, pojedyncza_linia, OUTy, wartosci_wezlow);

        reset_mapy(wartosci_wezlow, OUTy);
    }

    cout << "Poprawnie";
}