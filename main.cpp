/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittajat:
 * Krista Poutanen
 * &
 * Mikko Kaukonen
 *
 * */


#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <sstream>
using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';



using Gameboard = vector<vector<int>>;
bool check_wins(Gameboard& gameboard);
bool check_adjacent_numbers(Gameboard& gameboard);


// Tämä funktio oli valmiina harjoitustyön ohjelmakoodipohjassa.
// Ei siis itse tehty!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.

unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Kysyy käyttäjältä pelilaudan täyttötapaa ja
// täyttää pelilaudan joko satunnaisesti
// tai ei-satunnaisesti käyttäjän syötteellä

void fill_board(Gameboard& gameboard){
    default_random_engine rand_gen;
    string start_input = "";
    string seed_value = "";


    while(start_input != "R" && start_input != "r" &&
          start_input != "I" && start_input != "i"){
    cout << "Select start (R for random, I for input): ";

    getline(cin, start_input);
        }

    if (start_input == "R" || start_input == "r"){
            cout << "Enter seed value: ";
            getline(cin, seed_value);

            // Täyttää pelilaudan satunnaisgeneraattorin antamilla luvuilla
            // Mikäli siemenluvun syöte ei numeerinen palauttaa nollan
            rand_gen.seed( stoi_with_check(seed_value) );
            uniform_int_distribution<int> distribution(1, BOARD_SIDE);
            for(unsigned int y = 0; y < BOARD_SIDE; ++y ) {
                vector<int> row;
                for(unsigned int x = 0; x < BOARD_SIDE; ++x ) {
                row.push_back(distribution(rand_gen));
        }
                gameboard.push_back( row );

        }
        }

    if (start_input == "I" || start_input == "i"){
        cout << "Input: ";
        string fill_input;
        getline(cin, fill_input);


        // Erottelee käyttäjän syötemerkkijonon erillisiksi
        // numeroiksi ja täyttää pelilaudan niillä.
        vector<int> row{};
        stringstream ss ( fill_input ) ;
        int number;
        while ( ss >> number )
          row.push_back( number );


        int number_of_subvectors = BOARD_SIDE;

        vector<int> subvector_array[number_of_subvectors];

        for (int k = 0; k < number_of_subvectors; ++k)
        {
            auto start_itr = next(row.cbegin(), k*BOARD_SIDE);
            auto end_itr = next(row.cbegin(), k*BOARD_SIDE + BOARD_SIDE);

            subvector_array[k].resize(BOARD_SIDE);
            copy(start_itr, end_itr, subvector_array[k].begin());

        }

        for (unsigned int i = 0 ; i < BOARD_SIDE ; i++)
        {
            gameboard.push_back(subvector_array[i]);
        }

        }

        }


// Tämä funktio oli valmiina harjoitustyön ohjelmakoodipohjassa.
// Ei siis itse tehty!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Tulostaa pelilaudan rivi- ja sarakenumeroineen.

void print(const Gameboard& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}


// Tarkistaa  annettujen koordinaattien perusteella
// tuleeko pelilaudalle 2 vierekkäistä tyhjää
// ruutua riville tai sarakkeelle. Palauttaa true,
// jos kaksi tyhjää ruutua koskettavat toisiaan vaaka-
// tai pystysuunnassa, muuten palauttaa false.

bool check_adjacent_numbers(Gameboard& gameboard,
                            int x_coordinate,
                            int y_coordinate){
    unsigned int x = x_coordinate;
    unsigned int y = y_coordinate;


        if (y > 0 && gameboard[y-1][x] == 0)
        {
            return true;
        }
        if(y < BOARD_SIDE - 1 && gameboard[y+1][x] == 0)
        {
            return true;
        }
        if (x > 0 && gameboard[y][x-1] == 0)
        {
            return true;
        }
        if(x < BOARD_SIDE - 1 && gameboard[y][x+1] == 0)
        {
            return true;
        }


           return false;
       }


//Tarkistaa ettei pelilaudalla ole irrallaan olevia
// numeron sisältäviä ruutuja. Palauttaa true, jos
// tällaisia ruutuja löytyy, muuten palauttaa false.

bool check_isolated_numbers(Gameboard& gameboard){
    for (unsigned int i = 0; i < gameboard.size(); i++)
    {
           for (unsigned int j = 0; j < gameboard[i].size(); j++)
           {
               if (gameboard[i][j] != 0)
               {
                   if ((i == 0 || gameboard[i-1][j] == 0)&&
                       (i == BOARD_SIDE - 1 || gameboard[i+1][j] == 0)&&
                       (j == 0 || gameboard[i][j-1] == 0)&&
                       (j == BOARD_SIDE - 1 || gameboard[i][j+1] == 0))
                                {
                                return true;


                        }

                }
            }


    }
       return false;
}


// Kysyy käyttäjältä poistettavan ruudun koordinaatit,
// tarkistaa ne ja poistaa ruudun
// sekä tulostaa muuttuneen pelilaudan.
// Tarkistaa muiden funktioiden avulla voitto ja tappio tilanteet

void playing_game(Gameboard& gameboard) {
    string coordinate_x = "";
    string coordinate_y = "";
    int x_coordinate = 0;
    int y_coordinate = 0;
    int board_side = BOARD_SIDE;


    bool continue_asking = true;
    while (continue_asking == true)
    {
        cout << "Enter removable element (x, y): ";
        cin >> coordinate_x;
        if (coordinate_x == "Q" or coordinate_x == "q")
         {
            cout << "Quitting" << endl;
            continue_asking = false;
         }


        else {
            cin >> coordinate_y;
            x_coordinate = stoi_with_check(coordinate_x);
            y_coordinate = stoi_with_check(coordinate_y);

            if (x_coordinate < 1 or x_coordinate > board_side or
             y_coordinate < 1 or y_coordinate > board_side )
                {
                  cout << "Out of board" << endl;
                  continue;
                }
                  else
                      {
                      x_coordinate = x_coordinate - 1;
                      y_coordinate = y_coordinate - 1;
                      if (gameboard[y_coordinate][x_coordinate] == 0)
                      {
                          cout << "Already removed" << endl;

                        }
                      else
                        {
                          gameboard[y_coordinate][x_coordinate] = 0;
                                               print(gameboard);
                                                 }
                                           }

                            if (check_adjacent_numbers(gameboard,
                             x_coordinate, y_coordinate ) == true){
                                cout << "You lost" << endl;
                                continue_asking = false;}

                            else if (check_isolated_numbers(gameboard) == true){
                                cout << "You lost" << endl;
                                continue_asking = false;}

                            else if (check_wins(gameboard) == true){
                                cout << "You won" << endl;
                                continue_asking = false;}
                                          }
                            }



}


// Tarkistaa onko pelaaja voittanut pelin, palauttaa
// true, jos pelaaja voitti ja false, jos pelaaja ei
// voittanut.

bool check_wins(Gameboard& gameboard)
{
    for (unsigned int i = 0; i < gameboard.size(); i++)
    {
           for (unsigned int j = 0; j < gameboard[i].size(); j++)
           {
               if (gameboard[i][j] != 0)
               {
                    for (unsigned int k = 0; k < gameboard[i].size(); k++)
                    {
                        if (k != j && gameboard[i][j] == gameboard[i][k])
                        {
                            return false;
                            }
                    for (unsigned int k = 0; k < gameboard.size(); k++)
                    {
                       if (k != i && gameboard[i][j] == gameboard[k][j])

                                {
                                return false;
                                }
                            }
                        }



                }
            }

        }

       return true;
    }




int main()
{
    Gameboard gameboard;
    fill_board(gameboard);
    print(gameboard);
    playing_game(gameboard);


    return 0;
}
