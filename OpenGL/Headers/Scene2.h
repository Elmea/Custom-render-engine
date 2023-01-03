#pragma once
#include "Scene.h"

namespace Resource
{
	class Scene2 : public Scene
	{
	public:
		void Init(Resource::ResourceManager& resourcesManager) override;
	};
}