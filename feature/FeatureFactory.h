#pragma once
#include "Feature.h"
#include <string>
#include <map>



class FeatureFactory
{
	public:
		typedef CFeature *(*CreateCallback)();
		static void RegisterFeature (const std::string &type, CreateCallback cb);
		static void UnregisterFeature (const std::string &type);
		static CFeature *CreateFeature (const std::string &type);
	private:
		typedef std::map<std::string, CreateCallback> CallbackMap;
		static CallbackMap mFeatures;
};