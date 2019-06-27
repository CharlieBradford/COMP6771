// TODO(you): Include header guards

#include <exception>
#include <list>
#include <memory>
#include <string>
#include <vector>

class EuclideanVectorError : public std::exception {
 public:
  explicit EuclideanVectorError(const std::string& what) : what_(what) {}
  const char* what() const noexcept{ return what_.c_str(); }
 private:
  std::string what_;
};

class EuclideanVector {
 public:
  explicit EuclideanVector(int i): EuclideanVector{i, 0.0} {};
  EuclideanVector(): EuclideanVector{1} {};
  EuclideanVector(int i, double d);
  EuclideanVector(std::vector<double>::const_iterator begin,
                  std::vector<double>::const_iterator end) noexcept;
  EuclideanVector(const EuclideanVector& e) noexcept;
  EuclideanVector(EuclideanVector&& e) noexcept;
  ~EuclideanVector() noexcept;

  // EuclideanVector aCopy(const EuclideanVector& e) noexcept;
  // EuclideanVector aMove(EuclideanVector&& e) noexcept;

  EuclideanVector& operator=(EuclideanVector e) noexcept;
  EuclideanVector& operator=(EuclideanVector&& e) noexcept;

  double& operator[](int i) noexcept;
  double operator[](int i) const noexcept;

  EuclideanVector& operator+=(const EuclideanVector& e);
  EuclideanVector& operator-=(const EuclideanVector& e);
  EuclideanVector& operator*=(const double& rhs) noexcept;
  EuclideanVector& operator/=(const double& rhs);

  explicit operator std::vector<double>() noexcept;
  explicit operator std::list<double>() noexcept;

  double at(int i) noexcept;
  int GetNumDimensions() const noexcept;
  double GetEuclideanNorm() noexcept;
  EuclideanVector CreateUnitVector();

  friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;
  friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs) noexcept;

  friend EuclideanVector operator+(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend EuclideanVector operator-(const EuclideanVector& lhs, const EuclideanVector& rhs);
  friend double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs);

  friend EuclideanVector operator*(const EuclideanVector& lhs, const double& rhs) noexcept;
  friend EuclideanVector operator/(const EuclideanVector& lhs, const double& rhs);



  friend std::ostream& operator<<(std::ostream& os, const EuclideanVector& v) noexcept;
  // TODO(you): add more
 private:
  std::unique_ptr<double[]> magnitudes_;
  std::size_t size_;
  // TODO(you): add more
};
