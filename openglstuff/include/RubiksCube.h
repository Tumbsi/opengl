#pragma once
#include <array>

enum Face { U, D, L, R, F, B };

class RubiksCube {
public:
    std::array<std::array<int, 9>, 6> faces;
    void rotateFrontEdgesClockWise();
    void rotateFrontEdgesCounterClockWise();
    RubiksCube();
    void print() const;
    void rotateFace(Face f, bool clockwise);
};
