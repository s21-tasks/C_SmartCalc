#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <list>
#include <QMessageBox>
#include <graph.h>

#include "../Model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

  Notation post_exec();

private:
  Ui::Calculator *ui;
  Graph *graphWindow;

private slots:
  void NumPressed();
  void MathPressed();
  void TrigPressed();
  //    void ACPressed();
  void EqualPressed();

  void on_ButtonGraph_clicked();

signals:
  void signal(QString str, double xmin, double xmax, double ymin, double ymax);
};
#endif // CALCULATOR_H
