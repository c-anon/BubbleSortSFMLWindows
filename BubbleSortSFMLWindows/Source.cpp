#include <random>
#include <SFML/Graphics.hpp>

// globals bad
const uint16_t width = 1600;
const uint16_t height = 900;
const uint16_t elementsToSort = 100;
const float barWidth = (float)width / elementsToSort;


sf::Color GetRandomColor();
uint16_t GetRandomNumber(uint16_t maxNumber = 65535);
void UpdateHeights(std::map<uint16_t, sf::RectangleShape>& mapUint16Bar);

int main()
{
	const uint16_t framesPerSecond = 3;
	// window
	sf::RenderWindow window(sf::VideoMode(width, height), "Bubblesort visualization");
	window.setFramerateLimit(framesPerSecond);
	// numebers and bars connected to them
	std::map<uint16_t, sf::RectangleShape> mapUint16Bar;

	// initialize random values
	for (uint16_t i = 0; i < elementsToSort; ++i)
	{
		uint16_t randomNumber{ GetRandomNumber(900) };
		mapUint16Bar[i] = sf::RectangleShape({ float(barWidth), float(randomNumber) });
		mapUint16Bar[i].setPosition(i * barWidth, float((height - randomNumber)));
		mapUint16Bar[i].setFillColor(GetRandomColor());
	}

	// main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		for (const auto& bar : mapUint16Bar)
		{
			window.draw(bar.second);
		}

		window.display();
		UpdateHeights(mapUint16Bar);
	}
	return 0;
}

uint16_t GetRandomNumber(uint16_t maxNumber)
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<std::mt19937::result_type> distUINT16(0, maxNumber);
	return static_cast<uint16_t>(distUINT16(g));
}

sf::Color GetRandomColor()
{
	return sf::Color(static_cast<uint8_t>(GetRandomNumber(255)),
		static_cast<uint8_t>(GetRandomNumber(255)),
		static_cast<uint8_t>(GetRandomNumber(255)));
}

void UpdateHeights(std::map<uint16_t, sf::RectangleShape>& mapUint16Bar)
{
	for (uint16_t i = 0; i < elementsToSort - 1; ++i)
	{
		const sf::Color leftColor = mapUint16Bar[i].getFillColor();
		const sf::Color rightColor = mapUint16Bar[i + 1].getFillColor();
		const sf::Vector2f leftElemSize = mapUint16Bar[i].getSize();
		const sf::Vector2f rightElemSize = mapUint16Bar[i + 1].getSize();
		const sf::Vector2f leftElemPos = mapUint16Bar[i].getPosition();
		const sf::Vector2f rightElemPos = mapUint16Bar[i + 1].getPosition();
		if (leftElemSize.y > rightElemSize.y)
		{
			mapUint16Bar[i].setSize({ barWidth, rightElemSize.y });
			mapUint16Bar[i + 1].setSize({ barWidth, leftElemSize.y });
			mapUint16Bar[i].setPosition(leftElemPos.x, rightElemPos.y);
			mapUint16Bar[i + 1].setPosition(rightElemPos.x, leftElemPos.y);
			mapUint16Bar[i].setFillColor(rightColor);
			mapUint16Bar[i + 1].setFillColor(leftColor);
		}
	}
}
