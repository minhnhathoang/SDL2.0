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

    SDL_ShowCursor(true);

    Texture::getInstance()->setRenderer(renderer);
    Text::getInstance()->setRenderer(renderer);

    init();
}

void Game::init() {

    isRunning = true;
    isRestarting = false;
    status = -1;

    camera = { 0, 0, 0, 0 };

    if (player == nullptr) {
        player = new Player();
    }

    player->init();

    enemies.clear();

    for (int i = 0; i < 100; ++i) {
        enemies.emplace_back(new Enemy());
    }

    memset(keyboard, false, sizeof keyboard);


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
            Effect::getInstance()->addDeath((*it)->getID(), (*it)->getX(), (*it)->getY(), 1000, 0);
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

    if (player->getHP() <= 0 || player->getOxy() <= 0) {
        status = VICTORY;
    }

}

void Game::render() {
    if (isRestarting) return;

    SDL_RenderClear(renderer);

    Map::getInstance()->render(camera);
    Effect::getInstance()->renderDeaths(camera);
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->render(camera);
    }
    player->render(camera);
    //Effect::getInstance()->render(camera);

    SDL_Texture* shadow = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(shadow, SDL_BLENDMODE_MOD);

    Texture::getInstance()->load("assets/images/light/b.png", 1, 1);
    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture("assets/images/light/b.png"), SDL_BLENDMODE_ADD);

    SDL_SetRenderTarget(renderer, shadow);

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 0);
    SDL_RenderFillRect(renderer, nullptr);


    SDL_RenderClear(renderer);
    //Texture::getInstance()->render("assets/images/light/b.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, getAngle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, mouse.x, mouse.y), SDL_FLIP_NONE, 4);
    SDL_SetRenderTarget(renderer, 0);
    SDL_RenderCopy(renderer, shadow, NULL, NULL);

    SDL_DestroyTexture(shadow);

    renderHUD();

    endgame();

    SDL_RenderPresent(renderer);
}

//void Game::render() {
//    if (isRestarting) return;
//
//    SDL_RenderClear(renderer);
//
//    Map::getInstance()->render(camera);
//
//    Effect::getInstance()->renderDeaths(camera);
//
//
//    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
//        (*it)->render(camera);
//    }
//
//    player->render(camera);
//
//    Effect::getInstance()->render(camera);
//
//    SDL_Texture* shadow = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
//    SDL_SetTextureBlendMode(shadow, SDL_BLENDMODE_MOD);
//
//    Texture::getInstance()->load("assets/images/light/3.png", 1, 1);
//    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture("assets/images/light/3.png"), SDL_BLENDMODE_ADD);
//
//    SDL_SetRenderTarget(renderer, shadow);
////    static int u = 0, v = 0;
////    if (++v % 5 == 0) {
////        ++u;
////    }
//    SDL_SetRenderDrawColor(renderer, 200, 30, 30, 0);  /* put your desired tint , (the alpha value has no effect here) */
//    SDL_RenderFillRect(renderer, nullptr); /* draw the color to the entire shadow*/
//
//
//    Texture::getInstance()->render("assets/images/light/3.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, getAngle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, mouse.x, mouse.y), SDL_FLIP_NONE, 0.6);
//    SDL_SetRenderTarget(renderer, 0) /* set the render back to your scene*/;
//    SDL_RenderCopy(renderer, shadow, NULL, NULL); /* shadow */
//
//    SDL_DestroyTexture(shadow);
//
//
//
//
////    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MOD);
//
//
//
////    static int u = 100, v = 0;
////    ++v;
////    SDL_SetRenderDrawColor(renderer, listColor[player->idCrew].r, listColor[player->idCrew].g, listColor[player->idCrew].b, u);
////    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 2550);
////    if (v % 10 == 0)
////    u = u == 100 ? 0 : 100;
////
////    SDL_RenderFillRect(renderer, nullptr);
//
////    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
////    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
////    SDL_Rect dst  = {500, 500, 200, 200};
////    SDL_RenderFillRect(renderer, &dst);
//
//
////    Texture::getInstance()->load("assets/images/light/3.png", 1, 1);
////    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture("assets/images/light/3.png"), SDL_BLENDMODE_ADD);
////    Texture::getInstance()->render("assets/images/light/3.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, getAngle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, mouse.x, mouse.y), SDL_FLIP_NONE, 0.5);
////
//////    Texture::getInstance()->load("assets/images/light/4.png", 1, 1);
//////    SDL_SetTextureBlendMode(Texture::getInstance()->getTexture("assets/images/light/4.png"), SDL_BLENDMODE_MUL);
//////    Texture::getInstance()->render("assets/images/light/4.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, getAngle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, mouse.x, mouse.y));
//    //endgame();
//    //renderHUD();
////
//    SDL_RenderPresent(renderer);
//}

void Game::renderHUD() {
    // bar 321x19
    // health // (45, 699);
    // oxy bar (45, 731)

    Texture::getInstance()->render("assets/images/hud.png");

    SDL_SetRenderDrawBlendMode(Texture::getInstance()->getRenderer(), SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
    SDL_Rect dst = { 45, 699, player->getHP() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    SDL_SetRenderDrawColor(renderer, 53, 158, 187, 255);
    dst = { 45, 731, player->getOxy() * 321 / 100, 19 };
    SDL_RenderFillRect(renderer, &dst);

    auto [u, v] = player->getAmmunition();

    Text::getInstance()->render(to_string(u), 1260, 730 - 20 + 3, 1, 1);
    Text::getInstance()->render("/", 1275, 727, 1, 0.6);
    Text::getInstance()->render(to_string(v), 1280, 736 - 10, 0, 0.7);

    Text::getInstance()->render("$" + to_string(player->getCoin()), 10, 500);

    if (true) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 250);
        dst = { 45 + 500, 731, 100 * 321 / 100, 19 };
        SDL_RenderFillRect(renderer, &dst);
    }
}

void Game::endgame() {
    if (status == -1) {

        return;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer, nullptr);

    status = VICTORY;

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
    isRestarting = false;
}

void Game::clean() {
     Texture::getInstance()->release();
    Sound::getInstance()->release();
    Text::getInstance()->release();
    Map::getInstance()->release();
    Effect::getInstance()->release();

    delete player;

    while (enemies.size() > 0) {
        enemies.pop_back();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
