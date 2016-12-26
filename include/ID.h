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
        
        friend bool operator<(const ID& a, const ID& b) { return a.id < b.id; }
        friend bool operator>(const ID& a, const ID& b) { return a.id > b.id; }
        friend bool operator<=(const ID& a, const ID& b) { return a.id <= b.id; }
        friend bool operator>=(const ID& a, const ID& b) { return a.id >= b.id; }
        friend bool operator==(const ID& a, const ID& b) { return a.id == b.id; }
        friend bool operator!=(const ID& a, const ID& b) { return a.id != b.id; }
    };
    
    class VertexID : public ID
    {
        friend class Mesh;
        
        VertexID(int id, ID* previous) : ID(id, previous)
        {
            
        }
        
    public:
        const VertexID* next() const
        {
            return static_cast<VertexID*>(ID::next);
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
