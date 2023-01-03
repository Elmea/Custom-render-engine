#pragma once
#include <vector>
#include <atomic>
#include "IncludeGL.h"

#include "RessourceManager.h"
#include "myMaths.hpp"

namespace Resource
{
	struct Vertex
	{
		myMaths::Float3 Position;
		myMaths::Float3 Normal;
		myMaths::Float2 TextureUV;

		bool operator==(Vertex other) { return (Position == other.Position) && (Normal == other.Normal) && (TextureUV == other.TextureUV); }
	};

	class Model : public IResource
	{
	private:

		void AddVertex(Vertex v);

		unsigned int VBO, VAO, EBO;
		void Unload() override;

		int verticeCount;
		unsigned int indexCount;
		std::atomic<bool> isLoaded;
		std::atomic<bool> isInBuffer;

	public:


		std::vector<Vertex> vertices;
		std::vector<uint32_t> index;

		bool IsLoaded() { return isLoaded; }
		bool IsInBuffer() { return isInBuffer; }

		void fillBuffers();

		void Load(const char* fileName) override;
		
		void Draw();

		Vertex* getVertices();

		int getVerticesCount() { return verticeCount; }
		int getIndexCount() { return indexCount; }

		uint32_t* getIndex();

		unsigned int getVAO() { return VAO; }

		Model();
		~Model();
	};
}
