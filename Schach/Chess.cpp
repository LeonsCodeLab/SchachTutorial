
#include "Chess.h"
#include <corecrt_io.h>
#include <fcntl.h>

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_WTEXT);
    Board board = Board();
    bool whitePlays = true;
    while (board.getWinner() == 0)
    {
        board.printGameState();
        if (whitePlays)
            wcout << "Weiß: Bitte Zug eingeben" << endl;
        else
            wcout << "Schwarz: Bitte Zug eingeben" << endl;


        Color currentColor;
        if (whitePlays)
            currentColor = White;
        else
            currentColor = Black;

        string buff;
        cin >> buff;
        if (board.move(currentColor, buff))
            whitePlays =! whitePlays;
    }
    if (whitePlays)
        wcout << "Weiß gewinnt" << endl;
    else
        wcout << "Schwarz gewinnt" << endl;
}
