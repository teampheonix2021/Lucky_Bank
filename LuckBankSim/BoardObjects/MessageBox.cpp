#include "MessageBox.h"
using namespace std;

MessageBox::MessageBox() {}

void MessageBox::draw(GUI& gui)
{
    gui.drawMessageBox();
}