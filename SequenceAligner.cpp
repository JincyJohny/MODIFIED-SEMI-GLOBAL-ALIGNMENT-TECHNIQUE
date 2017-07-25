#include "SequenceAligner.h"
#include <algorithm>
#include <iostream>

SequenceAligner::SequenceAligner(std::string sensSample_,
                                 std::string contentSample_)
{
    _rows = sensSample_.length();
    int columns = contentSample_.length();
    _matrix = new int *[_rows + 1];
    for(int i = 0; i <= _rows; i++)
        _matrix[i] = new int[columns + 1];
    _matchScore = 3;
    _misMatchScore = -1;
    _gapSenseScore = 0; 
    _gapContScore = -1;

    _score = makeAlignementScore(sensSample_, contentSample_);
}


int SequenceAligner::makeAlignementScore(std::string& sensSample_,
                                         std::string& contentSample_)
{
    int m = sensSample_.length(); 
    int k = contentSample_.length();
    int top;
    int left;
    int diagonal;

    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <= k; j++)
        {
            if( (i == 0) || (j == 0))
            {
                _matrix[i][j] = 0;
            }
            else
            {
                if( (i == m) || (j == k))
                {
                    left = _matrix[i][j-1];
                    top = _matrix[i-1][j];
                }
                else
                {
                    left = std::max(0, _matrix[i][j-1] + _gapSenseScore);
                    top = std::max(0, _matrix[i-1][j] + _gapContScore);
                }
                if(sensSample_[i - 1] == contentSample_[j - 1])
                {
                    diagonal = _matrix[i-1][j-1] + _matchScore;
                }
                else
                {
                    diagonal = _matrix[i-1][j-1] + _misMatchScore;
                }

                _matrix[i][j] = std::max({top, left, diagonal});
            }
        }
    }

    return _matrix[m][k]; 
}
