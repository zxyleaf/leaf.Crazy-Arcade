#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gamescene.h>
#include <QSoundEffect>
#include <mypushbutton.h>
#include <QGraphicsView>
#include <QMainWindow>
extern QGraphicsView * view;
extern QVector<GameObject *> board;
extern QTimer * nowtime;
extern MyPushButton *s;
extern MyPushButton *t;
extern MyPushButton *b;
extern int page;
extern QSoundEffect * bk;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
    bool begin = 0;
  explicit MainWindow(QWidget *parent = nullptr);
  void loadScene(GameScene *gameScene);
  void loadScene1(GameScene *gameScene);
  void loadScene2(GameScene *gameScene);
  void loadScenetool(GameScene *gameScene);
  ~MainWindow();
  GameScene *gameScene;
  GameObject * timelist;
  GameObject * pretimelist;
public slots:
  int myclock();
 private:
  Ui::MainWindow *ui;
  int second = 0;
  friend class map;
};
extern MainWindow *Mainone;
#endif  // MAINWINDOW_H_
