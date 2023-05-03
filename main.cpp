#include <iostream>               // Pacman Game using C++, SFML and SQLite DataBase
#include <SFML/Graphics.hpp>      // for Graphics
#include <SFML/Audio.hpp>         // for sound
#include <SFML/Window.hpp>        // for keyboard
#include <SFML/System.hpp>        // for time
#include <SFML/Network.hpp>       // for network
#include <SFML/System/Export.hpp> // for time
#include <SFML/System/Time.hpp>   // for time
#include <string>                 // for textbox and sign up etc
#include <string.h>               // for string
#include <stdio.h>                // for printf
#include <stdlib.h>               // for random
#include <cstring>                // for string
#include <sstream>                // for ostream
#include <ctime>                  // for random
#include <random>                 // for random
#include <cstdlib>                // for random (rand and srand)
#include <fstream>                // for file handling
#include <vector>                 // for vector
#include <cmath>                  // for math
#include <random>                 // for random
#include <array>                  // for array
#include <chrono>                 // for time and date
#include <thread>                 // for thread (pausing game or delaying)
#include <cfloat>                 // for float
#include <sqlite3.h>              // for database
extern "C"                        // specify that the following code is C code being used with C++
{
#include <sqlite3.h> // for database SQLite
}

using namespace sf;
using namespace std;

// Defining values for keyboard keys
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define SHIFT_KEY 16
#define SPACE_KEY 32
#define Z_KEY 90
#define X_KEY 88
#define C_KEY 67
#define W_KEY 87 // }-> All of these may not be used, but roughly they will be needed
#define A_KEY 65
#define S_KEY 83
#define D_KEY 68
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define CTRL_KEY 17
#define TAB_KEY 9

// Defining values for game
#define MENU_SCREEN_WIDTH 1200
#define MENU_SCREEN_HEIGHT 900
#define SCREEN_TITLE "Pacman Game" // to make finding things easier
#define FPS 60

// Defining Login and Sign Up
#define LOGIN_SIGNUP_SCREEN_WIDTH 550
#define LOGIN_SIGNUP_SCREEN_HEIGHT 300
#define LOGIN_SCREEN_TITLE "Pacman Game (Login Page)"
#define SIGNUP_SCREEN_TITLE "Pacman Game (Signup Page)"

// Global Username and Password
string current_username;
string current_password;

struct CallbackData // callback values for sqlite3_exec
{
    const std::string &user;
    const std::string &pass;
    int result;
};

class TextBox // Selecting textbox using Enter key
{
private:
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool haslimit = false;
    int limit;

    void inputLogic(int charTyped)
    {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && charTyped != TAB_KEY)
        {
            text << static_cast<char>(charTyped);
        }

        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar()
    {
        string t = text.str();
        string newT = ""; // NewT means New Text
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }

public:
    TextBox()
    {
        // Nothing to do here
        cout << "Using textbox class" << endl;
    }
    TextBox(int size, Color color, bool sel)
    {
        /*font.loadFromFile("arial.ttf"); //Not necessary, did it manually
        textbox.setFont(font);*/
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = sel;

        if (sel)
        {
            textbox.setString("_");
        }
        else
        {
            textbox.setString("");
        }
    }
    void setFont(Font &font)
    {
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos) // pos means position
    {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF) // Tof means True or False
    {
        haslimit = ToF;
    }

    void setLimit(bool ToF, int lim)
    {
        haslimit = ToF;
        limit = lim - 1;
    }

    void setSelected(bool sel) // sel means selected
    {
        isSelected = sel;
        if (!sel)
        {
            string t = text.str();
            string newT = "";
            for (int i = 0; i < t.length(); i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    string getText()
    {
        return text.str();
    }

    void drawTo(RenderWindow &window)
    {
        window.draw(textbox);
    }

    void typedOn(Event input)
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode; // get value of char being typed
            if (charTyped < 128)
            {
                if (haslimit)
                {
                    if (text.str().length() <= limit)
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > limit && charTyped == DELETE_KEY)
                    {
                        deleteLastChar();
                    }
                }
                else
                {
                    inputLogic(charTyped);
                }
            }
        }
    }

    string return_text() // to verify login and signup
    {
        string t = text.str();
        // if there is an _ at the end of the string, remove it
        if (t[t.length() - 1] == '_')
        {
            t.erase(t.length() - 1);
        }
        // if there is a space at end of string remove it
        if (t[t.length() - 1] == ' ')
        {
            t.erase(t.length() - 1);
        }
        return t;
    }
    // destructors
    ~TextBox()
    {
        // Object Destroyed
        cout << "textbox object destroyed" << endl;
    }
};

class TextBox_Alternate // select textbox using Tab key
{
private:
    Text textbox;
    ostringstream text;
    bool isSelected = false;
    bool haslimit = false;
    int limit;

