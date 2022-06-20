#include "piece.h"
#include "board.h"
#include "minimax.h"
#include <iostream>
using namespace std;

int main()
{
    Board board;
    while (!board.possibleMoves().empty())
    {
        cout << board << endl;
        string input;
        cout << "Podaj ruch (np. a1 b2 ): ";
        getline(cin, input); // używając cin wczytaj do input
        if (input.length() < 5)
        {
            cout << "Bledny input" << endl;
            continue;
        }
        char fromX = input[0];
        int fromY = input[1] - '0';
        char toX = input[3];
        int toY = input[4] - '0';
       if (fromX < 'a' || fromX > 'h' || fromY < 1 || fromY > 8 ||toX < 'a' || toX > 'h' || toY < 1 || toY > 8)
        {
            cout << "Bledny input" << endl;
            continue;
        }
        if (!board.movePiece(field(fromX, fromY), field(toX, toY))) // nasz ruch
        {
            continue;
        }
        
        Move opponentMove = bestMove(board); // ruch przeciwnika
        board.movePiece(opponentMove.from, opponentMove.to); 
    }

   
}