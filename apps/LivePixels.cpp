#include <SFML/Graphics.hpp>
#include <LivePixels/SDFs/ISDF.hpp>
#include <LivePixels/math.hpp>

class Camera
{
private:
    lp::Quaternion<float> m_q;

public:
    Camera(const lp::Quaternion<float> &quater)
        : m_q(quater)
    {}

public:
    float RayMarching()
    {
        return 0;
    }
};

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}
