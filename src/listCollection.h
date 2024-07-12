#include "listElements.h"

struct Collection {
    const char* name;
    Element elements[30];
};

Collection Collection1 = { "Collection 1",  {element1, element2}};
Collection Collection2 = { "Collection 2",  { element3, element4}};
Collection Collection3 = { "Collection 3",  { element5}};

Collection collections[] = { Collection1, Collection2, Collection3 };