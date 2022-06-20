#pragma once
#include <iostream>
using namespace std;

enum Color
{
    white,
    black,
    none // za puste pole
};
enum Type
{
    queen,
    pawn
};

struct Piece
{
    Color color; 
    Type type;
};

ostream &operator<<(ostream &s, const Piece &p)
{
    if (p.color == white)
    {
        if (p.type == queen)
        {
            s << "W"; // queen - duza litera
        }
        else
        {
            s << "w"; // pawn - mała litera
        }
    }
    else if (p.color == black)
    {
        if (p.type == queen)
        {
            s << "B"; // queen - duza litera
        }
        else
        {
            s << "b";
        }
    }
    else
    {
        s << " "; // puste pole
    }
    return s;
}
