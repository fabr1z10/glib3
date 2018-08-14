#include <iostream>
#include <monkey/luawrapper.h>
#include <monkey/luatable.h>
#include <gfx/error.h>
#include <gfx/engine.h>
#include <monkey/monkey.h>
#include <set>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: monkey <directory>" << std::endl;
        return 1;
    }

    try {
        std::string homeDir(argv[1]);
        Engine::get().GetAssetManager().SetDirectory(homeDir);
        Monkey& m = Monkey::get();
        m.Start();
        
        
        
        //LuaWrapper::Init();
        //LuaWrapper::Load("main.lua");
        //LuaTable a("engine");
        //int c = a.Get<int>("ciao");
        
        //std::cout << devSize.x << std::endl;
        
                //std::cout << "prova = " << a.Get<int>("prova")<< "\n";

        //luabridge::LuaRef r = luabridge::getGlobal(LuaWrapper::L, "ciao");
        //r();
        //a.Set("prova", 20);
        //std::cout << "prova = " << a.Get<int>("prova")<< "\n";
        //r();

    } catch (Error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    std::cout << "pippo\n";
    return 0;
}
