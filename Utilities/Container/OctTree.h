#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <glm\glm.hpp>

#include "..\Helper\Global.h"
#include "..\Enumerators\Axis.h"

Template
using Value = std::function<float(T)>;
Template
using Distribute = std::function<int(T, float)>;

Template
class OctTree final {
public:
                            OctTree                 () = default;
                            ~OctTree                ();

    const Value<T>&         getValueMethod          (const Axis&) const;
    const Value<T>&         getMinMethod            (const Axis&) const;
    const Value<T>&         getMaxMethod            (const Axis&) const;
    const Distribute<T>&    getDistributeMethod     (const Axis&) const;
    const unsigned int      getBranchStrength       () const;
    const bool              getBranchByMedian       () const;

    void                    setValueMethod          (const Axis&, const Value<T>&);
    void                    setMinMethod            (const Axis&, const Value<T>&);
    void                    setMaxMethod            (const Axis&, const Value<T>&);
    void                    setDistributeMethod     (const Axis&, const Distribute<T>&);
    void                    setBranchStrength       (const unsigned int);
    void                    setBranchByMedian       (const bool = true);

    void                    Clear                   ();
    void                    MinMax                  ();
    void                    Populate                (const T* const, const unsigned int);
    void                    Collect                 (const glm::vec3&, std::vector<T>&);
private:
    class Branch final {
    public:
                            Branch                  (OctTree* const ,const T* const, const unsigned int);
                            ~Branch                 ();

        const glm::vec3&    getMin                  () const;
        const glm::vec3&    getMax                  () const;

        void                MinMax                  ();
        void                Collect                 (const glm::vec3&, std::vector<T>&);
    private:
        void                Sort                    (std::vector<T>&, const Axis&);
        void                Split                   (const std::vector<T>&, const Axis&, std::vector<T>&, std::vector<T>&);

        OctTree* const      m_master                { nullptr };
        Branch*             m_children[8];
        std::vector<T>      m_data;

        glm::vec3           m_min                   { 0.0f };
        glm::vec3           m_max                   { 0.0f };
    };

    Branch*                 m_root                  { nullptr };

    unsigned int            m_branchStrength        { 16 };
    bool                    m_branchByMedian        { false };

    Value<T>                m_valueMethod[3];
    Value<T>                m_minMethod[3];
    Value<T>                m_maxMethod[3];
    Distribute<T>           m_distributeMethod[3];
};

#pragma region OctTree

Template
OctTree<T>::~OctTree() {
    Clear();
}

Template
const Value<T>& OctTree<T>::getValueMethod(const Axis& axis) const {
    return m_valueMethod[(unsigned int)axis];
}

Template
const Value<T>& OctTree<T>::getMinMethod(const Axis& axis) const {
    return m_minMethod[(unsigned int)axis];
}

Template
const Value<T>& OctTree<T>::getMaxMethod(const Axis& axis) const {
    return m_maxMethod[(unsigned int)axis];
}

Template
const Distribute<T>& OctTree<T>::getDistributeMethod(const Axis& axis) const {
    return m_distributeMethod[(unsigned int)axis];
}

Template
const unsigned int OctTree<T>::getBranchStrength() const {
    return m_branchStrength;
}

Template
const bool OctTree<T>::getBranchByMedian() const {
    return m_branchByMedian;
}

Template
void OctTree<T>::setValueMethod(const Axis& axis, const Value<T>& method) {
    m_valueMethod[(unsigned int)axis] = method;
}

Template
void OctTree<T>::setMinMethod(const Axis& axis, const Value<T>& method) {
    m_minMethod[(unsigned int)axis] = method;
}

Template
void OctTree<T>::setMaxMethod(const Axis& axis, const Value<T>& method) {
    m_maxMethod[(unsigned int)axis] = method;
}

Template
void OctTree<T>::setDistributeMethod(const Axis& axis, const Distribute<T>& method) {
    m_distributeMethod[(unsigned int)axis] = method;
}

Template
void OctTree<T>::setBranchStrength(const unsigned int strength) {
    m_branchStrength = strength;
}

Template
void OctTree<T>::setBranchByMedian(const bool val) {
    m_branchByMedian = val;
}

Template
void OctTree<T>::Clear() {
    delete m_root;
    m_root = nullptr;
}

Template
void OctTree<T>::MinMax() {
    m_root->MinMax();
}

Template
void OctTree<T>::Populate(const T* const ptr, const unsigned int count) {
    Clear();
    m_root = new Branch(this, ptr, count);
    m_root->MinMax();
}

Template
void OctTree<T>::Collect(const glm::vec3& point, std::vector<T>& list) {
    m_root->Collect(point, list);

    std::sort(list.begin(), list.end());
    list.erase(unique(list.begin(), list.end()), list.end());
}

