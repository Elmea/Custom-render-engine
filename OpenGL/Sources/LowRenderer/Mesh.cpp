#include "IncludeGL.h"

#include "Mesh.h"

using namespace lowRenderer;

Mesh::Mesh(Resource::ResourceManager& resourcesManager, const char* modelFileName, const char* textureFileName, Resource::Shader* _Shader)
{
	model = (Resource::Model*)resourcesManager.Get<Resource::Model>(modelFileName);
	if (model == nullptr)
		model = (Resource::Model*)resourcesManager.Create<Resource::Model>(modelFileName);

	texture = (Resource::Texture*)resourcesManager.Get<Resource::Texture>(textureFileName);
	if (model == nullptr)
		texture = (Resource::Texture*)resourcesManager.Create<Resource::Texture>(textureFileName);

	shader = _Shader;
}

Mesh::Mesh(Resource::Model* _model, Resource::Texture* _texture, Resource::Shader* _Shader)
{
	model = _model;
	shader = _Shader;
	texture = _texture;
}