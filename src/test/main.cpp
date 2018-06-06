#include <test/io.h>
#include <gfx/engine.h>
#include <test/testgfx.h>
#include <test/solution.h>
#include <iostream>
#include <test/global.h>
//
//std::string homeDir;
//
//void testTCS() {
//    Solution s("/home/fabrizio/sources/tcs_processor/TestCaseUP/output/output_BR_76_Scenario_2_B_planner_input.xml");
//    std::cout << s.GetPosition("MNPPC", 1517810300) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810400) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810527) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517810528) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517813767) << std::endl;
//    std::cout << s.GetPosition("MNPPC", 1517813768) << std::endl;
//
//
//
//}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: viewer <file>\n";
            return 1;
        }
        Config::get().SetHomeDir(argv[1]);
        Config::get().GetRailway().Load();
    } catch (Error& err){
        std::cerr << err.what() << std::endl;
        return 1;
    }
}


