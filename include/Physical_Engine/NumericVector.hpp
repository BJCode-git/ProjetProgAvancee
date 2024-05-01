#ifndef NUMERICVECTOR_HPP
#define NUMERICVECTOR_HPP

#include <iostream>    // Pour std::cout, std::endl, etc...
#include <cmath>       // Pour std::sqrt, std::abs, etc...
#include <limits>      // Pour std::numeric_limits
#include <type_traits> // Pour std::enable_if_t, std::is_convertible_v, etc.
#include <array>       // Pour std::array

#include "debug.hpp"

template<typename T, size_t Size, typename En = void> 
class NumericVector;


using Vector2D  = NumericVector<unsigned int,2>;//std::pair<int, int>;
using Vector2DF = NumericVector<float       ,2>;//std::pair<float, float>;

// Point 2D
using Point2D  = NumericVector<unsigned int,2>;
using Point2DF = NumericVector<float       ,2>;
// Polygone 2D
using Polygon  = std::vector<Point2DF>;

/**
 * @class NumericVector
 * @brief A class template representing a numeric vector.
 * @tparam T The type of the elements in the vector.
 * @tparam Size The size of the vector.
 */
template< typename T, size_t Size>
class NumericVector<T, Size, std::enable_if_t<std::is_arithmetic<T>::value>>{
	private:
		std::array<T, Size> elements;

	public:
		/**
		 * @brief Default constructor. Initializes all elements to zero.
		 */
		NumericVector(){
			elements.fill(0);
		}

		/**
		 * @brief Constructor that initializes all elements to a given value.
		 * 
		 * @param value The value to initialize the elements with.
		 */
		NumericVector(const T& value) {
			elements.fill(value);
		}

		/**
		 * @brief Constructor that initializes the elements with an initializer list.
		 * 
		 * @param list The initializer list containing the values to initialize the elements with.
		 */
		NumericVector(std::initializer_list<T> list) {
			for(size_t i=0; i<std::min(list.size(),Size);i++){
				elements[i]=*(list.begin()+i);
			}
		}

		/**
		 * @brief Accesses the elements of the vector.
		 * 
		 * @param index The index of the element to access.
		 * @return T& A reference to the element at the specified index.
		 * @throw std::out_of_range If the index is out of range.
		 */
		T& operator[](size_t index) {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		/**
		 * @brief Accesses the elements of the vector (const version).
		 * 
		 * @param index The index of the element to access.
		 * @return const T& A const reference to the element at the specified index.
		 * @throw std::out_of_range If the index is out of range.
		 */
		const T& operator[](size_t index) const {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		/**
		 * @brief Equality comparison operator.
		 * 
		 * @param other The vector to compare with.
		 * @return bool True if the vectors are equal, false otherwise.
		 */
		bool operator==(const NumericVector<T, Size>& other) const {
			for (size_t i = 0; i < Size; ++i) {
				if (elements[i] != other[i]) {
					return false;
				}
			}
			return true;
		}

		/**
		 * @brief Inequality comparison operator.
		 * 
		 * @param other The vector to compare with.
		 * @return bool True if the vectors are not equal, false otherwise.
		 */
		bool operator!=(const NumericVector<T, Size>& other) const {
			return !(*this == other);
		}

		/**
		 * @brief Addition operator.
		 * 
		 * @param other The vector to add.
		 * @return NumericVector<T, Size> The resulting vector after addition.
		 */
		NumericVector<T, Size> operator+(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] + other[i];
			}
			return result;
		}

		/**
		 * @brief Subtraction operator.
		 * 
		 * @param other The vector to subtract.
		 * @return NumericVector<T, Size> The resulting vector after subtraction.
		 */
		NumericVector<T, Size> operator-(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] - other[i];
			}
			return result;
		}

		/**
		 * @brief Scalar multiplication operator.
		 * 
		 * @param scalar The scalar value to multiply the vector with.
		 * @return NumericVector<T, Size> The resulting vector after multiplication.
		 */
		NumericVector<T, Size> operator*(const T& scalar) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] * scalar;
			}
			return result;
		}

		/**
		 * @brief Scalar division operator.
		 * 
		 * @param scalar The scalar value to divide the vector by.
		 * @return NumericVector<T, Size> The resulting vector after division.
		 * @throw std::invalid_argument If the scalar value is zero.
		 */
		NumericVector<T, Size> operator/(const T& scalar) const {
			if (scalar == 0) {
				throw std::invalid_argument("Division by zero");
			}
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] / scalar;
			}
			return result;
		}

		/**
		 * @brief Calculates the scalar product of two vectors.
		 * 
		 * @param other The vector to calculate the scalar product with.
		 * @return T The scalar product of the two vectors.
		 */
		T scalarProduct(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += elements[i] * other[i];
			}
			return result;
		}

		/**
		 * @brief Calculates the cross product of two 3D vectors.
		 * 
		 * @param other The vector to calculate the cross product with.
		 * @return NumericVector<T, Size> The resulting vector after cross product.
		 * @throw static_assert If the size of the vectors is not 3.
		 */
		NumericVector<T, Size> crossProduct(const NumericVector<T, Size>& other) const {
			static_assert(Size == 3, "Cross product is only defined in 3D");
			return {elements[1] * other[2] - elements[2] * other[1],
					elements[2] * other[0] - elements[0] * other[2],
					elements[0] * other[1] - elements[1] * other[0]};
		}

		/**
		 * @brief Calculates the squared distance between two vectors.
		 * 
		 * @param other The vector to calculate the distance with.
		 * @return T The squared distance between the two vectors.
		 */
		T distance_square(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += (elements[i] - other[i]) * (elements[i] - other[i]);
			}
			return result;
		}

		/**
		 * @brief Calculates the distance between two vectors.
		 * 
		 * @param other The vector to calculate the distance with.
		 * @return T The distance between the two vectors.
		 */
		T distance(const NumericVector<T, Size>& other) const {
			return std::sqrt(distance_square(other));
		}

		/**
		 * @brief Normalizes the vector.
		 * 
		 * @return NumericVector<T, Size> The normalized vector.
		 * @throw std::invalid_argument If the vector is a zero vector.
		 */
		void normalize(){
			T norm = 0;
			for (size_t i = 0; i < Size; ++i) {
				norm += elements[i] * elements[i];
			}
			if (norm == 0) {
				throw std::invalid_argument("Cannot normalize zero vector");
			}

			for (size_t i = 0; i < Size; ++i) {
				elements[i] /= norm;
			}
		}
		
		/**
		 * @brief Outputs the vector to an output stream.
		 * 
		 * @param os The output stream.
		 * @param vector The vector to output.
		 * @return std::ostream& The output stream.
		 */
		friend std::ostream& operator<<(std::ostream& os, const NumericVector<T, Size>& vector) {
			os << "(";
			for (size_t i = 0; i < Size - 1; ++i) {
				os << vector[i] << ", ";
			}
			os << vector[Size - 1] << ")";
			return os;
		}
};

#endif // NUMERICVECTOR_HPP