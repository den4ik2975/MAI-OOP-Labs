#pragma once
#include "game.h"
void enableRawMode();
void disableRawMode();
char getArrowKey();
void printMenu(int selectedOption);
void addNpcMenu(Game& game);