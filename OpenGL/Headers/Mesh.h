#pragma once
#include <vector>

#include "Resources.h"

namespace lowRenderer
{
	class Mesh
	{
	private:
		Resource::Model* model;

		Resource::Shader* shader;

		Resource::Texture* texture;

	public:

		Mesh(Resource::Model* _model, Resource::Texture* _texture, Resource::Shader* _Shader);
		Mesh(Resource::ResourceManager& resourcesManager, const char* modelFileName, const char* textureFileName, Resource::Shader* _Shader);

		Resource::Shader* Shader() { return shader; }
		Resource::Texture* Texture() { return texture; }
		Resource::Model* Model () { return model; }
	};
}