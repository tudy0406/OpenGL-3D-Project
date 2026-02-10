//
//  GPSLab1.cpp
//
//  Copyright © 2017 CGIS. All rights reserved.
//

#include "GPSLab1.hpp"

namespace gps {
    glm::vec4 TransformPoint(const glm::vec4 &point)
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 1.0f));
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 transformationMatrix = rotation * translation;

        return transformationMatrix * point;
    }
    
    float ComputeAngle(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        float denom = glm::length(v1) * glm::length(v2);
        if (denom == 0.0f)
            return 0.0f;

        float cosTheta = glm::dot(v1, v2) / denom;

        return glm::acos(cosTheta);
    }
    
    bool IsConvex(const std::vector<glm::vec2> &vertices)
    {
        size_t n = vertices.size();
        if (n < 3) return false;

        float lastCrossZ = 0.0f;

        for (size_t i = 0; i < n; ++i) {
            glm::vec2 A = vertices[i];
            glm::vec2 B = vertices[(i + 1) % n];
            glm::vec2 C = vertices[(i + 2) % n];

            glm::vec2 AB = B - A;
            glm::vec2 BC = C - B;

            float crossZ = AB.x * BC.y - AB.y * BC.x;

            if (i == 0)
                lastCrossZ = crossZ;
            else if (crossZ * lastCrossZ < 0)
                return false;

            if (crossZ != 0)
                lastCrossZ = crossZ;
        }

        return true;
    }
    
    std::vector<glm::vec2> ComputeNormals(const std::vector<glm::vec2> &vertices)
    {
        std::vector<glm::vec2> normalsList;
        float lengthofVec;
        int n = vertices.size();
        for (int i = 0; i < vertices.size(); ++i) {
            glm::vec2 a = vertices[i % n];
            glm::vec2 b = vertices[(i+1) % n];
            glm::vec2 ab = glm::vec2(b.x - a.x, b.y - a.y);

            lengthofVec = glm::length(ab);
            if (lengthofVec != 0){
                normalsList.push_back(glm::vec2(ab.y / lengthofVec, (-1)*ab.x/lengthofVec));
            }
        }
 
        return normalsList;
    }
}
