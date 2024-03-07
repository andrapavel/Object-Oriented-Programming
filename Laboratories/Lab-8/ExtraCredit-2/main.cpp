#include <iostream>
#include "Classifier.h"

int main()
{
    // Create training data
    std::vector<std::vector<double>> trainData = { {1.0, 2.0}, {2.0, 1.0}, {2.0, 3.0}, {3.0, 2.0} };
    std::vector<int> trainLabels = { 0, 1, 0, 1 };
    ImageData trainImages(trainData);

    // Create test data
    std::vector<std::vector<double>> testData = { {1.5, 2.5}, {2.5, 1.5} };
    ImageData testImages(testData);

    // Use KNNClassifier
    KNNClassifier knnClassifier(1);  // Set k = 1
    knnClassifier.fit(trainImages, trainLabels);
    std::vector<int> knnPredictions = knnClassifier.predict(testImages);

    // Use BayesClassifier
    BayesClassifier bayesClassifier;
    bayesClassifier.fit(trainImages, trainLabels);
    std::vector<int> bayesPredictions = bayesClassifier.predict(testImages);

    // Print predictions
    std::cout << "KNN Predictions: ";
    for (int label : knnPredictions) 
    {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    std::cout << "Bayes Predictions: ";
    for (int label : bayesPredictions) 
    {
        std::cout << label << " ";
    }
    std::cout << std::endl;

    return 0;
}