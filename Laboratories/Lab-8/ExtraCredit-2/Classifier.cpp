#include "Classifier.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#define M_PI 3.14159265359

// ImageData

ImageData::ImageData(const std::vector<std::vector<double>>& imageData) : data(imageData) {}

std::vector<std::vector<double>> ImageData::getData() const 
{
    return data;
}

size_t ImageData::size() const 
{
    if (!data.empty()) 
    {
        return data[0].size();
    }
    else 
    {
        return 0;
    }
}


// KNNClassifier

KNNClassifier::KNNClassifier(int k) : k(k) {}

void KNNClassifier::fit(const ImageData& trainImages, const std::vector<int>& trainLabels) 
{
    // Store the training data and labels for future prediction
    this->trainImages = trainImages.getData();
    this->trainLabels = trainLabels;

}

// The Euclidean distance measures the straight - line distance between two points in Euclidean space.
double KNNClassifier::calculateEuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2) const 
{
    // Ensure that both vectors have the same size
    if (vec1.size() != vec2.size()) 
    {
        throw std::invalid_argument("Vector sizes are not equal");
    }

    // Calculate the Euclidean distance between the two vectors
    double distance = 0.0;
    for (size_t i = 0; i < vec1.size(); i++) 
    {
        // Calculate the difference between corresponding elements
        double diff = vec1[i] - vec2[i];
        // Square the difference and accumulate it
        distance += diff * diff;
    }
    // Take the square root of the accumulated sum to get the Euclidean distance
    distance = std::sqrt(distance);

    return distance;
}


// The predict function takes the testImages as input and returns a vector of predicted labels for each test image.
std::vector<int> KNNClassifier::predict(const ImageData& testImages) 
{
    // Get the test image matrix
    std::vector<std::vector<double>> testImageMatrix = testImages.getData();
    // Create a vector to store the predicted labels
    std::vector<int> predictions;

    // Iterate over each test image
    for (const std::vector<double>& testImage : testImageMatrix) 
    {
        // Create a vector to store distances between the test image and training images
        std::vector<std::pair<int, double>> distances;

        // Calculate distances between the test image and each training image
        for (size_t i = 0; i < trainImages.size(); ++i) 
        {
            // Calculate the Euclidean distance between the test image and a training image
            double distance = calculateEuclideanDistance(testImage, trainImages[i]);
            // Store the index and distance as a pair
            distances.emplace_back(i, distance);
        }

        // Sort distances in ascending order
        std::sort(distances.begin(), distances.end(),
            [](const std::pair<int, double>& a, const std::pair<int, double>& b) 
            {
                // Comparator function to compare distances
                return a.second < b.second;
            });

        // Count the occurrences of each label among the k nearest neighbors
        std::unordered_map<int, int> labelCounts;
        for (int i = 0; i < k; ++i) 
        {
            // Get the index and label of the nearest neighbor
            int index = distances[i].first;
            int label = trainLabels[index];

            // Increment the count for the label
            labelCounts[label]++;
        }

        // Find the label with the maximum count
        int maxCount = 0;
        int predictedLabel = -1;
        for (const auto& entry : labelCounts) 
        {
            if (entry.second > maxCount) 
            {
                // Update the maximum count and predicted label if a higher count is found
                maxCount = entry.second;
                predictedLabel = entry.first;
            }
        }

        // Store the predicted label for the test image
        predictions.push_back(predictedLabel);
    }

    // Return the vector of predicted labels
    return predictions;
}

bool KNNClassifier::save(const std::string& filepath) 
{
    std::ofstream file(filepath);
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file for saving: " << filepath << std::endl;
        return false;
    }

    // Save the k value, training images, and training labels to the file
    file << k << std::endl;

    // Save training images
    for (const std::vector<double>& image : trainImages) 
    {
        for (double pixel : image) 
        {
            file << pixel << " ";
        }
        file << std::endl;
    }

    // Save training labels
    for (int label : trainLabels) 
    {
        file << label << std::endl;
    }

    file.close();

    return true;  // Return success/failure status
}

