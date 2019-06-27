#include "assignments/ev/euclidean_vector.h"

#include <algorithm>  // Look at these - they are helpful https://en.cppreference.com/w/cpp/algorithm
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>

/*
 * CONSTRUCTORS
 */

EuclideanVector::EuclideanVector(int i, double d) {
  this->size_ = i;
  this->magnitudes_ = std::make_unique<double[]>(this->size_);
  for (std::size_t j = 0; j < this->size_; ++j) {
    this->magnitudes_[j] = d;
  }
}

EuclideanVector::EuclideanVector(std::vector<double>::const_iterator begin,
                                 std::vector<double>::const_iterator end) noexcept {
  this->size_ = end - begin;
  this->magnitudes_ = std::make_unique<double[]>(this->size_);
  auto i = 0;
  for (auto it = begin; it != end ; ++it, ++i) {
   this->magnitudes_[i] = *it;
  }
}

EuclideanVector::EuclideanVector(const EuclideanVector& e) noexcept{
  this->size_ = e.GetNumDimensions();
  this->magnitudes_ = std::make_unique<double[]>(this->size_);
  for (int i = 0; i < this->GetNumDimensions(); ++i) {
    this->magnitudes_[i] = e[i];
  }
}
EuclideanVector::EuclideanVector(EuclideanVector&& e) noexcept { this->size_ = e.GetNumDimensions();
  this->magnitudes_ = std::make_unique<double[]>(this->size_);
  for (int i = 0; i < this->GetNumDimensions(); ++i) {
    this->magnitudes_[i] = e[i];
  }
  e.size_ = 0;
  e.magnitudes_ = std::make_unique<double[]>(0);
}

/*
 * DESTRUCTOR
 */
EuclideanVector::~EuclideanVector() noexcept {
  delete this;
}
/*
EuclideanVector EuclideanVector::aCopy(const EuclideanVector& e) noexcept {
  return EuclideanVector();
}
EuclideanVector EuclideanVector::aMove(EuclideanVector&& e) noexcept {
  return <EuclideanVector&&>();
}
 */

/*
 * OPERATIONS
 */
EuclideanVector& EuclideanVector::operator=(EuclideanVector e) noexcept {
  this->size_ = e.GetNumDimensions();
  for (int i = 0; i < e.GetNumDimensions(); ++i) {
    this->magnitudes_[i] = e[i];
  }
  return *this;
}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& e) noexcept {
  this->size_ = e.GetNumDimensions();
  for (int i = 0; i < e.GetNumDimensions(); ++i) {
    this->magnitudes_[i] = e[i];
  }
  return *this;
}

double& EuclideanVector::operator[](int i) noexcept {
  return this->magnitudes_[i];
}

