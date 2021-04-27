#pragma once

#include <iostream>

#include "logic.hpp"


void print_greeting()
{

	std::cout << "Welcome to Tic Tac Toe game!\n";
	
}

size_t widthis()
{
	size_t width = 0;
	
	std::cout << "Input field width (it must be odd natural number):";
	bool ok = false;
	while (!ok) {
		std::cin >> width;
		if (!std::cin) // Если введена не цифра (не интежер)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Error: please input number!\n";
        }
		else if ((width % 2 == 0) || (width < 3)) {
			std::cout << "Error: please input odd natural numbers!\n";
		}
		else ok = true;
	}
	return width;
}

Pos query_player_move(GameField &field)
{
    Pos pos;
    std::cout << "Please make a move: input two number in range [1-3]\n";
    bool ok = false;

    while (!ok)
    {
        std::cout << "> ";
        std::cin >> pos.x >> pos.y;
        pos.x--;
        pos.y--;
        if (!std::cin) // Если введена не цифра (не интежер)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Error: please input numbers!\n";
        }
        else if (!is_valid_pos(pos.x, pos.y))
        {
            std::cout << "Error: position is out of field bounds!\n";
        }
		else if (get_cell(field, pos.x, pos.y) != CellState::Empty){
			std::cout << "Error: the cell is busy. Please input two new numbers in range [1..3]\n";
		}
        else
        {
            ok = true;
        }
    }
    return pos;
}


Pos query_player_move_ch(CellState** field, size_t size)
{
    size_t a = size;
	Pos pos;
    std::cout << "Please make a move: input two number in range [1-3]\n";
    bool ok = false;

    while (!ok)
    {
        std::cout << "> ";
        std::cin >> pos.x >> pos.y;
        pos.x--;
        pos.y--;
        if (!std::cin) // Если введена не цифра (не интежер)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Error: please input numbers!\n";
        }
        else if (!is_valid_pos_ch(pos.x, pos.y, a))
        {
            std::cout << "Error: position is out of field bounds!\n";
        }
		else if (get_cell_ch(field, pos.x, pos.y, a) != CellState::Empty){
			std::cout << "Error: the cell is busy. Please input two new numbers in range [1..3]\n";
		}
        else
        {
            ok = true;
        }
    }
    return pos;
}

void print_cell(CellState cell)
{
    switch (cell)
    {
    case CellState::Empty:
        std::cout << ".";
        break;

    case CellState::X:
        std::cout << "X";
        break;

    case CellState::O:
        std::cout << "O";
        break;
    }
}

void print_field(GameField const &field)
{
    std::cout << "=======\n";
    for (size_t col = 0; col < FIELD_WIDTH; col++)
    {
        std::cout << "||";
        for (size_t row = 0; row < FIELD_WIDTH; row++)
        {
            print_cell(get_cell(field, row, col));
        }
        std::cout << "||\n";
    }
    std::cout << "=======\n";
}

void print_field_ch(CellState** field, size_t const size)
{
    for (size_t i = 0; i < size + 4; i++){
		std::cout << "=";
	}
	std::cout << "\n";
    for (size_t col = 0; col < size; col++)
    {
        std::cout << "||";
        for (size_t row = 0; row < size; row++)
        {
            
			print_cell(get_cell_ch(field, row, col, size));
			//field = 0;
			//std::cout << field;
			field += row + col;
		}
		std::cout << "||\n";
		//field += col;
    }
    for (size_t i = 0; i < size + 4; i++){
		std::cout << "=";
	}
	std::cout << "\n";
}

void print_game_outcome(TurnOutcome outcome) {
    switch (outcome)
    {
    case TurnOutcome::DRAW:
        std::cout << "It's a draw!\n";
        break;
    
    case TurnOutcome::X_WON:
        std::cout << "You won! Congrats!\n";
        break;

    case TurnOutcome::O_WON:
        std::cout << "You lost. Good luck next time.\n";
        break;

    default:
        break;
    }
}