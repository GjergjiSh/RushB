#ifndef DISTANCE_ESTIMATOR_H
#define DISTANCE_ESTIMATOR_H

#include <iostream>
#include <unordered_map>

#include "KnownObjects.h"
#include <fstream>
#include "DetectionUtils.h"
#include "pugixml.hpp"

class DistanceEstimator {

public:
    DistanceEstimator() = default;
    ~DistanceEstimator() = default;
    std::unordered_map<int, std::shared_ptr<KnownObject>> known_objects;
    int Init(const char* config_path);
    float Estimate_Distance(DetectionUtils::tBoundingBox);

private:
    void Register_Objects();
    void Unregister_Object(std::shared_ptr<KnownObject> known_object);
    pugi::xml_document config;
};

#endif /* DISTANCE_ESTIMATOR_H */