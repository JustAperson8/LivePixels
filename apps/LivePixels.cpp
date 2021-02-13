#include <vector>
#include <SFML/Graphics.hpp>
#include "LivePixels/constants.hpp"
#include "LivePixels/math.hpp"
#include "LivePixels/Ray.hpp"
#include "LivePixels/SDFs.hpp"

class Bublic : public lp::SDFs::ISDF
{
private:
    float m_radius, m_Radius;
public:
    Bublic(float radius = 10, float Radius = 20)
        : m_radius(radius), m_Radius(Radius)
    {}

    ~Bublic() = default;

    [[nodiscard]] virtual float draw(const lp::Quaternion<float> &quater) const 
    {
        // auto Quater(quater);
        // Quater.setX(static_cast<int>(Quater.getX()) % 30);
        // Quater.setY(static_cast<int>(Quater.getY()) % 30);
        // Quater.setZ(static_cast<int>(Quater.getZ()) % 30);
        // return std::sqrt( std::pow(std::sqrt(Quater.getX() * Quater.getX() + Quater.getZ() * Quater.getZ()) - m_Radius, 2) + Quater.getY() * Quater.getY()) - m_radius;
        return std::sqrt( std::pow(std::sqrt(quater.getX() * quater.getX() + quater.getZ() * quater.getZ()) - m_Radius, 2) + quater.getY() * quater.getY()) - m_radius;
    }
};

class CubeSDF : public lp::SDFs::ISDF
{
private:
    lp::Quaternion<float> cube;

public:
    CubeSDF (lp::Quaternion<float> cube)
        : cube(cube)
    {
    } 
    
    virtual float draw(const lp::Quaternion<float> &quater) const override
    {
    }

    ~CubeSDF () = default;
};


int main() 
{ 
    size_t w = 200, h = 200; 
    // va is a view angle
    float vaw = 90, vah = 90; 
    std::vector<lp::SDFs::ISDF *> mapForRender(1, nullptr);
    mapForRender[0] = new lp::SDFs::GroupOfSDFs({new lp::SDFs::Sphere({0, 0, 0, 0}, 10), new lp::SDFs::Sphere({0, 0, -10, 0}, 10)}, {new Bublic(10, 12)});
    lp::Quaternion<float> startRotator(0, 1, 0, 0),
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
                    pixel.setFillColor(sf::Color(color + 100, color, color));
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