    void inputLogic(int charTyped)
    {
        if (charTyped != DELETE_KEY && charTyped != TAB_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY)
        {
            text << static_cast<char>(charTyped);
        }

        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar()
    {
        string t = text.str();
        string newT = ""; // NewT means New Text
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }

public:
    TextBox_Alternate()
    {
        // Nothing to do here
        cout << "Using textbox alternative class" << endl;
    }

    TextBox_Alternate(int size, Color color, bool sel)
    {
        /*font.loadFromFile("arial.ttf"); //Not necessary, did it manually
        textbox.setFont(font);*/
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = sel;

        if (sel)
        {
            textbox.setString("_");
        }
        else
        {
            textbox.setString("");
        }
    }

    void setFont(Font &font)
    {
        textbox.setFont(font);
    }

    void setPosition(Vector2f pos) // pos means position
    {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF) // Tof means True or False
    {
        haslimit = ToF;
    }

    void setLimit(bool ToF, int lim)
    {
        haslimit = ToF;
        limit = lim - 1;
    }

    void setSelected(bool sel) // sel means selected
    {
        isSelected = sel;
        if (!sel)
        {
            string t = text.str();
            string newT = "";
            for (int i = 0; i < t.length(); i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    string getText()
    {
        return text.str();
    }

    void drawTo(RenderWindow &window)
    {
        window.draw(textbox);
    }

    void typedOn(Event input)
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode; // get value of char being typed
            if (charTyped < 128)
            {
                if (haslimit)
                {
                    if (text.str().length() <= limit)
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > limit && charTyped == DELETE_KEY)
                    {
                        deleteLastChar();
                    }
                }
                else
                {
                    inputLogic(charTyped);
                }
            }
        }
    }
    string return_text() // to verify login and signup
    {
        string t = text.str();
        // if there is an _ at the end of the string, remove it
        if (t[t.length() - 1] == '_')
        {
            t.erase(t.length() - 1);
        }
        // if there is a space at end of string remove it
        if (t[t.length() - 1] == ' ')
        {
            t.erase(t.length() - 1);
        }
        return t;
    }
    // destructors
    ~TextBox_Alternate()
    {
        // Object Destroyed
        cout << "textbox alternative type object destroyed" << endl;
    }
};

void menu_screen(); // function prototypes
void menu_screen_signup_success();
void login_screen();
void signup_screen();
void signup_screen_error_blank();
void signup_screen_error_already_exists();
void signup_screen_error_unknown();
void signup_screen_error_database();
void signup_admin_not_allowed();
void login_screen_error_blank();
int confirm_login_sqlite(const std::string &user, const std::string &pass);
int signup_sqlite(const std::string &user, const std::string &pass);
static int callback(void *data, int argc, char **argv, char **azColName);
int load_highscore();
int save_data(string user, int score);
void login_screen_error_user_doesnt_exist();
void login_screen_error_wrong_pass();
void login_screen_error_database();
void admin_screen();
void maze_test();

void draw_maze(int array[][22], RectangleShape **place, int rows, int cols, int cell_size, Texture &wallTexture, Texture &palletTexture,
               Texture &pacmanTexture, RenderWindow &window, int &pac_rows, int &p_cols, Texture &cageTex, Texture &fruitTex, Texture &spaceTex);
void change_location(int ghosts[][22], RectangleShape **place, int rows, int cols, int cell_size, Texture &greenGhostTexture,
                     Texture &redGhostTexture, Texture &blueGhostTexture, Texture &pinkGhostTexture, Texture &wallTexture, Texture &spaceTex, Texture &cageTex);
class Score
{
protected:
    int score;
    int highscore;
    Text scoreText;
    Text highscoreText;
    Text gameOverText;
    Text restartText;
    Text winText;
    Font font;

public:
    Score() : score(0), scoreText(), highscoreText(), gameOverText(), winText(), restartText()
    {
        font.loadFromFile("Fonts/Roboto-Black.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(150, 0);

        highscoreText.setFont(font);
        highscoreText.setCharacterSize(24);
        highscoreText.setFillColor(Color::White);
        highscoreText.setPosition(400, 0);
        highscore = load_highscore();
        highscoreText.setString("Highscore: " + to_string(highscore));
        // set_highscore();

        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setPosition(450, 550);

        winText.setFont(font);
        winText.setString("You Win");
        winText.setCharacterSize(24);
        winText.setFillColor(Color::White);
        winText.setPosition(0, 60);

        restartText.setFont(font);
        restartText.setString("Press R to restart");
        restartText.setCharacterSize(24);
        restartText.setFillColor(Color::White);
        restartText.setPosition(0, 90);

        // set_highscore();
    }

    int return_score_2()
    {
        return score;
    }

    int return_highscore()
    {
        // get highscore from highscore sfml text
        string t = highscoreText.getString();
        // convert to integer
        int highscore = stoi(t.substr(12, t.length() - 1));
        return highscore;
    }

    void set_highscore()
    {
        int highscore1 = load_highscore();
        // convert highscore from int to string
        string highscore_str = to_string(highscore1);

        cout << "highscore is: " << highscore1 << endl;

        // set highscore sfml text
        highscoreText.setString("Highscore: " + highscore_str);
    }

    void set_highscore_1(int highscore1)
    {
        // convert highscore from int to string
        string highscore_str = to_string(highscore1);
        cout << "highscore is: " << highscore1 << endl;

        // set highscore sfml text
        highscoreText.setString("Highscore: " + highscore_str);
    }

    void draw_score(RenderWindow &window)
    {
        scoreText.setString("Score: " + to_string(score));
        window.draw(scoreText);
    }
    void draw_highscore(RenderWindow &window)
    {

        highscoreText.setString("Highscore: " + to_string(highscore));
        window.draw(highscoreText);
    }
    void draw_game_over(RenderWindow &window)
    {
        gameOverText.setString("Game Over");
        window.draw(gameOverText);
    }
    void draw_win(RenderWindow &window)
    {
        winText.setString("You Win");
        window.draw(winText);
    }
    void draw_restart(RenderWindow &window)
    {
        restartText.setString("Press R to restart");
        window.draw(restartText);
    }
    void calculate_score(int cellValue)
    {
        if (cellValue == 2)
        {
            score += 10;
        }
        else if (cellValue == 9)
        {
            score += 50;
        }
    }
    bool is_win()
    {
        if (score == 1660) // total dots are 146 and 4 are the fruits
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // return score
    int return_score()
    {
        return this->score;
    }
};
class Pacman
{
private:
    int x, y;
    int lives;
    Text livesText;
    Font f1;

public:
    Pacman() : x(10), y(15), lives(3), livesText()
    {
        f1.loadFromFile("Fonts/Roboto-Black.ttf");
        livesText.setFont(f1);
        livesText.setCharacterSize(24);
        livesText.setFillColor(Color::White);
        livesText.setPosition(725, 0);
    }
    void decrease_lives()
    {
        lives--;
    }
    // void calculate_lives(Texture& pac, Texture& ghost1, Texture& ghost2, Texture& ghost3, Texture& ghost4)

    bool is_game_over()
    {
        if (lives == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void draw_lives(RenderWindow &window)
    {
        livesText.setString("Lives: " + to_string(lives));
        window.draw(livesText);
    }
};
class Sounds
{
public:
    Sounds()
    {
        if (!beginning_sound_buffer.loadFromFile("beginning.wav"))
        {
            throw "Failed to load beginning.wav";
        }
        beginning_sound.setBuffer(beginning_sound_buffer);

        if (!chomp_sound_buffer.loadFromFile("chomp.wav"))
        {
            throw "Failed to load chomp.wav";
        }
        chomp_sound.setBuffer(chomp_sound_buffer);

        if (!death_sound_buffer.loadFromFile("death.wav"))
        {
            throw "Failed to load death.wav";
        }
        death_sound.setBuffer(death_sound_buffer);

        if (!intermission_sound_buffer.loadFromFile("intermission.wav"))
        {
            throw "Failed to load intermission.wav";
        }
        intermission_sound.setBuffer(intermission_sound_buffer);

        if (!eatfruit_sound_buffer.loadFromFile("eatfruit.wav"))
        {
            throw "Failed to load eatfruit.wav";
        }
        eatfruit_sound.setBuffer(eatfruit_sound_buffer);

        if (!eatghost_sound_buffer.loadFromFile("eatghost.wav"))
        {
            throw "Failed to load eatghost.wav";
        }
        eatghost_sound.setBuffer(eatghost_sound_buffer);
    }

    void playSound(const std::string &filename)
    {
        SoundBuffer sound_buffer;
        if (!sound_buffer.loadFromFile(filename))
        {
            throw "Failed to load ";
        }
        Sound sound;
        sound.setBuffer(sound_buffer);
        sound.play();
    }

    void beginning()
    {
        beginning_sound.play();
    }

    void eat(int check)
    {
        if (check == 2)
        {
            chomp_sound.play();
        }
    }

    void Death()
    {
        death_sound.play();
    }

    void win()
    {
        intermission_sound.play();
    }

    void eatFruit(int check)
    {
        if (check == 9)
        {
            eatfruit_sound.play();
        }
    }

    void eatGhost()
    {
        eatghost_sound.play();
    }

private:
    SoundBuffer beginning_sound_buffer;
    SoundBuffer chomp_sound_buffer;
    SoundBuffer death_sound_buffer;
    SoundBuffer intermission_sound_buffer;
    SoundBuffer eatfruit_sound_buffer;
    SoundBuffer eatghost_sound_buffer;

    Sound beginning_sound;
    Sound chomp_sound;
    Sound death_sound;
    Sound intermission_sound;
    Sound eatfruit_sound;
    Sound eatghost_sound;
};
class Messages
{
private:
    Text ReadyText;
    Font f2;

public:
    Messages() : ReadyText()
    {
        f2.loadFromFile("Fonts/Roboto-Black.ttf");
        ReadyText.setFont(f2);
        ReadyText.setCharacterSize(30);
        ReadyText.setFillColor(Color::Red);
        ReadyText.setPosition(450, 550);
    }
    void DisplayReady(RenderWindow &window)
    {
        ReadyText.setString("  READY ! ");
        window.draw(ReadyText);
    }
};

void maze_test()
{
    RenderWindow window(VideoMode(1100, 1100), "PAC MAN", Style::Default);
    window.setFramerateLimit(90);
    // disable stretching
    window.setVerticalSyncEnabled(true);
    Score score;
    Pacman pacman;
    Messages M1;

    int rows = 21, cols = 22;
    float cell_size = 50;
    int array[21][22] =
        {

            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},       // 0
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},       // 1
            {0, 1, 9, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 9, 1},       // 2
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},       // 3
            {0, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},       // 4
            {0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},       // 5
            {0, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1},       // 6
            {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},       // 7
            {1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 7, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1}, // 8
            {0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0},    // 9
            {1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1}, // 10
            {0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},       // 11
            {0, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},       // 12
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},       // 13
            {0, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},       // 14
            {0, 1, 9, 2, 1, 2, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 1, 2, 9, 1},       // 15
            {0, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1},       // 16
            {0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},       // 17
            {0, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1},       // 18
            {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},       // 19
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},       // 20
        };
    int ghosts[21][22] =
        {
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
            {0, 0, 0, 0, 1, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 1, 4, 0, 5, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
            {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
            {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
            {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
    sf::Texture wallTexture;
    wallTexture.loadFromFile("wall.png");

    sf::Texture palletTexture;
    palletTexture.loadFromFile("2pallets.png");

    sf::Texture greenGhostTexture;
    greenGhostTexture.loadFromFile("green.png");

    sf::Texture redGhostTexture;
    redGhostTexture.loadFromFile("red.png");

    sf::Texture blueGhostTexture;
    blueGhostTexture.loadFromFile("blue.png");

    sf::Texture pinkGhostTexture;
    pinkGhostTexture.loadFromFile("pink.png");

    sf::Texture pacmanTexture;
    pacmanTexture.loadFromFile("pacman.png");

    Texture spaceTex;
    spaceTex.loadFromFile("space.png");

    Texture fruitTex;
    fruitTex.loadFromFile("fruit.png");

    Texture cageTex;
    cageTex.loadFromFile("cage.png");

    Texture Pac_left;
    Pac_left.loadFromFile("Left.png");

    Texture Pac_up;
    Pac_up.loadFromFile("Up.png");

    Texture Pac_down;
    Pac_down.loadFromFile("Down.png");

    RectangleShape **place = new RectangleShape *[rows];
    RectangleShape **place2 = new RectangleShape *[rows];
    int pac_rows;
    int p_cols;
    for (int i = 0; i < rows; i++)
    {
        place[i] = new RectangleShape[cols];
        place2[i] = new RectangleShape[cols];
        for (int j = 0; j < cols; j++)
        {
            int cellValue = array[i][j];
            int cell_val2 = ghosts[i][j];
            RectangleShape rect;
            if (cellValue == 0) // space
            {
                rect.setTexture(&spaceTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 1) // wall
            {
                rect.setTexture(&wallTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place[i][j] = rect;
            }
            else if (cellValue == 2) // dots
            {
                rect.setTexture(&palletTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place[i][j] = rect;
            }
            else if (cell_val2 == 3) // green ghost
            {

                rect.setTexture(&greenGhostTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place2[i][j] = rect;
            }
            else if (cell_val2 == 4) // blue one
            {
                rect.setTexture(&blueGhostTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place2[i][j] = rect;
            }
            else if (cell_val2 == 5) // red one
            {
                rect.setTexture(&redGhostTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place2[i][j] = rect;
            }
            else if (cell_val2 == 6) // pink one
            {
                rect.setTexture(&pinkGhostTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place2[i][j] = rect;
            }
            else if (cellValue == 7) // cage
            {
                rect.setTexture(&cageTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place[i][j] = rect;
            }
            else if (cellValue == 8)
            {
                pac_rows = i;
                p_cols = j;
                rect.setTexture(&pacmanTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place[i][j] = rect;
            }
            else if (cellValue == 9)
            {
                rect.setTexture(&fruitTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
                rect.setPosition(Vector2f(j * cell_size, i * cell_size));
                place[i][j] = rect;
            }
        }
    }
    Clock deltaClock = Clock();
    bool moving_Left = false;
    int numFrames1 = 10; // Display the text for 5 seconds at 60 fps
    int frameCount1 = 0;
    int check;
    // game loop
    int movement_direction = 1;
    Sounds obj;
    obj.beginning(); // ready wala scene

    int ghost_rows[4] = {9, 9, 9, 7};
    int ghost_cols[4] = {7, 13, 15, 8};
    Clock A = Clock();

    random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 4);
    double pacmanTimer = 0;
    double ghostTimer = 0;
    int ghost_directions[4] = {1, 1, 1, 1};
    double ghost_speed = 0;
    int fakePacmanDirection = 0;

    // int h_scr = load_highscore();
    // score.set_highscore_1(h_scr);

    Clock deltaClock1;
    Time deltaTime;

    bool isGameOver = false;
    bool isLiveDecreased = false;
    double gameOverTimer = 0;
    double gameWinTimer = 0;
    bool ready = true;
    double readytime = 0;
    while (window.isOpen())
    {

        deltaTime = deltaClock1.restart();
        Event event;
        // set background color to black
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {

                window.close();
            }
        }

        window.clear(Color::Black);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                score.draw_score(window);
                score.draw_highscore(window);
                pacman.draw_lives(window);
                window.draw(place[i][j]);
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (ghosts[i][j] != 1 && ghosts[i][j] != 0 && ghosts[i][j] != 7)
                {
                    window.draw(place2[i][j]);
                }
            }
        }
        if (isGameOver)
        {
            score.draw_game_over(window);
            window.display();
            string user = ::current_username;
            int scr = score.return_score();
            save_data(user, scr);
            gameOverTimer += deltaTime.asSeconds();
            if (gameOverTimer >= 3)
            {
                window.close();
                menu_screen();
            }

            continue;
        }
        if (score.is_win())
        {
            score.draw_win(window);
            obj.win();
            window.display();
            string user = ::current_username;
            int scr = score.return_score();
            save_data(user, scr);
            gameWinTimer += deltaTime.asSeconds();
            if (gameWinTimer >= 3)
            {
                window.close();
                menu_screen();
            }

            continue;
        }
        if (ghost_speed < 0.0f)
        {
            // move ghosts
            for (int i = 0; i < 4; i++)
            {
                if (ghost_directions[i] == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
                {

                    // Move ghost right
                    ghosts[ghost_rows[i]][(ghost_cols[i] + 1)] = ghosts[ghost_rows[i]][ghost_cols[i]];
                    ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
                    ghost_cols[i] += 1;
                    // Update ghost timer
                    change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
                                    redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
                }
                else if (ghost_directions[i] == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
                {
                    // Move ghost down
                    ghosts[(ghost_rows[i] + 1)][ghost_cols[i]] = ghosts[ghost_rows[i]][ghost_cols[i]];
                    ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
                    ghost_rows[i] += 1;
                    // Update ghost timer
                    change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
                                    redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
                }
                else if (ghost_directions[i] == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
                {
                    // Move ghost left
                    ghosts[ghost_rows[i]][(ghost_cols[i] - 1)] = ghosts[ghost_rows[i]][ghost_cols[i]];
                    ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
                    ghost_cols[i] -= 1;
                    // Update ghost timer
                    change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
                                    redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
                }
                else if (ghost_directions[i] == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
                {
                    // Move ghost up
                    ghosts[(ghost_rows[i] - 1)][ghost_cols[i]] = ghosts[ghost_rows[i]][ghost_cols[i]];
                    ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
                    ghost_rows[i] -= 1;
                    // Update ghost timer
                    change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
                                    redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
                }
                else
                {
                    // change direction to one that is not blocked
                    int direction = dist(rng);
                    while (true)
                    {
                        if (direction == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
                        {
                            break;
                        }
                        else if (direction == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
                        {
                            break;
                        }
                        else if (direction == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
                        {
                            break;
                        }
                        else if (direction == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
                        {
                            break;
                        }
                        direction = dist(rng);
                    }
                    ghost_directions[i] = direction;
                }
            }
            ghost_speed = 0.5f;
        }
        else
        {
            // use move function
            for (int i = 0; i < 4; i++)
            {
                if (ghost_directions[i] == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
                {
                    place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(cell_size / 0.5f * deltaTime.asSeconds(), 0));
                }
                else if (ghost_directions[i] == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
                {
                    place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(0, cell_size / 0.5f * deltaTime.asSeconds()));
                }
                else if (ghost_directions[i] == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
                {
                    place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(-cell_size / 0.5f * deltaTime.asSeconds(), 0));
                }
                else if (ghost_directions[i] == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
                {
                    place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(0, -cell_size / 0.5f * deltaTime.asSeconds()));
                }
            }
        }
        if (ghostTimer < 0 && ghost_speed == 0.5f)
        {
            int num_ghosts = 4;
            int i = 0;
            // chrono::steady_clock::now().time_since_epoch().count();

            int ghost_direction;
            while (i < num_ghosts)
            {
                ghost_direction = dist(rng);

                // check if ghost can move in that direction
                if (ghost_direction == 1)
                {
                    if (array[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(array[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && array[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
                    {
                        ghost_directions[i] = ghost_direction;
                    }
                }
                else if (ghost_direction == 2)
                {
                    if (array[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(array[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && array[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
                    {
                        ghost_directions[i] = ghost_direction;
                    }
                }
                else if (ghost_direction == 3)
                {
                    if (array[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(array[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && array[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
                    {
                        ghost_directions[i] = ghost_direction;
                    }
                }
                else if (ghost_direction == 4)
                {
                    if (array[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(array[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && array[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
                    {
                        ghost_directions[i] = ghost_direction;
                    }
                }
                i++;
            }
            ghostTimer = 0.5f;
        }

        const float moveSpeed = 30.0f;

        if (ready)
        {
            M1.DisplayReady(window);
            window.display();
            readytime += deltaTime.asSeconds();
            if (readytime >= 3)
            {
                ready = false;
            }
            continue;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if ((array[pac_rows][p_cols - 1] != 1))
                movement_direction = 3; // Left
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if ((array[pac_rows - 1][p_cols] != 1))
                movement_direction = 2; // Up
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if ((array[pac_rows][p_cols + 1] != 1))
                movement_direction = 1; // Right
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if ((array[pac_rows + 1][p_cols] != 1))
                movement_direction = 4; // Down
        }
        if (pacmanTimer <= 0)
        {
            fakePacmanDirection = movement_direction;
            if (movement_direction == 3 && array[pac_rows][p_cols - 1] != 1) // left
            {
                check = array[pac_rows][p_cols - 1];
                score.calculate_score(check);
                obj.eat(check);
                obj.eatFruit(check);

                array[pac_rows][p_cols] = 0;
                array[pac_rows][p_cols - 1] = 8;
                p_cols--;
                // cout << pac_rows << " " << p_cols << endl;
                draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                          Pac_left, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                if ((pac_rows == 9 && p_cols == 0))
                {
                    array[pac_rows][p_cols] = 0;
                    pac_rows = 9;
                    p_cols = 21;
                    array[pac_rows][p_cols] = 0;
                    array[pac_rows][p_cols] = 8;
                    draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                              Pac_left, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                }
                // move pacman to the previous position
                place[pac_rows][p_cols].move(Vector2f(cell_size, 0));
            }
            else if (movement_direction == 1 && array[pac_rows][p_cols + 1] != 1) // right
            {
                check = array[pac_rows][p_cols + 1];
                score.calculate_score(check);
                obj.eat(check);
                obj.eatFruit(check);

                place[pac_rows][p_cols].move(Vector2f(moveSpeed * deltaTime.asSeconds(), 0));
                array[pac_rows][p_cols] = 0;
                array[pac_rows][p_cols + 1] = 8;
                p_cols++;
                draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                          pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                if ((pac_rows == 9 && p_cols == 21))
                {
                    array[pac_rows][p_cols] = 0;
                    pac_rows = 9;
                    p_cols = 0;
                    array[pac_rows][p_cols] = 0;
                    array[pac_rows][p_cols] = 8;
                    draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                              pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                }

                // move pacman to the previous position
                place[pac_rows][p_cols].move(Vector2f(-cell_size, 0));
            }
            else if (movement_direction == 2 && array[pac_rows - 1][p_cols] != 1) // Up
            {
                check = array[pac_rows - 1][p_cols];
                score.calculate_score(check);
                obj.eat(check);
                obj.eatFruit(check);
                place[pac_rows][p_cols].move(Vector2f(0, -moveSpeed * deltaTime.asSeconds()));
                array[pac_rows][p_cols] = 0;
                array[pac_rows - 1][p_cols] = 8;
                pac_rows--;
                draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                          Pac_up, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                // move pacman to the previous position
                place[pac_rows][p_cols].move(Vector2f(0, cell_size));
            }
            else if (movement_direction == 4 && array[pac_rows + 1][p_cols] != 1 && array[pac_rows + 1][p_cols] != 7) // down
            {
                check = array[pac_rows + 1][p_cols];
                score.calculate_score(check);
                obj.eat(check);
                obj.eatFruit(check);
                place[pac_rows][p_cols].move(Vector2f(0, moveSpeed * deltaTime.asSeconds()));
                array[pac_rows][p_cols] = 0;
                array[pac_rows + 1][p_cols] = 8;
                pac_rows++;
                draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                          Pac_down, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);

                // move pacman to the previous position
                place[pac_rows][p_cols].move(Vector2f(0, -cell_size));
            }
            else
            {
                fakePacmanDirection = 0;
            }
            pacmanTimer = 0.35f;
        }
        else
        {
            if (fakePacmanDirection == 1) // right
            {
                place[pac_rows][p_cols].move(Vector2f(cell_size / 0.35 * deltaTime.asSeconds(), 0));

                // set pacman texture to right
                place[pac_rows][p_cols].setTexture(&pacmanTexture);
            }
            else if (fakePacmanDirection == 3) // left
            {
                place[pac_rows][p_cols].move(Vector2f(-cell_size / 0.35 * deltaTime.asSeconds(), 0));

                // set pacman texture to left
                place[pac_rows][p_cols].setTexture(&Pac_left);
            }
            else if (fakePacmanDirection == 2) // up
            {
                place[pac_rows][p_cols].move(Vector2f(0, -cell_size / 0.35 * deltaTime.asSeconds()));

                // set pacman texture to up
                place[pac_rows][p_cols].setTexture(&Pac_up);
            }
            else if (fakePacmanDirection == 4) // down
            {
                place[pac_rows][p_cols].move(Vector2f(0, cell_size / 0.35 * deltaTime.asSeconds()));

                // set pacman texture to down
                place[pac_rows][p_cols].setTexture(&Pac_down);
            }
        }
        // check if pacman is colliding with ghost
        bool collision = false;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (ghosts[i][j] == 3 || ghosts[i][j] == 4 || ghosts[i][j] == 5 || ghosts[i][j] == 6)
                {
                    if (pac_rows == i && p_cols == j)
                    {
                        collision = true;

                        // call pacman.deduct life
                        if (!isLiveDecreased)
                        {
                            pacman.decrease_lives();
                            obj.Death();
                            isLiveDecreased = true;
                            if (pacman.is_game_over())
                            {
                                isGameOver = true;
                                break;
                            }
                            // move pac to the starting position
                            array[pac_rows][p_cols] = 0;
                            pac_rows = 15;
                            p_cols = 10;
                            array[pac_rows][p_cols] = 8;
                            draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
                                      pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
                            pacmanTimer = -0.35f;
                            movement_direction = 2;
                        }

                        // check if game is over
                    }
                }
            }
        }
        if (!collision)
        {
            isLiveDecreased = false;
        }
        if (isGameOver)
        {
            score.draw_game_over(window);
            obj.Death();
            window.display();
        }
        pacmanTimer -= deltaTime.asSeconds();
        ghostTimer -= deltaTime.asSeconds();
        ghost_speed -= deltaTime.asSeconds();
        window.display();
    }
}

void draw_maze(int array[][22], RectangleShape **place, int rows, int cols, int cell_size, Texture &wallTexture, Texture &palletTexture,
               Texture &pacmanTexture, RenderWindow &window, int &pac_rows, int &p_cols, Texture &cageTex, Texture &fruitTex, Texture &spaceTex)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int cellValue = array[i][j];

            RectangleShape rect;

            if (cellValue == 0) // space
            {
                rect.setTexture(&spaceTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 1) // wall
            {
                rect.setTexture(&wallTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 2) // dots
            {
                rect.setTexture(&palletTexture);
                rect.setSize(Vector2f(cell_size, cell_size));

                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 7) // cage
            {
                rect.setTexture(&cageTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 8)
            {
                pac_rows = i;
                p_cols = j;
                rect.setTexture(&pacmanTexture);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            else if (cellValue == 9)
            {
                rect.setTexture(&fruitTex);
                rect.setSize(Vector2f(cell_size, cell_size));
                rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
            }
            // Set the position of the rect based on the cell coordinates and size
            rect.setPosition(Vector2f(j * cell_size, i * cell_size));
            place[i][j] = rect;
        }
    }
}
void change_location(int ghosts[][22], RectangleShape **place, int rows, int cols, int cell_size, Texture &greenGhostTexture,
                     Texture &redGhostTexture, Texture &blueGhostTexture, Texture &pinkGhostTexture, Texture &wallTexture, Texture &spaceTex, Texture &cageTex)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            RectangleShape rect(Vector2f(cell_size, cell_size));
            rect.setPosition(Vector2f(j * cell_size, i * cell_size));

            int cell_val2 = ghosts[i][j];
            switch (cell_val2)
            {
            case 3:
                rect.setTexture(&greenGhostTexture);
                rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
                break;
            case 4:
                rect.setTexture(&blueGhostTexture);
                rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
                break;
            case 5:
                rect.setTexture(&redGhostTexture);
                rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
                break;
            case 6:
                rect.setTexture(&pinkGhostTexture);
                rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
                break;
            default:
                rect.setTexture(&spaceTex);
                rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
                break;
            }
            place[i][j] = rect;
        }
    }
}

int save_data(string user, int score)
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("PacmanDB.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT Score FROM UserInfo WHERE Username = ?";
    int exists = 0;
    rc = sqlite3_prepare_v2(db, sql_check, strlen(sql_check), &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    sqlite3_bind_text(stmt, 1, user.c_str(), user.length(), SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        exists = 1;
        int prev_score = sqlite3_column_int(stmt, 0);
        if (score > prev_score)
        {
            const char *sql_update = "UPDATE UserInfo SET Score = ? WHERE Username = ?";
            rc = sqlite3_prepare_v2(db, sql_update, strlen(sql_update), &stmt, NULL);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return -1;
            }
            sqlite3_bind_int(stmt, 1, score);
            sqlite3_bind_text(stmt, 2, user.c_str(), user.length(), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE)
            {
                fprintf(stderr, "Failed to update data: %s\n", sqlite3_errmsg(db));
                sqlite3_close(db);
                return -1;
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 2;
        }
    }
    if (!exists)
    {
        const char *sql_insert = "INSERT INTO UserInfo (Username, Score) VALUES (?, ?)";
        rc = sqlite3_prepare_v2(db, sql_insert, strlen(sql_insert), &stmt, NULL);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return -1;
        }
        sqlite3_bind_text(stmt, 1, user.c_str(), user.length(), SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, score);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return -1;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 3;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
}

int load_highscore()
{
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("PacmanDB.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    sqlite3_stmt *stmt;
    const char *sql_select = "SELECT MAX(Score) FROM UserInfo";
    rc = sqlite3_prepare_v2(db, sql_select, strlen(sql_select), &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }
    int highscore = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        highscore = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return highscore;
}

void admin_screen()
{
    Event event;
    RenderWindow window(VideoMode(800, 600), "Pacman Game (Admin Screen)", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }
        }
        window.clear();
        window.display();
    }
}

// Callback function for the SQLite query
static int callback(void *data, int argc, char **argv, char **azColName)
{
    CallbackData *cb_data = static_cast<CallbackData *>(data);

    std::string db_pass = argv[0] ? argv[0] : "";

    if (db_pass == cb_data->pass)
    {
        cb_data->result = 3; // both user and pass are correct
    }
    else
    {
        cb_data->result = 2; // user exists but pass is wrong
    }

    return 0;
}

int confirm_login_sqlite(const std::string &user, const std::string &pass)
{
    sqlite3 *db;
    CallbackData cb_data{user, pass, 1}; // default return value: user doesn't exist

    if (sqlite3_open("PacmanDB.db", &db))
    {
        std::cerr << "Error: could not open SQLite database" << std::endl;
        return -1;
    }

    std::string sql = "SELECT Password FROM Users WHERE Username = '" + user + "'";
    sqlite3_exec(db, sql.c_str(), callback, &cb_data, NULL);

    sqlite3_close(db);
    return cb_data.result;
}

int signup_sqlite(const std::string &user, const std::string &pass)
{
    sqlite3 *db;
    int return_val = 1; // default return value: user already exists

    if (sqlite3_open("PacmanDB.db", &db))
    {
        std::cerr << "Error: could not open SQLite database" << std::endl;
        return -1;
    }

    // First, check if the user already exists
    std::string check_sql = "SELECT COUNT(*) FROM Users WHERE Username = '" + user + "'";
    int count = 0;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, check_sql.c_str(), -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    // If the user does not exist, then insert the new user and password
    if (count == 0)
    {
        std::string insert_sql = "INSERT INTO Users (Username, Password) VALUES ('" + user + "', '" + pass + "')";
        if (sqlite3_exec(db, insert_sql.c_str(), NULL, 0, NULL) == SQLITE_OK)
        {
            return_val = 2; // signup successful
        }
        else
        {
            std::cerr << "Error: could not insert new user and password" << std::endl;
            return_val = -1; // unknown error
        }
    }

    sqlite3_close(db);
    return return_val;
}

void login_screen_error_blank()
{
    cout << "login screen called" << endl;
    Event event;
    Font impact;
    impact.loadFromFile("impact.ttf");
    Font Pixeloid;
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load PixeloidSans font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), LOGIN_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);
    // text, user doesnt exist
    Text user_doesnt_exist("Error: Field is Blank", Arial, 13);
    user_doesnt_exist.setFillColor(sf::Color::Red);
    user_doesnt_exist.setPosition(100, 214);
    // Bolden it
    user_doesnt_exist.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 350));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // load login_icon.png
        Texture loginTexture;
        loginTexture.loadFromFile("login_icon.png");
        Sprite loginSprite;
        loginSprite.setTexture(loginTexture);
        // set position
        loginSprite.setPosition(227, 49);
        // resize
        loginSprite.setScale(0.2, 0.2);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Confirm button has been clicked" << endl;
                        // getting username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        // check is user and pass are blank
                        if (username == "" || password == "")
                        {
                            cout << "\nfield is blank (error)" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            login_screen_error_blank();
                        }

                        if (username == "admin" || username == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        else if (password == "admin" || password == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        // checking if username and password are correct
                        int return_command = confirm_login_sqlite(username, password);
                        if (return_command == -1)
                        {
                            cout << "\nerror in opening database" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_database();
                        }
                        if (return_command == 1)
                        {
                            cout << "\nuser doesnt exist" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_user_doesnt_exist();
                        }
                        else if (return_command == 2)
                        {
                            cout << "\npassword incorrect" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_wrong_pass();
                        }
                        else if (return_command == 3)
                        {
                            cout << "\nyou have successfully logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = username;
                            ::current_password = password;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            maze_test();
                        }
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window); // textbox
            pass.drawTo(window); // textbox alternative
            window.draw(loginSprite);
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(user_doesnt_exist);
            window.display();
        }
    }
}

void login_screen_error_wrong_pass()
{
    cout << "login screen called" << endl;
    Event event;
    Font impact;
    impact.loadFromFile("impact.ttf");
    Font Pixeloid;
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load PixeloidSans font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), LOGIN_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);
    // text, user doesnt exist
    Text user_doesnt_exist("Error: Wrong Password", Arial, 13);
    user_doesnt_exist.setFillColor(sf::Color::Red);
    user_doesnt_exist.setPosition(100, 214);
    // Bolden it
    user_doesnt_exist.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 350));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // load login_icon.png
        Texture loginTexture;
        loginTexture.loadFromFile("login_icon.png");
        Sprite loginSprite;
        loginSprite.setTexture(loginTexture);
        // set position
        loginSprite.setPosition(227, 49);
        // resize
        loginSprite.setScale(0.2, 0.2);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Confirm button has been clicked" << endl;
                        // getting username and password
                        string username = user.return_text();
                        string password = pass.return_text();

                        if (username == "" || password == "")
                        {
                            cout << "\nfield is blank (error)" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            login_screen_error_blank();
                        }

                        if (username == "admin" || username == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        else if (password == "admin" || password == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        // checking if username and password are correct
                        int return_command = confirm_login_sqlite(username, password);
                        if (return_command == -1)
                        {
                            cout << "\nerror in opening database" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_database();
                        }
                        if (return_command == 1)
                        {
                            cout << "\nuser doesnt exist" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_user_doesnt_exist();
                        }
                        else if (return_command == 2)
                        {
                            cout << "\npassword incorrect" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_wrong_pass();
                        }
                        else if (return_command == 3)
                        {
                            cout << "\nyou have successfully logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = username;
                            ::current_password = password;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            maze_test();
                        }
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window); // textbox
            pass.drawTo(window); // textbox alternative
            window.draw(loginSprite);
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(user_doesnt_exist);
            window.display();
        }
    }
}

void login_screen_error_user_doesnt_exist()
{
    cout << "login screen called" << endl;
    Event event;
    Font impact;
    impact.loadFromFile("impact.ttf");
    Font Pixeloid;
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load PixeloidSans font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), LOGIN_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);
    // text, user doesnt exist
    Text user_doesnt_exist("Error: User doesn't exist", Arial, 13);
    user_doesnt_exist.setFillColor(sf::Color::Red);
    user_doesnt_exist.setPosition(90, 214);
    // Bolden it
    user_doesnt_exist.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 350));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // load login_icon.png
        Texture loginTexture;
        loginTexture.loadFromFile("login_icon.png");
        Sprite loginSprite;
        loginSprite.setTexture(loginTexture);
        // set position
        loginSprite.setPosition(227, 49);
        // resize
        loginSprite.setScale(0.2, 0.2);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Confirm button has been clicked" << endl;
                        // getting username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        if (username == "" || password == "")
                        {
                            cout << "\nfield is blank (error)" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            login_screen_error_blank();
                        }
                        if (username == "admin" || username == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        else if (password == "admin" || password == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        // checking if username and password are correct
                        int return_command = confirm_login_sqlite(username, password);
                        if (return_command == -1)
                        {
                            cout << "\nerror in opening database" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_database();
                        }
                        if (return_command == 1)
                        {
                            cout << "\nuser doesnt exist" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_user_doesnt_exist();
                        }
                        else if (return_command == 2)
                        {
                            cout << "\npassword incorrect" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_wrong_pass();
                        }
                        else if (return_command == 3)
                        {
                            cout << "\nyou have successfully logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = username;
                            ::current_password = password;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            maze_test();
                        }
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window); // textbox
            pass.drawTo(window); // textbox alternative
            window.draw(loginSprite);
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(user_doesnt_exist);
            window.display();
        }
    }
}

void login_screen_error_database()
{
    cout << "login screen called" << endl;
    Event event;
    Font impact;
    impact.loadFromFile("impact.ttf");
    Font Pixeloid;
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load PixeloidSans font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), LOGIN_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);
    // text, user doesnt exist
    Text user_doesnt_exist("Error: Database isn't opening", Arial, 13);
    user_doesnt_exist.setFillColor(sf::Color::Red);
    user_doesnt_exist.setPosition(90, 214);
    // Bolden it
    user_doesnt_exist.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 350));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // load login_icon.png
        Texture loginTexture;
        loginTexture.loadFromFile("login_icon.png");
        Sprite loginSprite;
        loginSprite.setTexture(loginTexture);
        // set position
        loginSprite.setPosition(227, 49);
        // resize
        loginSprite.setScale(0.2, 0.2);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Confirm button has been clicked" << endl;
                        // getting username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        if (username == "" || password == "")
                        {
                            cout << "\nfield is blank (error)" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            login_screen_error_blank();
                        }
                        if (username == "admin" || username == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        else if (password == "admin" || password == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            admin_screen();
                        }
                        // checking if username and password are correct
                        int return_command = confirm_login_sqlite(username, password);
                        if (return_command == -1)
                        {
                            cout << "\nerror in opening database" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_database();
                        }
                        else if (return_command == 1)
                        {
                            cout << "\nuser doesnt exist" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_user_doesnt_exist();
                        }
                        else if (return_command == 2)
                        {
                            cout << "\npassword incorrect" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_wrong_pass();
                        }
                        else if (return_command == 3)
                        {
                            cout << "\nyou have successfully logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = username;
                            ::current_password = password;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            maze_test();
                        }
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window); // textbox
            pass.drawTo(window); // textbox alternative
            window.draw(loginSprite);
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(user_doesnt_exist);
            window.display();
        }
    }
}

void login_screen() // function
{
    cout << "login screen called" << endl;
    Event event;
    Font impact;
    impact.loadFromFile("impact.ttf");
    Font Pixeloid;
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load PixeloidSans font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), LOGIN_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 350));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // load login_icon.png
        Texture loginTexture;
        loginTexture.loadFromFile("login_icon.png");
        Sprite loginSprite;
        loginSprite.setTexture(loginTexture);
        // set position
        loginSprite.setPosition(227, 49);
        // resize
        loginSprite.setScale(0.2, 0.2);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Confirm button has been clicked" << endl;
                        // getting username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        if (username == "" || password == "")
                        {
                            cout << "\nfield is blank (error)" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            login_screen_error_blank();
                        }
                        if (username == "admin" || username == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            admin_screen();
                        }
                        else if (password == "admin" || password == "Admin")
                        {
                            cout << "\nadmin has logged in" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            // setting current username and password
                            ::current_username = "admin";
                            ::current_password = "admin";
                            admin_screen();
                        }
                        // checking if username and password are correct
                        int return_command = confirm_login_sqlite(username, password);
                        if (return_command == 1)
                        {
                            cout << "\nuser doesnt exist" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_user_doesnt_exist();
                        }
                        else if (return_command == 2)
                        {
                            cout << "\npassword incorrect" << endl
                                 << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            login_screen_error_wrong_pass();
                        }
                        else if (return_command == 3)
                        {
                            cout << "\nyou have successfully logged in" << endl
                                 << endl;
                            // setting current username and password
                            ::current_username = username;
                            ::current_password = password;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            maze_test();
                        }
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window); // textbox
            pass.drawTo(window); // textbox alternative
            window.draw(loginSprite);
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.display();
        }
    }
}

void signup_admin_not_allowed()
{
    // start of function
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);

    // load error text
    Text error("Error: Admin is not allowed", Arial, 13);
    error.setFillColor(sf::Color::Red);
    error.setPosition(80, 214);
    // Bolden it
    error.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {

                            return_val = signup_sqlite(username, password);
                        }

                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.draw(error);
            window.display();
        }
    }
}

void signup_screen_error_blank()
{
    // start of function
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);

    // load error text
    Text error("Error: Fields cannot be Blank", Arial, 13);
    error.setFillColor(sf::Color::Red);
    error.setPosition(80, 214);
    // Bolden it
    error.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {

                            return_val = signup_sqlite(username, password);
                        }

                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.draw(error);
            window.display();
        }
    }
}

void signup_screen_error_already_exists()
{
    // start of function
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);

