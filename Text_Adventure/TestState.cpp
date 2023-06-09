#include "TestState.h"

TestState::TestState(unsigned int height, unsigned int width, unsigned int depth, unsigned int seed) {

	//Local Variable declearation
	unsigned int gl = 1; // ground level
	float treeGrassRatio = .55f;

	//Init random number generator
	if (seed == 0)
		std::srand((unsigned)std::time(NULL));
	else
		std::srand(seed);

	//Init Terrain entities
	AIR_ENTITY;
	GRASS_ENTITY;
	DIRT_ENTITY;
	Entity silt('#', Colors::silver, Colors::brown, false, true, nullptr);
	Entity tree('T', Colors::green, Colors::brown, false, true, nullptr);

	//Filling each tile space with a base entity
	InitMap(width, height, depth);

	for (unsigned int z = 0; z < m_map.size(); z++) {
		for (unsigned int y = 0; y < m_map[z].size(); y++) {
			for (unsigned int x = 0; x < m_map[z][y].size(); x++) {
				if (z < gl) {
					m_map[z][y][x].push(air);
				}
				else if (z == gl) {
					if ((float)std::rand() / RAND_MAX > treeGrassRatio)
						m_map[z][y][x].push(grass);
					else
						m_map[z][y][x].push(tree);
				}
				else {
					if ((float)std::rand() / RAND_MAX > 0.5f)
						m_map[z][y][x].push(dirt);
					else
						m_map[z][y][x].push(silt);
				}
			}
		}
	}

	//Using Celluar Automata on trees
	CellAuto2d(tree, grass, gl, 2);

}

TestState::~TestState() {

}

void TestState::Update() {

	char input = _getch();

	if (input == 'c')
		m_isRunning = false;
	if (input == 'w')
		m_camera.Move(0, -1);
	if (input == 's')
		m_camera.Move(0, 1);
	if (input == 'a')
		m_camera.Move(-1, 0);
	if (input == 'd')
		m_camera.Move(1, 0);
	if (input == 'q')
		m_camera.Move(0, 0, 1);
	if (input == 'e')
		m_camera.Move(0, 0, -1);
	if (input == '[')
		m_camera.SetZoom(m_camera.GetZoom() - 0.1f);
	if (input == ']')
		m_camera.SetZoom(m_camera.GetZoom() + 0.1f);
}

void TestState::UserInput() {

}
