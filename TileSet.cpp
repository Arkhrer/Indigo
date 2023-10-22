#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file): tileSet(gameObject){
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    tileSet.Open(file);

    if (tileSet.IsOpen()){
        rows = tileSet.GetHeight() / tileHeight;
        columns = tileSet.GetWidth() / tileWidth;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y){
    if(index >= 0 && index < rows * columns){

        tileSet.SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth(){
    return tileWidth;
}

int TileSet::GetTileHeight(){
    return tileHeight;
}
