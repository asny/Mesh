//
//  MeshCreator.h
//  Spider
//
//  Created by Asger Nyman Christiansen on 09/12/2016.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

class MeshCreator
{
    
public:
    
    static void load_from_obj(std::string file_path, mesh::Mesh& geometry, mesh::Attribute<mesh::VertexID, glm::vec2>& uv_attribute, mesh::Attribute<mesh::VertexID, glm::vec3>& normal_attribute)
    {
        std::vector<glm::vec3> positions, normals;
        std::vector<glm::vec2> uv_coordinates;
        std::vector<unsigned int> position_indices, uv_coordinates_indices, normal_indices;
        
        bool load_success = load_obj(file_path, positions, position_indices, uv_coordinates, uv_coordinates_indices, normals, normal_indices);
        if(load_success)
        {
            // Create the vertices
            auto mapping = std::map<unsigned int, mesh::VertexID*>();
            for( unsigned int i = 0; i < positions.size(); i++ )
            {
                auto vertex_id = geometry.create_vertex(positions.at(i));
                mapping[i] = vertex_id;
            }
            
            // Create the faces
            for (unsigned int i = 0; i < position_indices.size(); i += 3)
            {
                auto vertex_id1 = mapping[position_indices[i] - 1];
                auto vertex_id2 = mapping[position_indices[i+1] - 1];
                auto vertex_id3 = mapping[position_indices[i+2] - 1];
                geometry.create_face(vertex_id1, vertex_id2, vertex_id3);
            }
            
            // Add the uv coordinate attribute
            if(uv_coordinates.size() > 0 && uv_coordinates_indices.size() > 0)
            {
                for( unsigned int i = 0; i < normals.size(); i++ )
                {
                    // TODO: For now, we only support per vertex attributes
                    uv_attribute.at(mapping[i]) = uv_coordinates.at(i);
                }
            }
            
            // Add the normal attribute
            if(normals.size() > 0 && normal_indices.size() > 0)
            {
                for( unsigned int i = 0; i < normals.size(); i++ )
                {
                    // TODO: For now, we only support per vertex attributes
                    normal_attribute.at(mapping[i]) = normals.at(i);
                }
            }
        }
    }
    
    static void load_from_obj(std::string file_path, mesh::Mesh& geometry, mesh::Attribute<mesh::VertexID, glm::vec3>& normals)
    {
        mesh::Attribute<mesh::VertexID, glm::vec2> uv_coordinates;
        load_from_obj(file_path, geometry, uv_coordinates, normals);
    }
    
    static void load_from_obj(std::string file_path, mesh::Mesh& geometry, mesh::Attribute<mesh::VertexID, glm::vec2>& uv_coordinates)
    {
        mesh::Attribute<mesh::VertexID, glm::vec3> normals;
        load_from_obj(file_path, geometry, uv_coordinates, normals);
    }
    
    static void load_from_obj(std::string file_path, mesh::Mesh& geometry)
    {
        mesh::Attribute<mesh::VertexID, glm::vec2> uv_coordinates;
        mesh::Attribute<mesh::VertexID, glm::vec3> normals;
        load_from_obj(file_path, geometry, uv_coordinates, normals);
    }
    
    static std::shared_ptr<mesh::Mesh> create_box(bool view_from_inside)
    {
        auto mesh = std::shared_ptr<mesh::Mesh>(new mesh::Mesh());
        
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
    
    static std::shared_ptr<mesh::Mesh> create_quad()
    {
        auto mesh = std::make_shared<mesh::Mesh>();
        
        mesh::VertexID* v1 = mesh->create_vertex(glm::vec3(0., 0., 0.));
        mesh::VertexID* v2 = mesh->create_vertex(glm::vec3(0., 1., 0.));
        mesh::VertexID* v3 = mesh->create_vertex(glm::vec3(1., 1., 0.));
        mesh::VertexID* v4 = mesh->create_vertex(glm::vec3(1., 0., 0.));
        mesh->create_face(v1, v3, v2);
        mesh->create_face(v3, v1, v4);
        
        return mesh;
    }
    
    static std::shared_ptr<mesh::Mesh> create_quad(std::shared_ptr<mesh::Attribute<mesh::VertexID, glm::vec3>>& normals)
    {
        auto mesh = create_quad();
        
        // Normals
        for(auto vertexId = mesh->vertices_begin(); vertexId != mesh->vertices_end(); vertexId = vertexId->next())
        {
            normals->at(vertexId) = glm::vec3(0., 0., 1.);
        }
        
        return mesh;
    }
    
private:
    
    
    static bool load_obj(std::string file_path, std::vector<glm::vec3>& positions, std::vector<unsigned int>& position_indices,
                         std::vector<glm::vec2>& uv_coordinates, std::vector<unsigned int>& uv_coordinate_indices,
                         std::vector<glm::vec3>& normals, std::vector<unsigned int>& normal_indices)
    {
        std::string line;
        std::ifstream myfile(file_path);
        if (!myfile.is_open())
        {
            return false;
        }
        
        while ( getline(myfile, line) )
        {
            std::stringstream stream(line);
            std::string header;
            stream >> header;
            if ( header.compare("v") == 0 )
            {
                glm::vec3 position;
                std::string value;
                for (int i = 0; i < 3; i++)
                {
                    stream >> value;
                    position[i] = stod(value);
                }
                positions.push_back(position);
            }
            else if ( header.compare("vt") == 0 )
            {
                glm::vec2 uv_coordinate;
                std::string value;
                for (int i = 0; i < 2; i++)
                {
                    stream >> value;
                    uv_coordinate[i] = stod(value);
                }
                uv_coordinates.push_back(uv_coordinate);
            }
            else if ( header.compare("vn") == 0 )
            {
                glm::vec3 normal;
                std::string value;
                for (int i = 0; i < 3; i++)
                {
                    stream >> value;
                    normal[i] = stod(value);
                }
                normals.push_back(normal);
            }
            else if ( header.compare("f") == 0 )
            {
                for(int i = 0; i < 3; i++)
                {
                    std::string indices;
                    stream >> indices;
                    std::stringstream stream2(indices);
                    std::string value;
                    int j = 0;
                    while (getline(stream2, value, '/'))
                    {
                        if(value.length() != 0)
                        {
                            if(j % 3 == 0)
                            {
                                position_indices.push_back(stoi(value));
                            }
                            else if(j % 3 == 1)
                            {
                                uv_coordinate_indices.push_back(stoi(value));
                            }
                            else if(j % 3 == 2)
                            {
                                normal_indices.push_back(stoi(value));
                            }
                        }
                        j++;
                    }
                }
            }
        }
        myfile.close();
        
        return true;
    }
};
