#include <iostream>

//------------------------------------------------------------------------------
//Constants
//------------------------------------------------------------------------------
const int BLACK = 0;
const int WHITE = 1;
const int BOARD_SIZE = 8;
const char BLACK_PIECE = '@';
const char WHITE_PIECE = 'O';

//------------------------------------------------------------------------------
//Typedefs
//------------------------------------------------------------------------------
typedef char Board[BOARD_SIZE][BOARD_SIZE];

//------------------------------------------------------------------------------
//Function Prototypes
//------------------------------------------------------------------------------
void help();
void play();
void init(Board);
void draw(Board);
void test_draw();
int getRow(char row);
int getCol(char col);
void performFlip(char currentPiece, char oppositePiece, Board board, bool turn,
                 int col, int row);
void getCurrentPiece(bool turn, char& currentPiece, char& oppositePiece);
bool isValidMove(int row, int col, Board board, int validMoves,
                 int validCol[100], int validRow[100]);
bool isPass(int validMoves, int& passValue);
bool isInputQuit(char input0, char input1);
bool isValidPositionAt(bool turn, Board board, int row, int col,
                       char currentPiece, char oppositePiece);
bool isValidPositionAtNorth(bool turn, Board board, int row, int col,
                            char oppositePiece, char currentPiece);
bool isValidPositionAtSouth(bool turn, Board board, int row, int col,
                            char oppositePiece, char currentPiece);
bool isValidPositionAtEast(bool turn, Board board, int row, int col,
                           char oppositePiece, char currentPiece);
bool isValidPositionAtWest(bool turn, Board board, int row, int col,
                           char oppositePiece, char currentPiece);
bool isValidPositionAtNorthEast(bool turn, Board board, int row, int col,
                                char oppositePiece, char currentPiece);
bool isValidPositionAtNorthWest(bool turn, Board board, int row, int col,
                           char oppositePiece, char currentPiece);
bool isValidPositionAtSouthEast(bool turn, Board board, int row, int col,
                           char oppositePiece, char currentPiece);
bool isValidPositionAtSouthWest(bool turn, Board board, int row, int col,
                           char oppositePiece, char currentPiece);
void getValidPositions(bool turn, Board board, int validCol[100], int validRow[100],
                       int& validLen);
int main()
{
    //test_draw();
    //--------------------------------------------------------------------------
    //Menu and options
    //--------------------------------------------------------------------------
    char option;
    bool quit = false;
    while (!quit)
    {
        std::cout << "Welcome to Super Othello Version 0.1\n"
                  << "by Caleb Fischer\n\n";
        std::cout << "[?]   Help\n"
                  << "[P/p] PLay a new game\n"
                  << "[L/l] Load a previous game\n"
                  << "[S/s] Setup the board\n"
                  << "[Q/q] Quit\n"
                  << "Enter option: ";
        std::cin >> option;
        switch (option)
        {
            case '?':
                help();
            break;

            case 'p':
            case 'P':
                play();
                break;
                
            case 'l':
            case 'L':
                std::cout << "\nL/l feature to be implemented soon\n"
                          << std::endl;
                break;

            case 's':
            case 'S':
                std::cout << "\nS/s: to be implemented soon\n" << std::endl;
                break;

            case 'q':
            case 'Q':
                std::cout << "\nThanks for playing Super Othello Version 0.1"
                          << std::endl;
                quit = true;
        }
    }
}

//------------------------------------------------------------------------------
//Prints the help screen and example board
//------------------------------------------------------------------------------
void help()
{
    std::cout << "\nThe official rules can be found at\n"
              << "http://en.wikipedia.org/wiki/Reversi\n\n"
              << "The Othello board is set up in the following manner\n\n"
              << "  ABCDEFGH\n"
              << " +--------+\n"
              << "1|        |1\n"
              << "2|        |2\n"
              << "3|        |3\n"
              << "4|   O@   |4\n"
              << "5|   @O   |5\n"
              << "6|        |6\n"
              << "7|        |7\n"
              << "8|        |8\n"
              << " +--------+\n"
              << "  ABCDEFGH\n\n"
              << "BLACK plays @ and WHITE plays O. Players take turn in"
              << "entering\n"
              << "moves. The first player to enter a move is BLACK. To place a"
              << "@\n"
              << "at row 6 and column E, BLACK enters 6E. The result of the"
              << "move\n"
              << "is\n\n"
              << "  ABCDEFGH\n"
              << " +--------+\n"
              << "1|        |1\n"
              << "2|        |2\n"
              << "3|        |3\n"
              << "4|   O@   |4\n"
              << "5|   @@   |5\n"
              << "6|    @   |6\n"
              << "7|        |7\n"
              << "8|        |8\n"
              << " +--------+\n"
              << "  ABCDEFGH\n\n"
              << "Note that the WHITE piece at E5 is now a BLACK piece.\n\n";
}

