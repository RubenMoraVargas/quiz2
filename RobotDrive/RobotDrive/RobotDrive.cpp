#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>      
#include <stdlib.h>
#include <time.h>

const int N = 20;
const int M = 35;
char city[N][M];

void initRandom() {
    srand(time(NULL));
}

class Robot {
private:
    int posX;
    int posY;

public:
    Robot() {
        posX = rand() % N;
        posY = 0;
    }
    std::string move(int initialEnergy) {
        std::string actionsResume = "";
        int energy = initialEnergy;
        int moveCounter = 0;
        bool isAtDestination = false;
        actionsResume = "Robot start in X:" + std::to_string(this->posX) + " Y:" + std::to_string(this->posY) + ".\n";

        while (!isAtDestination) {
            if (energy < 0) {
                actionsResume = actionsResume + "Robot needs help!.\n";
                break;
            }

            if (posY == M - 1) {
                isAtDestination = true;
                actionsResume = actionsResume + "Robot has reached its destination!.\n";
                break;
            }

            if (city[posX][posY] == '*') {
                int randomDirection = rand() % 2;
                if (randomDirection == 0) {
                    if (posX > 0 && city[posX - 1][posY] != '*') {
                        posX--;
                    }
                    else {
                        return  actionsResume + "Robot needs assistence with obstacle on the right.\n";
                    }
                }
                else {
                    if (posX < N - 1 && city[posX + 1][posY] != '*') {
                        posX++;
                    }
                    else {
                        return  actionsResume + "Robot needs assistence with obstacle on the left.\n";
                    }
                }
            }
            else if (city[posX][posY] == 'R') {
                energy = initialEnergy;
                posY++;
                actionsResume = actionsResume + "Robot has recharged.\n";
            }
            else {
                posY++;
            }

            moveCounter++;
            if (moveCounter > 1) {
                energy -= 10;
                moveCounter = 0;
            }

            actionsResume = actionsResume + "Robot has moved to (" + std::to_string(posX) +
                ", " + std::to_string(posY) + "). Energy level: " + std::to_string(energy) + ".\n";
        }
        return actionsResume;
    }
};

int main() {
    initRandom();
    //Initialize city with obstacles and charging stations
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (rand() % 15 == 0) {
                city[i][j] = '*';
            }
            else if (rand() % 20 == 0) {
                city[i][j] = 'R';
            }
            else {
                city[i][j] = ' ';
            }
        }
    }
    int initEnergy = (rand() % 10 * 10) + 100;
    Robot robot;
    std::cout << robot.move(initEnergy);

    return 0;
}