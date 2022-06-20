#pragma once
#include "piece.h"
#include "field.h"
#include "move.h"
#include <vector>
#include <cstdlib>

class Board
{
    Piece board[8][8];
    Color activePlayer = white;
    vector<Move> history;
    bool isMovePossible(field from, field to)
    {
        if (board[from.x][from.y].color != activePlayer) // czy wybrana figura jest figura aktywnego gracza
        {
            return false;
        }
        if (board[to.x][to.y].color == activePlayer) // czy na wybranym polu jest pion aktywnego gracza
        {
            return false;
        }
        if (board[from.x][from.y].type == pawn) // jeśli ruszamy sie pionem
        {

            if (abs(from.x - to.x) != 1)
            {
                return false;
            }
            if (to.y - from.y != (activePlayer == white ? 1 : -1)) // jezeli jest biały przyjmij 1 jesli nie to -1
            {
                return false;
            }
        }
        else //  ruch damki
        {
            if (abs(to.x - from.x) != abs(to.y - from.y))
            {
                return false;
            }

            int dirX = to.x - from.x > 0 ? 1 : -1;
            int dirY = to.y - from.y > 0 ? 1 : -1;
            int x = from.x + dirX;
            int y = from.y + dirY;

            while (x != to.x)
            {
                if (board[x][y].color != none)
                {
                    return false;
                }
                x += dirX;
                y += dirY;
            }
        }

        return true;
    }

public:
    Board()
    {
        for (int row = 7; row >= 0; row--) // wiersz
        {
            for (int col = 0; col < 8; col++) // kolumny
            {
                board[row][col] = Piece{none}; // pusta plansza
            }
        }
        for (int i = 0; i < 4; i++)
        {
            board[2 * i][0] = Piece{white, pawn};
            board[2 * i + 1][1] = Piece{white, pawn};
            board[2 * i][2] = Piece{white, pawn};

            board[2 * i + 1][5] = Piece{black, pawn};
            board[2 * i][6] = Piece{black, pawn};
            board[2 * i + 1][7] = Piece{black, pawn};
        }
    }

    bool movePiece(field from, field to)
    {
        if (isMovePossible(from, to))
        {
            bool promotion = ((to.y == 7 || to.y == 0) && board[from.x][from.y].type == pawn); // warunki promocji
            history.push_back({from, to, board[to.x][to.y], promotion});                       // historia ruchow
            board[to.x][to.y] = board[from.x][from.y];
            if (promotion)
            {
                board[to.x][to.y].type = queen; // zmienia sie w damke
            }

            board[from.x][from.y] = Piece{none};
            activePlayer = activePlayer == white ? black : white;
            return true;
        }

        else
        {
            cout << "Nie mozna wykonac takiego ruchu" << endl;
            return false;
        }
    }

    void undo() // cofanie ruchow
    {
        Move lastMove = history.back();
        history.pop_back(); // pop_back - usuwa ale nie zwraca
        board[lastMove.from.x][lastMove.from.y] = board[lastMove.to.x][lastMove.to.y];
        board[lastMove.to.x][lastMove.to.y] = lastMove.capturedPiece;
        if (lastMove.promotion)
        {
            board[lastMove.from.x][lastMove.from.y].type = pawn;
        }

        activePlayer = activePlayer == white ? black : white;
    }

    vector<Move> possibleMoves()
    {
        vector<Move> moves;
        for (int fromX = 0; fromX < 8; fromX++) // po x wspolrzednej z pola z ktorego sie ruszamy
        {
            for (int fromY = 0; fromY < 8; fromY++) // po y wspolrzednej z pola z ktorego sie ruszamy
            {
                for (int toX = 0; toX < 8; toX++) // po x wspolrzednej z pola na ktore sie ruszamy
                {
                    for (int toY = 0; toY < 8; toY++) // po y wspolrzednej z pola na ktore sie ruszamy
                    {
                        if (isMovePossible(field(fromX, fromY), field(toX, toY)))
                        {
                            moves.push_back({field(fromX, fromY), field(toX, toY), board[toX][toY]});
                        }
                    }
                }
            }
        }
        return moves;
    }

    int positionValue()
    {
        int value = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j].color == activePlayer)
                {
                    if (board[i][j].type == queen)
                    {
                        value += 5; // zwiekszam o 5 gdy damka
                    }
                    else
                    {
                        value += 1; // zwiekszamy o 1 gdy pion
                    }
                }
                else if (board[i][j].color != none)
                {
                    if (board[i][j].type == queen)
                    {
                        value -= 5; // zmniejszam o 5
                    }
                    else
                    {
                        value -= 1;
                    }
                }
            }
        }
        return value;
    }

    friend ostream &operator<<(ostream &s, const Board &b);
};

ostream &operator<<(ostream &s, const Board &b)
{
    for (int row = 7; row >= 0; row--) // wiersz
    {
        s << row + 1 << ' ';
        for (int col = 0; col < 8; col++) // kolumny
        {
            s << b.board[col][row];
        }
        s << endl;
    }
    s << "  ABCDEFGH";
    return s;
}