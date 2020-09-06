#include <SFML/Graphics.hpp>
#include <LivePixels/SDFs.hpp>
#include <vector>
#include "LivePixels/constants.hpp"
#include <LivePixels/math.hpp>
#include <LivePixels/Ray.hpp>

int main(int argc, char **argv)
{
    size_t w = 300, h = 300;
    // va is a view angle
    float vaw = 90, vah = 90;
    std::vector<lp::SDFs::ISDF *> mapForRender(1, nullptr);
    mapForRender[0] = new lp::SDFs::Sphere(0, 20, 0, 0, 15);
    lp::Quaternion<float> startRotator(0, 1, 0, 0);
    lp::Ray ray(mapForRender);
    sf::RenderWindow window(sf::VideoMode(w, h), "Render");
    sf::RectangleShape pixel({1, 1});
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (float x = 0; x < w; ++x)
        {
            for (float y = 0; y < h; ++y)
            {
                lp::Quaternion<float> r1(std::cos(lp::angleToRadian((x * 90.f / 300.f) / 2)),
                                         0,
                                         std::sin(lp::angleToRadian((x * 90.f / 300.f) / 2)),
                                         0
                ),
                    r2(std::cos(lp::angleToRadian((y * 90.f / 300.f) / 2)),
                       0,
                       0,
                       std::sin(lp::angleToRadian((y * 90.f / 300.f) / 2))
                );

                float dist = ray.rayMarching(r2 * (r1 * startRotator * r1.inverse()) * r2.inverse());
                if (dist != lp::notFound)
                {
                    pixel.setPosition(x, y);
                    float color = 5000 / dist;
                    pixel.setFillColor(sf::Color(color, color, color));
                    window.draw(pixel);
                }
            }
        }
        window.display();
    }
    return 0;
}
