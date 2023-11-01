#include "../include/gui.h"

int main(int argc, char **argv) {
//use for testing for now

    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {

        return std::make_unique<GUI>(env);

    });

}
