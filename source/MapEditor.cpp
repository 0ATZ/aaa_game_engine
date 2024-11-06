#include "MapEditor.h"
#include "GameWindow.h"
#include <algorithm>
#include <stdio.h>
#include "BufferIO.h"

MapEditor::MapEditor(const char *const filename, TileSet *tileSet, T_UINT16 numRows, T_UINT16 numCols):
    TileMap(filename, tileSet, numRows, numCols)
{
    m_tileIndex = 0U;
    
    // // create null terminated filename string
    const size_t FILENAME_LENGTH = std::min(strlen(filename), (MAX_FILENAME_LENGTH - (size_t)1U));
    (void) memset(m_filename, 0, sizeof(m_filename));
    (void) memcpy(m_filename, filename, FILENAME_LENGTH);
}

MapEditor::~MapEditor()
{
    delete[] m_filename;
}

void MapEditor::update(T_UINT64 dtime)
{
    // TODO: put this logic into GameWindow (KeyReleases, KeyPresses, KeyState)
    // XOR detects change between prev and current
    //    AND (NOT current) masks out key presses, leaving key releases
    // p ^ c & ~c
    // 0 ^ 1 &  0 = 0
    // 1 ^ 1 &  0 = 0
    // 1 ^ 0 &  1 = 1

    T_UINT16 keyReleases = GameWindow::get_key_releases();

    if (keyReleases & GameWindow::UP)
    {
        m_tileIndex = (m_tileIndex + 1) % m_tileSet->getNumSprites();
    }
    if (keyReleases & GameWindow::DOWN)
    {
        // TODO: why overflow cause bad index lol?
        if (m_tileIndex > 0)
        {
            m_tileIndex = (m_tileIndex - 1) % m_tileSet->getNumSprites();
        }
        else
        {
            m_tileIndex = m_tileSet->getNumSprites() - 1;
        }
    }
    if (keyReleases & GameWindow::LEFT)
    {
        if (saveMapFile())
        {
            printf("saved tilemap to: %s\n", m_filename);
        }
        else
        {
            printf("ERROR: tilemap save failed: %s\n", m_filename);
        }
    }
}

void MapEditor::render()
{   
    // render the actual tilemap
    TileMap::render();

    // Render a cursor with the selected tile 
    GameWindow::render_sprite(
        m_tileSet->getSpriteByID(m_tileIndex), 
        Vector2::add(GameWindow::get_mouse_position(), m_scaledTileSize), 
        m_scaledTileSize
    );
}

t_vector MapEditor::getRowCol(t_point point)
{
    // figure out which tile was clicked 
    t_vector row_col = {-1, -1}; 
    if (intersects(point))
    {
        if (m_scaledTileSize.x > 0L && m_scaledTileSize.y > 0L)
        {
            // round down using integer division
            row_col = {
                point.x / m_scaledTileSize.x,
                point.y / m_scaledTileSize.y,
            };
        }
    }
    return row_col;
}

bool MapEditor::saveMapFile()
{
    T_UINT16 bytes_written = BufferIO::writeBuffer(m_filename, m_tileMap, m_numTiles, 1);
    return (bytes_written > 0);
}

void MapEditor::vOnClick()
{
    t_vector row_col = getRowCol(GameWindow::get_ingame_mouse_position());
    TileMap::setTileID((T_UINT16) row_col.y, (T_UINT16) row_col.x, m_tileIndex);
    // printf("clicked (%d, %d)!\n", m_cursorPosition.x, m_cursorPosition.y);
    // printf("pos (%d, %d)!\n", m_position.x, m_position.y);
}
