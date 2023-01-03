#include "GameObject.h"

using namespace lowRenderer;

GameObject::GameObject()
{
	mesh = nullptr;
	scale = myMaths::Float3(1.f, 1.f, 1.f);
	isChild = false;
	isParent = false;
	node.attachedObj = this;
}

GameObject::GameObject(Mesh* _mesh)
{
	mesh = _mesh;
	scale = myMaths::Float3(1.f, 1.f, 1.f);
	isChild = false;
	isParent = false;
	node.attachedObj = this;
}

myMaths::Mat4 GameObject::GetGlobalTransform()
{
	node.localTransform = myMaths::Mat4::CreateTransformMatrix(position, rotation, scale);

	if (!isChild)
	{
		node.globalTransform = node.localTransform;
	}
	else
	{
		node.globalTransform = node.parent->attachedObj->GetGlobalTransform() * node.localTransform;
	}

	return node.globalTransform;
}

void GameObject::Draw(myMaths::Mat4& VPMatrix)
{
	// create model matrix
	myMaths::Mat4 transform = GetGlobalTransform();

	if (mesh != nullptr)
	{
		int shaderId = mesh->Shader()->GetShader();
		glUseProgram(shaderId);

		glBindTexture(GL_TEXTURE_2D, mesh->Texture()->getTexture());

		mesh->Shader()->setMat4("model", transform);
		mesh->Shader()->setMat4("VP", VPMatrix);

		if (mesh->Model()->IsInBuffer())
			mesh->Model()->Draw();
	}
}

void GameObject::AddChild(GameObject& child)
{
	if (child.isChild)
		child.node.parent->attachedObj->RemoveChild(child);

	node.childs.push_back(&child.node);
	child.node.parent = &node;
	child.isChild = true;
	isParent = true;
}

void GameObject::SetParent(GameObject* parent)
{
	if (parent == nullptr)
	{
		isChild = false;
		return;
	}

	parent->AddChild(*this);
	isChild = true;
}

void GameObject::RemoveChild(GameObject& child)
{
	for (int i = 0; i < node.childs.size(); i++)
	{
		if (node.childs[i]->attachedObj == &child)
		{
			node.childs.erase(node.childs.begin() + i);
			child.isChild = false;
			break;
		}
	}

	if (node.childs.size() == 0)
		isParent = false;
}

void GameObject::RemoveAllChild()
{
	for (int i = 0; i < node.childs.size(); i++)
	{
		node.childs[i]->attachedObj->SetParent(nullptr);
	}

	isParent = false;
	node.childs.clear();
}

bool GameObject::IsLoaded()
{
	if (mesh != nullptr && mesh->Model() != nullptr && mesh->Texture() != nullptr)
		return mesh->Model()->IsInBuffer() && mesh->Texture()->IsBuffer();

	return false;
}
