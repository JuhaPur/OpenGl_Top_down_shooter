#pragma once
#include <System.h>
#include <Collider.h>
#include <game/Player.h>
#include <game/Enemy.h>
#include <Transform.h>

class Application;

class GameplaySystem : public System {
public:
    GameplaySystem(Application* app) {
        m_app = app;
    }

    std::shared_ptr<Collider> createCollider(const std::vector<std::string>& args) {
        auto collider = std::make_shared<Collider>();
        return collider;
    }

    std::shared_ptr<Player> loadPlayer(const std::vector<std::string>& args) {
        auto player = std::make_shared<Player>();
        return player;
    }

    std::shared_ptr<Enemy> loadEnemy(const std::vector<std::string>& args) {
        auto enemy = std::make_shared<Enemy>();
        return enemy;
    }
    std::shared_ptr<Bullet> loadBullet(const std::vector<std::string>& args) {
        auto bullet = std::make_shared<Bullet>();
        return bullet;
    }

    virtual std::shared_ptr<Component> createComponent(const std::string& type, const std::vector<std::string>& args) {
        if (type == "Collider") {
            std::shared_ptr<Collider> collider = createCollider(args);
            m_allColliders.push_back(collider);
            return collider;
        }
        if (type == "Player") {
            std::shared_ptr<Player> player = loadPlayer(args);
            m_allPlayers.push_back(player);
            return player;
        }

        if (type == "Enemy") {
            std::shared_ptr<Enemy> enemy = loadEnemy(args);
            m_allEnemies.push_back(enemy);
            return enemy;
        }
        if (type == "Enemy2") {
            std::shared_ptr<Enemy> enemy2 = loadEnemy(args);
            m_allEnemies.push_back(enemy2);
            return enemy2;
        }
        if (type == "Bullet") {
            std::shared_ptr<Bullet> bullet = loadBullet(args);
            m_allBullets.push_back(bullet);
            return bullet;
        }
        return 0;
    }

    Transform* playerTransform();
    Transform* enemyTransform();

    Transform* bulletTransform();

    const glm::vec3 mousePos();

    void movePlayer(float deltaTime);

    void rotatePlayer(float deltaTime);

    void moveEnemy(float deltaTime);

    void rotateEnemy(float deltaTime);

    void collisionDetection(float deltaTime);

    void checkBoundaries();

    void shoot(float deltaTime);

    virtual void start();
    virtual void update(float deltaTime);


private:
    Application* m_app = nullptr;
    std::vector<std::shared_ptr<Entity>> m_allEntites;
    std::vector<std::shared_ptr<Player> > m_allPlayers;
    std::vector<std::shared_ptr<Enemy>> m_allEnemies;
    std::vector<std::shared_ptr<Bullet>> m_allBullets;
    std::vector<std::shared_ptr<Collider>> m_allColliders;
};
