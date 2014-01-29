#ifndef READ_HPP_INCLUDED
#define READ_HPP_INCLUDED
#include <string>
#include <fstream>
using std::ifstream;
using std::string;
using std::ios;
namespace my{
    string read(const string& filename);
    string read(const string& filename)//read all file
    {
        ifstream f;
        f.open(filename);
        string str;
        if(f.good())
        {
          f.seekg( 0, ios::end );
          str.resize( f.tellg() );
          f.seekg( 0, ios::beg );

          f.read( (char*)str.data(), str.size() );
        };
        f.close();
        return str;
    }
}

#endif // READ_HPP_INCLUDED
