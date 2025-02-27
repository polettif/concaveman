#pragma once

#include "Rcpp.h"

namespace api {

Rcpp::DataFrame rcpp_concaveman_mat (Rcpp::NumericMatrix xy, Rcpp::IntegerVector hull_in,
        const double concavity, const double length_threshold)
{
    const size_t num_points = static_cast <int> (xy.nrow ());
    
    typedef double T;
    typedef std::array <T, 2> point_type;

    std::vector <point_type> points (num_points);
    for (auto i = 0; i < num_points; i++) {
        points[i] = { xy (i, 0), xy (i, 1) };
    }

    std::vector <int> hull = Rcpp::as <std::vector <int> > (hull_in);

    auto concave_points = concaveman::concaveman <T, 16> (points, hull,
            concavity, length_threshold);

    Rcpp::NumericVector xout (concave_points.size ()),
        yout (concave_points.size ());
    for (int i = 0; i < concave_points.size (); i++)
    {
        xout (i) = concave_points [i] [0];
        yout (i) = concave_points [i] [1];
    }

    Rcpp::DataFrame res = Rcpp::DataFrame::create (
            Rcpp::Named ("x") = xout,
            Rcpp::Named ("y") = yout);

    return res;
}

} // end namespace api
