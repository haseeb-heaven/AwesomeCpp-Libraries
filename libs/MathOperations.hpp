#ifndef MATHOPERATIONS_HPP
#define MATHOPERATIONS_HPP

#include <vector>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include "Logger.hpp" // Assuming Logger.hpp is in the same directory

class MathOperations
{
private:
    static Logger logger;

    // Helper function to validate matrix dimensions for addition and subtraction
    static void validateMatrixDimensions(const std::vector<std::vector<double>> &matrixA,
                                         const std::vector<std::vector<double>> &matrixB,
                                         const std::string &operation)
    {
        if (matrixA.size() == 0 || matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size())
        {
            logger.log("Matrix " + operation + " failed: Incompatible dimensions");
            throw std::invalid_argument("Incompatible matrix dimensions for " + operation);
        }
    }

public:
    MathOperations()
    {
        logger.log("MathOperations instance created");
    }

    /**
     * Adds two matrices.
     *
     * @param matrixA The first matrix.
     * @param matrixB The second matrix.
     * @return The result of matrix addition.
     * @throws std::invalid_argument if matrices have incompatible dimensions.
     */
    static std::vector<std::vector<double>> addMatrices(const std::vector<std::vector<double>> &matrixA,
                                                        const std::vector<std::vector<double>> &matrixB)
    {
        validateMatrixDimensions(matrixA, matrixB, "addition");
        std::vector<std::vector<double>> result(matrixA.size(), std::vector<double>(matrixA[0].size(), 0));
        for (size_t i = 0; i < matrixA.size(); ++i)
        {
            for (size_t j = 0; j < matrixA[i].size(); ++j)
            {
                result[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
        logger.log("Matrix addition successful");
        return result;
    }

    /**
     * Subtracts two matrices.
     *
     * @param matrixA The first matrix.
     * @param matrixB The second matrix.
     * @return The result of matrix subtraction.
     * @throws std::invalid_argument if matrices have incompatible dimensions.
     */
    static std::vector<std::vector<double>> subtractMatrices(const std::vector<std::vector<double>> &matrixA,
                                                             const std::vector<std::vector<double>> &matrixB)
    {
        validateMatrixDimensions(matrixA, matrixB, "subtraction");
        std::vector<std::vector<double>> result(matrixA.size(), std::vector<double>(matrixA[0].size(), 0));
        for (size_t i = 0; i < matrixA.size(); ++i)
        {
            for (size_t j = 0; j < matrixA[i].size(); ++j)
            {
                result[i][j] = matrixA[i][j] - matrixB[i][j];
            }
        }
        logger.log("Matrix subtraction successful");
        return result;
    }

    /**
     * Calculates the mean of a vector of numbers.
     *
     * @param data The input data vector.
     * @return The mean value.
     * @throws std::invalid_argument if the data vector is empty.
     */
    static double mean(const std::vector<double> &data)
    {
        if (data.empty())
        {
            logger.log("Mean calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double mean = sum / data.size();
        logger.log("Mean calculation successful");
        return mean;
    }

/**
 * Calculates the variance of a vector of numbers.
 *
 * @param data The input data vector.
 * @return The variance value.
 * @throws std::invalid_argument if the data vector is empty.
 */
static double variance(const std::vector<double> &data)
{
    if (data.empty())
    {
        logger.log("Variance calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    double meanValue = mean(data);
    double sum = 0.0;
    for (const auto &elem : data)
    {
        sum += (elem - meanValue) * (elem - meanValue);
    }
    double variance = sum / data.size();
    logger.log("Variance calculation successful");
    return variance;
}

/**
 * Calculates the standard deviation of a vector of numbers.
 *
 * @param data The input data vector.
 * @return The standard deviation value.
 * @throws std::invalid_argument if the data vector is empty.
 */
static double standardDeviation(const std::vector<double> &data)
{
    if (data.empty())
    {
        logger.log("Standard deviation calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    double varianceValue = variance(data);
    double standardDeviation = std::sqrt(varianceValue);
    logger.log("Standard deviation calculation successful");
    return standardDeviation;
}

/**
 * Calculates the covariance between two vectors of numbers.
 *
 * @param dataA The first data vector.
 * @param dataB The second data vector.
 * @return The covariance value.
 * @throws std::invalid_argument if either data vector is empty or they have different sizes.
 */
static double covariance(const std::vector<double> &dataA, const std::vector<double> &dataB)
{
    if (dataA.empty() || dataB.empty())
    {
        logger.log("Covariance calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    if (dataA.size() != dataB.size())
    {
        logger.log("Covariance calculation failed: Incompatible data vectors");
        throw std::invalid_argument("Data vectors are not of equal size");
    }
    double meanA = mean(dataA);
    double meanB = mean(dataB);
    double sum = 0.0;
    for (size_t i = 0; i < dataA.size(); ++i)
    {
        sum += (dataA[i] - meanA) * (dataB[i] - meanB);
    }
    double covariance = sum / dataA.size();
    logger.log("Covariance calculation successful");
    return covariance;
}

/**
 * Calculates the correlation coefficient between two vectors of numbers.
 *
 * @param dataA The first data vector.
 * @param dataB The second data vector.
 * @return The correlation coefficient.
 * @throws std::invalid_argument if either data vector is empty or they have different sizes.
 */
static double correlationCoefficient(const std::vector<double> &dataA, const std::vector<double> &dataB)
{
    if (dataA.empty() || dataB.empty())
    {
        logger.log("Correlation coefficient calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    if (dataA.size() != dataB.size())
    {
        logger.log("Correlation coefficient calculation failed: Incompatible data vectors");
        throw std::invalid_argument("Data vectors are not of equal size");
    }
    double covarianceValue = covariance(dataA, dataB);
    double standardDeviationA = standardDeviation(dataA);
    double standardDeviationB = standardDeviation(dataB);
    double correlationCoefficient = covarianceValue / (standardDeviationA * standardDeviationB);
    logger.log("Correlation coefficient calculation successful");
    return correlationCoefficient;
}

/**
 * Calculates the dot product of two vectors of numbers.
 *
 * @param dataA The first data vector.
 * @param dataB The second data vector.
 * @return The dot product.
 * @throws std::invalid_argument if either data vector is empty or they have different sizes.
 */
static double dotProduct(const std::vector<double> &dataA, const std::vector<double> &dataB)
{
    if (dataA.empty() || dataB.empty())
    {
        logger.log("Dot product calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    if (dataA.size() != dataB.size())
    {
        logger.log("Dot product calculation failed: Incompatible data vectors");
        throw std::invalid_argument("Data vectors are not of equal size");
    }
    double sum = 0.0;
    for (size_t i = 0; i < dataA.size(); ++i)
    {
        sum += dataA[i] * dataB[i];
    }
    logger.log("Dot product calculation successful");
    return sum;
}

/**
 * Calculates the cross product of two vectors of numbers (size 3).
 *
 * @param dataA The first data vector (size 3).
 * @param dataB The second data vector (size 3).
 * @return The cross product vector (size 3).
 * @throws std::invalid_argument if either data vector is empty or they are not of size 3.
 */
static std::vector<double> crossProduct(const std::vector<double> &dataA, const std::vector<double> &dataB)
{
    if (dataA.empty() || dataB.empty())
    {
        logger.log("Cross product calculation failed: Empty data vector");
        throw std::invalid_argument("Data vector is empty");
    }
    if (dataA.size() != 3 || dataB.size() != 3)
    {
        logger.log("Cross product calculation failed: Incompatible data vectors");
        throw std::invalid_argument("Data vectors are not of size 3");
    }
    std::vector<double> result(3, 0);
    result[0] = dataA[1] * dataB[2] - dataA[2] * dataB[1];
    result[1] = dataA[2] * dataB[0] - dataA[0] * dataB[2];
    result[2] = dataA[0] * dataB[1] - dataA[1] * dataB[0];
    logger.log("Cross product calculation successful");
    return result;
}

/**
 * Calculates the determinant of a 2x2 matrix.
 *
 * @param matrix The 2x2 matrix.
 * @return The determinant value.
 * @throws std::invalid_argument if the matrix is not of size 2x2.
 */
static double determinant(const std::vector<std::vector<double>> &matrix)
{
    if (matrix.size() != 2 || matrix[0].size() != 2)
    {
        logger.log("Determinant calculation failed: Incompatible matrix dimensions");
        throw std::invalid_argument("Matrix is not of size 2x2");
    }
    double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    logger.log("Determinant calculation successful");
    return determinant;
}

/**
 * Calculates the inverse of a 2x2 matrix.
 *
 * @param matrix The 2x2 matrix.
 * @return The inverse matrix.
 * @throws std::invalid_argument if the matrix is not of size 2x2 or has a determinant of zero.
 */
static std::vector<std::vector<double>> inverse(const std::vector<std::vector<double>> &matrix)
{
    if (matrix.size() != 2 || matrix[0].size() != 2)
    {
        logger.log("Inverse calculation failed: Incompatible matrix dimensions");
        throw std::invalid_argument("Matrix is not of size 2x2");
    }
    double det = determinant(matrix);
    if (det == 0)
    {
        logger.log("Inverse calculation failed: Determinant is zero");
        throw std::invalid_argument("Determinant is zero");
    }
    std::vector<std::vector<double>> result(2, std::vector<double>(2, 0));
    result[0][0] = matrix[1][1] / det;
    result[0][1] = -matrix[0][1] / det;
    result[1][0] = -matrix[1][0] / det;
    result[1][1] = matrix[0][0] / det;
    logger.log("Inverse calculation successful");
    return result;
}

/**
 * Calculates the transpose of a matrix.
 *
 * @param matrix The input matrix.
 * @return The transpose matrix.
 * @throws std::invalid_argument if the matrix is empty.
 */
static std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>> &matrix)
{
    if (matrix.size() == 0)
    {
        logger.log("Transpose calculation failed: Empty matrix");
        throw std::invalid_argument("Matrix is empty");
    }
    std::vector<std::vector<double>> result(matrix[0].size(), std::vector<double>(matrix.size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            result[j][i] = matrix[i][j];
        }
    }
    logger.log("Transpose calculation successful");
    return result;
}

/**
 * Calculates the trace of a square matrix.
 *
 * @param matrix The square matrix.
 * @return The trace value.
 * @throws std::invalid_argument if the matrix is empty or not square.
 */
static double trace(const std::vector<std::vector<double>> &matrix)
{
    if (matrix.size() == 0)
    {
        logger.log("Trace calculation failed: Empty matrix");
        throw std::invalid_argument("Matrix is empty");
    }
    if (matrix.size() != matrix[0].size())
    {
        logger.log("Trace calculation failed: Incompatible matrix dimensions");
        throw std::invalid_argument("Matrix is not square");
    }
    double trace = 0.0;
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        trace += matrix[i][i];
    }
    logger.log("Trace calculation successful");
    return trace;
}

/**
 * Calculates the rank of a matrix.
 *
 * @param matrix The input matrix.
 * @return The rank of the matrix.
 * @throws std::invalid_argument if the matrix is empty.
 */
static size_t rank(const std::vector<std::vector<double>> &matrix)
{
    if (matrix.size() == 0)
    {
        logger.log("Rank calculation failed: Empty matrix");
        throw std::invalid_argument("Matrix is empty");
    }
    size_t rank = 0;
    std::vector<std::vector<double>> temp(matrix.size(), std::vector<double>(matrix[0].size(), 0));
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[i].size(); ++j)
        {
            temp[i][j] = matrix[i][j];
        }
    }
    for (size_t i = 0; i < temp[0].size(); ++i)
    {
        if (temp[0][i] != 0)
        {
            ++rank;
            for (size_t j = 1; j < temp.size(); ++j)
            {
                double ratio = temp[j][i] / temp[0][i];
                for (size_t k = 0; k < temp[0].size(); ++k)
                {
                    temp[j][k] -= ratio * temp[0][k];
                }
            }
        }
    }
    for (size_t i = 1; i < temp.size(); ++i)
    {
        bool allZeros = true;
        for (size_t j = 0; j < temp[i].size(); ++j)
        {
            if (temp[i][j] != 0)
            {
                allZeros = false;
                break;
            }
        }
        if (!allZeros)
        {
            ++rank;
        }
    }
    logger.log("Rank calculation successful");
    return rank;
}

};

// Definition of the static logger member
Logger MathOperations::logger = Logger("libs/MathOperations.log");

#endif // MATHOPERATIONS_HPP