    // load error text
    Text error("Error: User already exists", Arial, 13);
    error.setFillColor(sf::Color::Red);
    error.setPosition(85, 214);
    // Bolden it
    error.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {

                            return_val = signup_sqlite(username, password);
                        }

                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.draw(error);
            window.display();
        }
    }
}
void signup_screen_error_unknown()
{
    // start of function
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);

    // load error text
    Text error("Error: Unknown Error", Arial, 13);
    error.setFillColor(sf::Color::Red);
    error.setPosition(90, 214);
    // Bolden it
    error.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {

                            return_val = signup_sqlite(username, password);
                        }

                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.draw(error);
            window.display();
        }
    }
}
void signup_screen_error_database()
{
    // start of function
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);

    // load error text
    Text error("Error: Database isn't opening", Arial, 13);
    error.setFillColor(sf::Color::Red);
    error.setPosition(85, 214);
    // Bolden it
    error.setStyle(sf::Text::Bold);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();
                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {

                            return_val = signup_sqlite(username, password);
                        }

                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.draw(error);
            window.display();
        }
    }
}

void signup_screen() // function
{
    cout << "sign up screen called" << endl;
    Event event;
    Font impact;
    Font Pixeloid;
    impact.loadFromFile("impact.ttf");
    Pixeloid.loadFromFile("PixeloidSans.ttf");
    if (!Pixeloid.loadFromFile("PixeloidSans.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    RenderWindow window(VideoMode(LOGIN_SIGNUP_SCREEN_WIDTH, LOGIN_SIGNUP_SCREEN_HEIGHT), SIGNUP_SCREEN_TITLE, Style::Close | Style::Titlebar);
    // creating textbox for username
    TextBox user(15, Color::Black, false); // testing textbox
    user.setFont(impact);
    user.setPosition(Vector2f(209, 116));
    user.setLimit(true, 25);
    // creating textbox Alternative for password
    TextBox_Alternate pass(15, Color::Black, false); // testing textbox
    pass.setFont(impact);
    pass.setPosition(Vector2f(209, 169));
    pass.setLimit(true, 25);
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    // OK Button
    Text Confirm("Confirm", Arial, 13);
    Confirm.setFillColor(sf::Color::Black);
    Confirm.setPosition(427, 214);
    // Bolden it
    Confirm.setStyle(sf::Text::Bold);
    // Cancel Button
    Text Cancel("Cancel", Arial, 13);
    Cancel.setFillColor(sf::Color::Black);
    Cancel.setPosition(329, 214);
    // Bolden it
    Cancel.setStyle(sf::Text::Bold);

    // load signup button
    Texture signupTexture;
    signupTexture.loadFromFile("signup_icon.png");
    Sprite signupSprite;
    signupSprite.setTexture(signupTexture);
    // set position
    signupSprite.setPosition(202, 41);
    // resize
    signupSprite.setScale(0.2, 0.2);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setKeyRepeatEnabled(true);
        window.setPosition(Vector2i(693.5, 393));
        // load form from .png file
        Texture formTexture;
        formTexture.loadFromFile("login_page.png");
        Sprite formSprite;
        formSprite.setTexture(formTexture);
        // set position
        formSprite.setPosition(0, 0);
        // resize
        formSprite.setScale(1.3, 1.3);

        // set textbox
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            user.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            user.setSelected(false);
        }

        // set textbox Alternative
        if (Keyboard::isKeyPressed(Keyboard::Tab))
        {
            pass.setSelected(true);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pass.setSelected(false);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Confirm.setFillColor(sf::Color::Green);
                }
                else
                {
                    Confirm.setFillColor(sf::Color::Black);
                }
                if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    Cancel.setFillColor(sf::Color::Red);
                }
                else
                {
                    Cancel.setFillColor(sf::Color::Black);
                }
            }
            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }
            if (event.type == Event::TextEntered)
            {
                user.typedOn(event);
            }
            if (event.type == Event::TextEntered)
            {
                pass.typedOn(event);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Confirm.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Conirm button has been clicked" << endl;
                        // get username and password
                        string username = user.return_text();
                        string password = pass.return_text();

                        int return_val;

                        if (username == "admin" || password == "admin" || username == "Admin" || password == "Admin")
                        {
                            cout << "Username or password cannot be admin!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_admin_not_allowed();
                        }

                        if (username == "" || password == "")
                        {
                            cout << "Username or password cannot be empty!" << endl;
                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_blank();
                        }
                        else
                        {
                            return_val = signup_sqlite(username, password);
                        }
                        if (return_val == -1)
                        {
                            cout << "Database error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_database();
                        }
                        else if (return_val == 1)
                        {
                            cout << "Username already exists!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_already_exists();
                        }
                        else if (return_val == 2)
                        {
                            cout << "Signup successful!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            menu_screen_signup_success();
                        }
                        else
                        {
                            cout << "Unknown error!" << endl;

                            window.close();
                            this_thread::sleep_for(chrono::milliseconds(200));
                            // call function to open new rendered window for playing
                            signup_screen_error_unknown();
                        }

                        /*window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();*/
                    }
                    else if (Cancel.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Cancel button has been clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        menu_screen();
                    }
                }
            }
            window.clear();
            window.draw(formSprite);
            user.drawTo(window);  // textbox
            pass.drawTo(window);  // textbox alternative
            window.draw(Confirm); // Confirm button
            window.draw(Cancel);  // Cancel button
            window.draw(signupSprite);
            window.display();
        }
    }
}

