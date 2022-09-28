#include "calculator.h"
#include "./ui_calculator.h"

double ans = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);

  ui->Answer->setText(QString::number(ans));
  QPushButton *numbuttons[10];
  for (int i = 0; i < 10; ++i) {
    QString butName = "Button" + QString::number(i);
    numbuttons[i] = Calculator::findChild<QPushButton *>(butName);
    connect(numbuttons[i], SIGNAL(released()), this, SLOT(NumPressed()));
  }
  connect(ui->Plus, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->Minus, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->Multi, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->Division, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->ButtonSkobka1, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->ButtonSkobka2, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->BSqr, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->BMod, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->ButtonDot, SIGNAL(released()), this, SLOT(MathPressed()));
  connect(ui->BSin, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BCos, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BTan, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BAsin, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BAcos, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BAtan, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BLn, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BLog, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->BSqrt, SIGNAL(released()), this, SLOT(TrigPressed()));
  connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(EqualPressed()));
}

Calculator::~Calculator() { delete ui; }

my_struct *Calculator::post_exec() {
  QString exec = ui->Display->text();
  QByteArray ba = exec.toLatin1();
  char *str = ba.data();
  return postfix(str);
}

void Calculator::NumPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString numval = button->text();
  QString displayVal = ui->Display->text();
  if (displayVal == "" || displayVal == "0" || displayVal == "0.0") {
    ui->Display->setText(numval);
  } else {
    QString val = displayVal + numval;
    ui->Display->setText(val);
  }
}

void Calculator::MathPressed() {
  QString displayVal = ui->Display->text();
  QPushButton *button = (QPushButton *)sender();
  QString butval = button->text();
  QString newval;
  if (butval == ".") {
    newval = displayVal + butval;
  } else {
    newval = displayVal + " " + butval + " ";
  }
  ui->Display->setText(newval);
}

void Calculator::TrigPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butval = button->text();
  QString displayVal = ui->Display->text();
  QString newval;
  newval = displayVal + " " + butval + "( ";
  ui->Display->setText(newval);
}

// void Calculator::ACPressed() {
//     ui->Display->setText("");
//     ui->Answer->setText("");
// }

void Calculator::EqualPressed() {
  QString xxx = ui->textX->text();
  double numX = xxx.toDouble();

  QString temp = ui->Display->text();
  QByteArray ba = temp.toLatin1();
  char *str = ba.data();
  my_struct *a = postfix(str);
  if (!validation(a)) {
    free(a);
    QMessageBox::warning(this, "Внимание", "Выражение введено неправильно.");
    return;
  }
  ui->Button1->setText(QString::number(numX));
  ans = polish(a, numX);

  ui->Answer->setText(QString::number(ans));
  free(a);
}

void Calculator::on_ButtonGraph_clicked() {
  QString temp = ui->Display->text();
  QByteArray ba = temp.toLatin1();
  char *str1 = ba.data();
  my_struct *test = postfix(str1);
  if (!validation(test)) {
    free(test);
    QMessageBox::warning(this, "Внимание", "Выражение введено неправильно.");
    return;
  }
  if (ui->xmin->text().toDouble() >= ui->xmax->text().toDouble() || (ui->xmin->text().toDouble() < -1e6) || (ui->xmax->text().toDouble() > 1e6)) {
    free(test);
    QMessageBox::warning(this, "Внимание", "Область определения указана неправильно.");
    return;
  }  
  if (ui->ymin->text().toDouble() >= ui->ymax->text().toDouble() || (ui->ymin->text().toDouble() < -1e6) || (ui->ymax->text().toDouble() > 1e6)) {
    free(test);
    QMessageBox::warning(this, "Внимание", "Область значения указана неправильно.");
    return;
  }
  delete graphWindow;
  graphWindow = new Graph();
  connect(this, &Calculator::signal, graphWindow, &Graph::slot);
  emit signal(ui->Display->text(), ui->xmin->text().toDouble(),
              ui->xmax->text().toDouble(), ui->ymin->text().toDouble(),
              ui->ymax->text().toDouble());
  graphWindow->show();
}
