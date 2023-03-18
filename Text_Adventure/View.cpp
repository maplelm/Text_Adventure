#include "View.h"

View::View() {
    x_position = 0;
    y_position = 0;
    z_position = 1;

    xWinPos = 1;
    yWinPos = 1;
}

View::~View() {

}

void View::Render(Map * map) {

    int maxDepth = (int)map->size() - 1;
    

    

    if (z_position > maxDepth)
        z_position = maxDepth;
    else if (z_position < 0)
        z_position = 0;

    std::string renderRow = "";
    for (int y = 0; y < VIEW_HEIGHT * zoom  ; y++) {
        for (int x = 0; x < VIEW_WIDTH * zoom; x++) {

            int targetypos = y + y_position;
            int targetxpos = x + x_position;
            
            if (targetypos >= map->at(z_position).size() || targetypos < 0
                || targetxpos >= map->at(z_position).at(targetypos).size() || targetxpos < 0) {
                renderRow += "\x1b[0m ";
            }
            else {
                // adding foreground color to entity
                renderRow += map->at(z_position).at(targetypos).at(targetxpos).back().GetFg();
                // adding background color to entity
                renderRow += map->at(z_position).at(targetypos).at(x + x_position).back().GetBg();
                // Adding entity model to renderRow
                renderRow += map->at(z_position).at(targetypos).at(x + x_position).back().GetTexture();
            }
        }
        renderRow += "\x1b[0m\n";
        Consoles::DrawToScreen(xWinPos, yWinPos + y, renderRow);
        renderRow = "";
    }
    //std::cout << "\x1b[?1049l";
    //std::cout << renderRow;
    //std::cout << "\x1b[?1049h";

}


void View::SetxPosition(int x) {
    x_position = x;
}

void View::SetyPosition(int y) {
    y_position = y;
}

void View::SetzPosition(int z) {
    z_position = z;
}

void View::SetZoom(float zoom) {
    if (zoom > 0)
        this->zoom = zoom;
}

const int View::GetxPosition() {
    return x_position;
}

const int View::GetyPosition() {
    return y_position;
}

const int View::GetzPosition() {
    return z_position;
}

const unsigned int View::GetxWindowPos() {
    return xWinPos;
}

const unsigned int View::GetyWindowPos() {
    return yWinPos;
}

const float View::GetZoom() {
    return zoom;
}

void View::Move(int x, int y, int z) {
    SetxPosition(x_position + x);
    SetyPosition(y_position + y);
    SetzPosition(z_position + z);
}

void View::MoveWindow(int x, int y) {

    if (xWinPos + x >= 0) 
        xWinPos += x;
    if (yWinPos + y >= 0)
        yWinPos += y;
}