#pragma endregion
#pragma region Branch

Template
OctTree<T>::Branch::Branch(OctTree* const master, const T* const ptr, const unsigned int count) : m_master(master) {
    for (unsigned int i = 0; i < count; i++) {
        m_data.push_back(ptr[i]);
    }
    if (count > m_master->getBranchStrength()) {
        std::vector<T> x_split[2];
        std::vector<T> y_split[2];
        std::vector<T> z_split[2];

        Sort(m_data, Axis::X);
        Split(m_data, Axis::X, x_split[0], x_split[1]);

        if (!(x_split[0].size() == count || x_split[1].size() == count)) {
            unsigned int index = 0;
            for (unsigned int i = 0; i < 2; i++) {
                Sort(x_split[i], Axis::Y);
                Split(x_split[i], Axis::Y, y_split[0], y_split[1]);

                for (unsigned int j = 0; j < 2; j++, index++) {
                    Sort(y_split[j], Axis::Z);
                    Split(y_split[j], Axis::Z, z_split[0], z_split[1]);

                    m_children[index++] = z_split[0].empty() ?
                        nullptr :
                        new Branch(master, z_split[0].data(), (unsigned int)z_split[0].size());
                    m_children[index] = z_split[1].empty() ?
                        nullptr :
                        new Branch(master, z_split[1].data(), (unsigned int)z_split[1].size());
                }
            }
            m_data.clear();
        }
    }
}

Template
OctTree<T>::Branch::~Branch() {
    for (Branch* child : m_children) {
        delete child;
        child = nullptr;
    }
}

Template
const glm::vec3& OctTree<T>::Branch::getMin() const {
    return m_min;
}

Template
const glm::vec3& OctTree<T>::Branch::getMax() const {
    return m_max;
}

Template
void OctTree<T>::Branch::MinMax() {
    glm::vec3 min { std::numeric_limits<float>::max() };
    glm::vec3 max { -std::numeric_limits<float>::max() };
    std::vector<glm::vec3> minList;
    std::vector<glm::vec3> maxList;
    
    if (m_data.empty()) {
        for (Branch* const ptr : m_children) {
            if (ptr) {
                ptr->MinMax();
                minList.push_back(ptr->getMin());
                maxList.push_back(ptr->getMax());
            }
        }
    } else {
        for (const T& it : m_data) {
            minList.push_back({
                m_master->getMinMethod(Axis::X)(it),
                m_master->getMinMethod(Axis::Y)(it),
                m_master->getMinMethod(Axis::Z)(it) });
            maxList.push_back({
                m_master->getMaxMethod(Axis::X)(it),
                m_master->getMaxMethod(Axis::Y)(it),
                m_master->getMaxMethod(Axis::Z)(it) });
        }
    }

    for (const glm::vec3& val : minList) {
        min.x = glm::min(val.x, min.x);
        min.y = glm::min(val.y, min.y);
        min.z = glm::min(val.z, min.z);
    }
    for (const glm::vec3& val : maxList) {
        max.x = glm::max(val.x, max.x);
        max.y = glm::max(val.y, max.y);
        max.z = glm::max(val.z, max.z);
    }

    m_min = min;
    m_max = max;
}

Template
void OctTree<T>::Branch::Collect(const glm::vec3& point, std::vector<T>& list) {
    if (m_min.x <= point.x && m_max.x >= point.x &&
        m_min.y <= point.y && m_max.y >= point.y &&
        m_min.z <= point.z && m_max.z >= point.z) {
        if (m_data.empty()) {
            for (Branch* const ptr : m_children) {
                if (ptr) {
                    ptr->Collect(point, list);
                }
            }
        } else {
            for (const T& it : m_data) {
                list.push_back(it);
            }
        }
    }
}

Template
void OctTree<T>::Branch::Sort(std::vector<T>& list, const Axis& axis) {
    auto value = m_master->getValueMethod(axis);
    auto method = [&](T i, T j) { return value(i) < value(j); };
    std::sort(list.begin(), list.end(), method);
}

Template
void OctTree<T>::Branch::Split(const std::vector<T>& list, const Axis& axis, std::vector<T>& neg, std::vector<T>& pos) {
    neg.clear();
    pos.clear();
    
    auto value = m_master->getValueMethod(axis);
    Distribute<T> distribute = m_master->getDistributeMethod(axis);

    const float divisor = m_master->getBranchByMedian() ?
        value(list[list.size() / 2]) :
        (value(list.front()) + value(list.back())) / 2;

    for (T it : list) {
        const int state = distribute(it, divisor);
        if (state < 0) {
            neg.push_back(it);
        } else if (state == 0) {
            neg.push_back(it);
            pos.push_back(it);
        } else {
            pos.push_back(it);
        }
    }
}

#pragma endregion