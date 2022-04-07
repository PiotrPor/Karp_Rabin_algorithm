#include <iostream>
#include <string>
#include <fstream>

int liczenie_hasza(std::string ciag, int podstawa, int dlugosc);
bool porownanie_brutal_force(std::string szukany, std::string fragment, int dlugosc);

int main()
{
    int ilosc_przypadkow_testowych = 0, odleglosc_od_poczatku = 0;
    int dlugosc_szukanego, dlugosc_pliku;
    int hasz_szukanego;
    int hasz_fragmentu;
    std::string szukany_ciag, nazwa_pliku, zawartosc_pliku, sprawdzany_fragment;
    std::ifstream wejsciowy;
    std::getline(std::cin, szukany_ciag); //pierwsza linijka zawiera ilosc przypadkow testowych
    ilosc_przypadkow_testowych = std::stoi(szukany_ciag); //zmiana na liczbe
    szukany_ciag.clear();
    while (ilosc_przypadkow_testowych > 0)
    {
        odleglosc_od_poczatku = -1; //taka wartosc poczatkowa jest potrzebna dla do{}while()
        std::getline(std::cin, nazwa_pliku);
        std::getline(std::cin, szukany_ciag);
        dlugosc_szukanego = szukany_ciag.size();
        hasz_szukanego = liczenie_hasza(szukany_ciag, 256, dlugosc_szukanego);
        //odczytanie tekstu, w ktorym szukamy ciagu znakow
        wejsciowy.open(nazwa_pliku);
        std::getline(wejsciowy, zawartosc_pliku);
        wejsciowy.close();
        //petla przechodzi po tekscie i porownuje kolejne wycinki tekstu ze wzorcem
        dlugosc_pliku = zawartosc_pliku.size();
        do {
            odleglosc_od_poczatku++;
            sprawdzany_fragment = zawartosc_pliku.substr(odleglosc_od_poczatku, dlugosc_szukanego); 
            hasz_fragmentu = liczenie_hasza(sprawdzany_fragment, 256, dlugosc_szukanego); //liczenie hasza
            if (hasz_szukanego == hasz_fragmentu)
            {
                //jesli hasze sie zgadzaja, to dokona porownania brutal force
                if (porownanie_brutal_force(szukany_ciag, sprawdzany_fragment, dlugosc_szukanego))
                {
                    std::cout << odleglosc_od_poczatku << " ";
                }
            }
        } while (odleglosc_od_poczatku + dlugosc_szukanego < dlugosc_pliku);
        //koniec tego przypadku
        std::cout << std::endl;
        ilosc_przypadkow_testowych -= 1;
    }
    return 0;
}

int liczenie_hasza(std::string ciag, int podstawa, int dlugosc)
{
    int a, jego_hasz = 0;
    jego_hasz = (int)ciag[0];
    for (a = 1; a < dlugosc; a++)
    {
        jego_hasz *= podstawa;
        jego_hasz += (int)ciag[a];
        while (jego_hasz > 244)
        {
            jego_hasz = jego_hasz % 151;
        }
    }
    return jego_hasz;
}

bool porownanie_brutal_force(std::string szukany, std::string fragment, int dlugosc)
{
    int a;
    for (a = 0; a < dlugosc; a++)
    {
        if (szukany[a] != fragment[a])
        {
            return false;
        }
    }
    return true;
}
