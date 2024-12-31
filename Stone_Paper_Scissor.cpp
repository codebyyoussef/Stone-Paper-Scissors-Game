#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice {stone = 1, paper = 2, scissors = 3};
enum enWinner {player1 = 1, computer = 2, draw = 3};

struct stRoundInfo
{
  short roundNumber = 0;
  enGameChoice player1Choice;
  enGameChoice computerChoice;
  enWinner winner;
  string winnerName;
};
struct stGameResults 
{
  short gameRounds = 0;
  short player1WinTimes = 0;
  short computerWinTimes = 0;
  short drawTimes = 0;
  enWinner finalWinner;
  string finalWinnerName = "";
};

void resetScreen()
{
	system("cls"); 		// clear the screen
	system("color 0F"); // turn the screen black
}

short readHowManyRounds()
{
  short gameRounds;
  do
  {
    cout << "How many rounds 1 to 10?\n";
    cin >> gameRounds;
  } while (gameRounds < 1 || gameRounds > 10);
  return gameRounds;
}

enGameChoice readPlayer1Choice()
{
  short choice;
  do
  {
    cout << "\nYour choice: [1]: Stone, [2]: Paper, [3]: Scissors? ";
    cin >> choice;
  } while (choice < 1 || choice > 3);
  return (enGameChoice) choice;
}

int randomNumber(int from, int to)
{
  int randNum = rand() % (to - from + 1) + from;
  return randNum;
}

enGameChoice getComputerChoice()
{
  return (enGameChoice) randomNumber(1, 3);
}

enWinner whoWonTheRound(stRoundInfo roundInfo)
{
  if (roundInfo.player1Choice == roundInfo.computerChoice)
  {
    return draw;
  }

  switch (roundInfo.player1Choice)
  {
    case stone:
      if (roundInfo.computerChoice == paper)
      {
        return computer;
      }
      break;
    case paper:
      if (roundInfo.computerChoice == scissors)
      {
        return computer;
      }
      break;
    case scissors:
      if (roundInfo.computerChoice == stone)
      {
        return computer;
      }
  }
  // if you reach here then player1 is the winner
  return player1;
}

string winnerName(enWinner winner)
{
  string arrWinnersNames[3] = {"Player1", "Computer", "No Winner"};
  return arrWinnersNames[winner - 1];
}

string choiceName(enGameChoice choice)
{
  string arrChoiceNames[3] = {"Stone", "Paper", "Scissors"};
  return arrChoiceNames[choice - 1];
}

void setWinnerScreenColor(enWinner winner)
{
	switch (winner)
	{
		case player1:
			system("color 2F"); // turn screen to green
			break;
		case computer:
			system("color 4F"); // turn screen to red
			cout << "\a";
			break;
		default:
			system("color 6F"); // turn screen to yellow
	}
}

void printRoundResults(stRoundInfo roundInfo)
{
  cout << "\n____________ Round[" << roundInfo.roundNumber << "] ____________\n\n";
  cout << "Player1 choice  : " << choiceName(roundInfo.player1Choice) << endl;
  cout << "Computer choice : " << choiceName(roundInfo.computerChoice) << endl;
  cout << "Round winner    : [" << roundInfo.winnerName << "]\n";
  cout << "__________________________________\n\n";

  setWinnerScreenColor(roundInfo.winner);
}

enWinner whoWonTheGame(short player1WinTimes, short computerWinTimes)
{
  if (player1WinTimes > computerWinTimes)
    return player1;
  else if (computerWinTimes > player1WinTimes)
    return computer;
  else  
    return draw;
}

stGameResults fillGameResults(short gameRounds, short player1WinTimes, short computerWinTimes, short drawTimes)
{
  stGameResults gameResults;

  gameResults.gameRounds = gameRounds;
  gameResults.player1WinTimes = player1WinTimes;
  gameResults.computerWinTimes = computerWinTimes;
  gameResults.drawTimes = drawTimes;
  gameResults.finalWinner = whoWonTheGame(player1WinTimes, computerWinTimes);
  gameResults.finalWinnerName = winnerName(gameResults.finalWinner);

  return gameResults;
}

string tabs(short numberOfTabs)
{
  string tabs;
  for (int i = 1; i <= numberOfTabs; i++)
  {
    tabs += "\t";
  }
  return tabs;
}

void showGameOverScreen()
{
  cout << tabs(2) << "____________________________________________________________\n\n";
  cout << tabs(2) << "                       +++ G a m e O v e r +++\n";
  cout << tabs(2) << "____________________________________________________________\n\n";
}

void showFinalGameResults(stGameResults gameResults)
{
	cout << tabs(2) << "_______________ [Game Results] _______________\n\n";
	cout << tabs(2) << "Game Rounds       : " << gameResults.gameRounds << endl;
	cout << tabs(2) << "Player1 Won times : " << gameResults.player1WinTimes << endl;
	cout << tabs(2) << "Computer Won times: " << gameResults.computerWinTimes << endl;
	cout << tabs(2) << "Draw times        : " << gameResults.drawTimes << endl;
	cout << tabs(2) << "Final winner      : " << gameResults.finalWinnerName << endl;
	cout << tabs(2) << "______________________________________________\n\n";

	setWinnerScreenColor(gameResults.finalWinner);
}

stGameResults playGame(short numberOfRounds)
{
  stRoundInfo roundInfo;
  short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;

  for (short round = 1; round <= numberOfRounds; round++)
  {
    cout << "\nRound [" << round << "] begins\n";
    roundInfo.roundNumber = round;
    roundInfo.player1Choice = readPlayer1Choice();
    roundInfo.computerChoice = getComputerChoice();
    roundInfo.winner = whoWonTheRound(roundInfo);
    roundInfo.winnerName = winnerName(roundInfo.winner);

    // increase win/draw counters
    if (roundInfo.winner == player1)  
      player1WinTimes++;
    else if (roundInfo.winner == computer)
      computerWinTimes++;
    else
      drawTimes++; 

	  printRoundResults(roundInfo);
  }
  return fillGameResults(numberOfRounds, player1WinTimes, computerWinTimes, drawTimes);
}

void startGame()
{
  char playAgain;
  do
  {
    resetScreen(); // return the screen black and clean it
    stGameResults gameResults = playGame(readHowManyRounds());
    showGameOverScreen();
    showFinalGameResults(gameResults);

    cout << "\n" << tabs(3) << "Do you want to play again? Y/N? ";
    cin >> playAgain;
  } while (playAgain == 'Y' || playAgain == 'y');
}

int main()
{
  srand((unsigned)time(NULL));

  startGame();
  return 0; 
}


/* Notes
  - projects like this you should divide them into functions and procedures, and each one of them must do one thing
*/