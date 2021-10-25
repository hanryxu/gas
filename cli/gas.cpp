//
// Created by Hanry on 12/2/2020.
//

// gas.cpp

// Portions you are to complete are marked with a TODOED: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODOED: item, remove its TODOED: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 120;         // max number of Flatulans allowed

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

// EDIT
const int MAXLIFE = 12;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.

class Flatulan {
public:
    // Constructor
    Flatulan(City *cp, int r, int c);

    // Accessors
    int row() const;

    int col() const;

    // Mutators
    void move();

    bool possiblyGetConverted();

private:
    City *m_city;
    int m_row;
    int m_col;
};

class Player {
public:
    // Constructor
    Player(City *cp, int r, int c);

    // Accessors
    int row() const;

    int col() const;

    int age() const;

    int health() const;

    bool isPassedOut() const;

    // Mutators
    void preach();

    void move(int dir);

    void getGassed();

private:
    City *m_city;
    int m_row;
    int m_col;
    int m_age;
    // TODOED: You'll probably find that a player object needs an additional
    //       data member to support your implementation of the behavior
    //       affected by the player's being blasted with gas.

    // EDIT
    int m_cntGassed;
};

class City {
public:
    // Constructor/destructor
    City(int nRows, int nCols);

    ~City();

    // Accessors
    int rows() const;

    int cols() const;

    Player *player() const;

    bool isPlayerAt(int r, int c) const;

    int flatulanCount() const;

    int nFlatulansAt(int r, int c) const;

    bool determineNewPosition(int &r, int &c, int dir) const;

    void display() const;

    // Mutators
    bool addFlatulan(int r, int c);

    bool addPlayer(int r, int c);

    void preachToFlatulansAroundPlayer();

    void moveFlatulans();

private:
    int m_rows;
    int m_cols;
    Player *m_player;
    Flatulan *m_flatulans[MAXFLATULANS];
    int m_nFlatulans;

    // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game {
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);

    ~Game();

    // Mutators
    void play();

private:
    City *m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);

int randInt(int min, int max);

void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

