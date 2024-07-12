#include "defineelements.h"
#include "definesettings.h"


struct Element {
    const char* name;
    int raw_element;
    const char* settings[10];
};

Element element1 = { "element1", RAW_ELEMENT1, { SETTINGS1, SETTINGS2} };
Element element2 = { "element2", RAW_ELEMENT2, { SETTINGS3, SETTINGS4} };
Element element3 = { "element3", RAW_ELEMENT3, { SETTINGS5, SETTINGS6} };
Element element4 = { "element4", RAW_ELEMENT4, { SETTINGS7, SETTINGS8} };
Element element5 = { "element5", RAW_ELEMENT5, { SETTINGS9, SETTINGS10} };