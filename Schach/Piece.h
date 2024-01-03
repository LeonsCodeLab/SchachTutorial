#pragma once
#include "PieceInfo.h"
#include <vector>

using namespace std;
class Piece
{
  private:
    Color color;
    Type type;

  public:
    Piece();
    Piece(Color, Type);
    Type getType();
    Color getColor();
};
