#include "../include/Replay.h"

namespace chessgame
{
    void Replay::print_onscreen(const std::string& inputfile)
    {
        std::ifstream& is(inputfile);
        if (is.is_open())
        {
            while (is.good())
            {
                /* code */

            }
            
        }
    }

    void Replay::print_on_file(std::ifstream& ist,std::ofstream& ost)
    {

    }
    
}