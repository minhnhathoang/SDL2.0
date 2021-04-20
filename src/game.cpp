#include "header.h"
#include "game.h"
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

    Texture::getInstance()->setRenderer(renderer);
    Text::getInstance()->setRenderer(renderer);

    init();
}

void Game::init() {

    isRunning = true;
    isRestarting = false;

    SDL_ShowCursor(true);

    camera = { 0, 0, 0, 0 };

    player = new Player();

    for (int i = 0; i < 10; ++i) {
        enemies.emplace_back(new Enemy());
    }

    memset(keyboard, false, sizeof keyboard);


    Texture::getInstance()->load("assets/images/hud.png", 1, 1);

    item = new Item();
    //Sound::getInstance()->playMusic();
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
                                if (curSelection == QUIT) this->quit();
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
                                curSelection = (curSelection + 2) % 3;
                                break;
                            case SDL_SCANCODE_DOWN:
                                curSelection = (curSelection + 1) % 3;
                                break;
                            case SDL_SCANCODE_RETURN:
                                if (curSelection == CONTINUE) {

                                } else if (curSelection == RESTART) {
                                    isRestarting = true;
                                    this->quit();
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
            //SDL_RenderClear(renderer);
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


    if (keyboard[SDL_SCANCODE_SPACE] == 0) {
        updateCamera();
    }

    player->update(camera, keyboard, mouse);


    Effect::getInstance()->update();


    checkCollision(player, enemies);

    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->getHP() <= 0) {
            Effect::getInstance()->addDeath((*it)->getID(), (*it)->getX(), (*it)->getY(), 5000, 0);
            enemies.erase(it);
        } else {
            (*it)->update(camera, player);
            int w = getDistance(player->getX(), player->getY(), (*it)->getX(), (*it)->getY());
            if (w >= 100 && w <= 1000) {
                (*it)->findPath(Map::getInstance()->getTile(player->getX(), player->getY() + 40));
            }
            ++it;
        }
    }

}

void Game::render() {
    if (isRestarting) return;

    SDL_RenderClear(renderer);

    Map::getInstance()->render(camera);

    Effect::getInstance()->renderDeaths(camera);

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

    int uu, vv;
    SDL_GetMouseState(&uu, &vv);
    SDL_RenderDrawLine(Texture::getInstance()->getRenderer(), player->getX() - camera.x, player->getY() - camera.y - 10, uu, vv);

    //item->render(camera);

    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->render(camera);
    }

    player->render(camera);

    Effect::getInstance()->render(camera);


    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);

    static int u = 200, v = 0;
//    ++v;
//    //SDL_SetRenderDrawColor(renderer, listColor[player->idCrew].r, listColor[player->idCrew].g, listColor[player->idCrew].b, u);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
//    if (v % 10 == 0)
//    u = u == 100 ? 0 : 100;
//
//  Effect::getInstance()->shake(camera, 20);
//
    SDL_RenderFillRect(renderer, NULL);

//    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
//    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
//    SDL_Rect dst  = {500, 500, 200, 200};
//    SDL_RenderFillRect(renderer, &dst);

    renderHUD();

    SDL_RenderPresent(renderer);
}

void Game::renderHUD() {
    // bar 321x19
    // health // (45,699);
    // oxy bar (45,731)

    Texture::getInstance()->render("assets/images/hud.png");

    SDL_SetRenderDrawColor(renderer, 235, 81, 69, 0);
    SDL_Rect dst = { 45, 699, player->getHP() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    SDL_SetRenderDrawColor(renderer, 53, 158, 187, 0);
    dst = { 45, 731, player->getOxy() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    auto [u, v] = player->getAmmunition();

    Text::getInstance()->render(to_string(u), 1260, 730 - 20 + 3, 1, 1);
    Text::getInstance()->render("/", 1275, 727, 1, 0.6);
    Text::getInstance()->render(to_string(v), 1280, 736 - 10, 0, 0.7);

    Text::getInstance()->render("$" + to_string(player->getCoin()), 10, 500);




    //Text::getInstance()->render("Shooting MEOW", 500, 500);

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 250);
}

void Game::updateCamera() {
    camera.x = player->getX() - SCREEN_WIDTH / 2 + camera.w;
    camera.y = player->getY() - SCREEN_HEIGHT / 2 + camera.h;
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
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
