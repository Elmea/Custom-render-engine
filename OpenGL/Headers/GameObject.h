#pragma once
#include "Mesh.h"
#include "Shader.h"

namespace lowRenderer
{
	class GameObject;

	struct SceneNode
	{
		GameObject* attachedObj;

		myMaths::Mat4 globalTransform;
		myMaths::Mat4 localTransform;

		SceneNode* parent;
		std::vector<SceneNode*> childs;
	};

	class GameObject
	{
	private:
		Mesh* mesh;

		bool isChild;
		bool isParent;
		SceneNode node;

	public:
		GameObject();

		GameObject(Mesh* _mesh);

		std::string name = "NewGameObject";

		myMaths::Float3 position;
		myMaths::Float3 rotation;
		myMaths::Float3 scale = (1.f, 1.f, 1.f);

		Resource::Shader* getShader() { return mesh->Shader(); }

		void Draw(myMaths::Mat4& VPMatrix);

		void SetParent(GameObject* parent);
		void AddChild(GameObject& child);
		void RemoveChild(GameObject& child);
		void RemoveAllChild();

		bool GotMesh() { return mesh != nullptr; }

		myMaths::Mat4 GetGlobalTransform();

		bool IsLoaded();
	};
}