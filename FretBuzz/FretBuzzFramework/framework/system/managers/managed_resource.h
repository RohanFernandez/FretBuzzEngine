#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class IManagedResource
		{
		public:
			IManagedResource() {};

			virtual ~IManagedResource()
			{
			
			}

			///unloads the resource in managed child
			virtual void unloadResource() = 0;
		};
	}
}