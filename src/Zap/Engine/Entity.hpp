/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Entity.hpp
*/

#pragma once

#include <Zap/NonCopyable.hpp>
#include <Zap/Types.hpp>

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace zap {

class Component
{
    public:
        virtual ~Component() = default;
};

class EntityCounter : public abstract::NonCopyable
{
    public:
        static u32 increment(void);
        static void reset(void);
        static u32 count(void);

        static u32 _count;
};

class Entity
{
    public:
        explicit Entity();
        explicit Entity(const std::string &name);

        template<typename T>
        std::shared_ptr<T> get() const
        {
            const auto it = components.find(std::type_index(typeid(T)));

            if (it != components.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }
            return nullptr;
        }

        template<typename T>
        bool has() const
        {
            return components.count(std::type_index(typeid(T))) > 0;
        }

        template<typename T>
        Entity &add(std::shared_ptr<T> component)
        {
            const std::type_index index(typeid(T));

            if (has<T>()) {
                remove<T>();
            }
            components[index] = component;
            // if (onComponentAdded)
            //     onComponentAdded(*this, index);
            return *this;
        }

        template<typename T>
        std::shared_ptr<T> remove()
        {
            const std::type_index index(typeid(T));
            const auto it = components.find(index);

            if (it != components.end()) {
                const auto removed = std::dynamic_pointer_cast<T>(it->second);

                components.erase(it);
                // if (onComponentRemoved)
                //     onComponentRemoved(*this, index);
                return removed;
            }
            return nullptr;
        }

        std::vector<std::shared_ptr<Component>> getAll() const noexcept;
        const std::string getName() const noexcept;

    private:
        std::string _name;
        std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};

}// namespace zap
