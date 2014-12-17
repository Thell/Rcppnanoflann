// [[Rcpp::plugins("cpp11")]]
#include <set>
#include <RcppEigen.h>
#include <Rcpp.h>
#include "nanoflann.hpp"

typedef nanoflann::KDTreeEigenMatrixAdaptor<
  Eigen::Matrix<double,Eigen::Dynamic,2>,
  2, nanoflann::metric_L2_Simple, size_t> KD_Tree;

//` Unique indexes of nearest neighbors.
//'
//' @title Eigen Matrix nanoflann nearest neighbor indexes
//' @name nanoflann_nnIndex
//' @param P dataframe (columns 1,2 being x,y) of data points.
//' @param Q dataframe (columns 1,2 being x,y) of query points.
//' @return vector of descending unqiue nearest neighbor indexes
//' @import Rcpp
//' @export
// [[Rcpp::export]]
std::vector<double> nnIndex(const Rcpp::DataFrame & P, const Rcpp::DataFrame & Q )
{
  using namespace Eigen;
  using namespace Rcpp;
  using namespace nanoflann;

  // Matrix of points to be queried against.
  const NumericVector & Px(P[0]);
  const NumericVector & Py(P[1]);
  MatrixX2d M(Px.size(), 2);
  M.col(0) = VectorXd::Map(&Px[0],Px.size());
  M.col(1) = VectorXd::Map(&Py[0],Py.size());

  // The points to query.
  const NumericVector & Qx(Q[0]);
  const NumericVector & Qy(Q[1]);
  double query_pt[2];
  const size_t query_count(Qx.size());

  // Populate a 2d tree.
  KD_Tree kd_tree( 2, M, 10 );
  kd_tree.index->buildIndex();

  std::set<size_t> nn;
  std::vector<double> out;
  out.reserve(query_count);

  size_t index(0);
  double quadrance;
  for( size_t i=0 ; i < query_count; ++i ) {
    query_pt[0] = Qx[i];
    query_pt[1] = Qy[i];
    kd_tree.index->knnSearch( &query_pt[0],1, &index, &quadrance);
    if( nn.insert(index).second ) out.emplace_back(index+1);
  }

  return out;
}