void menu_screen_signup_success()
{
    cout << "menu screen called" << endl;
    RenderWindow window(VideoMode(MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT), SCREEN_TITLE, Style::Close | Style::Titlebar);
    Event event;
    Font impact;
    Font lato_Italic;
    impact.loadFromFile("impact.ttf");
    cout << "loading font, impact.ttf..." << endl;
    lato_Italic.loadFromFile("Lato-Italic.ttf");
    cout << "loading font, Lato-Italic.ttf..." << endl;
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!lato_Italic.loadFromFile("Lato-Italic.ttf"))
    {
        cout << "Unable to load Lato-Italic font file!" << endl;
    }
    // load arial font
    Font Arial;
    Arial.loadFromFile("arial.ttf");
    // if error
    if (!Arial.loadFromFile("arial.ttf"))
    {
        cout << "Unable to load arial font file!" << endl;
    }
    else
    {
        cout << "loading font, arial.ttf..." << endl;
    }
    // text called signup successful
    Text signupSuccessful(">> Signed up Successfully", Arial, 20);
    signupSuccessful.setFillColor(sf::Color::Green);
    // turn bold
    signupSuccessful.setStyle(sf::Text::Bold);
    // set position
    signupSuccessful.setPosition(915, 850);

    // create the text objects
    // Guest Button
    Text playAsGuest("Play as Guest", lato_Italic, 45);
    playAsGuest.setFillColor(sf::Color::White);
    playAsGuest.setPosition(465, 435);
    cout << "Loading text, the game as a guest..." << endl;
    // Login Button
    Text login("Login", lato_Italic, 45);
    login.setFillColor(sf::Color::White);
    login.setPosition(538, 533);
    cout << "loading text, login..." << endl;
    // Sign Up Button
    Text signUp("Sign Up", lato_Italic, 45);
    signUp.setFillColor(sf::Color::White);
    signUp.setPosition(520, 632);
    cout << "loading text, signup..." << endl;
    // Exit Button
    Text exit("Exit", lato_Italic, 45);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(548, 732);
    cout << "Exiting program..." << endl;

    // load sound from click.wav file
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setPosition(Vector2i(360, 23));
        window.setKeyRepeatEnabled(true);
        // load background from.png file
        Texture background;
        background.loadFromFile("pacman_menu_background.png");
        // check error
        if (!background.loadFromFile("pacman_menu_background.png"))
        {
            // Error check on console
            cout << "Error loading Menu background image" << endl;
        }
        // create background sprite
        Sprite sBackground(background);

        // load title logo from png file
        Texture title_logo;
        title_logo.loadFromFile("pacman_horror_logo.png");
        // check error
        if (!title_logo.loadFromFile("pacman_horror_logo.png"))
        {
            // Error check on console
            cout << "Error loading Menu title logo image" << endl;
        }
        // create logo sprite
        Sprite sTitleLogo(title_logo);
        sTitleLogo.setPosition(258, 62);

        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (playAsGuest.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    playAsGuest.setFillColor(sf::Color::Blue);
                }
                else
                {
                    playAsGuest.setFillColor(sf::Color::White);
                }
                if (login.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    login.setFillColor(sf::Color::Yellow);
                }
                else
                {
                    login.setFillColor(sf::Color::White);
                }
                if (signUp.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    signUp.setFillColor(sf::Color::Green);
                }
                else
                {
                    signUp.setFillColor(sf::Color::White);
                }
                if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    exit.setFillColor(sf::Color::Red);
                }
                else
                {
                    exit.setFillColor(sf::Color::White);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (playAsGuest.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Play as Guest button clicked" << endl;
                        // play as guest
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        maze_test();
                    }
                    else if (login.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Login button clicked" << endl;
                        ::current_username = "Guest";
                        ::current_password = "Guest";
                        // login
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        login_screen();
                    }
                    else if (signUp.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Sign Up button clicked" << endl;
                        // sign up
                        this_thread::sleep_for(chrono::milliseconds(200));
                        window.close();
                        // call function to open new rendered window for playing
                        signup_screen();
                    }
                    else if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Exit button clicked" << endl;
                        // wait before executing next line
                        this_thread::sleep_for(chrono::milliseconds(400));
                        window.close(); // exit the program
                        break;
                        std::exit(0);
                        // exit the program
                    }
                }
            }
        }

        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.clear();           // Clear screen
        window.draw(sBackground); // draw background
        window.draw(sTitleLogo);  // draw title logo
        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.draw(playAsGuest);      // draw first button
        window.draw(login);            // draw login button
        window.draw(signUp);           // draw sign up button
        window.draw(exit);             // draw exit button
        window.draw(signupSuccessful); // draw sign up successful message
        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.display(); // display screen
        // <----------------------------------------------------->
        // <----------------------------------------------------->
    }
}

