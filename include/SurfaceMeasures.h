//
//  Created by Asger Nyman Christiansen on 13/05/2017.
//  Copyright © 2017 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include "Mesh.h"

namespace mesh
{
    glm::vec3 center(const Mesh& model) 
    {
        auto pos = glm::vec3(0.f, 0.f, 0.f);
        auto area_sum = 0.f;
        for(auto face = model.faces_begin(); face != model.faces_end(); face = face->next())
        {
            float A = model.area(face);
            pos += model.center(face) * A;
            area_sum += A;
        }
        
        return pos / area_sum;
    }
    
    glm::vec3 min_coordinates(const Mesh& model) 
    {
        auto pos = glm::vec3(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        for(auto vertex = model.vertices_begin(); vertex != model.vertices_end(); vertex = vertex->next())
        {
            glm::vec3 p = model.position()->at(vertex);
            pos.x = std::min(p.x, pos.x);
            pos.y = std::min(p.y, pos.y);
            pos.z = std::min(p.z, pos.z);
        }
        return pos;
    }
    
    glm::vec3 max_coordinates(const Mesh& model) 
    {
        auto pos = glm::vec3(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        for(auto vertex = model.vertices_begin(); vertex != model.vertices_end(); vertex = vertex->next())
        {
            glm::vec3 p = model.position()->at(vertex);
            pos.x = std::max(p.x, pos.x);
            pos.y = std::max(p.y, pos.y);
            pos.z = std::max(p.z, pos.z);
        }
        return pos;
    }
}
