//
//  Created by Asger Nyman Christiansen on 25/04/2017.
//  Copyright © 2017 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include "Mesh.h"
#include <glm/gtx/intersect.hpp>

namespace mesh
{
    class Search
    {
    public:
        struct Result {
            const FaceID* face_id;
            const glm::vec3 point;
            
            bool is_a_hit()
            {
                return face_id != nullptr;
            }
        };
        
        static Result closest_face(const Mesh& mesh, const glm::vec3& origin, const glm::vec3& direction)
        {
            for(auto face = mesh.faces_begin(); face != mesh.faces_end(); face = face->next())
            {
                glm::vec3 p1 = mesh.position()->at(face->v1());
                glm::vec3 p2 = mesh.position()->at(face->v2());
                glm::vec3 p3 = mesh.position()->at(face->v3());
                glm::vec3 output;
                if(glm::intersectRayTriangle(origin, direction, p1, p2, p3, output))
                {
                    glm::vec3 point = p1 + output.x * (p2 - p1) + output.y * (p3 - p1);
                    return Result {face, point};
                }
            }
            return Result();
        }
        
    };
}

