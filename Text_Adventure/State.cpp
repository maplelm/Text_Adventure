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

    // Getting the size of the layer so we don't have to call the functions everytime, its a waste of time
    int layerHeight = (int) m_map[layer].size();
    int layerWidth = (int) m_map[layer][0].size();

    //Exiting if map is empty
    if (m_map.size() == 0) {
        return; 
    }

    // Used to store new version of layer while it is being created;
    YAxis copyLayer;

    /////////////////////////////////////////////////////////////
    // Adjusting copyLayer to be the same size as m_map[layer] //
    /////////////////////////////////////////////////////////////
    copyLayer.resize(layerHeight);
    for (int eachRow = 0; eachRow < layerHeight; eachRow++) {
        //Sizing row to the same length as it is in the original array
        copyLayer[eachRow].resize(layerWidth);
        for (int eachCol = 0; eachCol < layerWidth; eachCol++) {
            copyLayer[eachRow][eachCol].shrink_to_fit();
        }
    }
    /////////////////////////////////////////////////////////////////////


    // repeats the process for secified number of times 
    for(int rounds = 0; rounds < r; rounds++) {

        //Process each cell in the layer
        for(int row = 0; row < layerHeight; row++) {
            for (int col = 0; col < layerWidth; col++) {
                
                // reset the neibhbors value for the next cell
                int neighbors = 0;

                //Check neighbors cells for each cell in the layer
                for (int localRow = -1; localRow < 2; localRow++ ) {
                    for (int localCol = -1; localCol < 2; localCol++) {
                        int checkRow = row + localRow;
                        int checkCol = col + localCol;

                        // if neighbor does not exist or if neighbor is self skip check
                        if(checkRow < 0 || checkRow >= m_map[layer].size() ||
                           checkCol < 0 || checkCol >= layerWidth ||
                           (localRow == 0 && localCol == 0))
                            continue;

                        if (m_map[layer][checkRow][checkCol].back()->GetTexture() == target->GetTexture())
                            neighbors++;
                    }
                }


                // if less then 2 neibhbors or greater then 4 cell dies
                if (neighbors <= 1 || neighbors > 4)
                    copyLayer[row][col].push_back( new Entity(*blank));
                else
                    copyLayer[row][col].push_back( new Entity(*target));
            }
        }

        // replacing all layer state with new layer state
        m_map[layer].swap(copyLayer);

        // deleting old allocated memory
        for(int row = 0; row < copyLayer.size(); row++)
            for (int col = 0; col < copyLayer[row].size(); col++) {
                delete copyLayer[row][col].back();
                copyLayer[row][col].pop_back();
        }
    }

}

void State::CellAuto3d(Entity * target, Entity * blank,int CLayer, int r) {

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

    bool passable = true;
    
    for (auto each : m_map[playerPos.z + z][playerPos.y + y][playerPos.x  + x]) {
        if (!each->GetisPassable()) {
            passable = false;
        }
    }
    if (passable) {
        for (auto itr = m_map[playerPos.z][playerPos.y][playerPos.x].begin(); itr <= m_map[playerPos.z][playerPos.y][playerPos.x].end(); ++itr) {
            Player * playerPtr = dynamic_cast<Player*>(*itr);

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
