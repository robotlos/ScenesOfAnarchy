#pragma once

#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision\Runtime\EnginePlugins\Havok\HavokPhysicsEnginePlugin\vHavokContactListener.hpp>


class myCollisionListener : public hkpContactListener
{
public:
	void contactProcessCallback(hkpContactProcessEvent &event) HKV_OVERRIDE
	{
		collision(false);
	}
	static long collision(bool reset)
	{
		static long collisions = 0;
		long t = collisions;
		if(reset)
		{
			collisions = 0;
			return t;
		}
		else
			collisions++;
		return collisions;
	}
};