#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class CollisionEvents2D
		{
		public:
			CollisionEvents2D() {};
			virtual ~CollisionEvents2D() = 0 {};

			virtual void OnCollisionEnter2D() {};
			virtual void OnCollisionExit2D()  {};
			virtual void OnCollisionStay2D()  {};
			virtual void OnTriggerEnter2D()   {};
			virtual void OnTriggerExit2D()    {};
			virtual void OnTriggerStay2D()    {};
		};
	}
}