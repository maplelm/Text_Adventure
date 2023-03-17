#include "State.h" 


void State::InitMap(int width, int height, int depth) {

    //Init Temp map elements to fill map vectors with
    YAxis yLayer;
    XAxis xLayer;
    ItemList iListLayer;


    for (int z = 0; z < depth; z++) {
        m_map.push_back(yLayer);
        for (int y = 0; y < height; y++) {
            m_map.at(z).push_back(xLayer);
            for (int x = 0; x < width; x++) {
                m_map.at(z).at(y).push_back(iListLayer);
            }
        }
    }
}


void State::CellAuto2d(Entity target, Entity blank, unsigned int layer, unsigned int r) {

    if (m_map.size() == 0) {
        return; 
    }
    YAxis copyLayer;
    copyLayer.resize(m_map[layer].size());
    for (auto y = 0; y < m_map[layer].size(); y++) {
        copyLayer[y].resize(m_map[layer][y].size());
        for (auto x = 0; x < m_map[layer][y].size(); x++) {
            copyLayer[y][x] = m_map[layer][y][x];
        }
    }
    copyLayer = m_map[layer];
    char targetTexture = target.GetTexture();
    char altTexture = blank.GetTexture();

    for (unsigned int rounds = 0; rounds < r; rounds++) {

        for (int y = 0; y < m_map[layer].size(); y++) {
            for (int x = 0; x < m_map[layer][y].size(); x++) {

                int neighbors = 0;

                for (int row = -1; row < 2; row++) {
                    for (int col = -1; col < 2; col++) {
                        int xtarget = col + x;
                        int ytarget = row + y;
                        if (ytarget < 0 || ytarget >= m_map[layer].size() ||
                            xtarget < 0 || xtarget >= m_map[layer][y].size())
                            continue;

                        if (m_map[layer][ytarget][xtarget].top().GetTexture() == targetTexture)
                            neighbors++;
                    }
                }

                if (neighbors <= 1 || neighbors > 4) {
                    copyLayer[y][x].pop();
                    copyLayer[y][x].push(blank);
                }
                else {
                    copyLayer[y][x].pop();
                    copyLayer[y][x].push(target);
                }

            }
        }
        m_map[layer] = copyLayer;

    }
}

void State::CellAuto3d(Entity target, Entity blank, unsigned int CLayer, unsigned int r) {

}


State::State() {
    m_isRunning = true;
}

State::State(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed) {
    
    //Making sure the state does not shutdown as it starts up
    m_isRunning = true;

    //Init map
    YAxis yLayer;
    XAxis xLayer;
    ItemList iListLayer;
    //Entity    air(' ', Colors::blue,  Colors::blue,  true,  true, nullptr);
    AIR_ENTITY;
    GRASS_ENTITY;
    DIRT_ENTITY;
    
    
    //checking for valid height,width,depth
    if (depth == 0)
        depth = 1;
    if (height == 0)
        height = 1;
    if (width == 0)
        width = 1;

    for (unsigned int z = 0; z < depth; z++) {
        m_map.push_back(yLayer);
        for (unsigned int y = 0; y < height; y++) {
            m_map[z].push_back(xLayer);
            for (unsigned int x = 0; x < width; x++) {
                m_map[z][y].push_back(iListLayer);
                if (z < 9)
                    m_map[z][y][x].push(air);
                if (z == 9)
                    m_map[z][y][x].push(grass);
                if (z > 9)
                    m_map[z][y][x].push(dirt);
            }
        }
    }

}

State::~State() {

}

void State::Render(bool fullMap) {
    if (!fullMap) {
        m_camera.Render(&m_map);
        return;
    }
    /*
    std::string renderRow = "";
    for (int i = 0; i < m_map.size(); i++) {
        for (int j = 0; j < m_map[i].size(); j++) {
            renderRow += m_map[i][j].GetModel();
        }
        renderRow += "\n";
    }
    std::cout << renderRow;
    */
}

void State::AddEntityToTile(unsigned int x, unsigned int y, unsigned int z, Entity entity) {
    if (z >= 0 && y >= 0 && x >= 0 &&
        z < m_map.size() && y < m_map[z].size() && x < m_map[z][y].size()) {
        m_map[z][y][x].push(entity);
    }
}

const bool State::IsOpen() {
    return m_isRunning;
}
