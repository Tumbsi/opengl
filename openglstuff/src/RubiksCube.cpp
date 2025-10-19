#include "RubiksCube.h"
#include <iostream>
#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>

//not used????
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
    for (int i = 0; i < 54; ++i) {
        stickers[i] = i; //initally each pos has its correct sticker, aka solved
    }
    for (int f = 0; f < 6; f++)
        for (int i = 0; i < 9; i++)
            stickers[f * 9 + i] = f; // all stickers on face f have same value
    for (int f = 0; f < 6; f++) {
        std::cout << "Face " << f << ": ";
        for (int i = 0; i < 9; i++) {
            std::cout << stickers[f * 9 + i] << " ";
        }
        std::cout << "\n";
    }

}

//prints current cube
void RubiksCube::print() const {
    static const char* faceNames[] = { "Up", "Down", "Left", "Right", "Front", "Back" };
    for (int f = 0; f < 6; ++f) {
        std::cout << faceNames[f] << ":\n";
        for (int i = 0; i < 9; ++i) {
            std::cout << stickers[f * 9 + i] << ' ';
            if ((i + 1) % 3 == 0) std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void RubiksCube::rotateFrontClockwise() {
    // Rotate the front face itself (9 stickers)
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[36 + i];
    stickers[36] = tempFace[6];
    stickers[37] = tempFace[3];
    stickers[38] = tempFace[0];
    stickers[39] = tempFace[7];
    stickers[40] = tempFace[4];
    stickers[41] = tempFace[1];
    stickers[42] = tempFace[8];
    stickers[43] = tempFace[5];
    stickers[44] = tempFace[2];

    // Rotate edges (12 stickers)
    int temp[3] = { stickers[6], stickers[7], stickers[8] }; // Up bottom row

    stickers[6] = stickers[20]; // Left right col → Up bottom row
    stickers[7] = stickers[23];
    stickers[8] = stickers[26];

    stickers[20] = stickers[9]; // Down top row → Left right col
    stickers[23] = stickers[10];
    stickers[26] = stickers[11];

    stickers[9] = stickers[27]; // Right left col → Down top row
    stickers[10] = stickers[30];
    stickers[11] = stickers[33];

    stickers[27] = temp[0]; // saved Up → Right left col
    stickers[30] = temp[1];
    stickers[33] = temp[2];
}


void RubiksCube::rotateFrontCounterClockwise() {
    // Rotate the front face itself (9 stickers counterclockwise)
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[36 + i];
    stickers[36] = tempFace[2];
    stickers[37] = tempFace[5];
    stickers[38] = tempFace[8];
    stickers[39] = tempFace[1];
    stickers[40] = tempFace[4];
    stickers[41] = tempFace[7];
    stickers[42] = tempFace[0];
    stickers[43] = tempFace[3];
    stickers[44] = tempFace[6];

    // Rotate edges (12 stickers counterclockwise)
    int temp[3] = { stickers[6], stickers[7], stickers[8] }; // save Up bottom row

    stickers[6] = stickers[27]; // Right → Up
    stickers[7] = stickers[30];
    stickers[8] = stickers[33];

    stickers[27] = stickers[9]; // Down → Right
    stickers[30] = stickers[10];
    stickers[33] = stickers[11];

    stickers[9] = stickers[20]; // Left → Down
    stickers[10] = stickers[23];
    stickers[11] = stickers[26];

    stickers[20] = temp[0]; // saved Up → Left
    stickers[23] = temp[1];
    stickers[26] = temp[2];
}

void RubiksCube::rotateUpClockwise() {
    // Rotate the Up face itself (9 stickers)
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[i]; // Up face positions 0-8

    stickers[0] = tempFace[6];
    stickers[1] = tempFace[3];
    stickers[2] = tempFace[0];
    stickers[3] = tempFace[7];
    stickers[4] = tempFace[4];
    stickers[5] = tempFace[1];
    stickers[6] = tempFace[8];
    stickers[7] = tempFace[5];
    stickers[8] = tempFace[2];

    // Rotate neighboring edges (12 stickers)
    int temp[3] = { stickers[36], stickers[37], stickers[38] }; // save Front top row

    // Left top → Front top
    stickers[36] = stickers[18];
    stickers[37] = stickers[19];
    stickers[38] = stickers[20];

    // Back top → Left top
    stickers[18] = stickers[45];
    stickers[19] = stickers[46];
    stickers[20] = stickers[47];

    // Right top → Back top
    stickers[45] = stickers[27];
    stickers[46] = stickers[28];
    stickers[47] = stickers[29];

    // Saved Front top → Right top
    stickers[27] = temp[0];
    stickers[28] = temp[1];
    stickers[29] = temp[2];
}

void RubiksCube::rotateUpCounterClockwise() {
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[i];
    stickers[0] = tempFace[2]; stickers[1] = tempFace[5]; stickers[2] = tempFace[8];
    stickers[3] = tempFace[1]; stickers[4] = tempFace[4]; stickers[5] = tempFace[7];
    stickers[6] = tempFace[0]; stickers[7] = tempFace[3]; stickers[8] = tempFace[6];

    int temp[3] = { stickers[36],stickers[37],stickers[38] }; // Front top
    stickers[36] = stickers[27]; stickers[37] = stickers[28]; stickers[38] = stickers[29]; // Right→Front
    stickers[27] = stickers[45]; stickers[28] = stickers[46]; stickers[29] = stickers[47]; // Back→Right
    stickers[45] = stickers[18]; stickers[46] = stickers[19]; stickers[47] = stickers[20]; // Left→Back
    stickers[18] = temp[0]; stickers[19] = temp[1]; stickers[20] = temp[2]; // Front→Left
}

void RubiksCube::rotateDownClockwise() {
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[9 + i];
    stickers[9] = tempFace[6]; stickers[10] = tempFace[3]; stickers[11] = tempFace[0];
    stickers[12] = tempFace[7]; stickers[13] = tempFace[4]; stickers[14] = tempFace[1];
    stickers[15] = tempFace[8]; stickers[16] = tempFace[5]; stickers[17] = tempFace[2];

    int temp[3] = { stickers[42],stickers[43],stickers[44] }; // Front bottom
    stickers[42] = stickers[24]; stickers[43] = stickers[25]; stickers[44] = stickers[26]; // Left→Front
    stickers[24] = stickers[51]; stickers[25] = stickers[52]; stickers[26] = stickers[53]; // Back→Left
    stickers[51] = stickers[33]; stickers[52] = stickers[34]; stickers[53] = stickers[35]; // Right→Back
    stickers[33] = temp[0]; stickers[34] = temp[1]; stickers[35] = temp[2]; // Front→Right
}

void RubiksCube::rotateDownCounterClockwise() {
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[9 + i];
    stickers[9] = tempFace[2]; stickers[10] = tempFace[5]; stickers[11] = tempFace[8];
    stickers[12] = tempFace[1]; stickers[13] = tempFace[4]; stickers[14] = tempFace[7];
    stickers[15] = tempFace[0]; stickers[16] = tempFace[3]; stickers[17] = tempFace[6];

    int temp[3] = { stickers[42],stickers[43],stickers[44] }; // Front bottom
    stickers[42] = stickers[33]; stickers[43] = stickers[34]; stickers[44] = stickers[35]; // Right→Front
    stickers[33] = stickers[51]; stickers[34] = stickers[52]; stickers[35] = stickers[53]; // Back→Right
    stickers[51] = stickers[24]; stickers[52] = stickers[25]; stickers[53] = stickers[26]; // Left→Back
    stickers[24] = temp[0]; stickers[25] = temp[1]; stickers[26] = temp[2]; // Front→Left
}

void RubiksCube::rotateLeftClockwise() {
    int tempFace[9]; for (int i = 0; i < 9; i++) tempFace[i] = stickers[18 + i];
    stickers[18] = tempFace[6]; stickers[19] = tempFace[3]; stickers[20] = tempFace[0];
    stickers[21] = tempFace[7]; stickers[22] = tempFace[4]; stickers[23] = tempFace[1];
    stickers[24] = tempFace[8]; stickers[25] = tempFace[5]; stickers[26] = tempFace[2];

    int temp[3] = { stickers[0],stickers[3],stickers[6] }; // Up left
    stickers[0] = stickers[45]; stickers[3] = stickers[48]; stickers[6] = stickers[51]; // Back right→Up
    stickers[45] = stickers[9]; stickers[48] = stickers[12]; stickers[51] = stickers[15]; // Down left→Back
    stickers[9] = stickers[36]; stickers[12] = stickers[39]; stickers[15] = stickers[42]; // Front left→Down
    stickers[36] = temp[0]; stickers[39] = temp[1]; stickers[42] = temp[2]; // Up→Front
}

void RubiksCube::rotateLeftCounterClockwise() {
    int tempFace[9]; for (int i = 0; i < 9; i++) tempFace[i] = stickers[18 + i];
    stickers[18] = tempFace[2]; stickers[19] = tempFace[5]; stickers[20] = tempFace[8];
    stickers[21] = tempFace[1]; stickers[22] = tempFace[4]; stickers[23] = tempFace[7];
    stickers[24] = tempFace[0]; stickers[25] = tempFace[3]; stickers[26] = tempFace[6];

    int temp[3] = { stickers[0],stickers[3],stickers[6] }; // Up left
    stickers[0] = stickers[36]; stickers[3] = stickers[39]; stickers[6] = stickers[42]; // Front→Up
    stickers[36] = stickers[9]; stickers[39] = stickers[12]; stickers[42] = stickers[15]; // Down→Front
    stickers[9] = stickers[45]; stickers[12] = stickers[48]; stickers[15] = stickers[51]; // Back→Down
    stickers[45] = temp[0]; stickers[48] = temp[1]; stickers[51] = temp[2]; // Up→Back
}

void RubiksCube::rotateRightClockwise() {
    // Rotate face itself
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[27 + i];
    stickers[27] = tempFace[6]; stickers[28] = tempFace[3]; stickers[29] = tempFace[0];
    stickers[30] = tempFace[7]; stickers[31] = tempFace[4]; stickers[32] = tempFace[1];
    stickers[33] = tempFace[8]; stickers[34] = tempFace[5]; stickers[35] = tempFace[2];

    // Rotate edges
    int temp[3] = { stickers[2], stickers[5], stickers[8] }; // Up right
    stickers[2] = stickers[38]; stickers[5] = stickers[41]; stickers[8] = stickers[44]; // Front → Up
    stickers[38] = stickers[11]; stickers[41] = stickers[14]; stickers[44] = stickers[17]; // Down → Front
    stickers[11] = stickers[53]; stickers[14] = stickers[50]; stickers[17] = stickers[47]; // Back → Down
    stickers[53] = temp[0]; stickers[50] = temp[1]; stickers[47] = temp[2]; // Up → Back
}

void RubiksCube::rotateRightCounterClockwise() {
    // Rotate face itself counterclockwise
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[27 + i];
    stickers[27] = tempFace[2]; stickers[28] = tempFace[5]; stickers[29] = tempFace[8];
    stickers[30] = tempFace[1]; stickers[31] = tempFace[4]; stickers[32] = tempFace[7];
    stickers[33] = tempFace[0]; stickers[34] = tempFace[3]; stickers[35] = tempFace[6];

    // Rotate edges counterclockwise
    int temp[3] = { stickers[2], stickers[5], stickers[8] }; // Up right
    stickers[2] = stickers[53]; stickers[5] = stickers[50]; stickers[8] = stickers[47]; // Back → Up
    stickers[53] = stickers[11]; stickers[50] = stickers[14]; stickers[47] = stickers[17]; // Down → Back
    stickers[11] = stickers[38]; stickers[14] = stickers[41]; stickers[17] = stickers[44]; // Front → Down
    stickers[38] = temp[0]; stickers[41] = temp[1]; stickers[44] = temp[2]; // Up → Front
}

void RubiksCube::rotateBackClockwise() {
    // Rotate face itself
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[45 + i];
    stickers[45] = tempFace[6]; stickers[46] = tempFace[3]; stickers[47] = tempFace[0];
    stickers[48] = tempFace[7]; stickers[49] = tempFace[4]; stickers[50] = tempFace[1];
    stickers[51] = tempFace[8]; stickers[52] = tempFace[5]; stickers[53] = tempFace[2];

    // Rotate edges
    int temp[3] = { stickers[0],stickers[1],stickers[2] }; // Up top
    stickers[0] = stickers[29]; stickers[1] = stickers[32]; stickers[2] = stickers[35]; // Right → Up
    stickers[29] = stickers[17]; stickers[32] = stickers[16]; stickers[35] = stickers[15]; // Down → Right (note orientation reversed)
    stickers[15] = stickers[18]; stickers[16] = stickers[21]; stickers[17] = stickers[24]; // Left → Down
    stickers[18] = temp[2]; stickers[21] = temp[1]; stickers[24] = temp[0]; // Up → Left (flip)
}

void RubiksCube::rotateBackCounterClockwise() {
    int tempFace[9];
    for (int i = 0; i < 9; i++) tempFace[i] = stickers[45 + i];
    stickers[45] = tempFace[2]; stickers[46] = tempFace[5]; stickers[47] = tempFace[8];
    stickers[48] = tempFace[1]; stickers[49] = tempFace[4]; stickers[50] = tempFace[7];
    stickers[51] = tempFace[0]; stickers[52] = tempFace[3]; stickers[53] = tempFace[6];

    int temp[3] = { stickers[0],stickers[1],stickers[2] }; // Up top
    stickers[0] = stickers[18]; stickers[1] = stickers[21]; stickers[2] = stickers[24]; // Left → Up
    stickers[18] = stickers[15]; stickers[21] = stickers[16]; stickers[24] = stickers[17]; // Down → Left
    stickers[15] = stickers[29]; stickers[16] = stickers[32]; stickers[17] = stickers[35]; // Right → Down
    stickers[29] = temp[2]; stickers[32] = temp[1]; stickers[35] = temp[0]; // Up → Right
}


void RubiksCube::randomize(int moves = 25) { //default amount of moves is 25! takes int
    //random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // List of 12 move lambdas
    std::vector<std::function<void()>> primitives = {
        [this]() { rotateUpClockwise(); },
        [this]() { rotateUpCounterClockwise(); },
        [this]() { rotateDownClockwise(); },
        [this]() { rotateDownCounterClockwise(); },
        [this]() { rotateLeftClockwise(); },
        [this]() { rotateLeftCounterClockwise(); },
        [this]() { rotateRightClockwise(); },
        [this]() { rotateRightCounterClockwise(); },
        [this]() { rotateFrontClockwise(); },
        [this]() { rotateFrontCounterClockwise(); },
        [this]() { rotateBackClockwise(); },
        [this]() { rotateBackCounterClockwise(); }
    };

    // Apply random moves
    for (int i = 0; i < moves; i++) {
        int r = std::rand() % primitives.size();
        primitives[r](); // call the random move
    }
}

bool RubiksCube::isSolved() {
    for (int f = 0; f < 6; f++) { //loop thru all 6 faces of the cube
        int center = stickers[f * 9 + 4]; //center sticker of the face
        for (int i = 0; i < 9; i++) { //check all 9 stickers
            if (stickers[f * 9 + i] != center) { //if any stickers  dont match the center, is not solved, return false
                return false;
            }
        }
    }
    return true; //all faces is correct
}


bool RubiksCube::isUpFrontEdgeCorrect() {
    // Up face bottom edge
    if (stickers[6] != 0) return false; // Up color
    // Front face top edge
    if (stickers[36 + 1] != 4) return false; // Front color
    return true;
}

void RubiksCube::solveUpCross() {
    while (!isUpFrontEdgeCorrect()) {
        rotateFrontClockwise();
        rotateUpClockwise();
        rotateFrontCounterClockwise();
    }
    // Repeat for other edges
}

