#pragma once

#include <random>
#include <algorithm>
#include "logic.hpp"

size_t get_empty_cells(size_t* free_cells, GameField const &field) {
    size_t *last_element = free_cells;
    size_t free_cells_num = 0;
    for (size_t i = 0; i < FIELD_WIDTH * FIELD_WIDTH; i++)
    {
        if (field[i] == CellState::Empty)
        {
            *last_element = i;
            last_element++;
            free_cells_num++;
        }
    }
    return free_cells_num;
}

size_t get_empty_cells_ch(size_t* free_cells, CellState** field, size_t size) {
    size_t *last_element = free_cells;
    size_t free_cells_num = 0;
    for (size_t i = 0; i < size * size; i++)
    {
        if (**field == CellState::Empty)
        {
            field += i;
			*last_element = i;
            last_element++;
            free_cells_num++;
        }
    }
    return free_cells_num;
}

Pos get_random_empty_cell(GameField const &field)
{
    size_t free_cells[FIELD_WIDTH * FIELD_WIDTH]{};
    size_t free_cells_num = get_empty_cells(free_cells, field);
    std::mt19937 algorithm;
    std::uniform_int_distribution<> dist(0, free_cells_num - 1);
    auto random_idx = dist(algorithm);
    size_t target_idx = free_cells[random_idx];

    return Pos{target_idx % FIELD_WIDTH, target_idx / FIELD_WIDTH};
}

Pos get_random_empty_cell_ch(CellState** field, size_t size)
{
    size_t free_cells[size * size]{};
    size_t free_cells_num = get_empty_cells_ch(free_cells, field,size);
    std::mt19937 algorithm;
    std::uniform_int_distribution<> dist(0, free_cells_num - 1);
    auto random_idx = dist(algorithm);
    size_t target_idx = free_cells[random_idx];

    return Pos{target_idx % size, target_idx / size};
}

Pos make_predictive_move(GameField const &field) {
    GameField test_field;
    std::copy_n(field, FIELD_WIDTH * FIELD_WIDTH, test_field);

    size_t free_cells[FIELD_WIDTH * FIELD_WIDTH]{};
    size_t free_cells_num = get_empty_cells(free_cells, field);

	
	
    for (size_t i = 0; i < free_cells_num; i++) {
        size_t free_cell_idx = free_cells[i];
        test_field[free_cell_idx] = CellState::O;
        if(check_turn_outcome(test_field) == TurnOutcome::O_WON) {
            return Pos{free_cell_idx % FIELD_WIDTH, free_cell_idx / FIELD_WIDTH};
        } 
		else if (check_turn_outcome(test_field) != TurnOutcome::O_WON) {
			test_field[free_cell_idx] = CellState::X;
			if(check_turn_outcome(test_field) == TurnOutcome::X_WON) {
				return Pos{free_cell_idx % FIELD_WIDTH, free_cell_idx / FIELD_WIDTH};
        	}
		}
        else test_field[free_cell_idx] = CellState::Empty;
    }
    return get_random_empty_cell(field);
}

Pos make_predictive_move_ch(CellState** field, size_t size) {

	CellState** test_field = new CellState*[size] {};
	for (size_t i = 0; i<size; i++){
		test_field[i] = new CellState[size] {};	
	}   
	
    std::copy_n(field, size * size, test_field);

    size_t free_cells[size * size]{};
    size_t free_cells_num = get_empty_cells_ch(free_cells, field, size);

	
	
    for (size_t i = 0; i < free_cells_num; i++) {
        size_t free_cell_idx = free_cells[i];
        **test_field = CellState::O;
		test_field += free_cell_idx;
		
        if(check_turn_outcome_ch(test_field,size) == TurnOutcome::O_WON) {
            return Pos{free_cell_idx % size, free_cell_idx / size};
        } 
		else if (check_turn_outcome_ch(test_field, size) != TurnOutcome::O_WON) {
			**test_field = CellState::X;
			test_field += free_cell_idx;
			
			if(check_turn_outcome_ch(test_field, size) == TurnOutcome::X_WON) {
				return Pos{free_cell_idx % size, free_cell_idx / size};
        	}
		}
        else {
			**test_field = CellState::Empty;
			test_field += free_cell_idx;
		}
    }
    return get_random_empty_cell_ch(field,size);
}

/*
// Попытка выиграть
Pos aiwinchk(Field &field) {
    GameField test_field;
    std::copy_n(field, FIELD_WIDTH * FIELD_WIDTH, test_field);
	
	size_t free_cells[FIELD_WIDTH * FIELD_WIDTH]{};
    size_t free_cells_num = get_empty_cells(free_cells, field);
	
   for (size_t y = 0; y < FIELD_WIDTH; y++) {
       for (size_t x = 0; x < FIELD_WIDTH; x++) {
           if (get_cell(field, pos.x, pos.y) != CellState::Empty) {
               set_cell(field, y, x, CellState::0);
               if (winchk(field, AI))
                   return 1;
               setval(field.map, y, x, EMPTY);
           }
       }
   }
   return 0;
}
*/
Pos query_ai_move(GameField const &field)
{
    // for every free cell
    //  - if we win by choosing this cell - do it!
    //  - if we prevent player of winning by choosing this cell - do it!
    //  - otherwise, pick random 

    return make_predictive_move(field);
}

Pos query_ai_move_ch(CellState** field, size_t size)
{
    // for every free cell
    //  - if we win by choosing this cell - do it!
    //  - if we prevent player of winning by choosing this cell - do it!
    //  - otherwise, pick random 

    return make_predictive_move_ch(field, size);
}