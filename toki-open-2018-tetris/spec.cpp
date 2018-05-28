#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;


vector<string> NON_TRIVIAL_TO_PERFECT_CLEAR = {"STJ", "ZTL", "SLJ", "ZJL", "TJ", "TL", "TTTJ", "TTTL", "TTLJ", "TTJL", "LTTJ", "LTTL", "LTLJ", "LTJL", "JTTJ", "JTTL", "JTLJ", "JTJL"};

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    string S;
    
    void InputFormat() {
        LINE(N, Q);
        LINE(S);
    }

    void GradingConfig() {
        TimeLimit(1);
    }

    void StyleConfig() {
        CustomScorer();
    }

    void Constraints() {
        CONS(1 <= N && N <= 200);
        CONS(0 <= Q && Q <= 1);
        CONS(S.length() == N);
        CONS(consistsOnlyOf(S, "OTJLSZ"));
    }

    void Subtask1() {
        Points(3);

        CONS(consistsOnlyOf(S, "O"));
    }

    void Subtask2() {
        Points(15);

        CONS(consistsOnlyOf(S, "OJL"));
    }

    void Subtask3() {
        Points(23);

        CONS(N <= 18);
    }

    void Subtask4() {
        Points(37);

        CONS(Q == 0);
    }

    void Subtask5() {
        Points(22);
    }

private:
    bool consistsOnlyOf(string s, string charset) {
        int len = s.length();
        for (int i = 0; i < len; i++) {
            if (charset.find(s[i]) == string::npos) return false;
        }
        return true;
    }
};


