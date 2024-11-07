#include "MapEditor.h"
#include "GameWindow.h"
#include <algorithm>
#include <stdio.h>
#include "BufferIO.h"

MapEditor::MapEditor(const char *const filename, TileSet *tileSet, T_UINT16 numRows, T_UINT16 numCols):
    TileMap(filename, tileSet, numRows, numCols)
{
    m_menuIndex = 0U;
    m_tileIndex = 0U;
    
    // create null terminated filename string
    const size_t FILENAME_LENGTH = std::min(strlen(filename), (MAX_FILENAME_LENGTH - (size_t)1U));
    (void) memset(m_filename, 0, sizeof(m_filename));
    (void) memcpy(m_filename, filename, FILENAME_LENGTH);

    m_borderSprite = new Sprite("./assets/sprites/green_16x16.bin", 16,16);
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

    T_UINT32 keyPresses = GameWindow::get_key_presses();

    // press right to increment index
    if (keyPresses & GameWindow::RIGHT)
    {
        m_menuIndex = (m_menuIndex + 1) % m_tileSet->getNumSprites();
    }

    // press LEFT to decrement index
    if (keyPresses & GameWindow::LEFT)
    {
        if (m_menuIndex > 0)
        {
            m_menuIndex = m_menuIndex - 1;
        }
        else
        {
            m_menuIndex = m_tileSet->getNumSprites() - 1;
        }
    }

    if (keyPresses & GameWindow::UP)
    {
        if (m_menuIndex >= 9)
        {
            m_menuIndex -= 9;
            m_menuIndex %= m_tileSet->getNumSprites();
        }
        else
        {
            m_menuIndex = m_tileSet->getNumSprites() - 9;
        }
        // printf("m_menuIndex: %d\n", m_menuIndex);
    }

    if (keyPresses & GameWindow::DOWN)
    {
        m_menuIndex += 9;
        m_menuIndex %= m_tileSet->getNumSprites();
        // printf("m_menuIndex: %d\n", m_menuIndex);
    }

    if (keyPresses & GameWindow::NUM1)
    {
        m_tileIndex = 0;
    }
    else if (keyPresses & GameWindow::NUM2)
    {
        m_tileIndex = 1;
    }
    else if (keyPresses & GameWindow::NUM3)
    {
        m_tileIndex = 2;
    }
    else if (keyPresses & GameWindow::NUM4)
    {
        m_tileIndex = 3;
    }
    else if (keyPresses & GameWindow::NUM5)
    {
        m_tileIndex = 4;
    }
    else if (keyPresses & GameWindow::NUM6)
    {
        m_tileIndex = 5;
    }
    else if (keyPresses & GameWindow::NUM7)
    {
        m_tileIndex = 6;
    }
    else if (keyPresses & GameWindow::NUM8)
    {
        m_tileIndex = 7;
    }
    else if (keyPresses & GameWindow::NUM9)
    {
        m_tileIndex = 8;
    }
    m_tileIndex %= m_tileSet->getNumSprites();

    // press zero to save
    if (keyPresses & GameWindow::NUM0)
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

    t_point borderPos = {
        150 + (m_tileIndex * 40) + (m_tileIndex * 16) - 8,
        540 - 8
    };

    // Render a border around the selected sprite 
    GameWindow::render_sprite(
        m_borderSprite, 
        borderPos, 
        Vector2::add(m_scaledTileSize, {16,16})
    );

    // render sprites corresponding to numkey selection 1-9
    for (int i = 0; i < 9; i ++)
    {
        // TODO: dynamic screen ratio 
        int index = (m_menuIndex + i) % m_tileSet->getNumSprites();
        int xpos = 150 + (i * 40) + (i * 16);

        // Render a cursor with the selected tile 
        GameWindow::render_sprite(
            m_tileSet->getSpriteByID(index), 
            {xpos, 540}, 
            m_scaledTileSize
        );

    }

    // Render a cursor with the selected tile 
    GameWindow::render_sprite(
        m_tileSet->getSpriteByID(m_tileIndex + m_menuIndex), 
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
    TileMap::setTileID((T_UINT16) row_col.y, (T_UINT16) row_col.x, m_tileIndex + m_menuIndex);
    // printf("clicked (%d, %d)!\n", m_cursorPosition.x, m_cursorPosition.y);
    // printf("pos (%d, %d)!\n", m_position.x, m_position.y);
}
