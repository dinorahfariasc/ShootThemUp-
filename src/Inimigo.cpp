#include "Inimigo.hpp"
#include <cmath>

using namespace sf;

void Inimigo::initShape()
{
    this->shape.setRadius(rand() % 20 + 20);
    this->shape.setPointCount(rand() % 20 + 3);
    this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

void Inimigo::initVariable()
{
    this->speed = 3.f;
    this->hpMax = 10;
    this->hp = 0;
    this->demage = 1;
    this->points = 5;
    this->atirarTimer = 0.f;
    this->atirarTimerMax = 100.f; // Ajuste conforme necessário
}

Inimigo::Inimigo(float pos_x, float pos_y, Texture* texture, Vector2f atiradorPos)
{
    this->initShape();
    this->initVariable();
    this->shape.setPosition(pos_x, pos_y);
    this->texture = texture;

    Vector2f dir = atiradorPos - this->shape.getPosition();
    float magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);
    this->direction = dir / magnitude;
}

Inimigo::~Inimigo()
{
    // Limpar projeteis
    for (auto* projetil : projeteis)
    {
        delete projetil;
    }
}

const sf::FloatRect Inimigo::getBounds() const
{
    return this->shape.getGlobalBounds();
}

void Inimigo::atirar(Vector2f atiradorPos)
{
    this->atirarTimer += 1.f; // Incrementa o timer (ajuste conforme necessário)

    if (this->atirarTimer >= this->atirarTimerMax)
    {
        // Calcula a direção do projétil
        Vector2f dir = atiradorPos - this->shape.getPosition();
        float magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);
        Vector2f direction = dir / magnitude;

        // Cria o projétil
        this->projeteis.push_back(new ProjetilInimigo(this->texture, 
                                                     this->shape.getPosition().x, 
                                                     this->shape.getPosition().y, 
                                                     direction.x, direction.y, 
                                                     5.f)); // Ajuste a velocidade conforme necessário

        this->atirarTimer = 0.f; // Reinicia o timer
    }
}

void Inimigo::update(Vector2f atiradorPos)
{
    // Atualiza a direção e move o inimigo
    Vector2f dir = atiradorPos - this->shape.getPosition();
    float magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);
    this->direction = dir / magnitude;
    this->shape.move(this->direction * this->speed);

    // Atualiza o timer e atira projéteis
    this->atirar(atiradorPos);

    // Atualiza projéteis
    this->updateProjetil();
}

void Inimigo::updateProjetil()
{
    unsigned counter = 0;
    for (auto* projetil : this->projeteis)
    {
        projetil->update();

        if (projetil->getBounds().top + projetil->getBounds().height < 0.f)
        {
            delete projetil;
            this->projeteis.erase(this->projeteis.begin() + counter);
            --counter;
        }

        ++counter;
    }
}

void Inimigo::render(sf::RenderTarget* target)
{
    target->draw(this->shape);

    for (auto* projetil : this->projeteis)
    {
        projetil->render(target);
    }
}
