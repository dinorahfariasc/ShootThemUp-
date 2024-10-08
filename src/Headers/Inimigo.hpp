#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <SFML/Graphics.hpp>
#include "ProjetInimigo.hpp"
#include <vector>

class Inimigo
{
private:
    sf::CircleShape shape;
    std::vector<ProjetInimigo*> projeteis;
    sf::Texture* texture; // Textura do projetil
    sf::Vector2f direction;
    float speed;
    int hpMax;
    int damage;
    int points;
    float atirarTimer; // Timer para controlar a frequência dos tiros
    float atirarTimerMax; // Frequência máxima para atirar
    int hp;
    int type;

    void initShape();
    void initVariable();
    void atirar(sf::Vector2f atiradorPos);
    void updateProjetil();

public:
    Inimigo(float pos_x, float pos_y, sf::Texture* texture, sf::Vector2f atiradorPos);
    virtual ~Inimigo();

    const sf::FloatRect getBounds() const;
    void update(sf::Vector2f atiradorPos);
    void render(sf::RenderTarget *target);
    void renderProjeteis(sf::RenderTarget *target);
    void takeDamage(int dano);
    int getDamage();
    int getHp();
    bool checkProjetilHit(sf::FloatRect atiradorBounds);
};

#endif