class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({3, 5});

        Input({"5 1", "TSJJL"});
    }

    void SampleTestCase2() {
        Subtasks({1, 2, 3, 5});

        Input({"4 1", "OOOO"});
    }

    void SampleTestCase3() {
        Subtasks({1, 2, 3, 4, 5});

        Input({"4 0", "OOOO"});
    }
    
    void SampleTestCase4() {
        Subtasks({3, 5});

        Input({"6 1", "SZSZSZ"});
    }

    // 1 <= N <= 18, Q = 0, Only "O"
    void TestGroup1() {
        Subtasks({1, 2, 3, 4, 5});
    
        CASE(N = 1, Q = 0, fullRandom("O"));
        CASE(N = 2, Q = 0, fullRandom("O"));
        CASE(N = 17, Q = 0, fullRandom("O"));
        CASE(N = 18, Q = 0, fullRandom("O"));
    }
    
    // 1 <= N <= 18, Q = 0, Only "OJL"
    void TestGroup2() {
        Subtasks({2, 3, 4, 5});
        
        CASE(N = 1, Q = 0, fullRandom("J"));
        CASE(N = 1, Q = 0, fullRandom("L"));
        
        CASE(N = 17, Q = 0, fullRandom("OJL"));
        CASE(N = 18, Q = 0, fullRandom("OJL"));
        
        CASE(N = 2, Q = 0, S = "LL");
        CASE(N = 2, Q = 0, S = "LJ");
        CASE(N = 2, Q = 0, S = "JL");
        CASE(N = 2, Q = 0, S = "JJ");
        
        CASE(N = 15, Q = 0, fullRandom("JL"));
        CASE(N = 16, Q = 0, fullRandom("J"));
        CASE(N = 17, Q = 0, fullRandom("L"));
        CASE(N = 18, Q = 0, fullRandom("JL"));
    }
    
    // 1 <= N <= 18, Q = 0, All letters
    void TestGroup3() {
        Subtasks({3, 4, 5});
        
        CASE(N = 1, Q = 0, fullRandom("T"));
        CASE(N = 1, Q = 0, fullRandom("S"));
        CASE(N = 1, Q = 0, fullRandom("Z"));
        
        CASE(N = 5, Q = 0, S = "STTLJ");
        CASE(N = 9, Q = 0, S = "ZSTJZTLTL");
        CASE(N = 9, Q = 0, S = "ZSTJZTLTJ");
        CASE(N = 5, Q = 0, S = "TSTJL");
        CASE(N = 8, Q = 0, S = "TZTLSTJL");
        CASE(N = 8, Q = 0, S = "TSTJZTLL");
        CASE(N = 5, Q = 0, S = "TSLJL");
        CASE(N = 7, Q = 0, S = "SLLLLLJ");
        CASE(N = 5, Q = 0, S = "STJLJ");
        CASE(N = 5, Q = 0, S = "SLJLJ");
        CASE(N = 5, Q = 0, S = "SLLLJ");
        CASE(N = 4, Q = 0, S = "SSLJ");
        CASE(N = 4, Q = 0, S = "SZLJ");
        CASE(N = 4, Q = 0, S = "SSJL");
        CASE(N = 4, Q = 0, S = "SZJL");
        CASE(N = 4, Q = 0, S = "SSLL");
        CASE(N = 4, Q = 0, S = "ZZLL");

        CASE(N = 18, Q = 0, S = "SZSZSZTLTJTLTJTLTJ");
        CASE(N = 18, Q = 0, S = "ZSZSZSTJTLTJTLTJTL");

        CASE(N = 11, Q = 0, S = "SZSTLTJTLTJ");
        CASE(N = 11, Q = 0, S = "ZSZTJTLTJTL");
        
        for (int i = 0; i < NON_TRIVIAL_TO_PERFECT_CLEAR.size(); i++) {
            string tmp = NON_TRIVIAL_TO_PERFECT_CLEAR[i];
            CASE(N = tmp.length(), Q = 0, S = tmp);
        }
        
        CASE(Q = 0, fullAppend(10));
        CASE(Q = 0, fullAppend(18));
        
        CASE(Q = 0, fullAppendButMiddle(10));
        CASE(Q = 0, fullAppendButMiddle(18));
        
        CASE(Q = 0, fullRandomButCompleted(18));
        CASE(Q = 0, fullRandomButCompleted(18));
        
        CASE(Q = 0, manySZ(18));
        CASE(Q = 0, manySZ(18));
        
        CASE(Q = 0, manySZButCompleted(18));
        CASE(Q = 0, manySZButCompleted(18));
        CASE(Q = 0, manySZButCompleted(18, false));
        
        CASE(N = 18, Q = 0, fullRandom("TSZ"));
        CASE(N = 18, Q = 0, fullRandom("TLJ"));
        CASE(N = 18, Q = 0, fullRandom("SZLJ"));
        
        CASE(N = 17, Q = 0, fullRandom("OTJLSZ"));
        CASE(N = 18, Q = 0, fullRandom("OTJLSZ"));
    }
    
    // 19 <= N <= 200, Q = 0, Only "O"
    void TestGroup4() {
        Subtasks({1, 2, 4, 5});
        
        CASE(N = 200, Q = 0, fullRandom("O"));
    }
    
    // 19 <= N <= 200, Q = 0, Only "OJL"
    void TestGroup5() {
        Subtasks({2, 4, 5});
        
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 0, fullRandom("OJL"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 0, fullRandom("OJL"));
        
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 0, fullRandom("JL"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 0, fullRandom("JL"));
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 0, fullRandom("L"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 0, fullRandom("L"));
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 0, fullRandom("J"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 0, fullRandom("J"));
        
        CASE(N = 197, Q = 0, fullRandom("JL"));
        CASE(N = 198, Q = 0, fullRandom("J"));
        CASE(N = 199, Q = 0, fullRandom("L"));
        CASE(N = 200, Q = 0, fullRandom("JL"));
    }
    
    // 19 <= N <= 200, Q = 0, All letters
    void TestGroup6() {
        Subtasks({4, 5});
        
        CASE(Q = 0, fullAppend(142));
        CASE(Q = 0, fullAppend(200));
        
        CASE(Q = 0, fullAppendButMiddle(142));
        CASE(Q = 0, fullAppendButMiddle(200));
        
        CASE(Q = 0, fullRandomButCompleted(200));
        CASE(Q = 0, fullRandomButCompleted(200));
        CASE(Q = 0, fullRandomButCompleted(200));
        
        CASE(Q = 0, manySZ(199));
        CASE(Q = 0, manySZ(200));
        
        CASE(Q = 0, manySZButCompleted(199));
        CASE(Q = 0, manySZButCompleted(200));
        CASE(Q = 0, manySZButCompleted(200, false));
        
        CASE(N = 200, Q = 0, fullRandom("TSZ"));
        CASE(N = 200, Q = 0, fullRandom("TLJ"));
        CASE(N = 200, Q = 0, fullRandom("SZLJ"));
        
        CASE(N = 199, Q = 0, fullRandom("OTJLSZ"));
        CASE(N = 200, Q = 0, fullRandom("OTJLSZ"));

        CASE(N = 198, Q = 0, S = "SZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJ");
        CASE(N = 198, Q = 0, S = "ZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTL");

        CASE(N = 200, Q = 0, S = "SZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLTJ");
        CASE(N = 200, Q = 0, S = "ZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJTL");
    }
    
    // 1 <= N <= 18, Q = 1, Only "O"
    void TestGroup7() {
        Subtasks({1, 2, 3, 5});
        
        CASE(N = 1, Q = 1, fullRandom("O"));
        CASE(N = 2, Q = 1, fullRandom("O"));
        CASE(N = 17, Q = 1, fullRandom("O"));
        CASE(N = 18, Q = 1, fullRandom("O"));
    }
    
    // 1 <= N <= 18, Q = 1, Only "OJL"
    void TestGroup8() {
        Subtasks({2, 3, 5});
        
        CASE(N = 1, Q = 1, fullRandom("J"));
        CASE(N = 1, Q = 1, fullRandom("L"));
        
        CASE(N = 17, Q = 1, fullRandom("OJL"));
        CASE(N = 18, Q = 1, fullRandom("OJL"));
        
        CASE(N = 2, Q = 1, S = "LL");
        CASE(N = 2, Q = 1, S = "LJ");
        CASE(N = 2, Q = 1, S = "JL");
        CASE(N = 2, Q = 1, S = "JJ");
        
        CASE(N = 15, Q = 1, fullRandom("JL"));
        CASE(N = 16, Q = 1, fullRandom("J"));
        CASE(N = 17, Q = 1, fullRandom("L"));
        CASE(N = 18, Q = 1, fullRandom("JL"));
    }
    
    // 1 <= N <= 18, Q = 1, All letters
    void TestGroup9() {
        Subtasks({3, 5});
    
        CASE(N = 1, Q = 1, fullRandom("T"));
        CASE(N = 1, Q = 1, fullRandom("S"));
        CASE(N = 1, Q = 1, fullRandom("Z"));
    
        CASE(N = 5, Q = 1, S = "STTLJ");
        CASE(N = 9, Q = 1, S = "ZSTJZTLTL");
        CASE(N = 9, Q = 1, S = "ZSTJZTLTJ");
        CASE(N = 5, Q = 1, S = "TSTJL");
        CASE(N = 8, Q = 1, S = "TZTLSTJL");
        CASE(N = 8, Q = 1, S = "TSTJZTLL");
        CASE(N = 5, Q = 1, S = "TSLJL");
        CASE(N = 7, Q = 1, S = "SLLLLLJ");
        CASE(N = 5, Q = 1, S = "STJLJ");
        CASE(N = 5, Q = 1, S = "SLJLJ");
        CASE(N = 5, Q = 1, S = "SLLLJ");
        CASE(N = 4, Q = 1, S = "SSLJ");
        CASE(N = 4, Q = 1, S = "SZLJ");
        CASE(N = 4, Q = 1, S = "SSJL");
        CASE(N = 4, Q = 1, S = "SZJL");
        CASE(N = 4, Q = 1, S = "SSLL");
        CASE(N = 4, Q = 1, S = "ZZLL");
        
        for (int i = 0; i < NON_TRIVIAL_TO_PERFECT_CLEAR.size(); i++) {
            string tmp = NON_TRIVIAL_TO_PERFECT_CLEAR[i];
            CASE(N = tmp.length(), Q = 1, S = tmp);
        }
        
        CASE(Q = 1, fullAppend(10));
        CASE(Q = 1, fullAppend(18));
        
        CASE(Q = 1, fullAppendButMiddle(10));
        CASE(Q = 1, fullAppendButMiddle(18));
        
        CASE(Q = 1, fullRandomButCompleted(18));
        CASE(Q = 1, fullRandomButCompleted(18));
        
        CASE(Q = 1, manySZ(18));
        CASE(Q = 1, manySZ(18));
        
        CASE(Q = 1, manySZButCompleted(18));
        CASE(Q = 1, manySZButCompleted(18));
        CASE(Q = 1, manySZButCompleted(18, false));
        
        CASE(N = 18, Q = 1, fullRandom("TSZ"));
        CASE(N = 18, Q = 1, fullRandom("TLJ"));
        CASE(N = 18, Q = 1, fullRandom("SZLJ"));
        
        CASE(N = 17, Q = 1, fullRandom("OTJLSZ"));
        CASE(N = 18, Q = 1, fullRandom("OTJLSZ"));

        CASE(N = 18, Q = 1, S = "SZSZSZTLTJTLTJTLTJ");
        CASE(N = 18, Q = 1, S = "ZSZSZSTJTLTJTLTJTL");

        CASE(N = 11, Q = 1, S = "SZSTLTJTLTJ");
        CASE(N = 11, Q = 1, S = "ZSZTJTLTJTL");
    }
    
    // 19 <= N <= 200, Q = 1, Only "O"
    void TestGroup10() {
        Subtasks({1, 2, 5});
        
        CASE(N = 200, Q = 1, fullRandom("O"));
    }
    
    // 19 <= N <= 200, Q = 1, Only "OJL"
    void TestGroup11() {
        Subtasks({2, 5});
        
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 1, fullRandom("OJL"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 1, fullRandom("OJL"));
        
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 1, fullRandom("JL"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 1, fullRandom("JL"));
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 1, fullRandom("L"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 1, fullRandom("L"));
        CASE(N = 2 * rnd.nextInt(10, 100) - 1, Q = 1, fullRandom("J"));
        CASE(N = 2 * rnd.nextInt(10, 100), Q = 1, fullRandom("J"));
        
        CASE(N = 197, Q = 1, fullRandom("JL"));
        CASE(N = 198, Q = 1, fullRandom("J"));
        CASE(N = 199, Q = 1, fullRandom("L"));
        CASE(N = 200, Q = 1, fullRandom("JL"));
    }
    
    // 19 <= N <= 200, Q = 1, All letters
    void TestGroup12() {
        Subtasks({5});
        
        CASE(Q = 1, fullAppend(142));
        CASE(Q = 1, fullAppend(200));
        
        CASE(Q = 1, fullAppendButMiddle(142));
        CASE(Q = 1, fullAppendButMiddle(200));
        
        CASE(Q = 1, fullRandomButCompleted(200));
        CASE(Q = 1, fullRandomButCompleted(200));
        CASE(Q = 1, fullRandomButCompleted(200));
        
        CASE(Q = 1, manySZ(199));
        CASE(Q = 1, manySZ(200));
        
        CASE(Q = 1, manySZButCompleted(199));
        CASE(Q = 1, manySZButCompleted(200));
        CASE(Q = 1, manySZButCompleted(200, false));
        
        CASE(N = 200, Q = 1, fullRandom("TSZ"));
        CASE(N = 200, Q = 1, fullRandom("TLJ"));
        CASE(N = 200, Q = 1, fullRandom("SZLJ"));
        
        CASE(N = 199, Q = 1, fullRandom("OTJLSZ"));
        CASE(N = 200, Q = 1, fullRandom("OTJLSZ"));

        CASE(N = 198, Q = 1, S = "SZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJ");
        CASE(N = 198, Q = 1, S = "ZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSZSTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTLTJTL");

        CASE(N = 200, Q = 1, S = "SZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTSZSTLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLLTJTLTJ");
        CASE(N = 200, Q = 1, S = "ZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTZSZTJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJJTLTJTL");
    }

