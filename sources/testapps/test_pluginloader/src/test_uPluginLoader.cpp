#include "uPluginLoader.hpp"
#include <iostream>


// Mock plugin interface
class IFakePlugin {
public:
    virtual ~IFakePlugin() = default;
    virtual const char* shout() const = 0;
};

class FakePlugin : public IFakePlugin {
public:
    const char* shout() const override {
        return "FakePlugin is alive!";
    }
};

// Redirected plugin entry/exit
IFakePlugin* FakeEntry() { return new FakePlugin(); }
void FakeExit(IFakePlugin* plugin) { delete plugin; }

// Custom test setup mimicking a real shared lib environment
int main() {
    using Entry = PluginTypes<IFakePlugin>::PluginEntry;
    using Exit = PluginTypes<IFakePlugin>::PluginExit;
    using Handle = PluginTypes<IFakePlugin>::PluginHandle;

    // Manually construct the plugin "handle"
    LibHandle dummyLibHandle = reinterpret_cast<LibHandle>(0x1); // pretend valid
    Entry entryFunc = &FakeEntry;
    Exit exitFunc = &FakeExit;

    IFakePlugin* rawPlugin = entryFunc();
    std::shared_ptr<IFakePlugin> pluginPtr(
        rawPlugin,
        [dummyLibHandle, exitFunc](IFakePlugin* p) {
            if (p) exitFunc(p);
            // No real unload
        });

    Handle pluginHandle = { dummyLibHandle, pluginPtr };

    // Simulated usage
    if (pluginHandle.second) {
        std::cout << pluginHandle.second->shout() << std::endl;
    } else {
        std::cerr << "Oops, plugin failed." << std::endl;
    }

    return 0;
}
