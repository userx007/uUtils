
#include "uFileViewer.hpp"


int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    uFileViewer viewer(argv[1]);

    viewer.show();

    // Show hex dump with various flag combinations
    viewer.showhex(16, "OSAD");
    viewer.showhex(16, "OSAd");
    viewer.showhex(16, "OSad");
    viewer.showhex(16, "Osad");
    viewer.showhex(32, "osad");

    return 0;
}
