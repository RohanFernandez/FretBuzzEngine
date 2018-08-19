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

		protected:
			friend class ResourceManager;

			///unloads the resource in managed child
			virtual void destroyResource() = 0;

		};
	}
}