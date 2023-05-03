//// headers
//#include <iostream>
//#include "SFML/Window.hpp"
//#include "SFML/Graphics.hpp"
//#include "SFML/Audio.hpp"
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <chrono>
//#include <thread>
//#include <random>
//using namespace std;
//using namespace sf;
//
//void draw_maze(int array[][22], RectangleShape** place, int rows, int cols, int cell_size, Texture& wallTexture, Texture& palletTexture,
//	Texture& pacmanTexture, RenderWindow& window, int& pac_rows, int& p_cols, Texture& cageTex, Texture& fruitTex, Texture& spaceTex);
//void change_location(int ghosts[][22], RectangleShape** place, int rows, int cols, int cell_size, Texture& greenGhostTexture,
//	Texture& redGhostTexture, Texture& blueGhostTexture, Texture& pinkGhostTexture, Texture& wallTexture, Texture& spaceTex, Texture& cageTex);
//class Score
//{
//protected:
//	int score;
//	Text scoreText;
//	Text highscoreText;
//	Text gameOverText;
//	Text restartText;
//	Text winText;
//	Font font;
//
//public:
//	Score() : score(0), scoreText(), highscoreText(), gameOverText(), winText(), restartText()
//	{
//		font.loadFromFile("Fonts/Roboto-Black.ttf");
//		scoreText.setFont(font);
//		scoreText.setCharacterSize(24);
//		scoreText.setFillColor(Color::White);
//		scoreText.setPosition(150, 0);
//
//		highscoreText.setFont(font);
//		highscoreText.setCharacterSize(24);
//		highscoreText.setFillColor(Color::White);
//		highscoreText.setPosition(400, 0);
//
//		gameOverText.setFont(font);
//		gameOverText.setString("Game Over");
//		gameOverText.setCharacterSize(30);
//		gameOverText.setFillColor(Color::Red);
//		gameOverText.setPosition(450, 550);
//
//		winText.setFont(font);
//		winText.setString("You Win");
//		winText.setCharacterSize(24);
//		winText.setFillColor(Color::White);
//		winText.setPosition(0, 60);
//
//		restartText.setFont(font);
//		restartText.setString("Press R to restart");
//		restartText.setCharacterSize(24);
//		restartText.setFillColor(Color::White);
//		restartText.setPosition(0, 90);
//	}
//	void draw_score(RenderWindow& window)
//	{
//		scoreText.setString("Score: " + to_string(score));
//		window.draw(scoreText);
//	}
//	void draw_highscore(RenderWindow& window)
//	{
//		int highscore = (score > 500) ? score : 500;
//		highscoreText.setString("Highscore: " + to_string(highscore));
//		window.draw(highscoreText);
//	}
//	void draw_game_over(RenderWindow& window)
//	{
//		gameOverText.setString("Game Over");
//		window.draw(gameOverText);
//	}
//	void draw_win(RenderWindow& window)
//	{
//		winText.setString("You Win");
//		window.draw(winText);
//	}
//	void draw_restart(RenderWindow& window)
//	{
//		restartText.setString("Press R to restart");
//		window.draw(restartText);
//	}
//	void calculate_score(int cellValue)
//	{
//		if (cellValue == 2)
//		{
//			score += 10;
//		}
//		else if (cellValue == 9)
//		{
//			score += 50;
//		}
//	}
//	bool is_win()
//	{
//		if (score == 1660) // total dots are 146 and 4 are the fruits
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//};
//class Pacman
//{
//private:
//	int x, y;
//	int lives;
//	Text livesText;
//	Font f1;
//
//public:
//	Pacman() : x(10), y(15), lives(3), livesText()
//	{
//		f1.loadFromFile("Fonts/Roboto-Black.ttf");
//		livesText.setFont(f1);
//		livesText.setCharacterSize(24);
//		livesText.setFillColor(Color::White);
//		livesText.setPosition(725, 0);
//	}
//	void decrease_lives()
//	{
//		lives--;
//	}
//	// void calculate_lives(Texture& pac, Texture& ghost1, Texture& ghost2, Texture& ghost3, Texture& ghost4)
//
//	bool is_game_over()
//	{
//		if (lives == 0)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	void draw_lives(RenderWindow& window)
//	{
//		livesText.setString("Lives: " + to_string(lives));
//		window.draw(livesText);
//	}
//};
//class Sounds
//{
//public:
//	Sounds()
//	{
//		if (!beginning_sound_buffer.loadFromFile("beginning.wav"))
//		{
//			throw "Failed to load beginning.wav";
//		}
//		beginning_sound.setBuffer(beginning_sound_buffer);
//
//		if (!chomp_sound_buffer.loadFromFile("chomp.wav"))
//		{
//			throw "Failed to load chomp.wav";
//		}
//		chomp_sound.setBuffer(chomp_sound_buffer);
//
//		if (!death_sound_buffer.loadFromFile("death.wav"))
//		{
//			throw "Failed to load death.wav";
//		}
//		death_sound.setBuffer(death_sound_buffer);
//
//		if (!intermission_sound_buffer.loadFromFile("intermission.wav"))
//		{
//			throw "Failed to load intermission.wav";
//		}
//		intermission_sound.setBuffer(intermission_sound_buffer);
//
//		if (!eatfruit_sound_buffer.loadFromFile("eatfruit.wav"))
//		{
//			throw "Failed to load eatfruit.wav";
//		}
//		eatfruit_sound.setBuffer(eatfruit_sound_buffer);
//
//		if (!eatghost_sound_buffer.loadFromFile("eatghost.wav"))
//		{
//			throw "Failed to load eatghost.wav";
//		}
//		eatghost_sound.setBuffer(eatghost_sound_buffer);
//	}
//
//	void playSound(const std::string& filename)
//	{
//		SoundBuffer sound_buffer;
//		if (!sound_buffer.loadFromFile(filename))
//		{
//			throw "Failed to load ";
//		}
//		Sound sound;
//		sound.setBuffer(sound_buffer);
//		sound.play();
//	}
//
//	void beginning()
//	{
//		beginning_sound.play();
//	}
//
//	void eat(int check)
//	{
//		if (check == 2)
//		{
//			chomp_sound.play();
//		}
//	}
//
//	void Death()
//	{
//		death_sound.play();
//	}
//
//	void win()
//	{
//		intermission_sound.play();
//	}
//
//	void eatFruit(int check)
//	{
//		if (check == 9)
//		{
//			eatfruit_sound.play();
//		}
//	}
//
//	void eatGhost()
//	{
//		eatghost_sound.play();
//	}
//
//private:
//	SoundBuffer beginning_sound_buffer;
//	SoundBuffer chomp_sound_buffer;
//	SoundBuffer death_sound_buffer;
//	SoundBuffer intermission_sound_buffer;
//	SoundBuffer eatfruit_sound_buffer;
//	SoundBuffer eatghost_sound_buffer;
//
//	Sound beginning_sound;
//	Sound chomp_sound;
//	Sound death_sound;
//	Sound intermission_sound;
//	Sound eatfruit_sound;
//	Sound eatghost_sound;
//};
//class Messages
//{
//private:
//	Text ReadyText;
//	Font f2;
//
//public:
//	Messages() : ReadyText()
//	{
//		f2.loadFromFile("Fonts/Roboto-Black.ttf");
//		ReadyText.setFont(f2);
//		ReadyText.setCharacterSize(30);
//		ReadyText.setFillColor(Color::Red);
//		ReadyText.setPosition(450, 550);
//	}
//	void DisplayReady(RenderWindow& window)
//	{
//		ReadyText.setString("  READY ! ");
//		window.draw(ReadyText);
//	}
//};
//int main()
//{
//	RenderWindow window(VideoMode(1100, 1100), "PAC MAN", Style::Default);
//	window.setFramerateLimit(90);
//	// disable stretching
//	window.setVerticalSyncEnabled(true);
//	Score score;
//	Pacman pacman;
//	Messages M1;
//
//	int rows = 21, cols = 22;
//	float cell_size = 50;
//	int array[21][22] =
//	{
//		
//		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},															// 0
//		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},		// 1
//		{0, 1, 9, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 9, 1},		// 2
//		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},		// 3
//		{0, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1},		// 4
//		{0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},		// 5
//		{0, 1, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1},		// 6
//		{0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},		// 7
//		{1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 7, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1}, // 8
//		{0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0},	// 9
//		{1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1}, // 10
//		{0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0},		// 11
//		{0, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1},		// 12
//		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1},		// 13
//		{0, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},		// 14
//		{0, 1, 9, 2, 1, 2, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 1, 2, 9, 1},		// 15
//		{0, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1},		// 16
//		{0, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1},		// 17
//		{0, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1},		// 18
//		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},		// 19
//		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},		// 20
//	};
//	int ghosts[21][22] =
//	{
//		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
//		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
//		{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//		{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
//		{0, 0, 0, 0, 1, 0, 1, 0, 6, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
//		{1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
//		{0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 1, 4, 0, 5, 0, 0, 0, 0 },
//		{1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
//		{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
//		{0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
//		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
//		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
//		{0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
//		{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//		{0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
//		{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//	};
//	sf::Texture wallTexture;
//	wallTexture.loadFromFile("wall.png");
//
//	sf::Texture palletTexture;
//	palletTexture.loadFromFile("2pallets.png");
//
//	sf::Texture greenGhostTexture;
//	greenGhostTexture.loadFromFile("green.png");
//
//	sf::Texture redGhostTexture;
//	redGhostTexture.loadFromFile("red.png");
//
//	sf::Texture blueGhostTexture;
//	blueGhostTexture.loadFromFile("blue.png");
//
//	sf::Texture pinkGhostTexture;
//	pinkGhostTexture.loadFromFile("pink.png");
//
//	sf::Texture pacmanTexture;
//	pacmanTexture.loadFromFile("pacman.png");
//
//	Texture spaceTex;
//	spaceTex.loadFromFile("space.png");
//
//	Texture fruitTex;
//	fruitTex.loadFromFile("fruit.png");
//
//	Texture cageTex;
//	cageTex.loadFromFile("cage.png");
//
//	Texture Pac_left;
//	Pac_left.loadFromFile("Left.png");
//
//	Texture Pac_up;
//	Pac_up.loadFromFile("Up.png");
//
//	Texture Pac_down;
//	Pac_down.loadFromFile("Down.png");
//
//	RectangleShape** place = new RectangleShape * [rows];
//	RectangleShape** place2 = new RectangleShape * [rows];
//	int pac_rows;
//	int p_cols;
//	for (int i = 0; i < rows; i++)
//	{
//		place[i] = new RectangleShape[cols];
//		place2[i] = new RectangleShape[cols];
//		for (int j = 0; j < cols; j++)
//		{
//			int cellValue = array[i][j];
//			int cell_val2 = ghosts[i][j];
//			RectangleShape rect;
//			if (cellValue == 0) // space
//			{
//				rect.setTexture(&spaceTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 1) // wall
//			{
//				rect.setTexture(&wallTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place[i][j] = rect;
//			}
//			else if (cellValue == 2) // dots
//			{
//				rect.setTexture(&palletTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place[i][j] = rect;
//			}
//			else if (cell_val2 == 3) // green ghost
//			{
//
//				rect.setTexture(&greenGhostTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place2[i][j] = rect;
//			}
//			else if (cell_val2 == 4) // blue one
//			{
//				rect.setTexture(&blueGhostTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place2[i][j] = rect;
//			}
//			else if (cell_val2 == 5) // red one
//			{
//				rect.setTexture(&redGhostTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place2[i][j] = rect;
//			}
//			else if (cell_val2 == 6) // pink one
//			{
//				rect.setTexture(&pinkGhostTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place2[i][j] = rect;
//			}
//			else if (cellValue == 7) // cage
//			{
//				rect.setTexture(&cageTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place[i][j] = rect;
//			}
//			else if (cellValue == 8)
//			{
//				pac_rows = i;
//				p_cols = j;
//				rect.setTexture(&pacmanTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place[i][j] = rect;
//			}
//			else if (cellValue == 9)
//			{
//				rect.setTexture(&fruitTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//				rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//				place[i][j] = rect;
//			}
//		}
//	}
//	Clock deltaClock = Clock();
//	bool moving_Left = false;
//	int numFrames1 = 10; // Display the text for 5 seconds at 60 fps
//	int frameCount1 = 0;
//	int check;
//	// game loop
//	int movement_direction = 1;
//	Sounds obj;
//	obj.beginning(); // ready wala scene
//
//	int ghost_rows[4] = { 9, 9, 9, 7 };
//	int ghost_cols[4] = { 7, 13, 15, 8 };
//	Clock A = Clock();
//
//	random_device rd;
//	std::mt19937 rng(rd());
//	std::uniform_int_distribution<int> dist(1, 4);
//	double pacmanTimer = 0;
//	double ghostTimer = 0;
//	int ghost_directions[4] = { 1, 1, 1, 1 };
//	double ghost_speed = 0;
//	int fakePacmanDirection = 0;
//
//	Clock deltaClock1;
//	Time deltaTime;
//
//	bool isGameOver = false;
//	bool isLiveDecreased = false;
//	double gameOverTimer = 0;
//	double gameWinTimer = 0;
//	bool ready = true;
//	double readytime = 0;
//	while (window.isOpen())
//	{
//
//		deltaTime = deltaClock1.restart();
//		Event event;
//		// set background color to black
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//			{
//
//				window.close();
//			}
//		}
//
//		window.clear(Color::Black);
//
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < cols; j++)
//			{
//				score.draw_score(window);
//				score.draw_highscore(window);
//				pacman.draw_lives(window);
//				window.draw(place[i][j]);
//			}
//		}
//
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < cols; j++)
//			{
//				if (ghosts[i][j] != 1 && ghosts[i][j] != 0 && ghosts[i][j] != 7)
//				{
//					window.draw(place2[i][j]);
//				}
//			}
//		}
//		if (isGameOver)
//		{
//			score.draw_game_over(window);
//			window.display();
//			gameOverTimer += deltaTime.asSeconds();
//			if (gameOverTimer >= 3)
//			{
//				window.close();
//			}
//			continue;
//		}
//		if (score.is_win())
//		{
//			score.draw_win(window);
//			obj.win();
//			window.display();
//			gameWinTimer += deltaTime.asSeconds();
//			if (gameWinTimer >= 3)
//			{
//				window.close();
//			}
//			continue;
//		}
//		if (ghost_speed < 0.0f)
//		{
//			// move ghosts
//			for (int i = 0; i < 4; i++)
//			{
//				if (ghost_directions[i] == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
//				{
//
//					// Move ghost right
//					ghosts[ghost_rows[i]][(ghost_cols[i] + 1)] = ghosts[ghost_rows[i]][ghost_cols[i]];
//					ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
//					ghost_cols[i] += 1;
//					// Update ghost timer
//					change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
//						redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
//				}
//				else if (ghost_directions[i] == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
//				{
//					// Move ghost down
//					ghosts[(ghost_rows[i] + 1)][ghost_cols[i]] = ghosts[ghost_rows[i]][ghost_cols[i]];
//					ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
//					ghost_rows[i] += 1;
//					// Update ghost timer
//					change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
//						redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
//				}
//				else if (ghost_directions[i] == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
//				{
//					// Move ghost left
//					ghosts[ghost_rows[i]][(ghost_cols[i] - 1)] = ghosts[ghost_rows[i]][ghost_cols[i]];
//					ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
//					ghost_cols[i] -= 1;
//					// Update ghost timer
//					change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
//						redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
//				}
//				else if (ghost_directions[i] == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
//				{
//					// Move ghost up
//					ghosts[(ghost_rows[i] - 1)][ghost_cols[i]] = ghosts[ghost_rows[i]][ghost_cols[i]];
//					ghosts[ghost_rows[i]][ghost_cols[i]] = 0;
//					ghost_rows[i] -= 1;
//					// Update ghost timer
//					change_location(ghosts, place2, rows, cols, cell_size, greenGhostTexture,
//						redGhostTexture, blueGhostTexture, pinkGhostTexture, wallTexture, spaceTex, cageTex);
//				}
//				else
//				{
//					// change direction to one that is not blocked
//					int direction = dist(rng);
//					while (true)
//					{
//						if (direction == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
//						{
//							break;
//						}
//						else if (direction == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
//						{
//							break;
//						}
//						else if (direction == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
//						{
//							break;
//						}
//						else if (direction == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
//						{
//							break;
//						}
//						direction = dist(rng);
//					}
//					ghost_directions[i] = direction;
//				}
//			}
//			ghost_speed = 0.5f;
//		}
//		else
//		{
//			// use move function
//			for (int i = 0; i < 4; i++)
//			{
//				if (ghost_directions[i] == 1 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
//				{
//					place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(cell_size / 0.5f * deltaTime.asSeconds(), 0));
//				}
//				else if (ghost_directions[i] == 2 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
//				{
//					place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(0, cell_size / 0.5f * deltaTime.asSeconds()));
//				}
//				else if (ghost_directions[i] == 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(ghosts[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && ghosts[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
//				{
//					place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(-cell_size / 0.5f * deltaTime.asSeconds(), 0));
//				}
//				else if (ghost_directions[i] == 4 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(ghosts[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && ghosts[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
//				{
//					place2[ghost_rows[i]][ghost_cols[i]].move(Vector2f(0, -cell_size / 0.5f * deltaTime.asSeconds()));
//				}
//			}
//		}
//		if (ghostTimer < 0 && ghost_speed == 0.5f)
//		{
//			int num_ghosts = 4;
//			int i = 0;
//			// chrono::steady_clock::now().time_since_epoch().count();
//
//			int ghost_direction;
//			while (i < num_ghosts)
//			{
//				ghost_direction = dist(rng);
//
//				// check if ghost can move in that direction
//				if (ghost_direction == 1)
//				{
//					if (array[ghost_rows[i]][ghost_cols[i] + 1] != 1 && !(array[ghost_rows[i]][ghost_cols[i] + 1] >= 3 && array[ghost_rows[i]][ghost_cols[i] + 1] <= 6))
//					{
//						ghost_directions[i] = ghost_direction;
//					}
//				}
//				else if (ghost_direction == 2)
//				{
//					if (array[ghost_rows[i] + 1][ghost_cols[i]] != 1 && !(array[ghost_rows[i] + 1][ghost_cols[i]] >= 3 && array[ghost_rows[i] + 1][ghost_cols[i]] <= 6))
//					{
//						ghost_directions[i] = ghost_direction;
//					}
//				}
//				else if (ghost_direction == 3)
//				{
//					if (array[ghost_rows[i]][ghost_cols[i] - 1] != 1 && !(array[ghost_rows[i]][ghost_cols[i] - 1] >= 3 && array[ghost_rows[i]][ghost_cols[i] - 1] <= 6))
//					{
//						ghost_directions[i] = ghost_direction;
//					}
//				}
//				else if (ghost_direction == 4)
//				{
//					if (array[ghost_rows[i] - 1][ghost_cols[i]] != 1 && !(array[ghost_rows[i] - 1][ghost_cols[i]] >= 3 && array[ghost_rows[i] - 1][ghost_cols[i]] <= 6))
//					{
//						ghost_directions[i] = ghost_direction;
//					}
//				}
//				i++;
//			}
//			ghostTimer = 0.5f;
//		}
//
//		const float moveSpeed = 30.0f;
//
//		if (ready)
//		{
//			M1.DisplayReady(window);
//			window.display();
//			readytime += deltaTime.asSeconds();
//			if (readytime >= 3)
//			{
//				ready = false;
//			}
//			continue;
//		}
//		
//			
//			if (Keyboard::isKeyPressed(Keyboard::Left))
//			{
//				if ((array[pac_rows][p_cols - 1] != 1))
//					movement_direction = 3; // Left
//			}
//			else if (Keyboard::isKeyPressed(Keyboard::Up))
//			{
//				if ((array[pac_rows - 1][p_cols] != 1))
//					movement_direction = 2; // Up
//			}
//			else if (Keyboard::isKeyPressed(Keyboard::Right))
//			{
//				if ((array[pac_rows][p_cols + 1] != 1))
//					movement_direction = 1; // Right
//			}
//			else if (Keyboard::isKeyPressed(Keyboard::Down))
//			{
//				if ((array[pac_rows + 1][p_cols] != 1))
//					movement_direction = 4; // Down
//			}
//			if (pacmanTimer <= 0)
//			{
//				fakePacmanDirection = movement_direction;
//				if (movement_direction == 3 && array[pac_rows][p_cols - 1] != 1) // left
//				{
//					check = array[pac_rows][p_cols - 1];
//					score.calculate_score(check);
//					obj.eat(check);
//					obj.eatFruit(check);
//
//					array[pac_rows][p_cols] = 0;
//					array[pac_rows][p_cols - 1] = 8;
//					p_cols--;
//					// cout << pac_rows << " " << p_cols << endl;
//					draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//						Pac_left, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//					if ((pac_rows == 9 && p_cols == 0))
//					{
//						array[pac_rows][p_cols] = 0;
//						pac_rows = 9;
//						p_cols = 21;
//						array[pac_rows][p_cols] = 0;
//						array[pac_rows][p_cols] = 8;
//						draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//							Pac_left, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//					}
//					// move pacman to the previous position
//					place[pac_rows][p_cols].move(Vector2f(cell_size, 0));
//				}
//				else if (movement_direction == 1 && array[pac_rows][p_cols + 1] != 1) // right
//				{
//					check = array[pac_rows][p_cols + 1];
//					score.calculate_score(check);
//					obj.eat(check);
//					obj.eatFruit(check);
//
//					place[pac_rows][p_cols].move(Vector2f(moveSpeed * deltaTime.asSeconds(), 0));
//					array[pac_rows][p_cols] = 0;
//					array[pac_rows][p_cols + 1] = 8;
//					p_cols++;
//					draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//						pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//					if ((pac_rows == 9 && p_cols == 21))
//					{
//						array[pac_rows][p_cols] = 0;
//						pac_rows = 9;
//						p_cols = 0;
//						array[pac_rows][p_cols] = 0;
//						array[pac_rows][p_cols] = 8;
//						draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//							pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//					}
//
//					// move pacman to the previous position
//					place[pac_rows][p_cols].move(Vector2f(-cell_size, 0));
//				}
//				else if (movement_direction == 2 && array[pac_rows - 1][p_cols] != 1) // Up
//				{
//					check = array[pac_rows - 1][p_cols];
//					score.calculate_score(check);
//					obj.eat(check);
//					obj.eatFruit(check);
//					place[pac_rows][p_cols].move(Vector2f(0, -moveSpeed * deltaTime.asSeconds()));
//					array[pac_rows][p_cols] = 0;
//					array[pac_rows - 1][p_cols] = 8;
//					pac_rows--;
//					draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//						Pac_up, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//					// move pacman to the previous position
//					place[pac_rows][p_cols].move(Vector2f(0, cell_size));
//				}
//				else if (movement_direction == 4 && array[pac_rows + 1][p_cols] != 1 && array[pac_rows + 1][p_cols] != 7) // down
//				{
//					check = array[pac_rows + 1][p_cols];
//					score.calculate_score(check);
//					obj.eat(check);
//					obj.eatFruit(check);
//					place[pac_rows][p_cols].move(Vector2f(0, moveSpeed * deltaTime.asSeconds()));
//					array[pac_rows][p_cols] = 0;
//					array[pac_rows + 1][p_cols] = 8;
//					pac_rows++;
//					draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//						Pac_down, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//
//					// move pacman to the previous position
//					place[pac_rows][p_cols].move(Vector2f(0, -cell_size));
//				}
//				else
//				{
//					fakePacmanDirection = 0;
//				}
//				pacmanTimer = 0.35f;
//			}
//			else
//			{
//				if (fakePacmanDirection == 1) // right
//				{
//					place[pac_rows][p_cols].move(Vector2f(cell_size / 0.35 * deltaTime.asSeconds(), 0));
//
//					// set pacman texture to right
//					place[pac_rows][p_cols].setTexture(&pacmanTexture);
//				}
//				else if (fakePacmanDirection == 3) // left
//				{
//					place[pac_rows][p_cols].move(Vector2f(-cell_size / 0.35 * deltaTime.asSeconds(), 0));
//
//					// set pacman texture to left
//					place[pac_rows][p_cols].setTexture(&Pac_left);
//				}
//				else if (fakePacmanDirection == 2) // up
//				{
//					place[pac_rows][p_cols].move(Vector2f(0, -cell_size / 0.35 * deltaTime.asSeconds()));
//
//					// set pacman texture to up
//					place[pac_rows][p_cols].setTexture(&Pac_up);
//				}
//				else if (fakePacmanDirection == 4) // down
//				{
//					place[pac_rows][p_cols].move(Vector2f(0, cell_size / 0.35 * deltaTime.asSeconds()));
//
//					// set pacman texture to down
//					place[pac_rows][p_cols].setTexture(&Pac_down);
//				}
//			}
//		// check if pacman is colliding with ghost
//		bool collision = false;
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < cols; j++)
//			{
//				if (ghosts[i][j] == 3 || ghosts[i][j] == 4 || ghosts[i][j] == 5 || ghosts[i][j] == 6)
//				{
//					if (pac_rows == i && p_cols == j)
//					{
//						collision = true;
//
//						// call pacman.deduct life
//						if (!isLiveDecreased)
//						{
//							pacman.decrease_lives();
//							obj.Death();
//							isLiveDecreased = true;
//							if (pacman.is_game_over())
//							{
//								isGameOver = true;
//								break;
//							}
//							// move pac to the starting position
//							array[pac_rows][p_cols] = 0;
//							pac_rows = 15;
//							p_cols = 10;
//							array[pac_rows][p_cols] = 8;
//							draw_maze(array, place, rows, cols, cell_size, wallTexture, palletTexture,
//								pacmanTexture, window, pac_rows, p_cols, cageTex, fruitTex, spaceTex);
//							pacmanTimer = -0.35f;
//							movement_direction = 2;
//						}
//
//						// check if game is over
//					}
//				}
//			}
//		}
//		if (!collision)
//		{
//			isLiveDecreased = false;
//		}
//		if (isGameOver)
//		{
//			score.draw_game_over(window);
//			obj.Death();
//			window.display();
//		}
//		pacmanTimer -= deltaTime.asSeconds();
//		ghostTimer -= deltaTime.asSeconds();
//		ghost_speed -= deltaTime.asSeconds();
//		window.display();
//	}
//}
//void draw_maze(int array[][22], RectangleShape** place, int rows, int cols, int cell_size, Texture& wallTexture, Texture& palletTexture,
//	Texture& pacmanTexture, RenderWindow& window, int& pac_rows, int& p_cols, Texture& cageTex, Texture& fruitTex, Texture& spaceTex)
//{
//	for (int i = 0; i < rows; i++)
//	{
//		for (int j = 0; j < cols; j++)
//		{
//			int cellValue = array[i][j];
//
//			RectangleShape rect;
//
//			if (cellValue == 0) // space
//			{
//				rect.setTexture(&spaceTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 1) // wall
//			{
//				rect.setTexture(&wallTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 2) // dots
//			{
//				rect.setTexture(&palletTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 7) // cage
//			{
//				rect.setTexture(&cageTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 8)
//			{
//				pac_rows = i;
//				p_cols = j;
//				rect.setTexture(&pacmanTexture);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			else if (cellValue == 9)
//			{
//				rect.setTexture(&fruitTex);
//				rect.setSize(Vector2f(cell_size, cell_size));
//				rect.setTextureRect(sf::IntRect(0, 0, cell_size, cell_size));
//			}
//			// Set the position of the rect based on the cell coordinates and size
//			rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//			place[i][j] = rect;
//		}
//	}
//}
//void change_location(int ghosts[][22], RectangleShape** place, int rows, int cols, int cell_size, Texture& greenGhostTexture,
//	Texture& redGhostTexture, Texture& blueGhostTexture, Texture& pinkGhostTexture, Texture& wallTexture, Texture& spaceTex, Texture& cageTex)
//{
//	for (int i = 0; i < rows; i++)
//	{
//		for (int j = 0; j < cols; j++)
//		{
//			RectangleShape rect(Vector2f(cell_size, cell_size));
//			rect.setPosition(Vector2f(j * cell_size, i * cell_size));
//
//			int cell_val2 = ghosts[i][j];
//			switch (cell_val2)
//			{
//			case 3:
//				rect.setTexture(&greenGhostTexture);
//				rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
//				break;
//			case 4:
//				rect.setTexture(&blueGhostTexture);
//				rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
//				break;
//			case 5:
//				rect.setTexture(&redGhostTexture);
//				rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
//				break;
//			case 6:
//				rect.setTexture(&pinkGhostTexture);
//				rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
//				break;
//			default:
//				rect.setTexture(&spaceTex);
//				rect.setTextureRect(IntRect(0, 0, cell_size, cell_size));
//				break;
//			}
//			place[i][j] = rect;
//		}
//	}
//}