double EuclideanVector::operator[](int i) const noexcept {
  return this->magnitudes_[i];
}
EuclideanVector& EuclideanVector::operator+=(const EuclideanVector& e) {
  if (this->GetNumDimensions() != e.GetNumDimensions()) {
    std::ostringstream err;
    err << "Dimensions of LHS(" << this->GetNumDimensions();
    err << ") and RHS(" << e.GetNumDimensions() << ") do not match";
    throw EuclideanVectorError(err.str());
  }
  for (std::size_t i = 0; i < this->size_; ++i) {
    this->magnitudes_[i] += e[i];
  }
  return *this;
}
EuclideanVector& EuclideanVector::operator-=(const EuclideanVector& e) {
  if (this->GetNumDimensions() != e.GetNumDimensions()) {
    std::ostringstream err;
    err << "Dimensions of LHS(" << this->GetNumDimensions();
    err << ") and RHS(" << e.GetNumDimensions() << ") do not match";
    throw EuclideanVectorError(err.str());
  }
  for (std::size_t i = 0; i < this->size_; ++i) {
    this->magnitudes_[i] -= e[i];
  }
  return *this;
}
EuclideanVector& EuclideanVector::operator*=(const double& rhs) noexcept {
  for (std::size_t j = 0; j < this->size_; ++j) {
    this->magnitudes_[j] *= rhs;
  }
  return *this;
}
EuclideanVector& EuclideanVector::operator/=(const double& rhs) {
  if (rhs == 0.0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  for (std::size_t j = 0; j < this->size_; ++j) {
    this->magnitudes_[j] /= rhs;
  }
  return *this;
}

EuclideanVector::operator std::vector<double>() noexcept {
  std::vector<double> v;
  for (std::size_t i = 0; i < this->size_; ++i) {
    v.push_back(this->magnitudes_[i]);
  }
  return v;
}
EuclideanVector::operator std::list<double>() noexcept {
  std::list<double> l;
  for (std::size_t i = 0; i < this->size_; ++i) {
    l.push_back(this->magnitudes_[i]);
  }
  return l;
}

/*
 * METHODS
 */
double EuclideanVector::at(int i) noexcept {
  return this->magnitudes_[i];
}
int EuclideanVector::GetNumDimensions() const noexcept {
  return this->size_;
}
double EuclideanVector::GetEuclideanNorm() noexcept {
  double norm = 0.0;
  for (std::size_t i = 0; i < this->size_; ++i) {
    norm += this->at(i) * this->at(i);
  }
  return pow(norm, 0.5);
}
EuclideanVector EuclideanVector::CreateUnitVector() {
  auto copy = *this;
  return copy / this->GetEuclideanNorm();
}

/*
 * FRIENDS
 */
bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
  auto equal = false;
  if (lhs.GetNumDimensions() == rhs.GetNumDimensions()) {
    equal = true;
    for (int i = 0; i < lhs.GetNumDimensions(); ++i) {
      if (lhs[i] != rhs[i]) {
        equal = false;
      }
    }
  }
  return equal;
}
bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept {
  return !(lhs == rhs);
}
EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    std::ostringstream err;
    err << "Dimensions of LHS(" << lhs.GetNumDimensions();
    err << ") and RHS(" << rhs.GetNumDimensions() << ") do not match";
    throw EuclideanVectorError(err.str());
  }
  auto size = lhs.GetNumDimensions();
  std::vector<double> magnitudes;
  for (int i = 0; i < size; ++i) {
    magnitudes.push_back(lhs[i] + rhs[i]);
  }
  return EuclideanVector(magnitudes.begin(), magnitudes.end());
}
EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    std::ostringstream err;
    err << "Dimensions of LHS(" << lhs.GetNumDimensions();
    err << ") and RHS(" << rhs.GetNumDimensions() << ") do not match";
    throw EuclideanVectorError(err.str());
  }
  auto size = lhs.GetNumDimensions();
  std::vector<double> magnitudes;
  for (int i = 0; i < size; ++i) {
    magnitudes.push_back(lhs[i] - rhs[i]);
  }
  return EuclideanVector(magnitudes.begin(), magnitudes.end());
}
double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs) {
  if (lhs.GetNumDimensions() != rhs.GetNumDimensions()) {
    std::ostringstream err;
    err << "Dimensions of LHS(" << lhs.GetNumDimensions();
    err << ") and RHS(" << rhs.GetNumDimensions() << ") do not match";
    throw EuclideanVectorError(err.str());
  }
  auto size = lhs.GetNumDimensions();
  auto dp = 0.0;
  for (int i = 0; i < size; ++i) {
    dp += lhs[i] * rhs[i];
  }
  return dp;
}
EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) noexcept {
  auto size = lhs.GetNumDimensions();
  std::vector<double> magnitudes;
  for (int i = 0; i < size; ++i) {
    magnitudes.push_back(lhs[i] * rhs);
  }
  return EuclideanVector(magnitudes.begin(), magnitudes.end());
}
EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs) {
  if (rhs == 0) {
    throw EuclideanVectorError("Invalid vector division by 0");
  }
  auto size = lhs.GetNumDimensions();
  std::vector<double> magnitudes;
  for (int i = 0; i < size; ++i) {
    magnitudes.push_back(lhs[i] / rhs);
  }
  return EuclideanVector(magnitudes.begin(), magnitudes.end());
}
std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept {
  os << "[";
  if (v.GetNumDimensions() > 0) {
    for (int i = 0; i < v.GetNumDimensions() - 1; ++i) {
      os << v[i] << " ";
    }
    os << v[v.GetNumDimensions() - 1] << "]";
  } else {
    os << "]";
  }
  return os;
}
