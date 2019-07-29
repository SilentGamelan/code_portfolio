/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9



// prototypes
void clear(void);
void greet(void);
void init(int board[DIM_MAX][DIM_MAX], int d, int max_tile);
void draw(int board[DIM_MAX][DIM_MAX], int d);
bool move(int tile, int board[DIM_MAX][DIM_MAX], int d, int max_tile);
bool won(int board[DIM_MAX][DIM_MAX], int d, int max_tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    int d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // board
    int board[DIM_MAX][DIM_MAX];

    // used in functions to remove repeated calculations, and make code easier to read
    int max_tile = (d*d) -1;


    // greet user with instructions
    greet();

    
    // initialize the board
    init(board, d, max_tile);

    
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(board, d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(board, d, max_tile))
        {
            printf("ftw!\n");
            break;
        }
        
        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }
        
 
        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, board, d, max_tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);
    
    // return to standard console graphics mode
    printf("\033[=0l");
    
    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 *
 * Forced to initalise the board to maximum permitted values due to way in which C handles passing arrays
 * Initialisation must be done with COMPILE TIME CONSTANTS, otherwise it will fail as compiler doesn't know how to correctly handle the pointer arithmetic
 * Technically only the COLUMNS are relevant for the prototype of 2-d array: void init(int board[][DIM_MAX) is also valid
 * 
 * This is because in a linear memory model, arrays are indexed by base_address+(n*type_size), or in pointer notation *(p+i) [index+offset]
 * The size is given in the declaration, so for instance, given int a[10]: a[5] = *(a+5), or &a+(5*sizeof(int))
 * 
 * A 2-d array in C is actually a 1-D array, whose members are each 1-D arrays.
 * Memory is still linear, so the mapping is instead: base_address+row_offset+column_offset, or &a+(n*sizeof(ROW))+(m*sizeof(int)) [ROW = sizeof(int)*ROWMAX]
 * ie; for a 9x9 int array[3][3] - 2,0 = array+(x*sizeof(ROW))+(y*(sizeof(int)) or 0+0+(2*(3*sizeof(int))) or 0+0+6*sizeof(int) or 24 bytes
 * 
 * So, given the COLUMNS, it is possible to work out the pointer arithmetic for the ROWS without the need for them to be explicitly declared as per the
 * aforemention prototype void init(int board[][DIM_MAX)
 * 
 * Generally this holds for n-dimensional arrays, where n-1 gives the amount of explicit dimension delcarations required, ie;
 * void init(board[][ROWS][COLUMNS])
 * 
 * Dynamically sized arrays can only be handled in C via "simulation" - using pointers and malloc in order to allocate (and possibly reallocate) memory.
 */
void init(int board[DIM_MAX][DIM_MAX], int d, int max_tile)
{
    int tile_num = max_tile;
    // Fills the board in descending order from max_tile ((d*d-)1)
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[i][j] = tile_num--;
        }
    }
    
    // checking if amount of tiles is even number; if so exchange tiles 1 and 2
    // NB: Apparently if( n & 1 == 0) is a faster, bitwise method to do it, as it strips all bits bar the 1's column and checks that. As base2, will always
    // indicate evenness
    if(d % 2 == 0){
        int temp;
        temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
    
    
}

/**
 * Prints the board in its current state.
 */
void draw(int board[DIM_MAX][DIM_MAX], int d)
{
    
    // prints the contents of board[]][] from 0,0 - skips printing space tile "0"
    for(int i = 0; i < d; i++){
        for(int j = 0 ; j < d; j++){
            if(board[i][j] > 0){
            printf("%2d\t", board[i][j]);
            }
            else {
                printf("  \t");
            }
        }
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile into empty space and returns true, 
 * else false
 */
bool move(int tile, int board[DIM_MAX][DIM_MAX], int d, int max_tile)
{
    
    bool valid_move = false;
    int tile_x, tile_y;
    //vector pairs corresponding to left, up, right, down 
    int check_y[4] = {0, -1, 1, 0};
    int check_x[4] = {-1, 0, 0, 1};
    
    // check that tile exists
    if(tile > 0 || tile <= max_tile){
        // search board, and find the x,y coords of tile to move 
        for(int i = 0; i < d; i++){
            for(int j = 0 ; j < d; j++){
                if(tile == board[i][j]){
                    tile_x = i;
                    tile_y = j;
                }
            }
        }
        
        // checks tiles left, above, right, below - first ensures that move wouldn't take place outside board and avoid array index-out-of-bounds errors
        for(int i = 0; i < 4; i++){
                if((tile_x + check_x[i] > -1 && tile_x + check_x[i] < d ) && (tile_y + check_y[i] > -1 && tile_y + check_y[i] < d)){
                    if(board[tile_x + check_x[i]][tile_y + check_y[i]] == 0){
                        valid_move = true;
                        // swaps space tile with move tile
                        board[tile_x + check_x[i]][tile_y + check_y[i]] = tile;
                        board[tile_x][tile_y] = 0;
                        break;
                    }
                }
            }
            
        }
    
    return valid_move;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int board[DIM_MAX][DIM_MAX], int d, int max_tile)
{
    bool victory = true;
    int tile_num = 1;
    
    
    // assume winning configuration until find a tile out of place
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            if(tile_num == max_tile+1){
                tile_num = 0;
            }
            if(board[i][j] != tile_num++){
                victory = false;
                break;
            }
        }
        
        if(victory == false){
            break;
        }
    }
    
    return victory;
}