//------------------------------------------------------------------------------
//The play function is responsible for checking validation of moves and
//switching turns
//------------------------------------------------------------------------------
void play()
{
    Board board;
    init(board);
    char input[100];
    bool turn = BLACK;
    bool quit = 0;
    while (!quit)
    {
        //----------------------------------------------------------------------
        //Input rows as characters A-H - 41 for 0-7 and columns as integers 1-8
        // - 1 for 0-7
        //----------------------------------------------------------------------
        int row = 0, col = 0;
        draw(board);
        
        //----------------------------------------------------------------------
        //Black's Turn.  getRow() and getCol() get the row and column numbers.
        //isValidMove checks if the move is valid and returns a bool value.
        //----------------------------------------------------------------------
        int passValue = 0;
        bool isValid = 0;
        while (!turn)
        {
            int validCol[100] = {0}, validRow[100] = {0}, validMoves = 0;
            char currentPiece = BLACK_PIECE, oppositePiece = WHITE_PIECE;
            getCurrentPiece(turn, currentPiece, oppositePiece);
            getValidPositions(turn, board, validCol, validRow, validMoves);
            
            //std::cout << "Valid Moves: " << validMoves;
            std::cout << "BLACK's turn: ";
            if(isPass(validMoves, passValue))
            {
                std::cout << "No valid moves\n";
                turn = WHITE;
            }
            
            std::cin >> input;
            quit = isInputQuit(input[0], input[1]);
            if(quit) break;
            
            col = getCol(input[0]);
            row = getRow(input[1]);
            isValid = isValidMove(col, row, board, validMoves, validCol,
                                  validRow);
            if (isValid)
            {
                performFlip(currentPiece, oppositePiece, board, turn, col, row);
                board[col][row] = BLACK_PIECE;
                turn = WHITE;
            }
            else
            {
                std::cout << "Invalid position" << '\n';
            }
        }
        draw(board);
        
        //----------------------------------------------------------------------
        //White's Turn
        //----------------------------------------------------------------------
        while (turn)
        {
            int validCol[100] = {0}, validRow[100] = {0}, validLen = 0, validMoves = 0;
            char currentPiece = BLACK_PIECE, oppositePiece = WHITE_PIECE;
            getValidPositions(turn, board, validCol, validRow, validMoves);
            getCurrentPiece(turn, currentPiece, oppositePiece);
            
            std::cout << "WHITE's turn: ";
            if(isPass(validMoves, passValue))
            {
                std::cout << "No valid moves\n";
                turn = BLACK;
            }
            
            std::cin >> input;
            quit = isInputQuit(input[0], input[1]);
            if(quit) break;
            
            col = getCol(input[0]);
            row = getRow(input[1]);
            isValid = isValidMove(col, row, board, validMoves, validCol,
                                  validRow);
            if (isValid)
            {
                performFlip(currentPiece, oppositePiece, board, turn, col, row);
                board[col][row] = WHITE_PIECE;
                turn = BLACK;
            }
            else
            {
                std::cout << "Invalid position" << '\n';
            }
        }
    }
}

// Function to test the draw() function
/*void test_draw()
{
    std::cout << "Testing draw() function ...\n";
    init(board);
    draw(board);
    board[0][0] = '@'; // put '@' at row 0, column 0
    draw(board);
}
*/

//------------------------------------------------------------------------------
//Init initializes the board to blank spaces and pieces in the center
//------------------------------------------------------------------------------
void init(Board board)
{
    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            board[col][row] = ' ';
        }
    }
    board[3][3] = WHITE_PIECE;
    board[3][4] = BLACK_PIECE;
    board[4][3] = BLACK_PIECE;
    board[4][4] = WHITE_PIECE;
}

