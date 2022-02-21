#include "DistanceEstimator.h"

int DistanceEstimator::Init(const char* config_path)
{
    try {
        this->config.load_file(config_path);
        std::cout << "Distance estimator loaded config file from: " << config_path << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "Distance estimator failed to load config file "
                  << ex.what()
                  << std::endl;
        return -1;
    }

    Register_Objects();

    return 0;
}

// Parse the config and add the create/register known objects from it
void DistanceEstimator::Register_Objects()
{
    // Known Objects node
    pugi::xml_node known_objects = config.child("Config").child("KnownObjects");

    // Loop through each node in Known Objects
    for (pugi::xml_node object = known_objects.first_child(); object; object = object.next_sibling()) {

        // Get the attributes
        int id = object.attribute("id").as_int();
        std::string name = object.attribute("name").as_string();
        float height = object.attribute("height").as_float();
        float width = object.attribute("width").as_float();

        std::cout << "Distance Estimator Registered object with: " << std::endl;

        std::cout << "id: " << id << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "height: " << height << std::endl;
        std::cout << "width: " << width << std::endl;

        // Create and register a known object
        std::shared_ptr<KnownObject> known_object = std::make_shared<KnownObject>(id, name, height, width);
        this->known_objects.emplace(std::make_pair(known_object->id, known_object));
    }
}

// Remove a known object from the registered known objects vector
void DistanceEstimator::Unregister_Object(std::shared_ptr<KnownObject> known_object)
{
    this->known_objects.erase(known_object->id);
}


/******************************************************************************************************************
 * @note: ID of the bounding box MUST match with the id of the object declared in the estimator config xml file
 ******************************************************************************************************************/
// Trigger the correct known objects distance calc method.
float DistanceEstimator::Estimate_Distance(DetectionUtils::tBoundingBox bounding_box)
{
    return (this->known_objects.at(bounding_box.id)->Get_Distance(bounding_box.roi.height));
}

