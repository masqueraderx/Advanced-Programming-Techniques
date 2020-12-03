Author: Xueren Ge
Class: ECE6122
Last Date Modified: 2020/11/30
Description: this file tells you how to build the project and how to run it.

How to build it?
  Use g++ ghost.cpp maze.cpp pacman.cpp main.cpp -lpthread -lGL -lglut -lGLU on pace-ice system. I tested it on Windows system and run it with Microsoft Visual Studio.

How to run it?
  Press 'g' to start to game. And use left, right, up, down arrow keys to determine which direction pacman move. When pacman was caught by one of ghosts, then the first round of the game is over. Note that there are only 3 rounds, which means pacman can revive three times. When pacman revive, it will be back to the origin place and ghost will return to their corresponding origin points. If paceman eat all coins and PowerUps in 3 rounds, then game over, it will show "You Win!", otherwise, it will show "You Lose!" when pacman are caught by ghost in all 3 rounds. If pacman eat the PowerUp, the ghost will turn white and run away from pacman for 5 seconds and then start over catching pacman. If the pacman catches the ghost after eating the PowerUp, the ghost will return to the origin place.
  