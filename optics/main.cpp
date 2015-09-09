#include <iostream>
#include <cstdio>

#include "optics.h"
#include "minioptics.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <numeric>
#include <cassert>

void loadData(std::vector< float > & data, std::string dataPath, unsigned int &dim, bool header)
{
  std::string line;
  std::ifstream dataStream ((char*)dataPath.c_str());
  assert(dataStream);
  
  if(header) dataStream >> line;
  
  while( dataStream >> line)
  {
    
    std::string x;
    std::istringstream lineStream (line);
  
    dim = 0;
    while(lineStream){
      if (!getline( lineStream, x, ',' )) break;
      data.push_back(atof(x.c_str()));
      dim++;
    }
  }
  
  dataStream.close();
}

float calcDist(const real_t* x1, const real_t* x2, unsigned int size)
{
  if ( x1 == x2 ){
    throw std::range_error("x1 == x2 in DBSCAN::calcDist(x1, x2)!");
  }
  real_t dist = 0.0;
  for ( unsigned int i = 0; i < size; i++ )
  {
    dist += (x1[i]- x2[i]) * (x1[i] - x2[i]);
  }
  return sqrt( dist );
}

std::vector< float > calcDistances(std::vector< float > &data, unsigned int dim)
{
  int dataSize = data.size()/dim;
  
  //std::cout << "Datasize222: " << data.size() << " dataSize: " << dataSize << std::endl;

  std::vector< float > distMat(dataSize*dataSize);
   
  for(int i = 0; i < dataSize; i++)
  {
    for(int j = i + 1; j < dataSize; j++)
    {
      try {
	distMat[i * dataSize + j] = calcDist(&data[i * dim], &data[j * dim], dim);
      }
      catch ( std::invalid_argument & e ){ std::cout << e.what() << std::endl; }
    } 
  }
  return distMat;
}

int main(void){
  
  
  // Load Data and calculate Distmatrix
  std::string dataPath = "../../tsne_3d.csv";// "../positions.csv";////;//"/home/florian/Data/data/otto/standard/holdout/holdout_traindata.csv";
  std::vector< float > data;
  unsigned int dim;
  loadData(data, dataPath, dim, true);
  
  std::cout << "Datasize: " << data.size()/dim << " Dim: " << dim << std::endl;
  std::vector< float > distMat = calcDistances(data, dim);
  //real_t* distMat = NULL;
  
  
  int minPts = 4;
  float epsilon = 10;//std::numeric_limits<float>::max();//2;
 
 float sum = 0;
 int it = 0;
  for ( auto & i: distMat )
  {
    sum += i;
    it++;
  }
  std::cout << "mean dist: " << sum/it << std::endl;
 
    
  /*
  //for( int s = 0; s < 2; s++ ){
    // Run DBSCAN
    clusterAlg::DBSCAN* dbscan_test = new clusterAlg::DBSCAN(&data[0], &distMat[0], data.size()/dim, dim, minPts, epsilon);
    
    dbscan_test->showInfo();
    
    dbscan_test->run();
    
    dbscan_test->showClustering();
    
    dbscan_test->showInfo();
    
    //for( auto &xx : dbscan_test->getClusterIDs() )
    //{
    //  std::cout << xx << std::endl;
    //}
    
    delete dbscan_test;
    std::cout << "----------------------------------------------------------" << std::endl;

  //}
*/
  

  
  
  for( int s = 0; s < 1; s++ ){
   
    //clusterAlg::MiniOPTICS* op = new clusterAlg::MiniOPTICS(&data[0], NULL, data.size()/dim, dim, epsilon);
    clusterAlg::OPTICS* op = new clusterAlg::OPTICS(&data[0], NULL, data.size()/dim, dim, minPts, epsilon);

    //op->setStartIdx(101);
    op->showInfo();
    
    op->run();
       
    op->updateClusterIDs(1.2);
    
    op->showClustering();

    //std::vector< int > l = op->getClusterIDs();
    //for ( auto & k : l ) {  std::cout << k << std::endl;}
    //op->showInfo();
    op->showInfo();

    //std::vector< real_t > dists = op->getClusterOrderDistances();
    //for ( auto & k : dists ) {  std::cout << k << std::endl;}
    
    //std::vector< int > dists = op->getClusterIDs();
    //for ( auto & k : dists ) {  std::cout << k << std::endl;}
    
    //std::vector< int > ddd = op->getClusterIDs2();
    //for ( auto & k : ddd ) {  std::cout << k << std::endl;}

    //std::cout << "----------------------------------------------------------" << std::endl;
    delete op; op = NULL;
  }



  //printf("System Success!\n");
  return 0;
  
}