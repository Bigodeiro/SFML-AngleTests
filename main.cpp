#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>

#define WIDTH 1280
#define HEIGTH 960



int main()
{
    //*tela e view
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);
    sf::View view(sf::Vector2f(0,0), sf::Vector2f(WIDTH, HEIGTH));
    window.setView(view);

    //*eixos do plano cartesiano
    sf::Vertex ordenadas[]=
    {
        sf::Vertex(sf::Vector2f(0,-999999)),
        sf::Vertex(sf::Vector2f(0,999999)),
    };
    sf::Vertex abscissas[]=
    {
        sf::Vertex(sf::Vector2f(999999,0)),
        sf::Vertex(sf::Vector2f(-999999,0)),
    };
    ordenadas[0].color = sf::Color(100,100,100);
    ordenadas[1].color = sf::Color(100,100,100);
    abscissas[0].color = sf::Color(100,100,100);
    abscissas[1].color = sf::Color(100,100,100);

    //*UnitCircle
    sf::CircleShape unitCircle(200);
    unitCircle.setOrigin(unitCircle.getRadius(),unitCircle.getRadius());
    unitCircle.setFillColor(sf::Color::Black);
    unitCircle.setOutlineThickness(2);

    //*Ponteiro Angular
    sf::Vertex angPointer[]=
    {
        sf::Vertex(unitCircle.getPosition()),
        sf::Vertex(sf::Vector2f(0,0))
    };
    angPointer[0].color = sf::Color(51, 158, 255);
    angPointer[1].color = sf::Color(51, 158, 255);

    //*Texto do angulo
    sf::Font fonte;
    if (!fonte.loadFromFile("src/fonts/arial.TTF"))
    {
        std::cout << "azar kk" << std::endl;

        system("pause");
    }
    sf::Text anguloTXT;
    anguloTXT.setFont(fonte);
    anguloTXT.setCharacterSize(20);
    anguloTXT.setPosition(15,15);
    anguloTXT.setString("teste");
    anguloTXT.setFillColor(sf::Color(51, 158, 255));

    //*Linha do ceno e do cosseno
    sf::Vertex seno[]=
    {
        sf::Vertex(sf::Vector2f(100,100)),
        sf::Vertex(sf::Vector2f(-100,-100))
    };
    sf::Vertex cosseno[]=
    {
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0))
    };
    seno[0].color = sf::Color(37,220,44);
    seno[1].color = sf::Color(37,220,44);
    cosseno[0].color = sf::Color(255,82,40);
    cosseno[1].color = sf::Color(255,82,40);
    

    //*Texto do seno e do cosseno
    sf::Text senoTXT;
    senoTXT.setFont(fonte);
    senoTXT.setCharacterSize(20);
    senoTXT.setPosition(15,15);
    senoTXT.setString("teste");
    senoTXT.setFillColor(sf::Color(37,220,44));

    sf::Text cossenoTXT;
    cossenoTXT.setFont(fonte);
    cossenoTXT.setCharacterSize(20);
    cossenoTXT.setPosition(15,15);
    cossenoTXT.setString("teste");
    cossenoTXT.setFillColor(sf::Color(255,82,40));

    //*Linha da Tangente
    

    while (window.isOpen())//! cada iteração aqui é um frame
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                
                window.close();

                break;
            }
        }

    //!codigo a ser executado todo frame
    window.clear();

    //* Atualizar angulação do ponteiro, utilizando semelhança de triangulo
    float mousePosX = sf::Mouse::getPosition(window).x - WIDTH/2;
    float mousePosY = sf::Mouse::getPosition(window).y - HEIGTH/2;
    float coeficienteAngularFuncPonteiro = (0 - mousePosY) / (0 - mousePosX);
    angPointer[1].position.x = (mousePosX * unitCircle.getRadius()) / sqrt( pow(mousePosX, 2) + pow(mousePosY, 2));
    angPointer[1].position.y = (mousePosY * unitCircle.getRadius()) / sqrt( pow(mousePosX, 2) + pow(mousePosY, 2));
    //A mesma coisa para o texto so que menor 
    anguloTXT.setPosition(((mousePosX * (unitCircle.getRadius())/4 ) / sqrt( pow(mousePosX, 2) + pow(mousePosY, 2)))+8, (mousePosY * (unitCircle.getRadius())/4 ) / sqrt( pow(mousePosX, 2) + pow(mousePosY, 2)));
    
    //*Calculo e atualização do angulo
    float ang = std::abs(atan(mousePosY/mousePosX));
    ang = ang * (180.0/3.141592653589793238463);
    if(mousePosX < 0 && mousePosY < 0)
    {
        ang = 90 + 90 - ang;
    }
    else if(mousePosX < 0 && mousePosY > 0)
    {
        ang = 180 + ang;
    }
    else if(mousePosX > 0 && mousePosY > 0)
    {
        ang = 270 + 90 - ang;
    }
    
    anguloTXT.setString(std::to_string(int(ang)));

    //*Calculo e atualização da linhas do seno e do cosseno
    seno[0].position = angPointer[1].position;
    cosseno[0].position = angPointer[1].position;

    seno[1].position = sf::Vector2f(angPointer[1].position.x ,0);
    cosseno[1].position = sf::Vector2f(0, angPointer[1].position.y);

    //*Calculo e atualização dos valores dos senos e cossenos
    senoTXT.setPosition(seno[1].position);
    cossenoTXT.setPosition(cosseno[1].position);
    float valseno = seno[1].position.x/unitCircle.getRadius();
    float valcosseno = cosseno[1].position.y/unitCircle.getRadius();

    std::string tempseno = std::to_string(valseno);
    std::string tempcosseno = std::to_string(valcosseno * -1);

    if (valseno < 0)
    {
        tempseno.resize(5);
    }else tempseno.resize(4);
    if (valcosseno < 0)
    {
        tempcosseno.resize(4);
    }else tempcosseno.resize(5);

    senoTXT.setString(tempseno);
    cossenoTXT.setString(tempcosseno);


    //? renderiza algo para a tela, modificando-a
    window.draw(unitCircle);
    window.draw(abscissas, 2, sf::Lines);
    window.draw(ordenadas, 2, sf::Lines);
    window.draw(angPointer, 2, sf::Lines);
    window.draw(anguloTXT);
    window.draw(seno, 2, sf::Lines);
    window.draw(cosseno, 2, sf::Lines);
    window.draw(senoTXT);
    window.draw(cossenoTXT);


    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();

    }

    return 0;
}