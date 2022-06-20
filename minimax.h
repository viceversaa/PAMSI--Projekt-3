#include "board.h"
#include <limits>
using namespace std;

int minimax(Board &board, Move &move, int depth)
{
    board.movePiece(move.from, move.to);
    if (depth == 0) 
    {
        int value = board.positionValue();
        board.undo();
        return -value;
    }

    vector<Move> moves = board.possibleMoves();
    if (moves.empty()) // koniec gry
    {
        board.undo();
        cout << "Aktualny gracz przegrał" << endl;
        return 1000000; // aktualny gracz przegral
    }
    int maxResult = numeric_limits<int>::min();
    for (Move move1 : moves)
    {
        int result = minimax(board, move1, depth - 1);
        if (result > maxResult)
        {
            maxResult = result; // zwraca najlepszy wynik
        }
    }
    board.undo();
    return -maxResult;
}

Move bestMove(Board &board)
{
    vector<Move> moves = board.possibleMoves();
    Move bestMove = moves[0];
    int bestResult = minimax(board, bestMove, 4); // co nam da najlepszy wynik
    for (int i = 1; i < moves.size(); i++)
    {
        int result = minimax(board, moves[i], 4);
        if (result > bestResult)
        {
            bestResult = result;
            bestMove = moves[i]; // wykonanie ruchu
        }
    }
    return bestMove;
}