#ifndef GAUSSIAN_MIXTURE_MODEL_H
#define GAUSSIAN_MIXTURE_MODEL_H

#include "Gaussian.h"
#include <vector>

class GaussianMixtureModel
{
public:
  typedef std::vector<Gaussian *> GaussianVector;
  typedef std::vector<double> WeightVector;
  typedef GaussianVector::iterator GaussianVectorIterator;
  typedef WeightVector::iterator WeightVectorIterator;
  
  GaussianMixtureModel(int dimOfGaussian);
  GaussianMixtureModel(int dimOfGaussian, int numOfGaussian);
  ~GaussianMixtureModel();
  
  Gaussian * GetGaussian(int index);
  double * GetMean(int index);
  double * GetCovariance(int index);
  double GetWeight(int index);
  void AddGaussian(double *mean, double *covariance, double weight);
  void SetGaussian(int index, double *mean, double *covariance);
  void SetMean(int index, double *mean);
  void SetCovariance(int index, double *covariance);
  void SetWeight(int index, double weight);
  double EvaluatePDF(int index, double *x);
  double EvaluatePDF(int index, vnl_vector<double> &x, vnl_vector<double> &xscratch);

  void PrintParameters();

  int GetNumberOfGaussians() { return m_numOfGaussian; }
  int GetNumberOfComponents() { return m_dimOfGaussian; }
  
private:
  int m_numOfGaussian;
  int m_dimOfGaussian;
  GaussianVector *m_gaussian;
  WeightVector *m_weight;
};

#endif
