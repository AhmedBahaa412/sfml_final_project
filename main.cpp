#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;

float speed = 0,angle =0,pi=180;
float movementx,movementy,dy=0.5;;
int main()
{   Texture t1,t2,t3;
    t1.loadFromFile("rocket.png");
    t2.loadFromFile("Rocket1.png");
    t3.loadFromFile("platform.png");
    Sprite Rocket(t1),sPlat(t3);
    RenderWindow app(VideoMode(1024, 640), "Mars Lander Game!");
    app.setFramerateLimit(60);
    Rocket.setPosition(rand()%1200,rand()%150);
    Rocket.setOrigin(50,87.5);
    RectangleShape rectangle(Vector2f(400,200));
    rectangle.setPosition(300,600);
    RectangleShape rectangle1(Vector2f(500,300));
    rectangle1.setPosition(0,320);
    RectangleShape rectangle2(Vector2f(600,400));
    rectangle2.setPosition(685,620);

    rectangle1.rotate(45);
    rectangle2.rotate(-45);
    while (app.isOpen())
    {
        Event e;

        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                {app.close();}
            if (Keyboard::isKeyPressed(Keyboard::Right) && angle <=44) {
                    angle=angle+1;
                    Rocket.rotate(+1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && angle >=-44) {
                    angle=angle-1;
                    Rocket.rotate(-1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)&& speed <0.5) speed=speed+0.15;

            if (Keyboard::isKeyPressed(Keyboard::Down)&& speed >0) speed=speed-0.15;
        }

        //logic
        if(speed == 0) {Rocket.setTexture(t1);}
        if(speed >= 0.15) {Rocket.setTexture(t2);}
        Rocket.move(0,dy); //gravity
        movementx= +abs(speed*sin((180/3.14)*angle));
        movementy= -abs(speed*cos((180/3.14)*angle));
        //std::cout<<movementx<<" "<<movementy<<" "<<angle<<std::endl;
        if (Rocket.getPosition().x<=0+50) {Rocket.setPosition(sf::Vector2f(50,Rocket.getPosition().y));}
        if (Rocket.getPosition().y<=0+87.5) {Rocket.setPosition(sf::Vector2f(Rocket.getPosition().x,87.5));}
        if (Rocket.getPosition().y>=640-87.5) {Rocket.setPosition(sf::Vector2f(Rocket.getPosition().x,640-87.5));}
        if (Rocket.getPosition().x>=1024-50) {Rocket.setPosition(sf::Vector2f(1024-50,Rocket.getPosition().y));}
        if(angle<=0)
        {
        Rocket.move(-movementx,movementy);
        }else{
        Rocket.move(movementx,movementy);
        }
        if ((Rocket.getPosition().x >= rectangle.getPosition().x) && (Rocket.getPosition().y+87.5>=rectangle.getPosition().y)
            && (Rocket.getPosition().x <=rectangle.getPosition().x+400) && (Rocket.getPosition().y+87.5<=rectangle.getPosition().y +200) && angle == 0 )
      {
          std::cout<<"You win"<<std::endl;
      }
      if ((Rocket.getPosition().x >= rectangle2.getPosition().x) && (Rocket.getPosition().y+87.5>=rectangle2.getPosition().y)
            && (Rocket.getPosition().x <=rectangle2.getPosition().x+400) && (Rocket.getPosition().y+87.5<=rectangle2.getPosition().y +200) )
      {
          std::cout<<"You lose"<<std::endl;
      }
        //drawing

        app.clear();
        app.draw(Rocket);
        app.draw(rectangle);
        app.draw(rectangle1);
        app.draw(rectangle2);

        app.display();


    }
    return 0;
}
