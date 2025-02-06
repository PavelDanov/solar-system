#include <cmath>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

constexpr double PI = 3.14159265359;

struct Planet
{
	std::string name;
	float semiMajor;
	float semiMinor;
	float radius;
	float speed;
	float angle;
	sf::CircleShape shape;

	Planet(std::string n, float a, float b, float r, float s, sf::Color color)
		: name{n}, semiMajor{a}, semiMinor{b}, radius{r}, speed{s}, angle{0.0f}
	{
		shape.setRadius(radius);
		shape.setFillColor(color);
		shape.setOrigin(radius, radius);
	}

	void update(float deltaTime, sf::Vector2f sunPosition)
	{
		angle += speed * deltaTime;
		float x = sunPosition.x + semiMajor * cos(angle);
		float y = sunPosition.y + semiMinor * sin(angle);
		shape.setPosition(x, y);
	}
};

int main()
{
	int winWidth{1920};
	int winHeight{1080};

	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Solar System", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::View view = window.getDefaultView();

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) return -1;

	sf::Vector2f sunPosition(winWidth / 2, winHeight / 2);
	sf::CircleShape sun(40);
	sun.setPosition(sunPosition);
	sun.setFillColor(sf::Color::Yellow);
	sun.setOrigin(40, 40);

	std::vector<Planet> planets =
	{
		Planet("Mercury", 80, 60, 4, 0.8f, sf::Color(192, 192, 192))
	};

	sf::Clock clock;
	float zoomFactor = 1.0f;

	while (window.isOpen())
	{
		sf::Event event;
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
				zoomFactor *= 0.90;
			else
				zoomFactor *= 1.1f;
		}

		view.setSize(view.getSize() * zoomFactor);
		view.setCenter(sunPosition);

		float deltaTime = clock.restart().asSeconds();

		for (auto& p : planets)
			p.update(deltaTime, sunPosition);

		window.setView(view);
		window.clear(sf::Color::Black);

		window.draw(sun);

		for (const auto& p : planets) {
			sf::VertexArray orbit(sf::LineStrip, 361);
			for (int i {0}; i <= 360; ++i)
			{
				float rad = i * (PI / 180);
				float x = sunPosition.x + p.semiMajor * cos(rad);
				float y = sunPosition.y + p.semiMinor * sin(rad);
				orbit[i].position = sf::Vector2f(x, y);
				orbit[i].color = sf::Color(100, 100, 100);
			}
			window.draw(orbit);
		}

		for (const auto& p : planets)
			window.draw(p.shape);

		window.display();
	}

	return 0;
}
