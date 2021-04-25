#include "texture.h"
#include "game.h"

Texture::Texture() {
    //renderer = Game::getIn->getRenderer();
}

void Texture::load(string ID, int row, int col) {

    if (textureMap.find(ID) != textureMap.end()) {
        return;
    }

    textureData u;

    u.texture = IMG_LoadTexture(renderer, ID.c_str());

    if (u.texture == nullptr) {
        cout << ID << " ";
        logSDLError("Load Texture");
    }

    SDL_QueryTexture(u.texture, 0, 0, &u.width, &u.height);

    u.nFrames = row * col;
    u.width /= col;
    u.height /= row;
    u.col = col;
    u.row = row;

    textureMap[ID] = u;

    // cout << textureMap.size() << endl;

}

void Texture::render(string ID, int x, int y, int currentFrames, float angle, SDL_RendererFlip flip, float scale, SDL_Point* point) {

    SDL_Rect src, dst;

    textureData& temp = textureMap[ID];

    src.x = (currentFrames % temp.col);
    if (src.x == 0) src.x = temp.col;
    src.x = (src.x - 1) * temp.width;
    src.y = (ceil(currentFrames * 1.0f / temp.col) - 1) * temp.height;
    src.w = temp.width;
    src.h = temp.height;

    dst.w = temp.width * scale;
    dst.h = temp.height * scale;
    dst.x = x - dst.w / 2;
    dst.y = y - dst.h / 2;

    SDL_RenderCopyEx(renderer, temp.texture, &src, &dst, angle, point, flip);
}

void Texture::render(string ID, SDL_Rect src, SDL_Rect dst) {
    textureData& temp = textureMap[ID];

    SDL_RenderCopy(renderer, temp.texture, &src, &dst);
}

void Texture::render(string ID, int x, int y) {
    textureData& temp = textureMap[ID];
    SDL_Rect dst;
    dst.x = x - temp.width / 2;
    dst.y = y - temp.height / 2;
    dst.w = temp.width;
    dst.h = temp.height;
    SDL_RenderCopy(renderer, temp.texture, 0, &dst);
}

void Texture::render(string ID) {
    textureData& temp = textureMap[ID];

    SDL_RenderCopy(renderer, temp.texture, 0, 0);
}

void Texture::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

SDL_Renderer* Texture::getRenderer() {
    return renderer;
}

SDL_Texture* Texture::getTexture(string ID) {
    return textureMap[ID].texture;
}

void Texture::destroy(string ID) {
    map<string, textureData>::iterator it = textureMap.find(ID);

    if (it == textureMap.end()) {
        cout << ID << " has not been loaded !\n";
    } else {
        SDL_DestroyTexture(it->second.texture);
        textureMap.erase(it);
    }
}

void Texture::release() {
    for (auto it = textureMap.begin(); it != textureMap.end(); ++it) {
        SDL_DestroyTexture(it->second.texture);
        it->second.texture = nullptr;
    }
    textureMap.clear();
}
