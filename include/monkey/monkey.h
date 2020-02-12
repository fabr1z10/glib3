#pragma once

#include <monkey/ref.h>
#include <monkey/singleton.h>

class Monkey : public Singleton<Monkey> {
	friend class Singleton<Monkey>;
	public:
		template<class T>
		T* Get(int id) {
			auto it = g_refs.find(id);
			if (it == g_refs.end()) {
				GLIB_FAIL("Unknown id!");
			}
			return dynamic_cast<T*>(it->second);
		}
		template<class T>
		T* Get(const std::string& id) {
			auto it = g_taggedRefs.find(id);
			if (it == g_taggedRefs.end()) {
				GLIB_FAIL("Unknown id: " << id);
			}
			return dynamic_cast<T*>(it->second);
		}

		int getNextId();
        bool isAlive (int) const;
		void add (int, Ref*);
		void add (const std::string&, Ref*);
		void remove (int);
		void remove (const std::string&);
	protected:
		Monkey();
	private:
		// every reference created is assigned a unique id and inserted here
		int g_id;
		std::unordered_map<int, Ref*> g_refs;
		std::unordered_map<std::string, Ref*> g_taggedRefs;

};