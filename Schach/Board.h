#pragma once
#include "Piece.h"
#include "PieceInfo.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Board
{
  public:
    Board();
    bool move(Color, string);
    void printGameState();
    int getWinner();

  private:
    bool isPathClear(int[2], int[2]);
    Piece gameBoard[8][8];
    bool isValidNotation(string);
    bool isValidMove(int[2], int[2], Color);
};