Flatulan::Flatulan(City *cp, int r, int c) {
    if (cp == nullptr) {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols()) {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Flatulan::row() const {
    return m_row;
}

int Flatulan::col() const {
    // TODOED: TRIVIAL:  Return the column the Flatulan is at.
    // Delete the following line and replace it with the correct code.
    //return 1;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_col;
}

void Flatulan::move() {
    // Attempt to move in a random direction; if it can't move, don't move.
    // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS - 1); // dir is now UP, DOWN, LEFT, or RIGHT
    // TODOED:  Move in the appropriate direction if allowed

    // EDIT
    int target_r = m_row, target_c = m_col;
    m_city->determineNewPosition(target_r, target_c, dir);
    // determineNewPosition ensures that the target location is in bound
    if (m_city->isPlayerAt(target_r, target_c))
        return;
    else {
        m_row = target_r;
        m_col = target_c;
    }
}

bool Flatulan::possiblyGetConverted() // return true if converted
{
    // Be converted with 2/3 probability
    // TODOED:
    // Delete the following line and replace it with the correct code.
    //return false;  // This implementation compiles, but is incorrect.

    // EDIT
    int random_num = randInt(1, 3);
    return (random_num != 3);
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City *cp, int r, int c) {
    if (cp == nullptr) {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1 || r > cp->rows() || c < 1 || c > cp->cols()) {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;

    // EDIT
    m_cntGassed = 0;
}

int Player::row() const {
    // TODOED: TRIVIAL:  Return the row the player is at.
    // Delete the following line and replace it with the correct code.
    //return 1;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_row;
}

int Player::col() const {
    // TODOED: TRIVIAL:  Return the column the player is at.
    // Delete the following line and replace it with the correct code.
    //return 1;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_col;
}

int Player::age() const {
    // TODOED: TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    //return 0;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_age;
}

int Player::health() const {
    // TODOED: TRIVIAL:  Return the player's health status.
    // Delete the following line and replace it with the correct code.
    //return 5;  // This implementation compiles, but is incorrect.

    // EDIT
    return (MAXLIFE - m_cntGassed);
}

bool Player::isPassedOut() const {
    // TODOED: TRIVIAL:  Return whether the player is passed out.
    // Delete the following line and replace it with the correct code.
    //return false;  // This implementation compiles, but is incorrect.

    // EDIT
    return (m_cntGassed >= MAXLIFE);
}

void Player::preach() {
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir) {
    m_age++;
    // TODOED:  If there is a grid position in the indicated direction that is
    //        adjacent to the player and vacant, move the player there;
    //        otherwise, don't move.

    // EDIT
    int target_r = m_row, target_c = m_col;
    m_city->determineNewPosition(target_r, target_c, dir);
    if (m_city->nFlatulansAt(target_r, target_c) == 0) {
        m_row = target_r;
        m_col = target_c;
    }
}

void Player::getGassed() {
    // TODOED: TRIVIAL

    // EDIT
    m_cntGassed++;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols) {
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS) {
        cout << "***** City created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nFlatulans = 0;
}


City::~City() {
    // TODOED:  Delete the player and all remaining dynamically allocated Flatulans.

    // EDIT
    // Seems that it's better to set pointers to nullptr after delete
    for (int i = 0; i < m_nFlatulans; i++) {
        delete m_flatulans[i];
        m_flatulans[i] = nullptr;
    }
    delete m_player;
    m_player = nullptr;
    m_nFlatulans = 0;
    m_rows = 0;
    m_cols = 0;
}

int City::rows() const {
    // TODOED: TRIVIAL:  Return the number of rows in the city.
    // Delete the following line and replace it with the correct code.
    //return 3;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_rows;
}

int City::cols() const {
    // TODOED: TRIVIAL:  Return the number of columns in the city.
    // Delete the following line and replace it with the correct code.
    //return 9;  // This implementation compiles, but is incorrect.

    // EDIT
    return m_cols;
}

Player *City::player() const {
    return m_player;
}

bool City::isPlayerAt(int r, int c) const {
    // TODOED:  Return true if the player is at row r, column c, otherwise false.
    // Delete the following line and replace it with the correct code.
    //return false;  // This implementation compiles, but is incorrect.

    // EDIT
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return true;
    return false;
}

int City::flatulanCount() const {
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const {
    // TODOED:  Return the number of Flatulans at row r, column c.
    // Delete the following line and replace it with the correct code.
    //return 0;  // This implementation compiles, but is incorrect.

    // EDIT
    int cnt = 0;
    for (int i = 0; i < this->flatulanCount(); i++)
        if (m_flatulans[i] != nullptr && m_flatulans[i]->row() == r && m_flatulans[i]->col() == c)
            cnt++;
    return cnt;
}

bool City::determineNewPosition(int &r, int &c, int dir) const {
    // TODOED:  If a move from row r, column c, one step in direction dir
    //        would go off the edge of the city, leave r and c unchanged and
    //        return false.  Otherwise, set r or c so that row r, column c,
    //        is now the new position resulting from the proposed move, and
    //        return true.
    switch (dir) {
        case UP:
            // TODOED:  Implement the behavior if dir is UP.
            // EDIT
            if (isInBounds(r - 1, c)) {
                r--;
                return true;
            }
            break;
        case DOWN:
            if (isInBounds(r + 1, c)) {
                r++;
                return true;
            }
            break;
        case LEFT:
            if (isInBounds(r, c - 1)) {
                c--;
                return true;
            }
            break;
        case RIGHT:
            // TODOED:  Implement the other directions.
            if (isInBounds(r, c + 1)) {
                c++;
                return true;
            }
            break;
        default:
            return false;
    }
    return false;
}

void City::display() const {
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

    // Indicate each Flatulan's position
    // TODOED:  If one Flatulan is at some grid point, set the char to 'F'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.

    // EDIT
    const string gridString = ".F234567899";
    // cout << "flatulanCount()=" << flatulanCount() << endl;
    for (int i = 0; i < this->flatulanCount(); i++) {
        if (m_flatulans[i] == nullptr)
            continue;
        int cur_r = m_flatulans[i]->row();
        int cur_c = m_flatulans[i]->col();
        int cur_cnt = gridString.find(grid[cur_r - 1][cur_c - 1]);
        grid[cur_r - 1][cur_c - 1] = gridString[cur_cnt + 1];
    }
    // Indicate player's position
    if (m_player != nullptr) {
        // Set the char to '@', unless there's also a Flatulan there
        // (which should never happen), in which case set it to '*'.
        char &gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++) {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c) {
    if (!isInBounds(r, c))
        return false;

    // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        //can use the function City::isPlayerAt()
        return false;

    // If there are MAXFLATULANS unconverted Flatulans, return false.
    // Otherwise, dynamically allocate a new Flatulan at coordinates (r,c).
    // Save the pointer to the newly allocated Flatulan and return true.

    // Your function must work as specified in the preceding paragraph even
    // in this scenario (which won't occur in this game):  MAXFLATULANS
    // Flatulans are added, then some are converted, then more are added.

    // TODOED:  Implement this.

    //return false;  // This implementation compiles, but is incorrect.

    // EDIT
    if (m_nFlatulans >= MAXFLATULANS)
        return false;
    m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
    if (m_flatulans[m_nFlatulans] != nullptr) {
        //Checked the bounds and if a player is here, so no need to check other things
        m_nFlatulans++;
        return true;
    }
    return false;
}

bool City::addPlayer(int r, int c) {
    if (!isInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;

    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer() {
    // Preach to Flatulans orthogonally or diagonally adjacent to player.
    // If a Flatulan is converted, destroy it and remove it from the city,
    // since we have no further need to display it or have it interact with
    // the player.

    // TODOED:  Implement this.

    // EDIT

    //We HAVE to CHECK if m_player exists!!
    if (m_player == nullptr)
        return;

    for (int i = 0; i < m_nFlatulans; i++) {
        {
            bool row_fits = (m_flatulans[i]->row() >= m_player->row() - 1 &&
                             m_flatulans[i]->row() <= m_player->row() + 1);
            bool col_fits = (m_flatulans[i]->col() >= m_player->col() - 1 &&
                             m_flatulans[i]->col() <= m_player->col() + 1);
            if (row_fits && col_fits) {
                bool randomPreached = m_flatulans[i]->possiblyGetConverted();
                if (randomPreached) {
                    delete m_flatulans[i];
                    m_flatulans[i] = m_flatulans[m_nFlatulans - 1];
                    m_flatulans[m_nFlatulans - 1] = nullptr;
                    //just for safety
                    m_nFlatulans--;
                    //Since we had moved the last one to the current location, we should still stay here and check this flatulan.
                    //VERY severe problem
                    i--;
                }
            }
        }
    }
};

void City::moveFlatulans() {
    for (int k = 0; k < m_nFlatulans; k++) {
        // TODOED:  Have the k-th Flatulan in the city make one move.
        //        If that move results in that Flatulan being orthogonally
        //        adjacent to the player, the player suffers a gas blast.

        // EDIT
        m_flatulans[k]->move();
        // move can guarantee that the new location is in bound
        int moved_r = m_flatulans[k]->row();
        int moved_c = m_flatulans[k]->col();
        bool ifUp = ((moved_r == m_player->row() - 1) && (moved_c == m_player->col()));
        bool ifDown = ((moved_r == m_player->row() + 1) && (moved_c == m_player->col()));
        bool ifLeft = ((moved_r == m_player->row()) && (moved_c == m_player->col() - 1));
        bool ifRight = ((moved_r == m_player->row()) && (moved_c == m_player->col() + 1));
        if (ifUp || ifDown || ifLeft | ifRight) {
            m_player->getGassed();
        }
    }
}

bool City::isInBounds(int r, int c) const {
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans) {
    if (nFlatulans < 0) {
        cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
        exit(1);
    }
    if (nFlatulans > MAXFLATULANS) {
        cout << "***** Trying to create Game with " << nFlatulans
             << " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1 && cols == 1 && nFlatulans > 0) {
        cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
        exit(1);
    }

    // Create city
    m_city = new City(rows, cols);

    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);

    // Populate with Flatulans
    while (nFlatulans > 0) {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a Flatulan where the player is
        if (r == rPlayer && c == cPlayer)
            continue;
        m_city->addFlatulan(r, c);
        nFlatulans--;
    }
}

Game::~Game() {
    delete m_city;
}

void Game::play() {
    m_city->display();
    Player *p = m_city->player();
    if (p == nullptr)
        return;

    while (!p->isPassedOut() && m_city->flatulanCount() > 0) {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin, action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else {
            switch (action[0]) {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_city->moveFlatulans();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir) {
    switch (dir) {
        case 'u':
            return UP;
        case 'd':
            return DOWN;
        case 'l':
            return LEFT;
        case 'r':
            return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max) {
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main() {
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char *term = getenv("TERM");
    if (term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else {
        static const char *ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif