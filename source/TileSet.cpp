#include "TileSet.h"
#include "GameWindow.h"
#include <iostream>

TileSet::TileSet()
{
    m_tileCount = 0U;
    (void) memset(m_tileSet, 0, sizeof(m_tileSet));
}

TileSet::TileSet(t_tileset tileSet) :
    TileSet() // call base constructor
{
    for (m_tileCount = 0U; m_tileCount < TILESET_SIZE; m_tileCount++)
    {
        if (tileSet[m_tileCount])
        {
            // create SDL texture for each tile
            (void) this->addTile(tileSet[m_tileCount]);
        }
        else
        {
            break;
        }
    }
    std::cout << "Created tileset with " << m_tileCount << " tiles." << std::endl;
}

// return the tileID 
t_index TileSet::addTile(t_tile *tilePixels)
{
    t_index L_retVal = 0xFFU; // return index 255 if failed to add
    if (this->hasSpace())
    {
        Tile * L_newTile = new Tile(tilePixels);
        if (L_newTile)
        {
            // createTexture gives the Tile sprite a textureID

            // use the current m_tileCount as the tileID 
            m_tileSet[m_tileCount] = L_newTile;
            L_retVal = m_tileCount;
            m_tileCount++;
        }
        else
        {
            std::cout << "ERROR: cannot not allocate memory for new tile." << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: tileset is full, cannot add new tile." << std::endl;
    }
    return L_retVal;
}

Tile * TileSet::getTileFromID(t_index tileID)
{
    Tile * L_tile = nullptr;
    if (isValid(tileID))
    {
        L_tile = m_tileSet[tileID];
    }
    return L_tile;
}

T_UINT16 TileSet::getTileCount()
{
    return m_tileCount;
}

// returns true if there is an available space in the texture cache
bool TileSet::hasSpace()
{
    if (m_tileCount < TILESET_SIZE)
    {
        return true;
    }
    return false;
}

// returns true if a Tile sprite has been registered to the tileID
bool TileSet::isValid(t_index tileID)
{
    if (tileID < m_tileCount)
    {
        return true;
    }
    return false;
}
