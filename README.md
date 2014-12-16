This is just a simple example of an R package using [Rcpp][1], [RcppEigen][2],
[nanoflann][3] and c++11 to process two dataframes (one of reference
data points and one of query points) to quickly return the unique indexes
of nearest neighbors in answer to the StackOverflow question [Closest point to a path][4].

[1]:http://mran.revolutionanalytics.com/packages/info/?Rcpp
[2]:http://mran.revolutionanalytics.com/packages/info/?RcppEigen
[3]:https://github.com/jlblancoc/nanoflann
[4]:http://stackoverflow.com/q/27321856/173985