bool KNNClassifier::load(const std::string& filepath) 
{
    std::ifstream file(filepath);
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file for loading: " << filepath << std::endl;
        return false;
    }

    // Load the k value, training images, and training labels from the file
    file >> k;

    std::string line;
    std::getline(file, line); // Read the newline character after reading k

    trainImages.clear();
    trainLabels.clear();

    // Load training images
    while (std::getline(file, line) && !line.empty()) 
    {
        std::vector<double> image;
        std::stringstream ss(line);
        double pixel;
        while (ss >> pixel) 
        {
            image.push_back(pixel);
        }
        trainImages.push_back(image);
    }

    // Load training labels
    int label;
    while (file >> label) 
    {
        trainLabels.push_back(label);
    }

    file.close();
    return true;
    return true;  // Return success/failure status
}

double KNNClassifier::eval(const ImageData& testImages) 
{
    double accuracy = 0.0; 
    // Predict labels for the test images
    std::vector<int> predictedLabels = predict(testImages);
    // Get the test image matrix
    std::vector<std::vector<double>> testImageMatrix = testImages.getData();

    // Check if the sizes of predicted labels and test images are equal
    if (predictedLabels.size() != testImageMatrix.size()) 
    {
        // Print an error message and return 0.0 if the sizes mismatch
        std::cout << "Error: Size mismatch between predicted labels and test images." << std::endl;
        return 0.0;
    }

    // Count the number of correct predictions
    int correctCount = 0;
    for (size_t i = 0; i < predictedLabels.size(); i++) 
    {
        // Compare the predicted label with the true label of the test image
        if (predictedLabels[i] == testImageMatrix[i][0]) 
        {
            correctCount++;
        }
    }

    // Calculate and return the accuracy
    return static_cast<double>(correctCount) / predictedLabels.size();
}


// BayesClassifier

// The function is used to train the classifier using the provided training images and labels.
void BayesClassifier::fit(const ImageData& trainImages, const std::vector<int>& trainLabels)
{
    // Store the training data and labels
    this->trainImages = trainImages.getData();
    this->trainLabels = trainLabels;

    // Calculate the counts of each label in the training data
    calculateLabelCounts(trainLabels);

    // Calculate the prior probabilities of each label
    int totalSamples = trainLabels.size();
    calculatePriorProbabilities(totalSamples);

    // Calculate the statistics of each feature
    calculateFeatureStats();
}

void BayesClassifier::calculateLabelCounts(const std::vector<int>& trainLabels)
{
    // Clear the existing label counts
    labelCounts.clear();

    // Count the occurrences of each label
    for (int label : trainLabels)
    {
        labelCounts[label]++;
    }
}

void BayesClassifier::calculatePriorProbabilities(int totalSamples)
{
    // Clear the existing prior probabilities
    priorProbabilities.clear();

    // Calculate the prior probability for each label
    for (const auto& entry : labelCounts)
    {
        int label = entry.first;
        int count = entry.second;
        double priorProbability = static_cast<double>(count) / totalSamples;
        priorProbabilities[label] = priorProbability;
    }
}


// The calculateFeatureStats function is responsible for calculating the feature statistics for each label in the training data.
void BayesClassifier::calculateFeatureStats()
{
    // Clear the existing feature statistics
    featureStats.clear();

    // Iterate over each label and calculate feature statistics for that label
    for (const auto& entry : labelCounts)
    {
        int label = entry.first;
        FeatureStats stats;

        // Calculate feature statistics for each feature
        for (size_t i = 0; i < trainImages[0].size(); i++)
        {
            double sum = 0.0;
            int count = 0;

            // Calculate the sum of values and the count for the current feature and label
            for (size_t j = 0; j < trainImages.size(); j++)
            {
                if (trainLabels[j] == label)
                {
                    sum += trainImages[j][i];
                    count++;
                }
            }

            // Calculate the mean for the current feature and label
            double mean = sum / count;

            // Calculate the sum of squared differences and the variance for the current feature and label
            double sumSquares = 0.0;
            for (size_t j = 0; j < trainImages.size(); ++j)
            {
                if (trainLabels[j] == label)
                {
                    double diff = trainImages[j][i] - mean;
                    sumSquares += diff * diff;
                }
            }

            // Calculate the standard deviation for the current feature and label
            double variance = sumSquares / count;
            double stddev = std::sqrt(variance);

            // Store the mean and standard deviation in the feature statistics
            stats.means.push_back(mean);
            stats.stdevs.push_back(stddev);

            // Store the feature statistics for the current label
            featureStats[label] = stats;
        }
    }
}


