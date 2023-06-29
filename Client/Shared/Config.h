#include "pch.h"
#include "Entity.h"
class Config
{
public:
	Entity Entity1;
	Entity Entity2;

    void toJson(json& j) const
    {
        j = json{
            {"Entity1", json{}},
            {"Entity2", json{}}
        };

        Entity1.toJson(j["Entity1"]);
        Entity2.toJson(j["Entity2"]);
    }

    // Function to populate the Config object from JSON
    void fromJson(const json& j)
    {
        if (j.contains("Entity1"))
            Entity1.fromJson(j["Entity1"]);
        if (j.contains("Entity2"))
            Entity2.fromJson(j["Entity2"]);
    }

};
