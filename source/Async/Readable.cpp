//
//  Readable.cpp
//  File file is part of the "Async" project and released under the MIT License.
//
//  Created by Samuel Williams on 29/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Readable.hpp"

#include <Concurrent/Fiber.hpp>

#include <cassert>

namespace Async
{
	using namespace Concurrent;
	
	Readable::Readable(Descriptor descriptor, Reactor & reactor) : _descriptor(descriptor), _reactor(reactor)
	{
		_reactor.changes().push_back({
			static_cast<uintptr_t>(_descriptor),
			EVFILT_WRITE,
			EV_ADD | EV_CLEAR,
			0,
			0,
			Fiber::current
		});
	}
	
	Readable::~Readable()
	{
		_reactor.changes().push_back({
			static_cast<uintptr_t>(_descriptor),
			EVFILT_WRITE,
			EV_DELETE,
			0,
			0,
			nullptr
		});
	}
	
	void Readable::wait()
	{
		assert(Fiber::current);
		
		Fiber::current->yield();
	}
}
