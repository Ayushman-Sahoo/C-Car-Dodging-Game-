#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace sf;
using namespace std;

// ================= ENEMY =================

struct Enemy {

    Sprite sprite;

    float speed;
    int lane;

    Enemy(
        Texture& tex,
        float x,
        float y,
        float scale,
        float spd,
        int ln
    ) {

        sprite.setTexture(tex);

        sprite.setScale(scale, scale);

        sprite.setPosition(x, y);

        speed = spd;

        lane = ln;
    }

    void update(float dt) {

        sprite.move(0, speed * dt * 60);
    }
};

// ================= MAIN =================

int main() {

    srand(time(0));

    // ================= WINDOW =================

    RenderWindow window(

        VideoMode(900, 700),

        "Car Dodging Game"
    );

    window.setFramerateLimit(60);

    float W = window.getSize().x;
    float H = window.getSize().y;

    // ================= LOAD TEXTURES =================

    Texture playerTex;

    Texture redTex1;
    Texture redTex2;

    Texture yellowTex1;
    Texture yellowTex2;
    Texture yellowTex3;

    if (!playerTex.loadFromFile("Assets/WhiteCar.png")) {

        cout << "Player texture failed!" << endl;
    }

    if (!redTex1.loadFromFile("Assets/RedCar1.png")) {

        cout << "RedCar1 failed!" << endl;
    }

    if (!redTex2.loadFromFile("Assets/RedCar2.png")) {

        cout << "RedCar2 failed!" << endl;
    }

    if (!yellowTex1.loadFromFile("Assets/YellowCar1.png")) {

        cout << "YellowCar1 failed!" << endl;
    }

    if (!yellowTex2.loadFromFile("Assets/YellowCar2.png")) {

        cout << "YellowCar2 failed!" << endl;
    }

    if (!yellowTex3.loadFromFile("Assets/YellowCar3.png")) {

        cout << "YellowCar3 failed!" << endl;
    }

    vector<Texture*> enemyTextures = {

        &redTex1,
        &redTex2,

        &yellowTex1,
        &yellowTex2,
        &yellowTex3
    };

    // ================= SCALE =================

    float scale = 0.45f;

    // ================= ROAD =================

    const int LANES = 4;

    float roadWidth = 400;

    float roadLeft =
        W / 2 - roadWidth / 2;

    float laneWidth =
        roadWidth / LANES;

    float lanePos[LANES];

    for (int i = 0; i < LANES; i++) {

        lanePos[i] =

            roadLeft +

            i * laneWidth +

            laneWidth / 2;
    }

    // ================= PLAYER =================

    int laneIndex = 1;

    Sprite player;

    player.setTexture(playerTex);

    player.setScale(scale, scale);

    float playerW =

        playerTex.getSize().x * scale;

    player.setPosition(

        lanePos[laneIndex] -

        playerW / 2,

        H - 140
    );

    // ================= FONT =================

    Font font;

    if (!font.loadFromFile(
        "Assets/DejaVuSans-Bold.ttf")) {

        cout << "Font failed!" << endl;
    }

    Text menu;
    Text scoreText;
    Text speedText;
    Text info;

    menu.setFont(font);
    scoreText.setFont(font);
    speedText.setFont(font);
    info.setFont(font);

    menu.setCharacterSize(28);

    menu.setString(

        "SELECT DIFFICULTY\n\n"

        "E - EASY\n"

        "M - MEDIUM\n"

        "H - HARD"
    );

    menu.setPosition(

        W / 2 - 150,

        H / 2 - 120
    );

    scoreText.setCharacterSize(22);

    speedText.setCharacterSize(22);

    info.setCharacterSize(28);

    scoreText.setPosition(20, 10);

    speedText.setPosition(W - 180, 10);

    info.setPosition(W / 2 - 120, 50);

    // ================= SOUND =================

    SoundBuffer crashBuffer;

    if (!crashBuffer.loadFromFile(
        "Assets/crash.wav")) {

        cout << "ERROR: Crash sound failed to load!"
             << endl;
    }

    Sound crash;

    crash.setBuffer(crashBuffer);

    crash.setVolume(100);

    // ================= GAME VARIABLES =================

    vector<Enemy> enemies;

    Clock spawnClock;
    Clock deltaClock;
    Clock scoreClock;

    bool started = false;

    bool gameOver = false;

    bool paused = false;

    float spawnDelay = 1.2f;

    float gameSpeed = 1.0f;

    float score = 0;

    float roadOffset = 0;

    float selectedSpeed = 2.0f;

    // ================= GAME LOOP =================

    while (window.isOpen()) {

        float dt =

            deltaClock.restart().asSeconds();

        Event e;

        while (window.pollEvent(e)) {

            // CLOSE

            if (e.type == Event::Closed) {

                window.close();
            }

            // KEY PRESS

            if (e.type == Event::KeyPressed) {

                // ================= MENU =================

                if (!started) {

                    // EASY

                    if (e.key.code ==
                        Keyboard::E) {

                        spawnDelay = 1.5f;

                        gameSpeed = 2.0f;

                        selectedSpeed = 2.0f;

                        started = true;
                    }

                    // MEDIUM

                    if (e.key.code ==
                        Keyboard::M) {

                        spawnDelay = 1.1f;

                        gameSpeed = 4.0f;

                        selectedSpeed = 4.0f;

                        started = true;
                    }

                    // HARD

                    if (e.key.code ==
                        Keyboard::H) {

                        spawnDelay = 0.7f;

                        gameSpeed = 6.0f;

                        selectedSpeed = 6.0f;

                        started = true;
                    }
                }

                // ================= CONTROLS =================

                else {

                    // PAUSE

                    if (e.key.code ==
                        Keyboard::P) {

                        paused = !paused;
                    }

                    // PLAYER MOVEMENT

                    if (!gameOver &&
                        !paused) {

                        if (e.key.code ==
                            Keyboard::Left &&

                            laneIndex > 0) {

                            laneIndex--;
                        }

                        if (e.key.code ==
                            Keyboard::Right &&

                            laneIndex < LANES - 1) {

                            laneIndex++;
                        }

                        player.setPosition(

                            lanePos[laneIndex] -

                            playerW / 2,

                            player.getPosition().y
                        );
                    }

                    // RESTART

                    if (e.key.code ==
                        Keyboard::R &&

                        gameOver) {

                        enemies.clear();

                        gameOver = false;

                        paused = false;

                        score = 0;

                        gameSpeed = selectedSpeed;

                        scoreClock.restart();
                    }
                }
            }
        }

        // ================= UPDATE =================

        if (started &&
            !paused &&
            !gameOver) {

            // SCORE

            if (scoreClock
                    .getElapsedTime()
                    .asSeconds() >= 1) {

                score++;

                scoreClock.restart();
            }

            // SPAWN ENEMIES

            if (spawnClock
                    .getElapsedTime()
                    .asSeconds() > spawnDelay) {

                spawnClock.restart();

                int lane =
                    rand() % LANES;

                float spawnY = -150;

                bool safe = true;

                for (auto& c : enemies) {

                    if (c.lane == lane &&

                        abs(c.sprite
                                .getPosition().y -

                            spawnY) < 180) {

                        safe = false;

                        break;
                    }
                }

                if (safe) {

                    Texture* t =

                        enemyTextures[
                            rand() %

                            enemyTextures.size()
                        ];

                    float ew =

                        t->getSize().x *

                        scale;

                    enemies.emplace_back(

                        *t,

                        lanePos[lane] -

                        ew / 2,

                        spawnY,

                        scale,

                        4 + gameSpeed,

                        lane
                    );
                }
            }

            // MOVE ENEMIES

            for (auto& c : enemies) {

                c.update(dt);
            }

            // COLLISION

            for (auto& c : enemies) {

                FloatRect p =

                    player.getGlobalBounds();

                FloatRect e =

                    c.sprite.getGlobalBounds();

                p.top += 20;
                p.height -= 40;

                e.top += 20;
                e.height -= 40;

                if (p.intersects(e)) {

                    // PLAY SOUND

                    crash.play();

                    gameOver = true;

                    float playerTop =

                        player.getPosition().y;

                    float enemyHeight =

                        c.sprite
                            .getGlobalBounds()
                            .height;

                    c.sprite.setPosition(

                        c.sprite
                            .getPosition().x,

                        playerTop -

                        enemyHeight + 5
                    );

                    break;
                }
            }

            // REMOVE OFFSCREEN

            enemies.erase(

                remove_if(

                    enemies.begin(),

                    enemies.end(),

                    [&](Enemy& c) {

                        return c.sprite
                                   .getPosition()
                                   .y > H;
                    }),

                enemies.end()
            );

            // SPEED LIMIT

            if (gameSpeed < 15) {

                gameSpeed += dt * 0.5f;
            }
        }

        // ROAD MOVEMENT

        if (started &&
            !paused &&
            !gameOver) {

            roadOffset += 300 * dt;
        }

        if (roadOffset > 80) {

            roadOffset = 0;
        }

        // ================= TEXT =================

        scoreText.setString(

            "Score: " +

            to_string((int)score)
        );

        stringstream ss;

        ss << "Speed: "

           << fixed

           << setprecision(1)

           << gameSpeed;

        speedText.setString(ss.str());

        if (gameOver) {

            info.setString(

                "GAME OVER - PRESS R"
            );
        }

        else if (paused) {

            info.setString("PAUSED");
        }

        else {

            info.setString("");
        }

        // ================= DRAW =================

        window.clear(Color::Black);

        // MENU

        if (!started) {

            window.draw(menu);
        }

        else {

            // ROAD

            RectangleShape road(

                Vector2f(
                    roadWidth,
                    H
                )
            );

            road.setPosition(
                roadLeft,
                0
            );

            road.setFillColor(
                Color(60, 60, 60)
            );

            window.draw(road);

            // ROAD LINES

            float centerX = W / 2;

            for (float y = -80;

                 y < H;

                 y += 100) {

                RectangleShape line(

                    Vector2f(6, 50)
                );

                line.setPosition(

                    centerX - 3,

                    y + roadOffset
                );

                line.setFillColor(
                    Color::White
                );

                window.draw(line);
            }

            // PLAYER

            window.draw(player);

            // ENEMIES

            for (auto& c : enemies) {

                window.draw(c.sprite);
            }

            // UI

            window.draw(scoreText);

            window.draw(speedText);

            window.draw(info);
        }

        window.display();
    }

    return 0;
}
