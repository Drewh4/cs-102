#include <iostream>

using namespace std;

char getRCEntry(char grid[], int dim, int r, int c);
int idxToRow(int idx, int dim);
int idxToCol(int idx, int dim);
void printTTT(char grid[], int dim);
int checkForWinner(char grid[], int dim);
bool getInputAndUpdateGrid(char grid[], int dim, char player);
bool checkForDraw(char grid[], int dim);

int main()
{
    char tttdata[121];
    
    int dim;
    // Get the dimension from the user
    cin >> dim;
    
    int dim_sq = dim*dim;

    for(int i=0; i < dim_sq; i++)
    {
        tttdata[i] = '?';
    }
    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    while(!done)
    {
        // Get the current player's input
        bool quit = getInputAndUpdateGrid(tttdata, dim, player);
        if(quit)
        {
            break;
        }

        // Show the updated board
        printTTT(tttdata, dim);

        // Check for winner 
        int winner = checkForWinner(tttdata, dim);
        if(winner == 1)
        {
            cout << "X player wins!" << endl;
            done = true;
        }
        else if(winner == 2)
        {
            cout << "O player wins!" << endl;
            done = true;
        }

         // Check for draw
        if( checkForDraw(tttdata, dim) )
        {
            cout << "Draw...game over!" << endl;
            done = true;
        }

        // switch players to get ready for next turn
        if( player == 'X') 
        {
            player = 'O';
        }
        else 
        {
            player = 'X';
        }
    }
    return 0;
}

char getRCEntry(char grid[], int dim, int r, int c)
{
    return grid[dim * r + c];
}

int idxToRow(int idx, int dim)
{
    return idx / dim;
}

int idxToCol(int idx, int dim)
{
    return idx % dim;
}

void printTTT(char grid[], int dim)
{
    for(int r = 0; r < dim; r++)//row
    {
        for(int c = 0; c < dim; c++)//column
        {
            {
                cout << " " << getRCEntry(grid, dim, r, c) << " ";
                if( c < dim - 1)
                {
                    cout << "|";//only needed in between boxes
                }
            }
        }
        if(r < dim - 1)
        {
            cout << endl;//new line isn't needed after the last row
        }
        if( r < dim - 1)
        {
            for(int d = 0; d < dim * 3 + (dim - 1); d++)
            {
                cout << "-";//not needed after last row
            }
        }
        cout << endl;
    }
}

int checkForWinner(char grid[], int dim)
{
    int player1 = 0, player2 = 0;
    
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(getRCEntry(grid, dim, r, c) == 'X')
            {
                player1++;
            }
            else if(getRCEntry(grid, dim, r, c) == 'O')
            {
                player2++;
            }
            if(player1 == dim)
            {
                return 1;
            }
            else if(player2 == dim)
            {
                return 2;
            }
        }
        player1 = 0;//reset after each row is checked
        player2 = 0;
    }
    
    for(int c = 0; c < dim; c++)
    {
        for(int r = 0; r < dim; r++)
        {
            if(getRCEntry(grid, dim, r, c) == 'X')
            {
                player1++;
            }
            else if(getRCEntry(grid, dim, r, c) == 'O')
            {
                player2++;
            }
            if(player1 == dim)
            {
                return 1;
            }
            else if(player2 == dim)
            {
                return 2;
            }
        }
        player1 = 0;//reset after each column is checked
        player2 = 0;
    }
    
    int c = 0;//column variable
    for(int r = 0; r < dim; r++)//diagonal from top left to bottom right is checked by adding 1 to each row and column index
    {
        if(getRCEntry(grid, dim, r, c) == 'X')
        {
            player1++;
            c++;
        }
        else if(getRCEntry(grid, dim, r, c) == 'O')
        {
            player2++;
            c++;
        }
        if(player1 == dim)
        {
            return 1;
        }
        else if(player2 == dim)
        {
            return 2;
        }
    }
    player1 = 0;//reset after diagonal is checked
    player2 = 0;
    
    int c2 = dim - 1;//column variable that represents the last column in the grid
    for(int r = 0; r < dim; r++)// diagonal from top right to bottom left is checked by incrementing row index and decrementing column index
    {
        if(getRCEntry(grid, dim, r, c2) == 'X')
        {
            player1++;
            c2--;
        }
        else if(getRCEntry(grid, dim, r, c2) == 'O')
        {
            player2++;
            c2--;
        }
        if(player1 == dim)
        {
            return 1;
        }
        else if(player2 == dim)
        {
            return 2;
        }
    }
    return 0;
}

bool getInputAndUpdateGrid(char grid[], int dim, char player)
{
    int num;
    cout << "It is " << player << "'s turn. Enter a number 0-(dim^2-1) representing the desired square." << endl;
    cin >> num;
    if(num < 0 || num > dim*dim -1)//invalid input
    {
        return true;
    }
    while(grid[num] != '?')
    {
        cout << "It is " << player << "'s turn. Enter a number 0-(dim^2-1) representing the desired square." 
             << endl;
        cin >> num;
        if(num < 0 || num > dim*dim -1)
        {
            return true;
        }
    }
    grid[num] = player;//updates the box
    return false;  
}

bool checkForDraw(char grid[], int dim)
{   int waysToDraw = dim * 2 + 2;//the number of ways to win depending on the dimensions
    int player1 = 0, player2 = 0, count = 0;
    
    for(int r = 0; r < dim; r++)
    {
        for(int c = 0; c < dim; c++)
        {
            if(getRCEntry(grid, dim, r, c) == 'X')
            {
                player1++;
            }
            else if(getRCEntry(grid, dim, r, c) == 'O')
            {
                player2++;
            }
        }
        
        if(player1 >= 1 && player2 >= 1)//at least one x and o in the row
        {
            count++;
        }
        player1 = 0;
        player2 = 0;
    }
    
    for(int c = 0; c < dim; c++)
    {
        for(int r = 0; r < dim; r++)
        {
            if(getRCEntry(grid, dim, r, c) == 'X')
            {
                player1++;
            }
            else if(getRCEntry(grid, dim, r, c) == 'O')
            {
                player2++;
            }
        }
        
        if(player1 >= 1 && player2 >= 1)//at least one x and o in the column
        {
            count++;
        }
        
        player1 = 0;
        player2 = 0;
    }
    
    int c = 0;
    for(int r = 0; r < dim; r++)
    {
        if(getRCEntry(grid, dim, r, c) == 'X')
        {
            player1++;
            c++;
        }
        else if(getRCEntry(grid, dim, r, c) == 'O')
        {
            player2++;
            c++;
        }
    }
    
    if(player1 >= 1 && player2 >= 1)//at least one x and o in the diagonal from top left to bottom right
    {
        count++;
    }
    
    player1 = 0;
    player2 = 0;
    
    int c2 = dim - 1;
    for(int r = dim - 1; r >= 0; r--)
    {
        if(getRCEntry(grid, dim, r, c2) == 'X')
        {
            player1++;
            c2--;
        }
        else if(getRCEntry(grid, dim, r, c2) == 'O')
        {
            player2++;
            c2--;
        }
    }
    
    if(player1 >= 1 && player2 >= 1)//at least one x and o in the diagonal from top right to bottom left
    {
        count++;
    }
    player1 = 0;
    player2 = 0;

    if(count == waysToDraw)// there is at least one x and o in every possible way to win
    {
        return true;
    }
    else
     {
         return false;
     }
     count = 0;
}