#include "header.h"
#include "game.h"
#include "item.h"
#include "text.h"
#include "texture.h"
#include "collision.h"


Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        logSDLError("SDL_Init");
    }

    window = SDL_CreateWindow("SAS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError("Create Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (renderer == nullptr) {
        logSDLError("Create Renderer");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    assert(TTF_Init() == 0 && TTF_GetError());
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, SDL_MIX_MAXVOLUME) < 0) {
        cerr << Mix_GetError() << '\n';
    }
    cerr << "SDL initialized successfully !" << '\n';

    SDL_ShowCursor(true);
}

void Game::init() {
    time = 0;

    isRunning = true;
    status = -1;

    camera = { 0, 0, 0, 0 };

    enemies.clear();

    while (enemies.size() < 10) {
        enemies.push_back(new Enemy());
    }

    memset(keyboard, false, sizeof keyboard);

    currentLight = NONE;
    showTab = false;

    Texture::getInstance()->load("assets/images/bar.png", 1, 1);
    Item::getInstance()->init();

    score = 0;
}

void Game::menu(int type) {
    SDL_Event event;

    if (type == 0) {
        Texture::getInstance()->load("assets/images/menu/play.png", 1, 1);
        Texture::getInstance()->load("assets/images/menu/quit.png", 1, 1);

        int curSelection = PLAY;
        while (true) {
            bool flag = false;

            if (curSelection == PLAY) {
                Texture::getInstance()->render("assets/images/menu/play.png");
            } else {
                Texture::getInstance()->render("assets/images/menu/quit.png");
            }

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_UP:
                            case SDL_SCANCODE_DOWN:
                                curSelection = curSelection == PLAY ? QUIT : PLAY;
                                break;
                            case SDL_SCANCODE_RETURN:
                                flag = true;
                                if (curSelection == QUIT) {
                                    this->quit();
                                } else {
                                    this->init();
                                    this->option();
                                }
                                break;
                            default:
                                break;
                        }
                    default:
                        break;
                }
            }
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            if (flag == true) {
                break;
            }
        }
        Texture::getInstance()->destroy("assets/images/menu/play.png");
        Texture::getInstance()->destroy("assets/images/menu/quit.png");
    } else {
        Texture::getInstance()->load("assets/images/menu/continue.png", 1, 1);
        Texture::getInstance()->load("assets/images/menu/restart.png", 1, 1);
        Texture::getInstance()->load("assets/images/menu/quit_.png", 1, 1);

        int curSelection = CONTINUE;
        while (true) {
            bool flag = false;

            if (curSelection == CONTINUE) {
                Texture::getInstance()->render("assets/images/menu/continue.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.5);
            } else if (curSelection == RESTART) {
                Texture::getInstance()->render("assets/images/menu/restart.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.5);
            } else {
                Texture::getInstance()->render("assets/images/menu/quit_.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.5);
            }

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_UP:
                                curSelection = (curSelection - 1 + 2) % 3 + 1;
                                break;
                            case SDL_SCANCODE_DOWN:
                                curSelection = (curSelection - 1 + 1) % 3 + 1;
                                break;
                            case SDL_SCANCODE_RETURN:
                                flag = true;
                                if (curSelection == CONTINUE) {

                                } else if (curSelection == RESTART) {
                                    this->init();
                                    this->option();
                                } else if (curSelection == QUIT) {
                                    this->quit();
                                }
                                flag = true;
                                break;
                        }
                    default:
                        break;
                }
            }
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            if (flag == true) {
                break;
            }
        }
        Texture::getInstance()->destroy("assets/images/menu/continue.png");
        Texture::getInstance()->destroy("assets/images/menu/restart.png");
        Texture::getInstance()->destroy("assets/images/menu/quit_.png");
    }
    SDL_RenderPresent(renderer);
}

void Game::handle() {
    mouse.R = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit();
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode < MAX_KEY) {
                    keyboard[event.key.keysym.scancode] = 1;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_F && Player::getInstance()->getELight() > 0 && currentLight != NONE) {
                    currentLight ^= 1;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_TAB) {
                    showTab ^= true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.scancode < MAX_KEY) {
                    keyboard[event.key.keysym.scancode] = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouse.L = 1;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouse.R = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouse.L = 0;
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    //mouse.R = 0;
                }
                break;
            default:
                break;
        }
    }
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (keyboard[SDL_SCANCODE_ESCAPE] == 1) {
        menu(1);
        keyboard[SDL_SCANCODE_ESCAPE] = 0;
    }
}