//------------------------------------------------------------------------------
//The draw function draws the header, footer, and board for every time the
//board is needed.  colLetter starts at A and rows at 1
//------------------------------------------------------------------------------
void draw(Board board)
{
    //Print header
    char colLetter = 65;
    std::cout << "\n  ";
    for (int header = 0; header < BOARD_SIZE; ++header)
    {
        std::cout << colLetter;
        ++colLetter;
    }
    std::cout << '\n' << " +";

    for (int header = 0; header < BOARD_SIZE; ++header)
    {
        std::cout << '-';
    }
    std::cout << "+\n";
    
    //Print board
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        std::cout << row + 1 << '|';
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            std::cout << board[col][row];
        }
        std::cout << '|' << row + 1 << '\n';
    }
    
    //Print footer
    std::cout << " +";
    for (int footer = 0; footer < BOARD_SIZE; ++footer)
    {
        std::cout << '-';
    }
    std::cout << "+\n";
    
    colLetter = 65;
    std::cout << "  ";
    for (int footer = 0; footer < BOARD_SIZE; ++footer)
    {
        std::cout << colLetter;
        ++colLetter;
    }
    std::cout << "\n\n";
}

int getRow(char row)
{
    return row - 49;
}

int getCol(char col)
{
    return col - 65;
}

