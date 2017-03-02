#pragma once
#include "handler.h"
#include "stddef.h"
#include <mutex>

namespace cng {

class MainLoop {
public:
	// Setup windows and event settings.
	virtual void init() = 0;

	// Run the main loop until the bool get false.
	virtual bool loop() = 0;

	// Destroy the resources.
	virtual void destroy() = 0;

	inline void loopMain() {
		init();
		while(loop());
		destroy();
	}
};

class DefaultMainLoop : public MainLoop {
	Handler* m_handler;
	std::recursive_mutex m_handlerAccess;
public:
  	DefaultMainLoop(): m_handler(NULL) {}
	virtual ~DefaultMainLoop() {}

	virtual void init() override;

	virtual void enter(Handler* handler);

	virtual bool loop() override;

	virtual void destroy() override;
};

}