// The predict function is responsible for predicting the labels of the test images using the trained Bayes classifier.
std::vector<int> BayesClassifier::predict(const ImageData& testImages)
{
    // Get the test image data
    std::vector<std::vector<double>> testImageMatrix = testImages.getData();
    std::vector<int> predictions;

    // Iterate over each test image
    for (const std::vector<double>& testImage : testImageMatrix)
    {
        // Initialize variables for predicting the label and calculating the maximum posterior probability
        int predictedLabel = -1;
        double maxPosterior = 0.0;

        // Iterate over each label's prior probability
        for (const auto& entry : priorProbabilities)
        {
            int label = entry.first;
            double prior = entry.second;

            // Calculate the likelihood of the test image belonging to the current label
            double likelihood = 1.0;
            const FeatureStats& stats = featureStats[label];
            for (size_t i = 0; i < testImage.size(); i++)
            {
                double x = testImage[i];
                double mean = stats.means[i];
                double stddev = stats.stdevs[i];

                // Calculate the exponent of the Gaussian distribution
                double exponent = -0.5 * (std::pow((x - mean) / stddev, 2));

                // Calculate the probability density function (PDF) value for the feature
                double pdf = (1.0 / (stddev * std::sqrt(2 * M_PI))) * std::exp(exponent);

                // Multiply the likelihood with the PDF value for the feature
                likelihood *= pdf;
            }

            // Calculate the posterior probability by multiplying the prior with the likelihood
            double posterior = prior * likelihood;

            // Update the predicted label if the current posterior probability is the maximum so far
            if (posterior > maxPosterior)
            {
                maxPosterior = posterior;
                predictedLabel = label;
            }
        }

        // Store the predicted label for the current test image
        predictions.push_back(predictedLabel);
    }

    // Return the vector of predicted labels
    return predictions;
}


bool BayesClassifier::save(const std::string& filepath) 
{
    std::ofstream file(filepath);
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file for saving: " << filepath << std::endl;
        return false;
    }

    // Save the prior probabilities and feature statistics to the file
    for (const auto& entry : priorProbabilities) 
    {
        int label = entry.first;
        double prior = entry.second;
        file << "Label: " << label << ", Prior: " << prior << std::endl;

        const FeatureStats& stats = featureStats[label];
        for (size_t i = 0; i < stats.means.size(); ++i) 
        {
            file << "Feature " << i + 1 << ": Mean = " << stats.means[i] << ", StdDev = " << stats.stdevs[i] << std::endl;
        }

        file << std::endl;
    }

    file.close();
    return true;
}

bool BayesClassifier::load(const std::string& filepath) 
{
    std::ifstream file(filepath);
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file for loading: " << filepath << std::endl;
        return false;
    }

    priorProbabilities.clear();
    featureStats.clear();

    std::string line;
    while (std::getline(file, line)) 
    {
        if (line.empty()) 
        {
            continue;
        }

        int label = -1;
        double prior = 0.0;
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix >> label >> prefix >> prior;
        priorProbabilities[label] = prior;

        FeatureStats stats;
        while (std::getline(file, line) && !line.empty()) 
        {
            std::istringstream iss(line);
            std::string featurePrefix;
            int featureIndex;
            double mean, stddev;
            iss >> featurePrefix >> featureIndex >> prefix >> mean >> prefix >> stddev;
            stats.means.push_back(mean);
            stats.stdevs.push_back(stddev);
        }

        featureStats[label] = stats;
    }

    file.close();
    return true;
}


// The eval function is responsible for evaluating the performance of the Bayes classifier 
// by calculating its accuracy on the given test images.
double BayesClassifier::eval(const ImageData& testImages)
{
    // Predict labels for the test images
    std::vector<int> predictedLabels = predict(testImages);

    // Get the test image data
    std::vector<std::vector<double>> testImageMatrix = testImages.getData();

    // Check for size mismatch between predicted labels and test images
    if (predictedLabels.size() != testImageMatrix.size())
    {
        std::cout << "Error: Size mismatch between predicted labels and test images." << std::endl;
        return 0.0;
    }

    // Count the number of correctly predicted labels
    int correctCount = 0;
    for (size_t i = 0; i < predictedLabels.size(); i++)
    {
        if (predictedLabels[i] == testImageMatrix[i][0])
        {
            correctCount++;
        }
    }

    // Calculate and return the accuracy
    return static_cast<double>(correctCount) / predictedLabels.size();
}

