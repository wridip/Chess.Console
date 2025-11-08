#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // For abs()
/*
// Function to print the board
void print_board(char board[8][8]) 
{
    printf("\n");
    for (int i = 0; i < 8; i++) 
    {
        printf("%d ", 8 - i); // Row numbers (8 to 1)
        for (int j = 0; j < 8; j++) 
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n"); // Column letters
}
*/


void print_board(char board[8][8])
{
    printf("\n");
    printf("    a   b   c   d   e   f   g   h\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", 8 - i); // Row numbers (8 to 1)

        for (int j = 0; j < 8; j++)
        {
            printf("| %c ", board[i][j]);
        }
        printf("| %d\n", 8 - i); // Row numbers on right side too
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
}

// Function to set up the chess board
void setup_board(char board[8][8]) 
{
    // Empty squares
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            board[i][j] = ' ';
        }
    }

    // Black pieces
    board[0][0] = 'r'; board[0][1] = 'n'; board[0][2] = 'b'; board[0][3] = 'q';
    board[0][4] = 'k'; board[0][5] = 'b'; board[0][6] = 'n'; board[0][7] = 'r';
    for (int j = 0; j < 8; j++) board[1][j] = 'p';

    // White pieces
    board[7][0] = 'R'; board[7][1] = 'N'; board[7][2] = 'B'; board[7][3] = 'Q';
    board[7][4] = 'K'; board[7][5] = 'B'; board[7][6] = 'N'; board[7][7] = 'R';
    for (int j = 0; j < 8; j++) board[6][j] = 'P';
}

// Function to check if a rook can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal
int check_rook_path(char board[8][8], int row1, int col1, int row2, int col2) 
{
    // Must move either horizontally or vertically
    if (row1 != row2 && col1 != col2) 
    {
        return 0;
    }

    // Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0;
    }

    // Horizontal move
    if (row1 == row2) 
    {
        if (col1 < col2) 
        {
            // Moving right
            for (int col = col1 + 1; col < col2; col++) 
            {
                if (board[row1][col] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
        else 
        {
            // Moving left
            for (int col = col1 - 1; col > col2; col--) 
            {
                if (board[row1][col] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
    }

    // Vertical move
    if (col1 == col2) 
    {
        if (row1 < row2) 
        {
            // Moving down
            for (int row = row1 + 1; row < row2; row++) 
            {
                if (board[row][col1] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
        else 
        {
            // Moving up
            for (int row = row1 - 1; row > row2; row--) 
            {
                if (board[row][col1] != ' ') 
                {
                    return 0; // Blocked
                }
            }
        }
    }

    // Check capture rules (cannot capture own piece)
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2])))) 
    {
        return 0;
    }

    return 1; // Valid rook move
}
//Function to check if a king can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal

int check_king_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	int row_diff = abs(row2 - row1);
	int col_diff = abs(col2 - col1);

	// Must move atleast one square, and at most one square in any direction
    if (row_diff <= 1 && col_diff <= 1 && (row1 != row2 || col1 != col2))
    {
        //Check if the destination square is occupied by own piece
        if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
        {
            return 0; // Cannot capture own piece
		}
		return 1; // Valid king move
    }
	return 0; // Invalid king move
}

// Function to check if a bishop can move from (row1, col1) to (row2, col2) on the chessboard
// Returns 1 if valid move, 0 if blocked or illegal

int check_bishop_path(char board[8][8], int row1, int col1, int row2, int col2)
{
    if (abs(row2 - row1) != abs(col2 - col1))
    {
        return 0; // Must move diagonally
    }
    if (row1 == row2 && col1 == col2)
    {
        return 0; // Same square move is invalid
    }
    // Determine the direction of movement
    int row_step = (row2 > row1) ? 1 : -1;
    int col_step = (col2 > col1) ? 1 : -1;

    //Start checking the path right after the starting square 
    int current_row = row1 + row_step;
    int current_col = col1 + col_step;

    while (current_row != row2)
    {
        if (board[current_row][current_col] != ' ')
        {
            return 0; // Blocked by another piece
        }
        current_row = current_row + row_step;
        current_col = current_col + col_step;
    }

	// Check if the destination square is occupied by own piece
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
    {
        return 0; // Cannot capture own piece
    }
    return 1; // Valid bishop move
}

// Function to check if a knight can move from (row1, col1) to (row2, col2) on the chessboard
int check_knight_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	//Knight moves in a "L" shape i.e. two squares in one direction and one square perpendicular
	//Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0; // Invalid move
	}
	//Knight can move in 8 possible ways
    int valid = (col2 == col1 + 1 && row2 == row1 - 2) ||
                (col2 == col1 + 2 && row2 == row1 - 1) ||
                (col2 == col1 + 2 && row2 == row1 + 1) ||
                (col2 == col1 + 1 && row2 == row1 + 2) ||
                (col2 == col1 - 1 && row2 == row1 + 2) ||
                (col2 == col1 - 2 && row2 == row1 + 1) ||
                (col2 == col1 - 2 && row2 == row1 - 1) ||
                (col2 == col1 - 1 && row2 == row1 - 2);
	if (!valid)
    {
                return 0; // Invalid knight move
	}


	// Check if the destination square is occupied by own piece
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2])))) 
    {
        return 0; // Cannot capture own piece
    }
	return 1; // Valid knight move
}


