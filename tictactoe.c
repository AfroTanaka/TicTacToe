#include <stdio.h>
#include <stdbool.h>

#define ROW_END 3
#define COLUMN_END 3

char get_user_move(void);
void display_board(char board[ROW_END][COLUMN_END]);
void update_board(char player_move, char board[ROW_END][COLUMN_END], int current_turn);
char int_to_char(int n);
int char_to_int(char c);
int get_board_row_index(char player_move);
int get_board_column_index(char player_move);
bool check_winner(char board[ROW_END][COLUMN_END], char mark);
bool check_draw(char board[ROW_END][COLUMN_END]);
bool is_occupied(char player_move, char board[ROW_END][COLUMN_END]);
void generate_board(char board[ROW_END][COLUMN_END]);

/* @brief input specific move from users
 * @arg None
 * @return character type of the specific grid number
 */
char get_user_move(void)
{
    int index;
    printf("your move: ");
    scanf("%d", &index);
    return index + '0' ;
}

void display_board(char board[ROW_END][COLUMN_END])
{
    for (int i = 0; i < ROW_END; i++) {
        for (int j = 0; j < COLUMN_END; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n-----------------\n");
    }
}

void update_board(
        char player_move, char board[ROW_END][COLUMN_END], int current_turn)
{
    int row = get_board_row_index(player_move);
    int column = get_board_column_index(player_move);
    if (current_turn % 2 == 0) {
        board[row][column] = 'o';
    } else {
        board[row][column] = 'x';
    }
}

char int_to_char(int n)
{
    return n + '0';
}

int char_to_int(char c)
{
    return c - '0';
}

/*
 * true - occupied
 * false - not occupied
 */
bool is_occupied(char player_move, char board[ROW_END][COLUMN_END])
{
    int row = get_board_row_index(player_move);
    int column = get_board_column_index(player_move);
    if (board[row][column] == 'o' || board[row][column] == 'x') {
        return true;
    }
    return false;
}

int get_board_row_index(char player_move)
{
    int row = (char_to_int(player_move) - 1) / COLUMN_END;
    return row;
}

int get_board_column_index(char player_move)
{
    int column = (char_to_int(player_move) - 1) % COLUMN_END;
    return column;
}

/*
 * true - someone won
 * false - draw or still going
 */
bool check_winner(char board[ROW_END][COLUMN_END], char mark)
{
    if (board[0][0] == mark && board[0][1] == mark && board[0][2] == mark) {
        return true;
    } else if (board[1][0] == mark && board[1][1] == mark
            && board[1][2] == mark) {
        return true;
    } else if (board[2][0] == mark && board[2][1] == mark
            && board[2][2] == mark) {
        return true;
    } else if (board[0][0] == mark && board[1][0] == mark
            && board[2][0] == mark) {
        return true;
    } else if (board[0][1] == mark && board[1][1] == mark
            && board[2][1] == mark) {
        return true;
    } else if (board[0][2] == mark && board[1][2] == mark
            && board[2][2] == mark) {
        return true;
    } else if (board[0][0] == mark && board[1][1] == mark
            && board[2][2] == mark) {
        return true;
    } else if (board[0][2] == mark && board[1][1] == mark
            && board[2][0] == mark) {
        return true;
    } else {
        return false;
    }
}

/*
 * true - this is a draw game
 * false - this is still going
 */
bool check_draw(char board[ROW_END][COLUMN_END])
{
    for (int i = 0; i < ROW_END; i++) {
        for (int j = 0; j < COLUMN_END; j++) {
            if (board[i][j] != 'o' && board[i][j] != 'x') {
                return false;
            }
        }
    }
    return true;
}

void generate_board(char board[ROW_END][COLUMN_END])
{
    int init = 1;
    for (int i = 0; i < ROW_END; i++) {
        for (int j = 0; j < COLUMN_END; j++) {
            board[i][j] = int_to_char(init);
            init += 1;
        }
    }
}

/*
 * return 'o' - player-x won
 * return 'x' - player-y won
 */
char play_tic_tac_toe()
{
    int current_turn = 0;
    char board[ROW_END][COLUMN_END];

    generate_board(board);
    while (1) {
        display_board(board);
        if (current_turn % 2 == 0) {
            printf("player-x turn\n");
        } else {
            printf("player-y turn\n");
        }
        char player_move = get_user_move();
        if (is_occupied(player_move, board)) {
            continue;
        }
        update_board(player_move, board, current_turn);
        char mark = (current_turn % 2 == 0 ? 'o' : 'x');
        if (check_winner(board, mark)) {
            return (display_board(board), mark);
        }
        if (check_draw(board)) {
            return (display_board(board), '-');
        }
        current_turn += 1;
    }
}

int main()
{
    char result = play_tic_tac_toe();
    if (result == '-') {
        puts("\033[1;36mDraw\033[0m");
    } else if (result == 'o') {
        puts("\033[1;33mPlayer-x win!\033[0m");
    } else {
        puts("\033[1;33mPlayer-y win!\033[0m");
    }
}