#pragma once
#include "myMaths.hpp"
#include "Shader.h"

namespace lowRenderer
{
	enum class lightType
	{
		LT_DIRECTIONAL ,
		LT_POINT,
		LT_SPOT
	};

	enum class colorType
	{
		CT_AMBIANT,
		CT_DIFFUSE,
		CT_SPECULAR
	};

	class Light
	{
	private:
		int id;

		bool active = true;

		myMaths::Float3 position;
		myMaths::Float3 direction;

		myMaths::Float3 ambiantColor;
		myMaths::Float3 diffuseColor;
		myMaths::Float3 specularColor;

		float intensity = 1;

		float constant = 0;
		float linear = 0;
		float quadratic = 0;

		float cutOff = 1;
		float outerCutOff = 0;

		lightType type;

	public:
		std::string name;

		Light(const char* _name, lightType _type, int _id) { name = _name; type = _type; setId(_id); }

		void SetLight(colorType type, myMaths::Float3 color);
		void SetLight(myMaths::Float3 _AmbiantColor, myMaths::Float3 _DiffuseColor, myMaths::Float3 _SpecularColor);
		void SetDir(myMaths::Float3 vector);
		void SetIntensity(float _intensity);
		void SetCutOff(float _cutOff);
		void SetOuterCutOff(float _outerCutOff);

		void setActive(bool _active) { active = _active; }
		bool isActive() { return active; }
		void SetPos(myMaths::Float3 _pos) { position = _pos; }

		void setAtenuation(float _constant, float _linear, float _quadratic);

		void setId(int _id);

		myMaths::Float3 getAmbiant() { return ambiantColor; }
		myMaths::Float3 getDiffuse() { return diffuseColor; }
		myMaths::Float3 getSpecular() { return specularColor; }
		myMaths::Float3 getDirection() { return direction; }
		myMaths::Float3 getPosition() { return position; }
		float getIntensity() { return intensity; }
		float getCutOff() { return cutOff; }
		float getOuterCutOff() { return outerCutOff; }

		myMaths::Float3* getAmbiantPtr() { return &ambiantColor; }
		myMaths::Float3* getDiffusePtr() { return &diffuseColor; }
		myMaths::Float3* getSpecularPtr() { return &specularColor; }
		myMaths::Float3* getDirectionPtr() { return &direction; }
		myMaths::Float3* getPositionPtr() { return &position; }
		float* getIntensityPtr() { return &intensity; }
		float* getCutOffPtr() { return &cutOff; }
		float* getOuterCutOffPtr() { return &outerCutOff; }

		bool followCamera = false;

		lightType getType() { return type; }

		void Generate(Resource::Shader* shader, myMaths::Float3 viewPos);

	};
}