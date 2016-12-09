//
//  MeshCreator.h
//  Spider
//
//  Created by Asger Nyman Christiansen on 09/12/2016.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include "Mesh.h"

class MeshCreator {
    
    
public:
    
    static std::shared_ptr<geogo::Mesh> create_box(bool view_from_inside)
    {
        auto mesh = std::shared_ptr<geogo::Mesh>(new geogo::Mesh());
        
        auto vertexNNP = mesh->create_vertex(glm::vec3(-1.0, -1.0,  1.0));
        auto vertexPPP = mesh->create_vertex(glm::vec3(1.0, 1.0,  1.0));
        auto vertexPNP = mesh->create_vertex(glm::vec3(1.0, -1.0,  1.0));
        auto vertexNPP = mesh->create_vertex(glm::vec3(-1.0, 1.0,  1.0));
        
        auto vertexNNN = mesh->create_vertex(glm::vec3(-1.0, -1.0,  -1.0));
        auto vertexPPN = mesh->create_vertex(glm::vec3(1.0, 1.0,  -1.0));
        auto vertexPNN = mesh->create_vertex(glm::vec3(1.0, -1.0,  -1.0));
        auto vertexNPN = mesh->create_vertex(glm::vec3(-1.0, 1.0,  -1.0));
        
        if(view_from_inside)
        {
            // Front
            mesh->create_face(vertexNNP, vertexPPP, vertexPNP);
            mesh->create_face(vertexPPP, vertexNNP, vertexNPP);
            
            // Top
            mesh->create_face(vertexNPP, vertexPPN, vertexPPP);
            mesh->create_face(vertexPPN, vertexNPP, vertexNPN);
            
            // Back
            mesh->create_face(vertexPNN, vertexNPN, vertexNNN);
            mesh->create_face(vertexNPN, vertexPNN, vertexPPN);
            
            // Bottom
            mesh->create_face(vertexNNN, vertexPNP, vertexPNN);
            mesh->create_face(vertexPNP, vertexNNN, vertexNNP);
            
            // Left
            mesh->create_face(vertexNNN, vertexNPP, vertexNNP);
            mesh->create_face(vertexNPP, vertexNNN, vertexNPN);
            
            // Right
            mesh->create_face(vertexPNP, vertexPPN, vertexPNN);
            mesh->create_face(vertexPPN, vertexPNP, vertexPPP);
        }
        else {
            // Front
            mesh->create_face(vertexNNP, vertexPNP, vertexPPP);
            mesh->create_face(vertexPPP, vertexNPP, vertexNNP);
            
            // Top
            mesh->create_face(vertexNPP, vertexPPP, vertexPPN);
            mesh->create_face(vertexPPN, vertexNPN, vertexNPP);
            
            // Back
            mesh->create_face(vertexPNN, vertexNNN, vertexNPN);
            mesh->create_face(vertexNPN, vertexPPN, vertexPNN);
            
            // Bottom
            mesh->create_face(vertexNNN, vertexPNN, vertexPNP);
            mesh->create_face(vertexPNP, vertexNNP, vertexNNN);
            
            // Left
            mesh->create_face(vertexNNN, vertexNNP, vertexNPP);
            mesh->create_face(vertexNPP, vertexNPN, vertexNNN);
            
            // Right
            mesh->create_face(vertexPNP, vertexPNN, vertexPPN);
            mesh->create_face(vertexPPN, vertexPPP, vertexPNP);
        }
        return mesh;
    }
};
