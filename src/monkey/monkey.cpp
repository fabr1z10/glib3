#include <monkey/monkey.h>

Monkey::Monkey() : g_id(0) {}

int Monkey::getNextId() {
	return g_id++;
}

void Monkey::add(int id, Ref * ref) {
	g_refs.insert(std::make_pair(id, ref));
}

void Monkey::add(const std::string& tag, Ref * ref) {
	g_taggedRefs.insert(std::make_pair(tag, ref));

}


void Monkey::remove(int id) {
	g_refs.erase(id);
}

void Monkey::dump() {

	std::cout << "# of items: " << g_refs.size() << "\n";
}

void Monkey::remove(const std::string& tag) {
	g_taggedRefs.erase(tag);
}

bool Monkey::isAlive (int id) const {
	return g_refs.count(id) > 0;

}