#include "View.h"

View::View() {
    x_position = 0;
    y_position = 0;
    z_position = 1;

    xWinPos = 1;
    yWinPos = 1;

    m_border.texture = '#';
    m_border.fg = Colors::black;
    m_border.bg = Colors::gold;

    isClearNeeded = false;

}

View::~View() {

}

void View::Render(Map* map) {

    // Checking for valid deepth value and fixing if invalid
    int maxDepth = (int)map->size() - 1;
    if (z_position > maxDepth)
        z_position = maxDepth;
    else if (z_position < 0)
        z_position = 0;

    //getting view size adjusted for zoom value
    int adjusted_height = (int) std::floor(VIEW_HEIGHT * zoom);
    int adjusted_width = (int) std::floor(VIEW_WIDTH * zoom);

    //////////////////////////
    // Render Camera Border //
    //////////////////////////

    std::string renderBuffer = "";
    std::string borderfg = Entity::GetColor(true, m_border);
    std::string borderbg = Entity::GetColor(false, m_border);
    std::string borderString = m_border.texture;

    for (int y = -1; y <= adjusted_height; y++) {
        std::string borderBuffer = borderfg + borderbg;
        if (y == -1 || y == adjusted_height) {
            for (int x = -1; x <= adjusted_width; x++)
                borderBuffer += m_border.texture;
            Consoles::DrawToScreen(xWinPos - 1, yWinPos + y, borderBuffer);
        }
        else {
            Consoles::DrawToScreen(xWinPos - 1, yWinPos + y, borderString);
            Consoles::DrawToScreen(xWinPos + adjusted_width, yWinPos + y, borderString);
        }
    }

    /////////////////////////
    // Render Camera Image //
    /////////////////////////
    for (int y = 0; y < adjusted_height; y++) {
        for (int x = 0; x < adjusted_width ; x++) {

            int targetypos = y + y_position;
            int targetxpos = x + x_position;
            
            
            if (targetypos >= map->at(z_position).size() || targetypos < 0
                || targetxpos >= map->at(z_position).at(targetypos).size() || targetxpos < 0) {
                renderBuffer +="\x1b[0m ";
                continue;
            }
            
            std::vector<Entity*>* targetList = &map->at(z_position).at(targetypos).at(targetxpos);
            
            for (auto each : (*targetList) | std::ranges::views::reverse) {
                if (each->GetisVisable()) {
                    renderBuffer += each->GetFg();
                    renderBuffer += each->GetBg();
                    renderBuffer += each->GetTexture();
                    break;
                }
            }
        }
        renderBuffer += "\x1b[0m\n";
        Consoles::DrawToScreen(xWinPos, yWinPos + y, renderBuffer);
        renderBuffer = "";
    }
}

void View::Render() {

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
    if (zoom > 0) {
        this->zoom = zoom;
        ClearNeeded();
    }
}

void View::SetisClearNeeded(bool isClearNeeded) {
    renderMutex.lock();
    this->isClearNeeded = isClearNeeded;
    renderMutex.unlock();
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

const bool View::GetisClearNeeded() {
    return isClearNeeded;
}

void View::Move(int x, int y, int z) {
    SetxPosition(x_position + x);
    SetyPosition(y_position + y);
    SetzPosition(z_position + z);
}

void View::MoveWindow(int x, int y) {

    if (xWinPos + x >= 1) 
        xWinPos += x;
    if (yWinPos + y >= 1)
        yWinPos += y;
    ClearNeeded();
}

void View::ClearNeeded() {
    if (!isClearNeeded) {
        renderMutex.lock();
        isClearNeeded = true;
        renderMutex.unlock();
    }
}