bool isInputQuit(char input0, char input1)
{
    if (input0 == 'q' || input0 == 'Q' && input1 == '\0')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool isValidMove(int col, int row, Board board, int validMoves,
                 int validCol[100], int validRow[100])
{
    bool valid = 0;
    std::cout << "Valid Moves: " << validMoves << '\n';
    for (int i = 0; i < validMoves; ++i)
    {
        //std::cout << "i: " << i;
        //std::cout << "COL: " << col << " ROW: " << row << "Valid: " << validCol[i] << ' ' << validRow[i] << '\n';
        if (col == validCol[i] && row == validRow[i])
        {
            valid = 1;
        }
    }
    return valid;
    
}

//------------------------------------------------------------------------------
//isPass checks if there are no moves available.  If two passes are made,
//game ends
//------------------------------------------------------------------------------
bool isPass(int validMoves, int& passValue)
{
    if (validMoves == 0)
    {
        ++passValue;
        return true;
    }
    else
    {
        return false;
    }
}

void getCurrentPiece(bool turn, char& currentPiece, char& oppositePiece)
{   
    if (turn == BLACK)
    {
        currentPiece = BLACK_PIECE;
        oppositePiece = WHITE_PIECE;
    }
    else
    {
        currentPiece = WHITE_PIECE;
        oppositePiece = BLACK_PIECE;
    }
}

void performFlip(char currentPiece, char oppositePiece, Board board, bool turn,
                 int col, int row)
{
    if (isValidPositionAtNorth(turn, board, row, col, currentPiece,
                               oppositePiece))
    {
        int rowCount = row - 1;
        while (1)
        {
            if (board[col][rowCount] == oppositePiece)
            {
                board[col][rowCount] = currentPiece;
            }

            else break;
            --rowCount;
        }
    }
    
    if (isValidPositionAtSouth(turn, board, row, col, currentPiece,
                               oppositePiece))
    {
        int rowCount = row + 1;
        while (1)
        {
            if (board[col][rowCount] == oppositePiece)
            {
                board[col][rowCount] = currentPiece;
            }

            else break;
            ++rowCount;
        }
    }

    if (isValidPositionAtEast(turn, board, row, col, currentPiece,
                              oppositePiece))
    {
        int colCount = col + 1;
        while (1)
        {
            if (board[colCount][row] == oppositePiece)
            {
                board[colCount][row] = currentPiece;
            }

            else break;
            ++colCount;
        }
    }

    if (isValidPositionAtWest(turn, board, row, col, currentPiece,
                               oppositePiece))
    {
        int colCount = col - 1;
        while (1)
        {
            if (board[colCount][row] == oppositePiece)
            {
                board[colCount][row] = currentPiece;
            }

            else break;
            --colCount;
        }
    }

    if (isValidPositionAtNorthEast(turn, board, row, col, currentPiece,
                                   oppositePiece))
    {
        int colCount = col + 1, rowCount = row - 1;
        while (1)
        {
            if (board[colCount][rowCount] == oppositePiece)
            {
                board[colCount][rowCount] = currentPiece;
            }

            else break;
            ++colCount;
            --rowCount;
        }
    }

    if (isValidPositionAtNorthWest(turn, board, row, col, currentPiece,
                                   oppositePiece))
    {
        int colCount = col - 1, rowCount = row - 1;
        while (1)
        {
            if (board[colCount][rowCount] == oppositePiece)
            {
                board[colCount][rowCount] = currentPiece;
            }

            else break;
            --colCount;
            --rowCount;
        }
    }

    if (isValidPositionAtSouthEast(turn, board, row, col, currentPiece,
                                   oppositePiece))
    {
        int colCount = col + 1, rowCount = row + 1;
        while (1)
        {
            if (board[colCount][rowCount] == oppositePiece)
            {
                board[colCount][rowCount] = currentPiece;
            }

            else break;
            ++colCount;
            ++rowCount;
        }
    }

    if (isValidPositionAtSouthWest(turn, board, row, col, currentPiece,
                                   oppositePiece))
    {
        int colCount = col - 1, rowCount = row + 1;
        while (1)
        {
            if (board[colCount][rowCount] == oppositePiece)
            {
                board[colCount][rowCount] = currentPiece;
            }

            else break;
            --colCount;
            ++rowCount;
        }
    }
}
//------------------------------------------------------------------------------
//getValidPositions sets up the array of all valid moves for the player
//isValidAt checks if the current spot is valid or not in each of 8 directions
//using a for loop.  If it is valid the column and row is recorded in the
//validCol and validRow array.  Valid moves counts the number of moves there are
//------------------------------------------------------------------------------
void getValidPositions(bool turn, Board board, int validCol[100], int validRow[100],
                       int& validMoves)
{
    char currentPiece = BLACK_PIECE, oppositePiece = WHITE_PIECE;   
    if (turn == BLACK)
    {
        currentPiece = BLACK_PIECE;
        oppositePiece = WHITE_PIECE;
    }
    else
    {
        currentPiece = WHITE_PIECE;
        oppositePiece = BLACK_PIECE;
    }

    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            //std::cout << "IS TRUE: " << isValidPositionAt(turn, board, row, col, currentPiece,
            //                     oppositePiece);
           
            if (isValidPositionAt(turn, board, row, col, currentPiece,
                                  oppositePiece))
            {
                //std::cout << "ROW: " << row << " COL: " << col;
                validRow[validMoves] = row;
                validCol[validMoves] = col;
                //std::cout << "Valid Row: " << validRow[validMoves] << "Valid Col" << validCol[validMoves] << '\n';
                ++validMoves;
                
                //std::cout << "Moves: " << validMoves << '\n';
                //std::cout << "VALID ROW: " << validRow[row] << " COL: " << validCol[col] << '\n';
            }
            
        }
    }    
}

bool isValidPositionAt(bool turn, Board board, int row, int col,
                       char currentPiece, char oppositePiece)
{
    bool isValidPos = 0;
    isValidPos = isValidPositionAtNorth(turn, board, row, col, currentPiece,
                                        oppositePiece) ||
                 isValidPositionAtSouth(turn, board, row, col, currentPiece,
                                        oppositePiece) ||
                 isValidPositionAtEast(turn, board, row, col, currentPiece,
                                        oppositePiece) ||
                 isValidPositionAtWest(turn, board, row, col, currentPiece,
                                        oppositePiece) ||
                 isValidPositionAtNorthEast(turn, board, row, col, currentPiece,
                                            oppositePiece) ||
                 isValidPositionAtNorthWest(turn, board, row, col, currentPiece,
                                            oppositePiece) ||
                 isValidPositionAtSouthWest(turn, board, row, col, currentPiece,
                                            oppositePiece) ||
                 isValidPositionAtSouthEast(turn, board, row, col, currentPiece,
                                            oppositePiece);
                                            
        return isValidPos;   
}