void Game::update() {

    ++time;
    if (time > 1e9) time = 0;

    if (keyboard[SDL_SCANCODE_SPACE] == 0) {
        updateCamera();
    }

    if (currentWeather == SUNNY) {
        Player::getInstance()->eLight += 3;
    }
    if (currentLight == FLASHLIGHT && Player::getInstance()->eLight > 0) {
        --Player::getInstance()->eLight;
    }
    if (time % 2000 == 0) {
        currentLight = randInt(NONE, FLASHLIGHT);
    }
    if (time % 1500 == 0) {
        currentWeather = randInt(NONE, SNOW);
    }
    if (Player::getInstance()->getELight() <= 0 && currentLight == FLASHLIGHT) {
        currentLight = DARK;
    }

    if (time % 4000 == 0) {
        while (enemies.size() < MAX_ENEMY + randInt(-5, 5)) {
            enemies.push_back(new Enemy());
        }
        if (time % 20000 == 0) {
            while (enemies.size() < MAX_ENEMY * randF(1.5, 2)) {
                enemies.push_back(new Enemy());
            }
        }
    }

    Player::getInstance()->update(camera, keyboard, mouse);

    Effect::getInstance()->update();

    checkCollision(Player::getInstance(), enemies, camera);

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->getHP() <= 0) {
            Effect::getInstance()->addDeath((*it)->getID(), (*it)->getX(), (*it)->getY() + 20 * (*it)->getScale(), 1000, (*it)->getScale());
            score += (*it)->getScale() * 10;
            enemies.erase(it);
        } else {
            (*it)->update(camera, Player::getInstance());
            int w = getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), (*it)->getX(), (*it)->getY());
            if (w >= 200 && w <= 1500) {
                int dst = Map::getInstance()->getTile(Player::getInstance()->getX(), Player::getInstance()->getY() + 40 * Player::getInstance()->getScale());
                (*it)->findPath(dst);
            }
            ++it;
        }
    }

    if (Player::getInstance()->getHP() <= 0 || Player::getInstance()->getOxy() <= 0) {
        status = DEFEAT;
    }

    Item::getInstance()->update(keyboard);

    Effect::getInstance()->shake(camera);

    if (score > 200) {
        Player::getInstance()->lockGuns[4] = true;
        Player::getInstance()->lockGuns[5] = true;
        Player::getInstance()->lockGuns[7] = true;
    }
    if (score > 400) {
        Player::getInstance()->lockGuns[2] = true;
    }
    if (score > 600) {
        Player::getInstance()->lockGuns[6] = true;
    }
    if (score > 700) {
        Player::getInstance()->lockGuns[3] = true;
        Player::getInstance()->lockGuns[10] = true;
    }
    if (score > 1000) {
        Player::getInstance()->lockGuns[11] = true;
    }
    if (score > 5000) {
        status = VICTORY;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (status == -1) {
        Map::getInstance()->render(camera);
        Effect::getInstance()->renderDeaths(camera);
        Item::getInstance()->render(camera, mouse);
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            (*it)->render(camera);
        }
        Player::getInstance()->render(camera, mouse);
        Effect::getInstance()->light(currentLight, getAngle(Player::getInstance()->getX() - camera.x, Player::getInstance()->getY() - camera.y, mouse.x, mouse.y), camera);
        Effect::getInstance()->render(camera);
        Effect::getInstance()->redScreen(0);
        renderHUD();
    } else {
        Map::getInstance()->render(camera);
        Effect::getInstance()->renderDeaths(camera);
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            (*it)->render(camera);
        }
        Player::getInstance()->render(camera, mouse);
        Effect::getInstance()->render(camera);
        this->endgame();
    }


    Effect::getInstance()->renderHit(camera);

    Effect::getInstance()->weather(currentWeather, camera);


    if (status == -1) {
        if (Player::getInstance()->getHP() <= 20) {
            Effect::getInstance()->alert(rgbA(255, 100, 100, 50));
        } else if (Player::getInstance()->getOxy() <= 1000) {
            Effect::getInstance()->alert(rgbA(53, 158, 187, 100));
        }
    }

    if (showTab && status == -1) {
        Item::getInstance()->renderTab(mouse);
        Text::getInstance()->render(30, "Score " + to_string(score), SCREEN_WIDTH / 2, 20, CENTER);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

void Game::renderHUD() {
    SDL_Rect src = { 0, 0, 1366, 72 };
    SDL_Rect dst = {0, SCREEN_HEIGHT - 72, 1366, 72 };
    Texture::getInstance()->render("assets/images/bar.png", src, dst);

    SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
    dst = { 45, 699, Player::getInstance()->getHP() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    SDL_SetRenderDrawColor(renderer, 53, 158, 187, 255);
    dst = { 45, 731, Player::getInstance()->getOxy() * 321 / 10000, 19 };
    SDL_RenderFillRect(renderer, &dst);

    auto [u, v] = Player::getInstance()->getAmmunition();

    Text::getInstance()->render(40, to_string(u), 1260, 730 - 20, RIGHT);
    Text::getInstance()->render(20, "/", 1275, 730, 1);
    Text::getInstance()->render(30, to_string(v), 1290, 736 - 12, LEFT);

    if (currentLight == FLASHLIGHT || showTab) {
        string num_str = to_string(float(Player::getInstance()->getELight()) / 100);
        Text::getInstance()->render(20, "Flashlight " + num_str.substr(0, num_str.find('.') + 3), SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT - 35, LEFT);
    }

    Item::getInstance()->radar(Player::getInstance(), enemies, 150, 150, 1700, 15);
}

void Game::endgame() {
    if (status == -1) {
        return;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRect(renderer, nullptr);

    if (status == VICTORY) {
        Texture::getInstance()->load("assets/images/victory.png", 1, 1);
        Texture::getInstance()->render("assets/images/victory.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    } else if (status == DEFEAT) {
        Texture::getInstance()->load("assets/images/defeat.png", 1, 1);
        Texture::getInstance()->render("assets/images/defeat.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void Game::updateCamera() {
    camera.x = Player::getInstance()->getX() - SCREEN_WIDTH / 2 + camera.w;
    camera.y = Player::getInstance()->getY() - SCREEN_HEIGHT / 2 + camera.h;
}

int Game::getTime() {
    return time;
 }

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

bool Game::running() {
    return isRunning;
}

void Game::option() {
    int currentColor = 0;
    SDL_Event event;
    bool flag = false;
    while (!flag) {
        SDL_RenderClear(renderer);
        SDL_Rect dst = {150, 500, 40, 40};

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        (currentColor += 15) %= 16;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        (currentColor += 1) %= 16;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        Player::getInstance()->setColor(currentColor);
                        Text::getInstance()->setColor(currentColor);
                        flag = true;
                    }
                    break;

            }
        }
        Text::getInstance()->render(40, "Choose color", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CENTER, listColor[currentColor]);
        for (int i = 0; i <= 15; ++i) {
            if (i == currentColor) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawLine(renderer, dst.x, dst.y + dst.h + 10, dst.x + dst.w, dst.y + dst.h + 10);
            }
            SDL_SetRenderDrawColor(renderer, listColor[i].r, listColor[i].g, listColor[i].b, 255);
            SDL_RenderFillRect(renderer, &dst);
            dst.x += dst.w + 30;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    }

    flag = false;
    bool currentSelect = true;
    while (!flag) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT || event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        currentSelect ^= true;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                        SDL_ShowCursor(currentSelect);
                        flag = true;
                    }
                    break;

            }
        }
        SDL_RenderClear(renderer);
        Text::getInstance()->render(40, "Do you want display cursor ?", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CENTER);
        Text::getInstance()->render(40, "Yes", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, LEFT);
        Text::getInstance()->render(40, "No", SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 + 50, RIGHT);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (currentSelect) {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 100, SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 + 100);
        } else {
            SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 100 + 150, SCREEN_HEIGHT / 2 + 100, SCREEN_WIDTH / 2 - 30 + 130, SCREEN_HEIGHT / 2 + 100);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    Player::getInstance()->init();
}

void Game::quit() {
    isRunning = false;
}

void Game::clean() {
    Texture::getInstance()->release();
    Sound::getInstance()->release();
    Text::getInstance()->release();
    Effect::getInstance()->release();

    while (!enemies.empty()) {
        enemies.pop_back();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
