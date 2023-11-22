#ifndef MATHOPERATIONS_HPP
#define MATHOPERATIONS_HPP

#include <vector>
#include <stdexcept>
#include <numeric>
#include "Logger.hpp" // Assuming Logger.hpp is in the same directory

class MathOperations
{
private:
    static Logger logger;

    static void validateMatrixDimensions(const std::vector<std::vector<double>> &matrixA,
                                         const std::vector<std::vector<double>> &matrixB,
                                         const std::string &operation)
    {
        if (matrixA.size() == 0 || matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size())
        {
            logger.addLog("Matrix " + operation + " failed: Incompatible dimensions");
            throw std::invalid_argument("Incompatible matrix dimensions for " + operation);
        }
    }

public:
    MathOperations()
    {
        logger.addLog("MathOperations instance created");
    }

    // Matrix addition
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
        logger.addLog("Matrix addition successful");
        return result;
    }

    // Matrix subtraction
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
        logger.addLog("Matrix subtraction successful");
        return result;
    }

    // Calculate mean of a vector of numbers
    static double mean(const std::vector<double> &data)
    {
        if (data.empty())
        {
            logger.addLog("Mean calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double mean = sum / data.size();
        logger.addLog("Mean calculation successful");
        return mean;
    }

    // Calculate variance of a vector of numbers
    static double variance(const std::vector<double> &data)
    {
        if (data.empty())
        {
            logger.addLog("Variance calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        double meanValue = mean(data);
        double sum = 0.0;
        for (const auto &elem : data)
        {
            sum += (elem - meanValue) * (elem - meanValue);
        }
        double variance = sum / data.size();
        logger.addLog("Variance calculation successful");
        return variance;
    }

    // Calculate standard deviation of a vector of numbers
    static double standardDeviation(const std::vector<double> &data)
    {
        if (data.empty())
        {
            logger.addLog("Standard deviation calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        double varianceValue = variance(data);
        double standardDeviation = std::sqrt(varianceValue);
        logger.addLog("Standard deviation calculation successful");
        return standardDeviation;
    }

    // Calculate covariance of two vectors of numbers
    static double covariance(const std::vector<double> &dataA, const std::vector<double> &dataB)
    {
        if (dataA.empty() || dataB.empty())
        {
            logger.addLog("Covariance calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        if (dataA.size() != dataB.size())
        {
            logger.addLog("Covariance calculation failed: Incompatible data vectors");
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
        logger.addLog("Covariance calculation successful");
        return covariance;
    }

    // Calculate correlation coefficient of two vectors of numbers
    static double correlationCoefficient(const std::vector<double> &dataA, const std::vector<double> &dataB)
    {
        if (dataA.empty() || dataB.empty())
        {
            logger.addLog("Correlation coefficient calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        if (dataA.size() != dataB.size())
        {
            logger.addLog("Correlation coefficient calculation failed: Incompatible data vectors");
            throw std::invalid_argument("Data vectors are not of equal size");
        }
        double covarianceValue = covariance(dataA, dataB);
        double standardDeviationA = standardDeviation(dataA);
        double standardDeviationB = standardDeviation(dataB);
        double correlationCoefficient = covarianceValue / (standardDeviationA * standardDeviationB);
        logger.addLog("Correlation coefficient calculation successful");
        return correlationCoefficient;
    }

    // Calculate the dot product of two vectors of numbers
    static double dotProduct(const std::vector<double> &dataA, const std::vector<double> &dataB)
    {
        if (dataA.empty() || dataB.empty())
        {
            logger.addLog("Dot product calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        if (dataA.size() != dataB.size())
        {
            logger.addLog("Dot product calculation failed: Incompatible data vectors");
            throw std::invalid_argument("Data vectors are not of equal size");
        }
        double sum = 0.0;
        for (size_t i = 0; i < dataA.size(); ++i)
        {
            sum += dataA[i] * dataB[i];
        }
        logger.addLog("Dot product calculation successful");
        return sum;
    }

    // Calculate the cross product of two vectors of numbers
    static std::vector<double> crossProduct(const std::vector<double> &dataA, const std::vector<double> &dataB)
    {
        if (dataA.empty() || dataB.empty())
        {
            logger.addLog("Cross product calculation failed: Empty data vector");
            throw std::invalid_argument("Data vector is empty");
        }
        if (dataA.size() != 3 || dataB.size() != 3)
        {
            logger.addLog("Cross product calculation failed: Incompatible data vectors");
            throw std::invalid_argument("Data vectors are not of size 3");
        }
        std::vector<double> result(3, 0);
        result[0] = dataA[1] * dataB[2] - dataA[2] * dataB[1];
        result[1] = dataA[2] * dataB[0] - dataA[0] * dataB[2];
        result[2] = dataA[0] * dataB[1] - dataA[1] * dataB[0];
        logger.addLog("Cross product calculation successful");
        return result;
    }

    // Calculate the determinant of a 2x2 matrix
    static double determinant(const std::vector<std::vector<double>> &matrix)
    {
        if (matrix.size() != 2 || matrix[0].size() != 2)
        {
            logger.addLog("Determinant calculation failed: Incompatible matrix dimensions");
            throw std::invalid_argument("Matrix is not of size 2x2");
        }
        double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        logger.addLog("Determinant calculation successful");
        return determinant;
    }

    // Calculate the inverse of a 2x2 matrix
    static std::vector<std::vector<double>> inverse(const std::vector<std::vector<double>> &matrix)
    {
        if (matrix.size() != 2 || matrix[0].size() != 2)
        {
            logger.addLog("Inverse calculation failed: Incompatible matrix dimensions");
            throw std::invalid_argument("Matrix is not of size 2x2");
        }
        double det = determinant(matrix);
        if (det == 0)
        {
            logger.addLog("Inverse calculation failed: Determinant is zero");
            throw std::invalid_argument("Determinant is zero");
        }
        std::vector<std::vector<double>> result(2, std::vector<double>(2, 0));
        result[0][0] = matrix[1][1] / det;
        result[0][1] = -matrix[0][1] / det;
        result[1][0] = -matrix[1][0] / det;
        result[1][1] = matrix[0][0] / det;
        logger.addLog("Inverse calculation successful");
        return result;
    }

    // Calculate the transpose of a matrix
    static std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>> &matrix)
    {
        if (matrix.size() == 0)
        {
            logger.addLog("Transpose calculation failed: Empty matrix");
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
        logger.addLog("Transpose calculation successful");
        return result;
    }

    // Calculate the trace of a matrix
    static double trace(const std::vector<std::vector<double>> &matrix)
    {
        if (matrix.size() == 0)
        {
            logger.addLog("Trace calculation failed: Empty matrix");
            throw std::invalid_argument("Matrix is empty");
        }
        if (matrix.size() != matrix[0].size())
        {
            logger.addLog("Trace calculation failed: Incompatible matrix dimensions");
            throw std::invalid_argument("Matrix is not square");
        }
        double trace = 0.0;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            trace += matrix[i][i];
        }
        logger.addLog("Trace calculation successful");
        return trace;
    }

    // Calculate the rank of a matrix
    static size_t rank(const std::vector<std::vector<double>> &matrix)
    {
        if (matrix.size() == 0)
        {
            logger.addLog("Rank calculation failed: Empty matrix");
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
        logger.addLog("Rank calculation successful");
        return rank;
    }

};
// Definition of the static logger member
Logger MathOperations::logger = Logger("MathOperations.log");
#endif // MATHOPERATIONS_HPP
