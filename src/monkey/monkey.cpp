#include <monkey/monkey.h>

//extern std::unordered_map<int, std::weak_ptr<Ref> > Ref::g_refs;

std::shared_ptr<Ref> Monkey::getRef(int id) {
	auto it = Ref::g_refs.find(id);
	if (it == Ref::g_refs.end()) {
		return nullptr;
	}
	return std::shared_ptr<Ref>(it->second);
}