#pragma once

#include <monkey/singleton.h>
#include <monkey/ref.h>
#include <memory>

class Monkey : public Singleton<Monkey> {
	public:
		template<class T>
		std::shared_ptr<T> get(int id) {
			auto ref = getRef(id);
			if (ref == nullptr) {
				GLIB_FAIL("Unknown id!");
			}
			return std::dynamic_pointer_cast<T>(ref);
		}
		
	private:
		std::shared_ptr<Ref> getRef(int id);
};