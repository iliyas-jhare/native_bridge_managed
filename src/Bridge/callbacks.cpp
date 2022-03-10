
#include "callbacks.h"

namespace
{
	class callbacks_impl final : public callbacks
	{
	public:
		explicit callbacks_impl(bridge_callbacks callbacks)
			: callbacks(callbacks)
		{}

		void log(const std::string& msg) const final
		{
			callbacks.log(msg.c_str());
		}

		void* owner_handle() const final
		{
			return callbacks.owner_handle();
		}

	private:
		bridge_callbacks callbacks;
	};
}

callbacks_ptr callbacks::create(bridge_callbacks callbacks)
{
	return std::make_shared<callbacks_impl>(callbacks);
}