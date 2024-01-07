#include "graph.h"
#include "calculator.h"
#include "ui_graph.h"
#include <iostream>

#include "qcustomplot.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::slot(QString str, double xmin, double xmax, double ymin,
                 double ymax) {
  x.clear();
  y.clear();
  ui->gr->xAxis->setRange(xmin, xmax);
  ui->gr->yAxis->setRange(ymin, ymax);
  // ui->gr->setInteraction(QCP::iRangeZoom, true);
  // ui->gr->setInteraction(QCP::iRangeDrag, true);
  QString temp = str; 
  QByteArray ba = temp.toLatin1();
  char *str1 = ba.data();
  Notation n;
  n.get_postfix(&str1);
//  my_struct *a = postfix(str1);
  N = 500;
  h = (xmax - xmin)/N;
  int i = 0;

  X = xBegin;

  for (X = xmin; X <= xmax; X += h) {
    if (X <= xmax) {
      double ans = n.polish(X);
      if (!std::isnan(ans) && !std::isinf(ans)) {
      x.push_back(X);
      y.push_back(ans);
      }
    }
  }
//  free(a);
  ui->gr->addGraph();
//  ui->gr->graph(0)->addData(x, y);
  ui->gr->replot();
}
