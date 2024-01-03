#include "Piece.h"
Piece::Piece() : color(EmptyCol), type(EmptyType) {};
Piece::Piece(Color color, Type type) : color(color), type(type){};
Type Piece::getType()
{
    return type;
}
Color Piece::getColor()
{
    return color;
}
