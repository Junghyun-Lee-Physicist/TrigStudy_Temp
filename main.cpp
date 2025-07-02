#include <iostream>
#include <string>
#include "EventLooper.hh"

int main(int argc, char** argv) {
    // Usage message
    if (argc < 2) {
        std::cerr << "Usage: ./exe_TrigStudy [SampleName] [UseCorrections (0 or 1)] [Debug (0 or 1)]\n";
        return 1;
    }

    std::string sampleName = argv[1];
    // Determine whether to apply trigger scale factors (default 0 if not provided)
    bool applySF = false;
    if (argc >= 3) {
        applySF = (std::stoi(argv[2]) != 0);
    }
    // Debug flag for verbose output (default off)
    bool debug = true;
    if (argc >= 4) {
        debug = (std::stoi(argv[3]) != 0);
    }

    std::cout << "[Main] Starting trigger study for sample '" << sampleName 
              << "' (ApplySF=" << applySF << ", Debug=" << debug << ")\n";

    // Create and run the event looper
    EventLooper looper(sampleName, applySF, debug);
    if (!looper.Init()) {
        std::cerr << "[Main] Initialization failed for sample '" << sampleName << "'.\n";
        return 1;
    }
    looper.Loop();

    std::cout << "[Main] Completed trigger study for sample '" << sampleName << "'.\n";
    return 0;
}
