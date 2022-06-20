#pragma once
#include "field.h"
#include "piece.h" 

struct Move
{
    field from, to;
    Piece capturedPiece;
    bool promotion = false;
};

ostream &operator<<(ostream &str, const Move &move)
{
    str << move.from << '-' << move.to;
    return str;
}
