# SameGame
This project involves creating a program that executes commands in a single-player game called SameGame. The game is played on a rectangular board divided into cells arranged in rows and columns.

Game Rules
Each cell on the board is either empty or contains a block of a specific type.
The player can remove groups of adjacent blocks of the same type from the board.
A group of blocks can only be removed if it contains at least two blocks.
After removing a group, the board is rearranged:
Blocks above the empty spaces in each column fall down to fill the gaps.
Columns with no blocks are shifted to the left to fill any empty columns on the right.
Parameters
The game is parameterized by three positive integers:

ROWS: the number of rows on the board.
COLUMNS: the number of columns on the board.
TYPES: the number of different block types.
These parameters are defined as symbolic constants that can be specified using the compiler's -D option. Default values for these constants are provided as follows:

ROWS is set to 10.
COLUMNS is set to 15.
TYPES is set to 4.
Command Execution
The program is invoked with two arguments: the coordinates of the cell selected by the player. The first argument is the row number (counted from 0), and the second argument is the column number (counted from 0). The cell at row 0 and column 0 is in the top-left corner of the board.

The input data represents the current state of the board, and the output represents the board's state after executing the player's command.

Group Definition
A group of blocks on the board is defined by the following three conditions:

All blocks in the group are of the same type.
It is possible to move from any block in the group to any other block in the group by making steps only to adjacent blocks in the same row or column, without leaving the group.
The group cannot be expanded without violating conditions 1 and 2.
Board Reordering
After removing a group of blocks, the program reorders the board as follows:

It moves each block down by one position in its column if there is an empty space directly below it.
It shifts all non-empty columns to the left to fill any empty columns on the right.
Input Format
The data input to the program consists of rows of characters, representing the current state of the board. Each row ends with the representation of the end-of-line character '\n'.

The number of characters in each row is determined by the constant COLUMNS.

The character '.' represents an empty cell.
The digits '0' to '0' + TYPES - 1 represent different block types.
The board described by the input data is well-ordered. There is no block below an empty cell, and there are no non-empty columns to the left of an empty column.

Output Format
The output format of the program is the same as the input format, representing the new state of the board after executing the player's command.

Examples
Below are examples of the program's output when compiled with the command:

gcc @opcje -DWIERSZE=10 -DKOLUMNY=15 -DRODZAJE=4 zadanie2.c -o zadanie2
Input data files with example commands are provided as .in files, and the expected output for each example is provided as .out files.

For the input data in the file przyklad1_8_9.in, the correct output when the program is executed with arguments 8 and 9 is in przyklad1_8_9.out.
For the input data in the file przyklad2_9_4.in, the correct output when the program is executed with arguments 9 and 4 is in przyklad2_9_4.out.
For the input data in the file przyklad3_6_7.in, the correct output when the program is executed with arguments 6 and 7 is in przyklad3_6_7.out.
