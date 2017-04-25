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
        static const VertexID* closest_vertex(const Mesh& mesh, const glm::vec3& origin, const glm::vec3& direction)
        {
            auto face = Search::closest_face(mesh, origin, direction);
            if(!face)
                return nullptr;
            return face->v1();
        }
        
        static const FaceID* closest_face(const Mesh& mesh, const glm::vec3& origin, const glm::vec3& direction)
        {
            for(auto face = mesh.faces_begin(); face != mesh.faces_end(); face = face->next())
            {
                glm::vec3 p1 = mesh.position()->at(face->v1());
                glm::vec3 p2 = mesh.position()->at(face->v2());
                glm::vec3 p3 = mesh.position()->at(face->v3());
                glm::vec3 output;
                if(glm::intersectRayTriangle(origin, direction, p1, p2, p3, output))
                {
                    return face;
                }
            }
            return nullptr;
        }
        
    };
}

