#include <fstream>
#include <iostream>
#include <algorithm>
#include "Resources.h"
#include "Game.h"

static void WriteErrorinFile(int code){
    std::ofstream errorfile("errorlog.txt");
    errorfile << SDL_GetError() << std::endl;
    errorfile.close();
    exit(code);
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
    if (imageTable.find(file) == imageTable.end()){
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if (texture == nullptr){
            WriteErrorinFile(101);
        }
        imageTable.emplace(file, std::shared_ptr<SDL_Texture>(texture, [](SDL_Texture* tx){ SDL_DestroyTexture(tx); }));
    }
    return imageTable[file];
}

void Resources::ClearImages(){
    std::vector<std::string> keys;
    for(auto iterator = imageTable.begin(); iterator != imageTable.end(); ++iterator){
        keys.push_back(iterator->first);
    }

    for(int i = 0; i < keys.size(); ++i){
        std::cout << keys.at(i) << " tem " << imageTable[keys.at(i)].use_count() << " usos" << std::endl;
        if(imageTable[keys.at(i)].use_count() == 1){
            imageTable.erase(keys.at(i));
            std::cout << "Deletado" << std::endl;
        }
    }

    keys.clear();
}


std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
    if (musicTable.find(file) == musicTable.end()){
        Mix_Music* music = Mix_LoadMUS(file.c_str());

        if (music == nullptr){
            WriteErrorinFile(102);
        }

        musicTable.emplace(file, std::shared_ptr<Mix_Music>(music, [](Mix_Music* msc){ Mix_FreeMusic(msc); }));
    }
    return musicTable[file];
}

void Resources::ClearMusics(){
    std::vector<std::string> keys;
    for(auto iterator = musicTable.begin(); iterator != musicTable.end(); ++iterator){
        keys.push_back(iterator->first);
    }

    for(int i = 0; i < keys.size(); ++i){
        std::cout << keys.at(i) << " tem " << musicTable[keys.at(i)].use_count() << " usos" << std::endl;
        if(musicTable[keys.at(i)].use_count() == 1){
            musicTable.erase(keys.at(i));
            std::cout << "Deletado" << std::endl;
        }
    }

    keys.clear();
}


std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
    if (soundTable.find(file) == soundTable.end()){
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

        if (chunk == nullptr){
            WriteErrorinFile(103);
        }
        soundTable.emplace(file, std::shared_ptr<Mix_Chunk>(chunk, [](Mix_Chunk* chk){ Mix_FreeChunk(chk); }));
    }
    return soundTable[file];
}

void Resources::ClearSounds(){
    std::vector<std::string> keys;
    for(auto iterator = soundTable.begin(); iterator != soundTable.end(); ++iterator){
        keys.push_back(iterator->first);
    }

    for(int i = 0; i < keys.size(); ++i){
        std::cout << keys.at(i) << " tem " << soundTable[keys.at(i)].use_count() << " usos" << std::endl;
        if(soundTable[keys.at(i)].use_count() == 1){
            soundTable.erase(keys.at(i));
            std::cout << "Deletado" << std::endl;
        }
    }

    keys.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size){
    std::string fullName = file + std::to_string(size);

    if (fontTable.find(fullName) == fontTable.end()){
        TTF_Font* font = TTF_OpenFont(file.c_str(), size);

        if (font == nullptr){
            WriteErrorinFile(104);
        }

        fontTable.emplace(fullName, std::shared_ptr<TTF_Font>(font, [](TTF_Font* fnt){ TTF_CloseFont(fnt); }));
    }
    return fontTable[fullName];
}

void Resources::ClearFonts(){
    std::vector<std::string> keys;
    for(auto iterator = fontTable.begin(); iterator != fontTable.end(); ++iterator){
        keys.push_back(iterator->first);
    }

    for(int i = 0; i < keys.size(); ++i){
        std::cout << keys.at(i) << " tem " << fontTable[keys.at(i)].use_count() << " usos" << std::endl;
        if(fontTable[keys.at(i)].use_count() == 1){
            fontTable.erase(keys.at(i));
            std::cout << "Deletado" << std::endl;
        }
    }

    keys.clear();
}