//------------------------------------------------------------------------------
//These functions check if a spot if valid in each direction.  Spot must be
//an empty spot or it will skip it.
//------------------------------------------------------------------------------
bool isValidPositionAtNorth(bool turn, Board board, int row, int col,
                            char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && row > 0)
    {
        for (int rowCheck = row - 1; rowCheck >= 0; --rowCheck)
        {
            //std::cout << "BOARD VALUE HERE = " << board[col][rowCheck] << '\n';
        
            if (board[col][rowCheck] == oppositePiece && rowCheck != 0)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[col][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
            }

            else if (board[col][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
            }   
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtSouth(bool turn, Board board, int row, int col,
                            char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && row < 7)
    {
        for (int rowCheck = row + 1; rowCheck <= 7; ++rowCheck)
        {
            if (board[col][rowCheck] == oppositePiece && rowCheck != 7)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[col][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
            }

            else if (board[col][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
            }   
        }
    }
    else
    {
        return false;
    }
}


bool isValidPositionAtEast(bool turn, Board board, int row, int col,
                           char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col < 7)
    {
        for (int colCheck = col + 1; colCheck <= 7; ++colCheck)
        {
            if (board[colCheck][row] == oppositePiece && colCheck != 7)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][row] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
                 
            }

            else if (board[colCheck][row] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
                 
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
                 
            }   
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtWest(bool turn, Board board, int row, int col,
                           char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col > 0)
    {
        for (int colCheck = col - 1; colCheck >= 0; --colCheck)
        {
            //std::cout << "BOARD VALUE HERE = " << board[col][rowCheck] << '\n';
        
            if (board[colCheck][row] == oppositePiece && colCheck != 0)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][row] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
                 
            }

            else if (board[colCheck][row] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
                 
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
                 
            }   
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtNorthEast(bool turn, Board board, int row, int col,
                                char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col < 7 && row > 0)
    {
        int rowCheck = row - 1;
        for (int colCheck = col + 1; colCheck <= 7; ++colCheck)
        {
            if (board[colCheck][rowCheck] == oppositePiece && colCheck != 7
                && rowCheck != 0)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
            }

            else if (board[colCheck][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
            }
            --rowCheck;
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtNorthWest(bool turn, Board board, int row, int col,
                                char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col > 0 && row > 0)
    {
        int rowCheck = row - 1;
        for (int colCheck = col - 1; colCheck >= 0; --colCheck)
        {
            if (board[colCheck][rowCheck] == oppositePiece && colCheck != 0
                && rowCheck != 0)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
            }

            else if (board[colCheck][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
            }
            --rowCheck;
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtSouthEast(bool turn, Board board, int row, int col,
                                char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col < 7 && row < 7)
    {
        int rowCheck = row + 1;
        for (int colCheck = col + 1; colCheck <= 7; ++colCheck)
        {
            if (board[colCheck][rowCheck] == oppositePiece && colCheck != 7
                && rowCheck != 7)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
            }

            else if (board[colCheck][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
            }
            ++rowCheck;
        }
    }
    else
    {
        return false;
    }
}

bool isValidPositionAtSouthWest(bool turn, Board board, int row, int col,
                                char currentPiece, char oppositePiece)
{
    bool isCaptureMove = 0;
    if (board[col][row] == ' ' && col > 0 && row < 7)
    {
        int rowCheck = row + 1;
        for (int colCheck = col - 1; colCheck >= 0; --colCheck)
        {
            if (board[colCheck][rowCheck] == oppositePiece && colCheck != 0
                && rowCheck != 7)
            {
                //std::cout << "CAPTURE MOVE IS TRUE" << '\n';
                isCaptureMove = 1;
            }
            
            else if (board[colCheck][rowCheck] == ' ')
            {
                //std::cout << "SPACE" << '\n';
                return false;
                 
            }

            else if (board[colCheck][rowCheck] == currentPiece && isCaptureMove == 1)
            {
                //std::cout << "MOVE IS VALID" << '\n';
                return true;
                 
            }

            else
            {
                //std::cout << "NOPE" << '\n';;
                return false;
                 
            }
            ++rowCheck;
        }
    }
    else
    {
        return false;
    }
}
