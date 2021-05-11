#include <memory>

#include <monkey/engine.h>
#include <monkey/scenefactory.h>
#include <monkey/renderingiterator.h>

#include <monkey/python/pymonkey.h>
#include <pybind11/stl.h>
#include <monkey/input/pytab.h>

#include <dlfcn.h>

namespace py = pybind11;

GLFWwindow* window;

Engine::Engine() : m_mouseEnabled{true}, m_sceneFactory{nullptr} {
    m_sceneFactory = std::make_shared<SceneFactory>();
}

void Engine::SetDeviceSize(glm::vec2 size) {
    m_deviceSize = size;
    m_aspectRatio = size.x / size.y;
}

void Engine::SetTitle(const std::string & title) {
    m_title = title;
}

void Engine::SetWindowSize(glm::ivec2 size) {
    m_winSize = size;
}

void Engine::SetFPS(int frameRate) {
    m_frameTime = 1.0 / static_cast<double>(frameRate);
}

void Engine::EnableMouse() {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void Engine::EnableKeyboard() {
    glfwSetKeyCallback(window, key_callback );

}

void Engine::init(const std::string& gameFolder) {

    std::stringstream dir;
    dir << gameFolder;
    if (gameFolder[gameFolder.size()-1] != '/')
        dir << '/';
    m_gameDirectory = dir.str();
    std::cout << m_gameDirectory << " ---\n";
    std::stringstream pycode ;
    pycode << "import example\n"
        "import sys\nsys.path.append('" << gameFolder << "')\n"
        "sys.path.append('" << m_gameDirectory << "../')\n";//example.what=150";
    
    py::exec(pycode.str().c_str());

    Monkey& m = Monkey::get();
    py::object pye = py::module::import("example").attr("engine");
    //pye.attr("__dir") = gameFolder;
    
    PyEngine py2(&m, this);
    pybind11::object w = py::cast(py2);
    py::module::import("example").attr("what") = w;
    py::module::import("example").attr("dir") = gameFolder;

    auto module = py::module::import("main");
    //module.attr("engine.device)
    m_mainTable = std::make_unique<PyTab>(module.attr("engine"));

	// read addon libs
	auto libs = m_mainTable->get<std::vector<std::string>>("libs");
	for (const auto& lib : libs) {
	    std::stringstream libFile;
	    libFile << "../" << lib << "/lib" << lib << ".so";
		void * handle = dlopen(libFile.str().c_str(), RTLD_NOW);
		if (!handle) {
			fputs(dlerror(), stderr);
			exit(1);
		}
        //void (*extend)(SceneFactory*);
        auto extendp = dlsym(handle, "applyExtension");
		char* error;
		if ((error = dlerror()) != NULL) {
		    fputs(error, stderr);
		    exit(1);
		}
        auto extend = reinterpret_cast<void(*)(SceneFactory*)>(extendp);

		extend(m_sceneFactory.get());

	}
    glm::vec2 deviceSize = m_mainTable->get<glm::vec2>("device_size");
    m_tickMultiplier = m_mainTable->get<float>("tick_multiplier", 1.0f);

    SetDeviceSize(deviceSize);
    m_winSize = m_mainTable->get<glm::vec2>("window_size");
    m_title = m_mainTable->get<std::string>("title");

    // initialize Open GL
    InitGL();

    int widthPixel;
    int widthPoint;
    int heightPixel;
    int heightPoint;
    glfwGetWindowSize(window, &widthPoint, &heightPoint);
    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
    m_pixelRatio = static_cast<float>(widthPixel) / widthPoint;


    // set-up the rendering engine
    auto renderingEngine = std::make_unique<RenderingEngine>();
    SetRenderingEngine(std::move(renderingEngine));

    EnableMouse();
    EnableKeyboard();
    SetFPS(60);

    m_assetManager.Init();
    m_sceneFactory->StartUp(this);

}

void Engine::restart() {

    m_scene->restart();
    m_scene->Begin();
}

void Engine::Init(const std::string& home, const std::string& game) {

    m_running = false;
    SetDirectory(home);
    m_game = game;
    std::stringstream str;
    str << m_directory << "data/" << m_game << '/';
    m_gameDirectory = str.str();
    m_sceneFactory->Init(this);
    // NOW YOU CAN INITIALIZE THE ASSET MANAGER!!!
    m_assetManager.Init();
    InitGL();

    // find pixel ratio
    int widthPixel;
    int widthPoint;
    int heightPixel;
    int heightPoint;
    glfwGetWindowSize(window, &widthPoint, &heightPoint);
    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
    m_pixelRatio = static_cast<float>(widthPixel) / widthPoint;


    // set-up the rendering engine
    auto renderingEngine = std::unique_ptr<RenderingEngine>(new RenderingEngine);
    SetRenderingEngine(std::move(renderingEngine));

    m_sceneFactory->StartUp(this);
    //





}

void Engine::InitGL() {

    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(m_winSize.x, m_winSize.y, m_title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    // note: we are setting a callback for the frame buffer resize event,
    // so the dimensions we will get will be in pixels and NOT screen coordinates!
    glfwSetFramebufferSizeCallback(window, Engine::WindowResizeCallback);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit()) {
        GLIB_FAIL("Unable to initialize GLEW ... exiting");
        exit(EXIT_FAILURE);
    }
    GLint Mv, mv;
    glGetIntegerv(GL_MAJOR_VERSION, &Mv);
    glGetIntegerv(GL_MINOR_VERSION, &mv);

    if(!GLEW_ARB_vertex_array_object) {
        GLIB_FAIL("ARB_vertex_array_object not available.");
    }
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);
    std::cout << "OpenGL version " << Mv << "." << mv << std::endl;
}

