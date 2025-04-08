using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StonePaperScissorsGame
{
    public partial class Form1 : Form
    {
        enum enGameChoice
        {
            Rock = 1,
            Paper = 2,
            Scissors = 3
        }

        enum enPlayer
        {
            Player1,
            Player2
        }
        enPlayer PlayerTurn = enPlayer.Player1;

        struct stRoundInfo
        {
            public string Player1Choice;
            public string Player2Choice;
        }
        stRoundInfo roundInfo;


        enum enWinner
        {
            Player1,
            Player2,
            Draw,
            InProgress
        }

        struct stGameResults
        {
            public byte Player1WinTimes;
            public byte Player2WinTimes;
            public byte DrawTimes;
            public enWinner FinalWinner;
            public bool GameOver;
        }
        stGameResults gameResults;

        public Form1()
        {
            InitializeComponent();
        }

        string GetFinalGameResultsString()
        {
            string gameResultsString = "";

            gameResultsString += "Player 1 Win Times: " + gameResults.Player1WinTimes.ToString() + "\n";
            gameResultsString += "Player 2 Win Times: " + gameResults.Player2WinTimes.ToString() + "\n";
            gameResultsString += "Draw Time: " + gameResults.DrawTimes.ToString() + "\n";
            gameResultsString += "Game Winner: " + gameResults.FinalWinner.ToString() + "\n";

            return gameResultsString;
        }

        void showFinalGameResults()
        {
            MessageBox.Show(GetFinalGameResultsString(), "Game Results");
        }

        bool IsGameOver()
        {
            return gameResults.Player1WinTimes == 3 || gameResults.Player2WinTimes == 3;
        }

        enWinner WhoWonTheGame()
        {
            if (gameResults.Player1WinTimes > gameResults.Player2WinTimes)
                return enWinner.Player1;
            else if (gameResults.Player2WinTimes > gameResults.Player1WinTimes)
                return enWinner.Player2;
            else
                return enWinner.Draw;
        }

        enWinner WhoWonTheRound()
        {
            if (roundInfo.Player1Choice == roundInfo.Player2Choice)
            {
                return enWinner.Draw;
            }

            switch (roundInfo.Player1Choice)
            {
                case "Rock":
                    if (roundInfo.Player2Choice == "Paper")
                    {
                        return enWinner.Player2;
                    }
                    break;
                case "Paper":
                    if (roundInfo.Player2Choice == "Scissors")
                    {
                        return enWinner.Player2;
                    }
                    break;
                case "Scissors":
                    if (roundInfo.Player2Choice == "Rock")
                    {
                        return enWinner.Player2;
                    }
                    break;
            }

            // if you reach here then player 1 is the winner
            return enWinner.Player1;
        }

        void DisplayRoundWinner()
        {
            lblRoundResult.Visible = true;
            lblRoundResult.ForeColor = Color.GreenYellow;

            if (WhoWonTheRound() == enWinner.Player1)
            {
                gameResults.Player1WinTimes++;
                lblPlayer1WinTimes.Text = gameResults.Player1WinTimes.ToString();
                lblRoundResult.Text = "Player 1 Won!";
            }
            else if (WhoWonTheRound() == enWinner.Player2)
            {
                gameResults.Player2WinTimes++;
                lblPlayer2WinTimes.Text = gameResults.Player2WinTimes.ToString();
                lblRoundResult.Text = "Player 2 Won!";
            }
            else
            {
                gameResults.DrawTimes++;
                lblRoundResult.Text = "Draw";
            }

            if (IsGameOver())
            {
                gameResults.GameOver = true;
                gameResults.FinalWinner = WhoWonTheGame();
                showFinalGameResults();
            }
        }

        void ResetGameRound()
        {
            lblPlayer1.ForeColor = Color.White;
            lblPlayer2.ForeColor = Color.White;

            roundInfo.Player1Choice = "";
            roundInfo.Player2Choice = "";

            PlayerTurn = enPlayer.Player1;
        }

        void SetRoundPlayersChoice(Button btn)
        {
            if (PlayerTurn == enPlayer.Player1)
            {
                lblPlayer1.ForeColor = Color.GreenYellow;
                roundInfo.Player1Choice = btn.Tag.ToString();
                PlayerTurn = enPlayer.Player2;
            }
            else
            {
                lblPlayer2.ForeColor = Color.GreenYellow;
                roundInfo.Player2Choice = btn.Tag.ToString();
                DisplayRoundWinner();
                ResetGameRound();
            }
        }

        private void button_Click(object sender, EventArgs e)
        {
            if (gameResults.GameOver)
                return;
            SetRoundPlayersChoice((Button) sender);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            lblLinkPlayOnline.LinkVisited = true;
            System.Diagnostics.Process.Start("https://www.twoplayergames.org");
        }

        void ResetGame()
        {
            ResetGameRound();

            lblPlayer1WinTimes.Text = "0";
            lblPlayer2WinTimes.Text = "0";

            lblRoundResult.Text = "";
            lblRoundResult.Visible = false;

            gameResults.Player1WinTimes = 0;
            gameResults.Player2WinTimes = 0;
            gameResults.DrawTimes = 0;
            gameResults.FinalWinner = enWinner.InProgress;
            gameResults.GameOver = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            ResetGame();
        }
    }
}
