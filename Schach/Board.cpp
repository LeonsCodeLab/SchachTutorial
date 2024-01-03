#include "Board.h"
Board::Board()
{
    
    gameBoard[0][1] = Piece(White, Pawn);
    gameBoard[1][1] = Piece(White, Pawn);
    gameBoard[2][1] = Piece(White, Pawn);
    gameBoard[3][1] = Piece(White, Pawn);
    gameBoard[4][1] = Piece(White, Pawn);
    gameBoard[5][1] = Piece(White, Pawn);
    gameBoard[6][1] = Piece(White, Pawn);
    gameBoard[7][1] = Piece(White, Pawn);

    gameBoard[0][0] = Piece(White, Rook);
    gameBoard[1][0] = Piece(White, Knight);
    gameBoard[2][0] = Piece(White, Bishop);
    gameBoard[3][0] = Piece(White, Queen);
    gameBoard[4][0] = Piece(White, King);
    gameBoard[5][0] = Piece(White, Bishop);
    gameBoard[6][0] = Piece(White, Knight);
    gameBoard[7][0] = Piece(White, Rook);

    gameBoard[0][7] = Piece(Black, Rook);
    gameBoard[1][7] = Piece(Black, Knight);
    gameBoard[2][7] = Piece(Black, Bishop);
    gameBoard[3][7] = Piece(Black, Queen);
    gameBoard[4][7] = Piece(Black, King);
    gameBoard[5][7] = Piece(Black, Bishop);
    gameBoard[6][7] = Piece(Black, Knight);
    gameBoard[7][7] = Piece(Black, Rook);

    gameBoard[0][6] = Piece(Black, Pawn);
    gameBoard[1][6] = Piece(Black, Pawn);
    gameBoard[2][6] = Piece(Black, Pawn);
    gameBoard[3][6] = Piece(Black, Pawn);
    gameBoard[4][6] = Piece(Black, Pawn);
    gameBoard[5][6] = Piece(Black, Pawn);
    gameBoard[6][6] = Piece(Black, Pawn);
    gameBoard[7][6] = Piece(Black, Pawn);
}

bool Board::isValidMove(int origin[2], int destination[2], Color currentcol)
{
    Piece piece = gameBoard[origin[0]][origin[1]];
    if (piece.getColor() != currentcol)
        return false;

    int delta[2];
    delta[0] = destination[0] - origin[0];
    delta[1] = destination[1] - origin[1];

    int pawnFirstMoveY;
    int movementDirection;
    if (piece.getColor() == White)
    {
        pawnFirstMoveY = 1;
        movementDirection = 1;
    }
    else
    {
        pawnFirstMoveY = 6;
        movementDirection = -1;
    }

    switch (piece.getType())
    {
    case King:
        return (delta[0] + delta[1] <= 2) && (delta[0] <= 1) && (delta[0] >= -1) && (delta[1] <= 1) &&
               (delta[1] >= -1) && (delta[0] + delta[1] >= -2);
        break;

    case Queen:
        return ((delta[0] == delta[1]) || (delta[0] == (0 - delta[1])) || (delta[0] == 0 && delta[1] != 0) ||
                (delta[1] == 0 && delta[0] != 0)) &&
               isPathClear(origin, destination);
        break;

    case Rook:
        return ((delta[0] == 0 && delta[1] != 0) || (delta[1] == 0 && delta[0] != 0)) &&
               isPathClear(origin, destination);
        break;

    case Bishop:
        return (delta[0] == delta[1] || delta[0] == (0 - delta[1])) && isPathClear(origin, destination);
        break;

    case Knight:
        return ((abs(delta[0]) == 1 && abs(delta[1]) == 2) || (abs(delta[0]) == 2 && abs(delta[1]) == 1)) &&
               isPathClear(origin, destination);
        break;

    case Pawn:
        if (delta[0] == 0)
        {
            return ((origin[1] == pawnFirstMoveY && delta[1] == 2 * movementDirection) ||
                    delta[1] == movementDirection) &&
                   gameBoard[destination[0]][destination[1]].getColor() == EmptyCol;
        }
        else
        {
            return delta[1] == movementDirection && abs(delta[0])==1 &&
                   (gameBoard[destination[0]][destination[1]].getColor() != piece.getColor());
        }
        break;

    default:
        return false;
        break;
    }

    return false;
}