glm::vec4 Engine::GetViewport(float x, float y, float width, float height) {
    glm::vec4 viewport;
    viewport[3] = static_cast<GLsizei> (m_actualSize.y * (height / m_deviceSize.y));
    viewport[2] = static_cast<GLsizei> (m_actualSize.x * (width / m_deviceSize.x));
    viewport.x = (m_winSize.x - m_actualSize.x) / 2.0f + x * (m_actualSize.x / m_deviceSize.x);
    viewport.y = (m_winSize.y - m_actualSize.y) / 2.0f + y * (m_actualSize.y / m_deviceSize.y);
    return viewport;

}


void Engine::SetViewport(float x, float y, float width, float height) {
    // convert from device size to window size
    //glm::vec4 viewport = GetViewport(x, y, width, height);
//    float vph = static_cast<GLsizei> (m_actualSize.y * (height / m_deviceSize.y));
//    float vpw = static_cast<GLsizei> (m_actualSize.x * (width / m_deviceSize.x));
//    float vpx = (m_winSize.x - m_actualSize.x) / 2.0f + x * (m_actualSize.x / m_deviceSize.x);
//    float vpy = (m_winSize.y - m_actualSize.y) / 2.0f + y * (m_actualSize.y / m_deviceSize.y);
    glViewport(x, y, width, height);
}



void Engine::MainLoop() {

    while (!glfwWindowShouldClose(window)) {

        // get current room
        std::cerr << "abc\n";
        auto room = m_mainTable->get<std::string>("room");
		std::cerr << "room: " << room;
        py::function builder;
//        try {
//            builder = m_mainTable->get<py::dict>("data")["rooms"][room.c_str()].cast<py::function>();
//        } catch (...) {
//            GLIB_FAIL("Unable to find the builder for room: " << room)
//        }
        std::cout << "=================================\n";
        std::cout << "Loading room: "<< room << std::endl;
        std::cout << "=================================\n";
		auto roomDef = m_mainTable->get<py::function>("create_room") ();//   builder().cast<py::object>();

        m_scene = m_sceneFactory->Create(roomDef);
        
        // start the scene (initialize components)
        // init runners
        for (auto& r : m_runners) {
            r.second->Init();
        }
        m_scene->start();
        m_scene->Begin();
        m_running = true;
		for (auto& r : m_runners) {
			r.second->Begin();
		}
//
//        //for (auto iter = m_scene->begin(); iter != m_scene->end(); ++iter) {
//        //    iter->Start();
//        //}
//
        auto initFunc = roomDef.attr("init").cast<py::list>();
        for (auto ifunc : initFunc) {
            ifunc();
        }
        //m_sceneFactory->PostInit();


        // call startUp
        int widthPixel, heightPixel;
        glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
        Engine::WindowResizeCallback(window, widthPixel, heightPixel);

        // run the scene
        m_endScene = false;
        std::cout << "Starting game: time step = " << m_frameTime << "\n";
        while (!glfwWindowShouldClose(window) && !m_endScene) {
            double currentTime = glfwGetTime();

            if (currentTime - m_timeLastUpdate >= m_frameTime) {
                //double t0 = glfwGetTime();
                m_timeLastUpdate = currentTime;

                // remove all entities scheduled for removal
                if (!m_garbage.empty()) {
                    for (auto & g : m_garbage) {
                        // remove from parent
                        auto parent = g.first->GetParent();
                        parent->Remove(g.first);
//                        if (g.second != nullptr) {
//                            g.second->AddChild(g.first);
//                        }
                    }
                    m_garbage.clear();
                }

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // update all active components
                // this calls update on children nodes
                m_scene->Update(m_frameTime);
                //iterateDepth(m_scene.get(), [&] (Entity* entity) { entity->Update(m_frameTime); });

                // update all the runners (script, collision, etc.)
                for (auto& runner : m_runners) {
                    if (runner.second->isActive())
                        runner.second->Update(m_frameTime);
                }

                // Finally render the scene
                m_renderingEngine->Update(m_frameTime);

                //double t1 = glfwGetTime();
                //std::cout << "frame updated in: " << (t1-t0) << " sec.\n";
                glfwSwapBuffers(window);
                glfwPollEvents();

            }
            //glfwSwapBuffers(window);
        }
        // remove assets loaded at scene level
        Monkey::get().dump();
        m_running = false;
		std::cerr << "CLEAN!\n";
        m_sceneFactory->CleanUp();
		std::cerr << "DONE!\n";
        std::cerr << "clearing runners";
        m_runners.clear();
        std::cerr << "done\n";
        m_scene = nullptr;
        m_garbage.clear();
		std::cerr << "done2\n";
		Monkey::get().dump();

    }
    // shutdown

    std::cerr << "shutting down the engine.\n";
    m_renderingEngine = nullptr;
    std::cerr << "lll\n";
    glfwDestroyWindow(window);
    glfwTerminate();
}

