#include <iostream>
#include <cmath>
#include <boost/rational.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/odeint.hpp>

using namespace std;
namespace ublas = boost::numeric::ublas;
using namespace boost::numeric::odeint;

// Number of program 1
double sqrt2 = sqrt(2);
cout << sqrt2 << endl;

// Number of program 2
boost::rational<int> half(1, 2);
boost::rational<int> third(1, 3);
boost::rational<int> sumResult = half + third;
cout << sumResult << endl;

// Number of program 3
symbol varX("x"), varY("y");
expression binomialExpr = pow(varX + varY, 6);
expression expandedExpr = expand(binomialExpr);
cout << expandedExpr << endl;

// Number of program 4
expression trigExpr = sin(varX) / cos(varX);
expression simplifiedExpr = simplify(trigExpr);
cout << simplifiedExpr << endl;

// Number of program 5
expression equation = (sin(varX) - varX) / pow(varX, 3);
expression_set solutionSet = solve(equation, varX);
cout << solutionSet << endl;

// Number of program 6
expression logExpr = log(varX);
expression logDerivative = diff(logExpr, varX);
double logDerivativeValue = eval(logDerivative, varX);
cout << "Derivative of log(x) with respect to x: " << logDerivative << endl;
cout << "Value of the derivative: " << logDerivativeValue << endl;

expression inverseExpr = 1 / varX;
expression inverseDerivative = diff(inverseExpr, varX);
double inverseDerivativeValue = eval(inverseDerivative, varX);
cout << "Derivative of 1/x with respect to x: " << inverseDerivative << endl;
cout << "Value of the derivative: " << inverseDerivativeValue << endl;

expression sinExpr = sin(varX);
expression sinDerivative = diff(sinExpr, varX);
double sinDerivativeValue = eval(sinDerivative, varX);
cout << "Derivative of sin(x) with respect to x: " << sinDerivative << endl;
cout << "Value of the derivative: " << sinDerivativeValue << endl;

expression cosExpr = cos(varX);
expression cosDerivative = diff(cosExpr, varX);
double cosDerivativeValue = eval(cosDerivative, varX);
cout << "Derivative of cos(x) with respect to x: " << cosDerivative << endl;
cout << "Value of the derivative: " << cosDerivativeValue << endl;

// Number of program 7
symbol varX("x"), varY("y");
expression equation1 = varX + varY - 2;
expression equation2 = 2 * varX + varY;
expression_set solutionSet = solve(equation1, equation2, varX, varY);
cout << "x = " << solutionSet[varX] << endl;
cout << "y = " << solutionSet[varY] << endl;

// Number of program 8
symbol varX("x");
expression integratedExpr1 = integrate(pow(varX, 2), varX);
cout << "Integration of x^2: " << integratedExpr1 << endl;

expression integratedExpr2 = integrate(sin(varX), varX);
cout << "Integration of sin(x): " << integratedExpr2 << endl;

expression integratedExpr3 = integrate(cos(varX), varX);
cout << "Integration of cos(x): " << integratedExpr3 << endl;

// Number of program 9
symbol varX("x");
expression functionF = symbol_function< double >("f")(varX);
expression differentialEquation = diff(functionF, varX, varX) + 9 * functionF - 1;
expression solution = dsolve(differentialEquation, functionF);
cout << solution << endl;

// Number of program 10
symbol varX("x"), varY("y"), varZ("z");
ublas::matrix<double> coefficientMatrix(2, 3);
coefficientMatrix(0, 0) = 3;
coefficientMatrix(0, 1) = 7;
coefficientMatrix(0, 2) = -12;
coefficientMatrix(1, 0) = 4;
coefficientMatrix(1, 1) = -2;
coefficientMatrix(1, 2) = -5;
ublas::vector<double> constants(2);
constants(0) = 0;
constants(1) = 0;

ublas::permutation_matrix<size_t> permutationMatrix(coefficientMatrix.size1());
ublas::lu_factorize(coefficientMatrix, permutationMatrix);
ublas::lu_substitute(coefficientMatrix, permutationMatrix, constants);
cout << "x = " << constants(0) << endl;
cout << "y = " << constants(1) << endl;