bool Board::isPathClear(int origin[2], int destination[2])
{
    int direction[2];
    direction[0] = (destination[0] > origin[0]) ? 1 : (destination[0] < origin[0]) ? -1 : 0;
    direction[1] = (destination[1] > origin[1]) ? 1 : (destination[1] < origin[1]) ? -1 : 0;

    int current[2] = {origin[0] + direction[0], origin[1] + direction[1]};

    while (current[0] != destination[0])
    {
        if (gameBoard[current[0]][current[1]].getColor() != EmptyCol)
            return false;
        current[0] += direction[0];
        current[1] += direction[1];
    }
    return true;
}
bool Board::move(Color currentColor, string move)
{
    if (isValidNotation(move))
    {

        int origin[2];

        origin[1] = move[0] - 'a';
        origin[0] = move[1] - '1';

        int destination[2];
        destination[1] = move[2] - 'a';
        destination[0] = move[3] - '1';

        Piece piece = gameBoard[origin[0]][origin[1]];

        if (isValidMove(origin, destination, currentColor))
        {
            Piece possibleEnemy = gameBoard[destination[0]][destination[1]];
            if (possibleEnemy.getColor() == piece.getColor())
            {
                return false;
            }
            gameBoard[destination[0]][destination[1]] = piece;
            gameBoard[origin[0]][origin[1]] = Piece();
            int promoteCol = (piece.getColor() == White) ? 7 : 0;
            if (piece.getType() == Pawn && destination[1] == promoteCol)
                gameBoard[destination[0]][destination[1]] = Piece(piece.getColor(), Queen);
            return true;
        }
    }
    return false;
}
bool Board::isValidNotation(string str)
{
    if (str[0] > 'h' || str[0] < 'a')
        return false;
    if (str[1] < '1' || str[1] > '8')
        return false;
    if (str[2] > 'h' || str[0] < 'a')
        return false;
    if (str[3] < '1' || str[1] > '8')
        return false;
    return true;
}
void Board::printGameState()
{
    wstringstream ss;

    ss << "\n";

    ss << "   | a | b | c | d | e | f | g | h |\n";

    ss << "  +---------------------------------+\n";

    for (int i = 7; i >= 0; i--)
    {
        ss << " " << i + 1 << " |";

        for (int j = 0; j < 8; j++)
        {
            if (gameBoard[i][j].getColor() == EmptyCol)
            {
                ss << "   |";
            }
            else
            {
                wstring pieceChar = L"";

                switch (gameBoard[i][j].getType())
                {
                case King:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♔' : L'♚';
                    break;
                case Rook:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♖' : L'♜';
                    break;
                case Bishop:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♗' : L'♝';
                    break;
                case Queen:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♕' : L'♛';
                    break;
                case Knight:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♘' : L'♞';
                    break;
                case Pawn:
                    pieceChar = (gameBoard[i][j].getColor() == White) ? L'♙' : L'♟︎';
                    break;
                }

                ss << " " << pieceChar << " |";
            }
        }

        ss << "\n  +---------------------------------+\n";
    }

    ss << "\n";

    wcout << ss.str();
}

int Board::getWinner()
{
    bool kings[2];
    kings[0] = false;
    kings[1] = false;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (gameBoard[i][j].getColor() != EmptyCol && gameBoard[i][j].getType() == King)
            {
                if (!kings[0])
                    kings[0] = gameBoard[i][j].getColor() == Black;
                if (!kings[1])
                    kings[1] = gameBoard[i][j].getColor() == White;
            }
        }
    }
    if (kings[0] == kings[1])
        return 0;
    if (kings[0])
        return 1;
    return 2;
}
