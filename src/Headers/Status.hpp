#ifndef STATUS_HPP
#define STATUS_HPP

#include <SFML/Graphics.hpp>
#include "Atirador.hpp"
#include "Base.hpp"


class Status
{
private:
    sf::Font font;
    sf::Text vidaAtiradorText;
    sf::Text vidaBaseText;
    sf::Text projeteisDisponiveisText;
    float vidaInicialAtirador;
    float vidaInicialBase;
    float projeteisDisponiveis;

    void initFont();

public:
    Status(float vidaInicialAtirador, float vidaInicialBase, float projeteisDisponiveis);
    ~Status();
    
    void update(const Atirador& atirador, const Base& base);
    void render(sf::RenderTarget* target);
};

#endif
