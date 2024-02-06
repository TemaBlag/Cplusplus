#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QFrame>
#include <QGridLayout>

class Cursors : public QWidget {

 public:
     Cursors(QWidget *parent = 0);
};

Cursors::Cursors(QWidget *parent)
    : QWidget(parent) {

  QFrame *frame1 = new QFrame(this); // создаем виджет
  frame1->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
  frame1->setCursor(Qt::WaitCursor); // задаем тип курсора SizeAllCursor для фрейма
//SizeAllCursor
  QFrame *frame2 = new QFrame(this); // создаем виджет
  frame2->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
  frame2->setCursor(Qt::WaitCursor); // задаем тип курсора WaitCursor для фрейма

  QFrame *frame3 = new QFrame(this); // создаем виджет
  frame3->setFrameStyle(QFrame::Box); // устанавливаем рамки фрейма
  frame3->setCursor(Qt::WaitCursor); // задаем тип курсора PointingHandCursor для фрейма

  // Группируем все фреймы в одну строку
  QGridLayout *grid = new QGridLayout(this);
  grid->addWidget(frame1, 0, 0);
  grid->addWidget(frame2, 0, 1);
  grid->addWidget(frame3, 0, 2);

  setLayout(grid);
}

int main(int argc, char *argv[]) {



  QApplication app(argc, argv);

  Cursors window;

  window.resize(350, 150);
  window.setWindowTitle("Icon");
  window.setWindowIcon(QIcon("D:\\C++\\FirstProject\\pic.ico"));
  window.setToolTip("QWidget");
  window.show();

  return app.exec();
}
