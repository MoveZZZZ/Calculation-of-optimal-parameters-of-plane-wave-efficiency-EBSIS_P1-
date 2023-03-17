#include "Include/cDane.h"
#include "Include/dodatkoweOtwory.h"
#include "Include/cMenu.h"
using namespace std;
int main() {
    cMenu* menu;
    menu = new cMenu();
    menu->printMenu();
    delete menu;

}
    