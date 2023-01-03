#pragma once
#include "RessourceManager.h"

namespace Resource
{
	class Texture : public IResource
	{
	private:
		GLuint texture;
		GLuint sampler = 0;

		int width, height, nrChannels;
		unsigned char* data;

		bool ispng = false;
		std::atomic<bool> isLoad = false;
		std::atomic<bool> isBuffer = false;

		void Unload() override;

	public:
		bool IsLoad()   { return isLoad; }
		bool IsBuffer() { return isBuffer; }

		void Load(const char* fileName) override;

		void ImgBuffer();

		GLuint getTexture() { return texture; }
		GLuint getSampler() { return sampler; }

		~Texture() { Unload(); }
	};
}