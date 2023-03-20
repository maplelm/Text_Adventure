#include "State.h" 


void State::InitMap(int width, int height, int depth, int groundLevel) {

    m_groundLevel = groundLevel;

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


void State::CellAuto2d(Entity * target, Entity * blank, unsigned int layer, unsigned int r) {

    struct toEdit {
        int x;
        int z;
        int z;
        char texture;
    };

    std::vector<toEdit> editList;

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
    
    char targetTexture = target->GetTexture();
    char altTexture = blank->GetTexture();

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

                        if (m_map[layer][ytarget][xtarget].back()->GetTexture() == targetTexture)
                            neighbors++;
                    }
                }

                if (neighbors <= 1 || neighbors > 4) {
                    copyLayer[y][x].pop_back();
                    copyLayer[y][x].push_back(blank);
                }
                else {
                    copyLayer[y][x].pop_back();
                    copyLayer[y][x].push_back(target);
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
    m_groundLevel = 1;
}

State::State(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed) {
    
    //Making sure the state does not shutdown as it starts up
    m_isRunning = true;

    m_groundLevel = 1;

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
                if (z < m_groundLevel)
                    // adding air entities
                    m_map[z][y][x].push_back(new Entity(' ', nullptr, Colors::blue, Colors::blue, true, true));
                if (z == m_groundLevel)
                    // adding grass
                    m_map[z][y][x].push_back(new Entity(' ', nullptr, Colors::black, Colors::green, true, true));
                if (z > m_groundLevel)
                    // adding dirt
                    m_map[z][y][x].push_back(new Entity('#', nullptr, Colors::brown, Colors::brown, false, true));
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
}

bool State::MovePlayer(int x, int y, int z) {

    // see if movement is valid
    if (playerPos.x + x < 0 || playerPos.x + x >= m_map[0][0].size())
        return false;
    if (playerPos.y + y < 0 || playerPos.y + y >= m_map[0].size())
        return false;
    if (playerPos.z + z < 0 || playerPos.z + z >= m_map.size())
        return false;

    bool passable = true;
    for (auto each : m_map[playerPos.z + z][playerPos.y + y][playerPos.x  + x])
        if (!each->GetisPassable())
            passable = false;
    if (passable) {
        for (auto itr = m_map[playerPos.z][playerPos.y][playerPos.x].begin(); itr < m_map[playerPos.z][playerPos.y][playerPos.x].end(); ++itr) {
            auto id1 = typeid(dynamic_cast<Player*>(*itr)).name();
            auto id2 = typeid(Player).name();
            if (typeid(*itr).name() == typeid(Player).name()) {
                m_map[playerPos.z + z][playerPos.y + y][playerPos.x + x].push_back(*itr);
                m_map[playerPos.z][playerPos.y][playerPos.x].erase(itr);
            }
        }
        return true;
    }
    return false;
}

void State::AddEntityToTile(unsigned int x, unsigned int y, unsigned int z, Entity * entity) {
    if (z >= 0 && y >= 0 && x >= 0 &&
        z < m_map.size() && y < m_map[z].size() && x < m_map[z][y].size()) {
        m_map[z][y][x].push_back(entity);
    }
}

const bool State::IsOpen() {
    return m_isRunning;
}
