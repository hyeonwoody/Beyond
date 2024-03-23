#pragma once
#include "FeatureFactory.h"

FeatureFactory::CallbackMap FeatureFactory::mFeatures;

void FeatureFactory::RegisterFeature (const std::string &type, CreateCallback cb)
{
	mFeatures[type] = cb;
}

void FeatureFactory::UnregisterFeature (const std::string &type)
{
	mFeatures.erase(type);
}

CFeature *FeatureFactory::CreateFeature (const std::string &type)
{
	CallbackMap::iterator it = mFeatures.find(type);
	if (it != mFeatures.end()){
		return (it->second());
	}
	return NULL;
}
