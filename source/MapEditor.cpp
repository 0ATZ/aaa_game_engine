#include "MapEditor.h"
#include "GameWindow.h"
#include <stdio.h>

MapEditor::MapEditor(const char *const filename, TileSet *tileSet, T_UINT16 numRows, T_UINT16 numCols):
    TileMap(filename, tileSet, numRows, numCols)
{
    m_cursorPosition = GameWindow::get_mouse_position();
    m_tileIndex = 0U; 
}

void MapEditor::update(T_UINT64 dtime)
{
    m_cursorPosition = GameWindow::get_mouse_position();
}

void MapEditor::render()
{   
    // render the actual tilemap
    TileMap::render();

    // Render a cursor with the selected tile 
    GameWindow::render_sprite(
        m_tileSet->getSpriteByID(m_tileIndex), 
        Vector2::add(m_cursorPosition, m_scaledTileSize), 
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
    t_vector row_col = getRowCol(m_cursorPosition); 
    printf("clicked (%d, %d)!\n", row_col.x, row_col.y);
}
