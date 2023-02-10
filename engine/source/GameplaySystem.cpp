#include <include/GameplaySystem.h>
#include <Application.h>
#include <Transform.h>

float playerSpeed = 150.0f;
float enemySpeed = 50.0f;
float bulletSpeed = 10.0f;

int enemyHealth = 5;

Transform* GameplaySystem::playerTransform() {
    for (auto player : m_allPlayers) {
        auto transform = player->getEntity()->getComponent<Transform>();
        return transform;       
    }
}

Transform* GameplaySystem::enemyTransform() {
    for (auto enemy : m_allEnemies) {
        auto transform = enemy->getEntity()->getComponent<Transform>();
        return transform;
    }
}

Transform* GameplaySystem::bulletTransform() {
    for (auto bullet : m_allBullets) {
        auto transform = bullet->getEntity()->getComponent<Transform>();
        return transform;
    }
}

const glm::vec3 GameplaySystem::mousePos() {
    auto mousePos = m_app->getCursorPos();

    auto windowX = m_app->getWindowSize().x;
    auto windowY = m_app->getWindowSize().y;

    auto newMouseX = 800.0f * (mousePos.x / windowX);
    auto newMouseY = 600.0f * (mousePos.y / windowY);

    glm::vec3 newMousePos(newMouseX, newMouseY, 0);

    return newMousePos;
}

void GameplaySystem::movePlayer(float deltaTime) {
    float deltaX = float(m_app->getKeyState(GLFW_KEY_D) - m_app->getKeyState(GLFW_KEY_A));
    float deltaY = float(m_app->getKeyState(GLFW_KEY_S) - m_app->getKeyState(GLFW_KEY_W));

    // Normalize the vector
    float deltaV = sqrt(deltaX * deltaX + deltaY * deltaY);

    glm::vec3 delta = deltaTime * playerSpeed * glm::vec3(deltaX / deltaV, deltaY / deltaV, 0.0f);

    if (deltaV != 0) {
        playerTransform()->setPosition(playerTransform()->getPosition() + delta);
    }
}

void GameplaySystem::rotatePlayer(float deltaTime) {
    glm::vec2 lookDir = mousePos() - playerTransform()->getPosition(); // Vector from player to cursor
    lookDir = glm::normalize(lookDir);
    float angle = glm::atan(lookDir.y, lookDir.x); // Rotation angle calculation

    playerTransform()->setRotationZ(angle);
}

void GameplaySystem::moveEnemy(float deltaTime) {
    float enemyDeltaX = playerTransform()->getPosition().x - enemyTransform()->getPosition().x;
    float enemyDeltaY = playerTransform()->getPosition().y - enemyTransform()->getPosition().y;

    float enemyDeltaV = sqrt(enemyDeltaX * enemyDeltaX + enemyDeltaY * enemyDeltaY);

    glm::vec3 enemyDelta = deltaTime * enemySpeed * glm::vec3(enemyDeltaX / enemyDeltaV, enemyDeltaY / enemyDeltaV, 0.0f);

    if (enemyDeltaV != 0) {
        enemyTransform()->setPosition(enemyTransform()->getPosition() + enemyDelta);
    }
}

void GameplaySystem::shoot(float deltaTime) {
    auto shootDir = mousePos() - playerTransform()->getPosition();

    if (m_app->getMouseState(GLFW_MOUSE_BUTTON_LEFT)) {
        printf("Bang bang\n");

        // Place the bullet at player's position and rotation
        bulletTransform()->setPosition(playerTransform()->getPosition());
        bulletTransform()->setRotationZ(playerTransform()->getRotationZ());
    }
    bulletTransform()->setPosition(bulletTransform()->getPosition() + glm::vec3(shootDir.x * bulletSpeed, shootDir.y * bulletSpeed, 0) * deltaTime);
}

void GameplaySystem::rotateEnemy(float deltaTime) {
    for (auto enemy : m_allEnemies) {
        glm::vec2 LookDir = playerTransform()->getPosition() - enemyTransform()->getPosition();
        LookDir = glm::normalize(LookDir);
        float angle = glm::atan(LookDir.y, LookDir.x);

        enemyTransform()->setRotationZ(angle);
    }

}

void GameplaySystem::collisionDetection(float deltaTime) {
    auto playerPos = playerTransform()->getPosition();
    auto playerScale = playerTransform()->getScaling();
    auto enemyPos = enemyTransform()->getPosition();
    auto enemyScale = enemyTransform()->getScaling();
    auto bulletPos = bulletTransform()->getPosition();
    auto bulletScale = bulletTransform()->getScaling();


    // Some stupid collision detection between player and enemy
    if (playerPos.x < enemyPos.x + enemyScale.x &&
        playerPos.x + playerScale.x > enemyPos.x &&
        playerPos.y < enemyPos.y + enemyScale.y &&
        playerScale.y + playerPos.y > enemyPos.y) {

        glm::vec2 enemyLookDir = playerTransform()->getPosition() - enemyTransform()->getPosition();

        printf("Collision at x: %f y: %f\n", playerPos.x, playerPos.y);
        playerTransform()->setPosition(playerPos + glm::vec3(1 * enemyLookDir.x, 1 * enemyLookDir.y, 0));
    }

    if (bulletPos.x < enemyPos.x + enemyScale.x &&
        bulletPos.x + bulletScale.x > enemyPos.x &&
        bulletPos.y < enemyPos.y + enemyScale.y &&
        bulletScale.y + bulletPos.y > enemyPos.y) {

        glm::vec2 knockbackDir = enemyTransform()->getPosition() - bulletTransform()->getPosition();

        printf("Collision at x: %f y: %f\n", playerPos.x, playerPos.y);
        enemyTransform()->setPosition(enemyPos + glm::vec3(1 * knockbackDir.x, 1 * knockbackDir.y, 0));
        bulletTransform()->setPosition(glm::vec3(0, 0, 0));
        enemyHealth -= 1;
        printf("Enemy health: %i\n", enemyHealth);

        // "Destroy" the enemy here
        if (enemyHealth <= 0) {
            enemyTransform()->setPosition(glm::vec3(0,0,10));
        }
    }
}

void GameplaySystem::checkBoundaries() {
    if (playerTransform()->getPosition().x > 800.0f || playerTransform()->getPosition().x < 0.0f ||
        playerTransform()->getPosition().y > 600.0f || playerTransform()->getPosition().y < 0.0f) {
        printf("Outside of window\n");
        playerSpeed *= -1;
    }
    else if (playerSpeed < 0) {
        playerSpeed = 150.0f;
    }
}

void GameplaySystem::start() {
}

void GameplaySystem::update(float deltaTime) {

    movePlayer(deltaTime);
    rotatePlayer(deltaTime);
    moveEnemy(deltaTime);
    rotateEnemy(deltaTime);
    collisionDetection(deltaTime);
    shoot(deltaTime);
    checkBoundaries();
}



