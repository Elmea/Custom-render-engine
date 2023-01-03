#include <fstream>
#include <string>
#include <chrono>

#include "Model.h"
#include "Debug.h"

using namespace Resource;

Model::Model()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	verticeCount = 0;
	indexCount = 0;
}

void Model::fillBuffers()
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Resource::Vertex) * verticeCount, vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indexCount, index.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	isInBuffer = true;
}

void Model::AddVertex(Vertex v)
{
	vertices.push_back(v);
	index.push_back(vertices.size()-1);
}

void Model::Load(const char* fileName)
{
	std::chrono::time_point start = std::chrono::steady_clock::now();

	std::ifstream file;
	char line[256];

	file.open(fileName, std::ios::in | std::ios::ate);

	if (!file.is_open())
		return;
	 
	file.seekg(0);

	int vertexUVCount = 0;
	int vertexNormalCount = 0;
	
	int globalCur = 0;

	std::vector<myMaths::Float3> positions;
	std::vector<myMaths::Float3> Normals;
	std::vector<myMaths::Float2> UVs;

	while (file.getline(line, 256))
	{
		if (line[0] == 'v')
		{
			switch (line[1])
			{
			case (' '):
			{
				int cur = 2;
				while (line[cur] == ' ')
					cur++;
				myMaths::Float3 newPos;
				std::string number;
				for (int i = 0; i < 3; i++)
				{
					while (line[cur] != ' ')
					{
						if (line[cur] == '\n' || line[cur] == '\0')
							break;
						number.push_back(line[cur]);
						cur++;
					}

					if (i == 0)
						newPos.x = std::stof(number);
					else if (i == 1)
						newPos.y = std::stof(number);
					else
						newPos.z = std::stof(number);

					number.clear();
					cur++;
				}

				positions.push_back(newPos);
				globalCur += cur;
			}
			break;

			case ('t'):
			{
				int cur = 3;
				std::string number;
				myMaths::Float2 newUV;
				for (int i = 0; i < 2; i++)
				{
					Vertex v;
					while (line[cur] != ' ')
					{
						if (line[cur] == '\n' || line[cur] == '\0')
							break;
						number.push_back(line[cur]);
						cur++;
					}

					if (i == 0)
						newUV.x = std::stof(number);
					else if (i == 1)
						newUV.y = std::stof(number);

					number.clear();
					cur++;
				}

				globalCur += cur;
				UVs.push_back(newUV);
			}
			break;

			case ('n'):
			{
				int cur = 3;
				std::string number;
				myMaths::Float3 newNormal;
				for (int i = 0; i < 3; i++)
				{
					while (line[cur] != ' ')
					{
						if (line[cur] == '\n' || line[cur] == '\0')
							break;
						number.push_back(line[cur]);
						cur++;
					}

					if (i == 0)
						newNormal.x = std::stof(number);
					else if (i == 1)
						newNormal.y = std::stof(number);
					else
						newNormal.z = std::stof(number);

					number.clear();
					cur++;
				}
				Normals.push_back(newNormal);
				globalCur += cur;
			}
			break;

			default:
				break;
			}
		}
		else if (line[0] == 'f')
		{
			int cur = 2;
			Vertex v;
			std::string number;
			for (int vertex = 0; vertex < 3; vertex++)
			{
				for (int i = 0; i < 3; i++)
				{
					while (line[cur] != '/' && line[cur] != ' ' && line[cur] != '\0')
					{
						number.push_back(line[cur]);
						cur++;
					}
					int result = std::stoi(number) - 1;

					if (i == 0)
						v.Position = positions[result];
					else if (i == 1)
						v.TextureUV = UVs[result];
					else
						v.Normal = Normals[result];

					number.clear();
					cur++;
				}

				AddVertex(v);
			}
			globalCur += cur;
		}
	}

	positions.clear();
	Normals.clear();
	UVs.clear();

	file.close();

	std::chrono::time_point end = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedSeconds = end - start;

	verticeCount = vertices.size();
	indexCount = index.size();
	Core::Debug::log.Print("%s : %d vertice parsed in %fs", fileName, verticeCount, elapsedSeconds.count());

	isLoaded = true;
}

void Model::Unload()
{
	vertices.~vector();
	index.~vector();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Model::Draw()
{
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

Vertex* Model::getVertices()
{
	return vertices.data();
}

uint32_t* Model::getIndex()
	
{
	return index.data();
}

Model::~Model()
{
	Unload();
}
