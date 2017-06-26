//
//  Attribute.hpp
//  Spider
//
//  Created by Asger Nyman Christiansen on 30/07/16.
//  Copyright © 2016 Asger Nyman Christiansen. All rights reserved.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

namespace mesh
{
    template <class IDType, class ValueType>
    class Attribute
    {
    public:
        
        const ValueType& at(const IDType& id) const
        {
            return mapping.at(id);
        }
        
        const ValueType& at(const IDType* id) const
        {
            return at(*id);
        }
        
        ValueType& at(const IDType& id)
        {
            auto it = mapping.find(id);
            if (it == mapping.end())
            {
                it = mapping.insert(std::make_pair(id, ValueType())).first;
            }
            return it->second;
        }
        
        ValueType& at(const IDType* id)
        {
            return at(*id);
        }
        
        void clear()
        {
            mapping.clear();
        }
        
        bool contains(const IDType* id)
        {
            return mapping.find(*id) != mapping.end();
        }
        
        bool contains(const IDType& id)
        {
            return mapping.find(id) != mapping.end();
        }
        
        unsigned long size()
        {
            return mapping.size();
        }
        
    private:
        std::unordered_map<IDType, ValueType> mapping;
    };
}
