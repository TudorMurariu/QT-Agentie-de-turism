#include "Agentiedeturismqt.h"
#include "Oferta.h"
#include "UI.h"

#include <iostream>
#include <string>

#include "Service.h"
#include "Repo.h"
#include "Validators.h"
#include "wishlist_Repo.h"

#include <stdlib.h>
#include <crtdbg.h>

#include <vector>
using namespace std;

void all_tests();

int main(int argc, char* argv[])
{
    all_tests();

    QApplication a(argc, argv);

    vector<Oferta> Lista_oferte;
    Valid valid;
    Repo repo(Lista_oferte);
    wish_list wish;
    Service service(repo, wish, valid);

    /// definim UI-ul
    console gui(service);
    gui.build_UI();
    gui.connectSignalsSlots();

    gui.show();

    _CrtDumpMemoryLeaks();

    return a.exec();
}
 
void all_tests()
{
    vector<Oferta> Lista_oferte;
    Valid valid;
    Repo repo(Lista_oferte);
    wish_list wish;
    Service service(repo, wish, valid);
    test_service(service);
    tests_validators(valid);
}