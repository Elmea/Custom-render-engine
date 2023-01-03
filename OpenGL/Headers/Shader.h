#pragma once
#include <IncludeGL.h>
#include <string>
#include <vector>

#include "RessourceManager.h"
#include "myMaths.hpp"

namespace Resource
{
	class Shader : public IResource
	{
	private:

		int shaderProgram = glCreateProgram();

	public:
		int GetShader() { return shaderProgram; }

		void createShader(const char* vertexShader, const char* fragmentShader);

		void Load(const char* name) override;

		void Unload() override;

		~Shader() { Unload(); }

        void setBool(const std::string& name, bool value) const;

        void setInt(const std::string& name, int value) const;

        void setFloat(const std::string& name, float value) const;

        void setVec2(const std::string& name, const myMaths::Float2& value) const;

        void setVec2(const std::string& name, float x, float y) const;

        void setVec3(const std::string& name, const myMaths::Float3& value) const;

        void setVec3(const std::string& name, float x, float y, float z) const;

        void setVec4(const std::string& name, const myMaths::Float4& value) const;

        void setVec4(const std::string& name, float x, float y, float z, float w);

        void setMat4(const std::string& name, const myMaths::Mat4& mat) const;

		void setMat4(const std::string& name, const myMaths::Mat4& mat, bool transposed) const;
	};
}