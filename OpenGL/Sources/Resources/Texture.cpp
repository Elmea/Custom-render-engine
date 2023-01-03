#include <STB_Image/stb_image.h>
#include "IncludeGL.h"

#include "Debug.h"
#include "Texture.h"

using namespace Resource;

void Texture::Load(const char* fileName)
{
	

	{
		const std::string path = fileName;

		if (path.find(".png") != std::string::npos)
			ispng = true;
	}

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	isLoad = true;
}

void Texture::ImgBuffer()
{
	ASSERT(data != nullptr, "Can't load texture")

		glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (ispng)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	// create a sampler and parameterize it
	// ------------------------------------

	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	glBindTextureUnit(id, texture);
	glBindSampler(id, sampler);

	isBuffer = true;
}

void Texture::Unload()
{
	glDeleteTextures(id, &texture);

	glDeleteSamplers(1, &sampler);
}