void menu_screen()
{
    cout << "menu screen called" << endl;
    RenderWindow window(VideoMode(MENU_SCREEN_WIDTH, MENU_SCREEN_HEIGHT), SCREEN_TITLE, Style::Close | Style::Titlebar);
    Event event;
    Font impact;
    Font lato_Italic;
    impact.loadFromFile("impact.ttf");
    cout << "loading font, impact.ttf..." << endl;
    lato_Italic.loadFromFile("Lato-Italic.ttf");
    cout << "loading font, Lato-Italic.ttf..." << endl;
    if (!impact.loadFromFile("impact.ttf"))
    {
        cout << "Unable to load impact font file!" << endl;
    }
    if (!lato_Italic.loadFromFile("Lato-Italic.ttf"))
    {
        cout << "Unable to load Lato-Italic font file!" << endl;
    }

    // create the text objects
    // Guest Button
    Text playAsGuest("Play as Guest", lato_Italic, 45);
    playAsGuest.setFillColor(sf::Color::White);
    playAsGuest.setPosition(465, 435);
    cout << "Loading text, the game as a guest..." << endl;
    // Login Button
    Text login("Login", lato_Italic, 45);
    login.setFillColor(sf::Color::White);
    login.setPosition(538, 533);
    cout << "loading text, login..." << endl;
    // Sign Up Button
    Text signUp("Sign Up", lato_Italic, 45);
    signUp.setFillColor(sf::Color::White);
    signUp.setPosition(520, 632);
    cout << "loading text, signup..." << endl;
    // Exit Button
    Text exit("Exit", lato_Italic, 45);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(548, 732);
    cout << "Exiting program..." << endl;

    // load sound from click.wav file
    SoundBuffer clickBuffer;
    if (!clickBuffer.loadFromFile("click.wav"))
    {
        cout << "Unable to load click sound file!" << endl;
    }
    Sound clickSound(clickBuffer);
    while (window.isOpen())
    {
        window.setFramerateLimit(FPS);
        window.setPosition(Vector2i(360, 23));
        window.setKeyRepeatEnabled(true);
        // load background from.png file
        Texture background;
        background.loadFromFile("pacman_menu_background.png");
        // check error
        if (!background.loadFromFile("pacman_menu_background.png"))
        {
            // Error check on console
            cout << "Error loading Menu background image" << endl;
        }
        // create background sprite
        Sprite sBackground(background);

        // load title logo from png file
        Texture title_logo;
        title_logo.loadFromFile("pacman_horror_logo.png");
        // check error
        if (!title_logo.loadFromFile("pacman_horror_logo.png"))
        {
            // Error check on console
            cout << "Error loading Menu title logo image" << endl;
        }
        // create logo sprite
        Sprite sTitleLogo(title_logo);
        sTitleLogo.setPosition(258, 62);

        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
                this_thread::sleep_for(chrono::milliseconds(400));
                std::exit(0);
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (playAsGuest.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    playAsGuest.setFillColor(sf::Color::Blue);
                }
                else
                {
                    playAsGuest.setFillColor(sf::Color::White);
                }
                if (login.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    login.setFillColor(sf::Color::Yellow);
                }
                else
                {
                    login.setFillColor(sf::Color::White);
                }
                if (signUp.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    signUp.setFillColor(sf::Color::Green);
                }
                else
                {
                    signUp.setFillColor(sf::Color::White);
                }
                if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    exit.setFillColor(sf::Color::Red);
                }
                else
                {
                    exit.setFillColor(sf::Color::White);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (playAsGuest.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Play as Guest button clicked" << endl;
                        // play as guest
                        ::current_username = "Guest";
                        ::current_password = "Guest";
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        maze_test();
                    }
                    else if (login.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Login button clicked" << endl;
                        // login
                        window.close();
                        this_thread::sleep_for(chrono::milliseconds(200));
                        // call function to open new rendered window for playing
                        login_screen();
                    }
                    else if (signUp.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Sign Up button clicked" << endl;
                        // sign up
                        this_thread::sleep_for(chrono::milliseconds(200));
                        window.close();
                        // call function to open new rendered window for playing
                        signup_screen();
                    }
                    else if (exit.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        clickSound.play();
                        cout << "Exit button clicked" << endl;
                        // wait before executing next line
                        this_thread::sleep_for(chrono::milliseconds(400));
                        window.close(); // exit the program
                        break;
                        std::exit(0);
                        // exit the program
                    }
                }
            }
        }

        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.clear();           // Clear screen
        window.draw(sBackground); // draw background
        window.draw(sTitleLogo);  // draw title logo
        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.draw(playAsGuest); // draw first button
        window.draw(login);       // draw login button
        window.draw(signUp);      // draw sign up button
        window.draw(exit);        // draw exit button
        // <----------------------------------------------------->
        // <----------------------------------------------------->
        window.display(); // display screen
        // <----------------------------------------------------->
        // <----------------------------------------------------->
    }
}

int main()
{
    // Program Starts and goes to menu screen
    cout << "main function called" << endl;
    menu_screen();

    return 0;
}