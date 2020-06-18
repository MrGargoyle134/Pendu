/**
(C) BILAL BOUAMER 2020, ALL RIGHTS RESERVED.
                  "PENDU"

A HANGMANGAME WRITTEN IN C++11 WITH THE WINDOWS API.

ALL THE WORDS USED IN THE FILE "MOTS.TXT" CAN BE DOWNLOADED AT:
http://www.siteduzero.com/uploads/fr/ftp/mateo21/cpp/dico.zip

ENJOY!
**/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <time.h>
#include <windows.h>

std::vector<std::string> words;
std::string word;

bool isword;

void ClearScreen() {
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hStdOut, & csbi)) return;
  DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
  COORD homeCoords = {
    0,
    0
  };
  DWORD count;
  if (!FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, & count)) return;
  if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, & count)) return;

  SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ResetPosition() {
  SetConsoleCursorPosition
    (GetStdHandle(STD_OUTPUT_HANDLE), COORD {
      0,
      0
    });
}


void loadwords()
{
    srand(time(NULL));
   std::ifstream file("mots.txt");

   if(file)
   {
      std::string line;

      while(getline(file, line))
      {
          words.push_back(line);
      }
   }
   else
   {
      std::cout << "ERREUR, impossible d'ouvrir le fichier." << std::endl;
   }

   int random = rand()%words.size();
   word = words[random];

}
std::string logo[6] =
{
"    ___    ___    _  _     ___    _   _     ",
"   | _ \\  | __|  | \\| |   |   \\  | | | | ",
"   |  _/  | _|   | .` |   | |) | | |_| |    ",
"  _|_|_   |___|  |_|\\_|   |___/   \\___/   ",
"_| ... |_|.....|_|.....|_|.....|_|.....|    ",
".`-0-0-'.`-0-0-'.`-0-0-'.`-0-0-'.`-0-0-.    ",
};

std::string Hangman[12] =
{
"+--------------------+",
"|....................|",
"|.........._____*....|",
"|..........|....|....|",
"|...............|....|",
"|...............|....|",
"|...............|....|",
"|...............|....|",
"|...............|....|",
"|...............|....|",
"|.........._____|_...|",
"+--------------------+",
};

void color(int col){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);}

int gamemode = 0;
bool game = true;

int main();

void Game()
{
    color(15);

     int choice = 0;
  std::string Gamemodes[2] = {
    ">Player vs CPU",
    ">Player vs Player",
  };
  while (!GetAsyncKeyState('Y')) {
    color(7);
    ResetPosition();
    if (GetAsyncKeyState(VK_UP)) {
      if (choice > 0) {
        choice--;
      }
    }
    if (GetAsyncKeyState(VK_DOWN)) {
      if (choice < 1) {
        choice++;
      }

    }
      if(choice == 0){color(127);}else{color(7);}
      std::cout << Gamemodes[0] << std::endl;
      if(choice == 1){color(127);}else{color(7);}
      std::cout << Gamemodes[1] << std::endl;
      color(7);
   Sleep(200);
   ResetPosition();
}
gamemode = choice;
ClearScreen();

if(gamemode == 0){loadwords();}else if(gamemode == 1){color(15);std::cout << "ENTRER UN MOT A DEVINER: ";
 std::cin >> word;}


char letter;

ClearScreen();

    std::string w = word;
for(int y = 0; y < word.size(); y++)
{
        w[y] = '_';
}
int Etat = 1;
int lettersguessed = 0;
int Percent;
while(game)
{
    Percent = lettersguessed*100/word.size();
    isword = false;
    //Display the hangman
    for(int a = 0; a < 12; a++)
    {
        for(int b = 0; b < 22; b++)
        {
            switch(Hangman[a][b])
            {
                case '\\': color(15);break;
                case '/': color(15);break;
                case '|': color(15);break;
                case '_': color(15); break;
                case '*': color(7); break;
                case '-': color(15);break;
                case '+': color(14);break;
                case '.': color(10);break;
                case 'O': color(12);break;
            }
            std::cout << Hangman[a][b];
        }
        std::cout << std::endl;
    }

    color(11);
    for(int i = 0; i < w.size();i++){std::cout << w[i] << " ";}

    std::cout << std::endl << std::endl;
    color(7);
    std::cout << "TU AS DEVINE ";
    color(12);
    std::cout << Percent << "%";
    color(7);
    std::cout << " DU MOT.\n";

    color(15);
    std::cout << "\nENTRER UNE LETTRE: ";
    std::cin >> letter;
    //Check if the letter is in the word

    for(int i = 0; i < word.size(); i++)
    {
        if(letter == word[i])
        {
            w[i] = letter;
            isword = true;
            lettersguessed++;
        }
    }
    if(isword == false){Etat++;}

    if(w == word)
    {
        //Win!
        std::cout << "TU A GAGNE!\n";
        system("PAUSE");
        game = false;
    }
    //Hangman

    if(Etat == 2)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|...............|....|";
Hangman[6]  = "|...............|....|";
Hangman[7]  = "|...............|....|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
    }
    else if(Etat == 3)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|..........|....|....|";
Hangman[6]  = "|..........|....|....|";
Hangman[7]  = "|...............|....|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
    }
    else if(Etat == 4)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|........+-|....|....|";
Hangman[6]  = "|..........|....|....|";
Hangman[7]  = "|...............|....|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
    }
    else if(Etat == 5)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|........+-|-+..|....|";
Hangman[6]  = "|..........|....|....|";
Hangman[7]  = "|...............|....|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
    }
    else if(Etat == 6)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|........+-|-+..|....|";
Hangman[6]  = "|..........|....|....|";
Hangman[7]  = "|........./.....|....|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
    }
    else if(Etat == 7)
    {
Hangman[0]  = "+--------------------+";
Hangman[1]  = "|....................|";
Hangman[2]  = "|.........._____*....|";
Hangman[3]  = "|..........|....|....|";
Hangman[4]  = "|..........O....|....|";
Hangman[5]  = "|........+-|-+..|....|";
Hangman[6]  = "|..........|....|....|";
Hangman[7]  = "|........./.\\...|...|";
Hangman[8]  = "|...............|....|";
Hangman[9]  = "|...............|....|";
Hangman[10] = "|.........._____|_...|";
Hangman[11] = "+--------------------+";
std::cout << "TU AS PERDU!\n";
std::cout << "LE MOT ETAIT: " << word << "." << std::endl;
system("PAUSE");
game = false;
    }
    ClearScreen();
}
}

void Intro()
{
    while(!GetAsyncKeyState(VK_SPACE))
    {
        ResetPosition();
    color(15);
    for(int i = 0; i < 6; i++){std::cout << std::endl;}
    for(int i = 0; i < 79; i++){std::cout << "*";}
    std::cout << "\n\n";
    for(int i = 0; i < 6; i++)
    {
        color(i+10);
        std::cout << "                   ";
        for(int a = 0; a < 43; a++)
        {
            std::cout << logo[i][a];
        }
        std::cout << std::endl;
    }
        std::cout << "\n";
    for(int i = 0; i < 79; i++){std::cout << "*";}
    std::cout << "\n\n";
    color(7);
    std::cout << "                               APPUYEZ SUR ESPACE\n";
    }
    ClearScreen();
    Game();
}

int main()
{
   Intro();
   return 0;
}
