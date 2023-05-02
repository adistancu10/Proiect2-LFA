#include <iostream>
#include <vector>
using namespace std;

const int stari = 100;
const int inputs = 100;
int delta[stari][inputs];

void stariinacc(int numStates, bool r[]) {
    r[0] = true;
    bool verif = true;
    while (verif) {
        verif = false;
        for (int i = 0; i < numStates; i++) {
            if (!r[i]) continue;
            for (int j = 0; j < inputs; j++) {
                int urmStare = delta[i][j];
                if (urmStare == -1) continue;
                if (!r[urmStare]) {
                    r[urmStare] = true;
                    verif = true;
                }
            }
        }
    }
}

void stariEchiv(int numStates, bool r[], bool echiv[][stari]) {
    for (int i = 0; i < numStates; i++) {
        if (!r[i]) continue;
        for (int j = 0; j < numStates; j++) {
            if (!r[j]) continue;
            if (i == j) {
                echiv[i][j] = true;
                continue;
            }
            bool s = (r[i] && r[j] &&
                              ((i == 0 && j == 0) ||
                               (i > 0 && j > 0 && echiv[i - 1][j - 1])));
            bool verific = false;
            for (int k = 0; k < inputs; k++) {
                int urm1 = delta[i][k];
                int urm2 = delta[j][k];
                if (!r[urm1] || !r[urm2]) continue;
                if (echiv[urm1][urm2]) continue;
                verific = true;
                break;
            }
            if (!s || verific) {
                echiv[i][j] = false;
            } else {
                echiv[i][j] = true;
            }
        }
    }
}

void minimizeDFA(int numStates, int numInputs, int stareincep, bool stariFinale[]) {

    bool r[stari] = {false};
    r[stareincep] = true;
    stariinacc(numStates, r);
    bool echiv[stari][stari] = {false};
    stariEchiv(numStates, r, echiv);

    int minNumStates = 0;
    int minStartState = -1;
    bool minstariFinale[stari] = {false};
    int minDelta[stari][inputs] = {-1};
    int starem[stari] = {-1};
    for (int i = 0; i < numStates; i++) {
        if (!r[i]) continue;
        if (starem[i] == -1) {
            starem[i] = minNumStates;
            if (stariFinale[i]) minstariFinale[minNumStates] = true;
            if (i == stareincep) minStartState = minNumStates;
            minNumStates++;
        }
        for (int j = 0; j < numInputs; j++) {
            int urmStare = delta[i][j];
            if (!r[urmStare]) continue;
            if (minDelta[starem[i]][j] == -1) {
                minDelta[starem[i]][j] = starem[urmStare];
            }
        }
    }

    cout << "Numar stari: " << minNumStates << endl;
    cout << "Starea initiala: " << minStartState << endl;
    cout << "Stari finale: ";
    for (int i = 0; i < minNumStates; i++) {
        if (minstariFinale[i]) cout << i << " ";
    }
    cout << endl << "Matrice de tranzitii: " << endl;
    for (int i = 0; i < minNumStates; i++) {
        for (int j = 0; j < numInputs; j++) {
            cout << minDelta[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {



    int numStates, numInputs, stareincep;
    fin >> numStates >> numInputs >> stareincep;
    bool stariFinale[stari] = {false};
    for (int i = 0; i < numStates; i++) {
        int isFinal;
        fin >> isFinal;
        if (isFinal) stariFinale[i] = true;
    }
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numInputs; j++) {
            fin >> delta[i][j];
        }
    }


    minimizeDFA(numStates, numInputs, stareincep, stariFinale);
    return 0;
}
