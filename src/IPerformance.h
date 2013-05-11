#ifndef ROCNROLL_IPERFORMANCE_H
#define ROCNROLL_IPERFORMANCE_H

using namespace std;

class IPerformance {
  public:
    virtual void printYAML(const string& name, const string& indent) = 0;
    virtual void printYAML() = 0;
    virtual void compute() = 0;

    virtual void makeFinite() = 0;
};
#endif
