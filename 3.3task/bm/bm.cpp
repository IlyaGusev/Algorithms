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
int KMPCount(ifstream&, const string&);
int KMP(const string&, const string&);

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
	cout<<needle<<endl;
	cout<<suff_table<<endl;
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
            if (k==-1){
                buffer.substr((int)buffer.length()-nlen-1);
                break;
            }
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

int KMP(const string& haystack, const string& needle){
    int hlen = haystack.length();
    int nlen = needle.length();
    if (hlen<nlen) return -1;

    char splitter = '#';
    string temp = needle + splitter + haystack;
    int len = nlen+hlen+1;
    vector<int> pi(len);
    pi[0] = 0;
    int k = 0;
    for(int i=1; i<len; i++){
        while (k>0 && temp[k]!=temp[i])
            k = pi[k-1];
        if (temp[k] == temp[i])
            k++;
        pi[i] = k;
        if (pi[i]==nlen)
            return i-2*nlen;
    }
    return -1;
}

int KMPCount(ifstream& fin, const string& needle){
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
            k = KMP(buffer, needle);
            if (k==-1){
                buffer.substr((int)buffer.length()-nlen-1);
                break;
            }
            else{
                buffer = buffer.substr(k+nlen);
                answer++;
            }
        }
    }
    fin.close();
    fin.open("input.txt");
    return answer;
}



namespace{
    TEST(BoyerMooreTest, Test1){
        string h = "abcabbbajlkfl;jaslfj";
        EXPECT_EQ(BoyerMoore(h,"abcabc"), 2);
    }
    /*TEST(BoyerMooreTest, Test1){
        ifstream fin;
        fin.open("input.txt");
        EXPECT_EQ(BoyerMooreCount(fin, "Lear"), 201);
        EXPECT_EQ(BoyerMooreCount(fin, "Kent"), 134);
        EXPECT_EQ(BoyerMooreCount(fin, "Edmond"), 12);
        EXPECT_EQ(BoyerMooreCount(fin, "Flourish"), 4);
        EXPECT_EQ(BoyerMooreCount(fin, "Bastard"), 11);
        EXPECT_EQ(BoyerMooreCount(fin, "Gloster"), 22);
        fin.close();
    }
    TEST(KMPTest, Test1){
        string h = "ababbadeccaabadbabbad";
        EXPECT_EQ(KMP(h,"abbad"), 2);
    }
    TEST(KMPTest, Test2){
        ifstream fin;
        fin.open("input.txt");
        EXPECT_EQ(BoyerMooreCount(fin, "Lear"), 201);
        EXPECT_EQ(BoyerMooreCount(fin, "Kent"), 134);
        EXPECT_EQ(BoyerMooreCount(fin, "Edmond"), 12);
        EXPECT_EQ(BoyerMooreCount(fin, "Flourish"), 4);
        EXPECT_EQ(BoyerMooreCount(fin, "Bastard"), 11);
        EXPECT_EQ(BoyerMooreCount(fin, "Gloster"), 22);
        fin.close();
    }*/
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