private:
    void fullRandom(string charset) {
        int len = charset.length();
        S = "";
        
        for (int i = 0; i < N; i++) {
            int x = rnd.nextInt(len);
            S += charset[x];
        }
    }
    
    void fullAppend(int maxlen) {
        N = 0;
        S = "";
        
        while (true) {
            int x = rnd.nextInt(NON_TRIVIAL_TO_PERFECT_CLEAR.size());
            string tmp = NON_TRIVIAL_TO_PERFECT_CLEAR[x];
            if (N + tmp.length() > maxlen) break;
            
            S += tmp;
            N += tmp.length();
        }
    }
    
    void fullAppendButMiddle(int maxlen) {
        N = 0;
        S = "";
        
        while (true) {
            int x = rnd.nextInt(NON_TRIVIAL_TO_PERFECT_CLEAR.size());
            string tmp = NON_TRIVIAL_TO_PERFECT_CLEAR[x];
            if (N + tmp.length() > maxlen) break;
            
            if (N == 0 || rnd.nextInt(100) < 30) {
                x = rnd.nextInt(2) * N;
            } else {
                x = rnd.nextInt(1, N-1);
            }
            S.insert(x, tmp);
            N += tmp.length();
        }
    }
    
    void manySZ(int maxlen) {
        stack<int> st;
        N = 0;
        S = "";
        
        for (int i = 0; i < maxlen; i++) {
            char c;
            
            if (rnd.nextInt(100) < 50) {
                if (st.empty()) {
                    string tmp = "SZ";
                    c = tmp[rnd.nextInt(tmp.length())];
                } else {
                    if (st.top() == 1 || st.top() == 3) {
                        c = 'Z';
                    } else {
                        c = 'S';
                    }
                }
            } else {
                string tmp = "OTJL";
                c = tmp[rnd.nextInt(tmp.length())];
            }
            
            S += c;
            N++;
            if (c == 'O') {
                // nothing
            } else if (c == 'T') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) {st.pop(); st.push(4);}
                else if (st.top() == 2) {st.pop(); st.push(3);}
                else if (st.top() == 3) {st.pop(); st.push(2);}
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'J') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1 || st.top() == 3) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2) st.pop();
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'L') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2 || st.top() == 4) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) st.pop();
                else if (st.top() == 3) {st.pop(); st.push(2);}
            } else if (c == 'S') {
                if (st.empty()) st.push(3);
                else if (st.top() == 2 || st.top() == 4) st.push(3);
            } else if (c == 'Z') {
                if (st.empty()) st.push(4);
                else if (st.top() == 1 || st.top() == 3) st.push(4);
            }
        }
    }
    
    void manySZButCompleted(int maxlen, bool with_o = true) {
        stack<int> st;
        N = 0;
        S = "";
        
        for (int i = 0; i < 0.3 * maxlen; i++) {
            char c;
            
            if (rnd.nextInt(100) < 50) {
                if (st.empty()) {
                    string tmp = "SZ";
                    c = tmp[rnd.nextInt(tmp.length())];
                } else {
                    if (st.top() == 1 || st.top() == 3) {
                        c = 'Z';
                    } else {
                        c = 'S';
                    }
                }
            } else {
                string tmp = with_o ? "OTJL" : "TJL";
                c = tmp[rnd.nextInt(tmp.length())];
            }
            
            S += c;
            N++;
            if (c == 'O') {
                // nothing
            } else if (c == 'T') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) {st.pop(); st.push(4);}
                else if (st.top() == 2) {st.pop(); st.push(3);}
                else if (st.top() == 3) {st.pop(); st.push(2);}
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'J') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1 || st.top() == 3) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2) st.pop();
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'L') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2 || st.top() == 4) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) st.pop();
                else if (st.top() == 3) {st.pop(); st.push(2);}
            } else if (c == 'S') {
                if (st.empty()) st.push(3);
                else if (st.top() == 2 || st.top() == 4) st.push(3);
            } else if (c == 'Z') {
                if (st.empty()) st.push(4);
                else if (st.top() == 1 || st.top() == 3) st.push(4);
            }
        }
        
        while (!st.empty()) {
            vector<string> tmp3 = {"TJ", "LJ"};
            vector<string> tmp4 = {"TL", "JL"};
        
            if (st.top() == 1) {S += "L"; N += 1;}
            else if (st.top() == 2) {S += "J"; N += 1;}
            else if (st.top() == 3) {S += tmp3[rnd.nextInt(2)]; N += 2;}
            else if (st.top() == 4) {S += tmp4[rnd.nextInt(2)]; N += 2;}
            st.pop();
        }
    }
    
    void fullRandomButCompleted(int maxlen) {
        stack<int> st;
        N = 0;
        S = "";
        
        for (int i = 0; i < 0.5 * maxlen; i++) {
            string charset = "OTJLSZ";
            char c = charset[rnd.nextInt(charset.length())];
            
            S += c;
            N++;
            if (c == 'O') {
                // nothing
            } else if (c == 'T') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) {st.pop(); st.push(4);}
                else if (st.top() == 2) {st.pop(); st.push(3);}
                else if (st.top() == 3) {st.pop(); st.push(2);}
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'J') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1 || st.top() == 3) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2) st.pop();
                else if (st.top() == 4) {st.pop(); st.push(1);}
            } else if (c == 'L') {
                if (st.empty()) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 2 || st.top() == 4) st.push(rnd.nextInt(1, 2));
                else if (st.top() == 1) st.pop();
                else if (st.top() == 3) {st.pop(); st.push(2);}
            } else if (c == 'S') {
                if (st.empty()) st.push(3);
                else if (st.top() == 2 || st.top() == 4) st.push(3);
            } else if (c == 'Z') {
                if (st.empty()) st.push(4);
                else if (st.top() == 1 || st.top() == 3) st.push(4);
            }
        }
        
        while (!st.empty()) {
            vector<string> tmp3 = {"TJ", "LJ"};
            vector<string> tmp4 = {"TL", "JL"};
        
            if (st.top() == 1) {S += "L"; N += 1;}
            else if (st.top() == 2) {S += "J"; N += 1;}
            else if (st.top() == 3) {S += tmp3[rnd.nextInt(2)]; N += 2;}
            else if (st.top() == 4) {S += tmp4[rnd.nextInt(2)]; N += 2;}
            st.pop();
        }
    }
};
