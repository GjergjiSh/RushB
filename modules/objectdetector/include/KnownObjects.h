#ifndef KNOWN_OBJECTS_H
#define KNOWN_OBJECTS_H

static const int FOCAL_LENGTH = 456;

#include <iostream>

class KnownObject {

public:
    ~KnownObject() = default;

    KnownObject(int id, std::string name, float known_height, float known_width) :
    id(id), name(name), known_height(known_height), known_width(known_width) {}

    float Get_Distance(float px_height) { return  ((known_height * FOCAL_LENGTH) / px_height); }

    int32_t id;
    std::string name;
    float known_height;
    float known_width;
};

#endif /* KNOWN_OBJECTS_H */