#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
//to store coordinates of snake
namespace kumar{
struct sn{
 int x,y;
}s[100];
}

//global var
int s_move,score,body,apple_x,apple_y,l_x,m_x,l_y,m_y;

int main(){

  kumar::s[0].x=60;//starting pos of snake
  kumar::s[0].y=60;
  bool wel=true;
  s_move=5;//right movement of snake

  bool flag=false;
  int play=1;

  body=1;
  //render window
  sf::RenderWindow window(sf::VideoMode(800,800),"SNAKE");
  window.setFramerateLimit(10);

  //wall
  sf::RectangleShape rectangle;
         rectangle.setSize(sf::Vector2f(700, 700));
         rectangle.setOutlineColor(sf::Color::Blue);
         rectangle.setOutlineThickness(10);
         rectangle.setPosition(50, 50);

  //apple
  sf::CircleShape apple;
          apple.setRadius(10);
          apple.setFillColor(sf::Color(200,84,201));
          apple.setPosition(100,100);


 // Load the text font
  sf::Font font;
        if (!font.loadFromFile("resources/sansation.ttf"))
               return EXIT_FAILURE;
 // Initialize the pause message
   sf::Text over;
           over.setFont(font);
           over.setCharacterSize(40);
           over.setPosition(250.f, 350.f);
           over.setFillColor(sf::Color::Green);
           over.setString("GAME OVER!!!");


 // Load the sounds used in the game
    sf::SoundBuffer hit_buffer;
       if (!hit_buffer.loadFromFile("resources/hit.wav"))
           return EXIT_FAILURE;
       sf::Sound hitSound(hit_buffer);

    sf::SoundBuffer over_buffer;
       if (!over_buffer.loadFromFile("resources/g_over.wav"))
           return EXIT_FAILURE;
       sf::Sound overSound(over_buffer);

    sf::SoundBuffer wel_buffer;
       if (!wel_buffer.loadFromFile("resources/wel.wav"))
           return EXIT_FAILURE;
       sf::Sound welSound(wel_buffer);


     //game loop
     while(window.isOpen()){
       sf::Event event;
       //event check
       while (window.pollEvent(event)){
         if (event.type == sf::Event::Closed)
            window.close();
         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(s_move!=2)
             s_move=1;

         }
         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(s_move!=1)
             s_move=2;

         }
         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(s_move!=4)
             s_move=3;

         }
         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(s_move!=3)
            s_move=4;
       }
         else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            play=2;
            s_move=2;

         }
       }


     //movement
       switch(s_move){
         case 1: kumar::s[0].x-=20;

              break;
        case 2:
                 kumar::s[0].x+=20;

               break;
        case 3:   kumar::s[0].y-=20;

                break;
        case 4:  kumar::s[0].y+=20;

              break;

      }
       //collision
      if(kumar::s[0].x<50||kumar::s[0].x>730||kumar::s[0].y<50||kumar::s[0].y>730){
          play=3;
          kumar::s[0].x=60;kumar::s[0].y=60;
          flag=true;
          s_move=5;
      }
      if(flag==true){

          overSound.play();
          flag=false;
      }

      //generate pos for apple

       l_x=apple.getPosition().x-20;
       m_x=apple.getPosition().x+40;
       l_y=apple.getPosition().y-20;
       m_y=apple.getPosition().y+40;
    if((kumar::s[0].x>=l_x&&kumar::s[0].x<=m_x)&&
       (kumar::s[0].y>=l_y&&kumar::s[0].y<=m_y)){
        hitSound.play();
        body++;
      int c=1;
      while(c){
          apple_x=(rand()%730)+1;
          if(apple_x<50||apple_x>730)
            c=1;
          else
            c=0;
      }
      c=1;
      while(c){
          apple_y=(rand()%730)+1;
          if(apple_y<50||apple_y>730)
            c=1;
          else
            c=0;
      }
      apple.setPosition(apple_x,apple_y);

      sf::Color colo(sf::Color(200,84,201));

      apple.setFillColor(colo);

      }






     //snake body
     std::vector<sf::CircleShape> myvector;
     for(int i=0;i<body;i++){
        sf::CircleShape shape(100);
         int x = kumar::s[i].x;
         int y= kumar::s[i].y;
        shape.setPosition( x,y);
        shape.setRadius(10);
        shape.setFillColor(sf::Color::Red);
        myvector.push_back(shape);
     }


       window.clear();
       if(play==2){
        window.draw(rectangle);
        for(std::vector<sf::CircleShape>::iterator it =myvector.begin();it!=myvector.end();++it){
           window.draw(*it);
        }
        window.draw(apple);

        for(int i=body;i>0;i--){
          kumar::s[i].x=kumar::s[i-1].x;
          kumar::s[i].y=kumar::s[i-1].y;

        }
       }
       else if(play==1){
            if(wel==true){
                wel=false;
                welSound.play();
            }
           over.setCharacterSize(70);
           over.setPosition(250.f, 150.f);
           over.setFillColor(sf::Color(207,181,59));
           over.setString("WELCOME");
           window.draw(over);
           over.setCharacterSize(20);
           over.setPosition(250.f, 300.f);
           over.setFillColor(sf::Color::Green);
           over.setString("1. Use arrow keys to move the snake\n\n2. Press Enter to START the game");
           window.draw(over);

       }
       else{
        over.setCharacterSize(70);
           over.setPosition(170.f, 220.f);
           over.setFillColor(sf::Color(192,192,192));
           over.setString("GAME OVER!!!!");
           window.draw(over);
           std::stringstream scr;
           scr<<"score\t"<<body-1;
           over.setCharacterSize(50);
           over.setPosition(300.f, 350.f);
           over.setFillColor(sf::Color(211,211,211));
           over.setString(scr.str());
           window.draw(over);
       }
      window.display();
    }

    return 0;
  }