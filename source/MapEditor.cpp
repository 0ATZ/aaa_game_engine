#include "MapEditor.h"
#include "GameWindow.h"
#include <stdio.h>

MapEditor::MapEditor(const char *const filename, TileSet *tileSet, T_UINT16 numRows, T_UINT16 numCols):
    TileMap(filename, tileSet, numRows, numCols)
{
    m_tileIndex = 0U;
    m_pressed = false;
}

void MapEditor::update(T_UINT64 dtime)
{
    T_UINT16 playerKeys = GameWindow::get_player_keys();
    if (playerKeys & GameWindow::UP)
    {
        m_pressed = true;
    }
    else
    {
        if (m_pressed)
        {
            m_tileIndex = (m_tileIndex + 1) % m_tileSet->getNumSprites();
            m_pressed = false;
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

void MapEditor::vOnClick()
{
    t_vector row_col = getRowCol(GameWindow::get_ingame_mouse_position());
    TileMap::setTileID((T_UINT16) row_col.y, (T_UINT16) row_col.x, m_tileIndex);
    // printf("clicked (%d, %d)!\n", m_cursorPosition.x, m_cursorPosition.y);
    // printf("pos (%d, %d)!\n", m_position.x, m_position.y);
}
