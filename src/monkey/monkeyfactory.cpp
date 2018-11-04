#include <monkey/monkeyfactory.h>
#include <monkey/factories.h>


MonkeyFactory::MonkeyFactory() : BasicSceneFactory() {

    AddFactory<WalkAreaComponentFactory>("walkarea");
    AddFactory<ScalingComponentFactory>("scaling");

}
