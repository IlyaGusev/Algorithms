#include "../prefix.hpp"
#include <gtest/gtest.h>
#include <climits>
#include <unordered_map>
#include <fstream>

using std::min;
using std::max;
using std::ifstream;
int BoyerMoore(const string&, const string&);
int BoyerMooreCount(ifstream&, const string&);

int BoyerMoore(const string& haystack, const string& needle){
    int hlen = haystack.length();
    int nlen = needle.length();
    if (hlen<nlen) return -1;

    int stop_table[UCHAR_MAX+1];
    for(int i=0; i<UCHAR_MAX+1; i++)
        stop_table[i] = -1;
    for (int i=0; i<nlen-1; i++)
        stop_table[(int)needle[i]] = i;

    vector<int> suff_table(nlen+1);
    string rneedle(needle.rbegin(), needle.rend());
    vector<int> n_pi = prefix_func(needle);
    vector<int> rn_pi = prefix_func(rneedle);
    for (int i=0; i<nlen+1; i++)
		suff_table[i] = nlen-n_pi.back();
	for (int i=0; i<nlen; i++) {
		int j = rn_pi[i];
		suff_table[j] = min(suff_table[j], i-rn_pi[i]+1);
	}
	int hpos = 0;
    while(hpos<=hlen-nlen)
    {
        int npos = nlen-1;
        while(needle[npos]==haystack[npos+hpos])
        {
            if(npos == 0)
                return hpos;
            --npos;
        }
        hpos += max(suff_table[nlen-npos-1], npos-stop_table[haystack[npos + hpos]]);
    }
    return -1;
}

int BoyerMooreCount(ifstream& fin, const string& needle){
    int blen = 2000;
    int nlen = needle.length();
    string buffer = "";
    int answer = 0;
    while(!fin.eof()){
        int k=0;
        while(k!=blen && !fin.eof()){
            char ch;
            fin>>ch;
            buffer = buffer + ch;
            k++;
        }
        k=0;
        while(k!=-1){
            k = BoyerMoore(buffer, needle);
            if (k==-1) break;
            else{
                buffer = buffer.substr(k+nlen);
                answer++;
            }
            if ((int)buffer.length()<2*nlen)
                break;
        }
    }
    fin.close();
    fin.open("input.txt");
    return answer;
}



namespace{
    class BoyerMooreTest : public ::testing::Test{
    protected:
        ifstream fin;
        BoyerMooreTest(){}
        virtual ~BoyerMooreTest() {}
        virtual void SetUp() { fin.open("input.txt"); }
        virtual void TearDown() { fin.close();}
    };
    TEST_F(BoyerMooreTest, Test1){
        string h = "ababbadeccaabadbabbad";
        cout<<BoyerMoore(h,"abbad")<<endl;
    }
    TEST_F(BoyerMooreTest, Test){
        EXPECT_EQ(BoyerMooreCount(fin, "Lear"), 201);
        EXPECT_EQ(BoyerMooreCount(fin, "Kent"), 134);
        EXPECT_EQ(BoyerMooreCount(fin, "Edmond"), 12);
        EXPECT_EQ(BoyerMooreCount(fin, "Flourish"), 4);
        EXPECT_EQ(BoyerMooreCount(fin, "Bastard"), 11);
        EXPECT_EQ(BoyerMooreCount(fin, "Gloster"), 22);
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
