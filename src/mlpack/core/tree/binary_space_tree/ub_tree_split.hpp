/**
 * @file ub_tree_split.hpp
 * @author Mikhail Lozhnikov
 *
 * Definition of UBTreeSplit, a class that splits the space according
 * to the median address of points contained in the node.
 */
#ifndef MLPACK_CORE_TREE_BINARY_SPACE_TREE_UB_TREE_SPLIT_HPP
#define MLPACK_CORE_TREE_BINARY_SPACE_TREE_UB_TREE_SPLIT_HPP

#include <mlpack/core.hpp>
#include "../address.hpp"

namespace mlpack {
namespace tree /** Trees and tree-building procedures. */ {

template<typename BoundType, typename MatType = arma::mat>
class UBTreeSplit
{
 public:
  //! The type of a one-dimensional address.
  typedef typename std::conditional<sizeof(typename MatType::elem_type) * CHAR_BIT <= 32,
                                    uint32_t,
                                    uint64_t>::type AddressElemType;

  /**
   * Split the node according to the median address of points contained in the
   * node.
   *
   * @param bound The bound used for this node.
   * @param data The dataset used by the binary space tree.
   * @param begin Index of the starting point in the dataset that belongs to
   *    this node.
   * @param count Number of points in this node.
   * @param splitCol The index at which the dataset is divided into two parts
   *    after the rearrangement.
   */
  bool SplitNode(BoundType& bound,
                 MatType& data,
                 const size_t begin,
                 const size_t count,
                 size_t& splitCol);

  bool SplitNode(BoundType& bound,
                 MatType& data,
                 const size_t begin,
                 const size_t count,
                 size_t& splitCol,
                 std::vector<size_t>& oldFromNew);

 private:
  //! This vector contains addresses of all points in the dataset.
  std::vector<std::pair<arma::Col<AddressElemType>, size_t>> addresses;

  /**
   * Calculate addresses for all points in the dataset.
   *
   * @param data The dataset used by the binary space tree.
   */
  void InitializeAddresses(const MatType& data);

  /**
   * Calculate addresses for all points in the dataset.
   *
   * @param data The dataset used by the binary space tree.
   * @param count Number of points in this node.
   */
  void PerformSplit(MatType& data,
                       const size_t count);

  void PerformSplit(MatType& data,
                       const size_t count,
                       std::vector<size_t>& oldFromNew);

  //! A comparator for sorting addresses.
  static bool ComparePair(
      const std::pair<arma::Col<AddressElemType>, size_t>& p1,
      const std::pair<arma::Col<AddressElemType>, size_t>& p2)
  {
    return bound::addr::CompareAddresses(p1.first, p2.first) < 0;
  }
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "ub_tree_split_impl.hpp"

#endif
