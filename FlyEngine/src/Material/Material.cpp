#include "Material.h"

namespace FlyEngine
{
	namespace Materials
	{

		Material::Material()
		{
			specs = new MaterialSpecification();
			specs->SetSpecs(MaterialList::WhitePlastic);
		}

		Material::~Material()
		{
			if (specs != nullptr)
			{
				delete specs;
				specs = nullptr;
			}
		}

		MaterialSpecification* Material::GetSpecs()
		{
			return specs;
		}

	}

}