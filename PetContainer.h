
#pragma once
#include "PetBase.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

template<typename T>
class PetContainer {
    static_assert(std::is_base_of_v<PetBase, T>, "T must inherit from PetBase");

private:
    std::vector<std::unique_ptr<T>> pets;

public:
    void add(std::unique_ptr<T> pet) {
        pets.push_back(std::move(pet));
    }

    void sortByAge() {
        std::sort(pets.begin(), pets.end(),
            [](const auto& a, const auto& b) { return a->getAge() < b->getAge(); });
    }

    template<typename Predicate>
    std::vector<const T*> findIf(Predicate pred) const {
        std::vector<const T*> result;
        for (const auto& pet : pets) {
            if (pred(pet.get())) {
                result.push_back(pet.get());
            }
        }
        return result;
    }

    size_t size() const { return pets.size(); }

    void displayAll() const {
        for (const auto& pet : pets) {
            pet->showStatus();
        }
    }
};

// явна€ инстанциаци€ дл€ MagicalPet
template class PetContainer<MagicalPet>;