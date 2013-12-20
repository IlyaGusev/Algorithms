#include <list>
#include <queue>
using namespace std;
const int N=4;
const int BORDER = 50;
const int dx[4] = { 0, 1, 0,-1};
const int dy[4] = {-1, 0, 1, 0};
const char direction[4] = {'l','d','r','u'};
const int rev[4]= {2, 3, 0, 1};
struct Puzzle{
        vector<vector<int> > field;
        pair<int, int> zero;
        vector<char> solution;
        vector<char> final_solution;
        bool have_answer;
        int max_distation;
        Puzzle() : field(N, vector<int>(N, 0)), zero(), solution(), final_solution(), have_answer(){
            //ifstream fin("input.txt");
            for (int i=0; i<N; i++)
                for (int j=0; j<N; j++){
                    cin>>field[i][j];
                    if (field[i][j]==0)
                        zero=make_pair(i,j);
                }
            //fin.close();
        }
        int heuristic(){
            int h=0;
            for (int i=0; i<N; i++)
                for (int j=0; j<N; j++){
                    if (field[i][j]!=0){
                        int di = (field[i][j]-1)/N-i;
                        int dj = (field[i][j]-1)%N-j;
                        if (di>=0) h+=di; else h+=-di;
                        if (dj>=0) h+=dj; else h+=-dj;
                    }
                    else{
                        h+=(N-1-i);
                        h+=(N-1-j);
                    }
                }
            return h;
        }
        bool has_solution()
        {
            int sum = 0;
            int a[N*N];
            int k = -1;
            for (int i=0; i<N; i++)
                for (int j=0; j<N; j++){
                    k ++;
                    a[k] = field[i][j];
                }
            for (int i=0; i<N*N; i++)
                for (int j=i; j<N*N; j++)
                    if (a[j]!=0 && a[j]<a[i])
                        sum++;
            for (int i=0; i<N; i++)
                for (int j=0; j<N; j++)
                    if (field[i][j] == 0) sum += i + 1;
            if (N==3)
            return (sum % 2) ? true : false;
            if (N==4)
            return (sum % 2) ? false : true;
        }
        vector<char> solve(){
            if (!has_solution()){
                return solution;
            }
            int h = heuristic();
            for (int i=h; i <= BORDER && !have_answer; i++)
            {
                max_distation = i;
                next_step(0, -1);
            }
            if (!have_answer)
            {
                return final_solution;
            }
            return final_solution;
        }
        void next_step(int level, int previous){
            if (have_answer) return;
            int h = heuristic();
            if (h == 0){
                have_answer = true;
                final_solution = solution;
                return;
            }
            if (level + h > max_distation) return;

            for (int i = 0; i < 4 && !have_answer; i++)
            if (zero.first + dx[i] >= 0 &&
                zero.second + dy[i] >= 0 &&
                zero.first + dx[i] < 4 &&
                zero.second + dy[i] < 4 &&
                rev[i] != previous)
            {
                swap(field[zero.first][zero.second], field[zero.first+dx[i]][zero.second+dy[i]]);
                zero.first = zero.first+dx[i];
                zero.second = zero.second+dy[i];
                solution.push_back(direction[i]);
                next_step(level+1, i);
                solution.pop_back();
                zero.first = zero.first-dx[i];
                zero.second = zero.second-dy[i];
                swap(field[zero.first][zero.second], field[zero.first+dx[i]][zero.second+dy[i]]);
            }
        }

};

int main(){
    Puzzle states;
    if (states.has_solution()){
        cout<<"YES"<<endl;
        vector<char> c = states.solve();
        for (int i=0; i<c.size(); i++)
            cout<<c[i];
    } else {
        cout<<"NO"<<endl;
    }
}
