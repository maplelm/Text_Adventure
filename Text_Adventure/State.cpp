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


void State::CellAuto2d(Entity * target, Entity * blank, int layer, int r) {

    //Do not run if given map is empty!
    if (m_map.size() == 0) {
        return;
    }

    // size of target map layer
    int mapLayerHeight = (int) m_map[layer].size();
    int mapLayerWidth = (int) m_map[layer][0].size();

    // Keeps track of changes to be made to target layer after algorithm runs
    std::vector<std::vector<std::vector<int>>> changesToMapMatrix;

    
    /* Adjusting copyLayer to be the same size as m_map[layer] 
    ************************************************************/
    changesToMapMatrix.resize(mapLayerHeight);
    for (int eachRow = 0; eachRow < mapLayerHeight; eachRow++) {
        //Resize each row to the correct width
        changesToMapMatrix[eachRow].resize(mapLayerWidth);
    }
    /*************************************************************/


    // repeats the process for secified number of times 
    for(int rounds = 0; rounds < r; rounds++) {

        //Process each cell in the layer
        for(int layerRow = 0; layerRow < mapLayerHeight; layerRow++) {
            for (int layerCol = 0; layerCol < mapLayerWidth; layerCol++) {
                
                //Keeps track of how many neighboring cells have the same entity in it
                int neighbors = 0;

                //Itrating through all neighboring cells
                for (int localRow = -1; localRow < 2; localRow++ ) {
                    for (int localCol = -1; localCol < 2; localCol++) {
                        int checkRow = layerRow + localRow;
                        int checkCol = layerCol + localCol;

                        // if neighbor does not exist or if neighbor is self skip check
                        if(checkRow < 0 || checkRow >= m_map[layer].size() ||
                           checkCol < 0 || checkCol >= mapLayerWidth ||
                           (localRow == 0 && localCol == 0))
                            continue;

                        for (auto eachEntity : m_map[layer][checkRow][checkCol]) {
                            if (eachEntity->GetId() == target->GetId()) {
                                neighbors++;
                                break;
                            }
                        }
                    }
                }
                // if less then 2 neibhbors or greater then 4 cell dies
                if (neighbors > 1 && neighbors <= 4)
                    changesToMapMatrix[layerRow][layerCol].push_back(1);
            }
        }

        // replacing all layer state with new layer state
        for (int y = 0; y < m_map[layer].size(); y++) {
            for (int x = 0; x < m_map[layer][y].size(); x++) {
                for (auto itr = m_map[layer][y][x].begin(); itr != m_map[layer][y][x].end(); itr++) {
                    if ((*itr)->GetId() == target->GetId()) {
                        if (changesToMapMatrix[y][x].empty()) {
                            delete *itr;
                            itr = m_map[layer][y][x].erase(itr);
                            itr = m_map[layer][y][x].insert(itr, new Entity(*blank));
                        }
                    }
                    else if ((*itr)->GetId() == blank->GetId()) {
                        if (!changesToMapMatrix[y][x].empty()) {
                            delete *itr;
                            itr = m_map[layer][y][x].erase(itr);
                            itr = m_map[layer][y][x].insert(itr, new Entity(*target)); 
                        }
                    }
                }
            }
        }
    }

    //Freeing passed in objects as function expects them to be allocted on the heap from a pointer
    if (target != nullptr)
        delete target;
    if (blank != nullptr)
        delete blank;
}

void State::CellAuto3d(Entity * target, Entity * blank,int CLayer, int r) {

}


State::State() {
    m_isRunning = true;
    m_groundLevel = 1;
    playerPos = { 0 };
}

State::State(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed) {
    
    //Making sure the state does not shutdown as it starts up
    m_isRunning = true;
    playerPos = { 0 };
    m_groundLevel = 1;

    //Init map
    YAxis yLayer;
    XAxis xLayer;
    ItemList iListLayer;
    
    //checking for valid height,width,depth
    if (depth <= 0)
        depth = 1;
    if (height <= 0)
        height = 1;
    if (width <= 0)
        width = 1;

    for (unsigned int z = 0; z < depth; z++) {
        m_map.push_back(yLayer);
        for (unsigned int y = 0; y < height; y++) {
            m_map[z].push_back(xLayer);
            for (unsigned int x = 0; x < width; x++) {
                m_map[z][y].push_back(iListLayer);
                if (z < m_groundLevel)
                    // adding air entities
                    m_map[z][y][x].push_back(AIR_ENTITY);
                if (z == m_groundLevel)
                    // adding grass
                    m_map[z][y][x].push_back(GRASS_ENTITY);
                if (z > m_groundLevel)
                    // adding dirt
                    m_map[z][y][x].push_back(DIRT_ENTITY);
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
    
    for (auto each : m_map[playerPos.z + z][playerPos.y + y][playerPos.x  + x]) {
        if (!each->GetisPassable())
            break;
        for (auto itr = m_map[playerPos.z][playerPos.y][playerPos.x].begin(); itr <= m_map[playerPos.z][playerPos.y][playerPos.x].end(); ++itr) {
            Player* playerPtr = dynamic_cast<Player*>(*itr);
            if (playerPtr) {
                m_map[playerPos.z + z][playerPos.y + y][playerPos.x + x].push_back(*itr);
                m_map[playerPos.z][playerPos.y][playerPos.x].erase(itr);
                playerPos.x += x;
                playerPos.y += y;
                playerPos.z += z;
                return true;
            }
        }
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

void State::AudioThread() {

}

View* State::GetCameraHandle() {
    return &m_camera;
}