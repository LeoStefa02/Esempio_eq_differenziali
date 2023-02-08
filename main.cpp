#include "./EquazioniDifferenziali/EquazioniDifferenziali.h"
#include "./FunzioneVettoriale.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include <vector>

using namespace std;

TGraph moto(EquazioneDifferenzialeBase* eq_diff, const FunzioneVettorialeBase& f, vector<double> x, double h, double Ds) {
    TGraph moto;
    unsigned int n_step = Ds / h;
    double t = 0;
    for(unsigned int i = 0; i < n_step; i++) {
        moto.AddPoint(x[0], x[1]);
        x = eq_diff->passo(t, x, h, f);
    }
    return moto;
}

vector<TGraph> grafici_alpha(EquazioneDifferenzialeBase* eq_diff, FunzioneVettoriale& f, vector<double> x, double h, double Ds) {
    vector<TGraph> grafici;
    f.set_alpha(1);
    grafici.push_back(moto(eq_diff, f, x, h, Ds));

    f.set_alpha(-1);
    grafici.push_back(moto(eq_diff, f, x, h, Ds));

    return grafici;
}

int main() {

    TApplication app("", 0, 0);

    FunzioneVettoriale eq(0);
    Eulero eulero;
    RungeKutta kutta;

    double prec = 0.1;
    double D_theta = 40 * M_PI;
    double h = 0.001;
    unsigned int n_step = D_theta / h;

    vector<double> x {1, 0, 0, -1};

    double h_s_eulero = eulero.h_stimato(0.1, x, eq, n_step, h);
    double h_s_kutta = kutta.h_stimato(0.1, x, eq, n_step, h);

    cout << "h stimato eulero: " << h_s_eulero << endl;
    cout << "h stimato kutta: " << h_s_kutta << endl;

    TCanvas canvas;
    canvas.Divide(4);

    vector<TGraph> grafici_eulero = grafici_alpha(&eulero, eq, x, h_s_eulero, D_theta);

    for(int i = 0; i < grafici_eulero.size(); i++) {
        canvas.cd(i + 1);
        grafici_eulero[i].Draw();
    }

    x = {1.1, 0, 0, -1};
    vector<TGraph> grafici_kutta = grafici_alpha(&eulero, eq, x, h_s_eulero, D_theta);

    for(int i = 0; i < grafici_kutta.size(); i++) {
        canvas.cd(i + 3);
        grafici_kutta[i].Draw();
    }

    app.Run();


}