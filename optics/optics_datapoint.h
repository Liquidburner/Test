/* 
 * Author: Florian
 * Date: 29.06.2015
 * 
 * Members:
 * 	vFeatures: data-vector
 * 	vDistances: vDistances to other datapoints
 * 	state: Current state in the Clustering-process
 * 	ID: Unique ID for the data-point
 * 	reachabilityDist: distance
 * 	clusterID: ID for the Cluster, the data-point belongs to
 * 		 initialy set to -999
 * 	clusterName: Name of the Cluster, the data-poitn belongs to
 * 		intitaly set to ""
 */

#ifndef OPTICS_DATAPOINT_H
#define OPTICS_DATAPOINT_H


#include "datapoint.h"
#include <limits>


namespace dataP{
  
class OpticsDatapoint : public Datapoint {

public:
  
  OpticsDatapoint(void) = default;
  OpticsDatapoint(const real_t* featureArray, unsigned int mfeature_size);
  virtual ~OpticsDatapoint(void);

  // Getter methods
  const real_t & getReachabilityDist(void) const;
  const real_t & getCoreDist(void) const;
  const real_t & getTmpDist(void) const;
  const bool & getSeedState(void) const;

  
  // Setter methods
  void setReachabilityDist(const real_t &d);
  void setCoreDist(const real_t &d);
  void setSeedState(const bool & state);
  void setTmpDist(const real_t & d);
  
  const static real_t INF;
  
private:

  real_t reachabilityDist;
  real_t coreDist;
  real_t tmpDist;
  bool isSeed;
  
};

// Custom compare operator for inverted heap structure in ClusterOrdering
struct compareOpticsDatapoints {
  bool operator()(const OpticsDatapoint * lhs, const OpticsDatapoint * rhs) const;
};

// Custom compare operator for inverted heap structure in ClusterOrdering
struct compareOpticsDatapoints_by_tmpDist {
  bool operator()(const OpticsDatapoint * lhs, const OpticsDatapoint * rhs) const;
};

/*
 * ClusterOrdering:
 * 	ids: vector with id's of clustered datapoints
 * 	reachabilityDists: matching reachabilityDistances for clustered datapoints
 */


struct ClusterOrdering{
  
  std::vector< unsigned int > ids;
  std::vector< real_t > reachabilityDists;
  
  inline void push_back( const unsigned int & eID, const real_t & eRD )
  {
    ids.push_back(eID);
    reachabilityDists.push_back(eRD);
  }
  
  inline void push_back( const dataP::OpticsDatapoint & d )
  {
    ids.push_back(d.getID());
    reachabilityDists.push_back(d.getReachabilityDist());
  }
  
  inline unsigned int size(void) const
  {
    return ids.size();
  }
  
};



}
#endif
