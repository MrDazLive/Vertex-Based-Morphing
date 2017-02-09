#include "Material.h"

unsigned int UniformBlock<Material>::m_blockSize = 4;

Material::Material(const std::string& name) : UniformBlock<Material>(this, name) {

}

void Material::BuildBlock(float* ptr) {
	const unsigned int size = getBlockSize();
	ptr[0] = 1.0f;
	ptr[1] = 1.3f;
	ptr[2] = 1.0f;
	ptr[3] = 1.4f;
}