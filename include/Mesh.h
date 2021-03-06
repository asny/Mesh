//
//  Mesh.hpp
//  Spider
//
//  Created by Asger Nyman Christiansen on 26/07/16.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include "Attribute.h"
#include <vector>
#include "glm.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "ID.h"

namespace mesh
{
    
    class Mesh
    {
        VertexID* start_vertex = nullptr;
        VertexID* end_vertex = nullptr;
        
        EdgeID* start_edge = nullptr;
        EdgeID* end_edge = nullptr;
        
        FaceID* start_face = nullptr;
        FaceID* end_face = nullptr;
        
        int no_vertices = 0;
        int no_edges = 0;
        int no_faces = 0;
        
        std::shared_ptr<Attribute<VertexID, glm::vec3>> position_attribute = std::make_shared<Attribute<VertexID, glm::vec3>>();
        std::shared_ptr<Attribute<VertexID, glm::vec3>> normal_attribute = nullptr;
        
    public:
        Mesh()
        {
            
        }
        
        ~Mesh()
        {
            for(auto vertex = vertices_begin(); vertex != vertices_end(); )
            {
                auto temp = vertex->next();
                delete vertex;
                vertex = temp;
            }
            for(auto edge = edges_begin(); edge != edges_end(); )
            {
                auto temp = edge->next();
                delete edge;
                edge = temp;
            }
            for(auto face = faces_begin(); face != faces_end(); )
            {
                auto temp = face->next();
                delete face;
                face = temp;
            }
        }
        
        VertexID* create_vertex()
        {
            end_vertex = new VertexID(no_vertices, end_vertex);
            no_vertices++;
            if(!start_vertex)
                start_vertex = end_vertex;
            return end_vertex;
        }
        
        VertexID* create_vertex(const glm::vec3& position)
        {
            auto vertex = create_vertex();
            position_attribute->at(vertex) = position;
            return vertex;
        }
        
        EdgeID* create_edge(VertexID* vertex1, VertexID* vertex2)
        {
            end_edge = new EdgeID(no_edges, end_edge, vertex1, vertex2);
            no_edges++;
            if(!start_edge)
                start_edge = end_edge;
            return end_edge;
        }
        
        FaceID* create_face(VertexID* vertex1, VertexID* vertex2, VertexID* vertex3)
        {
            end_face = new FaceID(no_faces, end_face, vertex1, vertex2, vertex3);
            no_faces++;
            if(!start_face)
                start_face = end_face;
            return end_face;
        }
        
        const std::shared_ptr<Attribute<VertexID, glm::vec3>>& position()
        {
            return position_attribute;
        }
        
        std::shared_ptr<const Attribute<VertexID, glm::vec3>> position() const
        {
            return position_attribute;
        }
        
        void transform(glm::mat4 transformation)
        {
            for(auto vertex = vertices_begin(); vertex != vertices_end(); vertex = vertex->next())
            {
                glm::vec3 pos = position_attribute->at(vertex);
                glm::vec4 transformed_pos = transformation * glm::vec4(pos, 1.);
                position_attribute->at(vertex) = glm::vec3(transformed_pos.x, transformed_pos.y, transformed_pos.z);
            }
        }
        
        float area(const FaceID* facet) const
        {
            glm::vec3 p1 = position_attribute->at(facet->v1());
            glm::vec3 p2 = position_attribute->at(facet->v2());
            glm::vec3 p3 = position_attribute->at(facet->v3());
            return 0.5f * length(cross(p2 - p1, p3 - p1));
        }
        
        glm::vec3 center(const FaceID* facet) const
        {
            glm::vec3 p1 = position_attribute->at(facet->v1());
            glm::vec3 p2 = position_attribute->at(facet->v2());
            glm::vec3 p3 = position_attribute->at(facet->v3());
            return (p1 + p2 + p3) / 3.f;
        }
        
        glm::vec3 normal(const FaceID* facet) const
        {
            glm::vec3 p1 = position_attribute->at(facet->v1());
            glm::vec3 p2 = position_attribute->at(facet->v2());
            glm::vec3 p3 = position_attribute->at(facet->v3());
            return normalize(cross(p2 - p1, p3 - p1));
        }
        
        glm::vec3 normal(const VertexID* vertex) const
        {
            auto n = glm::vec3(0., 0., 0.);
            for (auto face : vertex->faces()) {
                n += normal(face);
            }
            return normalize(n);
        }
        
        std::shared_ptr<Attribute<VertexID, glm::vec3>> normal()
        {
            if(!normal_attribute)
            {
                update_normals();
            }
            return normal_attribute;
        }
        
        void update_normals()
        {
            if(!normal_attribute)
            {
                normal_attribute = std::make_shared<Attribute<VertexID, glm::vec3>>();
            }
            for (auto vertex = vertices_begin(); vertex != vertices_end(); vertex = vertex->next())
            {
                normal_attribute->at(vertex) = normal(vertex);
            }
        }
        
        const VertexID* vertices_begin() const
        {
            return start_vertex;
        }
        
        const VertexID* vertices_end() const
        {
            return nullptr;
        }
        
        const EdgeID* edges_begin() const
        {
            return start_edge;
        }
        
        const EdgeID* edges_end() const
        {
            return nullptr;
        }
        
        const FaceID* faces_begin() const
        {
            return start_face;
        }
        
        const FaceID* faces_end() const
        {
            return nullptr;
        }
        
        int get_no_vertices() const
        {
            return no_vertices;
        }
        
        int get_no_edges() const
        {
            return no_edges;
        }
        
        int get_no_faces() const
        {
            return no_faces;
        }
    };
}
