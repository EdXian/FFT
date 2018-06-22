#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <cmath>
#include <complex>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/FFT>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "lpf.h"



#define pi 3.14159
using boost::multiprecision::cpp_dec_float_50;
using boost::multiprecision::cpp_dec_float_100;
using std::cout;
using std::endl;
using namespace Eigen;
#if 1
  typedef double FFTFloat;
#else
  typedef cpp_dec_float_100 FFTFloat;
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //lpf lpf1( 5 , 0.001);
 ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
 ui->customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
 double Fs = 1000;            // Sampling frequency
     double T = 1 / Fs;           // Sampling period
     int L = 1000;               // Length of signal
      double value = 0.0;
     std::vector<FFTFloat> timebuf(L);
     typedef std::complex<FFTFloat> C;
     std::vector<C> freqbuf;
     double t = 0;
      QVector<double> x2, y2;
      QVector<double> x3, y3;
     double last_value=0;
     double value2;
     for (int i = 0; i < L; i++) {

       value = 1*std::sin(2 * pi * 50 * t)
                       + std::sin(2 * pi * 100* t)
                       + std::sin(2 * pi *250 * t)+ std::sin(2 * pi *400 * t);
        x2.push_back( t*100);
        y2.push_back( value);
       //timebuf[i] = lpf1.filter(value );
        double a = 0.8;
       timebuf[i] = value  ;
        x3.push_back(t*100);
       y3.push_back((1-a)*value + a*last_value);
       last_value = value;

       t += T;
     }
     QVector<double> x, y;

     Eigen::FFT<FFTFloat> fft;
     fft.fwd(freqbuf, timebuf);
     cout << freqbuf.size() << endl;
     for (int i = 0; i < freqbuf.size(); i++) {
       const C &f = freqbuf[i];

       cout << i << " " << std::real(freqbuf[i]) << endl;
        x.push_back(i*0.001);
        y.push_back(-1*std::real(freqbuf[i]));
     }

     // create graph and assign data to it:




     ui->customPlot->addGraph();
     ui->customPlot->graph(0)->setData(x, y);
     // give the axes some labels:
     ui->customPlot->xAxis->setLabel("x");
     ui->customPlot->yAxis->setLabel("y");
     // set axes ranges, so we see all data:
     ui->customPlot->xAxis->setRange(0, 1);
     ui->customPlot->yAxis->setRange(-0.2, 0.2);
     ui->customPlot->replot();


     ui->customPlot2->addGraph();
     ui->customPlot2->graph(0)->setData(x2, y2);
     // give the axes some labels:
     ui->customPlot2->xAxis->setLabel("x");
     ui->customPlot2->yAxis->setLabel("y");
     // set axes ranges, so we see all data:
     ui->customPlot2->xAxis->setRange(0, 10);
     ui->customPlot2->yAxis->setRange(-2, 2);
     ui->customPlot2->replot();


     ui->customPlot3->addGraph();
     ui->customPlot3->graph(0)->setData(x3, y3);
     // give the axes some labels:
     ui->customPlot3->xAxis->setLabel("x");
     ui->customPlot3->yAxis->setLabel("y");
     // set axes ranges, so we see all data:
     ui->customPlot3->xAxis->setRange(0, 10);
     ui->customPlot3->yAxis->setRange(-2, 2);
     ui->customPlot3->replot();


}

MainWindow::~MainWindow()
{
    delete ui;
}
