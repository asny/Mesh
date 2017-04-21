//
//  ID.hpp
//  Spider
//
//  Created by Asger Nyman Christiansen on 10/08/16.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#pragma once
#include <vector>

namespace mesh
{
    class ID
    {
        int id;
        
    protected:
        ID* previous = nullptr;
        ID* next = nullptr;
        
        ID(int _id, ID* _previous) : id(_id), previous(_previous)
        {
            if(previous)
                _previous->next = this;
        }
        
    public:
        const int key() const { return id; }
        friend bool operator<(const ID& a, const ID& b) { return a.id < b.id; }
        friend bool operator>(const ID& a, const ID& b) { return a.id > b.id; }
        friend bool operator<=(const ID& a, const ID& b) { return a.id <= b.id; }
        friend bool operator>=(const ID& a, const ID& b) { return a.id >= b.id; }
        friend bool operator==(const ID& a, const ID& b) { return a.id == b.id; }
        friend bool operator!=(const ID& a, const ID& b) { return a.id != b.id; }
    };
    
    class EdgeID;
    class FaceID;
    
    class VertexID : public ID
    {
        friend class Mesh;
        friend class FaceID;
        
        std::vector<const FaceID*> neighbouring_faces = std::vector<const FaceID*>();
        
        VertexID(int id, ID* previous) : ID(id, previous)
        {
            
        }
        
    public:
        const VertexID* next() const
        {
            return static_cast<VertexID*>(ID::next);
        }
        
        const std::vector<const FaceID*>& faces() const
        {
            return neighbouring_faces;
        }
    };
    
    class EdgeID : public ID
    {
        friend class Mesh;
        
        VertexID* vertex1;
        VertexID* vertex2;
        
        EdgeID(int id, EdgeID* previous, VertexID* _vertex1, VertexID* _vertex2)
            : ID(id, previous), vertex1(_vertex1), vertex2(_vertex2)
        {
            
        }
        
    public:
        const EdgeID* next() const
        {
            return static_cast<EdgeID*>(ID::next);
        }
        
        const VertexID* v1() const
        {
            return vertex1;
        }
        
        const VertexID* v2() const
        {
            return vertex2;
        }
    };
    
    class FaceID : public ID
    {
        friend class Mesh;
        
        VertexID* vertex1;
        VertexID* vertex2;
        VertexID* vertex3;
        
        FaceID(int id, FaceID* previous, VertexID* _vertex1, VertexID* _vertex2, VertexID* _vertex3)
        : ID(id, previous), vertex1(_vertex1), vertex2(_vertex2), vertex3(_vertex3)
        {
            vertex1->neighbouring_faces.push_back(this);
            vertex2->neighbouring_faces.push_back(this);
            vertex3->neighbouring_faces.push_back(this);
        }
        
    public:
        const FaceID* next() const
        {
            return static_cast<FaceID*>(ID::next);
        }
        
        const VertexID* v1() const
        {
            return vertex1;
        }
        
        const VertexID* v2() const
        {
            return vertex2;
        }
        
        const VertexID* v3() const
        {
            return vertex3;
        }
    };
}


namespace std
{
    template <>
    struct hash<mesh::VertexID>
    {
        std::size_t operator()(const mesh::VertexID& k) const
        {
            return std::hash<int>()(k.key());
        }
    };
    
    template <>
    struct hash<mesh::EdgeID>
    {
        std::size_t operator()(const mesh::EdgeID& k) const
        {
            return std::hash<int>()(k.key());
        }
    };
    
    template <>
    struct hash<mesh::FaceID>
    {
        std::size_t operator()(const mesh::FaceID& k) const
        {
            return std::hash<int>()(k.key());
        }
    };
}
