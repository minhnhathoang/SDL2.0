#include "header.h"
#include "game.h"
#include "texture.h"
#include "collision.h"

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        logSDLError("SDL_Init");
    }

    window = SDL_CreateWindow("SAS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (window == nullptr) {
        logSDLError("Create Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError("Create Renderer");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    assert(TTF_Init() == 0 && TTF_GetError());
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, SDL_MIX_MAXVOLUME) < 0) {
        cout << Mix_GetError() << '\n';
    }

    cout << "SDL initialized successfully !" << '\n';

    SDL_ShowCursor(true);

    Texture::getInstance()->setRenderer(renderer);
    Text::getInstance()->setRenderer(renderer);

    init();

    item = new Item();
}

void Game::init() {

    isRunning = true;
    isRestarting = false;
    status = -1;

    camera = { 0, 0, 0, 0 };

    Player::getInstance()->init();

    enemies.clear();

    for (int i = 0; i < 10; ++i) {
        enemies.emplace_back(new Enemy());
    }

    memset(keyboard, false, sizeof keyboard);

    currentLight = LIGHT;

    Texture::getInstance()->load("assets/images/hud.png", 1, 1);
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
                                }
                                break;
                            default:
                                break;
                        }
                    default:
                        break;
                }
            }
            if (flag == true) break;
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }
    } else {
        Texture::getInstance()->load("assets/images/menu/continue.png", 1, 1);
        Texture::getInstance()->load("assets/images/menu/restart.png", 1, 1);
        Texture::getInstance()->load("assets/images/menu/quit_.png", 1, 1);

        int curSelection = CONTINUE;
        while (true) {
            bool flag = false;

            if (curSelection == CONTINUE) {
                Texture::getInstance()->render("assets/images/menu/continue.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            } else if (curSelection == RESTART) {
                Texture::getInstance()->render("assets/images/menu/restart.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
            } else {
                Texture::getInstance()->render("assets/images/menu/quit_.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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
                                    isRestarting = true;
                                    isRunning = false;
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
            if (flag == true)
                break;
            SDL_RenderPresent(renderer);
        }
    }
}

void Game::handle() {
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
                if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT && Player::getInstance()->getELight() > 0) {
                    currentLight ^= 1;
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
                    mouse.R = 0;
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

    if (currentLight == FLASHLIGHT) {
        Player::getInstance()->energyLight--;
    }

    if (keyboard[SDL_SCANCODE_SPACE] == 0) {
        updateCamera();
    }

    Player::getInstance()->update(camera, keyboard, mouse);

    Effect::getInstance()->update();


    checkCollision(Player::getInstance(), enemies);

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->getHP() <= 0) {
            Effect::getInstance()->addDeath((*it)->getID(), (*it)->getX(), (*it)->getY(), 1000, 0);
            enemies.erase(it);
        } else {
            (*it)->update(camera, Player::getInstance());
            int w = getDistance(Player::getInstance()->getX(), Player::getInstance()->getY(), (*it)->getX(), (*it)->getY());
            if (w >= 200 && w <= 1000) {
                int dst = Map::getInstance()->getTile(Player::getInstance()->getX(), Player::getInstance()->getY() + 40 * Player::getInstance()->getScale());
                (*it)->findPath(dst);
            }
            ++it;
        }
    }

    if (Player::getInstance()->getHP() <= 0 || Player::getInstance()->getOxy() <= 0) {
        status = DEFEAT;
    }

    item->update(keyboard);
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (status == -1) {
        Map::getInstance()->render(camera);
        Effect::getInstance()->renderDeaths(camera);
        item->render(camera);
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            (*it)->render(camera);
        }
        Player::getInstance()->render(camera);
        Effect::getInstance()->light(currentLight, getAngle(Player::getInstance()->getX() - camera.x, Player::getInstance()->getY() - camera.y, mouse.x, mouse.y), camera);
        Effect::getInstance()->render(camera);
        Effect::getInstance()->redScreen(-1);
        renderHUD();
    } else {
        Map::getInstance()->render(camera);
        Effect::getInstance()->renderDeaths(camera);
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            (*it)->render(camera);
        }
        Player::getInstance()->render(camera);
        Effect::getInstance()->render(camera);
        endgame();
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::renderHUD() {
    // bar 321x19
    // health // (45, 699);
    // oxy bar (45, 731)

    Texture::getInstance()->render("assets/images/hud.png");

    SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
    SDL_Rect dst = { 45, 699, Player::getInstance()->getHP() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    SDL_SetRenderDrawColor(renderer, 53, 158, 187, 255);
    dst = { 45, 731, Player::getInstance()->getOxy() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    auto [u, v] = Player::getInstance()->getAmmunition();

    Text::getInstance()->render(40, to_string(u), 1260, 730 - 20 + 3, 1, 1);
    Text::getInstance()->render(40, "/", 1275, 727, 1, 0.6);
    Text::getInstance()->render(40, to_string(v), 1280, 736 - 10, 0, 0.7);

    if (currentLight == FLASHLIGHT) {
        string num_str = to_string(float(Player::getInstance()->getELight()) / 100);
        Text::getInstance()->render(30, "Light " + num_str.substr(0, num_str.find('.') + 3), SCREEN_WIDTH / 2 - 70, 720);
    }
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

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

bool Game::running() {
    return isRunning;
}

bool Game::restarting() {
    return isRestarting;
}

void Game::quit() {
    isRunning = false;
    isRestarting = false;
}

void Game::clean() {
    Texture::getInstance()->release();
    Sound::getInstance()->release();
    Text::getInstance()->release();
    Map::getInstance()->release();
    Effect::getInstance()->release();

    while (enemies.size() > 0) {
        enemies.pop_back();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
