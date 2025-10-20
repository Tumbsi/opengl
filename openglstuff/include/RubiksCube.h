#pragma once
#include <array>
#include "cubie.h"

enum Face { U, D, L, R, F, B };

class RubiksCube {
public:
   // int stickers[54]; //positions 0 to 54
    std::array<int, 54> stickers; // your current flat representation


    cubie::cube toCubieCube() const;

    //keep functions closed, so much DRY code, but for the scope of the project it gets the pass, also simpler this way, but exhausting

    void rotateFrontClockwise();
    void rotateFrontCounterClockwise();
    void rotateUpClockwise();
    void rotateUpCounterClockwise();
    void rotateDownClockwise();
    void rotateDownCounterClockwise();
    void rotateLeftClockwise();
    void rotateLeftCounterClockwise();
    void rotateRightClockwise();
    void rotateRightCounterClockwise();
    void rotateBackClockwise();
    void rotateBackCounterClockwise();
    void randomize(int);
    void solveUpCross();
    
    bool isSolved();
    bool isUpFrontEdgeCorrect();

    
    RubiksCube(); //consturct init solved cube
    void print() const; //prints cube in console
};
