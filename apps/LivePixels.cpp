#include <SFML/Graphics.hpp>
#include <LivePixels/SDFs.hpp>
#include <vector>
#include "LivePixels/constants.hpp"
#include <LivePixels/math.hpp>
#include <LivePixels/Ray.hpp>

/*
class Cube : public lp::SDFs::ISDF
{
private:
    float m_side;

public:
    explicit Cube(float side)
        : m_side(side)
    {}

public:
    [[nodiscard]] float draw(const lp::Quaternion<float> &q) const override
    {
        return std::max(std::max(std::abs(q.getX()), std::abs(q.getY())), std::abs(q.getZ())) - m_side / 2;
    }
};
*/



int main(int argc, char **argv)
{
    size_t w = 200, h = 100;
    // va is a view angle
    float vaw = 90, vah = 45;
    std::vector<lp::SDFs::ISDF *> mapForRender(1, nullptr);
    mapForRender[0] = new lp::SDFs::Sphere({0, 5, 0, 0});
    lp::Quaternion<float> startRotator(0, 1, 0, 0), moving(0, 0, 0, 0),
        rot(std::cos(lp::angleToRadian(1)), 0, std::sin(lp::angleToRadian(1)), 0);
    lp::Ray ray(mapForRender, {0, 0, 0, 0}, 200, 7);
    ray.setPosition({0, 10, 10, 10});
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rot = {std::cos(lp::angleToRadian(1)), 0, std::sin(lp::angleToRadian(1)), 0};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rot = {std::cos(lp::angleToRadian(-1)), 0, std::sin(lp::angleToRadian(-1)), 0};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rot = {std::cos(lp::angleToRadian(-1)), 0, 0, std::sin(lp::angleToRadian(-1))};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rot = {std::cos(lp::angleToRadian(1)), 0, 0, std::sin(lp::angleToRadian(1))};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            rot = {std::cos(lp::angleToRadian(-1)), std::sin(lp::angleToRadian(-1)), 0, 0};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            rot = {std::cos(lp::angleToRadian(1)), std::sin(lp::angleToRadian(1)), 0, 0};
            startRotator = rot * startRotator * rot.inverse();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, -1, 0, 0));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, 1, 0, 0));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, 0, -1, 0));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, 0, 1, 0));
        window.clear();
        for (float x = 0; x < w; ++x)
        {
            for (float y = 0; y < h; ++y)
            {
                lp::Quaternion<float> r1(std::cos(lp::angleToRadian((x * vaw / w) / 2)),
                                         0,
                                         std::sin(lp::angleToRadian((x * vaw / w) / 2)),
                                         0
                ),
                    r2(std::cos(lp::angleToRadian((y * vah / h) / 2)),
                       0,
                       0,
                       std::sin(lp::angleToRadian((y * vah / h) / 2))
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
    for (auto &obj : mapForRender)
        delete obj;
    return 0;
}
