#include "RubiksCube.h"
#include <iostream>

static void rotateFaceClockwise(std::array<int, 9>& face) {
    std::array<int, 9> temp = face;
    face[0] = temp[6];
    face[1] = temp[3];
    face[2] = temp[0];
    face[3] = temp[7];
    face[4] = temp[4];
    face[5] = temp[1];
    face[6] = temp[8];
    face[7] = temp[5];
    face[8] = temp[2];
}

RubiksCube::RubiksCube() {
    int id = 0;
    for (int f = 0; f < 6; ++f) {
        for (int i = 0; i < 9; ++i) {
            faces[f][i] = id++;
        }
    }
}

void RubiksCube::print() const {
    static const char* faceNames[] = { "Up", "Down", "Left", "Right", "Front", "Back" };
    for (int f = 0; f < 6; ++f) {
        std::cout << faceNames[f] << ":\n";
        for (int i = 0; i < 9; ++i) {
            std::cout << faces[f][i] << ' ';
            if ((i + 1) % 3 == 0) std::cout << "\n";
        }
        std::cout << '\n';
    }
}

void RubiksCube::rotateFace(Face f, bool clockwise) {
    if (clockwise)
        rotateFaceClockwise(faces[f]);
    else
        for (int i = 0; i < 3; ++i)
            rotateFaceClockwise(faces[f]);
}

void RubiksCube::rotateFrontEdgesClockWise() {
    //save the Up face bottom row
    char temp[3] = {faces[U][6], faces[U][7], faces[U][8] };

    //move left face   right column -> Up face bottom row
    faces[U][6] = faces[L][2];
    faces[U][7] = faces[L][5];
    faces[U][8] = faces[L][8];

    //move Down face top row -> left face right column
    faces[L][2] = faces[D][0];
    faces[L][5] = faces[D][1];
    faces[L][8] = faces[D][2];

    // move right face left column -> down face top row
    faces[D][0] = faces[R][6];
    faces[D][1] = faces[R][3];
    faces[D][2] = faces[R][0];

    //move saved up face bottom row -> right face left column
    faces[R][0] = temp[2];
    faces[R][3] = temp[1];
    faces[R][6] = temp[0];

    // note: F face itself rotation is handled seperately
}

void RubiksCube::rotateFrontEdgesCounterClockWise() {
    //save the up bottom row
    char temp[3] = { faces[U][6], faces[U][7], faces[U][8] };

    // Move Right left column -> Up bottom row
    faces[U][6] = faces[R][0];
    faces[U][7] = faces[R][3];
    faces[U][8] = faces[R][6];

    // Move Down top row -> Right left column
    faces[R][0] = faces[D][2];
    faces[R][3] = faces[D][1];
    faces[R][6] = faces[D][0];

    // Move Left right column -> Down top row
    faces[D][0] = faces[L][8];
    faces[D][1] = faces[L][5];
    faces[D][2] = faces[L][2];

    // Move saved Up bottom row -> Left right column
    faces[L][2] = temp[0];
    faces[L][5] = temp[1];
    faces[L][8] = temp[2];

    // F face itself rotates counterclockwise
    //rotateFace(F, false);

}
