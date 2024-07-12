#include "defineelements.h"
#include "definesettings.h"


struct Element {
    const char* name;
    int raw_element;
    const char* settings[10];
};

static Element element1 = { "element1", RAW_ELEMENT1, { SETTINGS1, SETTINGS2} };
static Element element2 = { "element2", RAW_ELEMENT2, { SETTINGS3, SETTINGS4} };
static Element element3 = { "element3", RAW_ELEMENT3, { SETTINGS5, SETTINGS6} };
static Element element4 = { "element4", RAW_ELEMENT4, { SETTINGS7, SETTINGS8} };
static Element element5 = { "element5", RAW_ELEMENT5, { SETTINGS9, SETTINGS10} };