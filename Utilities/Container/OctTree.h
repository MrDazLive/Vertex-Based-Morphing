#pragma once

#include <vector>
#include <algorithm>
#include <functional>

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
    const Distribute<T>&    getDistributeMethod     (const Axis&) const;
    const unsigned int      getBranchStrength       () const;
    const bool              getBranchByMedian       () const;

    void                    setValueMethod          (const Axis&, const Value<T>&);
    void                    setDistributeMethod     (const Axis&, const Distribute<T>&);
    void                    setBranchStrength       (const unsigned int);
    void                    setBranchByMedian       (const bool = true);

    void                    Clear                   ();
    void                    Populate                (const T* const, const unsigned int);
private:
    class Branch final {
    public:
                            Branch                  (OctTree* const ,const T* const, const unsigned int);
                            ~Branch                 ();
    private:
        void                Sort                    (std::vector<T>&, const Axis&);
        void                Split                   (const std::vector<T>&, const Axis&, std::vector<T>&, std::vector<T>&);

        OctTree* const      m_master                { nullptr };
        Branch*             m_children[8];
        std::vector<T>      m_data;
    };

    Branch*                 m_root                  { nullptr };

    unsigned int            m_branchStrength        { 16 };
    bool                    m_branchByMedian        { false };

    Value<T>                m_valueMethod[3];
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
void OctTree<T>::Populate(const T* const ptr, const unsigned int count) {
    Clear();
    m_root = new Branch(this, ptr, count);
}

#pragma endregion
#pragma region Branch

Template
OctTree<T>::Branch::Branch(OctTree* const master, const T* const ptr, const unsigned int count) : m_master(master) {
    std::vector<T> m_data;
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
    delete[] m_children;
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