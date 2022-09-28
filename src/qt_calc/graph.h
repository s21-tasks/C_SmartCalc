#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
extern "C" {
#include "../c_files/s21_smartcalc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();
  my_struct *buff_exec;

signals:
  void firstWindow(); // Сигнал для первого окна на открытие

private:
  Ui::Graph *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;

public slots:
  void slot(QString str, double xmin, double xmax, double ymin, double ymax);
};

#endif // GRAPH_H
