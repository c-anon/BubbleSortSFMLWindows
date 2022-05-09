#include<vector>
#include<iostream>
#include <algorithm>
#include <random>
#include <set>
#include <thread>
#include <chrono>
#include <conio.h>

#include <SFML/Graphics.hpp>

// globals bad
const uint16_t width = 1600;
const uint16_t height = 900;
const uint16_t elementsToSort = 1000;
const float barWidth = (float)width / elementsToSort;

sf::Color getRandomColor();
uint16_t getRandomNumber(uint16_t maxNumber = 65535);
void updateHeights(std::map<uint16_t, sf::RectangleShape>& mapUint16Bar);

int main()
{
	//setting up window
	sf::RenderWindow window(sf::VideoMode(width, height), "Bogosort visualization");
	window.setFramerateLimit(100);
	// numeber and bars connected to the numbers
	std::map<uint16_t, sf::RectangleShape> mapUint16Bar;

	//initialize random values
	for (uint16_t i = 0; i < elementsToSort; ++i)
	{
		//mapUint16Bar[i] = 
		uint16_t randomNumber{ getRandomNumber(900) };
		mapUint16Bar[i] = sf::RectangleShape({ float(barWidth), float(randomNumber) });
		//mapUint16Bar[i].setSize({ float(barWidth), float(randomNumber) });
		mapUint16Bar[i].setPosition(i * barWidth, float((height - randomNumber)));
		mapUint16Bar[i].setFillColor(getRandomColor());
	}

	//loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		for (uint16_t i = 0; i < elementsToSort; ++i)
		{
			window.draw(mapUint16Bar[i]);
		}
		window.display();

		std::vector<float> heights(elementsToSort);
		for (uint16_t i = 0; i < elementsToSort; ++i)
		{
			heights.push_back(mapUint16Bar[i].getSize().y);
		}
		if (std::is_sorted(begin(heights), end(heights)))
		{
			std::chrono::seconds timespan(3);
			std::this_thread::sleep_for(timespan);
		}
		updateHeights(mapUint16Bar);
	}

	return 0;
}

uint16_t getRandomNumber(uint16_t maxNumber)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<std::mt19937::result_type> distUINT16(0, maxNumber);
	return distUINT16(g);
}

sf::Color getRandomColor()
{

	return sf::Color(getRandomNumber(255), getRandomNumber(255), getRandomNumber(255));
}

void updateHeights(std::map<uint16_t, sf::RectangleShape>& mapUint16Bar)
{

	//bubble sort 
	for (uint16_t i = 0; i < elementsToSort + 1; ++i)
	{
		const sf::Vector2f leftElemSize = mapUint16Bar[i].getSize();
		const sf::Vector2f rightElemSize = mapUint16Bar[i + 1].getSize();
		const sf::Vector2f leftElemPos = mapUint16Bar[i].getPosition();
		const sf::Vector2f rightElemPos = mapUint16Bar[i + 1].getPosition();
		if (leftElemSize.y > rightElemSize.y)
		{
			mapUint16Bar[i].setSize({ barWidth, rightElemSize.y });
			mapUint16Bar[i + 1].setSize({ barWidth, leftElemSize.y });
			mapUint16Bar[i].setPosition(leftElemPos.x, rightElemPos.y);
			mapUint16Bar[+1].setPosition(rightElemPos.x, leftElemPos.y);
		}
	}

	for (uint16_t i = 0; i < elementsToSort; ++i)
	{
		/*uint16_t randNumber = getRandomNumber(900);
		mapUint16Bar[i].setSize({ float(barWidth), float(randNumber) });
		mapUint16Bar[i].setPosition(float(i * barWidth), float(height - randNumber));*/
		//mapUint8Bar[i].setFillColor(sf::Color::White);
		//mapUint8Bar[i].setFillColor(getRandomColor());
		//mapUint8Bar[i].setOutlineColor(sf::Color::Black);
		//mapUint8Bar[i].setOutlineThickness(0.5f);
	}
}
