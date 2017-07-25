#include "ComparableSampling.h"

ComparableSampling::ComparableSampling(std::string inputString_,
                                       int N_,
                                       int windowSize_)
                                      :_sampledList(inputString_.size(), '-')
{
    makeComparableSampling(inputString_, N_, windowSize_);
}

void ComparableSampling::makeComparableSampling(std::string inputString_,
                                                int N_,
                                                int windowSize_)
{
    std::string curCollectionList;
    std::string prevCollectionList;

    std::pair<char, char> eNewOld;

    curCollectionList = getMinimalList(inputString_.substr(0,windowSize_), N_);

    for(int i = 1; i <= (inputString_.size() - windowSize_); i++)
    {
        prevCollectionList = curCollectionList;
        curCollectionList = getMinimalList(inputString_.substr(i,windowSize_), N_);
        if(prevCollectionList != curCollectionList)
        {
           eNewOld = getCollectionDiff(prevCollectionList, curCollectionList); 
           updateSampledList(eNewOld, windowSize_, i);
        }
    }
}

std::string ComparableSampling::getMinimalList(std::string windowList_,
                                               int N_)
{
    std::sort(windowList_.begin(), windowList_.end());
    return windowList_.substr(0,N_);
}

std::pair<char, char> ComparableSampling::getCollectionDiff(std::string prev_,
                                                            std::string cur_)
{
    bool itemExist;
    char eNew;
    char eOld;

    std::string cur = cur_;
    std::string prev = prev_;  
    for(int i = 0; i < cur_.size(); i++)
    {
        itemExist = false;

        for(int j = 0; j < prev_.size(); j++)
        {
            if(cur_[i] == prev_[j])
            {
                prev_[j] = 0;
                itemExist = true;
                break;
            }
        }

        if(!itemExist)
        {
            eNew = cur_[i];
            break;
        }
    }

    int curAsciiSum = getAsciiSum(cur);
    int prevAsciiSum = getAsciiSum(prev);

    eOld = prevAsciiSum - (curAsciiSum - eNew);

    return std::make_pair(eNew, eOld); 
}

void ComparableSampling::updateSampledList(std::pair<char, char> eNewOld_,
                                           int windowSize_,
                                           int index_)
{
    if(eNewOld_.first < eNewOld_.second)
    {
        _sampledList[index_ + windowSize_ - 1] = eNewOld_.first;
    }

    else
    {
        _sampledList[index_ - 1] = eNewOld_.second;
    }
}

int ComparableSampling::getAsciiSum(const std::string& str_) const
{
    int sum = 0;
    for(auto& i : str_)
        sum += i;

    return sum;
}

std::string ComparableSampling::getSampledList() const
{
    return _sampledList;
}