// width and height will be pixels!!
void Engine::WindowResizeCallback(GLFWwindow* win, int width, int height) {
    // notify cameras

    if (height == 0) height = 1;
    // update the window aspect
    Engine& engine = Engine::get();
    float winAspectRatio = static_cast<float>(width) / height;
    engine.m_winAspectRatio = winAspectRatio;
    engine.m_winSize = glm::vec2(width, height);
    if (winAspectRatio > engine.m_aspectRatio) {
        // vertical bands
        engine.m_actualSize = glm::vec2 (height * engine.m_aspectRatio, height);
    } else {
        // horizontal bands
        engine.m_actualSize = glm::vec2 (width, width / engine.m_aspectRatio);
    }

    for (auto& listener : Engine::get().m_resizeListeners)
        listener->Notify(width, height);

    // recalculate all camera viewports
    //glm::vec4 viewport;
    Entity* root = Engine::get().GetScene();
    ResizeIterator iterator(root, engine.m_winSize, engine.m_actualSize);
    while (!iterator.end()) {
        ++iterator;
    }

}

void Engine::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    if (Engine::get().m_mouseEnabled) {
        for (auto &listener : Engine::get().m_mouseListeners) {
            if (listener->isEnabled())
                listener->MouseButtonCallback(win, button, action, mods);
        }
    }
}

void Engine::cursor_pos_callback(GLFWwindow* win, double xpos, double ypos) {

    if (Engine::get().m_mouseEnabled) {
        for (auto &listener : Engine::get().m_mouseListeners) {
            if (listener->isEnabled())
                listener->CursorPosCallback(win, xpos, ypos);
        }
    }
}

void Engine::scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
    if (Engine::get().m_mouseEnabled) {
        for (auto &listener : Engine::get().m_mouseListeners)
            if (listener->isEnabled())
                listener->ScrollCallback(win, xoffset, yoffset);
    }
}


void Engine::RegisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.insert(listener);
}

void Engine::UnregisterToWindowResizeEvent(WindowResizeListener* listener) {
    m_resizeListeners.erase(listener);
}

void Engine::RegisterToMouseEvent(MouseListener* listener) {
    m_mouseListeners.insert(listener);
}

void Engine::UnregisterToMouseEvent(MouseListener* listener) {
    m_mouseListeners.erase(listener);
}

void Engine::RegisterToKeyboardEvent(KeyboardListener* listener) {
    m_keyboard.AddListener(listener);
}

void Engine::UnregisterToKeyboardEvent(KeyboardListener* listener) {
    m_keyboard.RemoveListener(listener);
}

Engine::~Engine() {

}


void Engine::SetRenderingEngine(std::unique_ptr<RenderingEngine> engine) {

    m_renderingEngine = std::move(engine);
    m_renderingEngine->Start();
}



void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // don't handle key events for disable keys until mods==16 (programmatically for demo-mode)
    Engine::get().m_keyboard.key_callback(window, key, scancode, action, mods);
}

void Engine::SetDirectory(const std::string& dir)
{
    m_directory = dir;
    if (m_directory.back() != '/')
        m_directory.push_back('/');

}