// Function to check if a queen can move from (row1, col1) to (row2, col2) on the chessboard
int check_queen_path(char board[8][8], int row1, int col1, int row2, int col2)
{
    if (row1 == row2 && col1 == col2) // Same square move is invalid
    {
        return 0; // Invalid move
    }
    //A queen moves like a rook or a bishop
    int valid = 0;
    if (row1 == row2 || col1 == col2) // Rook-like move
    {
        valid = check_rook_path(board, row1, col1, row2, col2);
    }
    else // Bishop-like move
    {
        valid = check_bishop_path(board, row1, col1, row2, col2);
    }
    return valid;
}

    /*
    This is an alternative way to check queen move without using rook and bishop functions
    if ((row1== row2 || col1 ==col2) || (abs(row2 - row1) == abs(col2 - col1)))
    {
    printf("Valid queen move\n");
    }
    else
    {
        printf("Invalid queen move\n");
    }
    */

    // Check if the destination square is occupied by own piece
/*
    if (board[row2][col2] != ' ' && ((isupper(board[row1][col1]) && isupper(board[row2][col2])) || (islower(board[row1][col1]) && islower(board[row2][col2]))))
    {
        return 0; // Cannot capture own piece
    }
    return 1;
*/
// Valid queen move
// Function to check if a pawn can move from (row1, col1) to (row2, col2) on the chessboard
// Function to check if a pawn move is valid
int check_pawn_path(char board[8][8], int row1, int col1, int row2, int col2)
{
	char piece = board[row1][col1];

	//Same square move is invalid
    if (row1 == row2 && col1 == col2) 
    {
        return 0;
	}
	//White pawn moves upward (row decreases)
    if (piece == 'P')
    {
		//Forward move by 1 (only if the square is empty)
        if (col1 == col2 && row2 == row1 - 1 && board[row2][col2] == ' ')
        {
			return 1; // Valid move
        }

		//Forward move by 2 (only if starting row = 6 and both squares are empty)
        if (col1 == col2 && row1 == 6 && row2 == 4 && board[5][col1] == ' ' && board[4][col1] == ' ')
        {
			return 1; // Valid move
        }

        //Diagonal capture by 1 (enemy must be black piece = lowecase)
        if ((col2 == col1 + 1 || col2 == col1 - 1) && row2 == row1 - 1 && board[row2][col2] != ' ' && islower(board[row2][col2]))
        {
			return 1; // Valid capture
        }
    }

    //Black pawn moves downward (row increases)
    else if (piece == 'p')
    {
        //Forward move by 1 (only if the square is empty)
        if (col1 == col2 && row2 == row1 + 1 && board[row2][col2] == ' ')
        {
            return 1; // Valid move
        }

        //Forward move by 2 (only if starting row = 1 and both squares are empty)
        if (col1 == col2 && row1 == 1 && row2 == 3 && board[2][col1] == ' ' && board[3][col1] == ' ')
        {
            return 1; // Valid move
        }

        //Diagonal capture by 1 (enemy must be white piece = uppercase)
        if ((col2 == col1 + 1 || col2 == col1 - 1) && row2 == row1 + 1 && board[row2][col2] != ' ' && isupper(board[row2][col2]))
        {
            return 1; // Valid capture
        }
    }

	// If none of the valid moves matched, return 0
	return 0; // Invalid pawn move
}

int is_king_in_check(char board[8][8], int is_white_king)
{
    int king_row = -1, king_col = -1;
	char king_char = is_white_king ? 'K' : 'k';

    // Find the king
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((is_white_king && board[i][j] == 'K') ||
                (!is_white_king && board[i][j] == 'k'))
            {
                king_row = i;
                king_col = j;
            }

    if (king_row == -1) return 0; // King missing (should not happen)
    //printf("DEBUG: Looking for attackers on king %c at %c%d\n", king_char, 'a' + king_col, 8 - king_row);

    // Check if any enemy piece can attack the king
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece = board[i][j];
            if (piece == ' ') continue;
            if (is_white_king)
            {
                if (isupper((unsigned char)piece)) continue;
            }
            else
            {
                if (islower((unsigned char)piece)) continue;
            }
            

            int can_attack = 0;
            switch (tolower(piece))
            {
            case 'p': can_attack = check_pawn_path(board, i, j, king_row, king_col); break;
            case 'r': can_attack = check_rook_path(board, i, j, king_row, king_col); break;
            case 'n': can_attack = check_knight_path(board, i, j, king_row, king_col); break;
            case 'b': can_attack = check_bishop_path(board, i, j, king_row, king_col); break;
            case 'q': can_attack = check_queen_path(board, i, j, king_row, king_col); break;
            case 'k': can_attack = check_king_path(board, i, j, king_row, king_col); break;
            }

            if (can_attack)
            {
                // printf("DEBUG: %c at %c%d attacks king at %c%d\n", piece, 'a' + j, 8 - i, 'a' + king_col, 8 - king_row);
                return 1; // King is attacked
            }
        }       
    }
    return 0;
}


