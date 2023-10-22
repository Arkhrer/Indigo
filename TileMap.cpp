#include <fstream>
#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated){
    this->tileSet = tileSet;
    Load(file);
}

void TileMap::Load(std::string file){
    std::ifstream map(file);

    if (map.is_open()){
        std::string str;

        std::getline(map,str,',');
        mapWidth = std::stoi(str);

        std::getline(map,str,',');
        mapHeight = std::stoi(str);

        std::getline(map,str,',');
        mapDepth = std::stoi(str);

        for (int k = 0; k < mapDepth; ++k){
            for (int i = 0; i < mapHeight; ++i){
                for (int j = 0; j < mapWidth; ++j){
                    std::getline(map,str,',');
                    tileMatrix.push_back(std::stoi(str) - 1);
                }
            }
        }
    }
}

void TileMap::SetTileSet(TileSet* tileSet){
    delete this->tileSet;
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
    return tileMatrix[z * (mapWidth * mapHeight) + y * mapWidth + x];
}

void TileMap::Render(){
    for (int i = 0; i < mapDepth; ++i){
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
    float paralaxX = 0.3 * layer * cameraX;
    float paralaxY = 0.3 * layer * cameraY;

    for (int i = 0; i < mapHeight; ++i){
        for (int j = 0; j < mapWidth; ++j){
            tileSet->RenderTile(tileMatrix[layer * (mapWidth * mapHeight) + i * mapWidth + j], tileSet->GetTileWidth() * j - paralaxX, tileSet->GetTileHeight() * i - paralaxY);
        }
    }
}

int TileMap::GetWidth(){
    return mapWidth;
}

int TileMap::GetHeight(){
    return mapHeight;
}

int TileMap::GetDepth(){
    return mapDepth;
}

void TileMap::Update(float dt){

}
bool TileMap::Is(std::string type){
    if (type.compare("TileMap") == 0){
        return true;
    }
    else{
        return false;
    }
}
