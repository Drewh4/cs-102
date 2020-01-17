#include <iostream>

using namespace std;

void printLeaderboard(string players[], int candy[], int numplayers);
void struckGold(string players[], int candy[], string playerName, int candyFound, int numplayers);
void rainingCandy(string players[], int candy[], int numplayers);
void theft(string players[], int candy[], int numplayers);
void toughLuck(string players[], int candy[], int numplayers);   
int findPlayer(string players[], string playerName, int numplayers);
int printPromptAndGetInput();
void sortLeaderboard(string players[], int candy[], int numplayers);
bool deletePlayer(string players[], int candy[], string playerName, int numplayers);
int dropLosers(string players[], int candy[], int numplayers);
string breakStringAtCaps(string in);

int main()
{
  const int SIZE = 20;
  string players[SIZE];
  int candy[SIZE];
  int numplayers = 0;; 

  string playerName;
  int numCandy;
  cout << "How many players will join the game?" << endl;
  cin >> numplayers;
  for(int i = 0; i < numplayers; i++)
  {
      cout << "Enter name and starting number of candies." << endl;
      cin >> playerName >> numCandy;
      players[i] = breakStringAtCaps(playerName);
      candy[i] = numCandy;
  }
  cout << endl;
  
  cout << "Initial Leaderboard:" << endl;
  printLeaderboard(players, candy, numplayers);
  
  int ans = printPromptAndGetInput();
  while(ans != 0)
  {
      if(ans < 0 || ans > 4)
      {
          cout << "Bad event option...type a number in {0,1,2,3,4}" << endl;
      }
      if(ans == 1)
      {
          cin >> playerName >> numCandy;
          if(numCandy <= 0)
          {
              cout << "Bad candy count...ignoring" << endl;
          }
          else if(findPlayer(players, playerName, numplayers) == -1)
          {
              cout << "Invalid player...ignoring" << endl; 
          }
          else
          {
              struckGold(players, candy, playerName, numCandy, numplayers);
          }
      }
      if(ans == 2)        
      {
          rainingCandy(players, candy, numplayers);
      }
      if(ans == 3)
      {
          theft(players, candy, numplayers);
          numplayers = dropLosers(players, candy, numplayers);
          if(numplayers == 0)
          {
              break;
          } 
          
      }
      if(ans == 4)
      {
          toughLuck(players, candy, numplayers);
          numplayers = dropLosers(players, candy, numplayers);
          if(numplayers == 0)
          {
              break;
          }
      }
      cout << endl;
      printLeaderboard(players, candy, numplayers);
      ans = printPromptAndGetInput();
  }
    
  cout << endl;
  cout << "FINAL LEADERBOARD:" << endl;
  printLeaderboard(players, candy, numplayers);

  return 0;
}



void printLeaderboard(string players[], int candy[], int numplayers)
{
    sortLeaderboard(players, candy, numplayers);
	for(int i = 0; i < numplayers; i++)
    {
        cout << players[i] << " " << candy[i] << endl;
    }
}
void struckGold(string players[], int candy[], string playerName, int candyFound, int numplayers)
{
    if(findPlayer(players, playerName, numplayers) == -1)
    {
        return;
    }
    else 
    {
        candy[findPlayer(players, playerName, numplayers)] += candyFound;
    }
}

void rainingCandy(string players[], int candy[], int numplayers)
{
    for(int i = 0; i < numplayers; i++)
    {
        candy[i] += 2;//adds 2 to all players
    }
}

void theft(string players[], int candy[], int numplayers)
{
    for(int i = 0; i < numplayers; i++)
    {
        if( i % 2 == 0)//divides 2 from even indexes
        {
            candy[i] = candy[i] / 2;
        }
    }
}

void toughLuck(string players[], int candy[], int numplayers)
{
    for(int i = 0; i < numplayers - 1; i++)
    {
        candy[0] -= 1;//first player loses one candy every iteration 
        candy[numplayers - 1 - i] += 1;//adds one to each player from last place to second 
        if(candy[0] == 0)//player has no more candy
        {break;}
    }
}

int findPlayer(string players[], string playerName, int numplayers)
{
    for(int i = 0; i < numplayers; i++)
        {
            if(playerName == players[i])
            {
                return i;
            }
        }
        return -1;
}

int printPromptAndGetInput()
{
    int ans;
    cout << "What event will occur this round?" << endl
           << "0. Quit" << endl
           << "1. Struck Gold: Player “x” finds “y” pieces of candy" << endl
           << "2. Raining Candy: All players collect 2 pieces of candy" << endl
           << "3. Theft: Big Bully steals half of the candy of all even-index players (minimum 1 piece)" << endl
           << "4. Tough Luck: Big Bully gives one piece of candy from the top player to each other player in reverse order." << endl;
    cin >> ans;
    return ans;
}

void sortLeaderboard(string players[], int candy[], int numplayers)
{
    int temp;
    string temp2;
    for(int i = 0; i < numplayers; i++)
	{		
		for(int j = i + 1; j < numplayers; j++)
		{
			if(candy[i] < candy[j])//bubble sort 
			{
				temp = candy[i];
				candy[i] = candy[j];
				candy[j] = temp;
                
                temp2 = players[i];
                players[i] = players[j];
                players[j] = temp2;
			}
		}
	}
}
bool deletePlayer(string players[], int candy[], string playerName, int numplayers)
{
    int index = findPlayer(players, playerName, numplayers);
    if(findPlayer(players, playerName, numplayers) == -1)
    {
        return false;
    }
    for(int i = index; i < numplayers - 1; i++)//deletes player and shifts the rest up
    {
        players[i] = players[i + 1];
        candy[i] = candy[i + 1];
    }
    return true;
}
    
string breakStringAtCaps(string in)
{
    string newString = "";
    for(int i = 0; i < in.size(); i++)//copying players name to another string 
    {
        if(in[i] >= 'A' && in[i] <= 'Z' && i > 0)//add a space before adding the capital letter 
        {
            newString += " ";
        }
        newString += in[i];
    }
    return newString;
}

int dropLosers(string players[], int candy[], int numplayers)
{
  int numLosers = 0;
  for (int i=0; i < numplayers; i++)
  {
    if (candy[i] <= 0)
    {
      numLosers++;
    }
  }

  while(numLosers > 0)
  {
    for (int i=0; i < numplayers; i++)
    {
      if (candy[i] <= 0)
      {
        deletePlayer(players, candy, players[i], numplayers);
        numLosers--;
        numplayers--;
        break;
      }
    }
  }
  return numplayers;
}