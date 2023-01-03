#pragma once
#include "Scene.h"

namespace Resource
{
	class Scene1 : public Scene
	{
	public:
		void Init(Resource::ResourceManager& resourcesManager) override;
	};
}