// forward declarations of your functions
void setup_board(char board[8][8]);
void print_board(char board[8][8]);
int check_pawn_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_rook_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_knight_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_bishop_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_queen_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_king_path(char board[8][8], int row1, int col1, int row2, int col2);
int check_pawn_path(char board[8][8], int row1, int col1, int row2, int col2);

// Function to make a move on the board
void make_move(char board[8][8], int row1, int col1, int row2, int col2)
{
    char piece = board[row1][col1];
	char target = board[row2][col2];

    if (target != ' ')
    {
        printf("%c captures %c at %c%d\n", piece, target, 'a' + col2, 8 - row2);
	}
    board[row2][col2] = piece;  //move piece to new position
    board[row1][col1] = ' ';    //empty the old position
}

//helper function to convert chess notation to array indices
int parse_square(const char* sq, int* row, int* col) //took help from google 
{
    // expects like "e2"
    if (!sq || strlen(sq) < 2)  //is the pointer null or does the string have at least 2 characters?
    {
		return 0;
    }
	char file = tolower((unsigned char)sq[0]);  //First character is file (a-h)
	char rank = sq[1];                          //Second character is rank (1-8)
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return 0;
    *col = file - 'a';              // a->0 ... h->7
    *row = 8 - (rank - '0');        // '8'->0 ... '1'->7 (top row is 0)
    return 1;
}


int main() 
{
    char board[8][8];
    setup_board(board);

    int white_turn = 1; // white starts first

    while (1) 
    {
        print_board(board);

        if (white_turn)
        {
            printf("White's move (uppercase pieces):\n");
        }
        else
            printf("Black's move (lowercase pieces):\n");

        int row1, col1, row2, col2;
		char from_square[3], to_square[3];
        
        char input[50];
        printf("Enter your move (e.g., e2 e4): ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Error reading input. Please try again.\n\n");
            continue;
		}
        if (sscanf(input, "%2s %2s", from_square, to_square) != 2)
        {
            printf("Invalid input format! Use format like e2 e4.\n\n");
            continue;
        }
       //  printf("Enter your move (from_row from_col to_row to_col): ");
       //  scanf_s("%d %d %d %d", &row1, &col1, &row2, &col2);

		/* out of bounds check
        if (row1 < 0 || row1 > 7 || col1 < 0 || col1 > 7 ||
            row2 < 0 || row2 > 7 || col2 < 0 || col2 > 7)
        {
            printf("Move out of bounds! Rows and columns must be between 0 and 7.\n\n");
            continue;
		}
        */
        

		//using the helper function to parse input
        if (!parse_square(from_square, &row1, &col1) || !parse_square(to_square, &row2, &col2))
        {
            printf("Invalid input format! Use format like e2 e4.\n\n");
			continue;
        }

        char piece = board[row1][col1];

        //Check if the square is empty
        if (piece == ' ')
        {
            printf("No piece at that position!\n\n");
            continue;
        }
        if (white_turn && !isupper(piece))
        {
            printf("It's White's turn! Please move a white piece (uppercase).\n\n");
            continue;
        }
        if (!white_turn && !islower(piece))
        {
            printf("It's Black's turn! Please move a black piece (lowercase).\n\n");
            continue;
        }

        int valid = 0;

        //Validate move according to the piece type
        switch (tolower(piece)) {
        case 'p': valid = check_pawn_path(board, row1, col1, row2, col2); break;
        case 'r': valid = check_rook_path(board, row1, col1, row2, col2); break;
        case 'n': valid = check_knight_path(board, row1, col1, row2, col2); break;
        case 'b': valid = check_bishop_path(board, row1, col1, row2, col2); break;
        case 'q': valid = check_queen_path(board, row1, col1, row2, col2); break;
        case 'k': valid = check_king_path(board, row1, col1, row2, col2); break;
        default: 
            printf("No piece at that position!\n"); 
            continue;
        }

        if (valid)
        {
            char backup_from = board[row1][col1];
            char backup_to = board[row2][col2];

            make_move(board, row1, col1, row2, col2);

            // Step 1: Check if *this player* just put themselves in check
            if (is_king_in_check(board, white_turn))
            {
                // Undo move
                board[row1][col1] = backup_from;
                board[row2][col2] = backup_to;
                printf("Illegal move! Your king would be in check.\n\n");
                continue;
            }

            // Step 2: Switch turn (opponent will now move)
            white_turn = !white_turn;

            // Step 3: Immediately check if opponent is in check
            if (is_king_in_check(board, white_turn))
            {
                print_board(board);
                printf("Checkmate! %s wins!\n",
                    white_turn ? "White" : "Black");
                break; //  End game immediately
            }
        }
        else
        {
            printf("Invalid move! Try again.\n\n");
        }

      
    }
    return 0;
}
