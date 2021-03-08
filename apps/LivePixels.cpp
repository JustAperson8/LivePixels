#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LivePixels/constants.hpp"
#include "LivePixels/math.hpp"
#include "LivePixels/Ray.hpp"
#include "LivePixels/SDFs.hpp"

class CubeSDF : public lp::SDFs::ISDF
{
public:
    float side;
    lp::Quaternion<float> movings, rotation; 

public:
    CubeSDF (float side, lp::Quaternion<float> movings, lp::Quaternion<float> rotation)
        : side(std::abs(side)), movings(movings), rotation(rotation)
    {} 
    
    virtual float draw(const lp::Quaternion<float> &quater) const override
    {
        auto result = quater - movings;
        lp::Quaternion<float> rx({std::cos(rotation.getX()) / 2, std::sin(rotation.getX() / 2), 0, 0});
        lp::Quaternion<float> ry({std::cos(rotation.getY()) / 2, 0, std::sin(rotation.getY() / 2), 0});
        lp::Quaternion<float> rz({std::cos(rotation.getZ()) / 2, 0, 0, std::sin(rotation.getZ()) / 2});
        result = rx * (ry * (rz * result * rz.inverse()) * ry.inverse()) * rx.inverse();
        return std::max(std::max(std::abs(result.getX()), std::abs(result.getY())), std::abs(result.getZ())) - side / 2;
    }

    ~CubeSDF () = default;
};


int main() 
{ 
    float test = 0;
    size_t w = 50, h = 50; 
    // va is a view angle
    float vaw = 90, vah = 90; 
    std::vector<lp::SDFs::ISDF *> mapForRender(3, nullptr);

    mapForRender[0] = new lp::SDFs::GroupOfSDFs({
        new CubeSDF(6, {0, 0, 0, 0}, {0, M_PI, 0, 0}), 
        new lp::SDFs::Sphere({0, 0, -1.6, -1.6}, 3),
        new lp::SDFs::Sphere({0, 0, -1.6, 1.6}, 3)
        }, {                
        new CubeSDF(20, {0, -10, 0, 0}, {0, 0, 0, 0}),
        new CubeSDF(20, {0, 10, 0, 0}, {0, 0, 0, 0}),
        });

    // mapForRender[0] = new lp::SDFs::GroupOfSDFs({new CubeSDF(6, {0, 10, 10, 10}, {0, 0, 0, 0})}, {});
    mapForRender[1] = new lp::SDFs::GroupOfSDFs({new CubeSDF(6, {0, 5, 5, 0}, {0, 0, 0, 0})}, {new lp::SDFs::Sphere({0, 5, 4, 0}, 5)});
    mapForRender[2] = new lp::SDFs::Sphere({0, 0, -2, -2}, 2);

    lp::Quaternion<float> startRotator(0, 1, 0, 0),
        rot(std::cos(lp::angleToRadian(1)), 0, std::sin(lp::angleToRadian(1)), 0);
    lp::Ray ray(mapForRender, {0, 0, 0, 0}, 200, 7);
    ray.setPosition({0, 10, 10, 10});
    sf::RenderWindow window(sf::VideoMode(w, h), "Render");
    sf::RectangleShape pixel({1, 1});
    while (window.isOpen())
    {
        test += 0.1;
        dynamic_cast<CubeSDF*>(dynamic_cast<lp::SDFs::GroupOfSDFs*>(mapForRender[1])->m_visibleSDFs[0])->rotation.setX(test);
        
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, 0, 0, 1));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            ray.setPosition(ray.getPosition() + lp::Quaternion<float>(0, 0, 0, -1));

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

                lp::Quaternion<float> wtf(r2 * (r1 * startRotator * r1.inverse()) * r2.inverse());
                float dist = ray.rayMarching(wtf);
                if (dist < 2000)
                    std::cout << wtf << std::endl;
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
