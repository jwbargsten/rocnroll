
#include <limits>
/*
 * regularize
 * approxfun
 * approx
 */


class LinearInterpolation {
  bool constant_interpolation; //constant = method 2, linear = method 1
  int rule; // rule = 1: NA, rule = 2: closest to extreme

    double ylow;
    double yhigh;
    double f1;
    double f2;
    int kind;

  vector<int> non_finite_idcs;
  vector<double> x;
  vector<double> y;
  vector<double> x_tie;
  vector<double> y_tie;

  void checkNA();
  public:

  function(v) .approxfun(x, y, v, method, yleft, yright, f)

R_approxfun(double *x, double *y, int nxy, double *xout, double *yout,
	    int nout, int method, double yleft, double yright, double f)

  /* f with constant :
   * If ‘y0’ and ‘y1’ are the values to the left
   * and right of the point then the value is ‘y0*(1-f)+y1*f’ so
   * that ‘f = 0’ is right-continuous and ‘f = 1’ is
   * left-continuous.
   */

    double interplolate(const double& x);
};



double interpolate(const double& xout)
{
  nx = x.size();
  nout = 1;
  m = 2;
  yout = approxfun(x,y,nx,xout,nout,m, yl, yr,f);
}



{
    int i;
    appr_meth M = {0.0, 0.0, 0.0, 0.0, 0}; /* -Wall */

    M.f2 = f;
    M.f1 = 1 - f;
    M.kind = method;
    M.ylow = yleft;
    M.yhigh = yright;
    for(i = 0; i < nout; i++)
	if(!ISNA(xout[i])) yout[i] = approx1(xout[i], x, y, nxy, &M);
	else yout[i] = xout[i];
}

SEXP ApproxTest(SEXP x, SEXP y, SEXP method, SEXP sf)
{
    int nx = LENGTH(x), m = asInteger(method);
    double f = asReal(sf);
    R_approxtest(REAL(x), REAL(y), nx, m, f);
    return R_NilValue;
}

SEXP Approx(SEXP x, SEXP y, SEXP v, SEXP method, 
	    SEXP yleft, SEXP yright, SEXP sf)
{
    SEXP xout = PROTECT(coerceVector(v, REALSXP));
    int nx = LENGTH(x), nout = LENGTH(xout), m = asInteger(method);
    double yl = asReal(yleft), yr = asReal(yright), f = asReal(sf);
    SEXP yout = PROTECT(allocVector(REALSXP, nout));
    R_approxfun(REAL(x), REAL(y), nx, REAL(xout), REAL(yout), nout, 
		m, yl, yr, f);
    UNPROTECT(2);
    return yout;
}

 approxfun(x, y = NULL,       method = "linear", yleft, yright, rule = 1, f = 0, ties = mean)

        tpr.stop <- approxfun( x[ind:(ind+1)], y[ind:(ind+1)] )(fpr.stop)


        tpr.stop <- approxfun( x[ind:(ind+1)], y[ind:(ind+1)] )(fpr.stop)
              ans <- uniroot(approxfun(c(alpha[i], alpha[i+1] ), c(x[i]-y[i], x[i+1]-y[i+1])),
              alpha.ticks <- approxfun(c(min.y, max.y), c(min.alpha, max.alpha)) ( axTicks(4))
            alpha2x <- approxfun(c( min(alpha.ticks), max(alpha.ticks)), c( min.x, max.x))
            text.y <- approxfun(perf@alpha.values[[i]], perf@y.values[[i]], rule=2, ties=mean)(print.cutoffs.at)
          approxfun(perf@x.values[[i]], perf@y.values[[i]], ties=mean, rule=2)(x.values)
        y.values.int.1 <- approxfun(x.values.1, y.values.1, method="constant",f=1,rule=2)(cutoffs)

