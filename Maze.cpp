#include<iostream>
#include"SFML/Graphics.hpp"
#include<vector>
using namespace std;

using namespace sf;
int main()
{
	RenderWindow window(VideoMode(600, 600), "PAC MAN", Style::Default);
	vector<vector<int>> maze;//2d vector array
	maze =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,1,1,2,2,1,1,2,2,1},
		{1,2,2,1,1,2,2,1,1,2,2,1},
		{1,2,2,2,2,2,5,2,2,2,2,1},
		{1,1,2,2,1,1,0,1,1,4,1,1},
		{2,2,2,2,1,6,7,8,1,2,2,2},//sp
		{1,1,2,2,1,1,1,1,1,2,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,1,1,2,2,1,1,2,2,1},
		{1,2,2,1,1,2,2,1,1,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1}
	};
	//window size is 600x600
	int numRows = maze.size();//50
	int numCols = maze[0].size();

	// Load the textures for the different sprites
	int cellsize = 50;

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

	// Create a vector of sprites for each cell in the maze// 2d vector cells 
	std::vector<std::vector<sf::Sprite>> cells(numRows, std::vector<sf::Sprite>(numCols));

	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		for (int i = 0; i < numRows; i++) 
		{
			for (int j = 0; j < numCols; j++) 
			{
				// Create a sprite based on the value in the maze array
				int cellValue = maze[i][j];
				sf::Sprite sprite;

				if (cellValue == 1)
				{
					sprite.setTexture(wallTexture);
				}
				else if (cellValue == 2) 
				{
					sprite.setTexture(palletTexture);
				}
				else if (cellValue == 4) 
				{
					sprite.setTexture(pacmanTexture);
				}
				else if (cellValue == 5)
				{
					sprite.setTexture(greenGhostTexture);
				}
				else if (cellValue == 6)
				{
					sprite.setTexture(redGhostTexture);
				}
				else if (cellValue == 7)
				{
					sprite.setTexture(blueGhostTexture);
				}
				else if (cellValue == 8)
				{
					sprite.setTexture(pinkGhostTexture);
				}
				// Set the position of the sprite based on the cell coordinates and size
				sprite.setPosition(j * cellsize, i * cellsize);

				// Add the sprite to the vector of sprites for this cell
				cells[i][j] = sprite;
			}
		}
		window.clear();
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < numCols; j++)
			{
				window.draw(cells[i][j]);
			}
		}
		window.display();
	}


}
