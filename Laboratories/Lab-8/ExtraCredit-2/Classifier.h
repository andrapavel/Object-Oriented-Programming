#pragma once

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>
#include <unordered_map>

// Class representing the image data
class ImageData 
{
private:
    std::vector<std::vector<double>> data;

public:

    ImageData(const std::vector<std::vector<double>>& imageData);
    std::vector<std::vector<double>> getData() const;

    size_t size() const;
};

class Classifier 
{
public:
    virtual void fit(const ImageData& trainImages, const std::vector<int>& trainLabels) = 0;
    virtual std::vector<int> predict(const ImageData& testImages) = 0;
    virtual bool save(const std::string& filepath) = 0;
    virtual bool load(const std::string& filepath) = 0;
    virtual double eval(const ImageData& testImages) = 0;
};


// KNNClassifier

class KNNClassifier : public Classifier 
{
private:
    int k; // Number of neighbors
    std::vector<std::vector<double>> trainImages;
    std::vector<int> trainLabels;

public:
    KNNClassifier(int k);
    void fit(const ImageData& trainImages, const std::vector<int>& trainLabels) override;
    std::vector<int> predict(const ImageData& testImages) override;
    bool save(const std::string& filepath) override;
    bool load(const std::string& filepath) override;
    double eval(const ImageData& testImages) override;

    double calculateEuclideanDistance(const std::vector<double>& vec1, const std::vector<double>& vec2) const;
};

class FeatureStats 
{
public:
    std::vector<double> means;
    std::vector<double> stdevs;
};

class BayesClassifier : public Classifier 
{
private:
    std::vector<double> prior;
    std::vector<std::vector<double>> likelihood;

    std::vector<std::vector<double>> trainImages;
    std::vector<int> trainLabels;
    std::unordered_map<int, int> labelCounts;
    std::unordered_map<int, double> priorProbabilities;
    std::unordered_map<int, FeatureStats> featureStats;

public:
    void fit(const ImageData& trainImages, const std::vector<int>& trainLabels) override;
    std::vector<int> predict(const ImageData& testImages) override;
    bool save(const std::string& filepath) override;
    bool load(const std::string& filepath) override;
    double eval(const ImageData& testImages) override;

private:
    void calculateLabelCounts(const std::vector<int>& trainLabels);
    void calculatePriorProbabilities(int totalSamples);
    void calculateFeatureStats();
};

#endif  // CLASSIFIER_H
