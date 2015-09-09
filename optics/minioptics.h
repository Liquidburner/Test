#ifndef MINIOPTICS_H
#define MINIOPTICS_H

#include "optics_datapoint.h"
#include "dataheap.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <boost/heap/fibonacci_heap.hpp>


namespace clusterAlg{

class MiniOPTICS{
  
public:
  
  MiniOPTICS(const real_t* dataArray, const real_t* distMatArray, unsigned int dataSize, unsigned int dataDim, real_t epsilon);
  virtual ~MiniOPTICS(void);
    
  MiniOPTICS(const MiniOPTICS & ) = delete;			// Delete Copy-constructor
  MiniOPTICS & operator= ( const MiniOPTICS & ) = delete;	// Delete assignment-operator
  MiniOPTICS & operator= ( MiniOPTICS && ) = delete; 		// Delete Move-assignment-operator

  // Main application methods 
  void run(void);
  void setStartIdx(const unsigned int & start);
  void updateClusterIDs(const real_t & threshold);
  
  // show methods
  void showClustering(void) const;
  void showInfo(void) const;
  
  // Getter methods
  const dataP::ClusterOrdering & getClusterOrder(void) const;
  const std::vector< unsigned int > & getClusterOrderIDs(void) const;
  const std::vector< real_t > & getClusterOrderDistances(void) const;
  const std::vector< int > & getClusterIDs(void) const;
  template <typename T> std::vector< T > getLabels(void) const;
  
private:
  
  // Data
  std::vector< dataP::OpticsDatapoint > Data;
  unsigned int dataSize;
  unsigned int dataDim;
  unsigned int startIdx;
  bool useStartIdx;
  unsigned int numProcessedIDs;
  bool clusterValley;
  unsigned int currentClusterID;

  // Algorithm specs
  real_t epsilon;
  real_t clusterThreshold;

  // DistanceMatrix
  const real_t* distMatP;
  bool calcDistMatB;
  
private:
  
  // Range query function with respect to epsilon and minPts
  std::vector< dataP::OpticsDatapoint* > RQ(const unsigned int &i);
  real_t readDist(const unsigned int &i, const unsigned int &j);
  real_t calcDist(const unsigned int &i, const unsigned int &j);
  real_t getDistance(const unsigned int &i, const unsigned int &j);


  // Expand a new cluster
  void expandClusterOrder( dataP::OpticsDatapoint & d );
  void addToCluster(const dataP::OpticsDatapoint & d);
  
  // Holds seed list with top element pointing to the smallest reachabilityDist
  Heap minSortedHeap;

  // Clusterordering vector < data-ID, data-reachabilityDist >
  dataP::ClusterOrdering clusterOrder;
  std::vector< int > clusterIDs;
  
};

}

#endif
