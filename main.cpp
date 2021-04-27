#include <iostream>
#include <cassert>

#include "logic.hpp"
#include "io.hpp"
#include "ai.hpp"
#define CHANGE

int main() {
    // Human is always X
    // AI is always O

    // while game is not over
    //  - read player input / run AI
    //  - apply move
    //  - process new game state
    //  - print turn outcome
char answer = 'y';
size_t size = 0;
	
    while (answer == 'y'){
        print_greeting();
/*
		size = widthis();
				
		CellState** map = init(size);
		print_field_ch(map, size);
		*/
        GameField field {};
        TurnOutcome outcome {};
        PlayerSign current_player = PlayerSign::X;
		
        do {
            Pos pos;
            if (current_player == PlayerSign::X) {
                pos = query_player_move(field);
            } else {
                pos = query_ai_move(field);
            }
            assert(set_cell(field, pos.x, pos.y, sign_to_cell(current_player)));

            outcome = check_turn_outcome(field);
            print_field(field);
            current_player = next_player(current_player);

        } while (outcome == TurnOutcome::CONTINUE);

        print_game_outcome(outcome);

        std::cout << "Do you want to play once more? (y/n)";
        std::cin >> answer;
        while ((answer != 'y') && (answer != 'n')) std::cin >> answer;
        if (answer == 'n') break;

    }
    return 0;
}