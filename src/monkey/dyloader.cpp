#include <monkey/dyloader.h>
#include <monkey/error.h>
#include <iostream>
#include <monkey/scenefactory.h>

#ifdef __linux__

    #include <dlfcn.h>
    void DynamicLoader::load(const std::string &file, SceneFactory* s) {

        void* handle = dlopen(file.c_str(), RTLD_NOW);
        if (handle == NULL) {
            GLIB_FAIL("ERROR! Cannot open extension library " << file << ": " << dlerror());
        } else {
            std::cout << "Loaded succesfully extension: " << file << std::endl;
        }
        typedef void (*hello_t)(SceneFactory*);

        hello_t hello = (hello_t) dlsym(handle, "hello");
        const char *dlsym_error = dlerror();
        if (dlsym_error) {
            std::cerr << "Cannot load symbol 'hello': " << dlsym_error << '\n';
        } else {
            hello(s);
        }
	}
#elif _WIN32
    #include <windows.h>
    void DynamicLoader::load(const std::string &file, SceneFactory* s) {
        HMODULE handle = LoadLibrary(TEXT(file.c_str()));
        if (handle == NULL) {
            GLIB_FAIL("ERROR! Cannot open extension library " << file);
        } else {
            std::cout << "Loaded succesfully extension: " << file << std::endl;
        }
        typedef void (*hello_t)(SceneFactory*);
        FARPROC initializer = GetProcAddress(handle, "hello");
        if (initializer == NULL) {
            std::cerr << "Cannot load symbol 'hello': \n";
        } else {
            hello_t hello = (hello_t) initializer;
            hello(s);
        }
    }
#endif


