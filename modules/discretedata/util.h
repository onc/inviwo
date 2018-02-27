/*********************************************************************
 *  Author  : Anke Friederici and Tino Weinkauf
 *  Init    : Thursday, December 14, 2017 - 13:12:35
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include "discretedata/connectivity.h"

namespace inviwo
{
namespace util
{

/** See std::hash_combine implementation from Boost
*/
template <class T>
inline void CombineHash(std::size_t& hash, const T& value)
{
    std::hash<T> hasher;
    hash ^= hasher(value) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
}

/** \class PairHash
*   \brief Functor for pair hashing.
*/
template<typename S, typename T>
struct PairHash
{
    inline size_t operator()(const std::pair<S, T> & v) const
    {
        size_t hash = 0;
        CombineHash(hash, v.first);
        CombineHash(hash, v.second);
        return hash;
    }
};

inline double tetrahedronVolume(double corners[4][3])
{
    glm::mat4 tet;
    for (int corner = 0; corner < 4; ++corner)
    {
        for (int scalar = 0; scalar < 3; ++scalar)
            tet[corner][scalar] = corners[corner][scalar];
        tet[corner][3] = 1;
    }

    double vol = glm::determinant(tet);
    return abs(vol);
}

} // namespace util
} // namespace
