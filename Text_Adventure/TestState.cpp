#include "TestState.h"

TestState::TestState(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed) {

	InitMap(width, height, depth);
	
	GenerateTerrain(seed);
    
	//Using Celluar Automata on trees
	CellAuto2d(TREE_ENTITY, GRASS_ENTITY, m_groundLevel, 1);

	// Place the player in a valid location on the map
	PlacePlayer();

	// Setting Main Camera to wanted position
	m_camera.MoveWindow(30, 2);
}

TestState::~TestState() {

}

void TestState::Update() {

}

void TestState::UserInput() {
	char input = Consoles::Update();

	if (input == 'c')
		m_isRunning = false;
	else if (input == 'w') {
		if (MovePlayer(0, -1))
			m_camera.Move(0, -1);
	}
	else if (input == 's') {
		if (MovePlayer(0, 1))
			m_camera.Move(0, 1);
	}
	else if (input == 'a') {
		if (MovePlayer(-1, 0))
			m_camera.Move(-1, 0);
	}
	else if (input == 'd') {
		if (MovePlayer(1, 0))
			m_camera.Move(1, 0);
	}
	else if (input == 'W')
		m_camera.MoveWindow(0, -1);
	else if (input == 'S')
		m_camera.MoveWindow(0, 1);
	else if (input == 'A')
		m_camera.MoveWindow(-1, 0);
	else if (input == 'D')
		m_camera.MoveWindow(1, 0);
	else if (input == 'q')
		m_camera.Move(0, 0, 1);
	else if (input == 'e')
		m_camera.Move(0, 0, -1);
	else if (input == '[')
		m_camera.SetZoom(m_camera.GetZoom() - 0.1f);
	else if (input == ']')
		m_camera.SetZoom(m_camera.GetZoom() + 0.1f);
}

void TestState::PlacePlayer() {

	bool playerPlaced = false;
	while (!playerPlaced) {
		float ySelect = (float)std::rand() / (float)RAND_MAX;
		int yPlayerStart = (int)std::floor((m_map[m_groundLevel].size() - 1) * ySelect);
		float xSelect = (float)std::rand() / (float)RAND_MAX;
		int xPlayerStart = (int)std::floor((m_map[m_groundLevel][yPlayerStart].size() - 1) * xSelect);

		bool canPass = true;
		for (auto eachEntity : m_map[m_groundLevel][yPlayerStart][xPlayerStart]) {
			if (!eachEntity->GetisPassable()) {
				canPass = false;
				break;
			}
		}
		if (!canPass)
			continue;
		Player* newPlayer = new Player('@', Colors::white, Colors::black);
		m_map[m_groundLevel][yPlayerStart][xPlayerStart].push_back(newPlayer);
		playerPos.x = xPlayerStart;
		playerPos.y = yPlayerStart;
		playerPos.z = m_groundLevel;

		m_camera.SetyPosition(yPlayerStart - (int)std::floor((float)VIEW_HEIGHT / 2.f));
		m_camera.SetxPosition(xPlayerStart - (int)std::floor((float)VIEW_WIDTH / 2.f));

		playerPlaced = true;

	}

}

void TestState::GenerateTerrain(unsigned int seed) {

	//Local Variable declearation
	float treeGrassRatio = .61f;

	//Init random number generator
	if (seed > 0)
		std::srand(seed);
	else
		std::srand((unsigned)std::time(NULL));

	// GENERATING THE MAP //
	for (unsigned int z = 0; z < m_map.size(); z++) {
		for (unsigned int y = 0; y < m_map[z].size(); y++) {
			for (unsigned int x = 0; x < m_map[z][y].size(); x++) {
				if (z < m_groundLevel) {
					m_map[z][y][x].push_back(AIR_ENTITY);
				}
				else if (z == m_groundLevel) {
					if ((float)std::rand() / (float)RAND_MAX > treeGrassRatio)
						m_map[z][y][x].push_back(GRASS_ENTITY);
					else {
						m_map[z][y][x].push_back(GRASS_ENTITY);
						m_map[z][y][x].push_back(TREE_ENTITY);
					}
				}
				else {
					if ((float)std::rand() / (float)RAND_MAX > 0.5f)
						m_map[z][y][x].push_back(DIRT_ENTITY);
					else
						m_map[z][y][x].push_back(SILT_ENTITY);
				}
			}
		}
	}
}