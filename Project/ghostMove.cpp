//
// Created by 葛学人 on 2020/12/1.
//

#include "ghostMove.h"
extern bool powerUp;
// how ghost1 move
void ghost1move(void)
{
    switch (powerUp)
    {
        // if pacman doesn't eat PowerUp, run to pacman (x, z)
        case 0:
            ghost1.move(ghost1.x, ghost1.z, x, z);
            break;
            // if pacman eat PowerUp, run to the contrary direction (-x, -z)
        case 1:
            ghost1.move(ghost1.x, ghost1.z, -x, -z);
            break;
        default:
            break;
    }

    if (ghost1.catchPac(ghost1.x, ghost1.z, x, z))
    {
        switch (powerUp)
        {
            // if pacman was caught and didn't eat powerUp
            case 0:
                reStart = 1;
                ghost1.ghostMove = 0;
                ghost2.ghostMove = 0;
                ghost3.ghostMove = 0;
                ghost4.ghostMove = 1;
                lives--;
                ghost1.ghostThread.join();
                ghost2.ghostThread.join();
                ghost3.ghostThread.join();
                ghost4.ghostThread.join();
                ghost1.init();
                ghost2.init();
                ghost3.init();
                ghost4.init();
                break;
                // if pacman was caught but eat powerUp
            case 1:
                ghost1.x = 0;
                ghost1.z = 0.5;
                ghost1.ghostMove = 0;
                ghost1.R = 1;
                ghost1.G = 128.0 / 255.5;
                ghost1.B = 192.0 / 255.0;
                ghost1.sketchGhost();
                break;
            default:
                break;
        }
    }
    // if lives was exhausted
    if (lives == 0)
    {
        cout << "You lose!" << endl;
        cout << "Waiting to close the window..." << endl;
        ghost1.ghostThread.join();
        ghost2.ghostThread.join();
        ghost3.ghostThread.join();
        ghost4.ghostThread.join();
        cout << "Closed" << endl;
        exit(0);
    }
    glutPostRedisplay();
}
