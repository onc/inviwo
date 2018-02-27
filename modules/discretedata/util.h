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
    const glm::dvec3 a(corners[0][0] - corners[1][0], corners[0][1] - corners[1][1], corners[0][2] - corners[1][2]);
    const glm::dvec3 b(corners[0][0] - corners[2][0], corners[0][1] - corners[2][1], corners[0][2] - corners[2][2]);
    const glm::dvec3 c(corners[0][0] - corners[3][0], corners[0][1] - corners[3][1], corners[0][2] - corners[3][2]);

    return fabs(glm::dot(glm::cross(a, b), c) / 6.0);
}

} // namespace util
} // namespace
