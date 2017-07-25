#include "ComparableSampling.h"
#include "SequenceAligner.h"


int main()
{

    ComparableSampling sampleObj("1519853248", 3, 6);
    ComparableSampling sampleObj1("165433368", 3, 6);

    std::cout << sampleObj.getSampledList() << std::endl;
    std::cout << sampleObj1.getSampledList() << std::endl;

    SequenceAligner a(sampleObj.getSampledList(),sampleObj1.getSampledList()  );
    std::cout << a._score << std::endl;
    return 0;
}

