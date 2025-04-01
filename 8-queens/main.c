#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define WIDTH 8
#define HEIGHT 8
#define MAX_BACKTRACK 2000
#define CORRECT_BOARDS 4
#define CYAN_F        "\x1b[44m"
#define YELLOW        "\x1b[43m"
#define RESET_COLOR   "\x1b[0m"

int board[WIDTH][HEIGHT]; /*Guarda les reines*/
int temp_board[WIDTH][HEIGHT];
int possible_moves[WIDTH][HEIGHT]; /*Guarda a on pot anar la seguent reina*/
int backtrackHist[MAX_BACKTRACK][WIDTH][HEIGHT];
int x, y;
int num_move = 0;
int backTrackID;
int correctBoardID = 0;
int totalSolutions = 0;

void print_board();
void print_piece(char *piece);
int calculate_possible_moves();
int check_conflict();
int chose_next_move();
void clear_possible_moves();
void backtracking();
int checkIfPased();
void cloneBoard();
void safeCorrectBoard();
void printCorrectBoards();

int main()
{
	int n = 0;
	while (n<4000)
	{
		n++;
		calculate_possible_moves();
		if (chose_next_move()) {
			backtracking();
		}
		if (num_move == 8) {print_board(); totalSolutions++;}
	}
	printf("\nTotal Solutions: %d\n\n\n", totalSolutions);
	return 0;
}



void backtracking()
{
	for (y=0; y!=HEIGHT; y++)
	{
		for (x=0; x!=WIDTH; x++)
		{
			backtrackHist[backTrackID][x][y] = board[x][y];
		}
	}
	backTrackID++;
	for (x=0; x!=WIDTH; x++)
	{
		if (board[x][num_move-1])
			board[x][num_move-1] = 0;
	}
	num_move--;
}

void cloneBoard()
{
	int xx, yy;
	for (yy=0; yy!=HEIGHT; yy++)
	{
		for (xx=0; xx!=WIDTH; xx++)
		{
			temp_board[xx][yy] = board[xx][yy];
		}
	}
}

int checkIfPased()
{
	int t, xx, yy;
	int passed;
	for (t=0; t!=backTrackID; t++)
	{
		passed = 1;
		for (yy=0; yy!=HEIGHT; yy++)
		{
			for (xx=0; xx!=WIDTH; xx++)
			{
				if (temp_board[xx][yy] != 0 && temp_board[xx][yy] != backtrackHist[t][xx][yy])
				{
					passed = 0;
				}	
			}
		}
		if (passed){return 1;}
	}
	return 0;

}


int chose_next_move()
{
	int minium = 10;
	for (y=0; y!=HEIGHT; y++)
	{
		for (x=0; x!=WIDTH; x++)
		{
			if (possible_moves[x][y]) {
				cloneBoard();
				temp_board[x][y] = 1;
				if (!checkIfPased())
				{
					board[x][y] = 1;
					num_move++;
					return 0;
				}
			}
		}
	}

	return 1;	
}

int check_conflict()
{
	int bx, by;
	int conflict = 0;
	for (by=0; by!=HEIGHT; by++)
	{
		for (bx=0; bx!=WIDTH; bx++)
		{
			if (board[bx][by]) {
				if (bx == x || by == y)
				{
					return 1;
				} else if (((bx - by == x-y) && (bx != x && by != y)) || (bx + by == x+y) && (bx != x && by != y))
				{
					return 1;
				}


			}
		}
	}
	return 0;
}

void clear_possible_moves()
{
	int xx, yy;
	for (yy=0; yy!=HEIGHT; yy++)
	{
		for (xx=0; xx!=WIDTH; xx++)
		{
			possible_moves[xx][yy] = 0;
		}
	}
}


int calculate_possible_moves()
{
	y = num_move;
	clear_possible_moves();
	for (x=0; x!=WIDTH; x++)
	{
		if (!check_conflict()) /*Comporbar si la posició (x y) la toca una altre reina*/
		{
			possible_moves[x][y] = 1;
		}

	}
	return 0;
}

void print_piece(char *piece)
    {
        if ((x+y) % 2 == 0)
        {
            printf(CYAN_F "  %s  " RESET_COLOR, piece);
        }
        else
        {
            printf("  %s  ", piece);
        }
}

void print_board()
{

    printf("\n");
    for (y=0; y!=HEIGHT; y++)
    {
        printf("%d ", y);
        for (x=0; x!=WIDTH; x++)
        {
            if (board[x][y] != 0)
            {
                char piece[20] = "Q";
                print_piece(piece);
            } else if (possible_moves[x][y] != 0)
            {
                char piece[20] = "·";
				print_piece(piece);
            } else
            {
                char piece[20] = " ";
                print_piece(piece);
            }

        }
        printf("\n");
    }
    printf("  ");
    for (x=1; x<=WIDTH; x++) { printf("  %c  ", x+64); } /*Print lletres board*/
    printf("\n");
}
